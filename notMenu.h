#ifndef ArduinoTemplate_notMenu_h
#define ArduinoTemplate_notMenu_h

#include <Adafruit_GFX.h>

#include "notDisplay.h"
#include "notJoystick.h"
#include "notGame.h"

char * nameString = "BattlePong";
int selection = 0;
int oldSelection = 0;


int _selection()
{
	if (joystickGetVertical() < -10)
	{
		selection = 0;
	}
	else if(joystickGetVertical() > 10)
	{
		selection = 1;
	}
	return selection;
}

void drawMainMenu()
{
	_selection();
    // Print title
	tft.setCursor(32, 40);
	tft.setTextColor(RED);
	tft.print(nameString);

    // Draw music symbol so good
//    tft.fillCircle(101, 106, 4, WHITE);
//    tft.fillRect(101, 96, 2, 10, WHITE);
//    tft.drawLine(101, 96, 104, 99, WHITE);
//    tft.drawLine(102, 96, 105, 99, WHITE);
//    tft.drawLine(103, 96, 106, 99, WHITE);


    // Match start
//    if (!selection)
//    {
    	tft.fillRect(32, 80, 64, 13, WHITE);
    	tft.setCursor(50, 83);
    	tft.setTextColor(BLACK);
    	tft.print("Start");
    	// Unselected Music Button
		tft.fillRect(32, 100, 64, 13, BLACK);
    	tft.drawRect(32, 100, 64, 13, WHITE);
    	tft.setTextColor(WHITE);
    	tft.setCursor(50, 103);
    	tft.print("Music");
//    }
//    else
//    {
//        tft.fillRect(32, 80, 64, 13, BLACK);
//		tft.drawRect(32, 80, 64, 13, WHITE);
//		tft.setCursor(50, 83);
//		tft.setTextColor(WHITE);
//		tft.print("Start");
//		// Selected music button
//		tft.fillRect(32, 100, 64, 13, WHITE);
//		tft.setCursor(50, 103);
//		tft.setTextColor(BLACK);
//		tft.print("Music");
//    }
	if(joystickDidPress)
	{
		startGame();
	}
}

void drawGameMenu()
{
	_selection();
    tft.fillScreen(BLACK);
	tft.setCursor(32, 40);
	tft.setTextColor(RED);
	tft.print("Pause");

	if (!selection)
	{
		//Selected Return
		tft.fillRect(32, 80, 64, 13, WHITE);
		tft.setCursor(50, 83);
		tft.setTextColor(BLACK);
		tft.print("Return");
		//Deselected Main Menu
		tft.fillRect(32, 100, 64, 13, BLACK);
		tft.drawRect(32, 100, 64, 13, WHITE);
		tft.setCursor(50, 103);
		tft.setTextColor(WHITE);
		tft.print("Main menu");
	}
	else
	{
		//Deselected Return
		tft.fillRect(32, 80, 64, 13, BLACK);
		tft.drawRect(32, 80, 64, 13, WHITE);
		tft.setCursor(50, 83);
		tft.setTextColor(BLACK);
		tft.print("Return");
		// Selected Main Menu
		tft.fillRect(32, 100, 64, 13, WHITE);
		tft.setCursor(50, 103);
		tft.setTextColor(BLACK);
		tft.print("Main Menu");
	}

	if(!selection && joystickDidPress )
	{
		drawMainMenu();
		playingGame = false;
		preGame = true;
	}

	if(selection && joystickDidPress)
	{
		//Stop drawing the menu, return to game
	}
}

#endif
