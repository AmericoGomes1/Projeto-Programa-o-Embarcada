#include <pic18f4520.h> 
#include "lcd.h"
#include "config.h"
#include "keypad.h"
#include "serial.h"
#include "bits.h"

#define ON 0x0F
#define L_CLR 0x01

void temp(unsigned int X) {

    unsigned int i;
    for (i = 0; i < X; i++) {
        volatile unsigned char j, k;
        for (j = 0; j < 41; j++) {
            for (k = 0; k < 3; k++);

        }
    }
}

void main(void) {
    unsigned long int cont = 1, rels = 1;
    unsigned int tecla = 16;

    lcdPosition(1, 0);
    lcdInit();
    kpInit();
    lcdString("Impressora:");
    for (;;) {
        cont++;
        rels++;
        lcdPosition(1, 0);

        lcdString("Copias:");
        lcdChar(((rels / 10000000) % 10) + 48);
        lcdChar(((cont/ 10000000) % 10) + 48);



        kpDebounce();

        if (kpRead() != tecla) {
            tecla = kpRead();

            if (bitTst(tecla, 9)) cont += 10000000;
            if (bitTst(tecla, 6)) rels += 10000000;
            if (bitTst(tecla, 8)) rels -= 10000000;
            if (bitTst(tecla, 4)) cont -= 10000000;
            if (bitTst(tecla, 7)) {
                lcdCommand(L_CLR);
                lcdString("Imprimindo...");
                TRISD = 0x00;
                PORTD = 0x01;

                temp(5000);
                PORTD = 0x02;

                temp(10000);
                PORTD = 0x03;
                lcdCommand(L_CLR);
                lcdString("Impressora:");
               
            }
        }

    }

}

