#include <gpio.h>

#include <stdbool.h>
#include <stdint.h>

#include <util.h>
#include <mmio.h>
#include <macros.h>

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
} __packed __aligned(32);

static struct gpio_map* _gpio = (struct gpio_map*)GPIO_BASE;

void
gpio_fsel_set_pin(const enum gpio gpio, const enum gpio_fsel fsel)
{
	_gpio->fsel[gpio / 10] |= fsel << (gpio % 10) * 3;
}

void
gpio_output_set_pin(const enum gpio_pin pins, const bool to)
{
	if (to) {
		_gpio->set[0] |= pins;
		_gpio->set[1] |= pins >> 32;
	} else {
		_gpio->clr[0] |= pins;
		_gpio->clr[1] |= pins >> 32;
	}
}

void
gpio_pud_set_state(const enum gpio_pud pud, const enum gpio_pin pins)
{
	volatile int count;

	_gpio->pud = (uint32_t)pud;
	for (count = 0; count < 150; count++);
	_gpio->pudclk[0] = pins;
	_gpio->pudclk[1] = pins >> 32;
	for (count = 0; count < 150; count++);
	_gpio->pud = 0;
	_gpio->pudclk[0] = 0;
	_gpio->pudclk[1] = 0;
}
