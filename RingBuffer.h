#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

void rb_init(void);
void rb_modtag_byte(uint8_t data);
void rb_behandel(void);
void rb_hent_sidste_5(uint8_t dest[5]);
uint8_t rb_er_aktiv(void);

#endif