#ifndef ArduinoTemplate_notSerial_h
#define ArduinoTemplate_notSerial_h

#include <Arduino.h>

#include "notBall.h"
#include "notPaddle.h"
#include "notScore2.h"
#include "notStates.h"

bool isHost = false;

void initSerial() {
	// Open
	Serial.begin(9600);
	Serial3.begin(9600);
	
	// Flush
	while (Serial3.available()) {
		Serial3.read();
	}
}

void bowlings_write_to_serial3(unsigned long num) {
	Serial3.write((char) (num >> 0));
	Serial3.write((char) (num >> 8));
	Serial3.write((char) (num >> 16));
	Serial3.write((char) (num >> 24));
}

unsigned long bowlings_read_from_serial3() {
	unsigned long num = 0;
	num = num | ((uint32_t) Serial3.read()) >> 0;
	num = num | ((uint32_t) Serial3.read()) << 8;
	num = num | ((uint32_t) Serial3.read()) << 16;
	num = num | ((uint32_t) Serial3.read()) << 24;
	return num;
}

void waitForByteCount(int count) {
	while (Serial3.available() < count) {}
}

int available() {
	return Serial3.available();
}

void serialStep() {
	if (isHost) {
		// Print the data
		if (balls[0].y < 50 * PIXEL_LENGTH) {
			bowlings_write_to_serial3(1UL);
			bowlings_write_to_serial3(0UL);
			bowlings_write_to_serial3(balls[0].x);
			bowlings_write_to_serial3(balls[0].y);
			bowlings_write_to_serial3(balls[0].radius);
		}
		
		// Read
		while (available() >= 4) {
			long code = bowlings_read_from_serial3();
			if (code == 2UL) {
				waitForByteCount(4);
				long location = bowlings_read_from_serial3();
				movePaddle(1, location - paddles[1].x);
			}
		}
	} else {
		// Print
		bowlings_write_to_serial3(2UL);
		bowlings_write_to_serial3(SCREEN_WIDTH * PIXEL_LENGTH - paddles[0].x - paddles[0].width);
		
		// Read
		balls[0].oldX = balls[0].x;
		balls[0].oldY = balls[0].y;
		scores[1].oldScore = scores[1].newScore;
		scores[0].oldScore = scores[0].newScore;
		while (available() >= 4) {
			long code = bowlings_read_from_serial3();
			if (code == 1UL) {
				waitForByteCount(4);
				long index = bowlings_read_from_serial3();
				balls[index].oldRadius = balls[index].radius;
				waitForByteCount(4);
				balls[index].x = SCREEN_WIDTH * PIXEL_LENGTH - bowlings_read_from_serial3();
				waitForByteCount(4);
				balls[index].y = -1 * bowlings_read_from_serial3();
				waitForByteCount(4);
				balls[index].radius = bowlings_read_from_serial3();
			} else if (code == 3UL) {
				waitForByteCount(4);
				scores[1].newScore = bowlings_read_from_serial3();
				waitForByteCount(4);
				scores[0].newScore = bowlings_read_from_serial3();
			} else if (code == 5UL) {
				lose = true;
			} else if (code == 6UL) {
				win = true;
			}
		}
	}
}

#endif
