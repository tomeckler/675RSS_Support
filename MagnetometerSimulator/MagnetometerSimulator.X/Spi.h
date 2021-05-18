/* 
 * File:   Spi.h
 * Author: teckler
 *
 * Created on January 14, 2021, 11:12 AM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

void configSPI(void);
void changeWavePeriod(uint16_t period);
void setGroupDelay(uint8_t delay);
void setStopAngle( int16_t toolface );

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

