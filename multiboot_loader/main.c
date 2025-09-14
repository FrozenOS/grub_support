#include <stdint.h>

#include "debug.h"
#include "elf_loader.h"
#include "multiboot.h"

void multiboot_loader_main(uint32_t multiboot_sig, struct MultibootInfoStruct *multiboot_struct) {
	uint32_t kernel_elf_base_addr = 0;
	uint64_t kernel_entry_point = 0;

	multiboot_init(multiboot_sig, multiboot_struct, &kernel_elf_base_addr);

	if (kernel_elf_base_addr == 0) {
		debugport_printstr("No kernel found, abort");
		for (;;) {}
	}

	load_elf_image((void *)kernel_elf_base_addr, &kernel_entry_point);

	for (;;) {}
}
