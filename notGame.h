//
//  notGame.h
//  ArduinoTemplate
//
//  Created by David Skrundz on 2014-11-25.
//  Copyright (c) 2014 davidskrundz. All rights reserved.
//

#ifndef ArduinoTemplate_notGame_h
#define ArduinoTemplate_notGame_h

#include "notScore.h"
#include "notMath.h"
#include "notPaddle.h"
#include "notSound.h"
#include "notBall.h"

bool playingGame = false;

void initGame() {
	// Create the border for the whole game
	addCollisionRect(0 * PIXEL_LENGTH, -SCREEN_HEIGHT * PIXEL_LENGTH, SCREEN_WIDTH * PIXEL_LENGTH, 2 * SCREEN_HEIGHT * PIXEL_LENGTH);
	
	// Create the paddles for the two players
	createPaddle(SCREEN_HEIGHT - 15);
	addCollisionRect(5 * PIXEL_LENGTH, -(SCREEN_HEIGHT - 15) * PIXEL_LENGTH, 20 * PIXEL_LENGTH, 5 * PIXEL_LENGTH); // OTHER
}

void startMatch() {
	createBall(20 * PIXEL_LENGTH, 20 * PIXEL_LENGTH, 7 * PIXEL_LENGTH,  0 * PIXEL_LENGTH, 6 * PIXEL_LENGTH);
}

void startGame() {
	playingGame = true;
	initScores();
	playStartSound();
	
	startMatch();
}

void gameCheck() {
	if (ballCount < 1) {
		startMatch();
	}
}

#endif
