#include <mailbox.h>

#include <stdint.h>

#include <mmio.h>

#define MAILBOX_BASE			(MMIO_BASE + 0xB880)
#define MAILBOX_COUNT			2
#define MAILBOX_FULL			0x80000000
#define MAILBOX_EMPTY			0x40000000
#define MAILBOX_LEVEL			0x400000FF
#define MAILBOX_CHANNEL_BITS	0xFF

enum mailbox_id {
	MAILBOX_READ,
	MAILBOX_WRITE,
};

struct mailbox {
	uint32_t data;
	uint32_t unused[3];
	uint32_t peek;
	uint32_t status;
	uint32_t sender;
	uint32_t config;
};

static struct mailbox* _mailboxes[MAILBOX_COUNT] = {
		(struct mailbox*)MAILBOX_BASE,
		(struct mailbox*)(MAILBOX_BASE + 0x30)
	};

static struct mailbox*
mailbox_lookup(enum mailbox_id id)
{
	return _mailboxes[(uint8_t)id];
}

uint32_t
mailbox_pop(enum mailbox_channel channel)
{
	uint32_t data;
	struct mailbox* mailbox;
	
	mailbox = mailbox_lookup(MAILBOX_READ);

	while (!(mailbox->status & MAILBOX_EMPTY));

	data = mailbox->data;
	if ((data & MAILBOX_CHANNEL_BITS) == (uint32_t)channel) {
		return (data >> 4);
	} 

	return 0;
}

void
mailbox_push(enum mailbox_channel channel, uint32_t value)
{
	uint32_t data;
	struct mailbox* mailbox;

	mailbox = mailbox_lookup(MAILBOX_WRITE);

	while (!(mailbox->status & MAILBOX_FULL));

	data = (value <<  4);
	data &= (uint8_t)channel;

	mailbox->data = data;
}
