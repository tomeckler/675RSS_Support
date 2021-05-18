/* 
 * File:   timing.h
 * Author: teckler
 *
 * Created on January 19, 2021, 3:20 PM
 */

#ifndef TIMING_H
#define	TIMING_H

#ifdef	__cplusplus
extern "C" {
#endif

extern double SYSTEM_Fp ;
extern double SYSTEM_Fosc ;

void configPll(void);
void triggerGammaCounts(uint8_t val);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMING_H */

