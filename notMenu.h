#ifndef ArduinoTemplate_notMenu_h
#define ArduinoTemplate_notMenu_h

#include <Adafruit_GFX.h>

#include "notDisplay.h"
#include "notJoystick.h"
#include "notGame.h"

char * nameString = "BattlePong";
int selection = 0;
int oldSelection = 2;


int _selection() {
	if (joystickGetVertical() < -10) {
		selection = 0;
	}
	else if(joystickGetVertical() > 10) {
		selection = 1;
	}
	return selection;
}

void drawMainMenu() {
	_selection();
    // Print title
	tft.setCursor(32, 40);
	tft.setTextColor(RED);
	tft.print(nameString);

	// Match start
	if (selection != oldSelection) {
		oldSelection = selection;
		if (!selection) {
			tft.fillRect(32, 80, 64, 13, WHITE);
			tft.setCursor(50, 83);
			tft.setTextColor(BLACK);
			tft.print("Start");
			// Unselected Music Button
			tft.fillRect(32, 100, 64, 13, BLACK);
			tft.drawRect(32, 100, 64, 13, WHITE);
			tft.setCursor(53, 103);
			tft.setTextColor(WHITE);
			tft.print("Host");
		} else {
			//Deselected Return
			tft.fillRect(32, 80, 64, 13, BLACK);
			tft.drawRect(32, 80, 64, 13, WHITE);
			tft.setCursor(50, 83);
			tft.setTextColor(WHITE);
			tft.print("Start");
			// Selected Main Menu
			tft.fillRect(32, 100, 64, 13, WHITE);
			tft.setCursor(53, 103);
			tft.setTextColor(BLACK);
			tft.print("Host");
		}
	}
	if (joystickDidPress) {
		joystickDidPress = false;
		if (selection) {
			isHost = true;
		} else {
			isHost = false;
		}
		startGame();
		selection = 0;
		oldSelection = 2;
	}
}

void drawGameMenu() {
	_selection();
	tft.setCursor(50, 40);
	tft.setTextColor(RED);
	tft.print("Pause");

	if (selection != oldSelection) {
		oldSelection = selection;
		if (!selection) {
			//Selected Return
			tft.fillRect(32, 80, 64, 13, WHITE);
			tft.setCursor(47, 83);
			tft.setTextColor(BLACK);
			tft.print("Return");
			//Deselected Main Menu
			tft.fillRect(32, 100, 64, 13, BLACK);
			tft.drawRect(32, 100, 64, 13, WHITE);
			tft.setCursor(38, 103);
			tft.setTextColor(WHITE);
			tft.print("Main menu");
		} else {
			//Deselected Return
			tft.fillRect(32, 80, 64, 13, BLACK);
			tft.drawRect(32, 80, 64, 13, WHITE);
			tft.setCursor(47, 83);
			tft.setTextColor(WHITE);
			tft.print("Return");
			// Selected Main Menu
			tft.fillRect(32, 100, 64, 13, WHITE);
			tft.setCursor(38, 103);
			tft.setTextColor(BLACK);
			tft.print("Main Menu");
		}
	}

	if (joystickDidPress) {
		joystickDidPress = false;
		if (selection) {
			endGame();
		} else {
			resumeGame();
		}
		selection = 0;
		oldSelection = 2;
	}
}

void drawWinState() {
	tft.setCursor(42, 40);
	tft.setTextColor(RED);
	tft.print("You Win!");
	if (selection != oldSelection) {
		oldSelection = selection;
		tft.fillScreen(BLACK);
		// Selected Main Menu
		tft.fillRect(32, 100, 64, 13, WHITE);
		tft.setCursor(38, 103);
		tft.setTextColor(BLACK);
		tft.print("Main Menu");
	}
	if (joystickDidPress) {
		joystickDidPress = false;
		endGame();
		selection = 0;
		oldSelection = 2;
	}
}

void drawLoseState() {
	tft.setCursor(42, 40);
	tft.setTextColor(RED);
	tft.print("You Lose");
	if (selection != oldSelection) {
		oldSelection = selection;
		tft.fillScreen(BLACK);
		// Selected Main Menu
		tft.fillRect(32, 100, 64, 13, WHITE);
		tft.setCursor(38, 103);
		tft.setTextColor(BLACK);
		tft.print("Main Menu");
	}
	if (joystickDidPress) {
		joystickDidPress = false;
		endGame();
		selection = 0;
		oldSelection = 2;
	}
}

#endif
