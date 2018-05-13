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
gpio_write_mask(volatile uint32_t* reg, uint32_t clear, uint32_t value)
{
	(*reg) &= ~(clear);
	(*reg) |= value;
}

static void
gpio_set_pin_bit(volatile uint32_t* registers, enum gpio_pin pin, bool value)
{
	if (pin < 31) {
		gpio_write_mask(registers, 1 << (int)pin, 1 << (int)pin);
	} else {
		gpio_write_mask(registers + 1, 1 << ((int)pin - 32), 1 << ((int)pin - 32));
	}
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
	gpio_set_pin_bit(&_gpio->pudclk[0], pin, true);
}

void
gpio_pin_function(enum gpio_pin pin, enum gpio_function function)
{
	int group = (int)pin / 10;
	int offset = ((int)pin % 10) * 3;

	gpio_write_mask(&_gpio->fsel[group], 0b111 << offset, (int)function << offset);
}

void
gpio_pin_output(enum gpio_pin pin, bool value)
{
	gpio_set_pin_bit(&_gpio->set[0], pin, value);
}
