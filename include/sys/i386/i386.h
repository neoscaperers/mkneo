#ifndef _SYS_I386_I386_H
#define _SYS_I386_I386_H

#include <sys/types.h>

#define COM0    0x3F8

__attribute__((always_inline)) inline void outb(uint16_t p, uint8_t v) {
    asm volatile ("outb %b0, %w1" ::"a"(v), "Nd"(p));
}

__attribute__((always_inline)) inline uint8_t inb(uint16_t p) {
    uint8_t r;
    asm volatile ("inb %w1, %b0" :"=a"(r) :"Nd"(p));
    return r;
}

#endif /*_SYS_I386_I386_H*/