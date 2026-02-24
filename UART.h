/* 
 * File:   UART.h
 * Author: abby m
 *
 * Created on February 11, 2026, 1:09 PM
 */

#ifndef UART_H
#define	UART_H
#include <avr/io.h>
#define F_CPU 16000000UL


uint8_t UART_rx(){
    // Wait for data to be fully received
    while ( !(UCSR0A & (1 << RXS))){
    //Do nothing
    }
    // Return the contents of the dataregister
    return UDR0;
}

void UART_tx(uint8_t data){
    // While the UART is still transmitting, wait
    while( !(UCSR0A & (1<< UDRE0))){
    }   
    // Write the data
    UDR0 = data;
}

void UART_sendString(char str[]) {
    PORTB = 0xFF;
    for (int i = 0; str[i] != '\0'; i++) {
        UART_tx(str[i]);  // Send each character
        PORTB ^= 0xFF;
    }
    PORTB = 0x00;
}

void UART_receiveString(char str[], uint16_t maxsize) {
    for (int i = 0; i < maxsize - 1; i++) {
        str[i] = UART_rx();
        if (str[i] == '\0') {
            i = maxsize; //terminates loop when null terminator found
        }
        if (i = maxsize - 2) {
            str[maxsize - 1] = '\0'; //ensures all strings end correctly
        }
    }
}

void UART_init(uint16_t baudRate){
    DDRB = 0xFF;
    //Calculate the BDDR value
    uint16_t BDR = F_CPU / (baudRate * 16UL) - 1;
    //uint16_t BDR = 103;
    uint8_t BDRH = (BDR >> 8);//Upper 8 bits
    uint8_t BDRL = BDR & 0xFF;//Lower 8 bits
    //Write to the baud rate registers
    UBRR0H = BDRH;
    UBRR0L = BDRL;
    //Enable the transmitter and receiver
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    //Set 8-bit data mode(1<<UMSEL01)|
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

#endif	/* UART_H */
    