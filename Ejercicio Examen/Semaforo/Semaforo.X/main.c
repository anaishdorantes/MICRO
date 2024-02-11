
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 2000000 

int contador = 0; // Contador para el peat�n
int semaforoAutosVerde = 0;
int semaforoAutosRojo = 0;
int semaforoAmarillo = 0;
int semaforoPeatonVerde = 0;
int semaforoPeatonRojo = 0;

void delay_10_seconds() {
    for(int i = 0; i < 1000; i++) { 
        __delay_ms(100);
    }
}

void delay_15_seconds() {
    for(int i = 0; i < 1500; i++) { 
        __delay_ms(100);
    }
}

void delay_5_seconds() {
    for(int i = 0; i < 500; i++) { 
        __delay_ms(100);
    }
}

void main(void) {
    ADCON1 = 0x0F; // Configura el Micro a digital
    TRISB = 0; // Pines B como salida 
    TRISAbits.TRISA0 = 1; // Configura RA0 como entrada para el bot�n
    TRISAbits.TRISA1 = 0; // Configura RA1 como salida para el sem�foro de autos (verde)
    TRISAbits.TRISA2 = 0; // Configura RA2 como salida para el sem�foro de autos (amarillo)
    TRISAbits.TRISA3 = 0; // Configura RA3 como salida para el sem�foro de autos (rojo)
    TRISAbits.TRISA4 = 0; // Configura RA4 como salida para el sem�foro de peatones (verde)
    TRISAbits.TRISA5 = 0;// Configura RA5 como salida para el sem�foro de peatones (rojo)
    
    while(1) {
        // Incrementar el contador de peatones cuando se presiona el bot�n
        if (PORTAbits.RA0 == 1) {
            __delay_ms(50); // Debounce
            while (PORTAbits.RA0 == 1); // Esperar a que el bot�n se libere
            contador++;
        }
        
        // Si el contador de peatones llega a 7, cambiar los sem�foros
        if (contador >= 7) {
            semaforoAutosVerde = 0;
            semaforoAmarillo = 1; // Encender luz amarilla para autos
            LATAbits.LATA1 = semaforoAutosVerde; // Sem�foro de autos (verde)
            LATAbits.LATA2 = semaforoAmarillo; // Sem�foro de autos (amarillo)
            delay_10_seconds();
            semaforoAmarillo = 0; // Apagar luz amarilla
            semaforoAutosRojo= 1;
            semaforoPeatonVerde = 1; // Verde para peatones
            semaforoPeatonRojo = 0;
            LATAbits.LATA2 = semaforoAmarillo; // Apagar el LED de sem�foro de autos (amarillo)
            LATAbits.LATA3 = semaforoAutosRojo; // Rojo para autos
            LATAbits.LATA4 = semaforoPeatonVerde; // Encender el LED de sem�foro de peatones (verde)
            LATAbits.LATA5 = semaforoPeatonRojo; // Encender el LED de sem�foro de peatones (rojo)
            delay_15_seconds();
           
            semaforoAutosVerde = 1; // Verde para autos
            semaforoPeatonVerde = 0; 
            semaforoPeatonRojo = 1; // Rojo para peatones 
            LATAbits.LATA1 = semaforoAutosVerde;// Sem�foro de autos (verde)
            LATAbits.LATA4 = semaforoPeatonVerde; // Apaga LED de sem�foro de peatones (verde)
            LATAbits.LATA5 = semaforoPeatonRojo;
            contador = 0; // Reiniciar el contador de peatones
        } else {
            semaforoAutosVerde = 1; // Verde para autos
            semaforoPeatonRojo = 1; // Rojo para peatones
            semaforoAutosRojo=0;
            LATAbits.LATA1 = semaforoAutosVerde; // Sem�foro de autos (verde)
            LATAbits.LATA2 = semaforoAmarillo; // Apagar el LED de sem�foro de autos (amarillo)
            LATAbits.LATA3 = semaforoAutosRojo; // Sem�foro de autos (rojo)
            LATAbits.LATA5 = semaforoPeatonRojo; // Sem�foro de peatones (rojo)
        }
     
        // Peque�a pausa para estabilidad
        __delay_ms(100); 
    }
    
    return; // Retorna 0 al finalizar el programa
}
