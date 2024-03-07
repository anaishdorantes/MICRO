
    #include <xc.h>
    #include "config.h"
    #define _XTAL_FREQ 20000000

    void inicializar_ADC(void);
    int leer_ADC(int);

    int valor1 = 0;
    int valor2 = 0;
    int promedio = 0;
    int decenas_promedio = 0;
    int unidades_promedio = 0;
    int resto_promedio = 0;
    int estado_bomba = 0;
    int diferencia = 0;
    int display_array[] = {63,6,91,79,102,109,124,71,127,103,119,124,57,94,121,113};

    void main(void) {
        TRISB = 0;
        TRISD = 0b11110000;
        inicializar_ADC();
        while(1){
            valor1 = leer_ADC(0);
            valor2 = leer_ADC(1);
            promedio = ((valor1 + valor2) / 2) / 10.23;

            decenas_promedio = promedio / 10; 
            LATB = display_array[decenas_promedio];
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 1;
            __delay_ms(50);
            unidades_promedio = promedio - (decenas_promedio * 10);
            LATB = display_array[unidades_promedio];
            LATDbits.LATD0 = 1;
            LATDbits.LATD1 = 0;
            __delay_ms(50);

            if(promedio > 70) {
                LATDbits.LATD2 = 1;
            } else {
                LATDbits.LATD2 = 0;
            }
        }

        return;
    }

    void inicializar_ADC(void){
        TRISA = 0xFF;
        ADCON1 = 0x0D;
        ADCON2 = 0xB5;
        ADRESH = 0;
        ADRESL = 0;
    }

    int leer_ADC(int canal){
        int digital = 0;

        ADCON0 = (ADCON0 & 0b11000011)|((canal << 2) & 0b00111100);

        ADCON0 |=((1<<ADON)| (1 << GO));

        while(ADCON0bits.GO_nDONE==1);

        digital = (ADRESH*256)|(ADRESL);

        return digital;
    }
