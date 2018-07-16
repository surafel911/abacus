#include <cpu.h>
#include <muart.h>

#include <stdint.h>

void
cpu_fiq_handler(void)
{
	muart_send('F');
}

void
cpu_irq_handler(void)
{
	muart_send('I');
}

void
cpu_synchronous_handler(const uint32_t esr)
{
	muart_send('E');
}
