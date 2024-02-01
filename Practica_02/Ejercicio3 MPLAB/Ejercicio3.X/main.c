
#include <xc.h>
#include "config.h"

#define _XTAL_FREQ 2000000 // Frecuencia del cristal de 2 MHz

int contador = 0;

void main(void) {
    ADCON1 = 0x0F; // Configuracion del Micro a digital
    TRISB = 0; // Configurar todos los pines B como salidas
    TRISAbits.RA0 = 1; // Botón que suma en binario 
    TRISAbits.RA1 = 1; // Botón que resta en binario 
    TRISAbits.RA2 = 1; // Botón que reinicia

    while (1) {
        // Botón que suma 
        if (PORTAbits.RA0 == 1) {
            __delay_ms(50); // sirve para que no tenga error al precionar el boton y no detecte mas de un click 
            while (PORTAbits.RA0 == 1); // espera a que el botón se libere
            contador++;
            if (contador > 255) {
                contador = 0; // Seguro en el que si el contador está en el 255 y se le suma 1 de nuevo debe de regresar a 0
            }
        }

        // que resta 
        if (PORTAbits.RA1 == 1) {
            __delay_ms(50); 
            while (PORTAbits.RA1 == 1); 
            contador--;
            if (contador < 0) {
                contador = 255; // Seguro en el que si el contador está en 0 y se le resta 1 de nuevo, se debe de poner el valor a 255
            }
        }

        // Botón de reinicio 
        if (PORTAbits.RA2 == 1) {
            __delay_ms(50); 
            while (PORTAbits.RA2 == 1); 
            contador = 0;
        }

        // Muestra los valores en binario en el puerto B
        LATB = contador;

        __delay_ms(200);
    }

    return;
}

