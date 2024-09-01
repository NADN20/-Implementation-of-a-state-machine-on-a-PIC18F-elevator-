
#ifndef Control_Elevator_H
#define	Control_Elevator_H

#include <stdio.h>
#include <stdbool.h>
#include "mcc.h"
#include "INIT_IN.h"
#include "INIT_OUT.h"
#include "Control_Elevator.h"
#include <xc.h>
#include "eusart1.h"


void controlLowSpeedRelayForInitialisation(void);
 void controlElevatorDownRelayForIntialisation(void);
 void Close_DoorForIntialisation(void);
 void initialisation_ascenseur(void);
void Close_Door(void);
void Open_Door(void);
void EnableSpeakers (void);
void DisableSpeakers(void);
void EnableLightingAndFun(void);
void DisableLightingAndFun(void);
void disableMotorRelays(void);
void ErrorSystemSecurity(void);
int controlElevatorUpRelay(void);
int controlElevatorDownRelay(void);
int controlHighSpeedRelay(void);
int controlLowSpeedRelay(void);

void display7SegNumberZero(void);
void display7SegNumberOne(void);
void display7SegNumberTwo(void);
void display7SegNumberThree(void); 


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

