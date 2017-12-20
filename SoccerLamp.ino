#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>

#define FASTLED_ESP8266_RAW_PIN_ORDER
//#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
//#define FASTLED_ESP8266_D1_PIN_ORDER

// Disables pragma messages
#define FASTLED_INTERNAL

//Sometimes, especially on the esp8266, you might have better luck by just tweaking the re-try attempt code with:
//#define FASTLED_INTERRUPT_RETRY_COUNT 1 // Enable in case of LEDs flickering/jittering
//#define FASTLED_INTERRUPT_RETRY_COUNT 0
//#define FASTLED_ALLOW_INTERRUPTS 0  // Use with caution, might disable WiFi!
#include <FastLED.h>
//#include "LED.h"

#include "TeamColor.h"

#define NUM_COLORS 2
#define NUM_STANDINGS 4

#define SCORE_GOAL_DELAY 100
#define SCORE_LOOP_DELAY 2000
#define STANDINGS_DELAY 10000
#define BLEND_DELAY 10

// Non-authenticated clients are allowed for 100 requests per 24 hours (one every 14,4 minutes)
// Registered clients are allowed for 50 requests per minute by default
#define LIVE_UPDATE 1 * 60 * 1000  // 1 min
#define STANDINGS_UPDATE 5 * 60 * 1000  // 5 min

// XXX Will overflow after 49 days on
unsigned long timeLast = 0;
unsigned long timeNow = 0;

ESP8266WiFiMulti WiFiMulti;

const char* ssid = ".......";
const char* password = ".......";

const char* apiKey = ".......";

// TODO competitionId as parameter
const char* leagueTable = "http://api.football-data.org/v1/competitions/455/leagueTable";
const char* fixtures = "http://api.football-data.org/v1/competitions/455/fixtures?timeFrame=n1";

/* Standing Status */
TeamColor standingTeams[NUM_STANDINGS];

/* Live status */
bool liveGame = false;
TeamColor liveTeams[2];
int liveGoals[2];

//byte black[] = {0, 0, 0};
TeamColor black = getMainColor(0);

#define NUM_LEDS 12

CRGB leds[NUM_LEDS];

void setup() {
  // D10 (GPIO1) = may cause reset; D8 (GPIO15) = extra instructions, D0 is off limits!
  FastLED.addLeds<NEOPIXEL, D4>(leds, NUM_LEDS);
  FastLED.setCorrection(TypicalSMD5050);
  FastLED.setTemperature(StandardFluorescent);

  // limit my draw to 1A at 5v of power draw
  //FastLED.setMaxPowerInVoltsAndMilliamps(5,1000);

  FastLED.clear();
  test_leds();

  //delay(3000);

  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  // Might solve LED flickering issues
  //WiFi.setSleepMode(WIFI_NONE_SLEEP);

  WiFiMulti.addAP(ssid, password);

  // wait for WiFi connection
  // TODO Should we wait on the main loop, in case it gets disconnected?
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    delay(10000);
  }
  Serial.println("Connected!");
  
  Serial.print("Router IP: ");
  Serial.println(WiFi.softAPIP());

  Serial.printf("MAC address: %s\n", WiFi.BSSIDstr().c_str());

  // TODO Disable blue board led
  //  pinMode(LED_BUILTIN, OUTPUT);
  //  digitalWrite(LED_BUILTIN, HIGH);

  checkUpdates();
}


void loop() {
  //test_leds();

  // TODO migrate to this function
  //  EVERY_N_SECONDS(10) {
  //    checkUpdates();
  //  }

  timeNow = millis();

  //Serial.print(".");
  Serial.printf("Data is %d seconds outdated...\n", (timeNow - timeLast) / 1000);

  // TODO invert logic
  if (!liveGame) {
    /******************************* STANDINGS ***********************/
    CRGB new_leds[NUM_LEDS];

    for (int i = 0; i < NUM_STANDINGS; i++) {
      CRGB old_leds[NUM_LEDS];
      memcpy(old_leds, leds, NUM_LEDS * sizeof(CRGB));

      fill_team(new_leds, standingTeams[i]);

      for (int amount = 0; amount < 255; amount++) {
        blend(old_leds, new_leds, leds, NUM_LEDS, amount);
        FastLED.show();
        delay(BLEND_DELAY);
      }
      delay(STANDINGS_DELAY);
    }

    if ((timeNow - timeLast) >= STANDINGS_UPDATE) {
      checkUpdates();
    }
  }
  else {
    /********************************* LIVE ****************************/
    // TODO kiss
    int halfHomeDelay = (SCORE_LOOP_DELAY - 2 * liveGoals[0] * SCORE_GOAL_DELAY) / 2;
    int halfAwayDelay = (SCORE_LOOP_DELAY - 2 * liveGoals[1] * SCORE_GOAL_DELAY) / 2;

    //LED1.set_Color(LEDArray, liveColorHome);
    show_team(liveTeams[0]);
    delay(halfHomeDelay);

    for (int i = 0; i < liveGoals[0]; i++) {
      //LED1.set_Color(LEDArray, liveColorHome);
      show_team(liveTeams[0]);
      delay(SCORE_GOAL_DELAY);

      //LED1.set_Color(LEDArray, black);
      show_black();
      delay(SCORE_GOAL_DELAY);
    }
    //LED1.set_Color(LEDArray, liveColorHome);
    show_team(liveTeams[0]);
    delay(halfHomeDelay);

    //LED1.set_Color(LEDArray, liveColorAway);
    show_team(liveTeams[1]);
    delay(halfAwayDelay);
    for (int i = 0; i < liveGoals[1]; i++) {
      //LED1.set_Color(LEDArray, liveColorAway);
      show_team(liveTeams[1]);
      delay(SCORE_GOAL_DELAY);

      //LED1.set_Color(LEDArray, black);
      show_black();
      delay(SCORE_GOAL_DELAY);
    }
    //LED1.set_Color(LEDArray, liveColorAway);
    show_team(liveTeams[1]);
    delay(halfAwayDelay);

    if ((timeNow - timeLast) >= LIVE_UPDATE) {
      checkUpdates();
    }
  }
}


void checkUpdates() {
  getStandings();
  getLive();

  // TODO only update if return value is OK
  timeLast = millis();
}


/**
   Get standing scores
*/
int getStandings() {
  String payload = download(leagueTable);

  //Serial.println("Allocate JsonBuffer");
  const size_t bufferSize = JSON_ARRAY_SIZE(20)
                            + JSON_OBJECT_SIZE(3)
                            + 20 * JSON_OBJECT_SIZE(9)
                            + 4060;
  //const size_t BUFFER_SIZE = 20000;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  //Serial.println("Parse JSON object");
  JsonObject& root = jsonBuffer.parseObject(payload);

  if (!root.success()) {
    Serial.println("Parsing failed!");
    Serial.println(payload);
    return -1;
  }

  Serial.print("Standings: ");
  for (int i = 0; i < NUM_STANDINGS; i++) {
    int teamId = root["standing"][i]["teamId"];
    const char* teamName = root["standing"][i]["team"];

    standingTeams[i] = getMainColor(root["standing"][i]["teamId"]);
    Serial.printf("%s -> ", teamName);
  }
  Serial.println();

  return 1;
}

////////////////////////////////////////////////////////////////

/**
   Get Live scores
*/
int getLive() {
  String payload = download(fixtures);

  // TODO move to parse()
  //Serial.println("Allocate JsonBuffer");
  const size_t bufferSize = JSON_ARRAY_SIZE(4)
                            + 18 * JSON_OBJECT_SIZE(1)
                            + 5 * JSON_OBJECT_SIZE(2) + 3 * JSON_OBJECT_SIZE(3)
                            + 4 * JSON_OBJECT_SIZE(4) + 4 * JSON_OBJECT_SIZE(8)
                            + 2060;
  // FIXME Get the largest real possible
  DynamicJsonBuffer jsonBuffer(bufferSize);

  //Serial.println("Parse JSON object");
  JsonObject& root = jsonBuffer.parseObject(payload);

  if (!root.success()) {
    Serial.println("Parsing failed!");
    Serial.println(payload);
    return -1;
  }

  int count = root["count"];
  Serial.printf("%d match(es) in the next 24 hours.\n", count);

  liveGame = false;

  // Set to 0, just in case
  liveTeams[0] = black;
  liveTeams[1] = black;

  liveGoals[0] = 0;
  liveGoals[1] = 0;

  for (int i = 0; i < count; i++) {
    String status = root["fixtures"][i]["status"];
    // TODO more than one live game
    if (status.equals("IN_PLAY")) {
      liveGame = true;

      int homeTeamId = root["fixtures"][i]["homeTeamId"];
      int awayTeamId = root["fixtures"][i]["awayTeamId"];

      const char* homeTeamName = root["fixtures"][i]["homeTeamName"];
      const char* awayTeamName = root["fixtures"][i]["awayTeamName"];

      liveTeams[0] = getMainColor(homeTeamId);
      liveTeams[1] = getMainColor(awayTeamId);

      liveGoals[0] = root["fixtures"][i]["result"]["goalsHomeTeam"];
      liveGoals[1] = root["fixtures"][i]["result"]["goalsAwayTeam"];

      Serial.printf("Live: %s (%d) X %s  (%d)\n", homeTeamName, liveGoals[0], awayTeamName, liveGoals[1]);

      return 1;

    }
  }

  return -1;
}


String download(const char* url) {
  // TODO retry in case of any error (maybe on the calling function?)
  HTTPClient http;

  //Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  http.begin(url); //HTTP
  http.addHeader("X-Auth-Token", apiKey);
  http.addHeader("X-Response-Control", "minified");

  //Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode <= 0) {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return "";
  }

  // HTTP header has been send and Server response header has been handled
  //Serial.printf("[HTTP] GET... code: %d\n", httpCode);

  if (httpCode != HTTP_CODE_OK) {
    Serial.printf("[HTTP] HTTP Code is not OK, got code %s\n", httpCode);
    http.end();
    return "";
  }

  // file found at server
  String payload = http.getString();

  http.end();

  //Serial.println(payload);
  return payload;
}

void partial_fill_solid(struct CRGB* leds, int startPixel, int endPixel, const struct CRGB& color)
{
  for (int i = startPixel; i < endPixel; i++) {
    leds[i] = color;
  }
}

void show_black() {
  FastLED.clear();
  FastLED.show();
}

void fill_team(struct CRGB* dest, TeamColor teamColor) {
  // Don't display NUM_COLORS if the team doesn't have all of them...
  int numColors = MIN(teamColor.nColors, NUM_COLORS);

  int ledIncrement = NUM_LEDS / numColors;
  for (int j = 0; j < numColors; j++) {
    partial_fill_solid(dest, j * ledIncrement, (j + 1) * ledIncrement, teamColor.colors[j]);
  }
}

void show_team(TeamColor teamColor) {
  fill_team(leds, teamColor);
  FastLED.show();
}

void test_leds() {
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(1000);
}
