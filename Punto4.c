#include <xc.h>
#define _XTAL_FREQ 8000000

// CONFIG
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

const char segmentos[10] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
};

unsigned char contador = 0;
unsigned char corriendo = 0;

void mostrar_display(unsigned char numero) {
    unsigned char unidades = numero % 10;
    unsigned char decenas = numero / 10;

    for (int i = 0; i < 50; i++) {
        // Decenas
        PORTA = 0b00000010;  // Encender display 2
        PORTD = segmentos[decenas];
        __delay_ms(5);

        // Unidades
        PORTA = 0b00000001;  // Encender display 1
        PORTD = segmentos[unidades];
        __delay_ms(5);
    }
}

void main(void) {
    TRISD = 0x00; // Segmentos
    TRISA = 0x00; // Control displays
    TRISB = 0xFF; // Entradas para botones
    PORTA = 0;
    PORTD = 0;

    while (1) {
        // Leer botones
        if (RB0 == 0) { __delay_ms(200); corriendo = 1; } // Iniciar
        if (RB1 == 0) { __delay_ms(200); corriendo = 0; } // Pausar
        if (RB2 == 0) { __delay_ms(200); corriendo = 1; } // Reanudar
        if (RB3 == 0) { __delay_ms(200); contador = 0; corriendo = 0; } // Reset

        mostrar_display(contador);

        // Aumentar contador si está corriendo
        if (corriendo) {
            __delay_ms(1000);
            contador++;
            if (contador > 99)
                contador = 0;
        }
    }
}
