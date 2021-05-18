// BoardStartup.c
// by:  Tom Eckler
// date:  14 JAN 2021
// Purpose:  config dsPIC33 to startup clocks, IOs, peripherals

// D10 = P92 = RF7
// D9  = P91 = RF6
// D8  = P61 = RF5
// D7  = P60 = RF4
// D6  = P59 = RG3
// D5  = P58 = RG2
// D4  = P38 = RG11
// D3  = P17 = RG10

#include <xc.h>
#include "CommonHardwareDefines.h"

void initBoard(void)
{
    // CLOCK & PLL
    
    // IOs used
    ANSELA = 0 ;
    ANSELB = 0 ;
    ANSELC = 0 ;
    ANSELD = 0 ;
    ANSELE = 0 ;
    ANSELF = 0 ;
    ANSELG = 0 ;
    TRISG = 0 ;
    TRISF = 0 ;
    PORTG = 0 ;
    PORTF = 0 ;
    TRISB = 1 ; // need PORTB.0 for SS input
    
    //PORTFbits.RF7 ^= 1; 
    //PORTFbits.RF6 ^= 1;
    //PORTFbits.RF5 ^= 1; 
};
