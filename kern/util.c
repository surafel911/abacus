#include <util.h>

#include <muart.h>

void
puts(const char* s)
{
	while (*s != '\0') {
		muart_send(*s);
		s++;
	}
}
