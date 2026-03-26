#include "bsp/input_config.h"

void configure_floor_button_ports() {
    TRISAbits.TRISA0 = 0x01;
    PORTAbits.RA0 = 0;
    TRISAbits.TRISA1 = 0x01;
    PORTAbits.RA1 = 0;
    TRISAbits.TRISA2 = 0x01;
    PORTAbits.RA2 = 0;
    TRISAbits.TRISA3 = 0x01;
    PORTAbits.RA3 = 0;
}

void configure_rising_edge_sensor() {
    TRISDbits.TRISD6 = 0x01;
    PORTDbits.RD6 = 0x00;
}

void configure_elevator_state_input() {
    TRISCbits.TRISC1 = 0x01;
    PORTCbits.RC1 = 0x00;
}

void configure_level_sensor() {
    TRISBbits.TRISB3 = 0x01;
    PORTBbits.RB3 = 0x00;
}

void configure_lower_limit_switch() {
    TRISBbits.TRISB4 = 0x01;
    PORTBbits.RB4 = 0x00;
}

void configure_upper_limit_switch() {
    TRISBbits.TRISB5 = 0x01;
    PORTBbits.RB5 = 0x00;
}

void configure_security_interrupt()
{
    TRISBbits.TRISB1 = 0x01;
    PORTBbits.RB1 = 0x00;
    TRISBbits.TRISB0 = 0x01;
    PORTBbits.RB0 = 0x00;

    INTCON2bits.INTEDG0 = 0x01;
    INTCONbits.INT0IE = 0x01;
    INTCONbits.INT0IF = 0x00;

    INTCON2bits.INTEDG1 = 0x01;
    INTCON3bits.INT1IE = 0x01;
    INTCON3bits.INT1IP = 0x01;
    INTCON3bits.INT1IF = 0x00;

    RCONbits.IPEN = 0x01;
    INTCONbits.GIEH = 0x01;
    INTCON2bits.RBPU = 0x01;

}

void configure_contactor_feedback() {
    TRISDbits.TRISD7 = 0x01;
    PORTDbits.RD7 = 0x00;
}

void configure_usart_ports()
{
   TRISCbits.TRISC6 = 1;
   TRISCbits.TRISC7 = 1 ;
   PORTCbits.RC6 = 0  ;
   PORTCbits.RC7 = 0  ;
}

void configure_manual_control_inputs() {
     TRISCbits.TRISC0 = 0x01;
     PORTCbits.RC0 = 0x00;
     TRISCbits.TRISC2 = 0x01;
     PORTCbits.RC2 = 0x00;
}

void configure_door_io() {

        TRISAbits.TRISA5 = 1;
        TRISAbits.TRISA4 = 1;
        PORTAbits.RA5=0;
        PORTAbits.RA4=0;
        TRISEbits.TRISE0 = 0;
        TRISEbits.TRISE1 = 0;
        PORTEbits.RE0=0;
        PORTEbits.RE1=0;

    }

void  initialize_inputs()
{
     configure_usart_ports();

     configure_contactor_feedback();
     configure_manual_control_inputs();
     configure_floor_button_ports();
     configure_rising_edge_sensor();
     configure_elevator_state_input();
     configure_level_sensor() ;
     configure_lower_limit_switch();
     configure_upper_limit_switch();
     configure_security_interrupt();
     configure_door_io();
}
