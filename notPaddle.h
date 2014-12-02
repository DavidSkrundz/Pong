#ifndef ArduinoTemplate_notPaddle_h
#define ArduinoTemplate_notPaddle_h

// Assert
#include <assert.h>

// Includes
#include "notCollisions.h"
#include "notMath.h"

// Defines
#define MAX_PADDLE_COUNT 2

typedef struct {
	int rectIndex;
	int leftCircleIndex;
	int rightCircleIndex;
	long x;
	long y;
	long oldX;
	long width;
	long oldWidth;
} Paddle;

Paddle paddles[MAX_PADDLE_COUNT];
int paddleCount = 0;

// Bottom: (SCREEN_HEIGHT - 15)
void createPaddle(long y) {
	assert(paddleCount < MAX_PADDLE_COUNT);
	paddles[paddleCount].rectIndex = collisionRectsCount;
	paddles[paddleCount].leftCircleIndex = collisionCirclesCount;
	paddles[paddleCount].rightCircleIndex = collisionCirclesCount + 1;
	paddles[paddleCount].y = y * PIXEL_LENGTH;
	paddles[paddleCount].x = ((SCREEN_WIDTH / 2) - 5) * PIXEL_LENGTH;
	paddles[paddleCount].oldX = paddles[paddleCount].x;
	paddles[paddleCount].width = 20 * PIXEL_LENGTH;
	paddles[paddleCount].oldWidth = paddles[paddleCount].width;
	addCollisionRect(paddles[paddleCount].x, paddles[paddleCount].y - 5 * PIXEL_LENGTH * (y < 0), paddles[paddleCount].width, 5 * PIXEL_LENGTH); // SELF
	addCollisionCircle(paddles[paddleCount].x, paddles[paddleCount].y + 2 * PIXEL_LENGTH - 5 * PIXEL_LENGTH * (y < 0), 2 * PIXEL_LENGTH);
	addCollisionCircle(paddles[paddleCount].x + paddles[paddleCount].width - 1 * PIXEL_LENGTH, paddles[paddleCount].y + 2 * PIXEL_LENGTH - 5 * PIXEL_LENGTH * (y < 0), 2 * PIXEL_LENGTH);
	++paddleCount;
}

void movePaddle(int index, long xAmount) {
	// Fix the amount so it can't go off screen
	if (paddles[index].x + xAmount < 2) {
		xAmount = 2 * PIXEL_LENGTH - paddles[index].x;
	} else if (paddles[index].x + xAmount > (SCREEN_WIDTH - 2) * PIXEL_LENGTH - paddles[index].width) {
		xAmount = (SCREEN_WIDTH - 2) * PIXEL_LENGTH - paddles[index].width - paddles[index].x;
	}
	paddles[index].oldX = paddles[index].x;
	paddles[index].x += xAmount;
	collisionRects[paddles[index].rectIndex].x += xAmount;
	collisionCircles[paddles[index].leftCircleIndex].x += xAmount;
	collisionCircles[paddles[index].rightCircleIndex].x += xAmount;
}

void removePaddles() {
	paddleCount = 0;
}

#endif
