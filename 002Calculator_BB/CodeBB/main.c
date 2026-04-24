#define UART0_BASE 0x44E09000

#define UART_LSR      0x14  // Line Status Register
#define UART_LSR_THRE 0x20  // Transmit Holding Register Empty
#define UART_LSR_DR   0x01  // Data Ready

#define WDT_BASE 0x44E35000
#define WDT_WSPR *(volatile unsigned int *)(WDT_BASE + 0x48)
#define WDT_WWPS *(volatile unsigned int *)(WDT_BASE + 0x34)

volatile unsigned char * const UART0_TX_RX = (unsigned char *)UART0_BASE;
volatile unsigned int * const UART0_STATUS = (unsigned int *)(UART0_BASE + UART_LSR);

void disable_watchdog() {
    WDT_WSPR = 0xAAAA;
    while (WDT_WWPS != 0);
    WDT_WSPR = 0x5555;
    while (WDT_WWPS != 0);
}

// Function to send a single character via UART
void uart_putc(char c) {
    // Wait until there is space in the FIFO
    while ((*UART0_STATUS & UART_LSR_THRE) == 0);
    *UART0_TX_RX = c;
}

// Function to receive a single character via UART
char uart_getc() {
    // Wait until data is available
    while ((*UART0_STATUS & UART_LSR_DR) == 0);
    return (char)(*UART0_TX_RX);
}

// Function to send a string via UART
void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

// Function to receive a line of input via UART
void uart_gets_input(char *buffer, int max_length) {
    int i = 0;
    char c;
    while (i < max_length - 1) { // Leave space for null terminator
        c = uart_getc();

        if (i == 0 && (c == '\n' || c == '\r')) {
            continue;
        }

        if (c == '\n' || c == '\r') {
            uart_putc('\n'); // Echo newline
            break;
        }
        uart_putc(c); // Echo character
        buffer[i++] = c;
    }
    buffer[i] = '\0'; // Null terminate the string
}

// Simple function to convert string to integer
int uart_atoi(const char *s) {
    int num = 0;
    int sign = 1;
    int i = 0;

    // Handle optional sign
    if (s[i] == '-') {
        sign = -1;
        i++;
    }

    for (; s[i] >= '0' && s[i] <= '9'; i++) {
        num = num * 10 + (s[i] - '0');
    }

    return sign * num;
}

// Function to convert integer to string
void uart_itoa(int num, char *buffer) {
    int i = 0;
    int is_negative = 0;

    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num > 0 && i < 14) { // Reserve space for sign and null terminator
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    // Reverse the string
    int start = 0, end = i - 1;
    char temp;
    while (start < end) {
        temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}

void main() {
    char input1[16];
    char input2[16];
    char result_str[16];
    int num1, num2, sum;

    disable_watchdog();
    uart_puts("Program: Add Two Numbers\n");

    while (1) {
        // Prompt for first number
        uart_puts("Enter first number: ");
        uart_gets_input(input1, sizeof(input1));
        num1 = uart_atoi(input1);

        // Prompt for second number
        uart_puts("Enter second number: ");
        uart_gets_input(input2, sizeof(input2));
        num2 = uart_atoi(input2);

        // Calculate sum
        sum = num1 + num2;

        // Convert sum to string
        uart_itoa(sum, result_str);

        // Display the result
        uart_puts("Sum: ");
        uart_puts(result_str);
        uart_putc('\n');
    }
}
