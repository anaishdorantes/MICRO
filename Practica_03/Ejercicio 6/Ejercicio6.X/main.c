
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 20000000
//0 1 2 3 4 5 6 7 8 9 A b C d e F
int display_array[]= {63,6,91,79,102,109,124,71,127,103,119,124,57,94,121,113};

void main(void) {
    while(1){
        ADCON1 = 0B00001111; 
        TRISB = 0; //SALIDA
        TRISD = 1;//ENTRADA
        if(PORTD == 0){
            LATB = display_array[0];
        }
        if(PORTD == 1){
            LATB = display_array[1];
        }
        if(PORTD == 2){
            LATB = display_array[2];
        }
        if(PORTD == 3){
            LATB = display_array[3];
        }
        if(PORTD == 4){
            LATB = display_array[4];
        }
        if(PORTD == 5){
            LATB = display_array[5];
        }
        if(PORTD == 6){
            LATB = display_array[6];
        }
        if(PORTD == 7){
            LATB = display_array[7];
        }
        if(PORTD == 8){
            LATB = display_array[8];
        }
        if(PORTD == 9){
            LATB = display_array[9];
        }
        if(PORTD == 10){
            LATB = display_array[10];
        }
        if(PORTD == 11){
            LATB = display_array[11];
        }
        if(PORTD == 12){
            LATB = display_array[12];
        }
        if(PORTD == 13){
            LATB = display_array[13];
        }
        if(PORTD == 14){
            LATB = display_array[14];
        }
        if(PORTD == 15){
            LATB = display_array[15];
        }
    }
    return;
}