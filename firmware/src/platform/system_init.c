#include <xc.h>

#include "platform/system_init.h"

#include "bsp/input_config.h"
#include "bsp/output_config.h"
#include "platform/mcc.h"

static void oscillator_initialize(void) {
    OSCTUNE = 0x00;
    OSCCON = 0x72;
    OSCCON2 = 0x00;
}

void system_initialize(void) {
    oscillator_initialize();
    INTERRUPT_Initialize();
    EUSART1_Initialize();
    initialize_outputs();
    initialize_inputs();

    ANSELC = 0x00;
    ANSELA = 0x00;
    ANSELE = 0x00;
    ANSELD = 0x00;
    ANSELB = 0x00;

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
}
