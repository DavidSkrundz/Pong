
#ifndef ArduinoTemplate_notSerial_h
#define ArduinoTemplate_notSerial_h

#include <Arduino.h>

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
//		bowlings_write_to_serial3(balls[);
	} else {
		// Read the data
	}
}

#endif
