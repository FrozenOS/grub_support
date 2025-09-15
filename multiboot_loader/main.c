#include <stdint.h>

#include "common.h"
#include "debug.h"
#include "elf_loader.h"
#include "multiboot.h"

extern void launch_kernel(void);

extern uint64_t p4_table;
extern uint64_t p3_table;
extern uint64_t p2_table;

uint64_t kernel_entry_point = 0;

void multiboot_loader_main(uint32_t multiboot_sig, struct MultibootInfoStruct *multiboot_struct) {
	uint32_t kernel_elf_base_addr = 0;

	debugport_printstr("FrozenOS cryo multiboot kernel loader\n");

	multiboot_init(multiboot_sig, multiboot_struct, &kernel_elf_base_addr);

	if (kernel_elf_base_addr == 0) {
		debugport_printstr("No kernel found, abort");
		for (;;) {}
	}

	load_elf_image((void *)kernel_elf_base_addr, &kernel_entry_point);

	debugport_printstr("Init page tables and starting kernel\n");

	// Setup long mode page table
	memset(&p4_table, 0, 4096);
	memset(&p3_table, 0, 4096);
	memset(&p2_table, 0, 4096);

	p4_table = (uint64_t)(&p3_table) | 0x3;
	p3_table = (uint64_t)(&p2_table) | 0x3;

	uint64_t *p2_table_entry = &p2_table;
	for (int i = 0; i < 512; i++) {
		p2_table_entry[i] = (2 * 1024 * 1024 * i) | 0x183;
	}

	launch_kernel();
}
