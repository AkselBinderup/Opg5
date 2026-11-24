#ifndef UART_H
#define UART_H

#include <stdint.h>

void start_uart(void);
void uart1_send_byte(uint8_t data);
void uart1_send_tekst(const char* tekst);

#endif