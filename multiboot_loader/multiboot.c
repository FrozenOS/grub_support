#include <stdint.h>

#include "debug.h"
#include "multiboot.h"

void multiboot_init(uint32_t multiboot_sig, struct MultibootInfoStruct *multiboot_struct) {
	porte9_printstr("Sig: ");
	porte9_printhex(multiboot_sig, false);
	porte9_putc('\n');

	if (multiboot_struct->flags & (1 << 6)) {
		porte9_printstr("Memory map addr ");
		porte9_printhex(multiboot_struct->mmap_addr, false);
		porte9_printstr(" length ");
		porte9_printhex(multiboot_struct->mmap_length, false);
		porte9_putc('\n');

		struct MultibootMMapEntry *mmap = (struct MultibootMMapEntry *)multiboot_struct->mmap_addr;
		for (unsigned int off = 0; off < multiboot_struct->mmap_length;
			 off += (mmap->size + sizeof(mmap->size))) {
			mmap = (struct MultibootMMapEntry *)(multiboot_struct->mmap_addr + off);
			porte9_printstr("Entry base ");
			porte9_printhex(mmap->base, true);
			porte9_printstr(" length ");
			porte9_printhex(mmap->length, true);
			porte9_printstr(" type ");
			porte9_printhex(mmap->type, false);
			porte9_putc('\n');
		}
	}

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
		porte9_printhex(multiboot_struct->framebuffer_addr, true);
		porte9_putc('\n');
		porte9_printstr("FB Width: ");
		porte9_printhex(multiboot_struct->framebuffer_width, false);
		porte9_putc('\n');
		porte9_printstr("FB Height: ");
		porte9_printhex(multiboot_struct->framebuffer_height, false);
		porte9_putc('\n');
	}
}
