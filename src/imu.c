#define F_CPU (1000000L) //pre-defining CPU speed
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "api.h"
#include "uart.h"


int NODE_HOME = NODE_demoNode1;


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
    //DDRB &= ~(_BV(PB2)); // set pin 16 for input
    DDRC &= ~(_BV(PC0)); // set pin 30 for input
    DDRD &= ~(_BV(PD6)); // set pin 14 for input

    // Setting PE1 and PE2. XTAL1 to input and XTAL2 to ouput . Pins 10 and 11
    DDRE |= _BV(PE2);
    DDRE &= ~(_BV(PE1));

    //sei(); // enable global interrupts
    initCAN(NODE_HOME); // initialize CAN bus

    for (;;) {
        // listen for button presses forever
    }
}
