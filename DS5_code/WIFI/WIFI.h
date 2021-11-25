/*
 * WIFI.h
 *
 *  Created on: Feb 25, 2019
 *      Author: Amir
 */

#ifndef WIFI_H_
#define WIFI_H_
#include "../Linux/VirtualAddresses.h"

#define DE1_CLINIC_ID	0

#define UPDATE_DB 1
#define DONT_UPDATE_DB 0

#define SUGGEST_NEW_CLINIC 1
#define STAY_IN_THIS_CLINIC 0

#define BUFFER_SIZE	1000

typedef struct {
	char name[100];
	char id[20];
	char addr[150];
	char numPatients[20];
	char waittime[20];
} Clinic;

// return number of patients in line for the current clinic ( clinic id  = 0)
// write return value to numPatients
void getNumberOfPatientsInLine(char* numPatients, char* waitTime);

// post the given patient with the UpdateDB flag (either be UPDATE_DB or DONT_UPDATE_DB) and will return the
// suggestFlag given by the server (either be SUGGEST_NEW_CLINIC or STAY_IN_THIS_CLINIC) while adding the clinic
// field to the clinic argument
unsigned char postPatient(char* name, char* phone, char* careCard, char* heartRate, char* clinicID, int updateDB, Clinic* clinic);


// global variables
char responseBuffer[BUFFER_SIZE];


// UART Functions
void Init_WiFi(void);
char putcharWiFi(char c);
char getcharWiFi(void);
int WiFiTestForReceivedData(void);
void WiFiFlush(void);

// WiFi function
void sendMessageWiFi(char* msg);
void getMessageWiFi(void);
void sendClinicMessageWiFi(char* msg);
void getClinicMessageWiFi(void);
void clearResponseBuffer(void);

char curr_clinic_wait_time[100];

#endif /* WIFI_H_ */
