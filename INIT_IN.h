
#ifndef INIT_IN_H
#define	INIT_IN_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



// TODO Insert declarations
 void configureFloorButtonPorts(void);  
 void configureRisingEdge(void);  
void configControlEtatAscensseur(void);
void configLevel(void);
void configUpperLimitSwitch(void);
 void configLowerLimitSwitch(void);
void configSecurityInterrupt (void);
void ConfigureKTC(void);
//void configureI2CPorts(void);//
void configureUSARTPorts(void);
void ConfigManualCommande(void);
void configPinsDoor(void);
void  Initialize_Input(void);
    
    
    
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

