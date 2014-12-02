#ifndef ArduinoTemplate_notScore2_h
#define ArduinoTemplate_notScore2_h

// Defines
#define SCORE_COUNT 2

typedef struct {
	int oldScore;
	int newScore;
} Score;

Score scores[SCORE_COUNT];

void initScores();

void localPlayerScored();
void otherPlayerScored();

#endif
