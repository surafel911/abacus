section = .boot

.global _start

_init:
		ldr		x0, =_start
		mov		sp, x0
		b		.

_start:
		mrs		x0, mpidr_el1
		and		x0, x0, #3
		cbz		x0, _init
.loop:	wfe
		b		.loop
