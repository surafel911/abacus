#include <muart.h>
#include <muart_i.h>
#include <gpio.h>

#include <stdbool.h>

void
kern_main(void)
{
	gpio_pin_fsel(GPIO_PIN_12, GPIO_FSEL_OUT);
	gpio_pin_output(GPIO_PIN_12, true);

	gpio_pud_mode(GPIO_PUD_OFF);
	gpio_pudclk_hold();
	gpio_pudclk_signal(GPIO_PIN_12);
	gpio_pudclk_hold();
	gpio_pudclk_reset();

	muart_setup();

	while (true) {
		muart_send('G');
		muart_send('A');
		muart_send('Y');
		muart_send('\n');
	}
}
