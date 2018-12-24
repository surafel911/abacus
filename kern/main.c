#include <util.h>
#include <gpio.h>
#include <muart.h>
#include <muart_i.h>

static char cc;

void
kern_main(void)
{
	muart_setup();

	muart_send(cc + 'A');

#if 0	
	asm volatile ("svc #10");

	
#endif
}
