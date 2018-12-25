.section .boot

bss_setup:
		adr		x1, __bss_end
		adr		x2, __bss_start
.zero:		stp		xzr, xzr, [x2], #16
		cmp		x1, x2
		b.ne		.zero
		ret

stack_setup:
		ldr		x0, =_start
		mov		sp, x0
		ret

aux_setup:
		movk	x0, #0x5004
		movk	x0, #0x3f21, lsl #16
		str		x1, [x0]
		ret

bootstrap:
		bl		stack_setup
		bl		bss_setup
		bl		aux_setup
		bl		kern_main
		b 		cpu_halt

.global _start
_start:
		mrs		x0, mpidr_el1
		and		x0, x0, #3
		cbz		x0, bootstrap
		b		cpu_halt
