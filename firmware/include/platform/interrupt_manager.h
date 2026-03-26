

#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

#include <xc.h>

#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

void __interrupt (low_priority) INTERRUPT_InterruptManager(void) ;
void __interrupt(high_priority) INTERRUPT_HighPriorityInterrupt(void);

void INTERRUPT_Initialize (void);

#endif
