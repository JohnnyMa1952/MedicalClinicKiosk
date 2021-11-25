/*
 * Icon.h
 *
 *  Created on: Feb 23, 2019
 *      Author: Amir
 */
#include "../Point/Point.h"

#define ICONRES 	64
#define NUMCULS		8

#define BACKSPACE 	0
#define UPARROW		1
#define CAMERA		2
#define HEART		3
#define APPICON		4
#define BIOMED		5

Point drawIcon(Point p, int colour, int backgroundcolour, int Erase, int icon);

