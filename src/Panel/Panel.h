#ifndef __PANEL_H__
#define __PANEL_H__

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "../Fonts/dotmat10pt7b_v2.h"
#include "../Fonts/font.h"
#include "../State/State.h"
#include "../RTC/RTC.h"
#include "../Program/Program.h"

#define PANEL_W 16
#define PANEL_H 16
#define PANEL_COUNT PANEL_H *PANEL_W

#define DELAY_TIME 1000   // in ms
#define DELAY_STRING 20   // in ms -  change by 1px/30ms = 64px/2s
#define DELAY_PROGRAM 33 // in ms

#define LOWER_CASE 8
#define UPPER_CASE 12
#define WHITESPACE 3
#define NUMBER 11
#define ONE 7
#define COLON 6

using namespace std;

typedef struct time
{
    int minutes = 0;
    int seconds = 0;
    bool decr = true;
} TIME;

class Panel
{
private:
    Adafruit_NeoMatrix *matrix;
    void init();
    
public:
    Panel();
    ~Panel();

    void run();
};

#endif