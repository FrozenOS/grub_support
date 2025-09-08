#include <stdint.h>

#include "multiboot.h"

extern char porte9_putc(char c);

void porte9_printstr(const char *s) {
	while (*s) {
		porte9_putc(*s);
		s++;
	}
}

void porte9_printhex(uint32_t n) {
	for (int i = 0; i < 8; i++) {
		uint8_t part = (n >> (28 - i * 4)) & 0xf;
		const char num2char[16] = {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		porte9_putc(num2char[part]);
	}
}

void multiboot_loader_main(uint32_t multiboot_sig, struct MultibootInfoStruct *multiboot_struct) {
	porte9_printstr("Sig: ");
	porte9_printhex(multiboot_sig);
	porte9_putc('\n');
	if (multiboot_struct->flags & (1 << 12)) {
		switch (multiboot_struct->framebuffer_type) {
			case 1:
				porte9_printstr("RGB Framebuffer Mode\n");
				break;
			case 2:
				porte9_printstr("VGA Text Mode\n");
				break;
			default:
				porte9_printstr("Unknown Video Mode\n");
				break;
		}
		porte9_printstr("FB Addr: ");
		porte9_printhex(multiboot_struct->framebuffer_addr);
		porte9_putc('\n');
		porte9_printstr("FB Width: ");
		porte9_printhex(multiboot_struct->framebuffer_width);
		porte9_putc('\n');
		porte9_printstr("FB Height: ");
		porte9_printhex(multiboot_struct->framebuffer_height);
		porte9_putc('\n');
	}

	for (;;) {
		porte9_putc('A');
	}
}
