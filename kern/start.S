.section .boot

.global _start
_start:
		mrs		x0, mpidr_el1
		and		x0, x0, #3
		cbz		x0, _init
.idle:	wfe
		b		.idle

_bss_setup:
		adr		x1, __bss_end
		adr		x2, __bss_start
.zero:	str		xzr, [x2], #8
		cmp		x1, x2
		b.ne	.zero

_stack_setup:
		ldr		x0, =_start
		mov		sp, x0

_init:
		b		_stack_setup
		b		_bss_setup
		b		kern_main
