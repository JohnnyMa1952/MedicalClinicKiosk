/*
 * Screen.h
 *
 *  Created on: Feb 21, 2019
 *      Author: Amir
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "../WIFI/WIFI.h"
#include "../Touch/Button.h"
#include "../Touch/ButtonTable.h"

#define OFFSET_ERROR 19

#define TAKEN 1
#define NOT_TAKEN 0

#define RUN 1
#define STOP 0

#define UPPER_CASE 1
#define LOWER_CASE 0

#define STAY 1
#define DONT_STAY 0

#define KEY_SIZE_X 65
#define KEY_SIZE_Y 70

#define FONT_OFFSET_X 17
#define FONT_OFFSET_Y 5

#define FONT_STEP 17
#define TOUCH_OFFSET 4

#define CONTROL_KEY_Y 410
#define CONTROL_KEY_X 35
#define CONTROL_KEY_HEIGHT 60

#define SPACE_BETWEEN_KEYS 3
#define BORDER 2
#define KEY_FONT 5

typedef struct {
	func1 draw; // routine to draw Screen (mostly back ground stuff, Not the buttons)
	func1 resetState; // routine to to reset the variable of the screen (like the text box becoming zero)
	func1 cleanup; // routine to clean up remaining threads of a screen when we want to change screens
	ButtonTable* buttonTable;
}Screen;

Screen* createScreen(func1 draw, func1 resetState, func1 cleanup, ButtonTable* buttonTable);
void freeScreen(Screen* screen);

typedef struct {
	Screen** array;
	size_t length; //number of items
	size_t size; //allocated size
}ScreenTable;

void insertScreen(ScreenTable* screenTable, Screen *screen);
ScreenTable* init_screenTable(int size);
void clearScreenTable(ScreenTable* screenTable);
void removeScreen(ScreenTable* screenTable, Screen *screen);

void runGUI(ScreenTable* screenTable);

// function for time thread (need to call gpa init first)
void* timeTread(void* args);

// Screen variables
char* nameTextBox;
int textBoxIndex;

char* phoneNumberBox;
int numberBoxIndex;

char* careCardNumberBox;
int careCardNumberBoxIndex;

char* heartRate;

char* num_patients_curr_clinic;
unsigned char suggestion;
unsigned char stay;

Clinic suggestedClinic;

// General Button functions
// Next Page Button Button
unsigned char draw_Next_Button(void);
unsigned char press_Next_Button(void);
unsigned char inside_Next_Button(Point press);

// Cancel sign in Button Button
unsigned char draw_Cancel_Button(void);
unsigned char press_Cancel_Button(void);
unsigned char release_Cancel_Button(void);
unsigned char inside_Cancel_Button(Point press);

// Cancel sign in Button Button
unsigned char draw_Back_Button(void);
unsigned char press_Back_Button(void);
unsigned char inside_Back_Button(Point press);


// Number keyboard buttons
unsigned char draw_0_Button(void);
unsigned char press_0_Button(void);
unsigned char inside_0_Button(Point press);

unsigned char draw_1_Button(void);
unsigned char press_1_Button(void);
unsigned char inside_1_Button(Point press);

unsigned char draw_2_Button(void);
unsigned char press_2_Button(void);
unsigned char inside_2_Button(Point press);

unsigned char draw_3_Button(void);
unsigned char press_3_Button(void);
unsigned char inside_3_Button(Point press);

unsigned char draw_4_Button(void);
unsigned char press_4_Button(void);
unsigned char inside_4_Button(Point press);

unsigned char draw_5_Button(void);
unsigned char press_5_Button(void);
unsigned char inside_5_Button(Point press);

unsigned char draw_6_Button(void);
unsigned char press_6_Button(void);
unsigned char inside_6_Button(Point press);

unsigned char draw_7_Button(void);
unsigned char press_7_Button(void);
unsigned char inside_7_Button(Point press);

unsigned char draw_8_Button(void);
unsigned char press_8_Button(void);
unsigned char inside_8_Button(Point press);

unsigned char draw_9_Button(void);
unsigned char press_9_Button(void);
unsigned char inside_9_Button(Point press);

unsigned char draw_Delete_Button(void);
unsigned char press_Delete_Button(void);
unsigned char inside_Delete_Button(Point press);

unsigned char draw_Plus_Button(void);
unsigned char press_Plus_Button(void);
unsigned char inside_Plus_Button(Point press);

#endif /* SCREEN_H_ */
