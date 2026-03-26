#include "bsp/output_config.h"

void configure_lighting_and_fan_output() {
    TRISEbits.TRISE2 = 0x00;
    PORTEbits.RE2 = 0x00;
}

void configure_seven_segment_ports() {
     TRISCbits.TRISC5 = 0;
     PORTCbits.RC5 = 0;
     TRISDbits.TRISD4 = 0;
     PORTDbits.RD4 = 0;
     TRISDbits.TRISD5 = 0;
     PORTDbits.RD5 = 0;
     TRISDbits.TRISD3 = 0;
     PORTDbits.RD3 = 0;
     TRISDbits.TRISD2 = 0;
     PORTDbits.RD2 = 0;
}

void configure_elevator_relay_outputs() {
     TRISDbits.TRISD0 = 0;
     TRISDbits.TRISD1 = 0;
     TRISBbits.TRISB7 = 0;
     TRISBbits.TRISB6 = 0;
     PORTDbits.RD0 = 0;
     PORTDbits.RD1 = 0;
     PORTBbits.RB7 = 0;
     PORTBbits.RB6 = 0;
}
void initialize_outputs()
{

 configure_lighting_and_fan_output();
 configure_seven_segment_ports();
 configure_elevator_relay_outputs();
}
