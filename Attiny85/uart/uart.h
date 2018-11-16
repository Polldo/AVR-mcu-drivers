//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "milliseconds.h"

void uart_init(void);

void uart_listen(void);

void uart_listen_stop(void);

extern void UART_WRITE_ROUTINE(byte data);
static inline void uart_data_write(byte data) {
	UART_WRITE_ROUTINE(data);
}

byte uart_data_read(void);

byte uart_data_received_feedback(void);

byte uart_wait_byte(void);

byte uart_timed_wait_data(d_word timeout);

word uart_wait_word(void);

#endif
