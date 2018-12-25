#include <util.h>

#include <muart.h>

void
putc(const char c)
{
	muart_send(c);
}

void
puts(const char* s)
{
	while (*s != '\0') {
		muart_send(*s);
		s++;
	}
}
