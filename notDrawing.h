#ifndef notDrawing_h
#define notDrawing_h

#include <Arduino.h>

#include "notBall.h"
#include "notPaddle.h"
#include "notCollisions.h"
#include "notMath.h"
#include "notScore2.h"

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
	
	int oldX = plancksToScreen(SCREEN_WIDTH * PIXEL_LENGTH - paddles[1].oldX - paddles[1].oldWidth);
	int oldW = plancksToScreen(paddles[1].oldWidth);
	int width = plancksToScreen(paddles[1].width);
	int x = plancksToScreen(SCREEN_WIDTH * PIXEL_LENGTH - paddles[1].x - paddles[1].width);
	int y = -plancksToScreen(paddles[1].y);
	tft2.drawFastHLine(oldX - 1, y, oldW + 2, BLACK);
	tft2.drawFastHLine(oldX - 2, y + 1, oldW + 4, BLACK);
	tft2.drawFastHLine(oldX - 2, y + 2, oldW + 4, BLACK);
	tft2.drawFastHLine(oldX - 1, y + 3, oldW + 2, BLACK);
	
	tft2.drawFastHLine(x - 1, y, width + 2, WHITE);
	tft2.drawFastHLine(x - 2, y + 1, width + 4, WHITE);
	tft2.drawFastHLine(x - 2, y + 2, width + 4, WHITE);
	tft2.drawFastHLine(x - 1, y + 3, width + 2, WHITE);
}

void drawBlocks() {
	for (int i = 0; i < blocksCount; ++i) {
		if (!blocks[i].active) { continue ; }
		if (blocks[i].y > 0) {
			drawRectangle(blocks[i].x, blocks[i].y, blocks[i].width, blocks[i].height, WHITE);
		} else {
			drawRectangle2(SCREEN_WIDTH * PIXEL_LENGTH - blocks[i].x, -blocks[i].y, blocks[i].width, blocks[i].height, WHITE);
		}
	}
}

void drawScores() {
	tft.setCursor(0, 150);
	tft.setTextColor(BLACK);
	char str1[3];
	sprintf(str1, "%d", scores[0].oldScore);
	tft.print(str1);
	
	tft.setCursor(SCREEN_WIDTH - 12, 150);
	char str2[3];
	sprintf(str2, "%d", scores[1].oldScore);
	tft.print(str2);
	
	tft.setTextColor(WHITE);
	
	tft.setCursor(0, 150);
	char str3[3];
	sprintf(str3, "%d", scores[0].newScore);
	tft.print(str3);
	
	tft.setCursor(SCREEN_WIDTH - 12, 150);
	char str4[3];
	sprintf(str4, "%d", scores[1].newScore);
	tft.print(str4);
	
	
	
	tft2.setCursor(0, 150);
	tft2.setTextColor(BLACK);
	sprintf(str1, "%d", scores[0].oldScore);
	tft2.print(str1);
	
	tft2.setCursor(SCREEN_WIDTH - 12, 150);
	sprintf(str2, "%d", scores[1].oldScore);
	tft2.print(str2);
	
	tft2.setTextColor(WHITE);
	
	tft2.setCursor(0, 150);
	sprintf(str3, "%d", scores[0].newScore);
	tft2.print(str3);
	
	tft2.setCursor(SCREEN_WIDTH - 12, 150);
	sprintf(str4, "%d", scores[1].newScore);
	tft2.print(str4);
}

#pragma mark - Helpers

// Hardcoded radius circle drawing so we can have a good framerate
void drawCircle(long x, long y, long r, int color) {
	// Unit conversion
	x = plancksToScreen(x);
	y = plancksToScreen(y);
	r = plancksToScreen(r);
	
	int x2 = SCREEN_WIDTH - x;
	int y2 = -y;
	
	// Check for out of bounds so we don't draw
	//	if (x - r > SCREEN_WIDTH || y - r > SCREEN_HEIGHT || y + r < 0 || x + r < 0) { return; }
	
	switch (r) {
		case 2: {
			if (!(x - r > SCREEN_WIDTH || y - r > SCREEN_HEIGHT || y + r < 0 || x + r < 0)) {
				tft.drawFastVLine(x - 2, y - 1, 3, color);
				tft.drawFastVLine(x + 2, y - 1, 3, color);
				tft.drawFastHLine(x - 1, y + 2, 3, color);
				tft.drawFastHLine(x - 1, y - 2, 3, color);
			}
			
			if (!(x2 - r > SCREEN_WIDTH || y2 - r > SCREEN_HEIGHT || y2 + r < 0 || x2 + r < 0)) {
				tft2.drawFastVLine(x2 - 2, y2 - 1, 3, color);
				tft2.drawFastVLine(x2 + 2, y2 - 1, 3, color);
				tft2.drawFastHLine(x2 - 1, y2 + 2, 3, color);
				tft2.drawFastHLine(x2 - 1, y2 - 2, 3, color);
			}
			break;
		}
		case 3: {
			if (!(x - r > SCREEN_WIDTH || y - r > SCREEN_HEIGHT || y + r < 0 || x + r < 0)) {
				tft.drawFastVLine(x - 3, y - 1, 3, color);
				tft.drawFastVLine(x + 3, y - 1, 3, color);
				tft.drawFastHLine(x - 1, y + 3, 3, color);
				tft.drawFastHLine(x - 1, y - 3, 3, color);
				tft.drawPixel(x - 2, y + 2, color);
				tft.drawPixel(x - 2, y - 2, color);
				tft.drawPixel(x + 2, y + 2, color);
				tft.drawPixel(x + 2, y - 2, color);
			}
			
			if (!(x2 - r > SCREEN_WIDTH || y2 - r > SCREEN_HEIGHT || y2 + r < 0 || x2 + r < 0)) {
				tft2.drawFastVLine(x2 - 3, y2 - 1, 3, color);
				tft2.drawFastVLine(x2 + 3, y2 - 1, 3, color);
				tft2.drawFastHLine(x2 - 1, y2 + 3, 3, color);
				tft2.drawFastHLine(x2 - 1, y2 - 3, 3, color);
				tft2.drawPixel(x2 - 2, y2 + 2, color);
				tft2.drawPixel(x2 - 2, y2 - 2, color);
				tft2.drawPixel(x2 + 2, y2 + 2, color);
				tft2.drawPixel(x2 + 2, y2 - 2, color);
			}
			break;
		}
		case 7: {
			if (!(x - r > SCREEN_WIDTH || y - r > SCREEN_HEIGHT || y + r < 0 || x + r < 0)) {
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
				tft.drawPixel(x - 5, y + 5, color);
				tft.drawPixel(x + 5, y + 5, color);
				tft.drawPixel(x - 5, y - 5, color);
				tft.drawPixel(x + 5, y - 5, color);
			}
			
			if (!(x2 - r > SCREEN_WIDTH || y2 - r > SCREEN_HEIGHT || y2 + r < 0 || x2 + r < 0)) {
				tft2.drawFastVLine(x2 - 7, y2 - 2, 5, color);
				tft2.drawFastVLine(x2 + 7, y2 - 2, 5, color);
				tft2.drawFastHLine(x2 - 2, y2 + 7, 5, color);
				tft2.drawFastHLine(x2 - 2, y2 - 7, 5, color);
				tft2.drawFastVLine(x2 - 6, y2 - 4, 2, color);
				tft2.drawFastVLine(x2 - 6, y2 + 3, 2, color);
				tft2.drawFastVLine(x2 + 6, y2 - 4, 2, color);
				tft2.drawFastVLine(x2 + 6, y2 + 3, 2, color);
				tft2.drawFastHLine(x2 - 4, y2 + 6, 2, color);
				tft2.drawFastHLine(x2 - 4, y2 - 6, 2, color);
				tft2.drawFastHLine(x2 + 3, y2 + 6, 2, color);
				tft2.drawFastHLine(x2 + 3, y2 - 6, 2, color);
				tft2.drawPixel(x2 - 5, y2 + 5, color);
				tft2.drawPixel(x2 + 5, y2 + 5, color);
				tft2.drawPixel(x2 - 5, y2 - 5, color);
				tft2.drawPixel(x2 + 5, y2 - 5, color);
			}
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

void drawRectangle2(long x, long y, long w, long h, int c) {
	tft2.drawRect(plancksToScreen(x), plancksToScreen(y), plancksToScreen(w), plancksToScreen(h), c);
}

#endif
