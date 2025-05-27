#define _XTAL_FREQ 20000000

#include <xc.h>

// CONFIGURACIÓN DE BITS
#pragma config FOSC = HS        // Oscilador HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

// Función para convertir binario a código Gray
unsigned char bin_to_gray(unsigned char num) {
    return num ^ (num >> 1);
}

void main(void) {
    TRISB &= 0xF0;  // Configurar RB0-RB3 como salidas (bits bajos)
    PORTB &= 0xF0;  // Apagar RB0-RB3 sin afectar RB4-RB7

    unsigned char i;
    while(1) {
        for(i = 0; i < 16; i++) {
            unsigned char gray = bin_to_gray(i) & 0x0F;  // Solo 4 bits
            PORTB = (PORTB & 0xF0) | gray;               // Actualiza solo RB0-RB3
            __delay_ms(500);
        }
    }
}

