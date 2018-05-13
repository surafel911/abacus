#include <mailbox.h>

#include <stdbool.h>
#include <stdint.h>

#include <bits.h>
#include <mmio.h>
#include <panic.h>

#define MAILBOX_BASE			(MMIO_BASE + 0xB880)
#define MAILBOX_COUNT			2
#define MAILBOX_STATUS_OK		0
#define MAILBOX_STATUS_FULL		0x80000000
#define MAILBOX_STATUS_EMPTY	0x40000000
#define MAILBOX_STATUS_LEVEL	0x400000FF
#define MAILBOX_CHANNEL			0xF
#define MAILBOX_CHANNEL_BITS	4

enum mailbox_id {
	MAILBOX_READ,
	MAILBOX_WRITE,
};

struct mailbox_map {
	uint32_t data;
	uint32_t unused[3];
	uint32_t peek;
	uint32_t status;
	uint32_t sender;
	uint32_t config;
};

static volatile struct mailbox_map* _mailboxes[MAILBOX_COUNT] = {
		(struct mailbox_map*)MAILBOX_BASE,
		(struct mailbox_map*)(MAILBOX_BASE + 0x20)
	};

static volatile struct mailbox_map*
mailbox_lookup(enum mailbox_id id)
{
	return _mailboxes[(int)id];
}

static inline void
mailbox_check_channel(enum mailbox_channel channel)
{
	if (channel == MAILBOX_CHANNEL_UNUSED) {
		panic();
	}
}

uint32_t
mailbox_pop(enum mailbox_channel channel)
{
	uint32_t data;
	volatile struct mailbox_map* mailbox;

	mailbox_check_channel(channel);

	mailbox = mailbox_lookup(MAILBOX_READ);

	while (true) {
		while ((mailbox->status & MAILBOX_STATUS_EMPTY) != MAILBOX_STATUS_OK);

		data = mailbox->data;
		if ((data & MAILBOX_CHANNEL_BITS) == (int)channel) {
			bits_clear((volatile uint32_t*)&data, MAILBOX_CHANNEL_BITS);
			return data;
		}
	}
}

void
mailbox_push(enum mailbox_channel channel, intptr_t address)
{
	uint32_t data;
	volatile struct mailbox_map* mailbox;

	mailbox_check_channel(channel);

	mailbox = mailbox_lookup(MAILBOX_WRITE);

	while ((mailbox->status & MAILBOX_STATUS_FULL) != MAILBOX_STATUS_OK);

	data = ((uint32_t)address | channel);

	mailbox->data = data;
}
