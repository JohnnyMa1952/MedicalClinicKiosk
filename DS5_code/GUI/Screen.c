/*
 * Screen.c
 *
 *  Created on: Feb 22, 2019
 *      Author: Amir
 */

#include "Screen.h"
#include "../Touch/button.h"
#include "../Touch/buttonTable.h"
#include "../Touch/touch_api.h"
#include "../GPS/gps.h"
#include "../Graphics/Fonts.h"

Screen* createScreen(func1 draw, func1 resetState, func1 cleanup, ButtonTable* buttonTable){
	Screen *ret = (Screen*)malloc(sizeof(Screen));
	ret->draw = draw;
	ret->resetState = resetState;
	ret->cleanup = cleanup;
	ret->buttonTable = buttonTable;
	return ret;
}

void freeScreen(Screen* screen)
{
	clearbuttonTable(screen->buttonTable);
	free(screen);
}

void insertScreen(ScreenTable* screenTable, Screen* screen)
{
	if(screenTable->length == screenTable->size){
		screenTable->size *= 2;
		screenTable->array = (Screen **)realloc(screenTable->array, screenTable->size * sizeof(Screen *));

	}
	screenTable->array[screenTable->length] = screen;
	screenTable->length++;
}

ScreenTable* init_screenTable(int size)
{
	ScreenTable* screenTable = (ScreenTable *)malloc(sizeof(ScreenTable));
	screenTable->length = 0;
	screenTable->size = size;
	screenTable->array = (Screen **) malloc(sizeof(Screen*)*size);
	return screenTable;
}

void clearScreenTable(ScreenTable* screenTable)
{
	for(int i = 0; i<screenTable->length; i++)
		freeScreen(screenTable->array[i]);

	screenTable->length = 0;
	free(screenTable);
}

void removeScreen(ScreenTable* screenTable, Screen *screen)
{
	for(int i = 0; i<screenTable->length; i++){
		if(screen == screenTable->array[i]){
			for(;i<screenTable->length-1; i++)
				screenTable->array[i] = screenTable->array[i+1];
			screenTable->array[i] = NULL;
			screenTable->length--;
			free(screen);
			return;
		}
	}
}

void runGUI(ScreenTable* screenTable)
{

	Screen* s = screenTable->array[0];
	unsigned char retval = RELEASE_SAME_SCREEN;
	register int i = 0;
	register int j;

	if(s == NULL)
		return;


	while(1){
		s->draw();
		drawButtonTable(s->buttonTable);
		retval = handleTouch(s->buttonTable);

		switch(retval){
			case RELEASE_CHANGE_SCREEN_NEXT:
				s->cleanup();
				i++;

				if(i >= screenTable->length)
					return;

				s = screenTable->array[i];
				break;

			case RELEASE_CHANGE_SCREEN_PREV:
				s->cleanup();
				i--;

				if(i < 0)
					return;

				s = screenTable->array[i];
				break;

			case RELEASE_CHANGE_SCREEN_TWO_NEXT:
				s->cleanup();
				i += 2;

				if(i >= screenTable->length)
					return;

				s = screenTable->array[i];
				break;

			case RESET_GUI_STATE:
				for(j=0; j <= i; j++){
					screenTable->array[j]->resetState();
					screenTable->array[j]->cleanup();
				}
				i = 0;
				s = screenTable->array[i];
				break;
			case KILL_GUI:
			case ERROR_REALSE:
				for(j=0; j <= i; j++){
						screenTable->array[j]->resetState();
						screenTable->array[j]->cleanup();
				}
				clearScreenTable(screenTable);
				return;
		}
	}

}


void* timeTread(void* args)
{
	while(*((volatile unsigned char *) args) == RUN){
		getTime();
		OutGraphicsString((Point){350, 10}, WHITE, BLUE, timeString, 1, 2, 1);
	}

	return NULL;
}

// General Button functions
// Next Page Button Button
unsigned char draw_Next_Button(void){
	char c[] = "Next";
	register unsigned int x = CONTROL_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*8 + BORDER*2*8 + KEY_SIZE_X*8;
	register unsigned int y = CONTROL_KEY_Y + BORDER*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2, y + CONTROL_KEY_HEIGHT}, LIME);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2 + BORDER, y + CONTROL_KEY_HEIGHT + BORDER}, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){x + (KEY_SIZE_X*2 - length)/2, y + FONT_OFFSET_Y*3}, BLACK, LIME, c, 1, 3, 1);

	return 0;
}

unsigned char press_Next_Button(void){
	char c[] = "Next";
	register unsigned int x = CONTROL_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*8 + BORDER*2*8 + KEY_SIZE_X*8;
	register unsigned int y = CONTROL_KEY_Y + BORDER*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2, y + CONTROL_KEY_HEIGHT}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2 + BORDER, y + CONTROL_KEY_HEIGHT + BORDER}, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){x + (KEY_SIZE_X*2 - length)/2, y + FONT_OFFSET_Y*3}, WHITE, MAGENTA, c, 1, 3, 1);

	return 0;
}

unsigned char inside_Next_Button(Point press){
	register unsigned int x1 = CONTROL_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*8 + BORDER*2*8 + KEY_SIZE_X*8;
	register unsigned int y1 = CONTROL_KEY_Y + TOUCH_OFFSET + BORDER*2;
	register unsigned int x2 = x1 + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2 - TOUCH_OFFSET;
	register unsigned int y2 = y1 + CONTROL_KEY_HEIGHT - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// Cancel sign in Button Button
unsigned char draw_Cancel_Button(void){
	char c[] = "Cancel";
	register unsigned int x = CONTROL_KEY_X + OFFSET_ERROR;
	register unsigned int y = CONTROL_KEY_Y + BORDER*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X*2, y + CONTROL_KEY_HEIGHT}, RED);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X*2 + BORDER, y + CONTROL_KEY_HEIGHT + BORDER}, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){x + (KEY_SIZE_X*2 - length)/2, y + FONT_OFFSET_Y*3}, BLACK, RED, c, 1, 3, 1);

	return 0;
}

unsigned char press_Cancel_Button(void){
	char c[] = "Cancel";
	register unsigned int x = CONTROL_KEY_X + OFFSET_ERROR;
	register unsigned int y = CONTROL_KEY_Y + BORDER*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X*2, y + CONTROL_KEY_HEIGHT}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X*2 + BORDER, y + CONTROL_KEY_HEIGHT + BORDER}, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){x + (KEY_SIZE_X*2 - length)/2, y + FONT_OFFSET_Y*3}, WHITE, MAGENTA, c, 1, 3, 1);

	return 0;
}

unsigned char release_Cancel_Button(void){
	return RESET_GUI_STATE;
}

unsigned char inside_Cancel_Button(Point press){
	register unsigned int x1 = CONTROL_KEY_X + OFFSET_ERROR + TOUCH_OFFSET;
	register unsigned int y1 = CONTROL_KEY_Y + TOUCH_OFFSET + BORDER*2;
	register unsigned int x2 = x1 + KEY_SIZE_X*2 - TOUCH_OFFSET;
	register unsigned int y2 = y1 + CONTROL_KEY_HEIGHT - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}

// prev page button
unsigned char draw_Back_Button(void){
	char c[] = "Back";
	register unsigned int x = CONTROL_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y = CONTROL_KEY_Y + BORDER*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2, y + CONTROL_KEY_HEIGHT}, GRAY);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2 + BORDER, y + CONTROL_KEY_HEIGHT + BORDER}, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){x + (KEY_SIZE_X*2 - length)/2, y + FONT_OFFSET_Y*3}, BLACK, GRAY, c, 1, 3, 1);

	return 0;
}

unsigned char press_Back_Button(void){
	char c[] = "Back";
	register unsigned int x = CONTROL_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y = CONTROL_KEY_Y + BORDER*2;

	Filled_Rectangle((Point){x, y}, (Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2, y + CONTROL_KEY_HEIGHT}, MAGENTA);
	Bordered_Rectangle((Point){x - BORDER, y - BORDER},
			(Point){x + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2 + BORDER, y + CONTROL_KEY_HEIGHT + BORDER}, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){x + (KEY_SIZE_X*2 - length)/2, y + FONT_OFFSET_Y*3}, WHITE, MAGENTA, c, 1, 3, 1);

	return 0;
}

unsigned char inside_Back_Button(Point press){
	register unsigned int x1 = CONTROL_KEY_X + OFFSET_ERROR + SPACE_BETWEEN_KEYS*6 + BORDER*2*6 + KEY_SIZE_X*6;
	register unsigned int y1 = CONTROL_KEY_Y + TOUCH_OFFSET + BORDER*2;
	register unsigned int x2 = x1 + KEY_SIZE_X*2 + SPACE_BETWEEN_KEYS + BORDER*2 - TOUCH_OFFSET;
	register unsigned int y2 = y1 + CONTROL_KEY_HEIGHT - TOUCH_OFFSET;

	return (press.x >= x1) && (press.x <= x2) && (press.y >= y1) && (press.y <= y2);
}
