
#ifndef ArduinoTemplate_notMenu_h
#define ArduinoTemplate_notMenu_h

#include <Adafruit_GFX.h>

#include "notDisplay.h"

char * nameString = "BattlePong";

// Draws a string as long as it exists on one line
void drawString(char * String, uint16_t x, uint16_t y, uint8_t size, uint16_t Color)
{
    for (int i = 0; i < sizeof(String)/sizeof(char); i++)
    {
        drawChar(x, y, String[i], Color, size)
        x+=size;
    }
}

void drawMainMenu()
{
    tft.fillscreen(BLACK);
    // Start match
    drawString(nameString, 32, 80, 10, BLUE);
    tft.drawRect(64, 40, 30, 10, WHITE);
    // Choose music

}

void drawGameMenu()
{
    tft.fillscreen(BLACK);
    // Continue
    tft.drawRect(64, 80, 30, 10, WHITE);
    // Back to main menu
}

#endif
