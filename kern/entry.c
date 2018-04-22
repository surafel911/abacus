#include <stdbool.h>
#include <stdint.h>

extern void
kern_entry(void)
{
//	*(uint32_t*)0x3F215004 |= 1;
	
	*(uint32_t*)0x3F215068 = 270;

	while (true) {
		while (!(*(uint32_t*)0x3F215054 & (1 << 5)))

		*(uint32_t*)0x3F215040 = 'a';
	}
}
