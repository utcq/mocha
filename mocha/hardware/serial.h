#include <stdint.h>

#ifndef _HW_SERIAL_H
#define _HW_SERIAL_H

#define PORT 0x3f8

namespace Serial {
	void outb(uint16_t port, uint8_t val);
	uint8_t inb(uint16_t port);
	void iowait();
	void init();
	int t_empty();
	void write(char ch);
	void write(const char *str);
}

#endif
