.section .text

#define FRAME_SIZE	248

exception_table:
.balign 128
.balign 128
.balign 128
.balign 128
		bl		save_register_state
		mrs		x0, esr_el1
		bl		cpu_synchronous_handler
		bl		load_register_state
		eret
.balign 128
		bl		save_register_state
		bl		enable_exceptions
		bl		cpu_irq_handler
		bl		load_register_state
		eret
.balign 128
		bl		save_register_state
		bl		enable_exceptions
		bl		cpu_fiq_handler
		bl		load_register_state
		eret
enable_exceptions:
		msr		daifclr, #2
		ret

save_register_state:
		sub	 	sp, sp, #FRAME_SIZE
		stp		x0, x1, [sp] 
		stp		x2, x3, [sp] 
		stp		x4, x5, [sp] 
		stp		x6, x7, [sp]
		stp		x8, x9, [sp]
		stp		x10, x11, [sp]
		stp		x12, x13, [sp]
		stp		x14, x15, [sp]
		stp		x16, x17, [sp]
		stp		x18, x19, [sp]
		stp		x20, x21, [sp]
		stp		x22, x23, [sp]
		stp		x24, x25, [sp]
		stp		x26, x27, [sp]
		stp		x28, x29, [sp]
		str		x30, [sp]
		ret

load_register_state:
		ldr		x30, [sp]
		ldp		x29, x28, [sp]
		ldp		x27, x26, [sp]
		ldp		x25, x24, [sp]
		ldp		x23, x22, [sp]
		ldp		x21, x20, [sp]
		ldp		x19, x18, [sp]
		ldp		x17, x16, [sp]
		ldp		x15, x14, [sp]
		ldp		x13, x12, [sp]
		ldp		x11, x10, [sp]
		ldp		x9, x8, [sp]
		ldp		x7, x6, [sp]
		ldp		x5, x4, [sp]
		ldp		x3, x2, [sp]
		ldp		x1, x0, [sp]
		add		sp, sp, #FRAME_SIZE
		ret

.global cpu_intr_enable
cpu_intr_enable:
		adr		x0, exception_table
		msr		vbar_el1, x0
		ret

.global cpu_idle
cpu_idle:
		wfi
		ret

.global cpu_halt
cpu_halt:
		b		cpu_halt

.global cpu_get_id
cpu_get_id:
		mrs		x0, mpidr_el1
		ret

.global cpu_get_el
cpu_get_el:
		mrs		x0, currentel
		ret
