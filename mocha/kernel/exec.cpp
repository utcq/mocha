#include <stdint.h>
#include <libc/stdio.h>
#include <mem/alloc.h>
extern "C" {
	#include <libc/string.h>
}

void test_run() {
	char *memloc  = (char*)malloc(8);
    char *opcodes = "\xEB\xFE";
    memcpy(memloc, opcodes, 2);
    void (*exec)() = reinterpret_cast<void (*)()>(opcodes);
}
