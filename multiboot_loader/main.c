extern char porte9_putc(char c);

void multiboot_loader_main(void) {
	for (;;) {
		porte9_putc('A');
	}
}
