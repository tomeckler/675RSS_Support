// spi.c - routines to handle spi commands from AziGammaToolface board
#include <xc.h>
#include <math.h>
#include <stdlib.h> // for rand())
#include "timing.h"
#include "GammaCountsGenerator.h"

#define     COUNTING_PERIOD (167)

// update @ 60RPM
#define DEFAULT_PERIOD (1000.0) /* 60RPM */
#define PI  (3.14159265359)

const float _amplitude = 9182.5;
float _angle = 0.0;
float _angleOffset = 0.0;
float _angleStep = (2.0*PI/DEFAULT_PERIOD);

uint16_t _groupDelay = 0 ;
uint16_t _step = 0;
uint16_t _period = DEFAULT_PERIOD;
int16_t _outval=0;
uint16_t _inVal;
uint16_t _interruptCount = 0 ;
int16_t _stopAngle = 360;   // free-run @ selected RPM
uint16_t _stallX, _stallY ;

void configSPI(void)
{
    SPI1CON1bits.SSEN   = 1; // use SS for this port
    SPI1CON1bits.MODE16 = 1 ;
    SPI1CON1bits.MSTEN  = 0 ;
    SPI1CON1bits.SMP    = 0 ; // MUST BE CLEARED IN SLAVE MODE
    SPI1CON1bits.CKE    = 0 ;
    SPI1CON1bits.CKP    = 1 ;
    
    // interrupt when data is in RCVBUF
    SPI1STATbits.SPIEN   = 0;
    SPI1STATbits.SPISIDL = 0;
    SPI1STATbits.SISEL   = 1;
    SPI1STATbits.SPIEN   = 1;
    
    IEC0bits.SPI1IE  = 0;		// Disable the interrupt
	IFS0bits.SPI1IF  = 0;
    IPC2bits.SPI1EIP = 5;
	IPC2bits.SPI1IP  = 5;
    IEC0bits.SPI1IE  = 1;		// eisable the interrupt
 }

void changeWavePeriod(uint16_t period)
{
    _angleStep = (2.0*PI/period);
    _period = period;
    _angleOffset = (-_angleStep*_groupDelay);
}

void setGroupDelay(uint8_t delay)
{
   _groupDelay = delay;
   _angleOffset = (-_angleStep*delay);
}

void setStopAngle( int16_t toolface )
{
    float _stallAngle;
    
    _stopAngle = toolface;
    if ( ( _stopAngle < 360 ) && ( _stopAngle >= 0 ) )
    {
        _stallAngle = ( _stopAngle * PI / 180.0 );
        _stallX = (uint16_t)(32768+_amplitude*cos(_stallAngle)); 
        _stallY= (uint16_t)(32768+_amplitude*-sin(_stallAngle));         
    }
    else
    {
        _stopAngle = 360;
    }
}

uint32_t _SPI1OvflCnt = 0 ;
uint32_t _desyncCounter = 0 ;

void __attribute__ ( (interrupt, auto_psv) ) _SPI1Interrupt( void )
{
    IFS0bits.SPI1IF = 0;
    PORTFbits.RF6 = 1 ;
    
    _inVal = SPI1BUF;
    if ( SPI1STATbits.SPIROV ) 
    {
        SPI1STATbits.SPIROV = 0 ;
        _SPI1OvflCnt++;
    }
    if ( _inVal == 0x8000 )
    {             
        if ( _stopAngle < 360 ) 
        {
            _outval = _stallX;
        }
        else
        {
            _outval = (uint16_t)(32768+_amplitude*cos(_angle));            
        }
     }
    else if ( _inVal == 0xC000 )
    {
        // do this here so can avoid varying time to calc sin(angle))
         // zero-cross output
        if (_interruptCount == 0 )
        {
            PORTDbits.RD8 = 1 ;
            // led trace
            PORTFbits.RF5 = 1 ;
        }
        else
        {
            PORTDbits.RD8 = 0 ;
            // led trace
            PORTFbits.RF5 = 0 ;
        }
        if ( _stopAngle < 360 ) 
        {
            _outval = _stallY;
        }
        else
        {        
            _outval = (uint16_t)(32768+_amplitude*-sin(_angle));
        }
        _angle += _angleStep;
        if ( ++_step >= _period )
        {
            // bias by 0.005 degrees - removed now that AziGammaToolFace performs ToolFace interpolation
            // NOTE:  Until "ReSampler"" code is fully debugged, keep timing advancement to make sure our
            //        counts with old method match the new.
            _angle = _angleOffset ;//+ (0.0005*PI/180.0) ; //+ (float)((rand()-(float)RAND_MAX/2)/(1000.0*(float)RAND_MAX));
            _step = 0;
        }
 
       // Gate counts timer on for the first
       if ( _interruptCount < COUNTING_PERIOD )
       {
           triggerGammaCounts(1);
           PORTFbits.RF7 = 1 ;
       }
       else
       {
           triggerGammaCounts(0);
           PORTFbits.RF7 = 0 ;
       }
       if ( ++_interruptCount >= _period) _interruptCount = 0 ;
    }
    else
    {
        // read SPI buf again to clear out garbage; we are out of sync
        _desyncCounter++;
        _inVal = SPI1BUF;
    }
    SPI1BUF = _outval;
    PORTFbits.RF6 = 0 ;
}

