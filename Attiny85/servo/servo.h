//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>
#include "globals.h"

void servo_start(byte temp_increment, d_word temp_wait_time);

void servo_stop(void);

void servo_update_position(d_word millis_now);

void servo_update_increment(d_word millis_now);

extern void SERVO_PWM(word time_on);
static inline void servo_set_position(word time_on) {
	SERVO_PWM(time_on);
}

#endif
