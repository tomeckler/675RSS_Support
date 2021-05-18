/* 
 * File:   Leds.c
 * Author: teckler
 *
 * Created on January 14, 2021, 7:56 AM
 */
#include <xc.h>

long _loopCnt = 0 ;

void updateLeds(void)
{
#define NUM_LEDS (8)
    static char blinkState = 2 ;
    
    if ( ++_loopCnt == 5000 )
    {
        switch(blinkState++){
        //case 0: PORTFbits.RF7 = getCountGate(); break;
        //case 1: PORTFbits.RF6 ^= 1; break;
        //case 2: PORTFbits.RF5 ^= 1; break;
        case 3: PORTFbits.RF4 ^= 1; break;
        case 4: PORTGbits.RG3 ^= 1; break;
        case 5: PORTGbits.RG2 ^= 1; break;
        case 6: PORTGbits.RG11 ^= 1; break;
        case 7: PORTGbits.RG10 ^= 1; 
                blinkState = 2 ;
                break;
        }
        _loopCnt = 0 ;
    }   
}

