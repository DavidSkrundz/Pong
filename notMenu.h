
#ifndef ArduinoTemplate_notMenu_h
#define ArduinoTemplate_notMenu_h

#include <Adafruit_GFX.h>

#include "notDisplay.h"

char * nameString = "BattlePong";

void drawMainMenu()
{
	tft.fillScreen(BLACK);
    // Start match
	tft.setCursor(32, 80);
	tft.setTextColor(BLUE);
	tft.print(nameString);
    tft.drawRect(64, 40, 30, 10, WHITE);
    // Choose music

}

void drawGameMenu()
{
    tft.fillScreen(BLACK);
    // Continue
    tft.drawRect(64, 80, 30, 10, WHITE);
    // Back to main menu
}

#endif
