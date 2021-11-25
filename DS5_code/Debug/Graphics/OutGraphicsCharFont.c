/*
 * OutGraphicsCharFont.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Amir
 */

#include "Fonts.h"
#include "Graphics.h"
#include "../Point/Point.h"

#define XRES 800
#define YRES 480

#define FONT1_XPIXELS	5				// width of Font1 characters in pixels (no spacing)
#define FONT1_YPIXELS	7				// height of Font1 characters in pixels (no spacing)

#define FONT2_XPIXELS	10				// width of Font2 characters in pixels (no spacing)
#define FONT2_YPIXELS	14				// height of Font2 characters in pixels (no spacing)

#define FONT3_XPIXELS	16				// width of Font3 characters in pixels (no spacing)
#define FONT3_YPIXELS	27				// height of Font3 characters in pixels (no spacing)

#define FONT4_XPIXELS	22				// width of Font4 characters in pixels (no spacing)
#define FONT4_YPIXELS	40				// height of Font4 characters in pixels (no spacing)

#define FONT5_XPIXELS	32				// width of Font5 characters in pixels (no spacing)
#define FONT5_YPIXELS	59				// height of Font5 characters in pixels (no spacing)


extern const unsigned char Font5x7[95][7];
extern const unsigned short int Font10x14[][14];
extern const unsigned char Font16x27[];
extern const unsigned char Font22x40[];
extern const unsigned char Font32x59[];

void OutGraphicsCharFont1(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int j, row, column, theX = x, theY = y ;
	register int pixels ;
	register char theColour = colour  ;
	register int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother

    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
        return ;


// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		for(j = 1, row = 0; j <= FONT1_YPIXELS*scale; j++)
		{
			// get the bit pattern for row 0 of the character from the software font
			pixels = Font5x7[theC][row] ;
			row = ((j % scale) == 0) ? row + 1 : row;
			BitMask = 16 ;

			for(column = 1; column <= FONT1_XPIXELS*scale; column++)
			{
				// if a pixel in the character display it
				if((pixels & BitMask))
					WriteAPixel((Point){theX+column, theY+j}, theColour) ;
				else if(Erase == 1)
					WriteAPixel((Point){theX+column, theY+j}, backgroundcolour);

				BitMask = (column % scale) ? BitMask : BitMask >> 1 ;
			}
		}
	}
}


Point OutGraphicsStringFont1(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale){
	int i = 0;
	while(s[i] != '\0'){
		OutGraphicsCharFont1(p.x + i*scale*(FONT1_XPIXELS + 1), p.y, colour, backgroundcolour, (int) s[i], Erase, scale);
		i++;
	}

	p.x = p.x + i*scale*(FONT1_XPIXELS + 1);
	p.y = p.y + FONT1_YPIXELS;
	return p;
}


void OutGraphicsCharFont2(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale)
{
	register int 	j, row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT2_YPIXELS;
		theColumn = FONT2_XPIXELS;

		for(row = 0, j = 1; j < theRow*scale ; j++)
		{
			pixels = Font10x14[theCharacter][row];		     								// get the pixels for row 0 of the character to be displayed
			row = ((j % scale) != 0) ? row : row + 1;
			BitMask = 512 ;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column <= theColumn*scale; column++)
			{
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel((Point){theX+column, theY+j}, theColour);
				else if(Erase == 1)																		// if not a valid pixel, do we erase or leave it along (no erase)
						WriteAPixel((Point){theX+column, theY+j}, backgroundcolour);

				BitMask = ((column % scale) != 0) ? BitMask : BitMask >> 1;
			}
		}
	}
}

Point OutGraphicsStringFont2(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale){
	int i = 0;
	while(s[i] != '\0'){
		OutGraphicsCharFont2(p.x + i*(FONT2_XPIXELS+1)*scale, p.y, colour, backgroundcolour, (int) s[i], Erase, scale);
		i++;
	}

	p.x = p.x + i*scale*(FONT2_XPIXELS + 1);
	p.y = p.y + FONT2_YPIXELS;
	return p;
}

void OutGraphicsCharFont3(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale)
{
	register int 	i, j, row,
					column,
					theX = x,
					theY = y ;
	register unsigned int 	pixels ;
	register char 	theColour = colour  ;
	register unsigned int 	BitMask,
					theCharacter = c,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT3_YPIXELS;
		theColumn = FONT3_XPIXELS;

		for(row = 0, j = 0; j < theRow*scale ; j++)	{
			i = theCharacter*theRow*2 + row;
			pixels = ((unsigned int) (Font16x27[i] << 8)) | ((unsigned int)0x00ff & Font16x27[i+1]);		     								// get the pixels for row 0 of the character to be displayed
			row = ((j % scale) != 0) ? row : row + 2;
			BitMask = 0x4000;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn*scale; column++)
			{
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel((Point){theX+column, theY+j}, theColour) ;
				else if(Erase == 1)																	// if not a valid pixel, do we erase or leave it along (no erase)
						WriteAPixel((Point){theX+column, theY+j}, backgroundcolour);

				BitMask = ((column % scale) != 0) ? BitMask : BitMask >> 1 ;
			}
		}
	}
}

Point OutGraphicsStringFont3(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale){
	int i = 0;
	while(s[i] != '\0'){
		OutGraphicsCharFont3(p.x + i*FONT3_XPIXELS*scale, p.y, colour, backgroundcolour, (int) s[i], Erase, scale);
		i++;
	}

	p.x = p.x + i*scale*(FONT3_XPIXELS + 1);
	p.y = p.y + FONT3_YPIXELS;
	return p;
}

void OutGraphicsCharFont4(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale)
{
	register int 	i, j, row,
					column,
					theX = x,
					theY = y ;
	register unsigned int 	pixels ;
	register char 	theColour = colour  ;
	register unsigned int 	BitMask,
					theCharacter = c,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT4_YPIXELS;
		theColumn = FONT4_XPIXELS;

		for(row = 0, j = 0; j < theRow*scale ; j++)	{
			i = theCharacter*theRow*3 + row;
			pixels = ((unsigned int) (Font22x40[i] << 16)) | ((unsigned int)0x00ff00 & Font22x40[i+1]<<8) | ((unsigned int)0x0000ff & Font22x40[i+2]);		     								// get the pixels for row 0 of the character to be displayed
			row = ((j % scale) != 0) ? row : row + 3;
			BitMask = 0x400000;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn*scale; column++)  	{
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel((Point){theX+column, theY+j}, theColour) ;
				else if(Erase == 1)																	// if not a valid pixel, do we erase or leave it along (no erase)
					WriteAPixel((Point){theX+column, theY+j}, backgroundcolour) ;

				BitMask = ((column % scale) != 0) ? BitMask : BitMask >> 1 ;
			}
		}
	}
}

Point OutGraphicsStringFont4(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale){
	int i = 0;
	while(s[i] != '\0'){
		OutGraphicsCharFont4(p.x + i*FONT4_XPIXELS*scale, p.y, colour, backgroundcolour, (int) s[i], Erase, scale);
		i++;
	}

	p.x = p.x + i*scale*(FONT4_XPIXELS + 1);
	p.y = p.y + FONT4_YPIXELS;
	return p;
}

void OutGraphicsCharFont5(int x, int y, int colour, int backgroundcolour, int c, int Erase, int scale)
{
	register int 	i, j, row,
					column,
					theX = x,
					theY = y ;
	register unsigned int 	pixels ;
	register char 	theColour = colour  ;
	register unsigned int 	BitMask,
					theCharacter = c,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT5_YPIXELS;
		theColumn = FONT5_XPIXELS;

		for(row = 0, j = 0; j < theRow*scale ; j++)	{
			i = theCharacter*theRow*4 + row;
			pixels = ((unsigned int) (Font32x59[i] << 24)) | ((unsigned int)0x00ff0000 & Font32x59[i+1]<< 16) |
					((unsigned int)0x0000ff00 & Font32x59[i+2]<< 8) | ((unsigned int)0x000000ff & Font32x59[i+3]);		     								// get the pixels for row 0 of the character to be displayed
			row = ((j % scale) != 0) ? row : row + 4;
			BitMask = 0x40000000;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn*scale; column++)  	{
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel((Point){theX+column, theY+j}, theColour) ;
				else if(Erase == 1)																	// if not a valid pixel, do we erase or leave it along (no erase)
					WriteAPixel((Point){theX+column, theY+j}, backgroundcolour) ;

				BitMask = ((column % scale) != 0) ? BitMask : BitMask >> 1 ;
			}
		}
	}
}

Point OutGraphicsStringFont5(Point p, int colour, int backgroundcolour, char* s, int Erase, int scale){
	int i = 0;
	while(s[i] != '\0'){
		OutGraphicsCharFont5(p.x + i*FONT5_XPIXELS*scale, p.y, colour, backgroundcolour, (int) s[i], Erase, scale);
		i++;
	}

	p.x = p.x + i*scale*(FONT5_XPIXELS + 1);
	p.y = p.y + FONT5_YPIXELS;
	return p;
}

Point OutGraphicsString(Point p, int colour, int backgroundcolour, char* s, int Erase, int font, int scale){
	switch(font)
	{
		case 1:
			p = OutGraphicsStringFont1(p, colour, backgroundcolour, s, Erase, scale);
			break;
		case 2:
			p = OutGraphicsStringFont2(p, colour, backgroundcolour, s, Erase, scale);
			break;
		case 3:
			p = OutGraphicsStringFont3(p, colour, backgroundcolour, s, Erase, scale);
			break;
		case 4:
			p = OutGraphicsStringFont4(p, colour, backgroundcolour, s, Erase, scale);
			break;
		case 5:
			p = OutGraphicsStringFont5(p, colour, backgroundcolour, s, Erase, scale);
			break;
		default:
			return p;
	}

	return p;
}
