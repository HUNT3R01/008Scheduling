ENTRY(_start)

SECTIONS
{
    . = 0x82000000; /* Starting address in RAM Beagle*/

    .text :
    {
        *(.text*)
    }

    .data : AT (ADDR(.text) + SIZEOF(.text))
    {
        *(.data*)
    }

    .bss :
    {
        __bss_start = .;
        *(.bss*)
        __bss_end = .;
    }
}
