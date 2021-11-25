/*
 * GraphicsTest.c
 *
 *  Created on: Jan 27, 2019
 *      Author: Amir
 */

#include <stdio.h>
#include "Fonts.h"
#include "Graphics.h"
#include "../Linux/VirtualAddresses.h"

/************************************************************************************************
** This macro pauses until the graphics chip status register indicates that it is idle
***********************************************************************************************/

#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

// defined constants representing colours pre-programmed into colour palette
// there are 256 colours but only 8 are shown below, we write these to the colour registers
//
// the header files "Colours.h" contains constants for all 256 colours
// while the course file "ColourPaletteData.c" contains the 24 bit RGB data
// that is pre-programmed into the palette


/*******************************************************************************************
* This function writes a single pixel to the x,y coords specified using the specified colour
* Note colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
********************************************************************************************/
void WriteAPixel(Point p, int Colour)
{
	WAIT_FOR_GRAPHICS;				// is graphics ready for new command

	GraphicsX1Reg = p.x;				// write coords to x1, y1
	GraphicsY1Reg = p.y;
	GraphicsColourReg = Colour;			// set pixel colour
	GraphicsCommandReg = PutAPixel;			// give graphics "write pixel" command
}

/*********************************************************************************************
* This function read a single pixel from the x,y coords specified and returns its colour
* Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
*********************************************************************************************/

int ReadAPixel(Point p)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = p.x;			// write coords to x1, y1
	GraphicsY1Reg = p.y;
	GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS;			// is graphics done reading pixel
	return (int)(GraphicsColourReg) ;	// return the palette number (colour)
}


/**********************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
**
************************************************************************************/

void ProgramPalette(int PaletteNumber, int RGB)
{
    WAIT_FOR_GRAPHICS;
    GraphicsColourReg = PaletteNumber;
    GraphicsX1Reg = RGB >> 16   ;        // program red value in ls.8 bit of X1 reg
    GraphicsY1Reg = RGB ;                // program green and blue into ls 16 bit of Y1 reg
    GraphicsCommandReg = ProgramPaletteColour; // issue command
}

/*********************************************************************************************
 * This function draw a horizontal line, 1 pixel at a time starting at the x,y coords specified
 * x1 < 800 and y1 < 480
*********************************************************************************************/
void HLine(Point p, int length, int Colour)
{
	if(length == 0)
		return;
	else if(length == 1)
		WriteAPixel(p, Colour);
	else{
		int x2 = p.x + length - 1;
		if(x2 < p.x){
			int temp = p.x;
			p.x = x2;
			x2 = temp;
		}
		WAIT_FOR_GRAPHICS;				// is graphics ready for new command
		GraphicsX1Reg = p.x;
		GraphicsY1Reg = p.y;
		GraphicsX2Reg = x2;
		GraphicsY2Reg = p.y;
		GraphicsColourReg = Colour;
		GraphicsCommandReg = DrawHLine;
	}
}

/*********************************************************************************************
 * This function draw a vertical line, 1 pixel at a time starting at the x,y coords specified
 * * x1 < 800 and y1 < 480
*********************************************************************************************/
void VLine(Point p, int length, int Colour)
{
	if(length == 0)
		return;
	if(length == 1)
		WriteAPixel(p, Colour);
	else{
		int y2 = p.y + length - 1;
		if(y2 < p.y){
			int temp = p.y;
			p.y = y2;
			y2 = temp;
		}
		WAIT_FOR_GRAPHICS;				// is graphics ready for new command
		GraphicsX1Reg = p.x;
		GraphicsY1Reg = p.y;
		GraphicsX2Reg = p.x;
		GraphicsY2Reg = y2;
		GraphicsColourReg = Colour;
		GraphicsCommandReg = DrawVLine;
	}
}

/*******************************************************************************
** Hardware line drawing algorithm
**  x1 < 800 and y1 < 480
*******************************************************************************/
void Line(Point p1, Point p2, int Colour)
{
	WAIT_FOR_GRAPHICS;				// is graphics ready for new command
	GraphicsX1Reg = p1.x;
	GraphicsY1Reg = p1.y;
	GraphicsX2Reg = p2.x;
	GraphicsY2Reg = p2.y;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawLine;
}

/*******************************************************************************
** Fill in the whole screen with specified colour
*******************************************************************************/
void Clear(int Colour)
{
	Point p;
	p.x = 0;

	for(p.y=0; p.y<480; p.y++)
		HLine(p, 800, Colour);
}

/*******************************************************************************
** Filled rectangle with upper right point and lower left point with specified colour
*******************************************************************************/
void Filled_Rectangle(Point ul, Point lr, int Colour)
{
	int length = lr.x - ul.x;
	for(; ul.y <= lr.y; ul.y++)
		HLine(ul, length, Colour);
}

/*******************************************************************************
** Rectangle with upper right point and lower left point with specified colour and border that is "border bits wide"
*******************************************************************************/
void Bordered_Rectangle(Point ul, Point lr, int Colour, int border)
{
	if(border == 0)
		return;

	int width = lr.x - ul.x;
	int height = lr.y - ul.y;
	Point p;
	for(int i=0; i<=border; i++){
		p.x = ul.x;
		p.y = ul.y + i;
		HLine(p, width, Colour);
		p.x = ul.x + i;
		p.y = ul.y;
		VLine(p, height, Colour);
		p.x = ul.x;
		p.y = lr.y - i;
		HLine(p, width, Colour);
		p.x = lr.x - i;
		p.y = ul.y;
		VLine(p, height, Colour);
	}
}

/*******************************************************************************
** Filled circle at center x1,y1 with radius "radius" and colour "colour"
*******************************************************************************/
void Filled_Circle(Point center, int radius, int Colour)
{
	Point p;
	for(int x = (center.x - radius); x <= (center.x + radius); x++){
		for(int y = (center.y - radius); y <= (center.y + radius); y++){
			if((((y-center.y)*(y-center.y)) + ((x-center.x)*(x-center.x))) <= (radius*radius)){
				p.x = x;
				p.y = y;
				WriteAPixel(p, Colour);
			}
		}
	}
}

void Bresenham_Circle(Point center, int radius, int Colour){
    int offset_y = 0;
    int offset_x = radius;
    int crit = 1 - radius;
    while (offset_y <= offset_x) {
    	WriteAPixel((Point){center.x + offset_x, center.y + offset_y}, Colour);     // octant 1
    	WriteAPixel((Point){center.x + offset_y, center.y + offset_x}, Colour);     // octant 2
    	WriteAPixel((Point){center.x - offset_x, center.y + offset_y}, Colour);     // octant 4
    	WriteAPixel((Point){center.x - offset_y, center.y + offset_x}, Colour);     // octant 3
    	WriteAPixel((Point){center.x - offset_x, center.y - offset_y}, Colour);     // octant 5
    	WriteAPixel((Point){center.x - offset_y, center.y - offset_x}, Colour);     // octant 6
    	WriteAPixel((Point){center.x + offset_x, center.y - offset_y}, Colour);     // octant 7
    	WriteAPixel((Point){center.x + offset_y, center.y - offset_x}, Colour);     // octant 8
        offset_y++;
        if (crit <= 0)
            crit = crit + (2 * offset_y) + 1;
        else{
            offset_x = offset_x - 1;
            crit = crit + (2 * (offset_y - offset_x)) + 1;
        }
    }
}

void Bordered_Circle(Point center, int radius, int Colour, int border){
	for(int i=0; i<border; i++)
		Bresenham_Circle(center, radius - i, Colour);
}

