//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>

#define PIN_SERVO 3
#define REG_DATA_HIGH r25
#define REG_DATA_LOW r24

.global SERVO_PWM
SERVO_PWM:
	cli
	sbi		_SFR_IO_ADDR(PORTB), PIN_SERVO
SERVO_LOOP:
	nop
	nop
	nop
	nop
	subi 	REG_DATA_LOW, 1
	sbci	REG_DATA_HIGH, 0
	brne	SERVO_LOOP
	cbi		_SFR_IO_ADDR(PORTB), PIN_SERVO
	sei
	ret
