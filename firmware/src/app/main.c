#include <xc.h>

#include "app/elevator_control.h"
#include "app/elevator_state_machine.h"
#include "platform/mcc.h"
#include "platform/system_init.h"

int main(void) {
    system_initialize();

    __delay_ms(500);

    initialize_elevator();
    elevator_state_machine_initialize();

    while (1) {
        elevator_state_machine_step();
    }
}
