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
#include "notScore2.h"
#include "notDrawing2.h"

// Defines
#define MAX_BALL_COUNT 3

// x, y, and speeds are in plancks
typedef struct {
	long x;
	long oldX;
	long y;
	long oldY;
	long radius;
	long oldRadius;
	long xSpeed;
	long ySpeed;
} Ball;
Ball balls[MAX_BALL_COUNT];
int ballCount = 0;


// Create a new ball
void createBall(long x, long y, long radius, long xSpeed, long ySpeed) {
	assert(ballCount < MAX_BALL_COUNT);
	balls[ballCount].x = x;
	balls[ballCount].oldX = x;
	balls[ballCount].y = y;
	balls[ballCount].oldY = y;
	balls[ballCount].radius = radius;
	balls[ballCount].oldRadius = radius;
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
	drawCircle(balls[index].oldX, balls[index].oldY, balls[index].oldRadius, BLACK);
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
	balls[index].oldX = balls[index].x;
	balls[index].oldY = balls[index].y;
	long totalIncrease = 0;
	long increaseAmount = 4 * PIXEL_LENGTH;
	int amount = 10;
	for (int i = 0; i < max(abs(xSpeed), abs(ySpeed)); i += amount) {
		if (xSpeed > 0) {
			balls[index].x += amount;
			xSpeed -= amount;
		} else if (xSpeed < 0) {
			balls[index].x -= amount;
			xSpeed += amount;
		}
		if (ySpeed > 0) {
			balls[index].y += amount;
			ySpeed -= amount;
		} else if (ySpeed < 0) {
			balls[index].y -= amount;
			ySpeed += amount;
		}
		// Check for collisions
		int collisions = checkRectCollisionWithCircle(balls[index].x, balls[index].y, balls[index].radius);
		if (collisions & 1 << 3) {
			otherPlayerScored();
			removeBall(index);
			return;
		}
		if (collisions & 1 << 2) {
			localPlayerScored();
			removeBall(index);
			return;
		}
		if (collisions & 1 << 0) {
			xSpeed = -xSpeed;
			balls[index].xSpeed = -balls[index].xSpeed;
		}
		if (collisions & 1 << 1) {
			ySpeed = -ySpeed;
			balls[index].ySpeed = -balls[index].ySpeed;
		}
		collisions = collisionBlockWithBall(balls[index].x, balls[index].y, balls[index].radius);
		if (collisions & 1 << 0) {
			xSpeed = -xSpeed;
			balls[index].xSpeed = -balls[index].xSpeed;
		}
		if (collisions & 1 << 1) {
			ySpeed = -ySpeed;
			balls[index].ySpeed = -balls[index].ySpeed;
		}
		// Circle Collisions
		long collisionAngle = checkCircleCollisionWithCircle(balls[index].x, balls[index].y, balls[index].radius);
		if (collisionAngle) {
			// Vertical bounce
			ySpeed = -ySpeed;
			balls[index].ySpeed = -balls[index].ySpeed;
			// Horizontal speed increase
			if (balls[index].y > 0) {
				if (balls[index].x < collisionRects[1].x) {
					if (totalIncrease < increaseAmount) {
						totalIncrease += increaseAmount;
						xSpeed -= increaseAmount;
						balls[index].xSpeed -= increaseAmount;
					}
				} else {
					if (totalIncrease < increaseAmount) {
						totalIncrease += increaseAmount;
						xSpeed += increaseAmount;
						balls[index].xSpeed += increaseAmount;
					}
				}
				balls[index].y -= 2 * PIXEL_LENGTH;
			} else {
				if (balls[index].x < collisionRects[2].x) {
					if (totalIncrease < increaseAmount) {
						totalIncrease += increaseAmount;
						xSpeed -= increaseAmount;
						balls[index].xSpeed -= increaseAmount;
					}
				} else {
					if (totalIncrease < increaseAmount) {
						totalIncrease += increaseAmount;
						xSpeed += increaseAmount;
						balls[index].xSpeed += increaseAmount;
					}
				}
				balls[index].y += 2 * PIXEL_LENGTH;
			}
		}
	}
}

void moveBalls() {
	for (int i = 0; i < ballCount; i++) {
		moveBall(i);
	}
}

#endif
