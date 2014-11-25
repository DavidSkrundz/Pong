
#ifndef ArduinoTemplate_notMath_h
#define ArduinoTemplate_notMath_h

#define PLANCK_LENGTH 1
#define PIXEL_LENGTH 100

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

int plancksToScreen(long plancks) {
	return (int)(plancks * PLANCK_LENGTH / PIXEL_LENGTH);
}

//http://www.codecodex.com/wiki/Calculate_an_integer_square_root
unsigned int sqrt32(unsigned long n) {
	unsigned int c = 0x8000;
	unsigned int g = 0x8000;
	for(;;) {
		if(g*g > n)
			g ^= c;
		c >>= 1;
		if(c == 0)
			return g;
		g |= c;
	}
}

long pointDistance(long x1, long y1, long x2, long y2) {
	return sqrt(sq(x1 - x2) + sq(y1 - y2));
}

long pointDirection(long x1, long y1, long x2, long y2) {
	return atan2(y2 - y1, x2 - x1);
}

#endif
