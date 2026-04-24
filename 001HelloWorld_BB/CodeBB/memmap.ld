ENTRY(_start)

SECTIONS
{
    . = 0x80000000; /*Ram inicia en beagle*/

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
