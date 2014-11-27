// Main Arduino Library
#include <Arduino.h>

// Core Graphics Library
//#include <Adafruit_GFX.h>

// U of A Image Drawing
//#include <lcd_image.h>

// SPI Stuff
//#include <SPI.h>

// SD Card Library
//#include <SD.h>

// Screen
#include "notDisplay.h"

// Joystick
#include "notJoystick.h"

// SD Card Hook
//Sd2Card card;

// "Objects"
#include "notSound.h"
#include "notScore.h"
#include "notSerial.h"
#include "notGame.h"
#include "notBall.h"
#include "notPaddle.h"
#include "notCollisions.h"
#include "notDrawing.h"
#include "notMenu.h"

void setup() {
	// Initialize Serial Port
	initSerial();
	
	// Screen
	initDisplay();
	
	// Joystick
	initJoystick();
	
	// Initialize SD Card
//	Serial.print("Initializing SD card...");
//	if (!SD.begin(SD_CS)) {
//		Serial.println("failed!");
//		while (1) {};  // Just wait, stuff exploded.
//	}
//	if (!card.init(SPI_HALF_SPEED, SD_CS)) {
//		Serial.println("Raw SD Initialization has failed");
//		while (1) {};  // Just wait, stuff exploded.
//	}
//	Serial.println(" OK!");
	
	initScores();
	initSound();
	initGame();
	
//	drawMainMenu();
}

// The Game Loop
long frameLength = 1000 / 20; // 1000 ms / 20 FPS
void loop() {
	long frameTime = millis() + frameLength;
	
	// Joystick Input
	updateJoystick();
	
	if (playingGame) {
		gameCheck();
		
		// Update
		if (joystickGetHorizontal() > 50) {
			movePaddle(0, map(joystickGetHorizontal(), 50, 512, 1, 5) * PIXEL_LENGTH);
		} else if (joystickGetHorizontal() < -50) {
			movePaddle(0, -map(abs(joystickGetHorizontal()), 50, 512, 1, 5) * PIXEL_LENGTH);
		}
		if (isHost) {
			moveBalls();
		}
		
		serialStep();
		
		// Redraw Screen
		drawCircles();
		drawPaddle();
		drawScores();
	} else {
//		playMenuSound(true);
		drawMainMenu();
	}
	
	long doneTime = millis();
	// Pause For The Rest Of The Frame
	bool outOfTime = true;
	while (millis() < frameTime) {
		outOfTime = false;
	}
	if (outOfTime) {
		// We Ran Out Of Time For The Frame So We Need To Optimize Or Give More Time (Reduce FPS)
		Serial.print("Ran out of time for frame...Missed by ");
		Serial.print(doneTime - frameTime);
		Serial.println("ms.");
	}
}