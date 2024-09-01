#include "Control_Elevator.h"
#include "eusart1.h"
#define _XTAL_FREQ  16000000

void controlLowSpeedRelayForInitialisation(){
    LATBbits.LATB7 = 0;
    LATBbits.LATB6 = 1; 
  
}

 bool KRC = false ;  
 int relayStatusInit=0;
  int relayStatus =0;
 int relayStatus1=0;
 int relayStatus2=0 ; 
 int relayStatus3=0;
 
 bool checkContactorStatusForIntialisation() {
    __delay_ms(1000); // Attendez un court instant pour permettre au contacteur de s'activer complètement
    return PORTDbits.RD7 ; // Lire l'état du contacteur depuis la broche RB1
}
  
bool checkContactorStatus() {
    return PORTDbits.RD7 ; // Lire l'état du contacteur depuis la broche RB1
}

bool checkElevatorUpRelay (){
     send_string("z");
    return PORTBbits.RB5 ; 
}
bool checkElevatorDownRelay (){
     send_string("x");
    return PORTBbits.RB4 ; 
}
bool checkElevatorLM1 (){
    return PORTDbits.RD6 ; 
}

bool checkElevatorLM2 (){
    return PORTBbits.RB3 ; 
}
 
 void controlElevatorDownRelayForIntialisation(){
 while (!KRC) {
        
        relayStatusInit = 1;
       
         
        bool contactorStatusInit = checkContactorStatusForIntialisation();
        
        // Comparer le retour de la fonction avec l'état du contacteur
        if (contactorStatusInit == 1 && relayStatusInit == 1) {
             LATDbits.LATD0 = 0; // Active le contacteur
             LATDbits.LATD1 = 1; 
            KRC = true; // Définir la variable KRC à true pour indiquer que le contacteur a été activé
        } else {
          //  //////lcd_writemessage(1, 1, "Error:1                                           ");
            ////////lcd_writemessage(1, 1, "Check_KRC                                           ");

        }
    }
  KRC = false;
}
void Close_Door() {
    LATEbits.LATE0 = 0;
    LATEbits.LATE1 = 1;
          send_string("A");
          
         
   
}
void disableMotorRelays() {
    LATBbits.LATB7= 0;
    LATBbits.LATB6 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1=0;
   
}

void ErrorSystemSecurity(){
    disableMotorRelays();
    Close_Door();
  
}
// Fonction pour commander le contacteur du moteur
int controlElevatorUpRelay() {
    while (!KRC)
    {
        
    relayStatus = 1;
        
    bool contactorStatus = checkContactorStatus(); // Vérifier l'état réel du contacteur
    bool Status818=checkElevatorUpRelay (); 
    bool Status817=checkElevatorDownRelay ();
    bool LM2=checkElevatorLM2 ();
    bool LM1=checkElevatorLM1 ();
    
    
    if (contactorStatus == 0 && relayStatus == 0 && Status818==0 && Status817 == 0 && LM1==0 && LM2==0     ) {    
       ErrorSystemSecurity();
             send_string("12");
      // //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        ////////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        ////////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2      ");                                          
                   
    } else if (contactorStatus == 0 && relayStatus == 0 && Status818==0 && Status817 == 0 && LM1==0 && LM2==1 ) {
       ErrorSystemSecurity();
               send_string("12");
       ////////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        ////////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
     //__delay_ms(500);
       // //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2      ");                                            
    } else if (contactorStatus == 0 && relayStatus == 0 && Status818==0 && Status817 == 0 && LM1==1 && LM2==0   ) { 
         ErrorSystemSecurity();
                 send_string("12");
       ////////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        ////////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
     //__delay_ms(500);
       // //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2   ");                                                 
            
    } else if (contactorStatus == 0 && relayStatus == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
     ErrorSystemSecurity();
             send_string("12");
       ////////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
       // //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
     //__delay_ms(500);
       // //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2  ");                                                 
            
    } else if (contactorStatus == 0 && relayStatus == 0 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
       ErrorSystemSecurity();
               send_string("13");
        
       ////////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        ////////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
     //__delay_ms(500);
       // //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
       //     //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
        
    }else if (contactorStatus == 0 && relayStatus == 0 && Status818==0 && Status817 == 1 && LM1 == 0 && LM2 ==1   ) { 
         ErrorSystemSecurity();
                 send_string("13");
       ////////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
      //  //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
     //__delay_ms(500);
       // //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
       //     //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
        
    } else if (contactorStatus == 0 && relayStatus == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
       ErrorSystemSecurity();
               send_string("12");
       ////////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
       // //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
     //__delay_ms(500);
       // //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
       //     //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
            
    
}else if (contactorStatus == 0 && relayStatus == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
       ErrorSystemSecurity();
               send_string("12");
       ////////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
       // //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
     //__delay_ms(500);
      //  //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
       //     //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
    
}else if (contactorStatus == 0 && relayStatus == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
       
       ErrorSystemSecurity();
               send_string("12");
       ////////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
       // //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
    // __delay_ms(500);
      //  //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
      //      //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
        //    //  __delay_ms(500);          
        //   //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");

}else if (contactorStatus == 0 && relayStatus == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
    ErrorSystemSecurity();
            send_string("12");
     //  //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
     //   //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
    // __delay_ms(500);
    //    //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
    //        //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
    //        //  __delay_ms(500);          
    //       //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
            
}else if (contactorStatus == 0 && relayStatus == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
        
    ErrorSystemSecurity();
            send_string("13");
    //   //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
    //    //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
    // __delay_ms(500);
    //    //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
    //        //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
    //        //  __delay_ms(500);          
    //       //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
            
}else if (contactorStatus == 0 && relayStatus == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
                ErrorSystemSecurity();
                        send_string("13");
    //   //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
    //    //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
    // __delay_ms(500);
    //    //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
    //        //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
    //        //  __delay_ms(500);          
    //       //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");    
}else if (contactorStatus == 0 && relayStatus == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
            ErrorSystemSecurity();
                    send_string("13");
    //   //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
    //    //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
    // __delay_ms(500);
    //    //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
    //        //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
    //        //  __delay_ms(500);          
    //       //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");    
}else if (contactorStatus == 0 && relayStatus == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
          ErrorSystemSecurity();
                  send_string("13");
    //   //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
    //    //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
    // __delay_ms(500);
    //    //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
    //        //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
    //        //  __delay_ms(500);          
    //       //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
        
    ErrorSystemSecurity();
            send_string("13");
    //   //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
    //    //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
    // __delay_ms(500);
    //    //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
    //        //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
    //        //  __delay_ms(500);          
    //       //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
        
     ErrorSystemSecurity();
             send_string("13");
    //   //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
    //    //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
    // __delay_ms(500);
    //    //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
    //        //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
    //        //  __delay_ms(500);          
    //       //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        
       ErrorSystemSecurity();
               send_string("12");
    //   //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
  ErrorSystemSecurity();
          send_string("13");
 //      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
   ErrorSystemSecurity();
           send_string("13");
 //      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");       
 
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
  ErrorSystemSecurity();
          send_string("12");
 //      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
 //           //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
 ErrorSystemSecurity();
 //      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
   //         //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
                      
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
        ErrorSystemSecurity();
   //    //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
   //         //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
        ErrorSystemSecurity();
   //    //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
   //         //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
   ErrorSystemSecurity();
   //    //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
   //         //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        ErrorSystemSecurity();
   //    //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
   //         //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
            ErrorSystemSecurity();
   //    //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
   //         //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0  ) { 
         ErrorSystemSecurity();
   //    //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
   //         //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}  else if (contactorStatus == 0 && relayStatus == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
      ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 0 && relayStatus == 1 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
      ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
     
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
     
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
             ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==0 && Status817 == 1 && LM1 == 0 && LM2==0   ) { 
       ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
              ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
              ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
        
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
            
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
         
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
      
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 

          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
        //////lcd_writemessage(2,1, "Error4:Check_Relay817 ");
      //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                             ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                                ");
                                                                  

}else if (contactorStatus == 1 && relayStatus == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
            ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
        //////lcd_writemessage(2,1, "Error4:Check_Relay817 ");
      //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                             ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                                ");
                                                                  

}else if (contactorStatus == 1 && relayStatus == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        LATDbits.LATD0 = 1; // Active le contacteur
    LATDbits.LATD1 = 0; 
    
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
        LATDbits.LATD0 = 1; // Active le contacteur
    LATDbits.LATD1 = 0;  
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
        LATDbits.LATD0 = 1; // Active le contacteur
    LATDbits.LATD1 = 0;  
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
    LATDbits.LATD0 = 1; // Active le contacteur
    LATDbits.LATD1 = 0; 
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
      ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817                                           ");
            
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
        
      ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817                                           ");
   
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
 ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
    ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
     ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
     ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==1 && Status817 == 1&& LM1 ==0 && LM2==1   ) { 
       ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else if (contactorStatus == 1 && relayStatus == 1 && Status818==1 && Status817 ==1 && LM1 ==1 && LM2==0   ) { 
        ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else {  
     //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                ");
        //////lcd_writemessage(2,1, "Error2:Check_Relay_LM1                                          ");
          //  __delay_ms(500);
           //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                            ");
 //////lcd_writemessage(2, 1, "Error4:Check_Relay817 ");
 __delay_ms(500); 
   //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");         
    //////lcd_writemessage(1, 1, "Error6:Check_Relay                                           ");
     
}
    }  
    KRC = false;
    }   
 
int controlElevatorDownRelay() {

    while (!KRC   )
    {
        
    relayStatus1 = 1;
      
    bool contactorStatus = checkContactorStatus(); // Vérifier l'état réel du contacteur
    bool Status818=checkElevatorUpRelay (); 
    bool Status817=checkElevatorDownRelay ();
    bool LM2=checkElevatorLM2 ();
    bool LM1=checkElevatorLM1 ();
    
    
    if (contactorStatus == 0 && relayStatus1 == 0 && Status818==0 && Status817 == 0 && LM1==0 && LM2==0     ) {    
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2      ");                                          
                   
    } else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==0 && Status817 == 0 && LM1==0 && LM2==1 ) {
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2      "); 
    }                                              
    else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==0 && Status817 == 0 && LM1==1 && LM2==0   ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2   ");                                                 
            
    } else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
     ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2  ");                                                 
            
    } else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
        
    }else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==0 && Status817 == 1 && LM1 == 0 && LM2 ==1   ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
        
    } else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
            
    
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
    
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
       
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
  
            
    
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
            
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
        
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
            
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
                ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");    
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");    
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
          ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
        
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus1 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
        
     ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
  ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
   ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");       
 
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
  ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
 ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
                      
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
   ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0  ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}  else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
      ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 0 && relayStatus1 == 1 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
      ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
     
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
     
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
             ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==0 && Status817 == 1 && LM1 == 0 && LM2==0   ) { 
       ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
              ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
              ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
        
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
            
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
         
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
      
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 

          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
        //////lcd_writemessage(2,1, "Error4:Check_Relay817 ");
      //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                             ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                                ");
                                                                  

}else if (contactorStatus == 1 && relayStatus1 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
            ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
        //////lcd_writemessage(2,1, "Error4:Check_Relay817 ");
      //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                             ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                                ");
                                                                  

}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        LATDbits.LATD1 = 1; // Active le contacteur
    LATDbits.LATD0 = 0; 
    
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
        LATDbits.LATD1 = 1; // Active le contacteur
    LATDbits.LATD0 = 0;  
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
        LATDbits.LATD1 = 1; // Active le contacteur
    LATDbits.LATD0 = 0;  
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
    LATDbits.LATD1 = 1; // Active le contacteur
    LATDbits.LATD0 = 0; 
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
      ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817                                           ");
            
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
        
      ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817                                           ");
   
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
 ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
    ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
     ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
     ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==1 && Status817 == 1&& LM1 ==0 && LM2==1   ) { 
       ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else if (contactorStatus == 1 && relayStatus1 == 1 && Status818==1 && Status817 ==1 && LM1 ==1 && LM2==0   ) { 
        ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else {  
     //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                ");
        //////lcd_writemessage(2,1, "Error2:Check_Relay_LM1                                          ");
          //  __delay_ms(500);
           //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                            ");
 //////lcd_writemessage(2, 1, "Error4:Check_Relay817 ");
 __delay_ms(500); 
   //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");         
    //////lcd_writemessage(1, 1, "Error6:Check_Relay                                           ");
     
}
   
    } 
    KRC = false;
    }   
int controlHighSpeedRelay() {
    while (!KRC)
    {
        
    relayStatus2 = 1;
      
    bool contactorStatus = checkContactorStatus(); // Vérifier l'état réel du contacteur
    bool Status818=checkElevatorUpRelay (); 
    bool Status817=checkElevatorDownRelay ();
    bool LM2=checkElevatorLM2 ();
    bool LM1=checkElevatorLM1 ();
    
    
    if (contactorStatus == 0 && relayStatus2 == 0 && Status818==0 && Status817 == 0 && LM1==0 && LM2==0     ) {    
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2      ");                                          
                   
    } else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==0 && Status817 == 0 && LM1==0 && LM2==1 ) {
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2      ");                                            
    } else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==0 && Status817 == 0 && LM1==1 && LM2==0   ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2   ");                                                 
            
    } else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
     ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2  ");                                                 
            
    } else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
        
    }else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==0 && Status817 == 1 && LM1 == 0 && LM2 ==1   ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
        
    } else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
            
    
}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
    
}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
       
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");

}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
            
}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
        
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
            
}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
                ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");    
}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");    
}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
          ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
        
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus2 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
        
     ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
  ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
   ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");       
 
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
  ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
 ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
                      
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
   ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0  ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}  else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
      ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 0 && relayStatus2 == 1 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
      ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
     
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
     
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
             ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==0 && Status817 == 1 && LM1 == 0 && LM2==0   ) { 
       ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
              ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
              ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
        
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
            
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
         
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
      
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 

          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
        //////lcd_writemessage(2,1, "Error4:Check_Relay817 ");
      //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                             ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                                ");
                                                                  

}else if (contactorStatus == 1 && relayStatus2 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
            ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
        //////lcd_writemessage(2,1, "Error4:Check_Relay817 ");
      //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                             ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                                ");
                                                                  

}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        LATBbits.LATB7 = 1; // Active le contacteur
    LATBbits.LATB6 = 0; 
    
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
        LATBbits.LATB7 = 1; // Active le contacteur
    LATBbits.LATB6 = 0;  
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
        LATBbits.LATB7 = 1; // Active le contacteur
    LATBbits.LATB6 = 0;  
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
    LATBbits.LATB7 = 1; // Active le contacteur
    LATBbits.LATB6 = 0; 
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
      ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817                                           ");
            
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
        
      ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817                                           ");
   
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
 ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
    ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
     ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
     ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==1 && Status817 == 1&& LM1 ==0 && LM2==1   ) { 
       ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else if (contactorStatus == 1 && relayStatus2 == 1 && Status818==1 && Status817 ==1 && LM1 ==1 && LM2==0   ) { 
        ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else {  
     //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                ");
        //////lcd_writemessage(2,1, "Error2:Check_Relay_LM1                                          ");
          //  __delay_ms(500);
           //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                            ");
 //////lcd_writemessage(2, 1, "Error4:Check_Relay817 ");
 __delay_ms(500); 
   //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");         
    //////lcd_writemessage(1, 1, "Error6:Check_Relay                                           ");
     
}
    }  
    KRC = false;
    }   
 
int controlLowSpeedRelay() {

    while (!KRC   )
    {
        
    relayStatus3 = 1;
    
    bool contactorStatus = checkContactorStatus(); // Vérifier l'état réel du contacteur
    bool Status818=checkElevatorUpRelay (); 
    bool Status817=checkElevatorDownRelay ();
    bool LM2=checkElevatorLM2 ();
    bool LM1=checkElevatorLM1 ();
    
    
    if (contactorStatus == 0 && relayStatus3 == 0 && Status818==0 && Status817 == 0 && LM1==0 && LM2==0     ) {    
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2      ");                                          
                   
    } else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==0 && Status817 == 0 && LM1==0 && LM2==1 ) {
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2      ");  
    }                                              
    else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==0 && Status817 == 0 && LM1==1 && LM2==0   ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2   ");                                                 
            
    } else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
     ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2  ");                                                 
            
    } else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
        
    }else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==0 && Status817 == 1 && LM1 == 0 && LM2 ==1   ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
        
    } else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
            
    
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            
            
    
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
       
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
  
      
    
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
            
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
        
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
            
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
                ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");    
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");    
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
          ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
        
    ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus3 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
        
     ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                          ");
        //////lcd_writemessage(2, 1, "Error2:Check_Relay_LM1                                               ");
   //  __delay_ms(500);
        //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                                    ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
            //  __delay_ms(500);          
           //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                            ");
            
}else if (contactorStatus == 0 && relayStatus3== 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        
       ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
  ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
   ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");       
 
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
  ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
 ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
                      
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
   ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
           
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0  ) { 
         ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}  else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                         "); 
           
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
      ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
            ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 0 && relayStatus3 == 1 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
      ErrorSystemSecurity();
       //////lcd_writemessage(1, 1, "Error1:Check_KRC                                             ");
            //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                         "); 
          //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                          ");
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
     
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
     ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
     
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
             ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                             ");
    
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==0 && Status817 == 1 && LM1 == 0 && LM2==0   ) { 
       ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
              ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
              ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error4:Check_Relay817                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
        
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
            
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
         
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
      
          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
             //////lcd_writemessage(2, 1, "Error5:Check_Relay818                                             ");
   //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error6:Check_Relay                                                ");
   
}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 

          ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
        //////lcd_writemessage(2,1, "Error4:Check_Relay817 ");
      //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                             ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                                ");
                                                                  

}else if (contactorStatus == 1 && relayStatus3 == 0 && Status818==1 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
            ErrorSystemSecurity();
      //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                  ");
        //////lcd_writemessage(2,1, "Error4:Check_Relay817 ");
      //  __delay_ms(500);
             //////lcd_writemessage(1, 1, "Error5:Check_Relay818                                             ");
             //////lcd_writemessage(2, 1, "Error6:Check_Relay                                                ");
                                                                  

}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
        LATBbits.LATB6 = 1; // Active le contacteur
    LATBbits.LATB7 = 0; 
    
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==0 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
        LATBbits.LATB6 = 1; // Active le contacteur
    LATBbits.LATB7 = 0;  
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
        LATBbits.LATB6 = 1; // Active le contacteur
    LATBbits.LATB7 = 0;  
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==0 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
    LATBbits.LATB6 = 1; // Active le contacteur
    LATBbits.LATB7 = 0; 
      KRC=true ;
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
        
      ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817                                           ");
            
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==0 && Status817 == 1 && LM1 ==0 && LM2==1   ) { 
        
      ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817                                           ");
   
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==0   ) { 
 ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==0 && Status817 == 1 && LM1 ==1 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==0   ) { 
    ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==1 && Status817 == 0 && LM1 ==0 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==0   ) { 
     ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==1 && Status817 == 0 && LM1 ==1 && LM2==1   ) { 
         ErrorSystemSecurity();
            //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==1 && Status817 == 1 && LM1 ==0 && LM2==0   ) { 
     ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==1 && Status817 == 1&& LM1 ==0 && LM2==1   ) { 
       ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else if (contactorStatus == 1 && relayStatus3 == 1 && Status818==1 && Status817 ==1 && LM1 ==1 && LM2==0   ) { 
        ErrorSystemSecurity();
   //////lcd_writemessage(1, 1, "Error4:Check_Relay817 ");
   //////lcd_writemessage(2, 1, "Error5:Check_Relay818 ");
              
}else {  
     //////lcd_writemessage(1, 1, "Error1:Check_KRC                                                ");
        //////lcd_writemessage(2,1, "Error2:Check_Relay_LM1                                          ");
          //  __delay_ms(500);
           //////lcd_writemessage(1, 1, "Error3:Check_Relay_LM2                                            ");
 //////lcd_writemessage(2, 1, "Error4:Check_Relay817 ");
 __delay_ms(500); 
   //////lcd_writemessage(1, 1, "Error5:Check_Relay818 ");         
    //////lcd_writemessage(1, 1, "Error6:Check_Relay                                           ");
     
}
   
    } 
    KRC = false;
    }   

void EnableSpeakers (){
    LATDbits.LATD7 = 0x01;
}
void DisableSpeakers(){
   LATDbits.LATD7=0x00; 
}

void EnableLightingAndFun(){
    
    LATEbits.LATE2 = 0x01;
    
}

void DisableLightingAndFun(){
    
    LATEbits.LATE2 = 0x00;
    
}

void Open_Door() {
    LATEbits.LATE0 = 1;
    LATEbits.LATE1 = 0;
      send_string("B");
          
    
    __delay_ms(200);
}





void Close_DoorForIntialisation() {
    LATEbits.LATE0 = 0;
    LATEbits.LATE1 = 1;
          send_string("10");
          
    __delay_ms(200);      
}




void display7SegNumberZero() {
    LATDbits.LATD5 = 1;
    LATDbits.LATD4 = 1;
  
    LATCbits.LATC5 = 1;
    LATDbits.LATD3 = 1;
    LATDbits.LATD2 = 0;    
}
void display7SegNumberOne() {
    LATDbits.LATD5 = 0;
    LATDbits.LATD4 = 0;
    
    
    LATCbits.LATC5 = 0;
    LATDbits.LATD3 = 0;
    LATDbits.LATD2 = 0;    
} 
void display7SegNumberTwo() { // Verifier 
    LATDbits.LATD5 = 1;
    LATDbits.LATD4 = 1;
  
    LATCbits.LATC5 = 1;
    LATDbits.LATD3 = 0;
    LATDbits.LATD2 = 1; 
    
}
void display7SegNumberThree() { // Verifier 
    LATDbits.LATD5 = 0;
    LATDbits.LATD4 = 1;
  
    LATCbits.LATC5 = 1;
    LATDbits.LATD3 = 0;
    LATDbits.LATD2 = 1; 
    
}

void initialisation_ascenseur() {
    while (!PORTBbits.RB4 ) 
    {
       
     
        Close_Door();
        controlElevatorDownRelayForIntialisation();
        controlLowSpeedRelayForInitialisation();
        
        // Vérifier si le signal RB5 est élevé (high)
        if (PORTBbits.RB4 == 1) {
           disableMotorRelays();
                
        }
        
    }
    
}


