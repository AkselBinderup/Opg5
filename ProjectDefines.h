#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

#include <xc.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <stdint.h>

// 115200 baud ved 16 MHz (med Double Speed U2X = 1)
// Bruger du 9600 baud i Avalonia-appen, så sæt U2X fra og brug 103
#define UBRR_115200      16    

#define ET_SEKUND        15624 // 1 sekund ved 16 MHz og 1024 prescaler
#define BRUGERNAVN_STR   ":Shakespear:"
#define RINGBUFFER_SIZE  32    // Lille størrelse gør det nemt at teste Buffer Overrun

#endif