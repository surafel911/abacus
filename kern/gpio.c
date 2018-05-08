#include <gpio.h>

#include <stdbool.h>
#include <stdint.h>

#include <mmio.h>

#define GPIO_BASE	(MMIO_BASE + 0x200000)

struct gpio_map {
	uint32_t fsel[6];
	uint32_t reserved1;
	uint32_t set[2];
	uint32_t reserved2;
	uint32_t clr[2];
	uint32_t reserved3;
	uint32_t lev[2];
	uint32_t reserved4;
	uint32_t eds[2];
	uint32_t reserved5;
	uint32_t ren[2];
	uint32_t reserved6;
	uint32_t fen[2];
	uint32_t reserved7;
	uint32_t hen[2];
	uint32_t reserved8;
	uint32_t len[2];
	uint32_t reserved9;
	uint32_t aren[2];
	uint32_t reserved10;
	uint32_t afen[2];
	uint32_t reserved11;
	uint32_t pud;
	uint32_t pudclk[2];
};

static volatile struct gpio_map* _gpio = (struct gpio_map*)GPIO_BASE;

static void
write_mask(volatile uint32_t* reg, uint32_t clear, uint32_t value)
{
	(*reg) &= ~(clear);
	(*reg) |= value;
}

void
gpio_pud_mode(enum gpio_pud pud)
{
	_gpio->pud = (uint8_t)pud;
}

void
gpio_pudclk_hold(void)
{
	for (volatile int index = 0; index < 150; index ++);
}

void
gpio_pudclk_reset(void)
{
	_gpio->pudclk[0] = 0;
	_gpio->pudclk[1] = 0;
}

void
gpio_pudclk_signal(enum gpio_pin pin)
{
	uint32_t mask;

	if (pin > 31) {
		mask = 1 << ((unsigned int)pin - 32);
		write_mask(&_gpio->pudclk[1], mask, mask);
	} else {
		mask = 1 << (unsigned int)pin;
		write_mask(&_gpio->pudclk[0], mask, mask);
	}
}

void
gpio_pin_fsel(enum gpio_pin pin, enum gpio_function function)
{
	uint32_t group = (unsigned int)pin / 10;
	uint32_t mask = (unsigned int)function << (((unsigned int)pin % 10) * 3);
	uint32_t clear_mask = 7 << (((unsigned int)pin % 10) * 3);

	write_mask(&_gpio->fsel[group], clear_mask, mask);
}

void
gpio_pin_output(enum gpio_pin pin, bool value)
{
	uint32_t mask;

	if (pin > 31) {
		mask = 1 << ((unsigned int)pin - 32);
		write_mask(&_gpio->set[1], mask, mask);
	} else {
		mask = 1 << (unsigned int)pin;
		write_mask(&_gpio->set[0], mask, mask);
	}
}
