#ifndef ABACUS_CPU_H
#define ABACUS_CPU_H

/*
 * Enables distrobution of interrupts to the CPU.
 */
void
cpu_intr_enable(void);

/*
 * Disables distrobution of interrupts to the CPU.
 */
void
cpu_intr_disable(void);

/*
 * Stops execution until the CPU receives an interrupt.
 */
void
cpu_idle(void);

/*
* Halts  execution on the CPU.
*/
void
cpu_halt(void);

#endif // ABACUS_CPU_H
