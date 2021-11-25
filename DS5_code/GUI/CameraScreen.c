/*
 * CameraScreen.c
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

#define CAMERA_BUTTON_SIZE 55
unsigned char picTaken; //if picture is taken

unsigned char draw_camera_screen(void){
	int length, offset;

	//static text
	char careCard[] = "CARE CARD";
	char place[] = "Place your Care Card in the red square";
	char ready[] = "Press the Camera when you are ready";
	char c[] = "Picture Taken. Got to next Page";

	//draw to screen
	Clear(BLUE);

	//draw static text
	length = GraphicsStringLength(careCard, 4, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset+OFFSET_ERROR,0}, WHITE, BLUE, careCard, 1, 4, 1);

	length = GraphicsStringLength(place, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset + OFFSET_ERROR, 60}, WHITE, BLUE, place, 1, 3, 1);

	length = GraphicsStringLength(ready, 3, 1);
	offset = (length <= XRES) ? (XRES-length)/2 : 0;
	OutGraphicsString((Point){offset + OFFSET_ERROR, 120}, WHITE, BLUE, ready, 1, 3, 1);

	drawIcon((Point){5 + OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	if(picTaken == TAKEN){
		length = GraphicsStringLength(c, 3, 1);
		offset = (length <= XRES) ? (XRES-length)/2 : 0;
		OutGraphicsString((Point){offset + OFFSET_ERROR, 305}, YELLOW, BLUE, c, 1, 3, 1);
	}

	return 0;
}

unsigned char resetState_camera_screen(void){
	picTaken = NOT_TAKEN;
	return 0;
}

unsigned char cleanup_camera_screen(void){
	// TODO clean up camera thread if one exits
	return 0;
}

//--------------------------BUTTONS----------------------------------------------------
unsigned char draw_Capture_Button(void){
	Filled_Rectangle((Point){XRES/2 - CAMERA_BUTTON_SIZE + OFFSET_ERROR, YRES/2 - CAMERA_BUTTON_SIZE},
			(Point){XRES/2 + CAMERA_BUTTON_SIZE + OFFSET_ERROR, YRES/2 + CAMERA_BUTTON_SIZE},
			(picTaken == TAKEN) ? RED : YELLOW);
	Bordered_Rectangle((Point){XRES/2 + OFFSET_ERROR - CAMERA_BUTTON_SIZE - BORDER, YRES/2 - CAMERA_BUTTON_SIZE - BORDER},
			(Point){XRES/2 + CAMERA_BUTTON_SIZE + OFFSET_ERROR + BORDER, YRES/2 + CAMERA_BUTTON_SIZE + BORDER}, BLACK, BORDER);

	if(picTaken == NOT_TAKEN)
		drawIcon((Point){XRES/2 - ICONRES/2 + + OFFSET_ERROR, YRES/2 - ICONRES/2}, BLACK, YELLOW, 1, CAMERA);
	else{
		char c[] = "Taken";
		OutGraphicsString((Point){XRES/2 - ICONRES*10/16 + OFFSET_ERROR, YRES/2 - ICONRES/2 + 15}, BLACK, RED, c, 1, 3, 1);
	}

	return 0;
}

unsigned char press_Capture_Button(void){
	Filled_Rectangle((Point){XRES/2 - CAMERA_BUTTON_SIZE + OFFSET_ERROR, YRES/2 - CAMERA_BUTTON_SIZE},
			(Point){XRES/2 + CAMERA_BUTTON_SIZE + OFFSET_ERROR, YRES/2 + CAMERA_BUTTON_SIZE}, MAGENTA);
	Bordered_Rectangle((Point){XRES/2 + OFFSET_ERROR - CAMERA_BUTTON_SIZE - BORDER, YRES/2 - CAMERA_BUTTON_SIZE - BORDER},
			(Point){XRES/2 + CAMERA_BUTTON_SIZE + OFFSET_ERROR + BORDER, YRES/2 + CAMERA_BUTTON_SIZE + BORDER}, BLACK, BORDER);

	if(picTaken == NOT_TAKEN)
		drawIcon((Point){XRES/2-ICONRES/2+ OFFSET_ERROR,YRES/2-ICONRES/2}, WHITE, MAGENTA, 1, CAMERA);
	else{
		char c[] = "Taken";
		OutGraphicsString((Point){XRES/2 - ICONRES*10/16 + OFFSET_ERROR, YRES/2 - ICONRES/2 + 15}, WHITE, MAGENTA, c, 1, 3, 1);
	}

	return 0;
}

unsigned char release_Capture_Button(void){
	//TODO CALL function to take a picture (likely a thread)
	if(picTaken == NOT_TAKEN){
		picTaken = TAKEN;
		char c[] = "Picture Taken. Got to next Page";
		register int length = GraphicsStringLength(c, 3, 1);
		register int offset = (length <= XRES) ? (XRES-length)/2 : 0;
		OutGraphicsString((Point){offset + OFFSET_ERROR, 305}, YELLOW, BLUE, c, 1, 3, 1);
	}
	return REDRAW_THIS_ON_RELEASE;
}

unsigned char inside_Capture_Button(Point press){
	return (press.x >= XRES/2 - CAMERA_BUTTON_SIZE) && (press.x <= XRES/2 + CAMERA_BUTTON_SIZE)
			&& (press.y >= YRES/2 - CAMERA_BUTTON_SIZE) && (press.y <= YRES/2 + CAMERA_BUTTON_SIZE);
}

unsigned char release_Camera_Next_Button(void){
	return RELEASE_CHANGE_SCREEN_NEXT;
}

unsigned char release_Camera_Back_Button(void){
	return RELEASE_CHANGE_SCREEN_PREV;
}

//-----------Generate Screen--------------------------------------------
Screen* generateCameraScreen(void){
	picTaken = NOT_TAKEN;
	ButtonTable* bt = init_buttonTable(4);

	Button* b = new_button(draw_Capture_Button, press_Capture_Button, release_Capture_Button, inside_Capture_Button);
	insertButton(bt, b);

	b = new_button(draw_Next_Button, press_Next_Button, release_Camera_Next_Button, inside_Next_Button);
	insertButton(bt, b);

	b = new_button(draw_Cancel_Button, press_Cancel_Button, release_Cancel_Button, inside_Cancel_Button);
	insertButton(bt, b);

	b = new_button(draw_Back_Button, press_Back_Button, release_Camera_Back_Button, inside_Back_Button);
	insertButton(bt, b);

	return createScreen(draw_camera_screen, resetState_camera_screen, cleanup_camera_screen, bt);
}
