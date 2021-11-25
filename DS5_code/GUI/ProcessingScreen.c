/*
 * ProcessingScreen.c
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
#include "../WIFI/WIFI.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define PROC_SPACE_BETWEEN_LINES 80

unsigned char draw_processing_screen(void){
	int length, offset;
	//static text
	char confirm[] = "Processing...";
	char messg1[] = "You are being registered";
	char messg2[] = "Thank you for your patience";
	char done[] = "Done!";
	char messg3[] = "Press next for the wait time information.";

	//draw to screen
	Clear(BLUE);

	length = GraphicsStringLength(confirm, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,2}, WHITE, BLUE, confirm, 1, 4, 1);

	length = GraphicsStringLength(messg1, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR, PROC_SPACE_BETWEEN_LINES}, WHITE, BLUE, messg1, 1, 3, 1);

	length = GraphicsStringLength(messg2, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR, PROC_SPACE_BETWEEN_LINES*2}, WHITE, BLUE, messg2, 1, 3, 1);

	drawIcon((Point){5 + OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	// post to DB about patient with the UpdateDB flag false

	char* name = malloc(sizeof(char)*textBoxIndex);
	char* phone = malloc(sizeof(char)*numberBoxIndex);
	char* careCard = malloc(sizeof(char)*careCardNumberBoxIndex);
	char* clinicID = malloc(sizeof(char)*5);
	unsigned char UpdateDB = DONT_UPDATE_DB;

	sprintf(name,"%s", nameTextBox);
	sprintf(phone,"%s", phoneNumberBox);
	sprintf(careCard, "%s", careCardNumberBox);
	sprintf(clinicID, "%d", DE1_CLINIC_ID);

	suggestion = postPatient(name, phone, careCard, clinicID, heartRate, UpdateDB, &suggestedClinic);

	Clear(BLUE);

	length = GraphicsStringLength(done, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,2}, WHITE, BLUE, done, 1, 4, 1);

	length = GraphicsStringLength(messg3, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR, PROC_SPACE_BETWEEN_LINES*3}, YELLOW, BLUE, messg3, 1, 3, 1);
	drawIcon((Point){5 + OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	free(name);
	free(phone);
	free(careCard);
	free(clinicID);

	return 0;
}

unsigned char resetState_processing_screen(void){
	return 0;
}

unsigned char cleanup_processing_screen(void){
	return 0;
}

// Continue Button
unsigned char release_processing_Next_Button(void){
	if(suggestion == SUGGEST_NEW_CLINIC){
		stay = DONT_STAY;
		return RELEASE_CHANGE_SCREEN_TWO_NEXT;
	}
	else{
		stay = STAY;
		return RELEASE_CHANGE_SCREEN_NEXT;
	}
}


//--------------------Generate Screen-------------------------------------------
Screen* generateProcessingScreen(void){
	ButtonTable* bt = init_buttonTable(1);
	Button* b = new_button(draw_Next_Button, press_Next_Button, release_processing_Next_Button, inside_Next_Button);
	insertButton(bt, b);

	return createScreen(draw_processing_screen, resetState_processing_screen, cleanup_processing_screen, bt);
}
