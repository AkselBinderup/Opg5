#include "ProjectDefines.h"
#include "Timer.h"

volatile uint8_t sekund_flag = 0;

void start_timer(void) {
    DDRB |= (1 << PB0);  
    OCR1A = ET_SEKUND;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TIMSK1 = (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect) {
    PORTB ^= (1 << PB0);  
    sekund_flag = 1;
}