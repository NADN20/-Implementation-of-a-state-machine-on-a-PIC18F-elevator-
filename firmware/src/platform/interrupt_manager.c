

#include "platform/interrupt_manager.h"
#include "platform/mcc.h"

void  INTERRUPT_Initialize (void)
{

    RCONbits.IPEN = 1;

    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    PIE1bits.SSP1IE = 1;
    IPR1bits.SSP1IP = 0;
    INTCON3bits.INT1IP = 1;

    TRISBbits.TRISB1 = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT1IF = 0;
    INTCON2bits.INTEDG1 = 1;
    INTCONbits.GIE = 1;
}

