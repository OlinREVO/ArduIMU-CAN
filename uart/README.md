AVR-UART
========

Debugging via UART - REVO Buildathon Fall 2013

Setting up the hardware
-----------------------
1. Obtain an FTDI cable. The one REVO has is on page 10 of this document http://www.ftdichip.com/Support/Documents/DataSheets/Cables/DS_TTL-232R_CABLES.pdf and a picture is here http://makeyourbot.wdfiles.com/local--files/fabio-1-1/ftdi.jpg
2. Plug the black wire (GND) into ground on your circuit.
3. DO NOT plug in the red wire (POWER) unless you do not have another power source. If you plug them both in, they will both be sad.
4. Plug the yellow wire (RXD) into pin 2 of the ATMega16M1 (TXD).
5. Plug the USB into your computer.

Setting up the software
-----------------------
Usage:
1. Put uart.c and uart.h in your src/ folder.
2. Put the following in any file where you want to use UART: #include "uart.h"
3. Add the following to your Makefile (this may need to be modified depending on your Makefile configuration):  
SOURCES += uart.c  
INC += -Isrc/  
CFLAGS += $(INC)

4. Call initUART to turn on UART functionality.
5. Call UART_putString to send a message.
6. Call endUART to turn off UART functionality. (It doesn't hurt anything to leave it on, so you shouldn't need this.)

See main.c in this folder for an example of how to debug using these functions.

Viewing messages
----------------
Run the following commands in the folder containing view_uart_script:

chmod +x view_uart_script
./view_uart_script
