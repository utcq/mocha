#include <libc/stdio.h>
extern "C" {
	#include <libc/stdlib.h>
}
#include <hardware/serial.h>

void dbprintf(const char *format, ...) {
	va_list args;
	va_start(args, format);

	while (*format != '\0') {
	    if (*format == '%') {
	        format++;

	        switch (*format) {
	            case 'd': {
	                int value = va_arg(args, int);
	                char buffer[16];
	                itoa(value, buffer, 10);
	                Serial::write(buffer);
	                break;
	            }
	            case 's': {
	                const char *str = va_arg(args, const char *);
	                Serial::write(str);
	                break;
	            }
	            case 'x': {
	                int value = va_arg(args, int);
	                char buffer[16];
	                itoa(value, buffer, 16);
	                Serial::write("0x");
	                Serial::write(buffer);
	                break;
	            }
	            case 'c': {
	                char value = va_arg(args, int);
	                char buffer[2];
	                buffer[0]=value;
	                buffer[1]='\0';
	                Serial::write(buffer);
	                break;
	            }
	            default:
	                Serial::write('%');
	                Serial::write(*format);
	        }
	    } else {
	        Serial::write(*format);
	    }

	    format++;
	}

	va_end(args);
}

