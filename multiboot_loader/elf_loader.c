#include <stddef.h>
#include <stdint.h>

#include "debug.h"
#include "elf.h"
#include "elf_loader.h"

static inline void *memcpy(void *restrict dest, const void *restrict src, size_t size) {
	uint8_t *d = dest;
	const uint8_t *s = src;
	for (size_t i = 0; i < size; i++) {
		d[i] = s[i];
	}
	return dest;
}

void load_elf_image(void *elf_image_base_addr, uint64_t *entry_point) {
	struct ELF64FileHeader *elf_file_header = elf_image_base_addr;

	if ((elf_file_header->e_ident_mag[0] != 0x7f) || (elf_file_header->e_ident_mag[1] != 'E') ||
		(elf_file_header->e_ident_mag[2] != 'L') || (elf_file_header->e_ident_mag[3] != 'F')) {
		debugport_printstr("Kernel image not ELF, abort");
		for (;;) {}
	}

	if (elf_file_header->e_machine != 0x3e) {
		debugport_printstr("Kernel image not x86-64, abort");
		for (;;) {}
	}

	for (int ph_idx = 0; ph_idx < elf_file_header->e_phnum; ph_idx++) {
		struct ELF64ProgramHeader *elf_prog_header =
			(struct ELF64ProgramHeader *)(elf_image_base_addr + elf_file_header->e_phoff +
										  ph_idx * elf_file_header->e_phentsize);

		if (elf_prog_header->p_type != 0x1) { // PT_LOAD
			continue;
		}

		debugport_printstr("ELF Load Segment PAddr ");
		debugport_printhex(elf_prog_header->p_paddr, true);
		debugport_printstr(" FileSz ");
		debugport_printhex(elf_prog_header->p_filesz, true);
		debugport_putc('\n');

		memcpy((void *)elf_prog_header->p_paddr,
			   elf_image_base_addr + elf_prog_header->p_offset,
			   elf_prog_header->p_filesz);
	}
}
