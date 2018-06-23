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

	muart_send(cc + 48);

	while (true) {
	}
}
