ARCH := i686
TOOLCHAIN := gcc

CROSS_COMPILE := $(ARCH)-elf-

CC := $(CROSS_COMPILE)gcc
CFLAGS := -fno-builtin -Wall -Wextra -ffreestanding

ifeq ($(CONFIG), RELEASE)
CFLAGS += -O2
else
CFLAGS += -Og -gdwarf-5
ASFLAGS += -gdwarf
endif

multiboot_loader.elf : entry.o main.o
	$(CROSS_COMPILE)ld -T multiboot_loader.ld $^ -o $@ -e _start

entry.o : entry.asm
	nasm -f elf32 $(ASFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf *.o *.elf
