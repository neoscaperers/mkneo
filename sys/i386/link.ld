ENTRY(_start)

SECTIONS
{
    . = 1M;
    
    .multiboot : {
        *(.multboot)
    }

    .multiboot_stub_data : {
        *(.multiboot_stub_data)
    }

    .multiboot_stub_text : {
        *(.multiboot_stub_text)
    }

    . = ALIGN(4K);
    . += 0xC0000000;
    _kernel_start = ALIGN(4K);
    _text_start = ALIGN(4K);
    .text ALIGN (4K) : AT (ADDR (.text) - 0xC0000000)
	{
		*(.text)
	}
    _text_end = ALIGN(4K);
	_rodata_start = ALIGN(4K);
    .rodata ALIGN (4K) : AT (ADDR (.rodata) - 0xC0000000)
	{
		*(.rodata)
	}
    _rodata_end = ALIGN(4K);
	_data_start = ALIGN(4K);
    .data ALIGN (4K) : AT (ADDR (.data) - 0xC0000000)
	{
		*(.data)
	}
    _data_end = ALIGN(4K);
    _bss_start = ALIGN(4K);
	.bss ALIGN (4K) : AT (ADDR (.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
	}
    _bss_end = ALIGN(4K);
    _kernel_end = ALIGN(4K);
}