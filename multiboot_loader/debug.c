#include "debug.h"

void porte9_printstr(const char *s) {
	while (*s) {
		porte9_putc(*s);
		s++;
	}
}

void porte9_printhex(uint64_t n, bool is_64bit) {
	for (int i = 0; i < (is_64bit ? 16 : 8); i++) {
		uint8_t part = (n >> ((is_64bit ? 60 : 28) - i * 4)) & 0xf;
		const char num2char[16] = {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		porte9_putc(num2char[part]);
	}
}
