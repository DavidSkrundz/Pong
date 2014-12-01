#ifndef ArduinoTemplate_notGame_h
#define ArduinoTemplate_notGame_h

#include "notScore.h"
#include "notMath.h"
#include "notPaddle.h"
#include "notSound.h"
#include "notBall.h"
#include "notDisplay.h"
#include "notStates.h"
#include "notSerial.h"

#define WIN_SCORE 10

void initGame() {
	// Create the border for the whole game
	addCollisionRect(0 * PIXEL_LENGTH, -SCREEN_HEIGHT * PIXEL_LENGTH, SCREEN_WIDTH * PIXEL_LENGTH, 2 * SCREEN_HEIGHT * PIXEL_LENGTH);
	
	// Create the paddles for the two players
	createPaddle(SCREEN_HEIGHT - 15);
	if (isHost) {
		createPaddle(10 - SCREEN_HEIGHT);
	}
}

void startMatch() {
	long code = -1;
	if (isHost) {
//		Serial3.write(11);
//		while (code != 10) {
//			if (Serial3.available()) {
//				code = Serial3.read();
//			}
//		}
		createBall(20 * PIXEL_LENGTH, 20 * PIXEL_LENGTH, 3 * PIXEL_LENGTH,  0 * PIXEL_LENGTH, 6 * PIXEL_LENGTH);
	} else {
//		while (code != 11) {
//			if (Serial3.available()) {
//				code = Serial3.read();
//			}
//		}
		Serial3.write(10);
		createBall(-20 * PIXEL_LENGTH, -20 * PIXEL_LENGTH, 3 * PIXEL_LENGTH,  0 * PIXEL_LENGTH, 6 * PIXEL_LENGTH);
	}
}

void startGame() {
	tft.fillScreen(BLACK);
	playingGame = true;
	preGame = false;
	postGame = false;
	initScores();
	initGame();
	
	startMatch();
}

void pauseGame() {
	tft.fillScreen(BLACK);
	playingGame = false;
	preGame = false;
	postGame = true;
}

void resumeGame() {
	tft.fillScreen(BLACK);
	playingGame = true;
	preGame = false;
	postGame = false;
}

void endGame() {
	tft.fillScreen(BLACK);
	playingGame = false;
	preGame = true;
	postGame = false;
	
	resetSounds();
	
	removePaddles();
	removeBalls();
	removeCollisionRects();
	removeCollisionCircles();
}

void gameCheck() {
	if (ballCount < 1) {
		startMatch();
	}
	// Win check
	if (scores[0].newScore >= WIN_SCORE) {
		postGame = true;
		playingGame = false;
		// Local Player Wins
		win = true;
		bowlings_write_to_serial3(5UL);
	}
	if (scores[1].newScore >= WIN_SCORE) {
		postGame = true;
		playingGame = false;
		// Other Player Wins
		lose = true;
		bowlings_write_to_serial3(6UL);
	}
}

#endif
