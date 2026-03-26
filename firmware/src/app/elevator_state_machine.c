#include <stdbool.h>

#include <xc.h>

#include "app/elevator_control.h"
#include "app/elevator_state_machine.h"
#include "platform/eusart1.h"
#include "platform/mcc.h"

#define MOVEMENT_TIMEOUT_MS 15000U
#define MOVEMENT_POLL_INTERVAL_MS 1U

typedef enum {
    Etage_RC,
    Att1M,
    Et1,
    Att2M,
    Et2,
    Att3,
    Et3,
    AttRC,
    Att2M1,
    Att3M1 ,
    Att1D2,
    AttRCD2,
    Att3M2,
    Att2D3,
    AttRCD3,
    Att1D3,

} EtatNormal;

typedef enum {
     Etat_Initial,
    Etat_Up,
    Etat_Down,
    Etat_Arret
} EtatTechnicien;

static bool ascArrive = false;
static bool movement_fault = false;
static int etatPrecedent = 0;
static EtatNormal etat_normal_courant =  Etage_RC;
static EtatTechnicien etat_technicien_courant = Etat_Initial;

static int get_upper_limit_switch_value() {
    if (PORTBbits.RB5 == 1) {
        send_string("z");
        return 1;
    } else {
        return 0;
    }
}
static int get_lower_limit_switch_value() {
    if (PORTBbits.RB4 == 1) {
        send_string("x");
        return 1;
    } else {
        return 0;
    }
}

static bool wait_for_next_sensor_edge(unsigned int *elapsed_ms) {
    while (PORTDbits.RD6 == etatPrecedent) {
        if (*elapsed_ms >= MOVEMENT_TIMEOUT_MS) {
            return false;
        }

        __delay_ms(MOVEMENT_POLL_INTERVAL_MS);
        *elapsed_ms += MOVEMENT_POLL_INTERVAL_MS;
    }

    return true;
}

static void signal_movement_fault(void) {
    handle_system_security_error();
    movement_fault = true;
    ascArrive = false;
}

static void wait_for_arrival_rdc() {

    int frontMontantCount = 0;
    unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 2) {
                control_high_speed_relay();
            }

            if (frontMontantCount == 4) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 6 && get_lower_limit_switch_value() == 1) {
                disable_motor_relays();

                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
}
static void wait_for_arrival_1d3(){
    int frontMontantCount = 0;
    unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent && get_upper_limit_switch_value() == 0 ) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 10) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 12) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
}
static void wait_for_arrival_1m() {
    int frontMontantCount = 0;
    unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent ) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 2) {
                control_high_speed_relay();
            }

            if (frontMontantCount == 4) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 6) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
}
static void wait_for_arrival_2m() {
    int frontMontantCount = 0;
    unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 10) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 12) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }
static void wait_for_arrival_3m() {
    int frontMontantCount = 0;
    unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 16) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 18 && get_upper_limit_switch_value() == 1) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }
static void wait_for_arrival_3m1(){

    int frontMontantCount = 0;
    unsigned int elapsed_ms = 0;
    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 10) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 12 && get_upper_limit_switch_value() == 1) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }
static void wait_for_arrival_1d2(){
        int frontMontantCount = 0;
        unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 4) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 6) {
                disable_motor_relays();

                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }
static void wait_for_arrival_rcd3(){
        int frontMontantCount = 0;
        unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 16) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 18 && get_lower_limit_switch_value() == 1) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }
static void wait_for_arrival_2d3() {
        int frontMontantCount = 0;
        unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 4) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 6) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }
static void wait_for_arrival_rcd2(){
        int frontMontantCount = 0;
        unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 10) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 12 && get_lower_limit_switch_value() == 1) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }
static void wait_for_arrival_3m2(){
        int frontMontantCount = 0;
        unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 4) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 6 && get_upper_limit_switch_value() == 1) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }
static void wait_for_arrival_2m1(){
        int frontMontantCount = 0;
        unsigned int elapsed_ms = 0;

    while (!ascArrive) {
        if (!wait_for_next_sensor_edge(&elapsed_ms)) {
            signal_movement_fault();
            return;
        }

        __delay_ms(40);
        elapsed_ms += 40;

        if (PORTDbits.RD6 != etatPrecedent) {

            frontMontantCount++; send_string("t");

            if (frontMontantCount == 4) {
                control_low_speed_relay();
            }

            if (frontMontantCount == 6) {
                disable_motor_relays();
                ascArrive = true;
            }
        }

        etatPrecedent = PORTDbits.RD6;
    }
    }

static bool start_normal_up_motion(void) {
    movement_fault = false;
    return control_elevator_up_relay() && control_high_speed_relay();
}

static bool start_normal_down_motion(void) {
    movement_fault = false;
    return control_elevator_down_relay() && control_high_speed_relay();
}

static bool start_manual_up_motion(void) {
    movement_fault = false;
    return control_low_speed_relay() && control_elevator_up_relay();
}

static bool start_manual_down_motion(void) {
    movement_fault = false;
    return control_low_speed_relay() && control_elevator_down_relay();
}

static void handle_normal_state() {
    switch (etat_normal_courant) {
        case Etage_RC:
            if (PIR1bits.RC1IF == 1) {
                uint8_t receivedData = EUSART1_Read();
                PIR1bits.RC1IF = 0;

                if (receivedData == 0x31) {
                    display_floor_zero();
                    open_door();

                    __delay_ms(2000);
                    close_door();
                    __delay_ms(2000);
                    etat_normal_courant = Etage_RC;
                    break;
                } else if (receivedData == 0x32) {
                    display_floor_zero();

                    etat_normal_courant = Att1M;
                    break;
                } else if (receivedData == 0x33) {
                    display_floor_zero();

                    etat_normal_courant = Att2M;
                    break;
                } else if (receivedData == 0x34) {
                    display_floor_zero();

                    etat_normal_courant = Att3;
                    break;
                } else {
                    display_floor_zero();

                    etat_normal_courant = Etage_RC;
                    break;
                }

            }

                  else if (PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0)     {
                    display_floor_zero();
                    open_door();

                    __delay_ms(2000);
                     close_door();
                    __delay_ms(2000);

                    etat_normal_courant = Etage_RC;

                  break;
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {
                    display_floor_zero();

                    etat_normal_courant = Att1M;
                  break;
                }
                 else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA3 == 0) {
                    display_floor_zero();

                    etat_normal_courant = Att2M;
                    break;
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 1) {
                    display_floor_zero();

                    etat_normal_courant = Att3;
                    break;
                }
                else if (PORTAbits.RA4 == 1 ) {
                    display_floor_zero();
                     open_door();
                    __delay_ms(2000);
                    close_door();
                    __delay_ms(2000);
                    etat_normal_courant = Etage_RC;
                    break;
                }
                else if (PORTAbits.RA5 == 1 ) {
                    display_floor_zero();
                    close_door();
                    __delay_ms(5000);
                    etat_normal_courant = Etage_RC;
                    break;
                }
                else {
                    display_floor_zero();

                    etat_normal_courant = Etage_RC;
                 break;
                }

            case Att1M:

                if (!start_normal_up_motion()) {
                    etat_normal_courant = Etage_RC;
                    break;
                }
                  send_string("u");
                wait_for_arrival_1m();
                if (movement_fault) {
                    etat_normal_courant = Etage_RC;
                    break;
                }
                display_floor_one();
                ascArrive = false;

                open_door();
                __delay_ms(1000);
                 close_door();
                 send_string("D");
                etat_normal_courant = Et1;
                break ;
        case Att2M:

                if (!start_normal_up_motion()) {
                    etat_normal_courant = Etage_RC;
                    break;
                }
                send_string("i");
                wait_for_arrival_2m();
                if (movement_fault) {
                    etat_normal_courant = Etage_RC;
                    break;
                }
                display_floor_two();
                ascArrive = false;

                open_door();
                    __delay_ms(1000);
                 close_door();
                  send_string("E");
                etat_normal_courant = Et2;
                break;

                case Att3:

                if (!start_normal_up_motion()) {
                    etat_normal_courant = Etage_RC;
                    break;
                }
                send_string("o");
                wait_for_arrival_3m();
                if (movement_fault) {
                    etat_normal_courant = Etage_RC;
                    break;
                }
                display_floor_three();
                ascArrive = false;

                open_door();
                  __delay_ms(1000);
                 close_door();
               send_string("F");
                etat_normal_courant = Et3;
                break;

            case Et1:
                 if (PIR1bits.RC1IF==1){
                    uint8_t receivedData = EUSART1_Read();
                    PIR1bits.RC1IF=0 ;
                    if (receivedData==0x31){
                       display_floor_one();

                    etat_normal_courant = AttRC;
                    break;
                    }
                    else if (receivedData==0x32 ) {
                        display_floor_one();
                   open_door();

                    __delay_ms(1000);
                     close_door();
                    __delay_ms(1000);
                    etat_normal_courant = Et1;
                    break;
                    }
                    else if (receivedData==0x33 ){
                          display_floor_one();

                    etat_normal_courant = Att2M1 ;
                    break;
                    }
                    else if  (receivedData==0x34 )
                    {

                     display_floor_one();

                    etat_normal_courant = Att3M1;
                    break;
                    }
                    else {
                         display_floor_one();

                    etat_normal_courant = Et1;
                    break;
                    }
                 }

               else  if (PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0 ) {
                    display_floor_one();

                    etat_normal_courant = AttRC;
                    break;
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {

                    display_floor_one();
                   open_door();

                    __delay_ms(1000);
                     close_door();
                    __delay_ms(1000);
                    etat_normal_courant = Et1;
                    break;

                }
                 else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA3 == 0) {

                     display_floor_one();

                    etat_normal_courant = Att2M1;
                    break;

                }
                 else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 1) {

                     display_floor_one();

                    etat_normal_courant = Att3M1;
                    break;

                }

                 else if (PORTAbits.RA4 == 1 ) {

                     display_floor_one();
                       open_door();
                    __delay_ms(1000);
                    close_door();
                    __delay_ms(1000);

                    etat_normal_courant = Et1;

                     break;
                }
                else if (PORTAbits.RA5 == 1 ) {

                    display_floor_one();
                    close_door();
                    __delay_ms(5000);
                    etat_normal_courant = Et1;
                    break;

                }

                else {
                    display_floor_one();

                    etat_normal_courant = Et1;
                    break;
                }

case Att3M1:

                if (!start_normal_up_motion()) {
                    etat_normal_courant = Et1;
                    break;
                }
                send_string("p");
                wait_for_arrival_3m1();
                if (movement_fault) {
                    etat_normal_courant = Et1;
                    break;
                }
                display_floor_three();
                ascArrive = false;

                open_door();
                  __delay_ms(1000);
                 close_door();
                  send_string("F");
                etat_normal_courant = Et3;
                 break  ;

                case Att2M1:

                if (!start_normal_up_motion()) {
                    etat_normal_courant = Et1;
                    break;
                }
                  send_string("q");
                wait_for_arrival_2m1();
                if (movement_fault) {
                    etat_normal_courant = Et1;
                    break;
                }
                display_floor_two();
                ascArrive = false;

                open_door();
                    __delay_ms(1000);
                 close_door();
               send_string("E");
                etat_normal_courant = Et2;
                break  ;

                case AttRC:

                if (!start_normal_down_motion()) {
                    etat_normal_courant = Et1;
                    break;
                }
                wait_for_arrival_rdc();
                if (movement_fault) {
                    etat_normal_courant = Et1;
                    break;
                }
                 send_string("s");
                ascArrive = false;
                display_floor_zero();

                open_door();
                 __delay_ms(1000);
                 close_door();
                  send_string("C");
                etat_normal_courant = Etage_RC;
                 break ;

            case Et2:
                if (PIR1bits.RC1IF==1){
                     uint8_t  receivedData = EUSART1_Read();
                    PIR1bits.RC1IF=0 ;
                    if (receivedData==0x33)
                    {
                        display_floor_two();
                    open_door();

                    __delay_ms(2000);
                     close_door();
                    etat_normal_courant = Et2 ;
                    break;
                    }
                    else if (receivedData==0x32 )
                    {
                         display_floor_two();

                    etat_normal_courant = Att1D2;
                    break;
                    }
                    else if (receivedData==0x31) {
                         display_floor_two();

                    etat_normal_courant = AttRCD2;
                    break;
                    }
                    else if (receivedData==0x34 )
                    {
                        display_floor_two();

                    etat_normal_courant = Att3M2;
                    break;
                    }
                    else {
                        display_floor_two();

                    etat_normal_courant = Et2;
                    break;

                    }
                }
                else  if (PORTAbits.RA2 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 0 && PORTAbits.RA3 == 0) {
                    display_floor_two();
                    open_door();

                    __delay_ms(2000);
                     close_door();
                    etat_normal_courant = Et2 ;
                    break;

                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {

                    display_floor_two();

                    etat_normal_courant = Att1D2;
                   break;

                }
                 else if (PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {

                     display_floor_two();

                    etat_normal_courant = AttRCD2;
                  break;
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 1) {

                    display_floor_two();

                    etat_normal_courant = Att3M2;

                   break;
                }

                else if (PORTAbits.RA4 == 1 ) {

                    display_floor_two();
                     open_door();
                    __delay_ms(2000);
                    close_door();
                    __delay_ms(2000);
                    etat_normal_courant = Et2;
                    break;
                }

               else if (PORTAbits.RA5 == 1 ) {

                    display_floor_two();
                    close_door();
                    __delay_ms(5000);
                    etat_normal_courant = Et2;
                    break;
                }
                else {

                    display_floor_two();

                    etat_normal_courant = Et2;
                   break;
                }

                case Att1D2:

                if (!start_normal_down_motion()) {
                    etat_normal_courant = Et2;
                    break;
                }
                 send_string("j");
                wait_for_arrival_1d2();
                if (movement_fault) {
                    etat_normal_courant = Et2;
                    break;
                }
                ascArrive = false;
                display_floor_one();

                open_door();
                    __delay_ms(1000);
                 close_door();
                send_string("D");
                etat_normal_courant = Et1;
                 break ;

                case AttRCD2:

                if (!start_normal_down_motion()) {
                    etat_normal_courant = Et2;
                    break;
                }
                   send_string("k");
                wait_for_arrival_rcd2();
                if (movement_fault) {
                    etat_normal_courant = Et2;
                    break;
                }
                ascArrive = false;
                display_floor_zero();
                open_door();

                    __delay_ms(1000);
                 close_door();
                send_string("C");
                etat_normal_courant = Etage_RC;
                 break ;

        case Att3M2:

                if (!start_normal_up_motion()) {
                    etat_normal_courant = Et2;
                    break;
                }
                 send_string("l");
                wait_for_arrival_3m2();
                if (movement_fault) {
                    etat_normal_courant = Et2;
                    break;
                }
                ascArrive = false;
                display_floor_three();

                open_door();
                __delay_ms(1000);
                 close_door();
             send_string("F");
                etat_normal_courant = Et3;
                  break ;

                case Et3:
                    if (PIR1bits.RC1IF==1){
                     uint8_t  receivedData = EUSART1_Read();
                    PIR1bits.RC1IF=0 ;
                    if (receivedData==0x34)
                    {
                      display_floor_three();
                    open_door();

                    __delay_ms(2000);
                     close_door();
                    etat_normal_courant = Et3 ;
                    break;
                    }
                    else if (receivedData==0x32)
                    {
                    display_floor_three();

                    etat_normal_courant = Att1D3;
                    break;
                    }
                    else if (receivedData==0x31)
                    {
                          display_floor_three();

                    etat_normal_courant = AttRCD3;
                    break;

                }
                    else if (receivedData==0x33){
                       display_floor_three();

                    etat_normal_courant = Att2D3;
                    break;
                    }
                    else {
                        display_floor_three();

                    etat_normal_courant = Et3;
                    break;
                }
                    }

                  else if (PORTAbits.RA2 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 0 && PORTAbits.RA3 == 1) {

                    display_floor_three();
                    open_door();

                    __delay_ms(2000);
                     close_door();
                    etat_normal_courant = Et3 ;
                    break;

                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {

                    display_floor_three();

                    etat_normal_courant = Att1D3;
                    break;

                }
                 else if (PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {

                     display_floor_three();

                    etat_normal_courant = AttRCD3;
                    break;

                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA3 == 0) {

                    display_floor_three();

                    etat_normal_courant = Att2D3;
                    break;

                }

                else if (PORTAbits.RA4 == 1 ) {

                    display_floor_three();
                     open_door();
                    __delay_ms(2000);
                    close_door();

                    etat_normal_courant = Et3;
                    break;
                }
                else if (PORTAbits.RA5 == 1 ) {

                    display_floor_three();
                    close_door();
                    __delay_ms(5000);
                    etat_normal_courant = Et3;
                    break;

                }
                else {

                    display_floor_three();

                    etat_normal_courant = Et3;
                    break;

                }

                case Att1D3:

                if (!start_normal_down_motion()) {
                    etat_normal_courant = Et3;
                    break;
                }
                 send_string("m");
                wait_for_arrival_1d3();
                if (movement_fault) {
                    etat_normal_courant = Et3;
                    break;
                }
                ascArrive = false;
                display_floor_one();

                open_door();
                    __delay_ms(1000);
                 close_door();
              send_string("D");
                etat_normal_courant = Et1;
                break ;

                case AttRCD3:

                if (!start_normal_down_motion()) {
                    etat_normal_courant = Et3;
                    break;
                }
                 send_string("v");
                wait_for_arrival_rcd3();
                if (movement_fault) {
                    etat_normal_courant = Et3;
                    break;
                }
                ascArrive = false;
                display_floor_zero();

                open_door();
                    __delay_ms(1000);
                 close_door();
                send_string("C");
                etat_normal_courant = Etage_RC;
                    break ;

        case Att2D3:

                if (!start_normal_down_motion()) {
                    etat_normal_courant = Et3;
                    break;
                }
                 send_string("n");
                wait_for_arrival_2d3();
                if (movement_fault) {
                    etat_normal_courant = Et3;
                    break;
                }
                ascArrive = false;
                display_floor_two();

                open_door();
                __delay_ms(1000);
                 close_door();
                  send_string("E");
                etat_normal_courant = Et2;
                break ;

        }
    }

static void handle_technician_state(void) {

    switch (etat_technicien_courant) {
        case Etat_Initial:

             close_door();
            disable_motor_relays();

            if (PORTCbits.RC0== 0 && PORTCbits.RC2== 1  ) {
              etat_technicien_courant = Etat_Up;

            } else if (PORTCbits.RC0== 1 && PORTCbits.RC2== 0 ) {
                etat_technicien_courant = Etat_Down;

            } else if ( PORTCbits.RC0== 1 && PORTCbits.RC2== 1) {
               etat_technicien_courant  = Etat_Arret;
            } else {
              etat_technicien_courant  = Etat_Arret;

            }

            break;

        case Etat_Up:

            close_door();
            if (!start_manual_up_motion()) {
                etat_technicien_courant = Etat_Arret;
                break;
            }

            if (PORTCbits.RC0 == 0 && PORTCbits.RC2 == 1) {
                etat_technicien_courant = Etat_Up;
            } else if ( PORTCbits.RC0== 1 && PORTCbits.RC2== 1){
                etat_technicien_courant = Etat_Arret;
            } else if ( PORTCbits.RC0== 1 && PORTCbits.RC2== 0) {
                etat_technicien_courant  = Etat_Down;
            } else {
               etat_technicien_courant  = Etat_Arret;
            }
            break;

        case Etat_Down:

            close_door();
            if (!start_manual_down_motion()) {
                etat_technicien_courant = Etat_Arret;
                break;
            }

            if (PORTCbits.RC0 == 1 && PORTCbits.RC2 == 0) {
                etat_technicien_courant  = Etat_Down;
            } else if (PORTCbits.RC0== 0 && PORTCbits.RC2== 0) {
                etat_technicien_courant  = Etat_Arret;
            } else if (PORTCbits.RC0== 0 && PORTCbits.RC2== 1) {
                etat_technicien_courant  = Etat_Up;
            } else {
                 etat_technicien_courant  = Etat_Arret;
            }
            break;

        case Etat_Arret:

            close_door();
            disable_motor_relays();

            if (PORTCbits.RC0== 0 && PORTCbits.RC2== 1) {
               etat_technicien_courant  = Etat_Up;
            } else if (PORTCbits.RC0== 1 && PORTCbits.RC2== 0) {
                etat_technicien_courant  = Etat_Down;

            } else {
             etat_technicien_courant  = Etat_Arret ;
            }
            break;
    }
}

static int read_mode_switch(void) {
    return PORTCbits.RC1;
}

static void run_active_mode(void) {

    int RC1_value = read_mode_switch() ;

    switch (RC1_value) {
        case 0:

            handle_normal_state();

            break;
        case 1:

              handle_technician_state();

            break;
        default:
            break;
    }
}

void elevator_state_machine_initialize(void) {
    ascArrive = false;
    movement_fault = false;
    etatPrecedent = PORTDbits.RD6;
    etat_normal_courant = Etage_RC;
    etat_technicien_courant = Etat_Initial;
}

void elevator_state_machine_step(void) {
    run_active_mode();
}
