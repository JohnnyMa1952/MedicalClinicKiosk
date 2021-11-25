/*
 * PINameScreen.c
 *
 *  Created on: Feb 23, 2019
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

#define PINAME_TEXT_BOX_CAPACITY 40
#define PINAME_FIRST_KEY_X 35
#define PINAME_FIRST_KEY_Y 180

// text box variables
Point curserPositionNameBox;
unsigned char upperCaseFlag;

// welcome screen draw function
unsigned char draw_piname_screen(){
	int length, offset;
	upperCaseFlag = LOWER_CASE;

	// allocate text box array if it's empty
	if(nameTextBox == NULL && textBoxIndex == 0)
		nameTextBox = malloc(sizeof(char)*(PINAME_TEXT_BOX_CAPACITY + 1));

	// draw static text
	char patient[] = "Patient Information";
	char info[] = "Please enter your Full Name";

	length = GraphicsStringLength(patient, 4, 1);
	offset = (length <= XRES) ? (XRES - length) / 2 : 0;
	Clear(BLUE);
	OutGraphicsString((Point){offset + OFFSET_ERROR, 1}, WHITE, BLUE, patient, 1, 4, 1);

	length = GraphicsStringLength(info, 3, 1);
	offset = (length <= XRES) ? (XRES - length) / 2 : 0;
	OutGraphicsString((Point){offset + OFFSET_ERROR, 70}, WHITE, BLUE, info, 1, 3, 1);

	drawIcon((Point){5 + OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	// text box
	Filled_Rectangle((Point){40 + OFFSET_ERROR, 120}, (Point){740 + OFFSET_ERROR, 164}, WHITE);
	Bordered_Rectangle((Point){40 + OFFSET_ERROR - BORDER, 120 - BORDER},
			(Point){740 + OFFSET_ERROR + BORDER, 164 + BORDER}, BLACK, BORDER);

	curserPositionNameBox.x = 44 + OFFSET_ERROR;
	curserPositionNameBox.y = 127;

	char c[] = "|";
	Point ret;
	if(nameTextBox != NULL && textBoxIndex > 0){
		ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, nameTextBox, 1, 3, 1);
		curserPositionNameBox.x = ret.x;
	}
	OutGraphicsString(curserPositionNameBox, GRAY, WHITE, c, 1, 3, 1);

	return 0;
}

// PI name screen reset state function (does nothing as this screen has no state)
unsigned char resetState_piname_screen(void){
	if (nameTextBox != NULL)
		free(nameTextBox);
	nameTextBox = NULL;
	textBoxIndex = 0;
	return 0;
}


// PI name cleanup function (kills the threads used in this state - not threads in this screen)
unsigned char cleanup_piname_screen(void){
	return 0;
}

// --------------------------Buttons---------------------------

// Q Button

unsigned char draw_Q_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'Q');
	else
		sprintf(c, "%c", 'q');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_Q_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'Q');
	else
		sprintf(c, "%c", 'q');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_Q_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'Q');
			nameTextBox[textBoxIndex] = 'Q';
		}
		else{
			sprintf(c, "%c", 'q');
			nameTextBox[textBoxIndex] = 'q';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_Q_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X;
	register unsigned int y1 = PINAME_FIRST_KEY_Y;
	register unsigned int x2 = x1 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y + TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// E Button
unsigned char draw_W_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'W');
	else
		sprintf(c, "%c", 'w');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_W_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'W');
	else
		sprintf(c, "%c", 'w');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_W_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'W');
			nameTextBox[textBoxIndex] = 'W';
		}
		else{
			sprintf(c, "%c", 'w');
			nameTextBox[textBoxIndex] = 'w';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_W_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// E Button
unsigned char draw_E_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'E');
	else
		sprintf(c, "%c", 'e');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_E_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'E');
	else
		sprintf(c, "%c", 'e');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_E_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'E');
			nameTextBox[textBoxIndex] = 'E';
		}
		else{
			sprintf(c, "%c", 'e');
			nameTextBox[textBoxIndex] = 'e';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_E_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// R Button
unsigned char draw_R_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'R');
	else
		sprintf(c, "%c", 'r');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_R_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'R');
	else
		sprintf(c, "%c", 'r');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_R_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'R');
			nameTextBox[textBoxIndex] = 'R';
		}
		else{
			sprintf(c, "%c", 'r');
			nameTextBox[textBoxIndex] = 'r';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_R_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// T Button
unsigned char draw_T_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'T');
	else
		sprintf(c, "%c", 't');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_T_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'T');
	else
		sprintf(c, "%c", 't');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_T_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'T');
			nameTextBox[textBoxIndex] = 'T';
		}
		else{
			sprintf(c, "%c", 't');
			nameTextBox[textBoxIndex] = 't';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_T_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// Y Button
unsigned char draw_Y_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'Y');
	else
		sprintf(c, "%c", 'y');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*5 + BORDER*10 + KEY_SIZE_X*5;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_Y_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'Y');
	else
		sprintf(c, "%c", 'y');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*5 + BORDER*2*5 + KEY_SIZE_X*5;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_Y_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'Y');
			nameTextBox[textBoxIndex] = 'Y';
		}
		else{
			sprintf(c, "%c", 'y');
			nameTextBox[textBoxIndex] = 'y';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_Y_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*5 + BORDER*2*5 + KEY_SIZE_X*5 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// U Button
unsigned char draw_U_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'U');
	else
		sprintf(c, "%c", 'u');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_U_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'U');
	else
		sprintf(c, "%c", 'u');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_U_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'U');
			nameTextBox[textBoxIndex] = 'U';
		}
		else{
			sprintf(c, "%c", 'u');
			nameTextBox[textBoxIndex] = 'u';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_U_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*67/10 + BORDER*2*67/10 + KEY_SIZE_X*67/10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// I Button
unsigned char draw_I_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'I');
	else
		sprintf(c, "%c", 'i');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*7 + BORDER*2*7 + KEY_SIZE_X*7;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_I_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'I');
	else
		sprintf(c, "%c", 'i');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*7 + BORDER*2*7 + KEY_SIZE_X*7;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_I_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'I');
			nameTextBox[textBoxIndex] = 'I';
		}
		else{
			sprintf(c, "%c", 'i');
			nameTextBox[textBoxIndex] = 'i';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_I_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*76/10 + BORDER*2*76/10 + KEY_SIZE_X*76/10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// O Button
unsigned char draw_O_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'O');
	else
		sprintf(c, "%c", 'o');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*8 + BORDER*2*8 + KEY_SIZE_X*8;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_O_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'O');
	else
		sprintf(c, "%c", 'o');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*8 + BORDER*2*8 + KEY_SIZE_X*8;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_O_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'O');
			nameTextBox[textBoxIndex] = 'O';
		}
		else{
			sprintf(c, "%c", 'o');
			nameTextBox[textBoxIndex] = 'o';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_O_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*9 + BORDER*2*9 + KEY_SIZE_X*9 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// P Button
unsigned char draw_P_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'P');
	else
		sprintf(c, "%c", 'p');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*9 + BORDER*2*9 + KEY_SIZE_X*9;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_P_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'P');
	else
		sprintf(c, "%c", 'p');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*9 + BORDER*2*9 + KEY_SIZE_X*9;
	register unsigned int y = PINAME_FIRST_KEY_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_P_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'P');
			nameTextBox[textBoxIndex] = 'P';
		}
		else{
			sprintf(c, "%c", 'p');
			nameTextBox[textBoxIndex] = 'p';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_P_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*10 + BORDER*2*10 + KEY_SIZE_X*10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// A Button

unsigned char draw_A_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'A');
	else
		sprintf(c, "%c", 'a');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_A_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'A');
	else
		sprintf(c, "%c", 'a');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_A_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'A');
			nameTextBox[textBoxIndex] = 'A';
		}
		else{
			sprintf(c, "%c", 'a');
			nameTextBox[textBoxIndex] = 'a';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_A_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// S Button
unsigned char draw_S_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'S');
	else
		sprintf(c, "%c", 's');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_S_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'S');
	else
		sprintf(c, "%c", 's');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_S_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'S');
			nameTextBox[textBoxIndex] = 'S';
		}
		else{
			sprintf(c, "%c", 's');
			nameTextBox[textBoxIndex] = 's';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_S_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// D Button
unsigned char draw_D_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'D');
	else
		sprintf(c, "%c", 'd');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_D_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'D');
	else
		sprintf(c, "%c", 'd');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_D_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'D');
			nameTextBox[textBoxIndex] = 'D';
		}
		else{
			sprintf(c, "%c", 'd');
			nameTextBox[textBoxIndex] = 'd';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_D_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// F Button
unsigned char draw_F_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'F');
	else
		sprintf(c, "%c", 'f');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_F_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'F');
	else
		sprintf(c, "%c", 'f');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_F_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'F');
			nameTextBox[textBoxIndex] = 'F';
		}
		else{
			sprintf(c, "%c", 'f');
			nameTextBox[textBoxIndex] = 'f';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_F_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// G Button
unsigned char draw_G_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'G');
	else
		sprintf(c, "%c", 'g');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_G_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'G');
	else
		sprintf(c, "%c", 'g');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_G_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'G');
			nameTextBox[textBoxIndex] = 'G';
		}
		else{
			sprintf(c, "%c", 'g');
			nameTextBox[textBoxIndex] = 'g';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_G_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// H Button
unsigned char draw_H_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'H');
	else
		sprintf(c, "%c", 'h');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*5 + BORDER*10 + KEY_SIZE_X*5;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y ;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_H_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'H');
	else
		sprintf(c, "%c", 'h');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*5 + BORDER*2*5 + KEY_SIZE_X*5;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y ;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_H_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'H');
			nameTextBox[textBoxIndex] = 'H';
		}
		else{
			sprintf(c, "%c", 'h');
			nameTextBox[textBoxIndex] = 'h';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_H_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*5 + BORDER*2*5 + KEY_SIZE_X*5 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// J Button
unsigned char draw_J_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'J');
	else
		sprintf(c, "%c", 'j');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_J_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'J');
	else
		sprintf(c, "%c", 'j');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_J_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'J');
			nameTextBox[textBoxIndex] = 'J';
		}
		else{
			sprintf(c, "%c", 'j');
			nameTextBox[textBoxIndex] = 'j';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_J_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*67/10 + BORDER*2*67/10 + KEY_SIZE_X*67/10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// K Button
unsigned char draw_K_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'K');
	else
		sprintf(c, "%c", 'k');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*7 + BORDER*2*7 + KEY_SIZE_X*7;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_K_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'K');
	else
		sprintf(c, "%c", 'k');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*7 + BORDER*2*7 + KEY_SIZE_X*7;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_K_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'K');
			nameTextBox[textBoxIndex] = 'K';
		}
		else{
			sprintf(c, "%c", 'k');
			nameTextBox[textBoxIndex] = 'k';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_K_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*76/10 + BORDER*2*76/10 + KEY_SIZE_X*76/10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// L Button
unsigned char draw_L_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'L');
	else
		sprintf(c, "%c", 'l');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*8 + BORDER*2*8 + KEY_SIZE_X*8;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_L_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'L');
	else
		sprintf(c, "%c", 'l');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*8 + BORDER*2*8 + KEY_SIZE_X*8;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_L_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'L');
			nameTextBox[textBoxIndex] = 'L';
		}
		else{
			sprintf(c, "%c", 'l');
			nameTextBox[textBoxIndex] = 'l';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_L_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*85/10 + BORDER*2*85/10 + KEY_SIZE_X*85/10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// Delete (back space) Button
unsigned char draw_PIName_Delete_Button(void){
	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*9 + BORDER*2*9 + KEY_SIZE_X*9;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	drawIcon((Point){x, y}, BLACK, YELLOW, 1, BACKSPACE);

	return 0;
}

unsigned char press_PIName_Delete_Button(void){
	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*9 + BORDER*2*9 + KEY_SIZE_X*9;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	drawIcon((Point){x, y}, WHITE, MAGENTA, 1, BACKSPACE);

	return 0;
}

unsigned char release_PIName_Delete_Button(void){
	char c[2]= " ";
	if (textBoxIndex > 0)
	{
		nameTextBox[textBoxIndex] = '\0';

		textBoxIndex--;
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x - FONT_STEP, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = curserPositionNameBox.x - FONT_STEP;
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_PIName_Delete_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*96/10 + BORDER*2*96/10 + KEY_SIZE_X*96/10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_Y + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// Z Button

unsigned char draw_Z_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'Z');
	else
		sprintf(c, "%c", 'z');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_Z_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'Z');
	else
		sprintf(c, "%c", 'z');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_Z_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'Z');
			nameTextBox[textBoxIndex] = 'Z';
		}
		else{
			sprintf(c, "%c", 'z');
			nameTextBox[textBoxIndex] = 'z';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_Z_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// X Button
unsigned char draw_X_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'X');
	else
		sprintf(c, "%c", 'x');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_X_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'X');
	else
		sprintf(c, "%c", 'x');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_X_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'X');
			nameTextBox[textBoxIndex] = 'X';
		}
		else{
			sprintf(c, "%c", 'x');
			nameTextBox[textBoxIndex] = 'x';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_X_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS + BORDER*2 + KEY_SIZE_X + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2 + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// C Button
unsigned char draw_C_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'C');
	else
		sprintf(c, "%c", 'c');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_C_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'C');
	else
		sprintf(c, "%c", 'c');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_C_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'C');
			nameTextBox[textBoxIndex] = 'C';
		}
		else{
			sprintf(c, "%c", 'c');
			nameTextBox[textBoxIndex] = 'c';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_C_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_X*2 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2 + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// V Button
unsigned char draw_V_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'V');
	else
		sprintf(c, "%c", 'v');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_V_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'V');
	else
		sprintf(c, "%c", 'v');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_V_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'V');
			nameTextBox[textBoxIndex] = 'V';
		}
		else{
			sprintf(c, "%c", 'v');
			nameTextBox[textBoxIndex] = 'v';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_V_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*6 + KEY_SIZE_X*3 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2 + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// B Button
unsigned char draw_B_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'B');
	else
		sprintf(c, "%c", 'b');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_B_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'B');
	else
		sprintf(c, "%c", 'b');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_B_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'B');
			nameTextBox[textBoxIndex] = 'B';
		}
		else{
			sprintf(c, "%c", 'b');
			nameTextBox[textBoxIndex] = 'b';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_B_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*4 + BORDER*8 + KEY_SIZE_X*4 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2 + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// H Button
unsigned char draw_N_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'N');
	else
		sprintf(c, "%c", 'n');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*5 + BORDER*10 + KEY_SIZE_X*5;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_N_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'N');
	else
		sprintf(c, "%c", 'n');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*5 + BORDER*2*5 + KEY_SIZE_X*5;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_N_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'N');
			nameTextBox[textBoxIndex] = 'N';
		}
		else{
			sprintf(c, "%c", 'n');
			nameTextBox[textBoxIndex] = 'n';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_N_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*5 + BORDER*2*5 + KEY_SIZE_X*5 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2 + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// M Button
unsigned char draw_M_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'M');
	else
		sprintf(c, "%c", 'm');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, BLACK, YELLOW, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char press_M_Button(void){
	char c[2];
	if(upperCaseFlag == UPPER_CASE)
		sprintf(c, "%c", 'M');
	else
		sprintf(c, "%c", 'm');

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);
	OutGraphicsString((Point){x + FONT_OFFSET_X, y + FONT_OFFSET_Y}, WHITE, MAGENTA, c, 1, KEY_FONT, 1);

	return 0;
}

unsigned char release_M_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		if(upperCaseFlag == UPPER_CASE){
			sprintf(c, "%c", 'M');
			nameTextBox[textBoxIndex] = 'M';
		}
		else{
			sprintf(c, "%c", 'm');
			nameTextBox[textBoxIndex] = 'm';
		}
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_M_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*67/10 + BORDER*2*67/10 + KEY_SIZE_X*67/10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2 + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// Space Button
unsigned char draw_Space_Button(void){
	char c[] = "Space";

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*7 + BORDER*2*7 + KEY_SIZE_X*7;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2, y + KEY_SIZE_Y}, YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);

	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){x + (KEY_SIZE_X*2 - length)/2, y + FONT_OFFSET_Y*4}, BLACK, YELLOW, c, 1, 3, 1);

	return 0;
}

unsigned char press_Space_Button(void){
	char c[] = "Space";

	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*7 + BORDER*2*7 + KEY_SIZE_X*7;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);

	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){x + (KEY_SIZE_X*2 - length)/2, y + FONT_OFFSET_Y*4}, WHITE, MAGENTA, c, 1, 3, 1);

	return 0;
}

unsigned char release_Space_Button(void){
	char c[2];
	if (textBoxIndex < PINAME_TEXT_BOX_CAPACITY)
	{
		sprintf(c, "%c", ' ');
		nameTextBox[textBoxIndex] = ' ';
		textBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionNameBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionNameBox.x, curserPositionNameBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_Space_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*76/10 + BORDER*2*76/10 + KEY_SIZE_X*76/10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;
	register unsigned int x2 = x1 + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2 - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// UpperCase Button
unsigned char draw_UpperCase_Button(void){
	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*9 + BORDER*2*9 + KEY_SIZE_X*9;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, (upperCaseFlag == UPPER_CASE) ? ORANGE : YELLOW);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);

	drawIcon((Point){x, y}, BLACK, (upperCaseFlag == UPPER_CASE) ? ORANGE : YELLOW, 1, UPARROW);

	return 0;
}

unsigned char press_UpperCase_Button(void){
	register unsigned int x = PINAME_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*9 + BORDER*2*9 + KEY_SIZE_X*9;
	register unsigned int y = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X, y + KEY_SIZE_Y}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X + BORDER, y + KEY_SIZE_Y + BORDER}, BLACK, BORDER);

	drawIcon((Point){x, y}, WHITE, MAGENTA, 1, UPARROW);

	return 0;
}

unsigned char release_UpperCase_Button(void){
	upperCaseFlag = (upperCaseFlag == UPPER_CASE) ? LOWER_CASE : UPPER_CASE;
	return REDRAW_ALL_ON_RELEASE;
}

unsigned char inside_UpperCase_Button(Point press){
	register unsigned int x1 = PINAME_FIRST_KEY_X + SPACE_BETWEEN_KEYS*10 + BORDER*2*10 + KEY_SIZE_X*10 + TOUCH_OFFSET;
	register unsigned int y1 = PINAME_FIRST_KEY_Y + SPACE_BETWEEN_KEYS*2 + BORDER*4 + KEY_SIZE_Y*2 + TOUCH_OFFSET;
	register unsigned int x2 = x1 + KEY_SIZE_X - TOUCH_OFFSET;
	register unsigned int y2 = y1 + KEY_SIZE_Y - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// Release function for the "next" button of this screen
unsigned char release_PIName_Next_Button(void){
	nameTextBox[textBoxIndex] = '\0';
	return RELEASE_CHANGE_SCREEN_NEXT;
}

// ------------------------- Generate Screen ----------------------------------
// generates a welcome screen (called from main)
Screen* generatePINameScreen(void){
	upperCaseFlag = LOWER_CASE;
	curserPositionNameBox = (Point){0,0};
	textBoxIndex = 0;
	ButtonTable* bt = init_buttonTable(32);

	Button* b = new_button(draw_Q_Button, press_Q_Button, release_Q_Button, inside_Q_Button);
	insertButton(bt, b);

	b = new_button(draw_D_Button, press_D_Button, release_D_Button, inside_D_Button);
	insertButton(bt, b);

	b = new_button(draw_W_Button, press_W_Button, release_W_Button, inside_W_Button);
	insertButton(bt, b);

	b = new_button(draw_E_Button, press_E_Button, release_E_Button, inside_E_Button);
	insertButton(bt, b);

	b = new_button(draw_R_Button, press_R_Button, release_R_Button, inside_R_Button);
	insertButton(bt, b);

	b = new_button(draw_T_Button, press_T_Button, release_T_Button, inside_T_Button);
	insertButton(bt, b);

	b = new_button(draw_Y_Button, press_Y_Button, release_Y_Button, inside_Y_Button);
	insertButton(bt, b);

	b = new_button(draw_U_Button, press_U_Button, release_U_Button, inside_U_Button);
	insertButton(bt, b);

	b = new_button(draw_I_Button, press_I_Button, release_I_Button, inside_I_Button);
	insertButton(bt, b);

	b = new_button(draw_O_Button, press_O_Button, release_O_Button, inside_O_Button);
	insertButton(bt, b);

	b = new_button(draw_P_Button, press_P_Button, release_P_Button, inside_P_Button);
	insertButton(bt, b);

	b = new_button(draw_A_Button, press_A_Button, release_A_Button, inside_A_Button);
	insertButton(bt, b);

	b = new_button(draw_S_Button, press_S_Button, release_S_Button, inside_S_Button);
	insertButton(bt, b);

	b = new_button(draw_G_Button, press_G_Button, release_G_Button, inside_G_Button);
	insertButton(bt, b);

	b = new_button(draw_H_Button, press_H_Button, release_H_Button, inside_H_Button);
	insertButton(bt, b);

	b = new_button(draw_J_Button, press_J_Button, release_J_Button, inside_J_Button);
	insertButton(bt, b);

	b = new_button(draw_K_Button, press_K_Button, release_K_Button, inside_K_Button);
	insertButton(bt, b);

	b = new_button(draw_L_Button, press_L_Button, release_L_Button, inside_L_Button);
	insertButton(bt, b);

	b = new_button(draw_Z_Button, press_Z_Button, release_Z_Button, inside_Z_Button);
	insertButton(bt, b);

	b = new_button(draw_X_Button, press_X_Button, release_X_Button, inside_X_Button);
	insertButton(bt, b);

	b = new_button(draw_F_Button, press_F_Button, release_F_Button, inside_F_Button);
	insertButton(bt, b);

	b = new_button(draw_C_Button, press_C_Button, release_C_Button, inside_C_Button);
	insertButton(bt, b);

	b = new_button(draw_V_Button, press_V_Button, release_V_Button, inside_V_Button);
	insertButton(bt, b);

	b = new_button(draw_B_Button, press_B_Button, release_B_Button, inside_B_Button);
	insertButton(bt, b);

	b = new_button(draw_N_Button, press_N_Button, release_N_Button, inside_N_Button);
	insertButton(bt, b);

	b = new_button(draw_M_Button, press_M_Button, release_M_Button, inside_M_Button);
	insertButton(bt, b);

	b = new_button(draw_UpperCase_Button, press_UpperCase_Button, release_UpperCase_Button, inside_UpperCase_Button);
	insertButton(bt, b);

	b = new_button(draw_PIName_Delete_Button, press_PIName_Delete_Button, release_PIName_Delete_Button, inside_PIName_Delete_Button);
	insertButton(bt, b);

	b = new_button(draw_Space_Button, press_Space_Button, release_Space_Button, inside_Space_Button);
	insertButton(bt, b);

	b = new_button(draw_Next_Button, press_Next_Button, release_PIName_Next_Button, inside_Next_Button);
	insertButton(bt, b);

	b = new_button(draw_Cancel_Button, press_Cancel_Button, release_Cancel_Button, inside_Cancel_Button);
	insertButton(bt, b);

	return createScreen(draw_piname_screen, resetState_piname_screen, cleanup_piname_screen, bt);
}
