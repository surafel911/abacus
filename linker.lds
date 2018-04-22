SECTIONS
{
	. = 0x8000;

	.text : {
		KEEP(*(.boot));
		*(.text*)
	}

	.data : {
		*(.data*)
	}

	.bss : {
		. = ALIGN(16);
		__bss_start = .;
		*(.bss*)
		. = ALIGN(16);
		__bss_nlwords = (. - __bss_start);
	}
}
