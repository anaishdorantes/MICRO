
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 20000000
int display_array[]= {63,6,91,79,102,109,124,71,127,103,119,124,57,94,121,113};

void main(void) {
    ADCON1 = 0B00001111; 
    TRISD = 0B11110000;
    TRISB = 0;
    while(1){
        __delay_ms(10);
        LATDbits.LD0 = 1;
        LATDbits.LD1 = 0;
        LATDbits.LD2 = 0;
        LATDbits.LD3 = 0;
        
        if(PORTDbits.RD7==1)
        {
           
            LATB = display_array[3];
        }
        if(PORTDbits.RD6==1)
        {
           
            LATB = display_array[2];
        }
        if(PORTDbits.RD5==1)
        {
            
            LATB = display_array[1];
        }
        if(PORTDbits.RD4==1)
        {
           
            LATB = display_array[10];
        }
        __delay_ms(10);
        LATDbits.LD0 = 0;
        LATDbits.LD1 = 1;
        LATDbits.LD2 = 0;
        LATDbits.LD3 = 0;
        if(PORTDbits.RD7==1)
        {
            
            LATB = display_array[6];
        }
        if(PORTDbits.RD6==1)
        {
            
            LATB = display_array[5];
        }
        if(PORTDbits.RD5==1)
        {
            
            LATB = display_array[4];
        }
        if(PORTDbits.RD4==1)
        {
            
            LATB = display_array[11];
        }
        __delay_ms(10);
        LATDbits.LD0 = 0;
        LATDbits.LD1 = 0;
        LATDbits.LD2 = 1;
        LATDbits.LD3 = 0;
        if(PORTDbits.RD7==1)
        {
            
            LATB = display_array[9];
        }
        if(PORTDbits.RD6==1)
        {
            
            LATB = display_array[8];
        }
        if(PORTDbits.RD5==1)
        {
           
            LATB = display_array[7];
        }
        if(PORTDbits.RD4==1)
        {
            
            LATB = display_array[12];
        }
        __delay_ms(10);
        LATDbits.LD0 = 0;
        LATDbits.LD1 = 0;
        LATDbits.LD2 = 0;
        LATDbits.LD3 = 1;
        if(PORTDbits.RD7==1)
        {
            
            LATB = display_array[15];
        }
        if(PORTDbits.RD6==1)
        {
           
            LATB = display_array[0];
        }
        if(PORTDbits.RD5==1)
        {
           
            LATB = display_array[14];
        }
        if(PORTDbits.RD4==1)
        {
            LATB = display_array[13];
        }
        }
        
            
    
    
    
    return;
}
