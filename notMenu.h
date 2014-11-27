#ifndef ArduinoTemplate_notMenu_h
#define ArduinoTemplate_notMenu_h

#include <Adafruit_GFX.h>

#include "notDisplay.h"

char * nameString = "BattlePong";

void drawMainMenu()
{
	tft.fillScreen(BLACK);
    // Print title
	tft.setCursor(32, 40);
	tft.setTextColor(RED);
	tft.print(nameString);
    // Match start
    tft.drawRect(44, 80, 40, 12, WHITE);
    tft.setCursor(50, 83);
    tft.setTextColor(WHITE);
    tft.print("Start");
    // Choose music
    tft.drawRect(44, 100, 40, 12, WHITE);
    // Draw music symbol so good
    tft.fillCircle(96, 100, 4, WHITE);
    tft.fillRect(96, 96, 2, 10, WHITE);
    tft.drawLine(95, 96, 98, 99, WHITE);
    tft.drawLine(96, 96, 99, 99, WHITE);
    tft.drawLine(97, 96, 100, 99, WHITE);
    tft.setCursor(50, 103);
    tft.print("Music");

}

void drawGameMenu()
{
    tft.fillScreen(BLACK);
    // Continue
    tft.drawRect(64, 80, 30, 10, WHITE);
    // Back to main menu
    tft.drawRect(64, 100, 30, 10, WHITE);
}

#endif
