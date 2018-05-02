#ifndef ABACUS_MAILBOX_H
#define ABACUS_MAILBOX_H

#include <stdint.h>

enum mailbox_channel {
	MAILBOX_POWER_MANAGEMENT,
	MAILBOX_FRAMEBUFFER,
	MAILBOX_VIRTUAL_UART,
	MAILBOX_VCHIQ,
	MAILBOX_LEDS,
	MAILBOX_BUTTONS,
	MAILBOX_TOUCHSCREEN,
	MAILBOX_UNUSED,
	MAILBOX_TAGS_ARM_TO_VC,
	MAILBOX_TAGS_VC_TO_ARM,
};

uint32_t
mailbox_pop(enum mailbox_channel channel);

void
mailbox_push(enum mailbox_channel channel, uint32_t value);

#endif // ABACUS_MAILBOX_H
