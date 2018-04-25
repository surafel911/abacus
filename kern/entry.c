#include <muart.h>
#include <muart_i.h>

#include <stdbool.h>

void
kern_entry(void)
{
	muart_setup();

	while (true) {
		muart_send('A');
	}
}
