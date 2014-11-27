
#ifndef ArduinoTemplate_notSound_h
#define ArduinoTemplate_notSound_h

#include "Tone.h"

#include "notSongs.h"

#define SOUND_PIN_1 13
#define SOUND_PIN_2 12

#define mspm 60000

Tone tone1;
int tone1BPM = 0;
int tone1mspb = 0;
int tone1CurrentIndex = 0;
int tone1CurrentTime = 0;
int tone1NextTime = 0;

Tone tone2;
int tone2BPM = 0;
int tone2mspb = 0;
int tone2CurrentIndex = 0;
int tone2CurrentTime = 0;
int tone2NextTime = 0;

void resetSounds() {
	tone1mspb = 0;
}

void initSound() {
	tone1.begin(SOUND_PIN_1);
	tone2.begin(SOUND_PIN_2);
	
	resetSounds();
}

#define defineSound(funcName, soundName) \
bool play ##funcName ## Sound(bool loop) { \
	if (tone1mspb == 0) { \
		tone1BPM = 120; \
		tone1mspb = mspm / tone1BPM; \
		tone1CurrentIndex = -1; \
		tone1NextTime = millis(); \
		 \
		tone2BPM = tone1BPM; \
		tone2mspb = mspm / tone1BPM; \
		tone2CurrentIndex = -1; \
		tone2NextTime = millis(); \
	} \
	tone1CurrentTime = millis(); \
	if (tone1CurrentTime >= tone1NextTime) { \
		++tone1CurrentIndex; \
		if (tone1CurrentIndex >= soundName ## Amount1) { \
			if (loop) { \
				tone1CurrentIndex -= soundName ## Amount1; \
			} else { \
				resetSounds(); \
				return true; \
			} \
		} \
		tone1NextTime = millis() + tone1mspb * soundName ## Tempo1[tone1CurrentIndex] / TIME_QUARTER; \
		tone1.play(soundName ## Melody1[tone1CurrentIndex], soundName ## Tempo1[tone1CurrentIndex] * tone1mspb); \
	} \
	tone2CurrentTime = millis(); \
	if (tone2CurrentTime >= tone2NextTime) { \
		++tone2CurrentIndex; \
		if (tone2CurrentIndex >= soundName ## Amount2) { \
			if (loop) { \
				tone2CurrentIndex -= soundName ## Amount2; \
			} else { \
				resetSounds(); \
				return true; \
			} \
		} \
		tone2NextTime = millis() + tone2mspb * soundName ## Tempo2[tone2CurrentIndex] / TIME_QUARTER; \
		tone2.play(soundName ## Melody2[tone2CurrentIndex], soundName ## Tempo2[tone2CurrentIndex] * tone2mspb); \
	} \
	return false; \
} \


bool playMenuSound(bool loop);
defineSound(Menu, tetris)

bool playGameStartSound(bool loop);
defineSound(GameStart, pacmanIntro)

#endif
