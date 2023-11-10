/*
	UART.c
	
	Based off AtMega2560 datasheet
	
	Conner Knipp

*/

void uart_init(void);
void uart_transmit(char data);
void uart_print(const char* str);
unsigned char uart_recieve(void);
void uart_flush(void);


// UART Initialization
void uart_init(void) {
	UBRR0H = 0;					//set baud to 9600 for 16MHz clock
	UBRR0L = 103;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);			//enable USART0 receive/transmit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);			//8 data bits, no parity, 1 stop bit
}

// Transmit a char
void uart_transmit(char data) {
	while (!(UCSR0A & (1 << UDRE0)));	//Wait for empty transmit buffer
	UDR0 = data;	// Put data into buffer, send data
}

// Transmit a string
void uart_print(const char* str) {
	while (*str) {
		uart_transmit(*str++);
	}
}

// Receive character
unsigned char uart_recieve(void) {
	while(!(UCSR0A) & (1<<RXC0));
	return UDR0;
}

// Flush UART
void uart_flush(void){
	unsigned char dummy;
	while(UCSR0A & (1<<RXC0)) dummy = UDR0;
}
