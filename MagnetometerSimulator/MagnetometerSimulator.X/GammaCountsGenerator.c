//
// GammaCountsGenerator.c
// by:  Tom Eckler
// date:  19 JAN 2021
//

#include <xc.h>
#include <stdint.h>
#include "timing.h" // for system clock speeds

uint32_t    _timer2Freq     = 0 ;
uint8_t     _resetCountsB   = 0 ;
uint8_t     _countGateB     = 0 ;
uint32_t    _totalCounts    = 0 ;

uint8_t getCountGate(void)
{
    return _countGateB;
}

void triggerGammaCounts(uint8_t val)
{
    _countGateB = val;
}

void resetCounts(void)
{
   _resetCountsB = 0;
}

void InitGammaCountsGenerator()
{   
    // config ISR timer on Timer2
    T2CONbits.TON   = 0;
    T2CONbits.TCS   = 0 ; // internal clock
    T2CONbits.TCKPS = 0; // 1,8,64,256
    T2CONbits.TGATE = 0 ; // no gated accumulation
    T2CONbits.TSIDL = 0 ; // don't stop in idle mode
    T2CONbits.T32   = 0 ; // 2 16 bit counters, not single 32-bit
    TMR2            = 0;
    
    
    // 1555.2 makes 48Khz
    // This is slower by 0.2/1555.2 = 0.013% high
    // This yielded 49Khz update rate!
    // 793 counts delivers 7993.6 counts per bin (target is 8000)
    // 792 should give 7993.6 * 793/792 = 8003.7
    PR2 = (uint16_t)793;
    
    uint32_t prescale = 1;
    
    _timer2Freq = (unsigned long) ((SYSTEM_Fp+(prescale/2)) / (prescale*PR2));
    
    // Timer2 on and connected to ISR
    IPC1bits.T2IP = 7 ;
    IFS0bits.T2IF = 0 ;
    IEC0bits.T2IE = 1 ;
    T2CONbits.TON = 1 ;
}

void GateCountsGeneration(uint8_t gate)
{
    _countGateB = gate;
}

// generate counts from 0-_groupDelay to COUNTS_PERIOD-_groupDelay
void __attribute__ ( (interrupt, auto_psv) ) _T2Interrupt( void )
{
    static uint8_t onB = 0;

    IFS0bits.T2IF = 0 ;

    // Always turn off, only turn on if _countGateB = 1
    // This makes all pulses of identical width
    if ( !onB  ||  _countGateB )
    {
        PORTBbits.RB1 = onB ;
        PORTBbits.RB2 = onB ;
        PORTBbits.RB3 = onB ;
        PORTBbits.RB4 = onB ;
    }
    onB ^= 1 ;
}

