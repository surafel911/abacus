#include <muart.h>
#include <muart_i.h>

#include <stddef.h>
#include <stdint.h>

#include <mmio.h>

#define MUART_BASE			(MMIO_BASE + 0x215040)
#define MUART_ENABLE		0x3
#define MUART_MODE_8BIT		0x3
#define MUART_FIFO_FULL		0x0
#define MUART_FIFO_CLEAR	0x6
#define MUART_HAS_DATA		0x1
#define MUART_CAN_SEND		(1 << 5)

struct muart_map {
	uint32_t io;
	uint32_t ier;
	uint32_t iir;
	uint32_t lcr;
	uint32_t mcr;
	uint32_t lsr;
	uint32_t msr;
	uint32_t scratch;
	uint32_t cntl;
	uint32_t stat;
	uint32_t baud;
};

static volatile struct muart_map* _muart = (struct muart_map*)MUART_BASE;

void
muart_setup(void)
{
	_muart->iir |= MUART_FIFO_CLEAR;
	_muart->lcr |= MUART_MODE_8BIT;

	_muart->cntl |= MUART_ENABLE;
}

uint8_t
muart_read(void)
{
	while ((_muart->lsr & MUART_HAS_DATA) == MUART_FIFO_FULL);

	return _muart->io;
}

void
muart_send(uint8_t byte)
{	
	if (byte == '\n') {
		muart_send('\r');
	}

	while ((_muart->lsr & MUART_CAN_SEND) == MUART_FIFO_FULL);

	_muart->io = byte;
}
