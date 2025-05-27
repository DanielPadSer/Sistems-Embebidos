#include <xc.h>
#define _XTAL_FREQ 8000000

// Configuración de bits del sistema (puedes adaptarlos a tu entorno)
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

// Solo los 5 valores de la tabla en código Gray de 3 bits
const unsigned char grayCode[5] = {
    0b000, // 0
    0b001, // 1
    0b011, // 2
    0b010, // 3
    0b110  // 4
};

void main(void) {
    TRISB = 0b11111000; // RB0-RB2 como salida (3 bits para LEDs)
    PORTB = 0;

    while (1) {
        for (char i = 0; i < 5; i++) {
            PORTB = (PORTB & 0b11111000) | (grayCode[i] & 0x07); // Enciende solo RB0-RB2
            __delay_ms(1000); // Espera de 1 segundo
        }
    }
}
