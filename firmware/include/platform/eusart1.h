#ifndef EUSART1_H
#define EUSART1_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <xc.h>

#define EUSART1_DataReady (EUSART1_is_rx_ready())

void EUSART1_Initialize(void);
bool EUSART1_is_tx_ready(void);
bool EUSART1_is_rx_ready(void);
bool EUSART1_is_tx_done(void);
uint8_t EUSART1_Read(void);
void EUSART1_Write(uint8_t txData);
void send_string(const char *text);

#endif
