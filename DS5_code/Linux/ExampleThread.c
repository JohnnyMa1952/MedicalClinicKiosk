/*
 * ExampleThread.c
 *
 *  Created on: Feb 21, 2019
 *      Author: Amir
 */

#include "VirtualAddresses.h"
#include "../GPS/gps.h"
#include "../Touch/button.h"
#include "../Graphics/Fonts.h"
#include "../Graphics/Graphics.h"
#include "../Touch/touch_api.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

//void* gps_fun(void* unused);
//void* button_fun(void* unused);
//
//int main(void)
//{
//	pthread_t gps_thread, button_thread;
//	int iret_gps, iret_button;
//	const char *unused = "unused";
//
//	MapMemory();
//
//	// Thread Creation
//	iret_gps = pthread_create( &gps_thread, NULL, gps_fun, (void*) unused);
//	if (iret_gps)
//	{
//		fprintf(stderr, "Error creating thread: %d\n", iret_gps);
//		UnmapMemory();
//		exit(EXIT_FAILURE);
//	}
//
//	iret_button = pthread_create( &button_thread, NULL, button_fun, (void*) unused);
//	if (iret_button)
//	{
//		fprintf(stderr, "Error creating thread: %d\n", iret_button);
//		UnmapMemory();
//		exit(EXIT_FAILURE);
//	}
//
//
//	pthread_join( button_thread, NULL );
//	pthread_join( gps_thread, NULL );
//
//	UnmapMemory();
//
//	exit(EXIT_FAILURE);
//	return 0;
//}
//
//void* gps_fun(void* unused){
//	Init_GPS();
//	for(int i=0; i<100;){
//		getTime();
//		OutGraphicsString((Point){250, 250}, WHITE, BLACK, timeString, 1, 3, 1);
//	}
//
//	exit(EXIT_FAILURE);
//	return 0;
//}
//
//volatile int counter = 0;
//
//unsigned char c_red(void){
//	Filled_Rectangle((Point){50,50}, (Point){200,200}, RED);
//	return RELEASE_SAME_SCREEN;
//}
//
//unsigned char c_blue(void){
//	Filled_Rectangle((Point){50,50}, (Point){200,200}, BLUE);
//	return RELEASE_SAME_SCREEN;
//}
//
//unsigned char c_white(void){
//	char count[10];
//	sprintf(count, "%d", counter++);
//	OutGraphicsString((Point){550, 150}, WHITE, BLACK, count, 1, 3, 1);
//	return REDRAW_ON_RELEASE;
//}
//
//unsigned char inside(Point press){
//	Point ul = (Point){50,50};
//	Point lr = (Point){200,200};
//	return (press.x >= ul.x) && (press.x <= lr.x) && (press.y>=ul.y) && (press.y <= lr.y);
//}
//
//void* button_fun(void* unused){
//	Clear(BLACK);
//	Init_Touch();
//
//	Button *b = new_button(c_red, c_blue, c_white, inside);
//	ButtonTable* bt = init_buttonTable(2);
//	insertButton(bt, b);
//	drawButtonTable(bt);
//	handleTouch(bt);
//	clearbuttonTable(bt);
//
//	exit(EXIT_FAILURE);
//	return 0;
//}
