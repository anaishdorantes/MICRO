#include "config.h"
#define _XTAL_FREQ 8000000 

#define ROW1 PORTBbits.RB0
#define ROW2 PORTBbits.RB1
#define ROW3 PORTBbits.RB2
#define ROW4 PORTBbits.RB3
#define COL1 PORTBbits.RB4
#define COL2 PORTBbits.RB5
#define COL3 PORTBbits.RB6
#define COL4 PORTBbits.RB7

#define SENSOR_A PORTBbits.RB4
#define SENSOR_B PORTBbits.RB5
#define PLUMA_TRIS TRISCbits.TRISC0
#define PLUMA PORTCbits.RC0
#define LED_VERDE PORTCbits.RC0
#define LED_ROJO PORTCbits.RC1
#define VIGILANTE_BOTON PORTCbits.RC2

uint16_t PIN_correcto = 1234; 
uint16_t PIN_ingresado = 0;
char mensaje_lcd[17];


void inicializar();
void ADC_Init();
uint16_t ADC_Read();
void LCD_Init();
void LCD_Command(char cmd);
void LCD_Write_Char(char data);
void LCD_Write_String(char *str);
void LCD_Write_Nibble(char nibble);
void LCD_Clear();
void LCD_Set_Cursor(char row, char column);
void leerPIN();
void levantarPluma();
void bajarPluma();
void togglePluma();

void main() {
    inicializar();

    while (1) {
        if (SENSOR_A) {
            LCD_Clear();
            LCD_Set_Cursor(1, 1);
            LCD_Write_String("Ingrese PIN:");

            leerPIN();

            if (PIN_ingresado == PIN_correcto) {
                levantarPluma();
            }
        }

        if (SENSOR_B) {
            bajarPluma();
        }

        if (VIGILANTE_BOTON) {
            togglePluma();
        }
    }
}

void inicializar() {
   
    TRISC = 0x00; 
    TRISB = 0xF0;

    LCD_Init();

    ADC_Init();

}

void leerPIN() {
  
    uint16_t pinIngresado = 0;

 
    char teclas[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

   
    int fila, columna;

    for (fila = 0; fila < 4; fila++) {

        switch (fila) {
            case 0:
                ROW1 = 1;
                break;
            case 1:
                ROW2 = 1;
                break;
            case 2:
                ROW3 = 1;
                break;
            case 3:
                ROW4 = 1;
                break;
        }

        for (columna = 0; columna < 4; columna++) {

            if (!COL1 || !COL2 || !COL3 || !COL4) {
 
                pinIngresado = pinIngresado * 10 + (fila * 4 + columna + 1); 
      
                while (!COL1 || !COL2 || !COL3 || !COL4);
            }
        }


        switch (fila) {
            case 0:
                ROW1 = 0;
                break;
            case 1:
                ROW2 = 0;
                break;
            case 2:
                ROW3 = 0;
                break;
            case 3:
                ROW4 = 0;
                break;
        }
    }

    
    PIN_ingresado = pinIngresado;
}

void levantarPluma() {
    PLUMA_TRIS = 0; 
    PLUMA = 1; 
    LED_VERDE = 1;
    LED_ROJO = 0;
}

void bajarPluma() {
    PLUMA_TRIS = 0;
    PLUMA = 0; 
    LED_VERDE = 0;
    LED_ROJO = 1;
}

void togglePluma() {
    PLUMA_TRIS = 0; 
    PLUMA = 1; 
    LED_VERDE = 1;
    LED_ROJO = 1; 
}

void ADC_Init() {
   
    ADCON1bits.PCFG = 0b0000; 
    ADCON0bits.ADON = 1; 
}

uint16_t ADC_Read() {
  
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);


    return ((ADRESH << 8) | ADRESL);
}

void LCD_Init() {

    __delay_ms(20);
    LCD_Command(0x03);
    __delay_ms(5);
    LCD_Command(0x03);
    __delay_ms(11);
    LCD_Command(0x03);
    __delay_ms(1);
    LCD_Command(0x02); 
    LCD_Command(0x28); 
    LCD_Command(0x0C);
    LCD_Command(0x06); 
    LCD_Command(0x01); 
}

void LCD_Command(char cmd) {
 
    PORTDbits.RD0 = 0; 
LCD_Write_Nibble(cmd >> 4);
PORTDbits.RD1 = 1; 
__delay_ms(1);
PORTDbits.RD1 = 0; 
LCD_Write_Nibble(cmd);
PORTDbits.RD1 = 1; 
__delay_ms(1);
PORTDbits.RD1 = 0; 

}

void LCD_Write_Char(char data) {
  
   PORTDbits.RD0 = 1; 
LCD_Write_Nibble(data >> 4);
PORTDbits.RD1 = 1; 
__delay_ms(1);
PORTDbits.RD1 = 0; 
LCD_Write_Nibble(data);
PORTDbits.RD1 = 1; 
__delay_ms(1);
PORTDbits.RD1 = 0; 

}

void LCD_Write_String(char *str) {
    
    while (*str) {
        LCD_Write_Char(*str++);
    }
}

void LCD_Write_Nibble(char nibble) {
   
PORTDbits.RD4 = (nibble >> 0) & 0x01;
PORTDbits.RD5 = (nibble >> 1) & 0x01;
PORTDbits.RD6 = (nibble >> 2) & 0x01;
PORTDbits.RD7 = (nibble >> 3) & 0x01;

}

void LCD_Clear() {
 
    LCD_Command(0x01);
    __delay_ms(2);
}

void LCD_Set_Cursor(char row, char column) {
    
    char position = 0;
    switch (row) {
        case 1:
            position = 0x80 + column - 1;
            break;
        case 2:
            position = 0xC0 + column - 1;
            break;
        default:
            break;
    }
    LCD_Command(position);
}

