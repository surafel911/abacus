#ifndef ABACUS_MACROS_H
#define ABACUS_MACROS_H

#if defined(__GNUC__)
	#include <macros_gnu.h>
#elif defined(__clang__)
	#include <macros_clang.h>
#endif // COMPILER

#endif // ABACUS_MACROS_H
