SECTIONS
{
	. = 0x8000;

	.text : {
		KEEP(*(.boot));
		*(.text*)
	}

	.rodata ALIGN(16) : {
		*(.rodata*)
	}

	.data ALIGN(16) : {
		*(.data*)
	}

	.bss (NOLOAD) : {
		. = ALIGN(16);
		__bss_start = .;
		*(.bss*)
		. = ALIGN(16);
		__bss_nlwords = (. - __bss_start);
	}
}
