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
#include "notBall.h"
#include "notCollisions.h"
#include "notDrawing.h"

bool isHost = true;

void setup() {
	// Initialize Serial Port
	Serial.begin(9600);
	
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
	
	// Create the border for the whole game
	addCollisionRect(0 * PIXEL_LENGTH, -SCREEN_HEIGHT * PIXEL_LENGTH, SCREEN_WIDTH * PIXEL_LENGTH, 2 * SCREEN_HEIGHT * PIXEL_LENGTH);
	
	// Create the paddles for the two players
	addCollisionRect(5 * PIXEL_LENGTH, (SCREEN_HEIGHT - 15) * PIXEL_LENGTH, 20 * PIXEL_LENGTH, 5 * PIXEL_LENGTH);
	
	createBall(2000, 2000, 700,  0, 600);
}

// The Game Loop
long frameLength = 1000 / 20; // 1000 ms / 20 FPS
void loop() {
	long frameTime = millis() + frameLength;
	
	// Joystick Input
	updateJoystick();
	
	// Clear Screen
	undrawCircles();
	undrawCollisionRects();
	
	// Update
	moveBalls();
	if (joystickGetHorizontal() > 50) {
		collisionRects[1].x += 1 * PIXEL_LENGTH;
	}
	if (joystickGetHorizontal() < -50) {
		collisionRects[1].x -= 1 * PIXEL_LENGTH;
	}
	
	// Redraw Screen
	drawCircles();
	drawCollisionRect();
	
	// Pause For The Rest Of The Frame
	bool outOfTime = true;
	while (millis() < frameTime) {
		outOfTime = false;
	}
	if (outOfTime) {
		// We Ran Out Of Time For The Frame So We Need To Optimize Or Give More Time (Reduce FPS)
		Serial.println("Ran out of time for frame...");
	}
}