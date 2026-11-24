#ifndef EXT_INT_H
#define EXT_INT_H

#include <stdint.h>

extern volatile uint16_t down_int_count;
extern volatile uint16_t up_int_count;
extern volatile uint8_t knap_aendret;

void start_ext_int0(void);

#endif