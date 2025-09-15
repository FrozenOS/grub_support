#include <stdint.h>

#include "debug.h"
#include "multiboot.h"

void multiboot_init(uint32_t multiboot_sig, struct MultibootInfoStruct *multiboot_struct,
					uint32_t *kernel_elf_base_addr) {
	debugport_printstr("Multiboot Sig: ");
	debugport_printhex(multiboot_sig, false);
	debugport_putc('\n');

	if (multiboot_struct->flags & (1 << 2)) {
		debugport_printstr("Command Line: ");
		debugport_printstr((char *)multiboot_struct->cmdline);
		debugport_putc('\n');
	}

	if (multiboot_struct->flags & (1 << 3)) {
		debugport_printstr("Module count ");
		debugport_printhex(multiboot_struct->mods_count, false);
		debugport_putc('\n');

		for (unsigned int cnt = 0; cnt < multiboot_struct->mods_count; cnt++) {
			struct MultibootModuleEntry *module =
				(struct MultibootModuleEntry *)(multiboot_struct->mods_addr +
												cnt * sizeof(struct MultibootModuleEntry));
			debugport_printstr("Module start ");
			debugport_printhex(module->mod_start, false);
			debugport_printstr(" end ");
			debugport_printhex(module->mod_end, false);
			debugport_putc('\n');

			if (cnt == 0) {
				*kernel_elf_base_addr = module->mod_start;
			}
		}
	}

	if (multiboot_struct->flags & (1 << 6)) {
		debugport_printstr("Memory map addr ");
		debugport_printhex(multiboot_struct->mmap_addr, false);
		debugport_printstr(" length ");
		debugport_printhex(multiboot_struct->mmap_length, false);
		debugport_putc('\n');

		struct MultibootMMapEntry *mmap = (struct MultibootMMapEntry *)multiboot_struct->mmap_addr;
		for (unsigned int off = 0; off < multiboot_struct->mmap_length;
			 off += (mmap->size + sizeof(mmap->size))) {
			mmap = (struct MultibootMMapEntry *)(multiboot_struct->mmap_addr + off);
			debugport_printstr("Entry base ");
			debugport_printhex(mmap->base, true);
			debugport_printstr(" length ");
			debugport_printhex(mmap->length, true);
			debugport_printstr(" type ");
			debugport_printhex(mmap->type, false);
			debugport_putc('\n');
		}
	}

	if (multiboot_struct->flags & (1 << 12)) {
		switch (multiboot_struct->framebuffer_type) {
			case 1:
				debugport_printstr("RGB Framebuffer Mode\n");
				break;
			case 2:
				debugport_printstr("VGA Text Mode\n");
				break;
			default:
				debugport_printstr("Unknown Video Mode\n");
				break;
		}
		debugport_printstr("FB Addr: ");
		debugport_printhex(multiboot_struct->framebuffer_addr, true);
		debugport_putc('\n');
		debugport_printstr("FB Width: ");
		debugport_printhex(multiboot_struct->framebuffer_width, false);
		debugport_putc('\n');
		debugport_printstr("FB Height: ");
		debugport_printhex(multiboot_struct->framebuffer_height, false);
		debugport_putc('\n');
	}
}
