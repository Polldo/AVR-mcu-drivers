//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>

#define PIN_READ 2
#define PIN_WRITE 1
#define CPU_CLK 8000000
#define BAUD_RATE 38400
#define BIT_TIME (CPU_CLK / BAUD_RATE)
#define FIRST_DELAY ((BIT_TIME / 2 - 15) / 3)
#define BIT_DELAY ((BIT_TIME - 7) / 3)
#define SREG_SAVE r0
#define REG_COUNT r18
#define REG_BIT_COUNT r19
#define REG_DATA r24

.extern	data_read
.extern is_data_received
.global PCINT0_vect
PCINT0_vect:
	push	SREG_SAVE
	in		SREG_SAVE, _SFR_IO_ADDR(SREG)
	sbic	_SFR_IO_ADDR(PINB), PIN_READ
	rjmp	PCIN_EXIT
	push 	REG_COUNT
	push	REG_BIT_COUNT
	push 	REG_DATA
	ldi 	REG_COUNT, FIRST_DELAY
FIRST_BIT_LOOP_R:
	dec 	REG_COUNT
	brne 	FIRST_BIT_LOOP_R
	ldi		REG_COUNT, BIT_DELAY
	ldi		REG_BIT_COUNT, 8
BIT_TIME_LOOP_R:
	dec 	REG_COUNT
	brne 	BIT_TIME_LOOP_R
	ldi		REG_COUNT, BIT_DELAY
	lsr		REG_DATA
	sbic	_SFR_IO_ADDR(PINB), PIN_READ
	ori		REG_DATA, 0x80
	dec		REG_BIT_COUNT
	brne	BIT_TIME_LOOP_R
	ldi		REG_COUNT, BIT_DELAY
STOP_BIT_LOOP_R:
	dec		REG_COUNT
	brne	STOP_BIT_LOOP_R
	sts		data_read, REG_DATA
	ldi		REG_DATA, 0x01
	sts		is_data_received, REG_DATA
	pop 	REG_DATA
	pop		REG_BIT_COUNT
	pop		REG_COUNT
PCIN_EXIT:
	out 	_SFR_IO_ADDR(SREG), SREG_SAVE
	pop		SREG_SAVE
	reti

.global UART_WRITE_ROUTINE
UART_WRITE_ROUTINE:
	push 	REG_COUNT
	push	REG_BIT_COUNT
	cbi		_SFR_IO_ADDR(PORTB), PIN_WRITE
	ldi 	REG_COUNT, BIT_DELAY
	ldi		REG_BIT_COUNT, 8
BIT_TIME_LOOP_W:
	dec 	REG_COUNT
	brne 	BIT_TIME_LOOP_W
	ldi		REG_COUNT, BIT_DELAY
	sbi		_SFR_IO_ADDR(PORTB), PIN_WRITE
	sbrs	REG_DATA, 0
	cbi		_SFR_IO_ADDR(PORTB), PIN_WRITE
	lsr		REG_DATA
	dec		REG_BIT_COUNT
	brne	BIT_TIME_LOOP_W
	ldi		REG_COUNT, BIT_DELAY
LAST_BIT_LOOP_W:
	dec		REG_COUNT
	brne	LAST_BIT_LOOP_W
	sbi		_SFR_IO_ADDR(PORTB), PIN_WRITE
	ldi		REG_COUNT, BIT_DELAY
STOP_BIT_LOOP_W:
	dec		REG_COUNT
	brne	STOP_BIT_LOOP_W
	pop		REG_BIT_COUNT
	pop		REG_COUNT
	ret
