#ifndef ELF_LOADER_H
#define ELF_LOADER_H

#include <stdint.h>

void load_elf_image(void *elf_image_base_addr, uint64_t *entry_point);

#endif
