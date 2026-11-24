#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

extern volatile uint8_t sekund_flag;
void start_timer(void);

#endif