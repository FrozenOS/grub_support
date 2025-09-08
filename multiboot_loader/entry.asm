global _start
global porte9_putc

extern multiboot_loader_main
extern stack_top

bits 32

_multiboot_header:
	dd 0x1badb002
	dd 4
	dd 0xe4524ffa
	dd 0
	dd 0
	dd 0
	dd 0
	dd 0
	dd 1
	dd 0
	dd 0
	dd 0

_start:
	cli
	mov esp, stack_top
	push ebx
	push eax
	call multiboot_loader_main
	jmp $

porte9_putc:
	mov al, [esp+4]
	out 0xe9, al
	ret
