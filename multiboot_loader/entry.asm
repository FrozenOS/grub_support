section .text

global _start
global x86_out8

extern multiboot_loader_main
extern stack_top

bits 32

_multiboot_header:
	dd 0x1badb002
	dd 0x4
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
	; Disable interrupts
	cli

	; Ensure paging is disabled
	mov eax, cr0
	and eax, 0x7fffffff
	mov cr0, eax

	; Setup stack
	mov esp, stack_top
	push ebx
	push eax
	call multiboot_loader_main
	jmp $

;; void x86_out8(uint16_t port, uint8_t value);
;;                       [esp+8]        [esp+4]
x86_out8:
	mov edx, [esp+4]
	mov eax, [esp+8]
	out dx, al
	ret
