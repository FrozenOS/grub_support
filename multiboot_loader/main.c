#include <stdint.h>

#include "debug.h"
#include "multiboot.h"

void multiboot_loader_main(uint32_t multiboot_sig, struct MultibootInfoStruct *multiboot_struct) {
	multiboot_init(multiboot_sig, multiboot_struct);

	for (;;) {
		porte9_putc('A');
	}
}
