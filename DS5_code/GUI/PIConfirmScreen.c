/*
 * PIConfirmScreen.c
 *
 *  Created on: Feb 24, 2019
 *      Author: JohnnyMa
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

#define INFO_X 60
#define INFO_Y 100

#define INFO_SPACE_BETWEEN_LINES 80

unsigned char draw_confirm_screen(void){
	int length, offset;
	//static text
	char confirm[] = "Confirmation";
	char name[textBoxIndex];
	char phone[15 + numberBoxIndex];
	char careCard[19 + careCardNumberBoxIndex];

	sprintf(name,"%s", nameTextBox);
	sprintf(phone,"Phone number: %s", phoneNumberBox);
	sprintf(careCard, "Care Card number: %s", careCardNumberBox);

	//draw to screen
	Clear(BLUE);

	length = GraphicsStringLength(confirm, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,0}, WHITE, BLUE, confirm, 1, 4, 1);

	OutGraphicsString((Point){INFO_X + OFFSET_ERROR, INFO_Y}, YELLOW, BLUE, name, 1, 4, 1);
	OutGraphicsString((Point){INFO_X + OFFSET_ERROR, INFO_Y + INFO_SPACE_BETWEEN_LINES}, YELLOW, BLUE, phone, 1, 4, 1);
	OutGraphicsString((Point){INFO_X + OFFSET_ERROR, INFO_Y + INFO_SPACE_BETWEEN_LINES*2}, YELLOW, BLUE, careCard, 1, 4, 1);


	drawIcon((Point){5 + OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	return 0;
}

unsigned char resetState_confirm_screen(void){
	return 0;
}

unsigned char cleanup_confirm_screen(void){
	return 0;
}

unsigned char release_Confirm_Next_Button(void){
	if(textBoxIndex == 0 || numberBoxIndex == 0 || careCardNumberBoxIndex == 0){
		char messg1[] = "No field can be empty!";
		char messg2[] = "Please go back.";
		OutGraphicsString((Point){500 + OFFSET_ERROR, 350}, WHITE, BLUE, messg1, 1, 2, 1);
		OutGraphicsString((Point){500 + OFFSET_ERROR, 365}, WHITE, BLUE, messg2, 1, 2, 1);
		return REDRAW_THIS_ON_RELEASE;
	}
	else
		return RELEASE_CHANGE_SCREEN_NEXT;
}

unsigned char release_Confirm_Back_Button(void){
	return RELEASE_CHANGE_SCREEN_PREV;
}

//--------------------Generate Screen-------------------------------------------
Screen* generatePIConfirmScreen(void){
	ButtonTable* bt = init_buttonTable(3);

	Button* b = new_button(draw_Next_Button, press_Next_Button, release_Confirm_Next_Button, inside_Next_Button);
	insertButton(bt, b);

	b = new_button(draw_Cancel_Button, press_Cancel_Button, release_Cancel_Button, inside_Cancel_Button);
	insertButton(bt, b);

	b = new_button(draw_Back_Button, press_Back_Button, release_Confirm_Back_Button, inside_Back_Button);
	insertButton(bt, b);

	return createScreen(draw_confirm_screen, resetState_confirm_screen, cleanup_confirm_screen, bt);
}
