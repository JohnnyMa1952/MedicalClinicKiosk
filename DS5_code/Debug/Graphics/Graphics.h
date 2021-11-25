/*
 * Graphics.h
 *
 *  Created on: Feb 5, 2019
 *      Author: Amir
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define	BLACK			0
#define	WHITE			1
#define	RED			2
#define	LIME			3
#define	BLUE			4
#define	YELLOW			5
#define	CYAN			6
#define	MAGENTA			7

// #defined constants representing values we write to the graphics 'command' register to get
// it to draw something. You will add more values as you add hardware to the graphics chip
// Note DrawHLine, DrawVLine and DrawLine at the moment do nothing - you will modify these

#define DrawHLine		1
#define DrawVLine		2
#define DrawLine			3
#define	PutAPixel		0xA
#define	GetAPixel		0xB
#define	ProgramPaletteColour    0x10

#include "../Point/Point.h"

void WriteAPixel(Point p, int Colour);
int ReadAPixel(Point p);
void ProgramPalette(int PaletteNumber, int RGB);

/*********************************************************************************************
 * This function draw a horizontal line, 1 pixel at a time starting at the x,y coords specified
 * x1 < 800 and y1 < 480
*********************************************************************************************/
void HLine(Point p, int length, int Colour);


/*********************************************************************************************
 * This function draw a vertical line, 1 pixel at a time starting at the x,y coords specified
 * * x1 < 800 and y1 < 480
*********************************************************************************************/
void VLine(Point p, int length, int Colour);


/*******************************************************************************
** Hardware line drawing algorithm
**  x1 < 800 and y1 < 480
*******************************************************************************/
void Line(Point p1, Point p2, int Colour);

/*******************************************************************************
** Fill in the whole screen with specified colour
*******************************************************************************/
void Clear(int Colour);

/*******************************************************************************
** Filled rectangle with upper left point and lower right point with specified colour
*******************************************************************************/
void Filled_Rectangle(Point ul, Point lr, int Colour);

/*******************************************************************************
** Rectangle with upper left point and lower right point with specified colour and border that is "border bits wide"
*******************************************************************************/
void Bordered_Rectangle(Point ul, Point lr, int Colour, int border);

/*******************************************************************************
** Filled circle at center x1,y1 with radius "radius" and colour "colour"
*******************************************************************************/
void Filled_Circle(Point center, int radius, int Colour);

void Bresenham_Circle(Point center, int radius, int Colour);
void Bordered_Circle(Point center, int radius, int Colour, int border);


#endif /* GRAPHICS_H_ */
