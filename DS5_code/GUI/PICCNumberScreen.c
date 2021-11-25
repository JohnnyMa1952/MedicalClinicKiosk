/*
 * PICCNumberScreen.c
 *
 *  Created on: Feb 25, 2019
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

#define PICC_NUM_BOX_CAPACITY 13

#define PICC_FIRST_KEY_X 250
#define PICC_FIRST_KEY_Y 150

// text box variables
Point curserPositionCCBox;

// welcome screen draw function
unsigned char draw_picarecard_screen(){
	int length, offset;

	// allocate phone number box array if it's empty
	if(careCardNumberBox == NULL && careCardNumberBoxIndex == 0)
		careCardNumberBox = malloc(sizeof(char)*(PICC_NUM_BOX_CAPACITY + 1));

	// draw static text
	char patient[] = "Patient Information";
	char info[] = "Please enter your Care Card number";

	length = GraphicsStringLength(patient, 4, 1);
	offset = (length <= XRES) ? (XRES - length) / 2 : 0;
	Clear(BLUE);
	OutGraphicsString((Point){offset + OFFSET_ERROR, 1}, WHITE, BLUE, patient, 1, 4, 1);

	length = GraphicsStringLength(info, 3, 1);
	offset = (length <= XRES) ? (XRES - length) / 2 : 0;
	OutGraphicsString((Point){offset + OFFSET_ERROR, 50}, WHITE, BLUE, info, 1, 3, 1);

	drawIcon((Point){5 + OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	// text box
	Filled_Rectangle((Point){PICC_FIRST_KEY_X + OFFSET_ERROR, 85},
			(Point){PICC_FIRST_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*4, 123}, WHITE);
	Bordered_Rectangle((Point){PICC_FIRST_KEY_X + OFFSET_ERROR - BORDER, 85 - BORDER},
			(Point){PICC_FIRST_KEY_X + SPACE_BETWEEN_KEYS*3 + BORDER*2*3 + KEY_SIZE_X*4 + OFFSET_ERROR + BORDER, 123 + BORDER}, BLACK, BORDER);

	curserPositionCCBox.x = PICC_FIRST_KEY_X + 3 + OFFSET_ERROR;
	curserPositionCCBox.y = 89;

	char c[] = "|";
	Point ret;
	if(careCardNumberBox != NULL && careCardNumberBoxIndex > 0){
		ret = OutGraphicsString(curserPositionCCBox, BLACK, WHITE, careCardNumberBox, 1, 3, 1);
		curserPositionCCBox.x = ret.x;
	}
	OutGraphicsString(curserPositionCCBox, GRAY, WHITE, c, 1, 3, 1);

	return 0;
}

// PI phone number screen reset state function (does nothing as this screen has no state)
unsigned char resetState_picarecard_screen(void){
	if (careCardNumberBox != NULL)
		free(careCardNumberBox);
	careCardNumberBox = NULL;
	careCardNumberBoxIndex = 0;
	return 0;
}


// PI phone number cleanup function (kills the threads used in this state - not threads in this screen)
unsigned char cleanup_picarecard_screen(void){
	return 0;
}

// --------------------------Buttons---------------------------
unsigned char release_picarecard_6_Button(void){
	char c[2] = "6";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '6';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_7_Button(void){
	char c[2] = "7";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '7';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_8_Button(void){
	char c[2] = "8";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '8';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_9_Button(void){
	char c[2] = "9";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '9';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_2_Button(void){
	char c[2] = "2";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '2';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_3_Button(void){
	char c[2] = "3";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '3';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_4_Button(void){
	char c[2] = "4";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '4';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_5_Button(void){
	char c[2] = "5";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '5';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_Plus_Button(void){
	char c[2] = "+";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '+';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_0_Button(void){
	char c[2] = "0";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '0';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_1_Button(void){
	char c[2] = "1";
	if (careCardNumberBoxIndex < PICC_NUM_BOX_CAPACITY)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '1';
		careCardNumberBoxIndex++;
		Point ret = OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = ret.x;

		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char release_picarecard_Delete_Button(void){
	char c[2] = " ";
	if (careCardNumberBoxIndex > 0)
	{
		careCardNumberBox[careCardNumberBoxIndex] = '\0';
		careCardNumberBoxIndex--;

		OutGraphicsString((Point){curserPositionCCBox.x, curserPositionCCBox.y}, BLACK, WHITE, c, 1, 3, 1);
		sprintf(c, "%c", '|');
		OutGraphicsString((Point){curserPositionCCBox.x - FONT_STEP, curserPositionCCBox.y}, GRAY, WHITE, c, 1, 3, 1);
		curserPositionCCBox.x = curserPositionCCBox.x - FONT_STEP;
	}
	return REDRAW_THIS_ON_RELEASE;
}

// Release function for the "next" button of this screen
unsigned char release_picarecardNumber_Next_Button(void){
	careCardNumberBox[careCardNumberBoxIndex] = '\0';
	return RELEASE_CHANGE_SCREEN_NEXT;
}

// Release function for the "back" button of this screen
unsigned char release_picarecardNumber_Back_Button(void){
	careCardNumberBox[careCardNumberBoxIndex] = '\0';
	return RELEASE_CHANGE_SCREEN_PREV;
}

// ------------------------- Generate Screen ----------------------------------
// generates a welcome screen (called from main)
Screen* generatePICarecardNumberScreen(void){
	curserPositionCCBox = (Point){0,0};
	careCardNumberBoxIndex = 0;
	ButtonTable* bt = init_buttonTable(16);
	Button* b = new_button(draw_0_Button, press_0_Button, release_picarecard_0_Button, inside_0_Button);
	insertButton(bt, b);

	b = new_button(draw_1_Button, press_1_Button, release_picarecard_1_Button, inside_1_Button);
	insertButton(bt, b);

	b = new_button(draw_2_Button, press_2_Button, release_picarecard_2_Button, inside_2_Button);
	insertButton(bt, b);

	b = new_button(draw_3_Button, press_3_Button, release_picarecard_3_Button, inside_3_Button);
	insertButton(bt, b);

	b = new_button(draw_4_Button, press_4_Button, release_picarecard_4_Button, inside_4_Button);
	insertButton(bt, b);

	b = new_button(draw_5_Button, press_5_Button, release_picarecard_5_Button, inside_5_Button);
	insertButton(bt, b);

	b = new_button(draw_6_Button, press_6_Button, release_picarecard_6_Button, inside_6_Button);
	insertButton(bt, b);

	b = new_button(draw_7_Button, press_7_Button, release_picarecard_7_Button, inside_7_Button);
	insertButton(bt, b);

	b = new_button(draw_8_Button, press_8_Button, release_picarecard_8_Button, inside_8_Button);
	insertButton(bt, b);

	b = new_button(draw_9_Button, press_9_Button, release_picarecard_9_Button, inside_9_Button);
	insertButton(bt, b);

	b = new_button(draw_Plus_Button, press_Plus_Button, release_picarecard_Plus_Button, inside_Plus_Button);
	insertButton(bt, b);

	b = new_button(draw_Delete_Button, press_Delete_Button, release_picarecard_Delete_Button, inside_Delete_Button);
	insertButton(bt, b);

	b = new_button(draw_Back_Button, press_Back_Button, release_picarecardNumber_Back_Button, inside_Back_Button);
	insertButton(bt, b);

	b = new_button(draw_Next_Button, press_Next_Button, release_picarecardNumber_Next_Button, inside_Next_Button);
	insertButton(bt, b);

	b = new_button(draw_Cancel_Button, press_Cancel_Button, release_Cancel_Button, inside_Cancel_Button);
	insertButton(bt, b);

	return createScreen(draw_picarecard_screen, resetState_picarecard_screen, cleanup_picarecard_screen, bt);
}
