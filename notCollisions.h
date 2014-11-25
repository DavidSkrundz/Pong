#ifndef ArduinoTemplate_notCollisions_h
#define ArduinoTemplate_notCollisions_h

#include <assert.h>

#include "notGeometry.h"

/*
 0) Wall
 1) Local Player Paddle
 2) Other Player Paddle
 */
#define MAX_COLLISION_RECTS 3

Rect collisionRects[MAX_COLLISION_RECTS];
int collisionRectsCount = 0;

void addCollisionRect(long x, long y, long width, long height) {
	assert(collisionRectsCount < MAX_COLLISION_RECTS);
	collisionRects[collisionRectsCount].x = x;
	collisionRects[collisionRectsCount].y = y;
	collisionRects[collisionRectsCount].width = width;
	collisionRects[collisionRectsCount].height = height;
	++collisionRectsCount;
}

void removeCollisionRect(int index) {
	--collisionRectsCount;
	for (int i = index; i < collisionRectsCount - 1; ++i) {
		collisionRects[i] = collisionRects[i + 1];
	}
}

void removeCollisionRect(long x, long y) {
	for (int i = 0; i < collisionRectsCount - 1; ++i) {
		if (collisionRects[i].x == x && collisionRects[i].y == y) {
			removeCollisionRect(i);
		}
	}
}

void removeCollisionRects() {
	collisionRectsCount = 0;
}

#define MAX_COLLISION_CIRCLES 4

Circle collisionCircles[MAX_COLLISION_CIRCLES];
int collisionCirclesCount = 0;

void addCollisionCircle(long x, long y, long radius) {
	assert(collisionCirclesCount < MAX_COLLISION_CIRCLES);
	collisionCircles[collisionCirclesCount].x = x;
	collisionCircles[collisionCirclesCount].y = y;
	collisionCircles[collisionCirclesCount].radius = radius;
	++collisionCirclesCount;
}

void removeCollisionCircle(int index) {
	--collisionCirclesCount;
	for (int i = index; i < collisionCirclesCount; ++i) {
		collisionCircles[i] = collisionCircles[i + 1];
	}
}

void removeCollisionCircle(long x, long y) {
	for (int i = 0; i < collisionCirclesCount; ++i) {
		if (collisionCircles[i].x == x && collisionCircles[i].y == y) {
			removeCollisionCircle(i);
		}
	}
}

/*
 0000) No Collision
 0001) Horizontal Collision
 0010) Vertical Collision
 0011) Vert + Horz Collisions
 
 0100) Local Player Scored
 1000) Other Player Scored
 */
// Kind of broken checking if the ball is outside of the rect
int checkRectCollisionWithCircle(long x, long y, long r) {
	int collision = 0;
	for (int i = 0; i < collisionRectsCount; ++i) {
		Rect currentRect = collisionRects[i];
		// Left
		if (abs(currentRect.x - x) <= r && (y < currentRect.y + currentRect.height && y >= currentRect.y)) {
			collision |= 1 << 0;
		}
		// Right
		if (abs(currentRect.width + currentRect.x - x) <= r && (y < currentRect.y + currentRect.height && y >= currentRect.y)) {
			collision |= 1 << 0;
		}
		// Top
		if (abs(currentRect.y - y) <= r && (x < currentRect.x + currentRect.width && x >= currentRect.x)) {
			if (i == 0) {
				return 1 << 2;
			}
			collision |= 1 << 1;
		}
		// Bottom
		if (abs(currentRect.height + currentRect.y - y) <= r && (x < currentRect.x + currentRect.width && x >= currentRect.x)) {
			if (i == 0) {
				return 1 << 3;
			}
			collision |= 1 << 1;
		}
	}
	return collision;
}

long checkCircleCollisionWithCircle(long x, long y, long radius) {
	for (int i = 0; i < collisionCirclesCount; ++i) {
		Circle currentCircle = collisionCircles[i];
		if (sq(currentCircle.x - x) + sq(currentCircle.y - y) < sq(currentCircle.radius + radius)) {
			// Collision
			return 1;
		}
	}
	return 0;
}

#endif
