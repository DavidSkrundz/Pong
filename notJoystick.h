#ifndef ArduinoTemplate_notJoystick_h
#define ArduinoTemplate_notJoystick_h

#include <Arduino.h>

// Pins For The Joystick
#define JOYSTICK_VERT 0
#define JOYSTICK_HORZ 1
#define JOYSTICK_PRESS 9

#define JOYSTICK_VERT2 3
#define JOYSTICK_HORZ2 2
#define JOYSTICK_PRESS2 26

int joystickVerticalRest = -1;
int joystickHorizontalRest = -1;

int joystickVerticalRest2 = -1;
int joystickHorizontalRest2 = -1;

// Callable
bool joystickDidPress = false;
bool joystickPressed = false;
bool joystickDidRelease = false;

bool joystickDidPress2 = false;
bool joystickPressed2 = false;
bool joystickDidRelease2 = false;

int joystickGetVertical() {
	return (analogRead(JOYSTICK_VERT) - joystickVerticalRest);
}

int joystickGetHorizontal() {
	return (analogRead(JOYSTICK_HORZ) - joystickHorizontalRest);
}

int joystickGetVertical2() {
	return (analogRead(JOYSTICK_VERT2) - joystickVerticalRest2);
}

int joystickGetHorizontal2() {
	return (analogRead(JOYSTICK_HORZ2) - joystickHorizontalRest2);
}

// End Callable


void initJoystick() {
	// Initialize Joystick
	pinMode(JOYSTICK_PRESS, INPUT);
	digitalWrite(JOYSTICK_PRESS, HIGH);
	
	pinMode(JOYSTICK_PRESS2, INPUT);
	digitalWrite(JOYSTICK_PRESS2, HIGH);
	
	// Callibrate the joystick
	joystickVerticalRest = analogRead(JOYSTICK_VERT); // will be 0-1023
	joystickHorizontalRest = analogRead(JOYSTICK_HORZ); // will be 0-1023
	
	joystickVerticalRest2 = analogRead(JOYSTICK_VERT2); // will be 0-1023
	joystickHorizontalRest2 = analogRead(JOYSTICK_HORZ2); // will be 0-1023
}

void updateJoystick() {
	bool pressed = !digitalRead(JOYSTICK_PRESS); // LOW if pressed -> press == true when pressed
	if (pressed) {
		joystickDidRelease = false;
		if (!joystickPressed) {
			joystickPressed = true;
			joystickDidPress = true;
		} else {
			joystickDidPress = false;
		}
	} else {
		joystickDidPress = false;
		if (joystickPressed) {
			joystickPressed = false;
			joystickDidRelease = true;
		} else {
			joystickDidRelease = false;
		}
	}
	
	pressed = !digitalRead(JOYSTICK_PRESS2); // LOW if pressed -> press == true when pressed
	if (pressed) {
		joystickDidRelease2 = false;
		if (!joystickPressed2) {
			joystickPressed2 = true;
			joystickDidPress2 = true;
		} else {
			joystickDidPress2 = false;
		}
	} else {
		joystickDidPress2 = false;
		if (joystickPressed2) {
			joystickPressed2 = false;
			joystickDidRelease2 = true;
		} else {
			joystickDidRelease2 = false;
		}
	}
}

#endif
