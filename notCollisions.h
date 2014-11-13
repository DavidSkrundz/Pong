//
//  notCollisions.h
//  ArduinoTemplate
//
//  Created by David Skrundz on 2014-11-11.
//  Copyright (c) 2014 davidskrundz. All rights reserved.
//

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

/** Not Implemented For Not
#define MAX_COLLISION_CIRCLES 0

Circle collisionCircles[MAX_COLLISION_CIRCLES];
int collisionCirclesCount = 0;
*/

/*
 0000) No Collision
 0001) Horizontal Collision
 0010) Vertical Collision
 0011) Vert + Horz Collisions
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
			collision |= 1 << 1;
		}
		// Bottom
		if (abs(currentRect.height + currentRect.y - y) <= r && (x < currentRect.x + currentRect.width && x >= currentRect.x)) {
			collision |= 1 << 1;
		}
	}
	return collision;
}

#endif
