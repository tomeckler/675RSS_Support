/* 
 * File:   timing.c
 * Author: teckler
 *
 * Created on January 19, 2021, 3:20 PM
 * 
 * Purpose:  Configure the dsPIC33EP512GM710 chip's base frequency & 
 *           PLL frequency.  Derive timing parameters from this
 */

/*
 * 
 */

#include <xc.h>

double SYSTEM_Fp ;
double SYSTEM_Fosc ;

//
// CLOCK OUTPUT
// ROSEL = Fosc
// RODIV<3:0> = 0 
//

void configOscOut(void)
{
    // full osc freq out (no division))
    REFOCONbits.RODIV = 0;
}

void configPll(void)
{
    // PLL PARAMETERS
    // CLKDIV<4:0> = PLLPRE<4:0> 00000 N1 = 2
    // CLKDIV<7:6> = PLLPOST<1:0> 11  N2 = 2x(3+1) = 8
    // PLLFBD<8:0> = PLLDIV<8:0> 000110000  M=48+2=50
    //
    // N1 = 2 (PLLPRE + 2)
    // N2 = 2X(PLLPOST+1) = 8
    //
    // Fvco = Fin ( M / N1 ) = Fin x ( 75 / 2 ) = 8Mhz * 37.5 = 300Mhz (required >= 120Mhz, <= 340Mhz)
    // 
    // Fpllo = 7.3728Mhz * M / ( N1 x N2 ) 
    //       = 7.3738Mhz * 81 / ( 2 * 2 ) = 149.31945Mhz
    //       
    // GOAL:  150Mhz.  This requires 150/149.31945 = 1.0046 (+0.47%)
    //                 This is nearly exactly what one OSCTUn count 
    //                 delivers
    // Select Internal FRC at POR
    // 
    // SCOPE:  7.3728Mhz nominal measrued as 7.3746Mhz
    // TARGET:  7.3728Mhz+0.047% = 
    //
    //_FOSCSEL (FNOSC_FRC & IESO_OFF);
    
    // Enable Clock Switching and Configure Primary Oscillator in  XT mode
    // does this even apply here?
    //_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
    
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD=79;              // M=81
    CLKDIVbits.PLLPOST=0;   // N2 = 2
    CLKDIVbits.PLLPRE=0;    // N1 = 2
    
    /*******************************/
    /* NOTE:  OSCTUN HAS NO EFFECT */
    /*******************************/
   
    // Center frequency = 7.3728Mhz
    // tweak this 0.47% (about 10 counts) higher to achieve 150Mhz
    OSCTUN = 31;
    
    __builtin_write_OSCCONH(0x01); 
    
    // Wait for clock switch to occur
    while(OSCCONbits.COSC!=0b001);
    
    // Wait for PLL to lock
    while(OSCCONbits.LOCK != 1 );
    
    SYSTEM_Fosc = (81.0*7372800.0/4.0);
    SYSTEM_Fp = SYSTEM_Fosc / 2.0;
}
