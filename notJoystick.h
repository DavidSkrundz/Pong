
#ifndef ArduinoTemplate_notJoystick_h
#define ArduinoTemplate_notJoystick_h

#include <Arduino.h>

// Pins For The Joystick
#define JOYSTICK_VERT 0
#define JOYSTICK_HORZ 1
#define JOYSTICK_PRESS 9

int joystickVerticalRest = -1;
int joystickHorizontalRest = -1;


// Callable
bool joystickDidPress = false;
bool joystickPressed = false;
bool joystickDidRelease = false;

int joystickGetVertical() {
	return (analogRead(JOYSTICK_VERT) - joystickVerticalRest);
}

int joystickGetHorizontal() {
	return (analogRead(JOYSTICK_HORZ) - joystickHorizontalRest);
}
// End Callable


void initJoystick() {
	// Initialize Joystick
	pinMode(JOYSTICK_PRESS, INPUT);
	digitalWrite(JOYSTICK_PRESS, HIGH);
	
	// Callibrate the joystick
	joystickVerticalRest = analogRead(JOYSTICK_VERT); // will be 0-1023
	joystickHorizontalRest = analogRead(JOYSTICK_HORZ); // will be 0-1023
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
}

#endif
