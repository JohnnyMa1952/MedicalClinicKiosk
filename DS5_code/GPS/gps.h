/*
 * gps.h
 *
 *  Created on: Feb 5, 2019
 *      Author: nisha
 */

#ifndef GPS_H_
#define GPS_H_

unsigned char getHour(void);
unsigned char getMinute(void);
unsigned char getSecond(void);
int getTime(void);
void Init_GPS(void);

char* timeString;

#endif /* GPS_H_ */
