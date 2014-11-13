//
//  notMath.h
//  ArduinoTemplate
//
//  Created by David Skrundz on 2014-11-11.
//  Copyright (c) 2014 davidskrundz. All rights reserved.
//

#ifndef ArduinoTemplate_notMath_h
#define ArduinoTemplate_notMath_h

#define PLANCK_LENGTH 1
#define PIXEL_LENGTH 100

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

int plancksToScreen(long plancks) {
	return (int)(plancks * PLANCK_LENGTH / PIXEL_LENGTH);
}

#endif
