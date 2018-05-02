#ifndef ABACUS_MACROS_CLANG_H
#define ABACUS_MACROS_CLANG_H

#ifndef __aligned
#define __aligned(x)	__attribute__((align_value(x)))
#endif // __aligned

#endif // ABACUS_MACROS_CLANG_H
