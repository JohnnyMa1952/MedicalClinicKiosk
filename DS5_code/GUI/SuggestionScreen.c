/*
 * SuggestionScreen.c
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
#include "../WIFI/WIFI.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define DECLINE_BUTTON_UL ((Point){30 + OFFSET_ERROR, 380})
#define DECLINE_BUTTON_LR ((Point){290 + OFFSET_ERROR, 460})

#define ACCEPT_BUTTON_UL ((Point){500 + OFFSET_ERROR, 380})
#define ACCEPT_BUTTON_LR ((Point){760 + OFFSET_ERROR, 460})

#define CANCEL_BUTTON_UL ((Point){722 + OFFSET_ERROR, 8})
#define CANCEL_BUTTON_LR ((Point){762 + OFFSET_ERROR, 58})

unsigned char draw_suggestion_screen(void){
	int length, offset;

	char suggestion[] = "Want to wait less?";
	char messg2[] = "It looks like there is a longer wait than usual.";
	char messg3[] = "Would you like to visit the clinic below instead?";
	char* positionInLineHere = malloc(sizeof(char)*50);
	char* positionInLineThere = malloc(sizeof(char)*50);
	char* addr = malloc(sizeof(char)*160);

	Clear(BLUE);
	drawIcon((Point){5+ OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	length = GraphicsStringLength(suggestion, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,2}, WHITE, BLUE, suggestion, 1, 4, 1);

	sprintf(positionInLineHere,"Position in line here: %s", num_patients_curr_clinic);

	sprintf(positionInLineThere,"There are %s patients waiting there.", suggestedClinic.numPatients);
	sprintf(addr,"%s, %s", suggestedClinic.name, suggestedClinic.addr);

	length = GraphicsStringLength(addr, 2, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,300}, YELLOW, BLUE, addr, 1, 2, 1);

	length = GraphicsStringLength(positionInLineThere, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,340}, YELLOW, BLUE, positionInLineThere, 1, 3, 1);

	length = GraphicsStringLength(messg2, 2, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,200}, WHITE, BLUE, messg2, 1, 2, 1);

	length = GraphicsStringLength(messg3, 2, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,230}, WHITE, BLUE, messg3, 1, 2, 1);

	length = GraphicsStringLength(positionInLineHere, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,150}, WHITE, BLUE, positionInLineHere, 1, 4, 1);

	free(positionInLineThere);
	free(positionInLineHere);
	free(addr);

	return 0;
}

unsigned char resetState_suggestion_screen(void){
	return 0;
}

unsigned char cleanup_suggestion_screen(void){
	return 0;
}

// stay Button
unsigned char draw_stay_Button(void){
	char c[] = "No, stay here";
	Filled_Rectangle(DECLINE_BUTTON_UL, DECLINE_BUTTON_LR, ORANGE);
	Bordered_Rectangle(DECLINE_BUTTON_UL, DECLINE_BUTTON_LR, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){DECLINE_BUTTON_UL.x + (260 - length)/2, DECLINE_BUTTON_UL.y + FONT_OFFSET_Y*41/10}, BLACK, ORANGE, c, 1, 3, 1);
	return 0;
}

unsigned char press_stay_Button(void){
	char c[] = "No, stay here";
	Filled_Rectangle(DECLINE_BUTTON_UL, DECLINE_BUTTON_LR, MAGENTA);
	Bordered_Rectangle(DECLINE_BUTTON_UL, DECLINE_BUTTON_LR, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){DECLINE_BUTTON_UL.x + (260 - length)/2, DECLINE_BUTTON_UL.y + FONT_OFFSET_Y*41/10}, WHITE, MAGENTA, c, 1, 3, 1);

	return 0;
}

unsigned char release_stay_Button(void){
	stay = STAY;
	return RELEASE_CHANGE_SCREEN_PREV;
}

unsigned char inside_stay_Button(Point press){
	return (press.x >= DECLINE_BUTTON_UL.x) && (press.x <= DECLINE_BUTTON_LR.x) && (press.y >= DECLINE_BUTTON_UL.y) && (press.y <= DECLINE_BUTTON_LR.y);
}

// leave Button
unsigned char draw_leave_Button(void){
	char c[] = "Yes, go there";
	Filled_Rectangle(ACCEPT_BUTTON_UL, ACCEPT_BUTTON_LR, LIME);
	Bordered_Rectangle(ACCEPT_BUTTON_UL, ACCEPT_BUTTON_LR, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){ACCEPT_BUTTON_UL.x + (260 - length)/2, ACCEPT_BUTTON_UL.y + FONT_OFFSET_Y*41/10}, BLACK, LIME, c, 1, 3, 1);
	return 0;
}

unsigned char press_leave_Button(void){
	char c[] = "Yes, go there";
	Filled_Rectangle(ACCEPT_BUTTON_UL, ACCEPT_BUTTON_LR, MAGENTA);
	Bordered_Rectangle(ACCEPT_BUTTON_UL, ACCEPT_BUTTON_LR, BLACK, BORDER);
	int length = GraphicsStringLength(c, 3, 1);
	OutGraphicsString((Point){ACCEPT_BUTTON_UL.x + (260 - length)/2, ACCEPT_BUTTON_UL.y + FONT_OFFSET_Y*41/10}, WHITE, MAGENTA, c, 1, 3, 1);

	return 0;
}

unsigned char release_leave_Button(void){
	stay = DONT_STAY;
	return RELEASE_CHANGE_SCREEN_PREV;
}

unsigned char inside_leave_Button(Point press){
	return (press.x >= ACCEPT_BUTTON_UL.x) && (press.x <= ACCEPT_BUTTON_LR.x) && (press.y >= ACCEPT_BUTTON_UL.y) && (press.y <= ACCEPT_BUTTON_LR.y);
}

// exit button
unsigned char draw_suggestion_Cancel_Button(void){
	char c[] = "X";
	Filled_Rectangle(CANCEL_BUTTON_UL, CANCEL_BUTTON_LR, RED);
	Bordered_Rectangle(CANCEL_BUTTON_UL, CANCEL_BUTTON_LR, BLACK, BORDER);
	OutGraphicsString((Point){CANCEL_BUTTON_UL.x + 9, CANCEL_BUTTON_UL.y + 6}, WHITE, RED, c, 1, 4, 1);
	return 0;
}

unsigned char press_suggestion_Cancel_Button(void){
	char c[] = "X";
	Filled_Rectangle(CANCEL_BUTTON_UL, CANCEL_BUTTON_LR, MAGENTA);
	Bordered_Rectangle(CANCEL_BUTTON_UL, CANCEL_BUTTON_LR, BLACK, BORDER);
	OutGraphicsString((Point){CANCEL_BUTTON_UL.x + 9, CANCEL_BUTTON_UL.y + 6}, WHITE, MAGENTA, c, 1, 4, 1);
	return 0;
}

unsigned char inside_suggestion_Cancel_Button(Point press){
	return (press.x >= CANCEL_BUTTON_UL.x + 25) && (press.x <= CANCEL_BUTTON_LR.x + 25) && (press.y >= CANCEL_BUTTON_UL.y) && (press.y <= CANCEL_BUTTON_LR.y);
}

//--------------------Generate Screen-------------------------------------------
Screen* generateSuggestionScreen(void){
	ButtonTable* bt = init_buttonTable(1);
	Button* b = new_button(draw_stay_Button, press_stay_Button, release_stay_Button, inside_stay_Button);
	insertButton(bt, b);

	b = new_button(draw_leave_Button, press_leave_Button, release_leave_Button, inside_leave_Button);
	insertButton(bt, b);

	b = new_button(draw_suggestion_Cancel_Button, press_suggestion_Cancel_Button, release_Cancel_Button, inside_suggestion_Cancel_Button);
	insertButton(bt, b);

	return createScreen(draw_suggestion_screen, resetState_suggestion_screen, cleanup_suggestion_screen, bt);
}
