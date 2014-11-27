#ifndef ArduinoTemplate_notSerial_h
#define ArduinoTemplate_notSerial_h

#include <Arduino.h>

#include "notBall.h"
#include "notPaddle.h"
#include "notScore2.h"

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

void serialStep() {
	if (isHost) {
		// Print the data
		bowlings_write_to_serial3(1L);
		bowlings_write_to_serial3(0L);
		bowlings_write_to_serial3(balls[0].x);
		bowlings_write_to_serial3(balls[0].y);
		bowlings_write_to_serial3(balls[0].radius);
		
		// Read
		while (Serial3.available()) {
			long code = bowlings_read_from_serial3();
			if (code == 2L) {
				paddles[1].oldX = paddles[1].x;
				movePaddle(1, bowlings_read_from_serial3() - paddles[1].x);
			}
		}
	} else {
		// Print
		bowlings_write_to_serial3(2L);
		bowlings_write_to_serial3(SCREEN_WIDTH * PIXEL_LENGTH - paddles[0].x - paddles[0].width);
		
		// Read
		while (Serial3.available()) {
			long code = bowlings_read_from_serial3();
			if (code == 1L) {
				long index = bowlings_read_from_serial3();
				balls[index].oldX = balls[index].x;
				balls[index].oldY = balls[index].y;
				balls[index].oldRadius = balls[index].radius;
				balls[index].x = SCREEN_WIDTH * PIXEL_LENGTH - bowlings_read_from_serial3();
				balls[index].y = -1 * bowlings_read_from_serial3();
				balls[index].radius = bowlings_read_from_serial3();
			}
			if (code == 3L) {
				scores[1].oldScore = scores[1].newScore;
				scores[1].newScore = bowlings_read_from_serial3();
				scores[0].oldScore = scores[0].newScore;
				scores[0].newScore = bowlings_read_from_serial3();
			}
//			if (typeChar == 'P') {
//				paddles[0].oldWidth = paddles[0].width;
//				paddles[0].width = bowlings_read_from_serial3();
//			}
		}
	}
}

#endif
