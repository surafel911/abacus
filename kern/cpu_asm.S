.section .text

.global cpu_idle
cpu_idle:
		wfi
		ret

.global cpu_halt
cpu_halt:
.halt:	wfe
		b		.halt
		ret

.global exception_setup
exception_setup:
		msr		daifclr, #2
		adr		x0, exception_table
		msr		vbar_el1, x0
		ret

irq_handler:
		stp		x0, x1, [sp, #-16]

.global exception_table
exception_table:
.balign 128
.balign 128
.balign 128
.balign 128
.balign 128
		bl		irq_handler
