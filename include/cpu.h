#ifndef ABACUS_CPU_H
#define ABACUS_CPU_H

/*
 * Halts execution on the CPU.
 */
void
cpu_halt(void);

/*
 * Pauses execution until next interrupt.
 */
void
cpu_idle(void);

/*
 *
 */
void
cpu_setup(void);

#endif // ABACUS_CPU_H
