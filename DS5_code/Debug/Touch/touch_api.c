/*
 * touch_api.c

 *
 *  Created on: Jan 31, 2019
 *      Author: JohnnyMa
 */
/*
 * IMPORTANT we use MSB in the point to see if it is a press of release
 * MUST MASK IT
 * IF RELEASE MSB = 1
 */
#include <stdio.h>
#include "touch_api.h"
#include "../Linux/VirtualAddresses.h"

#define TRUE 1
#define FALSE 0

#define WAIT_FOR_TOUCH		while((TouchScreen_LineStatusReg & 0x0001) != 0x0001);

/*
 * Basic data-transfer to touch screen using the serial wrapper
 * (same code as exercise1.3)
 */
unsigned char putcharTouchScreen(unsigned char c){
	while((TouchScreen_LineStatusReg&0x20) == 0); //wait for transmitter holding reg. to be 1
	TouchScreen_TransmitterFifo = c;
	return c;
}

unsigned char getcharTouchScreen(void){
	while((TouchScreen_LineStatusReg&0x01) == 0); //wait for Data Ready bit to be 1
	unsigned char ret = TouchScreen_ReceiverFifo;
	return ret;
}

int TouchScreenTestForReceivedData(void){ //poll to see if a char has been recieved
	return (TouchScreen_LineStatusReg & 0x01);
}

void TouchScreenFlush(void){
	//unsigned char c;
	while((TouchScreen_LineStatusReg & 0x01) == 0x01) //keep reading the receiver fifo until no more chars
		//c = getcharTouchScreen();
	return;
}


//main functions ***************************************************************************
void Init_Touch(void){
	TouchScreen_LineControlReg = 0x80; //init LCR bit7 to 1
	//set baud (freq of BR_CLK)/(9600 * 16) = 325.52 we round to 326
	TouchScreen_DivisorLatchLSB = 0x45;
	TouchScreen_DivisorLatchMSB = 0x01;
	TouchScreen_LineControlReg = 0x03; // no parity, 8 bit words, 1 stop
	TouchScreen_FifoControlReg = 0x06; //set fifo bit 1 and 2 to reset fifo
	TouchScreen_FifoControlReg = 0x00; //clear fifocontrolreg

	//send enable signal to touchscreen for it to autodetect UART/serial
	putcharTouchScreen(0x55);
	putcharTouchScreen(0x01);
	putcharTouchScreen(0x12);
	TouchScreenFlush();


	// UNCOMMENT WHEN TOUCH BOARD IS FIXED
//	//configure touch to be p=1 for all pd and pm and be p=0 for all pu
//	putcharTouchScreen(0x55);
//	putcharTouchScreen(0x04);
//	putcharTouchScreen(0x21);
//	putcharTouchScreen(0x00);
//	putcharTouchScreen(0x0C);
//	putcharTouchScreen(0x51);
//	TouchScreenFlush();
//
//	// read register to confirm value
//	putcharTouchScreen(0x55);
//	putcharTouchScreen(0x04);
//	putcharTouchScreen(0x20);
//	putcharTouchScreen(0x00);
//	putcharTouchScreen(0x0C);
//	putcharTouchScreen(0x01);
//	TouchScreenFlush();
}

int ScreenTouched(void){
	return (TouchScreen_LineStatusReg & 0x01);
}

void WaitForTouch(){
	while(!(TouchScreen_LineStatusReg & 0x01));
	return;
}

Point getPoint(void){ //helper function to get point data
	Point p1;
	
	p1.y = (int) getcharTouchScreen();  //we flipped x and y b/c some idiot connected  the cable backwards !!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	p1.y |= ((int)getcharTouchScreen() << 7); //shift to place then or
	p1.x = (int) getcharTouchScreen();
	p1.x |= ((int)getcharTouchScreen() << 7);

	p1.x = (p1.x-190)*10/46; //calibration to match screen and touch controller
	p1.y =  (p1.y-425)/7;

	return p1;
}

unsigned char handleTouch(ButtonTable* buttonTable){
	Button *b = NULL;
	Point touchPoint;
	unsigned char fromTouch = 0;
	unsigned char prev_fromTouch = 0;
	unsigned char is_press = FALSE; //press or release flag
	unsigned char release_ret = RELEASE_SAME_SCREEN;
	register int i;

	while(1){
		is_press = FALSE;
		WAIT_FOR_TOUCH

		do{
			fromTouch = getcharTouchScreen();
			is_press = (fromTouch == 0x81) || (prev_fromTouch == 0 && fromTouch == 0x80);
		}while((fromTouch != 0x81) && (fromTouch != 0x80)); //wait for pen down or pen up

		prev_fromTouch = (fromTouch == 0x80) ? 0 : fromTouch;
		touchPoint = getPoint();

		for(i=0; i < buttonTable->length; i++){
			b = buttonTable->array[i];
			if(b->inside(touchPoint)){
				if(is_press)
					b->press();
				else{
					release_ret = b->release();
					if(release_ret == REDRAW_ON_RELEASE)
						b->draw();
				}
			}
			else
				b->draw();
		}

		TouchScreenFlush();

		if(release_ret == RELEASE_CHANGE_SCREEN_NEXT && release_ret == RELEASE_CHANGE_SCREEN_PREV)
			return release_ret;
	}

	// will never get here (added for warnings)
	return 0;
}
