#ifndef ELF_H
#define ELF_H

#include <stdint.h>

struct ELF64FileHeader {
	uint8_t e_ident_mag[4];
	uint8_t e_ident_class;
	uint8_t e_ident_data;
	uint8_t e_ident_version;
	uint8_t e_ident_osabi;
	uint8_t e_ident_abiversion;
	uint8_t e_ident_pad[7];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint64_t e_entry;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} __attribute__((packed));

struct ELF64ProgramHeader {
	uint32_t p_type;
	uint32_t p_flags;
	uint64_t p_offset;
	uint64_t p_vaddr;
	uint64_t p_paddr;
	uint64_t p_filesz;
	uint64_t p_memsz;
	uint64_t p_align;
} __attribute__((packed));

#endif
