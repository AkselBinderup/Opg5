#include "ProjectDefines.h"
#include "ExtInt.h"

volatile uint16_t down_int_count = 0;
volatile uint16_t up_int_count = 0;
volatile uint8_t knap_aendret = 0;
static uint8_t venter_paa_ned = 1;

void start_ext_int0(void) {
    DDRD &= ~(1 << PD2);   
    PORTD |= (1 << PD2);   
    DDRB |= (1 << PB1);    

    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);
}

ISR(INT0_vect) {
    PORTB ^= (1 << PB1);  
    knap_aendret = 1;

    if (venter_paa_ned == 1) {
        down_int_count++;  
        venter_paa_ned = 0;
        EICRA |= (1 << ISC01) | (1 << ISC00); 
    } else {
        up_int_count++;    
        venter_paa_ned = 1;
        EICRA |= (1 << ISC01);
        EICRA &= ~(1 << ISC00);  
    }
}