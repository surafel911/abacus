#include <muart.h>
#include <muart_i.h>
#include <mailbox.h>

#include <stdbool.h>
#include <stdint.h>

char cc;

void
kern_main(void)
{
	muart_setup();
	
	while (true) {
		muart_send(cc ? 'F' : 'T');
	}
}
