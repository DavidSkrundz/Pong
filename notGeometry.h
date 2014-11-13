//
//  notGeometry.h
//  ArduinoTemplate
//
//  Created by David Skrundz on 2014-11-12.
//  Copyright (c) 2014 davidskrundz. All rights reserved.
//

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
