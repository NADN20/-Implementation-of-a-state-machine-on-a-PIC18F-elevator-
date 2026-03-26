#include <stdbool.h>
#include <xc.h>

#include "app/elevator_control.h"
#include "platform/eusart1.h"

#define _XTAL_FREQ 16000000
#define RELAY_COMMAND_TIMEOUT_MS 1000U
#define RELAY_POLL_INTERVAL_MS 10U
#define INITIALIZATION_TIMEOUT_MS 10000U
#define INITIALIZATION_POLL_INTERVAL_MS 50U

static bool check_contactor_status(void)
{
    return PORTDbits.RD7;
}

static bool check_elevator_up_feedback(void)
{
    return PORTBbits.RB5;
}

static bool check_elevator_down_feedback(void)
{
    return PORTBbits.RB4;
}

static bool wait_for_contactor_ready(unsigned int timeout_ms)
{
    unsigned int elapsed_ms = 0;

    while (elapsed_ms < timeout_ms) {
        if (check_contactor_status()) {
            return true;
        }

        __delay_ms(RELAY_POLL_INTERVAL_MS);
        elapsed_ms += RELAY_POLL_INTERVAL_MS;
    }

    return false;
}

static int validate_relay_command(void)
{
    if (!wait_for_contactor_ready(RELAY_COMMAND_TIMEOUT_MS)) {
        handle_system_security_error();
        return 0;
    }

    if (check_elevator_up_feedback() || check_elevator_down_feedback()) {
        handle_system_security_error();
        return 0;
    }

    return 1;
}

static int set_direction_relay(unsigned char up_enabled, unsigned char down_enabled)
{
    if (!validate_relay_command()) {
        return 0;
    }

    LATDbits.LATD0 = up_enabled;
    LATDbits.LATD1 = down_enabled;

    return 1;
}

static int set_speed_relay(unsigned char high_speed_enabled, unsigned char low_speed_enabled)
{
    if (!validate_relay_command()) {
        return 0;
    }

    LATBbits.LATB7 = high_speed_enabled;
    LATBbits.LATB6 = low_speed_enabled;

    return 1;
}

void control_low_speed_relay_for_initialization(void)
{
    LATBbits.LATB7 = 0;
    LATBbits.LATB6 = 1;
}

void control_elevator_down_relay_for_initialization(void)
{
    if (!wait_for_contactor_ready(RELAY_COMMAND_TIMEOUT_MS)) {
        handle_system_security_error();
        return;
    }

    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 1;
}

void close_door(void)
{
    LATEbits.LATE0 = 0;
    LATEbits.LATE1 = 1;
    send_string("A");
}

void disable_motor_relays(void)
{
    LATBbits.LATB7 = 0;
    LATBbits.LATB6 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
}

void handle_system_security_error(void)
{
    disable_motor_relays();
    close_door();
}

int control_elevator_up_relay(void)
{
    return set_direction_relay(1, 0);
}

int control_elevator_down_relay(void)
{
    return set_direction_relay(0, 1);
}

int control_high_speed_relay(void)
{
    return set_speed_relay(1, 0);
}

int control_low_speed_relay(void)
{
    return set_speed_relay(0, 1);
}

void enable_speakers(void)
{
    LATDbits.LATD7 = 0x01;
}

void disable_speakers(void)
{
    LATDbits.LATD7 = 0x00;
}

void enable_lighting_and_fan(void)
{
    LATEbits.LATE2 = 0x01;
}

void disable_lighting_and_fan(void)
{
    LATEbits.LATE2 = 0x00;
}

void open_door(void)
{
    LATEbits.LATE0 = 1;
    LATEbits.LATE1 = 0;
    send_string("B");
    __delay_ms(200);
}

void close_door_for_initialization(void)
{
    LATEbits.LATE0 = 0;
    LATEbits.LATE1 = 1;
    send_string("10");
    __delay_ms(200);
}

void display_floor_zero(void)
{
    LATDbits.LATD5 = 1;
    LATDbits.LATD4 = 1;
    LATCbits.LATC5 = 1;
    LATDbits.LATD3 = 1;
    LATDbits.LATD2 = 0;
}

void display_floor_one(void)
{
    LATDbits.LATD5 = 0;
    LATDbits.LATD4 = 0;
    LATCbits.LATC5 = 0;
    LATDbits.LATD3 = 0;
    LATDbits.LATD2 = 0;
}

void display_floor_two(void)
{
    LATDbits.LATD5 = 1;
    LATDbits.LATD4 = 1;
    LATCbits.LATC5 = 1;
    LATDbits.LATD3 = 0;
    LATDbits.LATD2 = 1;
}

void display_floor_three(void)
{
    LATDbits.LATD5 = 0;
    LATDbits.LATD4 = 1;
    LATCbits.LATC5 = 1;
    LATDbits.LATD3 = 0;
    LATDbits.LATD2 = 1;
}

void initialize_elevator(void)
{
    unsigned int elapsed_ms = 0;

    if (PORTBbits.RB4) {
        disable_motor_relays();
        return;
    }

    close_door_for_initialization();
    control_low_speed_relay_for_initialization();
    control_elevator_down_relay_for_initialization();

    while (!PORTBbits.RB4 && elapsed_ms < INITIALIZATION_TIMEOUT_MS) {
        __delay_ms(INITIALIZATION_POLL_INTERVAL_MS);
        elapsed_ms += INITIALIZATION_POLL_INTERVAL_MS;
    }

    disable_motor_relays();

    if (!PORTBbits.RB4) {
        handle_system_security_error();
    }
}
