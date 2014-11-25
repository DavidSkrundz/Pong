//
//  notScore.h
//  ArduinoTemplate
//
//  Created by David Skrundz on 2014-11-25.
//  Copyright (c) 2014 davidskrundz. All rights reserved.
//

#ifndef ArduinoTemplate_notScore_h
#define ArduinoTemplate_notScore_h

// Defines
#define SCORE_COUNT 2

typedef struct {
	int oldScore;
	int newScore;
} Score;

Score scores[SCORE_COUNT];

void initScores() {
	scores[0].oldScore = 0;
	scores[0].newScore = 0;
	
	scores[1].oldScore = 0;
	scores[1].newScore = 0;
}

void localPlayerScored() {
	scores[0].oldScore = scores[0].newScore;
	scores[0].newScore += 1;
}

void otherPlayerScored() {
	scores[1].oldScore = scores[1].newScore;
	scores[1].newScore += 1;
}

#endif
