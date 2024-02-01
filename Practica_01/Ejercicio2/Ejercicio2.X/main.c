
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 2000000 // Frecuencia del cristal de 2 MHz

void main(void) {
    ADCON1 = 0x0F; // Configura el Micro a digital
    TRISB = 0; // Configurar todos los pines de B como salidas
    TRISAbits.RA0 = 1; // Botón para iniciar el corrimiento de derecha a izq

    while (1) {
        // Espera a que se presione el botón
        while (PORTAbits.RA0 == 1);

        // corre hacia la derecha pero empieza con 3 LEDs encendidos
        for (int i = 0; i < 8; i++) {
            LATB = (1 << i) | (1 << (i + 1)) | (1 << (i + 2));
            __delay_ms(500);
        }

        // corre hacia la izquierda
        for (int i = 8; i >= 0; i--) {
            LATB = (1 << i) | (1 << (i + 1)) | (1 << (i + 2));
            __delay_ms(500);
        }
        
        while (PORTAbits.RA0 == 0);
    }

    return;
}

