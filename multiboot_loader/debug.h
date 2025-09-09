#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

char porte9_putc(char c);
void porte9_printstr(const char *s);
void porte9_printhex(uint64_t n, bool is_64bit);

#endif
