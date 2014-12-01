#ifndef ArduinoTemplate_notScore_h
#define ArduinoTemplate_notScore_h

#include "notSerial.h"
#include "notScore2.h"

void initScores() {
	scores[0].oldScore = 0;
	scores[0].newScore = 0;
	
	scores[1].oldScore = 0;
	scores[1].newScore = 0;
}

void localPlayerScored() {
	scores[0].oldScore = scores[0].newScore;
	scores[0].newScore += 1;
//	bowlings_write_to_serial3(3UL);
	writeInt(3);
	bowlings_write_to_serial3(scores[0].newScore);
	bowlings_write_to_serial3(scores[1].newScore);
}

void otherPlayerScored() {
	scores[1].oldScore = scores[1].newScore;
	scores[1].newScore += 1;
	writeInt(3);
//	bowlings_write_to_serial3(3UL);
	bowlings_write_to_serial3(scores[0].newScore);
	bowlings_write_to_serial3(scores[1].newScore);
}

#endif
