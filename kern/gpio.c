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

struct gpio_map* _gpio = (struct gpio_map*)GPIO_BASE;

#if 0
static void
write_bits(uint32_t* reg, uint32_t clear, uint32_t value)
{
	(*reg) &= ~(clear);
	(*reg) |= value;
}
#endif

void
gpio_pud_mode(enum gpio_pud pud)
{
	_gpio->pud = (uint32_t)pud;
}

void
gpio_pudclk_signal(enum gpio_pin pin)
{
	if (pin > 31) {
		
	} else {
		
	}
}

void
gpio_pin_setup(enum gpio_pin pin, enum gpio_function function)
{

}
