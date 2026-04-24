#define UART0_BASE  0x44E09000

// Registros del AM335x UART (compatible TL16C750 / PL011)
#define UART_THR    0x00   // Transmit Holding Register
#define UART_LSR    0x14   // Line Status Register
#define UART_LSR_THRE 0x20 // Bit 5: TX Holding Register Empty

volatile unsigned int * const UART0 = (unsigned int *)UART0_BASE;

void uart_putc(char c) {
    // Espera a que el registro de transmisión esté vacío
    while (!(UART0[UART_LSR / 4] & UART_LSR_THRE));
    UART0[UART_THR / 4] = c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

void main() {
    uart_puts("Hello World\r\n");
    while (1);
}