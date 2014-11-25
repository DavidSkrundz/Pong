
#ifndef ArduinoTemplate_notGeometry_h
#define ArduinoTemplate_notGeometry_h

#include "notMath.h"

// x, y, width, height are in plancks
typedef struct {
	long x;
	long y;
	long width;
	long height;
} Rect;

// x, y, and radius are in plancks
typedef struct {
	long x;
	long y;
	long radius;
} Circle;

#endif
