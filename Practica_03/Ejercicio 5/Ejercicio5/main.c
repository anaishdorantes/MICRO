

// REPASO 
//LAT- Escribe en el puerto o en el pin 
//TRIS- Declara si es entrada o salida 
//PORT- Lectura en el puerto 

#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 2000000// FRECUENCIA DEL CRISTAL DE 20 MHz
 
                  // 0  1  2  3  4  5    6   7  8   9   10 11 12 13   14  15
                  // 0  1  2  3  4  5    6   7  8   9   A   B   C  D  E   F
int display_array[]={63,6,91,79,102,109,125,7,127,103,119,124,57,94,121,113};


void main(void) {
    ADCON1=0B00001111; 
    TRISD = 0;//Todo puerto D son salidas
    TRISEbits.RE0=0; //RE0 COMO SALIDA
    TRISEbits.RE1=0; //RE1 COMO SALIDA
    
    
    for(int i; i<=15; i++){
        LATD=display_array[i];
        if(i%2 ==0){
            LATEbits.LE0=0;
            LATEbits.LE1=1;
            
        }
        __delay_ms(1000);
    }
    return;
}
