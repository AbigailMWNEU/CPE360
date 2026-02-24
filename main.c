/* 
 * File:   main.c
 * Author: kennel
 *
 * Created on February 12, 2026, 2:08 PM
 */

//#include <avr/io.h>
#include "UART.h"
#include <util/delay.h>
#define F_CPU 16000000


int main() {
    uint16_t baudRate = 9600;
    UART_init(baudRate);    
    while(1){
        UART_sendString("UART");
        _delay_ms(500);
    }
}

