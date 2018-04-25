#ifndef ABACUS_MUART_H
#define ABACUS_MUART_H

#include <stdint.h>

uint8_t
muart_read(void);

void
muart_send(uint8_t byte);

#endif // ABACUS_MUART_H
