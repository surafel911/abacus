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

/*
 *
 */
int
cpu_get_id(void);

/*
 *
 */
int
cpu_get_el(void);
#endif // ABACUS_CPU_H
