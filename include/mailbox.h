#ifndef ABACUS_MAILBOX_H
#define ABACUS_MAILBOX_H

#include <stdint.h>

enum mailbox_channel {
	MAILBOX_CHANNEL_POWER,
	MAILBOX_CHANNEL_FRAMEBUFFER,
	MAILBOX_CHANNEL_VUART,
	MAILBOX_CHANNEL_VCHIQ,
	MAILBOX_CHANNEL_LEDS,
	MAILBOX_CHANNEL_BUTTONS,
	MAILBOX_CHANNEL_TOUCHHSCREEN,
	MAILBOX_CHANNEL_UNUSED,
	MAILBOX_TAGS_ARM_TO_VC,
	MAILBOX_TAGS_VC_TO_ARM,
};

uint32_t
mailbox_pop(enum mailbox_channel channel);

void
mailbox_push(enum mailbox_channel channel, intptr_t address);

#endif // ABACUS_MAILBOX_H
