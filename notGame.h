#ifndef ArduinoTemplate_notGame_h
#define ArduinoTemplate_notGame_h

#include "notScore.h"
#include "notMath.h"
#include "notPaddle.h"
#include "notSound.h"
#include "notBall.h"
#include "notDisplay.h"

#define WIN_SCORE 10

bool playingGame = false;
bool preGame = true;
bool postGame = false;

void initGame() {
	// Create the border for the whole game
	addCollisionRect(0 * PIXEL_LENGTH, -SCREEN_HEIGHT * PIXEL_LENGTH, SCREEN_WIDTH * PIXEL_LENGTH, 2 * SCREEN_HEIGHT * PIXEL_LENGTH);
	
	// Create the paddles for the two players
	createPaddle(SCREEN_HEIGHT - 15);
	createPaddle(5 - SCREEN_HEIGHT);
}

void startMatch() {
	createBall(20 * PIXEL_LENGTH, 20 * PIXEL_LENGTH, 7 * PIXEL_LENGTH,  0 * PIXEL_LENGTH, 6 * PIXEL_LENGTH);
}

void startGame() {
	tft.fillScreen(BLACK);
	playingGame = true;
	preGame = false;
	postGame = false;
	initScores();
	
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
	
	removeBalls();
	removeCollisionRects();
	removeCollisionCircles();
}

void gameCheck() {
	if (ballCount < 1) {
		startMatch();
	}
//	// Win check
//	if (scores[0].newScore >= WIN_SCORE) {
//		postGame = true;
//		playingGame = false;
//		// Local Player Wins
//		
//	}
//	if (scores[1].newScore >= WIN_SCORE) {
//		postGame = true;
//		playingGame = false;
//		// Other Player Wins
//		
//	}
}

#endif
