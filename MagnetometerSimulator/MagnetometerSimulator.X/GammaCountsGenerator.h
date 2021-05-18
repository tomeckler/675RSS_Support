/* 
 * File:   GammaCountsGenerator.h
 * Author: teckler
 *
 * Created on January 19, 2021, 3:08 PM
 */

#ifndef GAMMACOUNTSGENERATOR_H
#define	GAMMACOUNTSGENERATOR_H

#ifdef	__cplusplus
extern "C" {
#endif

void InitGammaCountsGenerator();
void triggerGammaCounts(uint8_t val);
void changeWavePeriod(uint16_t period);
uint8_t getCountGate(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GAMMACOUNTSGENERATOR_H */

