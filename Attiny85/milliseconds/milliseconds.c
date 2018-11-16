//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "milliseconds.h"

static volatile d_word millis;

void milliseconds_start(void) {
	millis = 0;
	TCNT1 = 0x00;
	TCCR1 |= (1<<CS12)+(1<<CS11);
	TIMSK |= (1<<TOIE1);
	sei();
}

void milliseconds_stop(void) {
	TCCR1 &= ~((1<<CS12)+(1<<CS11));
	TIMSK &= ~(1<<TOIE1);
}

d_word milliseconds_get(void) {
	d_word temp_millis;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		temp_millis = millis;
	}
	return temp_millis;
}

void milliseconds_delay(d_word msec) {
	d_word now = milliseconds_get();
	while (milliseconds_get() - now < msec);
}

ISR(TIM1_OVF_vect) {
	millis++;
}
