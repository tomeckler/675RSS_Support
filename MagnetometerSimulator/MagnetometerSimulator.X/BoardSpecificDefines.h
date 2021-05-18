/* 
 * File:   BoardSpecificDefines.h
 * Author: boestreicher
 *
 * Created on June 19, 2018, 10:39 AM
 */

#ifndef BOARDSPECIFICDEFINES_H
#define	BOARDSPECIFICDEFINES_H

#include "CommonHardwareDefines.h"

//
//	Define all the interrupt priorities here.
//	Note that the default priority is 4
//

//
//	This is the one millisecond background timer
//
#define TIMER_INTERRUPT_PRIORITY (3)

//
//	This is the Flash memory
//	This MUST be among the highest priority in order 
//	to avoid buffer overflow errors
//
#define SPI1_INTERRUPT_PRIORITY		(6)

//
//	This is the Magnetometer and Accel
//
#define SPI2_INTERRUPT_PRIORITY (5)

//
//	SPI3 is not currently used
//
#define SPI3_INTERRUPT_PRIORITY		(2)
#define UART1_INTERRUPT_PRIORITY    (3)
#define UART2_INTERRUPT_PRIORITY    (3)
#define UART3_INTERRUPT_PRIORITY    (3)
#define UART4_INTERRUPT_PRIORITY    (3)
#define CAN_RCV_INTERRUPT_PRIORITY	(5)
#define CAN_EVENT_INTERRUPT_PRIORITY	(5)


extern volatile uint16_t DummyLed;

#if defined(__33EP512GM710_H)
#include "BoardSpecificRssAziGamma.h"
#elif defined(__33EP512GM706_H)
#include "BoardSpecificUTrans.h"
#endif

#endif	/* BOARDSPECIFICDEFINES_H */

