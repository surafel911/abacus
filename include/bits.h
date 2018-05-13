#ifndef ABACUS_BITS_H
#define ABACUS_BITS_H

#include <stdint.h>

inline void
bits_clear(volatile uint32_t* word, uint32_t clear)
{
	(*word) &= ~clear;
}

inline void
bits_write(volatile uint32_t* word, uint32_t clear, uint32_t value)
{
	bits_clear(word, clear);

	(*word) |= value;
}

#endif // ABACUS_BITS_H
