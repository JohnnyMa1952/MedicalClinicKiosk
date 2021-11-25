/*
 * VitalsScreen.c
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
#include "../biomed/biomed.h"

#define BIOMED_BUTTON_SIZE 55

unsigned char vitalsTaken;

unsigned char draw_vitals_screen(void){
	int length, offset;;

	//static text
	char vitals[] = "Check Vitals";
	char place[] = "Place sensor on right index finger";
	char ready[] = "Press Heart Button when you are ready";
	char c[50];

	//draw to screen
	Clear(BLUE);

	//draw static text
	length = GraphicsStringLength(vitals, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,0}, WHITE, BLUE, vitals, 1, 4, 1);

	length = GraphicsStringLength(place, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset + OFFSET_ERROR, 60}, WHITE, BLUE, place, 1, 3, 1);

	length = GraphicsStringLength(ready, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset + OFFSET_ERROR, 120}, WHITE, BLUE, ready, 1, 3, 1);

	drawIcon((Point){5 + OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	if(vitalsTaken == TAKEN){
			sprintf(c, "Heart Rate is %s BPM. Go to next Page.", heartRate);
			length = GraphicsStringLength(c, 3, 1);
			offset = (length <= XRES) ? (XRES-length)/2 : 0;
			OutGraphicsString((Point){offset + OFFSET_ERROR, 305}, YELLOW, BLUE, c, 1, 3, 1);
	}

	return 0;
}

unsigned char resetState_vitals_screen(void){
	vitalsTaken = NOT_TAKEN;
	return 0;
}

unsigned char cleanup_vitals_screen(void){
	return 0;
}

//--------------------------BUTTONS----------------------------------------------------
unsigned char draw_Check_Button(void){
	Filled_Rectangle((Point){XRES/2 - BIOMED_BUTTON_SIZE + OFFSET_ERROR, YRES/2 - BIOMED_BUTTON_SIZE},
			(Point){XRES/2 + BIOMED_BUTTON_SIZE + OFFSET_ERROR, YRES/2 + BIOMED_BUTTON_SIZE},
			(vitalsTaken == TAKEN) ? RED : YELLOW);
	Bordered_Rectangle((Point){XRES/2 + OFFSET_ERROR - BIOMED_BUTTON_SIZE - BORDER, YRES/2 - BIOMED_BUTTON_SIZE - BORDER},
			(Point){XRES/2 + BIOMED_BUTTON_SIZE + OFFSET_ERROR + BORDER, YRES/2 + BIOMED_BUTTON_SIZE + BORDER}, BLACK, BORDER);

	if(vitalsTaken == NOT_TAKEN)
		drawIcon((Point){XRES/2 - ICONRES/2 + + OFFSET_ERROR, YRES/2 - ICONRES/2}, BLACK, YELLOW, 1, HEART);
	else{
		char c[] = "Taken";
		OutGraphicsString((Point){XRES/2 - ICONRES*10/16 + OFFSET_ERROR, YRES/2 - ICONRES/2 + 15}, BLACK, RED, c, 1, 3, 1);
	}

	return 0;
}

unsigned char press_Check_Button(void){
	Filled_Rectangle((Point){XRES/2 - BIOMED_BUTTON_SIZE + OFFSET_ERROR, YRES/2 - BIOMED_BUTTON_SIZE},
			(Point){XRES/2 + BIOMED_BUTTON_SIZE + OFFSET_ERROR, YRES/2 + BIOMED_BUTTON_SIZE}, MAGENTA);
	Bordered_Rectangle((Point){XRES/2 + OFFSET_ERROR - BIOMED_BUTTON_SIZE - BORDER, YRES/2 - BIOMED_BUTTON_SIZE - BORDER},
			(Point){XRES/2 + BIOMED_BUTTON_SIZE + OFFSET_ERROR + BORDER, YRES/2 + BIOMED_BUTTON_SIZE + BORDER}, BLACK, BORDER);

	if(vitalsTaken == NOT_TAKEN)
		drawIcon((Point){XRES/2-ICONRES/2+ OFFSET_ERROR,YRES/2-ICONRES/2}, WHITE, MAGENTA, 1, HEART);
	else{
		char c[] = "Taken";
		OutGraphicsString((Point){XRES/2 - ICONRES*10/16 + OFFSET_ERROR, YRES/2 - ICONRES/2 + 15}, WHITE, MAGENTA, c, 1, 3, 1);
	}

	return 0;
}

unsigned char release_Check_Button(void){
	if(vitalsTaken == NOT_TAKEN){
		char c[50];
		sprintf(heartRate, "%d", getHR());
		vitalsTaken = TAKEN;
		sprintf(c, "Heart Rate is %s BPM. Go to next Page.", heartRate);
		register int length = GraphicsStringLength(c, 3, 1);
		register int offset = (length <= XRES) ? (XRES-length)/2 : 0;
		OutGraphicsString((Point){offset + OFFSET_ERROR, 305}, YELLOW, BLUE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_Check_Button(Point press){
	return (press.x >= XRES/2 - BIOMED_BUTTON_SIZE) && (press.x <= XRES/2 + BIOMED_BUTTON_SIZE)
			&& (press.y >= YRES/2 - BIOMED_BUTTON_SIZE) && (press.y <= YRES/2 + BIOMED_BUTTON_SIZE);
}


unsigned char release_vitals_Next_Button(void){
	return RELEASE_CHANGE_SCREEN_NEXT;
}

unsigned char release_vitals_Back_Button(void){
	return RELEASE_CHANGE_SCREEN_PREV;
}

//-----------Generate Screen--------------------------------------------
Screen* generateVitalsScreen(void){
	ButtonTable* bt = init_buttonTable(4);

	heartRate = malloc(sizeof(char)*20);
	vitalsTaken = NOT_TAKEN;

	Button* b = new_button(draw_Next_Button, press_Next_Button, release_vitals_Next_Button, inside_Next_Button);
	insertButton(bt, b);

	b = new_button(draw_Cancel_Button, press_Cancel_Button, release_Cancel_Button, inside_Cancel_Button);
	insertButton(bt, b);

	b = new_button(draw_Check_Button, press_Check_Button, release_Check_Button, inside_Check_Button);
	insertButton(bt, b);

	b = new_button(draw_Back_Button, press_Back_Button, release_vitals_Back_Button, inside_Back_Button);
	insertButton(bt, b);

	return createScreen(draw_vitals_screen,resetState_vitals_screen,cleanup_vitals_screen,bt);
}


