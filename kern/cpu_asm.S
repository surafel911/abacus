.section ".text"

.global cpu_idle
cpu_idle:
		wfi
		ret

.global cpu_halt
cpu_halt:
		wfe
		ret
