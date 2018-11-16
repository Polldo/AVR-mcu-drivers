//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "uart.h"

#define PIN_READ 2
#define PIN_WRITE 1

extern volatile byte is_data_received;
extern volatile byte data_read;

void uart_init(void) {
	DDRB &= ~(1 << PIN_READ);
	PORTB &= ~(1 << PIN_READ);
	DDRB |= 1 << PIN_WRITE;
	PORTB |= 1 << PIN_WRITE;
	is_data_received = 0x00;
	data_read = 0x00;
	data_write = 0x00;
	sei();
}

void uart_listen(void) {
	GIMSK |= (1<<PCIE);
	PCMSK = (1<<PIN_READ);
}

void uart_listen_stop(void) {
	GIMSK &= ~(1<<PCIE);
	PCMSK &= ~(1<<PIN_READ);
}

byte uart_data_read(void) {
	is_data_received = 0x00;
	return data_read;
}

byte uart_data_received_feedback(void) {
	return is_data_received;
}

byte uart_wait_byte(void) {
	while(!is_data_received);
	return uart_data_read();
}

byte uart_timed_wait_data(d_word timeout) {
	milliseconds_start();
	d_word millis_start = milliseconds_get();
	while((!is_data_received) && (milliseconds_get() - millis_start < timeout));
	milliseconds_stop();
	return is_data_received;
}

word uart_wait_word(void) {
	while(!is_data_received);
	byte lower = uart_data_read();
	while(!is_data_received);
	byte upper = uart_data_read(); 
	return ( ( ((word) lower) << 8 ) | (word) upper ); 
}
