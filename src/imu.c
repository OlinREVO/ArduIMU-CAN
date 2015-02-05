#define F_CPU (1000000L) //pre-defining CPU speed
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "api.h"
#include "uart.h"


// TODO: change this method for each of the demo nodes
void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen) {
    uint8_t cmd = msg[0];
    int ledOn = cmd & 0b01;
    int whichLED = cmd & 0b10;
    if (whichLED) {
        if (ledOn) {
            PORTB |= _BV(PB4);
        } else {
            PORTB &= ~(_BV(PB4));
        }
    } else {
        if (ledOn) {
            PORTB |= _BV(PB6);
        } else {
            PORTB &= ~(_BV(PB6));
        }
    }
}



int main (void) {
    DDRB |= 0xFF; // set all PORTB pins for output
    /*Same as saying*/
    //DDRB = 11111111;

    PORTB |= _BV(PB4); //set pin PB4 high
    /*Same as saying*/
    //PORTB = 00001000;

    for (;;) {
        // keeps led on forever
    }
}