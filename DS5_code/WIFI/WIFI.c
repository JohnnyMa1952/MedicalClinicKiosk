/*
 * WIFI.c
 *
 *  Created on: Feb 25, 2019
 *      Author: Amir
 */

#include "WIFI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void getNumberOfPatientsInLine(char* numPatients, char* waitTime){
	 char command[60];
	 const char delims[] = "{\":,}";

	 sprintf(command, "getWaitlistPosition(0)\r\n");
	 sendMessageWiFi(command);
	 getClinicMessageWiFi();
	 WiFiFlush();

	 char* start = strstr(responseBuffer, "{");
	 char* token;

	 token = strtok(start, delims);
	 token = strtok(NULL, delims); //wait_list val
	 sprintf(numPatients, token);

	 token = strtok(NULL, delims);
	 token = strtok(NULL, delims); //wait_time val
	 sprintf(waitTime, token);

	 while(token != NULL){
		 token = strtok(NULL, delims);
	 }

	 clearResponseBuffer();
	 return;
}


unsigned char postPatient(char* name, char* phone, char* careCard, char* clinicID, char* heartRate, int updateDB, Clinic* clinic){
	 char putPatient[200];
	 const char delims[] = "{\":,}";
	 const char delims_addr[] = "{\":}";
	 char copy[BUFFER_SIZE];
	 register int j=0;

	 sprintf(putPatient, "putClinicPatient(%s, \"%s\", %s, %s, \"%s\")\r\n", clinicID, name, careCard, phone, (updateDB == UPDATE_DB) ? "true" : "false");
	 sendMessageWiFi(putPatient);
	 getClinicMessageWiFi();

	 for(j=0; j<BUFFER_SIZE; j++)
		 copy[j] = responseBuffer[j];

	 WiFiFlush();

	 // process response based on updateFlag and suggestionFlag
	 char* res = strstr(copy ,"\"suggestion_flag\":true");
	 if(res == NULL){
		 clearResponseBuffer();
		 return STAY_IN_THIS_CLINIC;
	 }

	 char* start = strstr(responseBuffer, "{");
	 char* token;

	 token = strtok(start, delims);
	 token = strtok(NULL, delims); // name val
	 sprintf(clinic->name, token);

	 token = strtok(NULL, delims);
	 token = strtok(NULL, delims); // waitime val
	 sprintf(clinic->waittime, token);

	 token = strtok(NULL, delims);
	 token = strtok(NULL, delims); // waitlist val
	 sprintf(clinic->numPatients, token);

	 token = strtok(NULL, delims);
	 token = strtok(NULL, delims_addr); // addr val
	 sprintf(clinic->addr, token);

	 token = strtok(NULL, delims);
	 token = strtok(NULL, delims); // id val
	 sprintf(clinic->id, token);

	 token = strtok(NULL, delims);
	 token = strtok(NULL, delims); // suggestion flag val

	 while(token != NULL){
		 token = strtok(NULL, delims);
	 }

	 clearResponseBuffer();
	 return SUGGEST_NEW_CLINIC;
}

// ***********************************
// UART FUNCTIONS
// ***********************************

/*
 * Initialize WiFi Port. Call this before using WiFi
 */
void Init_WiFi(void){
	WiFi_LineControlReg = 0x80; // init LCR bit7 to 1
	WiFi_DivisorLatchLSB = 0x1B; // baud rate = (50 MHz)/(115200 * 16) = 27 = 0x1B
	WiFi_DivisorLatchMSB = 0x01;
	WiFi_LineControlReg = 0x03; // no parity, 8 bit words, 1 stop
	WiFi_FifoControlReg = 0x06; // set fifo bit 1 and 2 to reset fifo
	WiFi_FifoControlReg = 0x00; // clear fifocontrolreg

	WiFiFlush();

	char connectToLab[40];
	sprintf(connectToLab, "connectHotspot()\r\n");
	sendMessageWiFi(connectToLab);
	WiFiFlush();

	char checkConnection[40];
	sprintf(checkConnection, "check_connection()\r\n");
	sendMessageWiFi(checkConnection);
	WiFiFlush();
	sendMessageWiFi(checkConnection);
	WiFiFlush();
}

char putcharWiFi(char c){

	// wait for transmitter holding reg to be 1
	while((WiFi_LineStatusReg&0x20) == 0);
	WiFi_TransmitterFifo = c;

	return c;
}

char getcharWiFi(void){

	// wait for Data Ready bit to be 1
	while((WiFi_LineStatusReg&0x01) == 0);
	return WiFi_ReceiverFifo;
}

/*
 * Poll the UART to determine if any char has been received.
 * It does not wait for one or read it, just test to see
 * if one is available to read from the FIFO
 */
int WiFiTestForReceivedData(void){
	return (WiFi_LineStatusReg&0x01) == 1;
}

/*
 * Remove/flush the UART receiver buffer by removing any unread characters
 */
void WiFiFlush(void){
	// keep reading the receiver FIFO until no more chars
	while((WiFi_LineStatusReg&0x01) == 1)
		getcharWiFi();
}


// ***********************************
// WIFI SEND AND RECEIVE FUNCTIONS
// ***********************************

/*
 * wifi.c
 *
 *  Created on: Feb 14, 2019
 *      Author: nisha
 */
#include "wifi.h"
#include <stdio.h>

// ***********************************
// UART FUNCTIONS
// ***********************************

/*
 * Clear response buffer
 */
void clearResponseBuffer(void) {
	register int i;
	for(i = 0; i < BUFFER_SIZE; i++) {
		responseBuffer[i] = '\0';
	}
}

/*
 * Get the response from the wifi module
 * Checks for '>' for end of the msg
 */
void getMessageWiFi(void) {

//	char receivedData[1000] = "";

	while(getcharWiFi() != '>');

//	int k;
//	for(k = 0; k < j; k++) {
//		printf("%c", receivedData[k]);
//	}
}

/*
 * Send a command to WiFi module.
 */
void sendMessageWiFi(char* msg) {

	int i;
	// send msg string to RX port of wifi module
	for(i = 0; msg[i] != '\0'; i++) {
		putcharWiFi(msg[i]);
		// wait for char to be received
		while(WiFiTestForReceivedData() != 1);
		printf("%c", getcharWiFi());
	}

	getMessageWiFi();
	//WiFiFlush(); // safe keeping
}

/*
 * Gets the response message from the wifi module
 * Checks for '}' for end of msg
 */
void getClinicMessageWiFi(void) {

	register int j = 0;
//	responseBuffer[j] = '{';
//
//	while(getcharWiFi() != '{');

	do {
		responseBuffer[j] = getcharWiFi();
		j++;
	} while(responseBuffer[j-1] != '}');

	return;
}


