/* TEST CODE - UART
        Initializes the UART controller and sends out sporadic debug messages.
*/

#include "uart.h"

int main (void) {
    initUART(); // intitialize UART controller
    for (;;) {
        // spit out debug messages forever
        _delay_ms(500);
        UART_putString("Hello, World!\n");
    }

    return(0);
}