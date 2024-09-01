#include "INIT_IN.h"


  
// Configure the ports for floor buttons as inputs
void configureFloorButtonPorts() {
    TRISAbits.TRISA0 = 0x01;   // etage_RC
    PORTAbits.RA0 = 0;
    TRISAbits.TRISA1 = 0x01;   // etage_1
    PORTAbits.RA1 = 0;
    TRISAbits.TRISA2 = 0x01;   // etage_2
    PORTAbits.RA2 = 0;
    TRISAbits.TRISA3 = 0x01;   // etage_3
    PORTAbits.RA3 = 0;
}

// Configure the rising edge port as an input
void configureRisingEdge() {
    TRISDbits.TRISD6 = 0x01;
    PORTDbits.RD6 = 0x00;  
}

// Configure the control elevator state port as an input
void configControlEtatAscensseur() {
    TRISCbits.RC1 = 0x01;
    PORTCbits.RC1 = 0x00;
}

// Configure the photocell port as an input
void configLevel() {
    TRISBbits.TRISB3 = 0x01; 
    PORTBbits.RB3 = 0x00;  
}

// Configure the lower limit switch port as an input
void configLowerLimitSwitch() {
    TRISBbits.TRISB4 = 0x01;
    PORTBbits.RB4 = 0x00;
}

// Configure the upper limit switch port as an input
void configUpperLimitSwitch() {
    TRISBbits.TRISB5 = 0x01;
    PORTBbits.RB5 = 0x00;
}

// Configure the security interruption ports and interrupts
// Configure the security interruption ports and interrupts
void configSecurityInterrupt() 
{
    TRISBbits.TRISB1 = 0x01; // Pin set as input for interrupt
    PORTBbits.RB1 = 0x00;   // Initialize the pin value as low
    TRISBbits.RB0 = 0x01;
    PORTBbits.RB0 = 0x00;
    
    INTCON2bits.INTEDG0 = 0x01; // Set INT0 interrupt to trigger on a falling edge.
    INTCONbits.INT0IE = 0x01;   // Enable INT0 interrupt.
    INTCONbits.INT0IF = 0x00;   // Clear INT0 interrupt flag.
    
    INTCON2bits.INTEDG1 = 0x01; // Set INT1 interrupt to trigger on a falling edge.
    INTCON3bits.INT1IE = 0x01;  // Enable INT1 interrupt.
    INTCON3bits.INT1IP = 0x01;  // Set the priority level of INT1 interrupt to high.
    INTCON3bits.INT1IF = 0x00;  // Clear INT1 interrupt flag.
    
    // Priority Levels Configuration
    RCONbits.IPEN = 0x01;      // Enable interrupt priority levels
    INTCONbits.GIEH = 0x01;    // Enable high-priority interrupts
    INTCON2bits.RBPU = 0x01;   // Enable individual pull-ups for PORTB pins


}

// Configure ports for speakers
void ConfigureKTC() {
    TRISDbits.RD7 = 0x01; // Set RD7 as an intput
    PORTDbits.RD7 = 0x00; // Set RD7 pin to low
}

void configureUSARTPorts()
{
   TRISCbits.TRISC6 = 1;
   TRISCbits.TRISC7 = 1 ;
   PORTCbits.RC6 = 0  ;
   PORTCbits.RC7 = 0  ;
}

/*/ Configure ports for I2C communication
void configureI2CPorts() {
     TRISCbits.TRISC4 = 1; // Set RC4 as an input
     PORTCbits.RC4 = 0;    // Set RC4 pin to low
     TRISCbits.TRISC3 = 1; // Set RC3 as an input
     PORTCbits.RC3 = 0;    // Set RC3 pin to low
}
  **/  
void ConfigManualCommande() {
     TRISCbits.RC0 = 0x01; // Set RC0 as an intput
     PORTCbits.RC0 = 0x00; // Set RC0 pin to low
     TRISCbits.RC2 = 0x01; // Set RC2 as an intput
     PORTCbits.RC2 = 0x00; // Set RC2 pin to low
}

void configPinsDoor() {
           
        TRISAbits.TRISA5 = 1;
        TRISAbits.TRISA4 = 1;
        PORTAbits.RA5=0;
        PORTAbits.RA4=0;
        TRISEbits.TRISE0 = 0;
        TRISEbits.TRISE1 = 0;
        PORTEbits.RE0=0;
        PORTEbits.RE1=0;

    }

void  Initialize_Input()
{
     configureUSARTPorts();
    // configureI2CPorts();
     ConfigureKTC();
     ConfigManualCommande();    
     configureFloorButtonPorts();
     configureRisingEdge();
     configControlEtatAscensseur();
     configLevel() ;
     configLowerLimitSwitch();
     configUpperLimitSwitch();
     configSecurityInterrupt();
     configPinsDoor();
}