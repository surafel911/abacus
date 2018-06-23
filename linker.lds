SECTIONS
{
	. = 0x8000;

	.text ALIGN(4K) : {
		KEEP(*(.boot));
		*(.text*)
	}

	.rodata ALIGN(4K) : {
		*(.rodata*)
	}

	.data ALIGN(4K) : {
		*(.data*)
	}

	.bss ALIGN(4K) (NOLOAD) : {
		__bss_start = .;
		*(.bss*)
		. = ALIGN(16);
		__bss_end = .;
	}
}
