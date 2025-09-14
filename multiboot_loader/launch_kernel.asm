section .text

global launch_kernel

extern p4_table
extern kernel_entry_point

launch_kernel:
	; Load PML4
	mov eax, p4_table
	mov cr3, eax

	; Enable PAE
	mov eax, cr4
	or eax, 0x20
	mov cr4, eax

	; Enable long mode
	mov ecx, 0xc0000080
	rdmsr
	or eax, 0x100
	wrmsr

	; Enable paging
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax

	; Load GDT
	lgdt [gdt_pointer]

	; Jump to 64-bits code
	jmp 0x8:start_64bit

bits 64

start_64bit:
	mov rax, [kernel_entry_point]
	jmp rax

section .rodata

align 16

gdt:
    dq 0
    dq (1<<43) | (1<<44) | (1<<47) | (1<<53)

gdt_pointer:
    dw $ - gdt - 1
    dq gdt
