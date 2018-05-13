#ifndef ABACUS_MACROS_CLANG_H
#define ABACUS_MACROS_CLANG_H

#ifndef __aligned
	#define __aligned(x)	__attribute__((align_value(x)))
#endif // __aligned

#ifndef __noreturn
	#define __noreturn		__attribute__((noreturn))
#endif // __noreturn

#endif // ABACUS_MACROS_CLANG_H
