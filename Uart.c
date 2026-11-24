#include "ProjectDefines.h"
#include "Uart.h"
#include "RingBuffer.h"

void start_uart(void) {
    UCSR0A = (1 << U2X0); 
    UBRR0 = UBRR_115200;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    UCSR1A = (1 << U2X1); 
    UBRR1 = UBRR_115200;
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

void uart1_send_byte(uint8_t data) {
    while (!(UCSR1A & (1 << UDRE1))) {
    }
    UDR1 = data;
}

void uart1_send_tekst(const char* tekst) {
    for (int i = 0; tekst[i] != '\0'; i++) {
        uart1_send_byte((uint8_t)tekst[i]);
    }
}

ISR(USART0_RX_vect) {
    uint8_t modtaget = UDR0;
    rb_modtag_byte(modtaget);
}