/*
 * PIPhoneNumberScreen.c
 *
 *  Created on: Feb 24, 2019
 *      Author: Amir
 */

#include "Screen.h"
#include "GUI.h"
#include "../Touch/button.h"
#include "../Graphics/Fonts.h"
#include "../Graphics/Graphics.h"
#include "../Touch/touch_api.h"
#include "../Point/Point.h"
#include "../Graphics/Icon.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define PIPHONE_NUM_BOX_CAPACITY 13

#define PIPHONE_FIRST_KEY_X 250
#define PIPHONE_FIRST_KEY_Y 150

// text box variables
Point curserPositionPhoneBox;

// welcome screen draw function
unsigned char draw_piphone_screen(){
	int length, offset;

	// allocate phone number box array if it's empty
	if(phoneNumberBox == NULL && numberBoxIndex == 0)
		phoneNumberBox = malloc(sizeof(char)*(PIPHONE_NUM_BOX_CAPACITY + 1));

	// draw static text
	char patient[] = "Patient Information";
	char info[] = "Please enter your Phone Number";

	length = GraphicsStringLength(patient, 4, 1);
	offset = (length <= XRES) ? (XRES - length) / 2 : 0;
	Clear(BLUE);
	OutGraphicsString((Point){offset + OFFSET_ERROR, 1}, WHITE, BLUE, patient, 1, 4, 1);

	length = GraphicsStringLength(info, 3, 1);
	offset = (length <= XRES) ? (XRES - length) / 2 : 0;
	OutGraphicsString((Point){offset + OFFSET_ERROR, 50}, WHITE, BLUE, info, 1, 3, 1);

	drawIcon((Point){5 + OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	// text box
	Filled_Rectangle((Point){PIPHONE_FIRST_KEY_X + OFFSET_ERROR, 85},
			(Point){PIPHONE_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*4, 123}, WHITE);
	Bordered_Rectangle((Point){PIPHONE_FIRST_KEY_X + OFFSET_ERROR - BORDER, 85 - BORDER},
			(Point){PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*4 + OFFSET_ERROR + BORDER, 123 + BORDER}, BLACK, BORDER);

	curserPositionPhoneBox.x = PIPHONE_FIRST_KEY_X + 3 + OFFSET_ERROR;
	curserPositionPhoneBox.y = 89;

	char c[] = "|";
	Point ret;
	if(phoneNumberBox != NULL && numberBoxIndex > 0){
		ret = OutGraphicsString(curserPositionPhoneBox, BLACK, WHITE, phoneNumberBox, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;
	}
	OutGraphicsString(curserPositionPhoneBox, GRAY, WHITE, c, 1, 3, 1);

	return 0;
}

// PI phone number screen reset state function (does nothing as this screen has no state)
unsigned char resetState_piphone_screen(void){
	if (phoneNumberBox != NULL)
		free(phoneNumberBox);
	phoneNumberBox = NULL;
	numberBoxIndex = 0;
	return 0;
}


// PI phone number cleanup function (kills the threads used in this state - not threads in this screen)
unsigned char cleanup_piphone_screen(void){
	return 0;
}

// --------------------------Buttons---------------------------

// 6 Button
unsigned char draw_6_Button(void){
	char c[2] = "6";
	register unsigned int x = PIPHONE_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_6_Button(void){
	char c[2] = "6";
	register unsigned int x = PIPHONE_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_6_Button(void){
	char c[2] = "6";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '6';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_6_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 7 Button
unsigned char draw_7_Button(void){
	char c[2] = "7";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_7_Button(void){
	char c[2] = "7";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_7_Button(void){
	char c[2] = "7";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '7';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_7_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 8 Button
unsigned char draw_8_Button(void){
	char c[2] = "8";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_8_Button(void){
	char c[2] = "8";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_8_Button(void){
	char c[2] = "8";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '8';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_8_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 9 Button
unsigned char draw_9_Button(void){
	char c[2] = "9";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_9_Button(void){
	char c[2] = "9";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_9_Button(void){
	char c[2] = "9";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '9';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_9_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 2 Button
unsigned char draw_2_Button(void){
	char c[2] = "2";
	register unsigned int x = PIPHONE_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_2_Button(void){
	char c[2] = "2";
	register unsigned int x = PIPHONE_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_2_Button(void){
	char c[2] = "2";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '2';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_2_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 3 Button
unsigned char draw_3_Button(void){
	char c[2] = "3";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_3_Button(void){
	char c[2] = "3";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_3_Button(void){
	char c[2] = "3";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '3';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_3_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 4 Button
unsigned char draw_4_Button(void){
	char c[2] = "4";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_4_Button(void){
	char c[2] = "4";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_4_Button(void){
	char c[2] = "4";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '4';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_4_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 5 Button
unsigned char draw_5_Button(void){
	char c[2] = "5";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_5_Button(void){
	char c[2] = "5";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_5_Button(void){
	char c[2] = "5";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '5';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_5_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// Plus Button
unsigned char draw_Plus_Button(void){
	char c[2] = "+";
	register unsigned int x = PIPHONE_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_Plus_Button(void){
	char c[2] = "+";
	register unsigned int x = PIPHONE_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_Plus_Button(void){
	char c[2] = "+";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '+';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_Plus_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 0 Button
unsigned char draw_0_Button(void){
	char c[2] = "0";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_0_Button(void){
	char c[2] = "0";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_0_Button(void){
	char c[2] = "0";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '0';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_0_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// 1 Button
unsigned char draw_1_Button(void){
	char c[2] = "1";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_1_Button(void){
	char c[2] = "1";
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_PIPhone_1_Button(void){
	char c[2] = "1";
	if (numberBoxIndex < PIPHONE_NUM_BOX_CAPACITY)
	{
		phoneNumberBox[numberBoxIndex] = '1';
		numberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_1_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*2*2 + KEY_SIZE_X*2;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// delete Button
unsigned char draw_Delete_Button(void){
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	drawIcon((Point){x, y}, BLACK, YELLOW, 1, BACKSPACE);

	return 0;
}

unsigned char press_Delete_Button(void){
	register unsigned int x = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3 + OFFSET_ERROR;
	register unsigned int y = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	drawIcon((Point){x, y}, WHITE, MAGENTA, 1, BACKSPACE);

	return 0;
}

unsigned char release_PIPhone_Delete_Button(void){
	char c[2] = " ";
	if (numberBoxIndex > 0)
	{
		phoneNumberBox[numberBoxIndex] = '\0';
		numberBoxIndex--;

		OutGraphicsString((Point){curserPositionPhoneBox.x, curserPositionPhoneBox.y}, BLACK, WHITE, c, 1, 3, 1);
		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionPhoneBox.x - FONT_STEP, curserPositionPhoneBox.y}, GRAY, WHITE, c, 1, 3, 1);
		curserPositionPhoneBox.x = curserPositionPhoneBox.x - FONT_STEP;
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_Delete_Button(Point press){
	register unsigned int x1 = PIPHONE_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*3;
	register unsigned int y1 = PIPHONE_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// Release function for the "next" button of this screen
unsigned char release_PIPhoneNumber_Next_Button(void){
	phoneNumberBox[numberBoxIndex] = '\0';
	return RELEASE_CHANGE_SCREEN_NEXT;
}

// Release function for the "back" button of this screen
unsigned char release_PIPhoneNumber_Back_Button(void){
	phoneNumberBox[numberBoxIndex] = '\0';
	return RELEASE_CHANGE_SCREEN_PREV;
}

// ------------------------- Generate Screen ----------------------------------
// generates a welcome screen (called from main)
Screen* generatePIPhoneNumberScreen(void){
	curserPositionPhoneBox = (Point){0,0};
	numberBoxIndex = 0;
	ButtonTable* bt = init_buttonTable(16);
	Button* b = new_button(draw_0_Button, press_0_Button, release_PIPhone_0_Button, inside_0_Button);
	insertButton(bt, b);

	b = new_button(draw_1_Button, press_1_Button, release_PIPhone_1_Button, inside_1_Button);
	insertButton(bt, b);

	b = new_button(draw_2_Button, press_2_Button, release_PIPhone_2_Button, inside_2_Button);
	insertButton(bt, b);

	b = new_button(draw_3_Button, press_3_Button, release_PIPhone_3_Button, inside_3_Button);
	insertButton(bt, b);

	b = new_button(draw_4_Button, press_4_Button, release_PIPhone_4_Button, inside_4_Button);
	insertButton(bt, b);

	b = new_button(draw_5_Button, press_5_Button, release_PIPhone_5_Button, inside_5_Button);
	insertButton(bt, b);

	b = new_button(draw_6_Button, press_6_Button, release_PIPhone_6_Button, inside_6_Button);
	insertButton(bt, b);

	b = new_button(draw_7_Button, press_7_Button, release_PIPhone_7_Button, inside_7_Button);
	insertButton(bt, b);

	b = new_button(draw_8_Button, press_8_Button, release_PIPhone_8_Button, inside_8_Button);
	insertButton(bt, b);

	b = new_button(draw_9_Button, press_9_Button, release_PIPhone_9_Button, inside_9_Button);
	insertButton(bt, b);

	b = new_button(draw_Plus_Button, press_Plus_Button, release_PIPhone_Plus_Button, inside_Plus_Button);
	insertButton(bt, b);

	b = new_button(draw_Delete_Button, press_Delete_Button, release_PIPhone_Delete_Button, inside_Delete_Button);
	insertButton(bt, b);

	b = new_button(draw_Back_Button, press_Back_Button, release_PIPhoneNumber_Back_Button, inside_Back_Button);
	insertButton(bt, b);

	b = new_button(draw_Next_Button, press_Next_Button, release_PIPhoneNumber_Next_Button, inside_Next_Button);
	insertButton(bt, b);

	b = new_button(draw_Cancel_Button, press_Cancel_Button, release_Cancel_Button, inside_Cancel_Button);
	insertButton(bt, b);

	return createScreen(draw_piphone_screen, resetState_piphone_screen, cleanup_piphone_screen, bt);
}
