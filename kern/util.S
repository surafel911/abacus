.section .text

.global PUT32
PUT32:
		str 	w1, [x0]
		ret

.global GET32
GET32:
		ldr 	w0, [x0]
		ret
