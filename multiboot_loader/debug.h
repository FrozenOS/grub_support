#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

void x86_out8(uint16_t port, uint8_t value);
void debugport_putc(char c);
void debugport_printstr(const char *s);
void debugport_printhex(uint64_t n, bool is_64bit);

#endif
