#ifndef INPUT_CONFIG_H
#define INPUT_CONFIG_H

#include <xc.h>

void configure_floor_button_ports(void);
void configure_rising_edge_sensor(void);
void configure_elevator_state_input(void);
void configure_level_sensor(void);
void configure_upper_limit_switch(void);
void configure_lower_limit_switch(void);
void configure_security_interrupt(void);
void configure_contactor_feedback(void);
void configure_usart_ports(void);
void configure_manual_control_inputs(void);
void configure_door_io(void);
void initialize_inputs(void);

#endif
