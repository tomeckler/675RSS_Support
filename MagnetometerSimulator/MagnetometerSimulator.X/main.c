/* 
 * File:   main.c
 * Author: teckler
 *
 * Created on January 13, 2021, 1:31 PM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "BoardStartup.h"
#include "Leds.h"
#include "timing.h"
#include "Spi.h"
#include "GammaCountsGenerator.h"

// NOTE: CONVERTED FROM Brad O. code in 50435 project
//       this board has no crystal, so is changed to
//       use internal high speed RC
// DSPIC33EP512GM710 Configuration Bit Settings

// 'C' source line config statements

//
//	APPLICATION : Must match Bootloader
//

// FICD
//#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
//#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
//#pragma config BOREN = ON               //  (BOR is enabled)
//#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
//#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
//#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
//	The watchdog timeout period is set to one second
//#pragma config WDTPOST = PS1024         // Watchdog Timer Postscaler bits (1:1024)
//#pragma config WDTPRE = PR32            // Watchdog Timer Prescaler bit (1:32)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
//#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

// FOSC
//#pragma config POSCMD = EC              // Primary Oscillator Mode Select bits (EC (External Clock) Mode)
#pragma config OSCIOFNC = OFF             // OSC2 Pin Function is clock out
//#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
//#pragma config FCKSM = CSECME           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are enabled)

// FOSCSEL
#pragma config FNOSC = FRCPLL             // FastRC (soon to be FastRC + PLL)
//#pragma config PWMLOCK = OFF            // PWM Lock Enable bit (Certain PWM registers may only be written after key sequence)
//#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FGS
//#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
//#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

int16_t _newPeriod     = 0 ;
int16_t _newGroupDelay = 0 ;
int16_t _stallAtToolface = -1;  // values 0..359 mean stall at those angles; 360+ means free-run at selected period

/*
 * 
 */
int main(int argc, char** argv) 
{     
    initBoard();
    configSPI();
    configPll();
    InitGammaCountsGenerator();
    
    while(1)
    {
        updateLeds();
        
        // hand-crank vars to trigger these changes
        if ( _newPeriod ) { changeWavePeriod( _newPeriod ); _newPeriod=0; }
        if ( _newGroupDelay > -1 ) { setGroupDelay( _newGroupDelay ); _newGroupDelay = -1 ; }
        if ( _stallAtToolface > -1 ) { setStopAngle( _stallAtToolface ); _stallAtToolface = -1 ; }
    }
    return (EXIT_SUCCESS);
}

