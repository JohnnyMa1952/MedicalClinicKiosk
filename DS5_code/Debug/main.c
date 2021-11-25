/*
 * main.c
 *
 *  Created on: Feb 6, 2019
 *      Author: JohnnyMa
 */
#include <stdio.h>
#include <stdlib.h>
#include "GPS/gps.h"
#include "Touch/button.h"
#include "Graphics/Fonts.h"
#include "Graphics/Graphics.h"
#include "Touch/touch_api.h"
#include "Linux/VirtualAddresses.h"


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
//	Filled_Rectangle((Point){50,50}, (Point){200,200}, WHITE);
//	return RELEASE_CHANGE_SCREEN_NEXT;
//}
//
//unsigned char inside(Point press){
//	Point ul = (Point){50,50};
//	Point lr = (Point){200,200};
//	return (press.x >= ul.x) && (press.x <= lr.x) && (press.y>=ul.y) && (press.y <= lr.y);
//}
//
//int main(void){
//	MapMemory();
//	Clear(BLACK);
//	Init_Touch();
//	Init_GPS();
//
//	Button *b = new_button(c_red, c_blue, c_white, inside);
//	ButtonTable* bt = init_buttonTable(2);
//	insertButton(bt, b);
//	drawButtonTable(bt);
//	handleTouch(bt);
//	clearbuttonTable(bt);
//
//	getTime();
//	OutGraphicsString((Point){250, 250}, WHITE, BLACK, timeString, 1, 3, 1);
//
//	UnmapMemory();
//}
