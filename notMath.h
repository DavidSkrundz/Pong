#ifndef ArduinoTemplate_notMath_h
#define ArduinoTemplate_notMath_h

#define PLANCK_LENGTH 1
#define PIXEL_LENGTH 100

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

int plancksToScreen(long plancks) {
	return (int)(plancks * PLANCK_LENGTH / PIXEL_LENGTH);
}

long pointDistance(long x1, long y1, long x2, long y2) {
	return sqrt(sq(x1 - x2) + sq(y1 - y2));
}

long pointDirection(long x1, long y1, long x2, long y2) {
	return atan2(y2 - y1, x2 - x1);
}

#endif
