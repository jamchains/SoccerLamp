#include <FastLED.h>
#include "Arduino.h"
#include "TeamColor.h"



TeamColor getMainColor(int teamID) {
  TeamColor ret;

  switch (teamID) {
    //    case 0:  {// Name
    //        ret.nColors = 3;
    //        ret.colors[0] = CRGB::Black;
    //        ret.colors[1] = CRGB::Black;
    //        ret.colors[2] = CRGB::Black;
    //        break;
    //      }
/**************** La Liga ****************/
    case 81:  {// Barcelona
        ret.nColors = 3;
        ret.colors[0] = CRGB::Brown;
        ret.colors[1] = CRGB::Blue;
        ret.colors[2] = CRGB::Red;
        break;
      }
    case 95:  {// Valencia
        ret.nColors = 4;
        ret.colors[0] = CRGB::Black;
        ret.colors[1] = CRGB::Red;
        ret.colors[2] = CRGB::White;
        ret.colors[3] = CRGB::Yellow;
        break;
      }
    case 78:  {// Club Atlético de Madrid
        ret.nColors = 3;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::Red;
        ret.colors[2] = CRGB::Blue;
        break;
      }
    case 86:  {// Real Madrid CF
        ret.nColors = 1;
        ret.colors[0] = CRGB::White;
        break;
      }
    case 559:  {// Sevilla FC
        ret.nColors = 2;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::Red;
        break;
      }
    case 94:  {// Villarreal CF
        ret.nColors = 1;
        ret.colors[0] = CRGB::Yellow;
        break;
      }
    case 82:  {// Getafe CF
        ret.nColors = 1;
        ret.colors[0] = CRGB::Blue;
        break;
      }
    case 745:  {// CD Leganes
        ret.nColors = 2;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::Blue;
        break;
      }
    case 298:  {// Girona FC
        ret.nColors = 1;
        ret.colors[0] = CRGB::White;
        break;
      }
    case 92:  {// Real Sociedad de Fútbol
        ret.nColors = 2;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::Blue;
        break;
      }
    case 558:  {// RC Celta de Vigo
        ret.nColors = 2;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::SkyBlue;
        break;
      }
    case 90:  {// Real Betis
        ret.nColors = 2;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::Green;
        break;
      }
    case 278:  {// SD Eibar
        ret.nColors = 1;
        ret.colors[0] = CRGB::Blue;
        break;
      }
    case 77:  {// Athletic Club Bilbao
        ret.nColors = 3;
        ret.colors[0] = CRGB::Red;
        ret.colors[1] = CRGB::Black;
        ret.colors[2] = CRGB::White;
        break;
      }
    case 88:  {// Levante UD
        ret.nColors = 2;
        ret.colors[0] = CRGB::Blue;
        ret.colors[1] = CRGB::Red;
        break;
      }
    case 80:  {// RCD Espanyol
        ret.nColors = 2;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::Blue;
        break;
      }
    case 560:  {// RC Deportivo La Coruna
        ret.nColors = 2;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::Blue;
        break;
      }
    case 263:  {// Deportivo Alavés
        ret.nColors = 1;
        ret.colors[0] = CRGB::White;
        break;
      }
    case 84:  {// Málaga CF
        ret.nColors = 2;
        ret.colors[0] = CRGB::White;
        ret.colors[1] = CRGB::Blue;
        break;
      }
    case 275:  {// UD Las Palmas
        ret.nColors = 2;
        ret.colors[0] = CRGB::Blue;
        ret.colors[1] = CRGB::Yellow;
        break;
      }

/**************** World Cup 2018 ****************/
      case 808:  {// Russia
          ret.nColors = 3;
          ret.colors[0] = CRGB::White;
          ret.colors[1] = CRGB::Blue;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 801:  {// Saudi Arabia
          ret.nColors = 2;
          ret.colors[0] = CRGB::Green;
          ret.colors[1] = CRGB::White;
          break;
      }
      case 825:  {// Egypt
          ret.nColors = 3;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Black;
          break;
      }
      case 758:  {// Uruguay
          ret.nColors = 3;
          ret.colors[0] = CRGB::Blue;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Yellow;
          break;
      }
      case 815:  {// Morocco
          ret.nColors = 2;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::Green;
          break;
      }
      case 840:  {// Iran
          ret.nColors = 3;
          ret.colors[0] = CRGB::Green;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 765:  {// Portugal
          ret.nColors = 3;
          ret.colors[0] = CRGB::Green;
          ret.colors[1] = CRGB::Red;
          ret.colors[2] = CRGB::Yellow;
          break;
      }
      case 760:  {// Spain
          ret.nColors = 2;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::Yellow;
          break;
      }
      case 773:  {// France
          ret.nColors = 3;
          ret.colors[0] = CRGB::Blue;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 779:  {// Australia
          ret.nColors = 3;
          ret.colors[0] = CRGB::Blue;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 832:  {// Peru
          ret.nColors = 2;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::White;
          break;
      }
      case 782:  {// Denmark
          ret.nColors = 2;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::White;
          break;
      }
      case 762:  {// Argentina
          ret.nColors = 3;
          ret.colors[0] = CRGB::LightBlue;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Yellow;
          break;
      }
      case 1066:  {// Iceland
          ret.nColors = 3;
          ret.colors[0] = CRGB::Blue;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 799:  {// Croatia
          ret.nColors = 3;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Blue;
          break;
      }
      case 776:  {// Nigeria
          ret.nColors = 2;
          ret.colors[0] = CRGB::Green;
          ret.colors[1] = CRGB::White;
          break;
      }
      case 793:  {// Costa Rica
          ret.nColors = 3;
          ret.colors[0] = CRGB::Blue;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 780:  {// Serbia
          ret.nColors = 3;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::Blue;
          ret.colors[2] = CRGB::White;
          break;
      }
      case 764:  {// Brazil
          ret.nColors = 3;
          ret.colors[0] = CRGB::Green;
          ret.colors[1] = CRGB::Yellow;
          ret.colors[2] = CRGB::Blue;
          break;
      }
      case 788:  {// Switzerland
          ret.nColors = 2;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::White;
          break;
      }
      case 759:  {// Germany
          ret.nColors = 3;
          ret.colors[0] = CRGB::Black;
          ret.colors[1] = CRGB::Red;
          ret.colors[2] = CRGB::Yellow;
          break;
      }
      case 769:  {// Mexico
          ret.nColors = 3;
          ret.colors[0] = CRGB::Green;
          ret.colors[1] = CRGB::White;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 792:  {// Sweden
          ret.nColors = 2;
          ret.colors[0] = CRGB::Blue;
          ret.colors[1] = CRGB::Yellow;
          break;
      }
      case 772:  {// Korea Republic
          ret.nColors = 3;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::Blue;
          ret.colors[2] = CRGB::White;
          break;
      }
      case 805:  {// Belgium
          ret.nColors = 3;
          ret.colors[0] = CRGB::Black;
          ret.colors[1] = CRGB::Yellow;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 1836:  {// Panama
          ret.nColors = 3;
          ret.colors[0] = CRGB::Blue;
          ret.colors[1] = CRGB::Red;
          ret.colors[2] = CRGB::White;
          break;
      }
      case 802:  {// Tunisia
        ret.nColors = 2;
        ret.colors[0] = CRGB::Red;
        ret.colors[1] = CRGB::White;
        break;
      }
      case 770:  {// England
          ret.nColors = 2;
          ret.colors[0] = CRGB::White;
          ret.colors[1] = CRGB::Red;
          break;
      }
      case 794:  {// Poland
          ret.nColors = 2;
          ret.colors[0] = CRGB::Red;
          ret.colors[1] = CRGB::White;
          break;
      }
      case 804:  {// Senegal
          ret.nColors = 3;
          ret.colors[0] = CRGB::Green;
          ret.colors[1] = CRGB::Yellow;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 818:  {// Colombia
          ret.nColors = 3;
          ret.colors[0] = CRGB::Yellow;
          ret.colors[1] = CRGB::Blue;
          ret.colors[2] = CRGB::Red;
          break;
      }
      case 766:  {// Japan
          ret.nColors = 2;
          ret.colors[0] = CRGB::White;
          ret.colors[1] = CRGB::Red;
          break;
      }

/**************** Control ****************/
      case 0: { // Turn off lights
        ret.nColors = 1;
        ret.colors[0] = CRGB::Black;
        break;
      }
    default: {  // Error
        ret.nColors = 1;
        ret.colors[0] = CRGB::Red;
        break;
      }
  }

  return ret;
}
