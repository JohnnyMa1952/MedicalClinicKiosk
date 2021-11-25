/*
 * DoneScreen.c
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

#define DONE_BUTTON_UL ((Point){335 + OFFSET_ERROR, 380})
#define DONE_BUTTON_LR ((Point){495 + OFFSET_ERROR, 460})

unsigned char draw_done_screen(void){
	int length, offset;

	char done[] = "Check-in Complete!";
	char* messg1 = malloc(sizeof(char)*100);
	char messg2[] = "You will receive a text message";
	char messg3[] = "close to your appointment.";
	char* positionInLine = malloc(sizeof(char)*50);
	char* addr = malloc(sizeof(char)*160);

	// post to DB about patient with the UpdateDB flag true
	char* name = malloc(sizeof(char)*textBoxIndex);
	char* phone = malloc(sizeof(char)*numberBoxIndex);
	char* careCard = malloc(sizeof(char)*careCardNumberBoxIndex);
	char* clinicID = malloc(sizeof(char)*5);
	unsigned char UpdateDB = UPDATE_DB;

	sprintf(name,"%s", nameTextBox);
	sprintf(phone,"%s", phoneNumberBox);
	sprintf(careCard, "%s", careCardNumberBox);
	sprintf(clinicID, "%s", (stay == STAY) ? "0" : suggestedClinic.id);

	Clear(BLUE);
	drawIcon((Point){5+ OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	postPatient(name, phone, careCard, clinicID, heartRate, UpdateDB, &suggestedClinic);

	length = GraphicsStringLength(done, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,2}, WHITE, BLUE, done, 1, 4, 1);

	if(stay == STAY){
		 getNumberOfPatientsInLine(num_patients_curr_clinic, curr_clinic_wait_time);
		 sprintf(positionInLine,"Position in line: %s", num_patients_curr_clinic);
		 sprintf(messg1,"Please take a seat while you wait.");
	}
	else{
		sprintf(positionInLine,"Position in line: %s", suggestedClinic.numPatients);
		sprintf(addr,"%s, %s", suggestedClinic.name, suggestedClinic.addr);
		sprintf(messg1,"Please head to the new location below.");

		length = GraphicsStringLength(addr, 2, 1);
		offset = (length <= XRES) ? (XRES-length)/2 : 0;
		OutGraphicsString((Point){offset+OFFSET_ERROR,300}, YELLOW, BLUE, addr, 1, 2, 1);
	}

	length = GraphicsStringLength(messg1, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,200}, WHITE, BLUE, messg1, 1, 3, 1);

	length = GraphicsStringLength(messg2, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,230}, WHITE, BLUE, messg2, 1, 3, 1);

	length = GraphicsStringLength(messg3, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,260}, WHITE, BLUE, messg3, 1, 3, 1);

	length = GraphicsStringLength(positionInLine, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,150}, WHITE, BLUE, positionInLine, 1, 4, 1);

	free(name);
	free(phone);
	free(careCard);
	free(clinicID);
	free(positionInLine);
	free(addr);
	free(messg1);

	return 0;
}

unsigned char resetState_done_screen(void){
	return 0;
}

unsigned char cleanup_done_screen(void){
	return 0;
}

// done Button
unsigned char draw_done_Button(void){
	char c[] = "Done";
	Filled_Rectangle(DONE_BUTTON_UL, DONE_BUTTON_LR, LIME);
	Bordered_Rectangle(DONE_BUTTON_UL, DONE_BUTTON_LR, BLACK, BORDER);
	int length = GraphicsStringLength(c, 4, 1);
	OutGraphicsString((Point){DONE_BUTTON_UL.x + (140 - length)/2, DONE_BUTTON_UL.y + FONT_OFFSET_Y*34/10}, BLACK, LIME, c, 1, 4, 1);

	return 0;
}

unsigned char press_done_Button(void){
	char c[] = "Done";
	Filled_Rectangle(DONE_BUTTON_UL, DONE_BUTTON_LR, MAGENTA);
	Bordered_Rectangle(DONE_BUTTON_UL, DONE_BUTTON_LR, BLACK, BORDER);
	int length = GraphicsStringLength(c, 4, 1);
	OutGraphicsString((Point){DONE_BUTTON_UL.x + (140 - length)/2, DONE_BUTTON_UL.y + FONT_OFFSET_Y*34/10}, WHITE, MAGENTA, c, 1, 4, 1);

	return 0;
}

unsigned char release_done_Button(void){
	return RESET_GUI_STATE;
}

unsigned char inside_done_Button(Point press){
	return (press.x >= DONE_BUTTON_UL.x) && (press.x <= DONE_BUTTON_LR.x) && (press.y >= DONE_BUTTON_UL.y) && (press.y <= DONE_BUTTON_LR.y);
}


//--------------------Generate Screen-------------------------------------------
Screen* generateDoneScreen(void){
	ButtonTable* bt = init_buttonTable(1);
	Button* b = new_button(draw_done_Button, press_done_Button, release_done_Button, inside_done_Button);
	insertButton(bt, b);

	return createScreen(draw_done_screen, resetState_done_screen, cleanup_done_screen, bt);
}
