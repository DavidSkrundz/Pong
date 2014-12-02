#ifndef ArduinoTemplate_notCollisions_h
#define ArduinoTemplate_notCollisions_h

#include <assert.h>

#include "notGeometry.h"
#include "notDrawing2.h"

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



#define MAX_BLOCKS 12

Block blocks[MAX_BLOCKS];
int blocksCount = 0;

void addBlock(long x, long y, long width, long height) {
	assert(blocksCount < MAX_BLOCKS);
	blocks[blocksCount].x = x;
	blocks[blocksCount].y = y;
	blocks[blocksCount].width = width;
	blocks[blocksCount].height = height;
	blocks[blocksCount].active = 1;
	
	++blocksCount;
}

void removeBlock(int i) {
	if (blocks[i].y > 0) {
		drawRectangle(blocks[i].x, blocks[i].y, blocks[i].width, blocks[i].height, BLACK);
	} else {
		drawRectangle2(SCREEN_WIDTH * PIXEL_LENGTH - blocks[i].x, -blocks[i].y, blocks[i].width, blocks[i].height, BLACK);
	}
	blocks[i].active = 0;
}

void removeBlock(long x, long y) {
	for (int i = 0; i < blocksCount - 1; ++i) {
		if (blocks[i].x == x && blocks[i].y == y) {
			removeCollisionRect(i);
		}
	}
}

void removeBlocks() {
	blocksCount = 0;
}

/*
 0000) No Collision
 0001) Horizontal Collision
 0010) Vertical Collision
 0011) Vert + Horz Collisions
 */
// Kind of broken checking if the ball is outside of the rect
int collisionBlockWithBall(long x, long y, long r) {
	for (int i = 0; i < blocksCount; ++i) {
		Block currentBlock = blocks[i];
		// Left
		if (!currentBlock.active) continue;
		if (x + r > currentBlock.x && x < currentBlock.x && y > currentBlock.y && y < currentBlock.y + currentBlock.height) {
			removeBlock(i);
			return 1 << 0;
		}
		// Right
		if (x - r < currentBlock.x + currentBlock.width && x > currentBlock.x + currentBlock.width && y > currentBlock.y && y < currentBlock.y + currentBlock.height) {
			removeBlock(i);
			return 1 << 0;
		}
		// Top
		if (y + r > currentBlock.y && y < currentBlock.y && x > currentBlock.x && x < currentBlock.x + currentBlock.width) {
			removeBlock(i);
			return 1 << 1;
		}
		// Bottom
		if (y - r < currentBlock.y + currentBlock.height && y > currentBlock.y + currentBlock.height && x > currentBlock.x && x < currentBlock.x + currentBlock.width) {
			removeBlock(i);
			return 1 << 1;
		}
	}
	return 0;
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

void removeCollisionCircles() {
	collisionCirclesCount = 0;
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
