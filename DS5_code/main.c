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
#include "GUI/Screen.h"
#include "GUI/GUI.h"
#include "biomed/biomed.h"
#include "WIFI/WIFI.h"


int main(void){
	MapMemory();
	Init_Touch();
	Init_GPS();
	Init_ipod();
	Init_WiFi();

	Screen* s = generateWelcomeScreen();
	ScreenTable* screenTable = init_screenTable(10);
	insertScreen(screenTable, s);

	s = generatePINameScreen();
	insertScreen(screenTable, s);

	s = generatePIPhoneNumberScreen();
	insertScreen(screenTable, s);

	s = generatePICarecardNumberScreen();
	insertScreen(screenTable, s);

	s = generatePIConfirmScreen();
	insertScreen(screenTable, s);

	s = generateCameraScreen();
	insertScreen(screenTable, s);

	s = generateVitalsScreen();
	insertScreen(screenTable, s);

	s = generateProcessingScreen();
	insertScreen(screenTable, s);

	s = generateDoneScreen();
	insertScreen(screenTable, s);

	s = generateSuggestionScreen();
	insertScreen(screenTable, s);

	runGUI(screenTable);

	UnmapMemory();
}
