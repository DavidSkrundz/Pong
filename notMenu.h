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
    tft.drawRect(64, 80, 30, 10, WHITE);
    tft.setCursor(64, 80);
    tft.setTextColor(WHITE);
    tft.print("Start");
    // Choose music
    tft.drawRect(64, 100, 30, 10, WHITE);
    // Draw music symbol so good
    tft.fillCircle(100, 100, 7, WHITE);
    tft.fillRect(100, 100, 3, 10, WHITE);
    tft.drawLine(100, 110, 103, 107, WHITE);
    tft.drawLine(101, 110, 104, 107, WHITE);
    tft.drawLine(102, 110, 105, 107, WHITE);
    tft.setCursor(64, 100);
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
