#include <stdbool.h>

#include <util.h>
#include <gpio.h>
#include <muart_i.h>

static char cc;

void
kern_setup(void)
{
}

void
kern_main(void)
{
	gpio_output_set_pin(GPIO_PIN_24, true);

	gpio_fsel_set_pin(GPIO_14, GPIO_FSEL_ALT5);
	gpio_fsel_set_pin(GPIO_15, GPIO_FSEL_ALT5);
	gpio_pud_set_state(GPIO_PUD_DOWN, GPIO_PIN_14 | GPIO_PIN_15);

	muart_setup();

	putc(cc + 'A');

	asm volatile ("svc #10");
}
