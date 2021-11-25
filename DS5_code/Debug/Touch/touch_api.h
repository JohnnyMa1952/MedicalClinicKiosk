/*
 * touch_api.h
 *
 *  Created on: Jan 31, 2019
 *      Author: JohnnyMa
 */

#ifndef TOUCH_API_H_
#define TOUCH_API_H_

#include <stdio.h>
#include "buttonTable.h"

void Init_Touch(void); //initialize touch screen
int ScreenTouched(void); //check if screen is touched

unsigned char handleTouch(ButtonTable* buttonTable);

#endif /* TOUCH_API_H_ */
