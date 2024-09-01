#include "INIT_OUT.h"


void ConfigLightingAndFun() {
    TRISEbits.RE2 = 0x00; // Set RE2 as an output
    PORTEbits.RE2 = 0x00; // Set RE2 pin to low
}


// Configure ports for seven-segment display
void configureSevenSegmentPorts() {
     TRISCbits.TRISC5 = 0; // Set RC5 as an output
     PORTCbits.RC5 = 0;    // Set RC5 pin to low
     TRISDbits.TRISD4 = 0; // Set RD4 as an output
     PORTDbits.RD4 = 0;    // Set RD4 pin to low
     TRISDbits.TRISD5 = 0; // Set RD5 as an output
     PORTDbits.RD5 = 0;    // Set RD5 pin to low
     TRISDbits.TRISD3 = 0; // Set RD3 as an output
     PORTDbits.RD3 = 0;    // Set RD3 pin to low
     TRISDbits.TRISD2 = 0; // Set RD2 as an output
     PORTDbits.RD2 = 0;    // Set RD2 pin to low 
}


void configureControlElevatorRelay() {
     TRISDbits.TRISD0 = 0; // Set RD0 as an output
     TRISDbits.TRISD1 = 0; // Set RD1 as an output
     TRISBbits.TRISB7 = 0; // Set RB7 as an output
     TRISBbits.TRISB6 = 0; // Set RB6 as an output
     PORTDbits.RD0 = 0;    // Set RD0 pin to low
     PORTDbits.RD1 = 0;    // Set RD1 pin to low
     PORTBbits.RB7 = 0;    // Set RB7 pin to low
     PORTBbits.RB6 = 0;    // Set RB6 pin to low
}
void Initialize_Output()
{
     
 ConfigLightingAndFun();
 configureSevenSegmentPorts();
 configureControlElevatorRelay();   
}
