#include "debug.h"

void debugport_putc(char c) {
#if (DEBUG_IO_PORT != 0x0)
	x86_out8(DEBUG_IO_PORT, c);
#endif
}

void debugport_printstr(const char *s) {
	while (*s) {
		debugport_putc(*s);
		s++;
	}
}

void debugport_printhex(uint64_t n, bool is_64bit) {
	for (int i = 0; i < (is_64bit ? 16 : 8); i++) {
		uint8_t part = (n >> ((is_64bit ? 60 : 28) - i * 4)) & 0xf;
		const char num2char[16] = {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		debugport_putc(num2char[part]);
	}
}
