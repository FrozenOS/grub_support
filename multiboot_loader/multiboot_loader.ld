SECTIONS {
	. = 0x200000; /* 2 MiB */

	PROVIDE(text_begin = .);

	.text : {
		*(.text .stub .text.* .gnu.linkonce.t.*)
	}

	. = ALIGN(0x1000);

	PROVIDE(rodata_begin = .);

	.rodata : {
		*(.rodata .rodata.* .gnu.linkonce.r.*)
	}

	. = ALIGN(0x1000);

	PROVIDE(data_begin = .);

	.data : {
		*(.data)
	}

	.bss : {
		*(.bss)
		. = ALIGN(0x1000);
		. += 0x4000; /* 16kB of stack memory */
		PROVIDE(stack_top = .);
		PROVIDE(p4_table = .);
		. += 0x1000; /* 4kB PML4 table */
		PROVIDE(p3_table = .);
		. += 0x1000; /* 4kB PDPT table */
		PROVIDE(p2_table = .);
		. += 0x1000; /* 4kB PD table */
	}

	/DISCARD/ : {
		*(.eh_frame .note.GNU-stack)
	}
}
