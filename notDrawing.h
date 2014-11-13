//
//  notDrawing.h
//  ArduinoTemplate
//
//  Created by David Skrundz on 2014-11-11.
//  Copyright (c) 2014 davidskrundz. All rights reserved.
//

#ifndef notDrawing_h
#define notDrawing_h

#include <Arduino.h>

#include "notBall.h"
#include "notCollisions.h"
#include "notMath.h"

void drawCircle(long x, long y, long r, int c);
void drawRectangle(long x, long y, long w, long h, int c);


void undrawCircles() {
	for (int i = 0; i < ballCount; ++i) {
		drawCircle(balls[i].x, balls[i].y, balls[i].radius, BLACK);
	}
}

void drawCircles() {
	for (int i = 0; i < ballCount; ++i) {
		drawCircle(balls[i].x, balls[i].y, balls[i].radius, WHITE);
	}
}


///* Not used
void undrawCollisionRects() {
	for (int i = 0; i < collisionRectsCount; ++i) {
		drawRectangle(collisionRects[i].x, collisionRects[i].y, collisionRects[i].width, collisionRects[i].height, BLACK);
	}
}
void drawCollisionRect() {
	for (int i = 0; i < collisionRectsCount; ++i) {
		drawRectangle(collisionRects[i].x, collisionRects[i].y, collisionRects[i].width, collisionRects[i].height, WHITE);
	}
}
//*/

#pragma mark - Helpers

void drawCircle(long x, long y, long r, int c) {
	tft.drawCircle(plancksToScreen(x), plancksToScreen(y), plancksToScreen(r), c);
}

void drawRectangle(long x, long y, long w, long h, int c) {
	tft.drawRect(plancksToScreen(x), plancksToScreen(y), plancksToScreen(w), plancksToScreen(h), c);
}

#endif
