/* 
 * File:   CommonHardwareDefines.h
 * Author: boestreicher
 *
 * Created on June 19, 2018, 10:38 AM
 */

#ifndef COMMONHARDWAREDEFINES_H
#define	COMMONHARDWAREDEFINES_H


typedef enum tagSPI_INTERRUPT_TRIGGERS
{
	SPI_INTERRUPT_ON_TX_FIFO_FULL = 7,
	SPI_INTERRUPT_ON_TX_FIFO_EMPTY = 6,
	SPI_INTERRUPT_ON_TX_COMPLETE = 5,
	SPI_INTERRUPT_ON_TX_FIFO_NOT_FULL = 4,

	SPI_INTERRUPT_ON_RX_BUFFER_FULL = 3,
	SPI_INTERRUPT_ON_RX_FIFO_ALMOST_FULL = 2,
	SPI_INTERRUPT_ON_SR_EMPTY = 1,
	SPI_INTERRUPT_ON_RX_FIFO_EMPTY = 0
} SPI_INTERRUPT_TRIGGERS;


enum _enumOscModes
{
	OSC_FAST_RC = 0,
	OSC_FAST_RC_PLL = 1,
	OSC_PRIMARY = 2,
	OSC_PRIMARY_PLL = 3,
	OSC_SECONDARY = 4,
	OSC_LOW_POWER = 5,
	OSC_FAST_RC_DIV16 = 6,
	OSC_FAST_RC_DIVN = 7
};


/* Definitions *****************************************************/
#define STOP_TIMER_IN_IDLE_MODE     0x2000
#define TIMER_SOURCE_INTERNAL       0x0000
#define TIMER_SOURCE_EXTERNAL       0x0002
#define TIMER_ON                    0x8000
#define GATED_TIME_DISABLED         0x0000
#define TIMER_16BIT_MODE            0x0000

#define TIMER_PRESCALER_1           0x0000
#define TIMER_PRESCALER_8           0x0010
#define TIMER_PRESCALER_64          0x0020
#define TIMER_PRESCALER_256         0x0030



#endif	/* COMMONHARDWAREDEFINES_H */

