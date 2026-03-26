#ifndef ELEVATOR_CONTROL_H
#define ELEVATOR_CONTROL_H

void control_low_speed_relay_for_initialization(void);
void control_elevator_down_relay_for_initialization(void);
void close_door_for_initialization(void);
void initialize_elevator(void);

void close_door(void);
void open_door(void);
void enable_speakers(void);
void disable_speakers(void);
void enable_lighting_and_fan(void);
void disable_lighting_and_fan(void);
void disable_motor_relays(void);
void handle_system_security_error(void);

int control_elevator_up_relay(void);
int control_elevator_down_relay(void);
int control_high_speed_relay(void);
int control_low_speed_relay(void);

void display_floor_zero(void);
void display_floor_one(void);
void display_floor_two(void);
void display_floor_three(void);

#endif
