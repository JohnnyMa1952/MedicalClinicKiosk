/*
 * Screen.c
 *
 *  Created on: Feb 21, 2019
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

// flag to control threads
volatile unsigned char threadsRunWelcomeScreen;
pthread_t time_thread, curr_queue_thread;

// screen functions
unsigned char draw_welcome_screen();
unsigned char resetState_welcome_screen(void);
unsigned char cleanup_welcome_screen(void);

// button functions
unsigned char inside_welcome_screen_button(Point press);
unsigned char release_welcome_screen_button();

// function to add when wi-fi is set up. (for the threads)
void* currQueueThread(void* args);

// generates a welcome screen (called from main)
Screen* generateWelcomeScreen(void){
	threadsRunWelcomeScreen = STOP;
	num_patients_curr_clinic = malloc(sizeof(char)*5);
	Button* b = new_button(dummy, dummy, release_welcome_screen_button, inside_welcome_screen_button);
	ButtonTable* bt = init_buttonTable(1);
	insertButton(bt, b);
	return createScreen(draw_welcome_screen, resetState_welcome_screen, cleanup_welcome_screen, bt);
}

// welcome screen draw function
unsigned char draw_welcome_screen(){

	int length, offset, iret_time, iret_curr_queue;

	// draw static text
	char welcome[] = "Welcome to Zion Medical Clinic";
	char press[] = "Press Anywhere to Check-in";
	length = GraphicsStringLength(welcome, 4, 1);
	offset = (length <= XRES) ? (XRES - length) / 2 : 0;
	Clear(BLUE);
	OutGraphicsString((Point){offset+ OFFSET_ERROR, 130}, WHITE, BLUE, welcome, 1, 4, 1);
	length = GraphicsStringLength(press, 3, 1);
	offset = (length <= XRES) ? (XRES - length) / 2 : 0;
	OutGraphicsString((Point){offset+ OFFSET_ERROR, 230}, YELLOW, BLUE, press, 1, 3, 1);
	drawIcon((Point){5+ OFFSET_ERROR, 0}, WHITE, BLUE, 1, APPICON);

	// setup threads for updates
	threadsRunWelcomeScreen = RUN;

	// Thread Creation
	iret_time = pthread_create( &time_thread, NULL, timeTread, (void*) &threadsRunWelcomeScreen);
	if (iret_time)
	{
		fprintf(stderr, "Error creating thread: %d\n", iret_time);
		exit(EXIT_FAILURE);
	}

	iret_curr_queue = pthread_create( &curr_queue_thread, NULL, currQueueThread, (void*) &threadsRunWelcomeScreen);
	if (iret_curr_queue)
	{
		fprintf(stderr, "Error creating thread: %d\n", iret_curr_queue);
		exit(EXIT_FAILURE);
	}

	return 0;
}

// thread to get number of patients and display them on screen
void* currQueueThread(void* args){

	char* queue = malloc(40*sizeof(char));
	int length, offset;

	//while(*((volatile unsigned char *) args) == RUN){
		getNumberOfPatientsInLine(num_patients_curr_clinic, curr_clinic_wait_time);
		sprintf(queue, "There are %s patients waiting in line.", num_patients_curr_clinic);
		length = GraphicsStringLength(queue, 3, 1);
		offset = (length <= XRES) ? (XRES - length) / 2 : 0;
		OutGraphicsString((Point){offset + OFFSET_ERROR, 330}, WHITE, BLUE, queue, 1, 3, 1);
	//}

	free(queue);
	return NULL;
}

// welcome screen reset state function (does nothing as this screen has no state)
unsigned char resetState_welcome_screen(void){
	return 0;
}


// welcome screen cleanup function (kills the threads used in this state)
unsigned char cleanup_welcome_screen(void){
	threadsRunWelcomeScreen = STOP;
	pthread_join(time_thread, NULL);
	pthread_join(curr_queue_thread, NULL);
	return 0;
}

// --------------------------Buttons---------------------------
// welcome screen has one one button which is the whole screen and when pressed moves to the next screen
unsigned char release_welcome_screen_button(){
	return RELEASE_CHANGE_SCREEN_NEXT;
}

unsigned char inside_welcome_screen_button(Point press){
	return (press.x >= 0) && (press.x <= XRES) && (press.y >= 0) && (press.y <= YRES);
}
