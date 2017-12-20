#ifndef TEAM_COLOR
#define TEAM_COLOR

#include <FastLED.h>
#include "Arduino.h"

#define MAX_COLORS 4

struct TeamColor {
  CRGB colors[MAX_COLORS];
  int nColors;
};

TeamColor getMainColor(int teamID);

#endif
