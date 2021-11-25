/*
 * button.h
 *
 *  Created on: Feb 5, 2019
 *      Author: JohnnyMa
 */
/*
 * IMPORTANT onClick is a void pointer so you can return it any value u want as long as it is a pointer
 * return NULL if the function is null
 */
#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdlib.h>
#include "../Graphics/Graphics.h"
#include "../Point/Point.h"

// return values for release function
#define RELEASE_SAME_SCREEN 		0
#define RELEASE_CHANGE_SCREEN_NEXT 	1
#define RELEASE_CHANGE_SCREEN_PREV 	2
#define ERROR_REALSE 				3
#define REDRAW_ON_RELEASE 			4

typedef unsigned char (*func1)(void); //function pointer
typedef unsigned char (*func2)(Point p); //like a boolean statement to see if point is within

typedef struct {
	func1 draw; // routine to draw button (used to revert back changes)
	func1 press; //on press (just change color to indicate a press being registered)
	func1 release; // on release does the actual action the button is supposed to do
	func2 inside; // if a point is inside the button
}Button;

Button* new_button(func1 draw, func1 press, func1 release, func2 inside);

#endif /* BUTTON_H_ */
