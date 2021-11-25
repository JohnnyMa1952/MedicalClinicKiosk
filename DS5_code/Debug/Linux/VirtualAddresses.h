/*
 * VirtualAddresses.h
 *
 *  Created on: Feb 21, 2019
 *      Author: Amir
 */

#ifndef VIRTUALADDRESSES_H_
#define VIRTUALADDRESSES_H_

#define HW_REGS_BASE ( 0xff200000 )
#define HW_REGS_SPAN ( 0x00200000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

// always call MapMemory before accessing addresses and always call UnmapMemmory When you're dones
int MapMemory(void);
int UnmapMemory(void);

void *virtual_base;

// DE1 IO
#define LEDS        (*(volatile unsigned int *)(virtual_base + ((0xFF200020)&(HW_REGS_MASK))))
#define PUSHBUTTONS (*(volatile unsigned int *)(virtual_base + ((0xFF200010)&(HW_REGS_MASK))))
#define HEX0_1      (*(volatile unsigned int *)(virtual_base + ((0xFF200030)&(HW_REGS_MASK))))
#define HEX2_3      (*(volatile unsigned int *)(virtual_base + ((0xFF200040)&(HW_REGS_MASK))))
#define HEX4_5      (*(volatile unsigned int *)(virtual_base + ((0xFF200050)&(HW_REGS_MASK))))


// GPS
#define GPS_ReceiverFifo						(*(volatile unsigned char *)(virtual_base + ((0xFF210210)&(HW_REGS_MASK))))
#define GPS_TransmitterFifo						(*(volatile unsigned char *)(virtual_base + ((0xFF210210)&(HW_REGS_MASK))))
#define GPS_InterruptEnableReg					(*(volatile unsigned char *)(virtual_base + ((0xFF210212)&(HW_REGS_MASK))))
#define GPS_InterruptIdentificationReg			(*(volatile unsigned char *)(virtual_base + ((0xFF210214)&(HW_REGS_MASK))))
#define GPS_FifoControlReg						(*(volatile unsigned char *)(virtual_base + ((0xFF210214)&(HW_REGS_MASK))))
#define GPS_LineControlReg						(*(volatile unsigned char *)(virtual_base + ((0xFF210216)&(HW_REGS_MASK))))
#define GPS_ModemControlReg						(*(volatile unsigned char *)(virtual_base + ((0xFF210218)&(HW_REGS_MASK))))
#define GPS_LineStatusReg						(*(volatile unsigned char *)(virtual_base + ((0xFF21021A)&(HW_REGS_MASK))))
#define GPS_ModemStatusReg						(*(volatile unsigned char *)(virtual_base + ((0xFF21021C)&(HW_REGS_MASK))))
#define GPS_ScratchReg							(*(volatile unsigned char *)(virtual_base + ((0xFF21021E)&(HW_REGS_MASK))))
#define GPS_DivisorLatchLSB						(*(volatile unsigned char *)(virtual_base + ((0xFF210210)&(HW_REGS_MASK))))
#define GPS_DivisorLatchMSB						(*(volatile unsigned char *)(virtual_base + ((0xFF210212)&(HW_REGS_MASK))))


// graphics register addresses
#define GraphicsCommandReg   			(*(volatile unsigned short int *)(virtual_base + ((0xFF210000)&(HW_REGS_MASK))))
#define GraphicsStatusReg   			(*(volatile unsigned short int *)(virtual_base + ((0xFF210000)&(HW_REGS_MASK))))
#define GraphicsX1Reg   				(*(volatile unsigned short int *)(virtual_base + ((0xFF210002)&(HW_REGS_MASK))))
#define GraphicsY1Reg   				(*(volatile unsigned short int *)(virtual_base + ((0xFF210004)&(HW_REGS_MASK))))
#define GraphicsX2Reg   				(*(volatile unsigned short int *)(virtual_base + ((0xFF210006)&(HW_REGS_MASK))))
#define GraphicsY2Reg   				(*(volatile unsigned short int *)(virtual_base + ((0xFF210008)&(HW_REGS_MASK))))
#define GraphicsColourReg   			(*(volatile unsigned short int *)(virtual_base + ((0xFF21000E)&(HW_REGS_MASK))))
#define GraphicsBackGroundColourReg   	(*(volatile unsigned short int *)(virtual_base + ((0xFF210010)&(HW_REGS_MASK))))

// TouchScreen
#define TouchScreen_ReceiverFifo				(*(volatile unsigned char *)(virtual_base + ((0xFF210230)&(HW_REGS_MASK))))
#define TouchScreen_TransmitterFifo				(*(volatile unsigned char *)(virtual_base + ((0xFF210230)&(HW_REGS_MASK))))
#define TouchScreen_InterruptEnableReg			(*(volatile unsigned char *)(virtual_base + ((0xFF210232)&(HW_REGS_MASK))))
#define TouchScreen_InterruptIdentificationReg	(*(volatile unsigned char *)(virtual_base + ((0xFF210234)&(HW_REGS_MASK))))
#define TouchScreen_FifoControlReg				(*(volatile unsigned char *)(virtual_base + ((0xFF210234)&(HW_REGS_MASK))))
#define TouchScreen_LineControlReg				(*(volatile unsigned char *)(virtual_base + ((0xFF210236)&(HW_REGS_MASK))))
#define TouchScreen_ModemControlReg				(*(volatile unsigned char *)(virtual_base + ((0xFF210238)&(HW_REGS_MASK))))
#define TouchScreen_LineStatusReg				(*(volatile unsigned char *)(virtual_base + ((0xFF21023A)&(HW_REGS_MASK))))
#define TouchScreen_ModemStatusReg				(*(volatile unsigned char *)(virtual_base + ((0xFF21023C)&(HW_REGS_MASK))))
#define TouchScreen_ScratchReg					(*(volatile unsigned char *)(virtual_base + ((0xFF21023E)&(HW_REGS_MASK))))
#define TouchScreen_DivisorLatchLSB				(*(volatile unsigned char *)(virtual_base + ((0xFF210230)&(HW_REGS_MASK))))
#define TouchScreen_DivisorLatchMSB				(*(volatile unsigned char *)(virtual_base + ((0xFF210232)&(HW_REGS_MASK))))

#endif /* VIRTUALADDRESSES_H_ */
