#ifndef ArduinoTemplate_notSerial_h
#define ArduinoTemplate_notSerial_h

#include <Arduino.h>

#include "notBall.h"
#include "notPaddle.h"

bool isHost = true;

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
		Serial3.write('B');
		Serial3.write('0');
		bowlings_write_to_serial3(balls[0].x);
		bowlings_write_to_serial3(balls[0].y);
		bowlings_write_to_serial3(balls[0].radius);
		
		// Read
		int typeChar = Serial3.read();
		if (typeChar == 'P') {
			int index = Serial3.read() - '0';
			paddles[index].oldX = paddles[index].x;
			paddles[index].oldWidth = paddles[index].width;
			paddles[index].x = bowlings_read_from_serial3();
		}
	} else {
		// Print
		Serial3.write('P');
		Serial3.write('1');
		bowlings_write_to_serial3(SCREEN_WIDTH * PIXEL_LENGTH - paddles[0].x);
		
		// Read
		int typeChar = Serial3.read();
		Serial.print(typeChar);
		if (typeChar == 'B') {
			int index = Serial3.read() - '0';
			balls[index].oldX = balls[index].x;
			balls[index].oldY = balls[index].y;
			balls[index].oldRadius = balls[index].radius;
			balls[index].x = SCREEN_WIDTH * PIXEL_LENGTH - bowlings_read_from_serial3();
			balls[index].y = -1 * bowlings_read_from_serial3();
			balls[index].radius = bowlings_read_from_serial3();
		}
	}
}

#endif
