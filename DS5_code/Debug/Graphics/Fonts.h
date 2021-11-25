/*
 * Fonts.h
 *
 *  Created on: Jan 31, 2019
 *      Author: Amir
 */

#ifndef FONTS_H_
#define FONTS_H_

#include "../Point/Point.h"

// write given chat array "s" starting at point p with the color "colour" and
// (optionally background color "backgroundcolour" if Erase is true)
// with the specified font "font" 1-5 and optionally scale the characters by "scale"
// USE BIGGER FONTS INSTEAD OF SCALE - MAKES STUFF LOOK BETTER
Point OutGraphicsString(Point p, int colour, int backgroundcolour, char* s, int Erase, int font, int scale);

void OutGraphicsCharFont1(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale);
void OutGraphicsCharFont2(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale);
void OutGraphicsCharFont3(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale);
void OutGraphicsCharFont4(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale);
void OutGraphicsCharFont5(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale);

Point OutGraphicsStringFont1(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale);
Point OutGraphicsStringFont2(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale);
Point OutGraphicsStringFont3(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale);
Point OutGraphicsStringFont4(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale);
Point OutGraphicsStringFont5(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale);

#endif /* FONTS_H_ */
