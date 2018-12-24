#include <stdint.h>

#include <cpu.h>
#include <cpu_i.h>
#include <util.h>

void
cpu_fiq_handler(void)
{
	puts("FIQ");
}

void
cpu_irq_handler(void)
{
	puts("IRQ");
}

void
cpu_synchronous_handler(const uint32_t esr)
{
	puts("SVC");
}

void
cpu_setup(void)
{
	cpu_intr_enable();
}
