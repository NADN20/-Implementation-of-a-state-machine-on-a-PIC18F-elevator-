

#include "platform/eusart1.h"

void EUSART1_Initialize(void)
{

    BAUDCON1 = 0x00;

    RCSTA1 = 0x90;

    TXSTA1 = 0x20;

     SPBRG1 = 0x19;

}

bool EUSART1_is_tx_ready(void)
{
    return (bool)(PIR1bits.TX1IF && TXSTA1bits.TXEN);
}

bool EUSART1_is_rx_ready(void)
{
    return PIR1bits.RC1IF;
}

bool EUSART1_is_tx_done(void)
{
    return TXSTA1bits.TRMT;
}

uint8_t EUSART1_Read(void)
{

    while(!PIR1bits.RC1IF)
    {
    }

    if(1 == RCSTA1bits.OERR)
    {

        RCSTA1bits.CREN = 0;
        RCSTA1bits.CREN = 1;
    }

    return RCREG1;
}

void EUSART1_Write(uint8_t txData)
{
    while(0 == PIR1bits.TX1IF)
    {
    }

    TXREG1 = txData;
}

void send_string(const char *x)
{
    while(*x)
    {
        EUSART1_Write(*x++);
    }
}
