#include <libc/stdio.h>
#include <hardware/gdt.h>
#include <hardware/cpuid.h>
#include <mem/alloc.h>
extern "C" {
	#include <hardware/idt.h>
}

extern void test_run();

int main() {
	dbprintf("\033[32;49;3m[...] Startup\n\033[0m");
	init_gdt();
	init_idt();
	init_alloc();
	test_run();
	return 0;
}

extern "C" {
	void _start(void) {
		main();
		for (;;) {}
	}
}
