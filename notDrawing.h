
#ifndef notDrawing_h
#define notDrawing_h

#include <Arduino.h>

#include "notBall.h"
#include "notPaddle.h"
#include "notCollisions.h"
#include "notMath.h"

void drawCircle(long x, long y, long r, int c);
void drawRectangle(long x, long y, long w, long h, int c);

void drawCircles() {
	for (int i = 0; i < ballCount; ++i) {
		drawCircle(balls[i].oldX, balls[i].oldY, balls[i].oldRadius, BLACK);
	}
	for (int i = 0; i < ballCount; ++i) {
		drawCircle(balls[i].x, balls[i].y, balls[i].radius, WHITE);
	}
}

void drawPaddle() {
	tft.drawFastHLine(plancksToScreen(paddles[0].oldX) - 1, plancksToScreen(paddles[0].y), plancksToScreen(paddles[0].oldWidth) + 2, BLACK);
	tft.drawFastHLine(plancksToScreen(paddles[0].oldX) - 2, plancksToScreen(paddles[0].y) + 1, plancksToScreen(paddles[0].oldWidth) + 4, BLACK);
	tft.drawFastHLine(plancksToScreen(paddles[0].oldX) - 2, plancksToScreen(paddles[0].y) + 2, plancksToScreen(paddles[0].oldWidth) + 4, BLACK);
	tft.drawFastHLine(plancksToScreen(paddles[0].oldX) - 1, plancksToScreen(paddles[0].y) + 3, plancksToScreen(paddles[0].oldWidth) + 2, BLACK);
	
	tft.drawFastHLine(plancksToScreen(paddles[0].x) - 1, plancksToScreen(paddles[0].y), plancksToScreen(paddles[0].width) + 2, WHITE);
	tft.drawFastHLine(plancksToScreen(paddles[0].x) - 2, plancksToScreen(paddles[0].y) + 1, plancksToScreen(paddles[0].width) + 4, WHITE);
	tft.drawFastHLine(plancksToScreen(paddles[0].x) - 2, plancksToScreen(paddles[0].y) + 2, plancksToScreen(paddles[0].width) + 4, WHITE);
	tft.drawFastHLine(plancksToScreen(paddles[0].x) - 1, plancksToScreen(paddles[0].y) + 3, plancksToScreen(paddles[0].width) + 2, WHITE);
}

void drawScores() {
	tft.setCursor(0, 0);
	tft.setTextColor(BLACK);
	char str1[3];
	sprintf(str1, "%d", scores[0].oldScore);
	tft.print(str1);
	
	tft.setCursor(SCREEN_WIDTH - 12, 0);
	char str2[3];
	sprintf(str2, "%d", scores[1].oldScore);
	tft.print(str2);
	
	tft.setTextColor(WHITE);
	
	tft.setCursor(0, 0);
	char str3[3];
	sprintf(str3, "%d", scores[0].newScore);
	tft.print(str3);
	
	tft.setCursor(SCREEN_WIDTH - 12, 0);
	char str4[3];
	sprintf(str4, "%d", scores[1].newScore);
	tft.print(str4);
}

#pragma mark - Helpers

// Hardcoded radius circle drawing so we can have a good framerate
void drawCircle(long x, long y, long r, int color) {
	// Unit conversion
	x = plancksToScreen(x);
	y = plancksToScreen(y);
	r = plancksToScreen(r);
	
	// Check for out of bounds so we don't draw
	if (x - r > SCREEN_WIDTH || y - r > SCREEN_HEIGHT || y + r < 0 || x + r < 0) { return; }
	
	switch (r) {
		case 2: {
			tft.drawFastVLine(x - 2, y - 1, 3, color);
			tft.drawFastVLine(x + 2, y - 1, 3, color);
			tft.drawFastHLine(x - 1, y + 2, 3, color);
			tft.drawFastHLine(x - 1, y - 2, 3, color);
			break;
		}
		case 7: {
			tft.drawFastVLine(x - 7, y - 2, 5, color);
			tft.drawFastVLine(x + 7, y - 2, 5, color);
			tft.drawFastHLine(x - 2, y + 7, 5, color);
			tft.drawFastHLine(x - 2, y - 7, 5, color);
			tft.drawFastVLine(x - 6, y - 4, 2, color);
			tft.drawFastVLine(x - 6, y + 3, 2, color);
			tft.drawFastVLine(x + 6, y - 4, 2, color);
			tft.drawFastVLine(x + 6, y + 3, 2, color);
			tft.drawFastHLine(x - 4, y + 6, 2, color);
			tft.drawFastHLine(x - 4, y - 6, 2, color);
			tft.drawFastHLine(x + 3, y + 6, 2, color);
			tft.drawFastHLine(x + 3, y - 6, 2, color);
			tft.drawPixel(x - 5,y + 5, color);
			tft.drawPixel(x + 5, y + 5, color);
			tft.drawPixel(x - 5, y - 5, color);
			tft.drawPixel(x + 5, y - 5, color);
			break;
		}
		default: {
			
			break;
		}
	}
}

void drawRectangle(long x, long y, long w, long h, int c) {
	tft.drawRect(plancksToScreen(x), plancksToScreen(y), plancksToScreen(w), plancksToScreen(h), c);
}

#endif
