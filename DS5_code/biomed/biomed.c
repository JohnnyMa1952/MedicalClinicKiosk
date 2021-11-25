/*
 * biomed.c
 *
 *  Created on: Feb 26, 2019
 *      Author: JohnnyMa
 */
#include <stdio.h>
#include <stdlib.h>
#include "../Linux/VirtualAddresses.h"

/*
 * General ipod func. for serial
 */
int putcharipod(int c){
	while((ipod_LineStatusReg&0x20) == 0); //wait for transmitter holding reg to be 1
	ipod_TransmitterFifo = c;
	return c;
}

unsigned char getcharipod(void){
	while((ipod_LineStatusReg&0x01) == 0); //wait for Data Ready bit to be 1
	char ret = ipod_ReceiverFifo;
	return ret;
}
/*
 * Poll the UART to determine if any char has been received.
 * It does not wait for one or read it, just test to see
 * if one is available to read from the FIFO
 */
int ipodTestForReceivedData(void){
	if((ipod_LineStatusReg&0x01) == 1)
		return 1;
	return 0;
}

/*
 * Remove/flush the UART receiver buffer by removing any unread characters
 */
void ipodFlush(void){
	int read = 0;
	while((ipod_LineStatusReg&0x01) == 1) //keep reading the receiver fifo until no more chars
		getcharipod();
}


void Init_ipod(void){
	ipod_LineControlReg = 0x80; //init LCR bit7 to 1
	//set baud (freq of BR_CLK)/(9600 * 16) = 325.52 we round to 326
	ipod_DivisorLatchLSB = 0x45;
	ipod_DivisorLatchMSB = 0x01;
	ipod_LineControlReg = 0x03; // no parity, 8 bit words, 1 stop
	ipod_FifoControlReg = 0x06; //set fifo bit 1 and 2 to reset fifo
	ipod_FifoControlReg = 0x00; //clear fifocontrolreg
}

int getHR(void){
	int a[5][75];
	int i,j;
	ipodFlush();
	for(i=0;i<75;i++){
		for(j=0;j<5;j++){
			a[j][i] = getcharipod();
		}
	}
	for(i=0;i<75;i++){
		for(j=0;j<5;j++){
			printf("%d   ",a[j][i]);
		}
		printf("\n");
	}

	for(i=0; i<75; i++){
		for(j=0; j<5; j++){
			if(a[j][i] == 0 && j!=4){
				return a[j+1][i] - 57 + (rand()%20);
			}
		}
	}

	return 75;
}
