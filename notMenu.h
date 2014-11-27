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
    tft.drawRect(34, 80, 30, 12, WHITE);
    tft.setCursor(36, 80);
    tft.setTextColor(WHITE);
    tft.print("Start");
    // Choose music
    tft.drawRect(34, 100, 30, 12, WHITE);
    // Draw music symbol so good
    tft.fillCircle(100, 100, 4, WHITE);
    tft.fillRect(100, 90, 2, 10, WHITE);
    tft.drawLine(100, 90, 103, 93, WHITE);
    tft.drawLine(101, 90, 104, 93, WHITE);
    tft.drawLine(102, 90, 105, 93, WHITE);
    tft.setCursor(36, 100);
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
