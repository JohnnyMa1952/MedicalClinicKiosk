/*
 * gps.c
 *
 *  Created on: Feb 5, 2019
 *      Author: nisha
 */
#include "gps.h"
#include "../Linux/VirtualAddresses.h"
#include <stdlib.h>
#include <stdio.h>


/*
 * Initialize GPS Port. Call this before using GPS
 */
void Init_GPS(void){
	GPS_LineControlReg = 0x80; // init LCR bit7 to 1
	GPS_DivisorLatchLSB = 0x45; // baud rate = (50 MHz)/(9600 * 16)
	GPS_DivisorLatchMSB = 0x01;
	GPS_LineControlReg = 0x03; // no parity, 8 bit words, 1 stop
	GPS_FifoControlReg = 0x06; // set fifo bit 1 and 2 to reset fifo
	GPS_FifoControlReg = 0x00; // clear fifocontrolreg
	timeString = malloc(sizeof(char)*9);
}

int putcharGPS(int c){

	// wait for transmitter holding reg to be 1
	while((GPS_LineStatusReg&0x20) == 0);

	GPS_TransmitterFifo = c;

	return c;
}

int getcharGPS(void){

	// wait for Data Ready bit to be 1
	while((GPS_LineStatusReg&0x01) == 0);

	int ret = GPS_ReceiverFifo;

	return ret;
}

/*
 * Poll the UART to determine if any char has been received.
 * It does not wait for one or read it, just test to see
 * if one is available to read from the FIFO
 */
int GPSTestForReceivedData(void){

	if((GPS_LineStatusReg&0x01) == 1)
		return 1;

	return 0;
}

/*
 * Remove/flush the UART receiver buffer by removing any unread characters
 */
void GPSFlush(void){
	// keep reading the receiver FIFO until no more chars
	while((GPS_LineStatusReg & 0x01) == 1)
		getcharGPS();
}



/**
 * Get the real time hour in 24 format in pacific time.
 * Meant to be used for HEX. First 4 bits represents first digit. Last 4 bits represents last digit.
 * Ex) 8'b00010010 => 0x12 for 12PM
 * Input:
 * Return: 8 bit char representing the hour
 */
unsigned char getHour(void) {
	char strArray[1000] = "";

	int i = 0;

	while(i < 1000){

		// appends character to character array
		strArray[i] = getcharGPS();

		if(i > 4 && strArray[i] == '$') {
			// checks for GPGGA string
			if(strArray[0] == 'G' && strArray[1] == 'P' && strArray[2] == 'G' && strArray[3] == 'G' && strArray[4] == 'A') {
				// get hour
				register int h = ((int)strArray[6] & 0x0F)*10 + ((int)(strArray[7] & 0x0F));

				if(h >= 0x08)
					h = h - 0x08;
				else
					h = h + 0x10;
				return ((unsigned char) ((h/10) << 4) & 0xF0) | ((unsigned char) ((h%10) & 0x0F));
			}
			i = 0;
		} else {
			i++;
		}
	}

	return 0;
}

/**
 * Get the real time minutes in pacific time.
 * Meant to be used for HEX. First 4 bits represents first digit. Last 4 bits represents last digit.
 * Ex) 8'b00110010 => 0x32 for 32 mins
 * Input:
 * Return: 8 bit char representing the minutes
 */
unsigned char getMinute(void) {
	char strArray[1000] = "";

	int i = 0;

	while(i < 1000){

		// appends character to character array
		strArray[i] = getcharGPS();

		if(i > 4 && strArray[i] == '$') {
			// checks for GPGGA string
			if(strArray[0] == 'G' && strArray[1] == 'P' && strArray[2] == 'G' && strArray[3] == 'G' && strArray[4] == 'A') {
				// get hour
				char minute = ((strArray[8] << 4) & 0xF0) | (strArray[9] & 0x0F);
				return minute;
			}
			i = 0;
		} else {
			i++;
		}
	}

	return 0;
}

/**
 * Get the real time seconds in pacific time.
 * Meant to be used for HEX. First 4 bits represents first digit. Last 4 bits represents last digit.
 * Ex) 8'b01000010 => 0x42 for 42 seconds
 * Input:
 * Return: 8 bit char representing the minutes
 */
unsigned char getSecond(void) {
	char strArray[1000] = "";

	int i = 0;

	while(i < 1000){

		// appends character to character array
		strArray[i] = getcharGPS();

		if(i > 4 && strArray[i] == '$') {
			// checks for GPGGA string
			if(strArray[0] == 'G' && strArray[1] == 'P' && strArray[2] == 'G' && strArray[3] == 'G' && strArray[4] == 'A') {
				// get hour
				char second = ((strArray[10] << 4) & 0xF0) | (strArray[11] & 0x0F);
				return second;
			}
			i = 0;
		} else {
			i++;
		}
	}

	return 0;
}

/**
 * Get the real time pacific time as a char array in the format HH:MM:SS.
 * Char array of size 5 with char[0], char[2], char[3] as 8 bit values
 * meant to be used for HEX. First 4 bits represents first digit. Last 4 bits represents last digit.
 * Ex) charArray = ['0x12', ':', '0x32', ':', '0x55']
 * Input:
 * Return: pointer to char array
 */
int getTime(void) {
	char strArray[1000] = "";

	int i = 0;

	while(i < 1000){

		// appends character to character array
		strArray[i] = getcharGPS();

		if(i > 4 && strArray[i] == '$') {
			// checks for GPGGA string
			if(strArray[0] == 'G' && strArray[1] == 'P' && strArray[2] == 'G' && strArray[3] == 'G' && strArray[4] == 'A') {
				// get hour
				char hour = ((strArray[6] << 4) & 0xF0) | (strArray[7] & 0x0F);
				char minute = ((strArray[8] << 4) & 0xF0) | (strArray[9] & 0x0F);
				char second = ((strArray[10] << 4) & 0xF0) | (strArray[11] & 0x0F);

				if(hour >= 8) {
					hour = hour - 8;
				} else {
					hour = hour + 16;
				}


				sprintf(timeString, "%d%d:%d%d:%d%d", ((int) 0x0f & (hour >> 4)), ((int) 0x0f & hour),
						((int) 0x0f &(minute>>4)), ((int) 0x0f & minute), ((int)0x0f & (second>>4)),
						((int) 0x0f & second));
				return 0;
			}
			i = 0;
		} else {
			i++;
		}
	}

	return 1;
}

