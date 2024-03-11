#include <hardware/serial.h>
#include <stdint.h>

void Serial::outb(uint16_t port, uint8_t val) {
	__asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port));
}
uint8_t Serial::inb(uint16_t port) {
	uint8_t ret_val=0;
	__asm__ __volatile__ ("inb %1, %0" : "=a"(ret_val) : "Nd"(port));
	return ret_val;
}
void Serial::iowait() {
	 __asm__ __volatile__ ("outb %%al, $0x80" :: "a"(0));
}
/*void Serial::init() {
	Serial::outb(PORT + 1, 0x00);   
	Serial::outb(PORT + 3, 0x80);   
	Serial::outb(PORT + 0, 0x03); 
	Serial::outb(PORT + 1, 0x00);  
	Serial::outb(PORT + 3, 0x03); 
	Serial::outb(PORT + 2, 0xC7);   
	Serial::outb(PORT + 4, 0x0B);  
	Serial::outb(PORT + 4, 0x1E);   
	Serial::outb(PORT + 0, 0xAE);    
	if(Serial::inb(PORT + 0) != 0xAE) {
	    return;
	}
	Serial::outb(PORT + 4, 0x0F);
}*/
int Serial::t_empty() {
	return Serial::inb(PORT + 5) & 0x20;
}
void Serial::write(char ch) {
	while (Serial::t_empty() == 0);
	Serial::outb(PORT, ch);
}
void Serial::write(const char *str) {
	while (*str) {
		Serial::write(*str);
		str++;
	}
	Serial::write('\0');
}
