#include <xc.h>
#define _XTAL_FREQ 4000000

// Configuración PIC
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

// Tabla de números para display 7 segmentos (común cátodo)
const unsigned char digitos[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                                   0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void mostrarNumero(int numero) {
    int unidades = numero % 10;
    int decenas = (numero / 10) % 10;
    int centenas = (numero / 100) % 10;
    int millares = (numero / 1000) % 10;

    // Activar dígito 1
    PORTD = 0b0001;
    PORTC = digitos[millares];
    __delay_ms(2);

    // Activar dígito 2
    PORTD = 0b0010;
    PORTC = digitos[centenas];
    __delay_ms(2);

    // Activar dígito 3
    PORTD = 0b0100;
    PORTC = digitos[decenas];
    __delay_ms(2);

    // Activar dígito 4
    PORTD = 0b1000;
    PORTC = digitos[unidades];
    __delay_ms(2);
}

void main(void) {
    int contador = 0;

    // Configurar puertos
    TRISC = 0x00; // Salida para segmentos
    TRISD = 0x00; // Salida para control de dígitos
    PORTC = 0x00;
    PORTD = 0x00;

    while (1) {
        for (int i = 0; i < 50; i++) {
            mostrarNumero(contador);
        }

        contador++;
        if (contador > 9999) {
            contador = 0;
        }
    }
}