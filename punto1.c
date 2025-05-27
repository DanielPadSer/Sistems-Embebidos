#include <xc.h>
#include <stdint.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

void main(void) {
    TRISB = 0x00;
    TRISA = 0x01;     // RA0 como entrada
    PORTB = 0x00;

    uint8_t modo = 0;
    uint8_t paso = 0;
    uint8_t btn_ant = 0;

    while (1) {
        uint8_t btn = RA0;

        // Cambio de modo al detectar flanco de subida
        if (btn == 1 && btn_ant == 0) {
            modo++;
            if (modo > 2) modo = 0;
            paso = 0;
        }
        btn_ant = btn;

        // Ejecutar paso según modo
        switch (modo) {
            case 0:
                PORTB = 1 << paso;
                paso++;
                if (paso >= 8) paso = 0;
                break;
            case 1:
                PORTB = 1 << (7 - paso);
                paso++;
                if (paso >= 8) paso = 0;
                break;
            case 2:
                switch (paso) {
                    case 0: PORTB = 0x18; break;
                    case 1: PORTB = 0x24; break;
                    case 2: PORTB = 0x42; break;
                    case 3: PORTB = 0x81; break;
                }
                paso++;
                if (paso >= 4) paso = 0;
                break;
        }

        __delay_ms(3000);
    }
}