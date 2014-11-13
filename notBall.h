//
//  notBall.h
//  ArduinoTemplate
//
//  Created by David Skrundz on 2014-11-10.
//  Copyright (c) 2014 davidskrundz. All rights reserved.
//

#ifndef notBall_h
#define notBall_h

// Arduino Library
#include <Arduino.h>

// Assert
#include <assert.h>

// Math
#include "notCollisions.h"
#include "notMath.h"
#include "notGeometry.h"


// Defines
#define MAX_BALL_COUNT 3

// x, y, and speeds are in plancks
typedef struct {
	long x;
	long y;
	long radius;
	long xSpeed;
	long ySpeed;
} Ball;
Ball balls[MAX_BALL_COUNT];
int ballCount = 0;


// Create a new ball
void createBall(long x, long y, long radius, long xSpeed, long ySpeed) {
	assert(ballCount < MAX_BALL_COUNT);
	balls[ballCount].x = x;
	balls[ballCount].y = y;
	balls[ballCount].radius = radius;
	balls[ballCount].xSpeed = xSpeed;
	balls[ballCount].ySpeed = ySpeed;
	++ballCount;
}

void createBall(long x, long y, long radius) {
	createBall(x, y, radius, 0.0, 0.0);
}

// Remove ball
void removeBall(int index) {
	--ballCount;
	for (int i = index; i < ballCount - 1; ++i) {
		balls[i] = balls[i + 1];
	}
}

void removeBall(long x, long y) {
	for (int i = 0; i < ballCount - 1; ++i) {
		if (balls[i].x == x && balls[i].y == y) {
			removeBall(i);
		}
	}
}

void removeBall(long x, long y, long radius) {
	for (int i = 0; i < ballCount - 1; ++i) {
		if (balls[i].x == x && balls[i].y == y && balls[i].radius == radius) {
			removeBall(i);
		}
	}
}

void removeBalls() {
	ballCount = 0;
}

// Move
void moveBall(int index) {
	long xSpeed = balls[index].xSpeed;
	long ySpeed = balls[index].ySpeed;
	for (int i = 0; i < max(abs(xSpeed), abs(ySpeed)); ++i) {
		if (xSpeed > 0) {
			balls[index].x += 1;
			xSpeed -= 1;
		} else if (xSpeed < 0) {
			balls[index].x -= 1;
			xSpeed += 1;
		}
		if (ySpeed > 0) {
			balls[index].y += 1;
			ySpeed -= 1;
		} else if (ySpeed < 0) {
			balls[index].y -= 1;
			ySpeed += 1;
		}
		// Check for collisions
		int collisions = checkRectCollisionWithCircle(balls[index].x, balls[index].y, balls[index].radius);
		if (collisions & 1 << 0) {
			xSpeed = -xSpeed;
			balls[index].xSpeed = -balls[index].xSpeed;
		}
		if (collisions & 1 << 1) {
			ySpeed = -ySpeed;
			balls[index].ySpeed = -balls[index].ySpeed;
		}
	}
}

void moveBalls() {
	for (int i = 0; i < ballCount; i++) {
		moveBall(i);
	}
}

#endif
