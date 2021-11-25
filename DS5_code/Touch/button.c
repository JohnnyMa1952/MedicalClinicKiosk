/*
 * button.c
 *
 *  Created on: Feb 5, 2019
 *      Author: JohnnyMa
 */
#include "button.h"

Button* new_button(func1 draw, func1 press, func1 release, func2 inside){
	Button *ret = (Button*)malloc(sizeof(Button));
	ret->draw = draw;
	ret->press = press;
	ret->release = release;
	ret->inside = inside;
	return ret;
}

unsigned char dummy(){
	return RELEASE_SAME_SCREEN;
}

// TEMPLATES - C doesn't support functions as return values
////determine if touch is in the rectangle
////parameters: point pressed, upper left and lower right points
////returns true if clicked in rectangle false else
//func2 in_rectangle_fun(Point ul, Point lr){
//
//	unsigned char fun(Point press) {
//		return (press.x >= ul.x) && (press.x <= lr.x) && (press.y>=ul.y) && (press.y <= lr.y);
//	};
//
//	return fun;
//}
//
////determine if you clicked in rectangle
////parameters: point pressed and circle center and circle radius
//func2 in_circle_fun(Point centre, int radius){
//
//	unsigned char fun(Point press){
//		press.y = press.y-centre.y;
//		press.x = press.x-centre.x;
//		return ((press.y*press.y) + (press.x*press.x)) <= (radius*radius);
//	}
//
//	return fun;
//}
