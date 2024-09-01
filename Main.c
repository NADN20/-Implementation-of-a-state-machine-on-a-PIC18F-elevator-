#include <stdio.h>
#include <stdbool.h>
#include "mcc.h"
#include "INIT_IN.h"
#include "INIT_OUT.h"
#include "Control_Elevator.h"
#include <xc.h>
#include "eusart1.h"


void OSCILLATOR_Initialize(void)
{
    
      OSCTUNE = 0X00;
    // SCS FOSC; IRCF 1MHz_HFINTOSC/16; IDLEN disabled; 
      OSCCON = 0x72;
    // PRISD enabled; SOSCGO disabled; MFIOSEL disabled; 
      OSCCON2=0X00;
    // INTSRC disabled; PLLEN disabled; TUN 0; 
   
}



typedef enum {
    Etage_RC,                   // ETAGE RC
    Att1M,                // 0 lel 1       
    Et1,                    //etage 1
    Att2M,                    // RC lel 2 
    Et2,                 //etage 2 
    Att3,                // RC lel 3 
    Et3,                   // etage 3
    AttRC,                  // 1 lel 0
    Att2M1,               // 1 lel 2
    Att3M1 ,                // 1 lel 3  
    Att1D2,               // 2  lel 1 
    AttRCD2,               //  2 lel 0
    Att3M2,                   // 2 lel3
    Att2D3,                   // 3 tahbet lel 2
    AttRCD3,                   // 3 lel 0
    Att1D3,                          // 3 lel 1       
            
} EtatNormal;

typedef enum {
     Etat_Initial,
    Etat_Up,
    Etat_Down,
    Etat_Arret
} EtatTechnicien;

   bool ascArrive = false;
   int etatPrecedent = 0;
   EtatNormal etat_normal_courant =  Etage_RC;
   EtatTechnicien etat_technicien_courant = Etat_Initial;

int getRB5Value() {
    if (PORTBbits.RB5 == 1) {
        send_string("z");  // Envoyer la chaîne "x"
        return 1;  // La condition est vraie, retourne 1
    } else {
        return 0;  // La condition est fausse, retourne 0
    }
}
int getRB4Value() {
    if (PORTBbits.RB4 == 1) {
        send_string("x");  // Envoyer la chaîne "x"
        return 1;  // La condition est vraie, retourne 1
    } else {
        return 0;  // La condition est fausse, retourne 0
    }
}

void SYSTEM_Initialize(void)
{
    OSCILLATOR_Initialize();
    INTERRUPT_Initialize();
   // I2C1_Initialize();
    EUSART1_Initialize();
    Initialize_Output();
    Initialize_Input(); 
}
    
 unsigned char rx_data;
  
 

 void attenteArriveeRDC() {

    int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
            
            // Exécuter une fonction au deuxième front montant
            if (frontMontantCount == 2) { 
                controlHighSpeedRelay();
            }
         
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 4) {
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 6 && getRB4Value() == 1 ||getRB4Value() == 1 ) {  
                disableMotorRelays();
                
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
}
void attenteArrivee1D3(){
    int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent && getRB5Value() == 0 ) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
           
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 10) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 12) {
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
}
void attenteArrivee1M() {
    int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent ) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
            
           
            // Exécuter une fonction au deuxième front montant
            if (frontMontantCount == 2) { 
                controlHighSpeedRelay();
            }
            
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 4) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 6) {
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
}
void attenteArrivee2M() {
    int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t");
            
           
       
            
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 10) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 12) {
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    }   
void attenteArrivee3M() {
    int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
            
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 16) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 18 && getRB5Value()==1 || getRB5Value() == 1) {
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    }  
void attenteArrivee3M1(){
       
    int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée
    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
            
            
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
            
           
           
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 10) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 12 && getRB5Value() == 1 || getRB5Value() == 1  ) {  // ou 818=1
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    }
void attenteArrivee1D2(){
        int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
            
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 4) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 6) {
                disableMotorRelays();
                
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    } 
void attenteArriveeRCD3(){
        int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t");  
            
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 16) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 18 && getRB4Value() ==1 || getRB4Value() == 1) {   //ou 817=1 
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    }
void attenteArrivee2D3() {
        int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
            
           
            
            
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 4) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 6) {
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    }    
void attenteArriveeRCD2(){
        int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
            
                     
            
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 10) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 12 && getRB4Value()==1 || getRB4Value() == 1 ) {   
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    }     
void  attenteArrivee3M2(){
        int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t"); 
            
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 4) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 6 && getRB5Value()==1 || getRB5Value() == 1 ) { // ou 818=1
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    } 
void attenteArrivee2M1(){
        int frontMontantCount = 0; // Variable pour stocker l'état précédent de l'entrée

    while (!ascArrive) {
        while (PORTDbits.RD6 == etatPrecedent) {
        }
        
        // Temporisation pour filtrer les rebonds
        __delay_ms(40);
        
        // Vérifier si la broche est toujours à l'état haut après la temporisation
        if (PORTDbits.RD6 != etatPrecedent) {
            // L'état de l'entrée a changé, incrémenter le compteur
            frontMontantCount++; send_string("t");
            
          
            // Exécuter une fonction au sixième front montant
            if (frontMontantCount == 4) { 
                controlLowSpeedRelay();
            }
            
            // Exécuter une fonction au huitième front montant
            if (frontMontantCount == 6) {
                disableMotorRelays();
                ascArrive = true; // Terminer la boucle
            }
        }
        
        // Mettre à jour l'état précédent de l'entrée
        etatPrecedent = PORTDbits.RD6;
    }
    }



void gestionEtatNormal() {
    switch (etat_normal_courant) {
        case Etage_RC:
            if (PIR1bits.RC1IF == 1) {
                uint8_t receivedData = EUSART1_Read();
                PIR1bits.RC1IF = 0; 

                if (receivedData == 0x31) {
                    display7SegNumberZero();
                    Open_Door();
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:0                ");
                    __delay_ms(2000);
                    Close_Door();
                    __delay_ms(2000);
                    etat_normal_courant = Etage_RC;
                    break;
                } else if (receivedData == 0x32) {
                    display7SegNumberZero();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS                ");
                    etat_normal_courant = Att1M;
                    break;
                } else if (receivedData == 0x33) {
                    display7SegNumberZero();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS          ");
                    etat_normal_courant = Att2M;
                    break;
                } else if (receivedData == 0x34) {
                    display7SegNumberZero();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS          ");
                    etat_normal_courant = Att3;
                    break;
                } else {
                    display7SegNumberZero();
                    // lcd_writemessage(1, 1, "WAITS FOR CALL           ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:0         ");
                    etat_normal_courant = Etage_RC;
                    break;
                }
              
            }

                  else if (PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0)     {
                    display7SegNumberZero();
                    Open_Door();
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:0                ");
                    __delay_ms(2000);
                     Close_Door();
                    __delay_ms(2000);
                   
                    etat_normal_courant = Etage_RC; 
                    
                  break;
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {
                    display7SegNumberZero();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS                ");
                   
                    etat_normal_courant = Att1M;
                  break;   
                } 
                 else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA3 == 0) {
                    display7SegNumberZero();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS          ");
                    etat_normal_courant = Att2M;
                    break;
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 1) {
                    display7SegNumberZero();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS          ");
                   
                    etat_normal_courant = Att3;
                    break;
                }              
                else if (PORTAbits.RA4 == 1 ) {
                    display7SegNumberZero();
                     Open_Door();
                    __delay_ms(2000);
                    Close_Door();
                    __delay_ms(2000);
                    etat_normal_courant = Etage_RC;
                    break;
                }
                else if (PORTAbits.RA5 == 1 ) {
                    display7SegNumberZero();
                    Close_Door();
                    __delay_ms(5000);
                    etat_normal_courant = Etage_RC;
                    break;
                }
                else {
                    display7SegNumberZero();
                    // lcd_writemessage(1, 1, "WAITS FOR CALL           ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:0         ");
                   
                    etat_normal_courant = Etage_RC;
                 break;     
                }
              

            case Att1M:
               
                controlElevatorUpRelay();
                controlHighSpeedRelay();
                  send_string("u");
                attenteArrivee1M();
                display7SegNumberOne();
                ascArrive = false; 
           
                // lcd_writemessage(2, 1, "100: 24V FLOOR:1             ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL               ");
                Open_Door();
                __delay_ms(1000);
                 Close_Door();    
                 send_string("D");
                etat_normal_courant = Et1;
                break ; 
        case Att2M:
           
                controlElevatorUpRelay();
                controlHighSpeedRelay();
                send_string("i");
                attenteArrivee2M();
                display7SegNumberTwo();
                ascArrive = false; 
               
                // lcd_writemessage(2, 1, "100: 24V FLOOR:2           ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL             ");
                Open_Door();
                    __delay_ms(1000);
                 Close_Door();
                  send_string("E");
                etat_normal_courant = Et2;
                break;
               
                case Att3:
                   
                controlElevatorUpRelay();
                controlHighSpeedRelay(); 
                send_string("o");
                attenteArrivee3M();
                display7SegNumberThree();
                ascArrive = false; 
               
                  // lcd_writemessage(2, 1, "100: 24V FLOOR:3              ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL                ");
                Open_Door();
                  __delay_ms(1000);
                 Close_Door();    
               send_string("F");
                etat_normal_courant = Et3;
                break;
               
            case Et1:
                 if (PIR1bits.RC1IF==1){
                    uint8_t receivedData = EUSART1_Read();
                    PIR1bits.RC1IF=0 ; 
                    if (receivedData==0x31){
                       display7SegNumberOne();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS          ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1         ");
                   
                    etat_normal_courant = AttRC; 
                    break;
                    }
                    else if (receivedData==0x32 ) {
                        display7SegNumberOne();
                   Open_Door();
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1           ");
                    __delay_ms(1000);
                     Close_Door();
                    __delay_ms(1000);
                    etat_normal_courant = Et1;
                    break;
                    } 
                    else if (receivedData==0x33 ){  
                          display7SegNumberOne();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS            ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1           ");
                    etat_normal_courant = Att2M1 ; 
                    break;
                    }
                    else if  (receivedData==0x34 )
                    {
                    
                     display7SegNumberOne();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS             ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1            ");
                    etat_normal_courant = Att3M1;
                    break;
                    }
                    else {
                         display7SegNumberOne();
                    // lcd_writemessage(1, 1, "WAITS FOR CALL                ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1              ");
                    etat_normal_courant = Et1;
                    break;
                    }
                 }
            
                                      // Ascenseur à l'étage 1, attendre la demande d'arrêt
               else  if (PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0 ) {
                    display7SegNumberOne();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS          ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1         ");
                   
                    etat_normal_courant = AttRC; 
                    break;
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {
                  
                    display7SegNumberOne();
                   Open_Door();
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1           ");
                    __delay_ms(1000);
                     Close_Door();
                    __delay_ms(1000);
                    etat_normal_courant = Et1;
                    break;
                     
                }
                 else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA3 == 0) {
                  
                     display7SegNumberOne();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS            ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1           ");
                    etat_normal_courant = Att2M1;
                    break;
                     
                }
                 else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 1) {
                  
                     display7SegNumberOne();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS             ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1            ");
                    etat_normal_courant = Att3M1;
                    break;
                     
                }  
                
               
                 else if (PORTAbits.RA4 == 1 ) {
                   
                     display7SegNumberOne();
                       Open_Door();
                    __delay_ms(1000);
                    Close_Door();
                    __delay_ms(1000);

                    etat_normal_courant = Et1;
                    
                     break; 
                }
                else if (PORTAbits.RA5 == 1 ) {
                   
                    display7SegNumberOne();
                    Close_Door();
                    __delay_ms(5000);
                    etat_normal_courant = Et1;
                    break;
                      
                }
                
                else {
                    display7SegNumberOne();
                   
                    // lcd_writemessage(1, 1, "WAITS FOR CALL                ");
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:1              ");
                    etat_normal_courant = Et1;
                    break;
                }
                
                
case Att3M1:
                
                controlElevatorUpRelay();
                controlHighSpeedRelay();
                send_string("p");
                attenteArrivee3M1();
                display7SegNumberThree();
                ascArrive = false; 
                
                 // lcd_writemessage(2, 1,"100: 24V FLOOR:3          ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL            ");
                Open_Door();
                  __delay_ms(1000);
                 Close_Door();    
                  send_string("F");
                etat_normal_courant = Et3;
                 break  ;
                
                case Att2M1:
                   
                controlElevatorUpRelay();
                controlHighSpeedRelay();
                  send_string("q");
                attenteArrivee2M1();
                display7SegNumberTwo();
                ascArrive = false; 
                  // lcd_writemessage(2, 1, "100: 24V FLOOR:2          ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL            ");
                Open_Door();
                    __delay_ms(1000);
                 Close_Door();    
               send_string("E");
                etat_normal_courant = Et2;
                break  ;
                
             
                case AttRC:
                    
                
                controlElevatorDownRelay();
                controlHighSpeedRelay();
                attenteArriveeRDC();
                 send_string("s");
                ascArrive = false; // Réinitialiser ascArrive à false
                display7SegNumberZero();
                // lcd_writemessage(2, 1, "100: 24V FLOOR:0          ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL            ");
                Open_Door();
                 __delay_ms(1000);
                 Close_Door(); 
                  send_string("C");
                etat_normal_courant = Etage_RC;
                 break ;
                 
            case Et2:
                if (PIR1bits.RC1IF==1){
                     uint8_t  receivedData = EUSART1_Read();
                    PIR1bits.RC1IF=0 ; 
                    if (receivedData==0x33)
                    {  
                        display7SegNumberTwo();
                    Open_Door();
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:2        ");
                    __delay_ms(2000);
                     Close_Door();
                    etat_normal_courant = Et2 ; 
                    break;
                    }
                    else if (receivedData==0x32 ) 
                    {
                         display7SegNumberTwo();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");
                    etat_normal_courant = Att1D2;
                    break;
                    }
                    else if (receivedData==0x31) {
                         display7SegNumberTwo();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");
                    etat_normal_courant = AttRCD2; 
                    break;
                    }
                    else if (receivedData==0x34 )
                    {
                        display7SegNumberTwo();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");
                    etat_normal_courant = Att3M2;
                    break;
                    }
                    else {    
                        display7SegNumberTwo();
                   // lcd_writemessage(1, 1, "WAITS FOR CALL       ");
                   // lcd_writemessage(2, 1, "100: 24V FLOOR:2       ");
                    etat_normal_courant = Et2; 
                    break;
                        
                    }
                }
                else  if (PORTAbits.RA2 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 0 && PORTAbits.RA3 == 0) {
                    display7SegNumberTwo();
                    Open_Door();
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:2        ");
                    __delay_ms(2000);
                     Close_Door();
                    etat_normal_courant = Et2 ;
                    break;
                      
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {
                 
                    display7SegNumberTwo();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");
                    etat_normal_courant = Att1D2;
                   break;   
                    
                } 
                 else if (PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 1 && PORTAbits.RA3 == 0) {
                  
                     display7SegNumberTwo();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");
                    etat_normal_courant = AttRCD2; 
                  break;   
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 1) {
                   
                    display7SegNumberTwo();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");
                    etat_normal_courant = Att3M2;
                   
                   break; 
                }
                
                else if (PORTAbits.RA4 == 1 ) {
                  
                    display7SegNumberTwo();
                     Open_Door();
                    __delay_ms(2000);
                    Close_Door();
                    __delay_ms(2000);
                    etat_normal_courant = Et2;
                    break;
                }
               
               else if (PORTAbits.RA5 == 1 ) {
                  
                    display7SegNumberTwo();
                    Close_Door();
                    __delay_ms(5000);
                    etat_normal_courant = Et2;
                    break; 
                }
                else {
                  
                    display7SegNumberTwo();
                   // lcd_writemessage(1, 1, "WAITS FOR CALL       ");
                   // lcd_writemessage(2, 1, "100: 24V FLOOR:2       ");
                    etat_normal_courant = Et2;
                   break;    
                }
                
                case Att1D2: 
                  
                controlElevatorDownRelay(); 
                controlHighSpeedRelay();
                 send_string("j");
                attenteArrivee1D2();
                ascArrive = false; // Réinitialiser ascArrive à false
                display7SegNumberOne();
                  // lcd_writemessage(2, 1, "100: 24V FLOOR:1             ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL               ");
                Open_Door();
                    __delay_ms(1000);
                 Close_Door(); 
                send_string("D");
                etat_normal_courant = Et1;
                 break ;
                
                case AttRCD2:
                  
                controlElevatorDownRelay();
                controlHighSpeedRelay();
                   send_string("k");
                attenteArriveeRCD2();
                ascArrive = false; // Réinitialiser ascArrive à false
                display7SegNumberZero();
                Open_Door();
                 // lcd_writemessage(2, 1, "100: 24V FLOOR:0             ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL               ");
                    __delay_ms(1000);
                 Close_Door(); 
                send_string("C");
                etat_normal_courant = Etage_RC;
                 break ;
                
        case Att3M2:
           
                controlElevatorUpRelay();
                controlHighSpeedRelay();
                 send_string("l");
                attenteArrivee3M2();
                ascArrive = false;       // Réinitialiser ascArrive à false
                display7SegNumberThree();
                  // lcd_writemessage(2,1,"100: 24V FLOOR:3               ");
                // lcd_writemessage(1,1,"WAITS FOR CALL                 ");
                Open_Door();
                __delay_ms(1000);
                 Close_Door(); 
             send_string("F");
                etat_normal_courant = Et3;
                  break ;
                
              
                case Et3: 
                    if (PIR1bits.RC1IF==1){
                     uint8_t  receivedData = EUSART1_Read();
                    PIR1bits.RC1IF=0 ; 
                    if (receivedData==0x34)
                    {  
                      display7SegNumberThree();
                    Open_Door();
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:3             ");
                    __delay_ms(2000);
                     Close_Door();
                    etat_normal_courant = Et3 ; 
                    break;
                    }
                    else if (receivedData==0x32)
                    {  
                    display7SegNumberThree();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");

                    etat_normal_courant = Att1D3;
                    break;
                    }
                    else if (receivedData==0x31)
                    {
                          display7SegNumberThree();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS            ");
                     
                    etat_normal_courant = AttRCD3; 
                    break;
                       
                }
                    else if (receivedData==0x33){ 
                       display7SegNumberThree();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");
                    etat_normal_courant = Att2D3;
                    break;
                    }      
                    else { 
                        display7SegNumberThree();
                   // lcd_writemessage(1, 1, "WAITS FOR CALL           ");
                   // lcd_writemessage(2, 1, "100: 24V FLOOR:3         ");
                    etat_normal_courant = Et3;
                    break;
                }
                    }
    
                  else if (PORTAbits.RA2 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 0 && PORTAbits.RA3 == 1) {
                  
                    display7SegNumberThree();
                    Open_Door();
                    // lcd_writemessage(2, 1, "100: 24V FLOOR:3             ");
                    __delay_ms(2000);
                     Close_Door();
                    etat_normal_courant = Et3 ;
                    break;
                       
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA3 == 0) {
                   
                    display7SegNumberThree();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");

                    etat_normal_courant = Att1D3;
                    break;
                     
                    
                } 
                 else if (PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 1 && PORTAbits.RA3 == 0) {
                   
                     display7SegNumberThree();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS            ");
                    etat_normal_courant = AttRCD3; 
                    break;
                       
                }
                else if (PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA3 == 0) {
                   
                    display7SegNumberThree();
                    // lcd_writemessage(1, 1, "RECEIVING CALLS         ");
                    etat_normal_courant = Att2D3;
                    break;
                      
                    
                }
                
                else if (PORTAbits.RA4 == 1 ) {
                  
                    display7SegNumberThree();
                     Open_Door();
                    __delay_ms(2000);
                    Close_Door();

                    etat_normal_courant = Et3;
                    break;
                }
                else if (PORTAbits.RA5 == 1 ) {
                  
                    display7SegNumberThree();
                    Close_Door();
                    __delay_ms(5000);
                    etat_normal_courant = Et3;
                    break;
                       
                }
                else {
                   
                    display7SegNumberThree();
                   // lcd_writemessage(1, 1, "WAITS FOR CALL           ");
                   // lcd_writemessage(2, 1, "100: 24V FLOOR:3         ");
                    etat_normal_courant = Et3;
                    break;
                    
                    
                }
              
                
                case Att1D3:
                   
                controlElevatorDownRelay();
                controlHighSpeedRelay();
                 send_string("m");
                attenteArrivee1D3();
                ascArrive = false; // Réinitialiser ascArrive à false
                display7SegNumberOne();
                   // lcd_writemessage(2, 1, "100: 24V FLOOR:1             ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL               ");
                Open_Door();
                    __delay_ms(1000);
                 Close_Door(); 
              send_string("D");
                etat_normal_courant = Et1;
                break ;
                
                
                case AttRCD3:
                   
                controlElevatorDownRelay();
                controlHighSpeedRelay();
                 send_string("v");
                attenteArriveeRCD3();
                ascArrive = false; // Réinitialiser ascArrive à false
                display7SegNumberZero();
                 // lcd_writemessage(2, 1, "100: 24V FLOOR:0             ");
                // lcd_writemessage(1, 1, "WAITS FOR CALL               ");
                Open_Door();
                    __delay_ms(1000);
                 Close_Door(); 
                send_string("C");
                etat_normal_courant = Etage_RC;
                    break ;
                
        case Att2D3:
           
                controlElevatorUpRelay();
                controlHighSpeedRelay(); 
                 send_string("n");
                attenteArrivee2D3();
                ascArrive = false;       // Réinitialiser ascArrive à false
                display7SegNumberThree();
                   // lcd_writemessage(2,1,"100: 24V FLOOR:3               ");
                // lcd_writemessage(1,1,"WAITS FOR CALL                 ");
                Open_Door();
                __delay_ms(1000);
                 Close_Door(); 
                  send_string("E");
                etat_normal_courant = Et2;
                break ; 
              
          
        }
    }

                

   void gestionEtatTechnicien() {
   
    switch (etat_technicien_courant) {
        case Etat_Initial:
            // lcd_writemessage(1,1,"100:ModeTechnicien               ");
             Close_Door(); 
            disableMotorRelays();
            
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
             // lcd_writemessage(2,1,"Etat_Up                     ");
            Close_Door(); 
            controlLowSpeedRelay();
            controlElevatorUpRelay();
            
            
            if ( PORTCbits.RC0== 1 && PORTCbits.RC2== 1){
                etat_technicien_courant = Etat_Arret;
            } else if ( PORTCbits.RC0== 1 && PORTCbits.RC2== 0) {
                etat_technicien_courant  = Etat_Down;
            } else {
               etat_technicien_courant  = Etat_Arret;
            }
            break;
            
        case Etat_Down:
            // lcd_writemessage(2,1,"Etat_Down                    ");
            Close_Door(); 
            controlLowSpeedRelay();
            controlElevatorDownRelay();            
            
            if (PORTCbits.RC0== 0 && PORTCbits.RC2== 0) {
                etat_technicien_courant  = Etat_Arret;
            } else if (PORTCbits.RC0== 0 && PORTCbits.RC2== 1) {
                etat_technicien_courant  = Etat_Up;
            } else {
                 etat_technicien_courant  = Etat_Arret;
            }
            break;
    
        case Etat_Arret:
             // lcd_writemessage(2,1,"Etat_Arret                      ");

            Close_Door(); 
            disableMotorRelays();
            
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
  
   int Read_Case() {
    return PORTCbits.RC1;
}
   
   void fonction_switch() {
       
    int RC1_value = Read_Case() ;
    
    switch (RC1_value) {
        case 0:
            
            gestionEtatNormal();
             
            break;
        case 1:
           
              gestionEtatTechnicien();
            
            break;
        default:
            break;
    }
}




int main() {
    
    SYSTEM_Initialize();
    ANSELC = 0x00;
    ANSELA = 0x00;
    ANSELE = 0x00;
    ANSELD = 0x00;
    ANSELB = 0x00;
  
    // Activer les interruptions globales
    INTERRUPT_GlobalInterruptEnable();

    // Activer les interruptions des périphériques
    INTERRUPT_PeripheralInterruptEnable();
     
    __delay_ms(500);
   //lcd_start();
    //// lcd_writemessage(1, 1, "Tunis Sky Ride        ");
    //__delay_ms(500);
    //// lcd_writemessage(2, 1, "TSR-100  V 1.0x       ");
    //__delay_ms(3000);
    //  lcd_delete(); 
      // // lcd_writemessage(1,1,"Wait For                ");
 
       //  // lcd_writemessage(2, 1,"Initialisation    "); 
      
        initialisation_ascenseur();
            
          // // lcd_writemessage(1, 1, "WAITS FOR CALL                         ");
            //        // lcd_writemessage(2, 1, "100: 24V FLOOR:0              ");
                    etat_normal_courant = Etage_RC;
                      
            // display7SegNumberZero();

while (1) {
     
      
        fonction_switch();

    }
}

/*void __interrupt(high_priority) Isr(void)
{
 
    if ( INTCON3bits.INT1IF == 1)   
         
 {
        if (PORTBbits.RB1==1 )
        {
            LATBbits.LATB7=0;
     LATBbits.LATB6=0;
     LATDbits.LATD1=0;
     LATDbits.LATD0=0;      
   
 
        }else  { 
                    INTCON3bits.INT1IF = 0;
        return ;

        }
            
}
}
*/