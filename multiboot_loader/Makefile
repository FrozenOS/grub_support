ARCH := i686
TOOLCHAIN := gcc

CROSS_COMPILE := $(ARCH)-elf-

ASM_SRC := entry.asm
C_SRC := main.c multiboot.c debug.c

OBJS := $(ASM_SRC:.asm=.o) $(C_SRC:.c=.o)

DEBUG_IO_PORT := 0x0

CC := $(CROSS_COMPILE)gcc
CFLAGS := -std=c23 -pedantic -MMD -fno-builtin -Wall -Wextra -ffreestanding -DDEBUG_IO_PORT=$(DEBUG_IO_PORT)

ifeq ($(CONFIG), RELEASE)
CFLAGS += -O2
else
CFLAGS += -Og -gdwarf-5
ASFLAGS += -gdwarf
endif

multiboot_loader.elf : $(OBJS)
	$(CROSS_COMPILE)ld -T multiboot_loader.ld $^ -o $@ -e _start

entry.o : entry.asm
	nasm -f elf32 $(ASFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf *.o *.d *.elf

-include $(C_SRC:.c=.d)
