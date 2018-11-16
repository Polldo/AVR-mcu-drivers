//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "servo.h"

#define PIN_SERVO 3
#define PWM_PERIOD 17 //expressed in milliseconds
#define SERVO_UPPER_LIMIT 2000 + 500
#define SERVO_LOWER_LIMIT 1000 - 500

static int8_t servo_direction;
static int8_t servo_position_increment;
static word servo_time_on; //expressed in microseconds. Range from 1000 to 2000.
static d_word millis_servo_wait_time; //Time to wait before updating the servo position.
static d_word millis_last_update_time;
static d_word millis_start_cycle_time;

void servo_start(byte temp_increment, d_word temp_wait_time) {
	DDRB |= (1<<PIN_SERVO);
	PORTB &= ~(1<<PIN_SERVO);
	servo_direction = 1;
	servo_position_increment = temp_increment;
	servo_time_on = (SERVO_UPPER_LIMIT + SERVO_LOWER_LIMIT) / 2;
	millis_servo_wait_time = temp_wait_time;
	millis_last_update_time = 0;
	millis_start_cycle_time = 0;
}

void servo_stop(void) {
	PORTB &= ~(1<<PIN_SERVO);
}

void servo_update_position(d_word millis_now) {
	if (millis_now - millis_start_cycle_time >= PWM_PERIOD) {
		servo_set_position(servo_time_on);
		millis_start_cycle_time = millis_now;
	}
}

void servo_update_increment(d_word millis_now) {
	if (millis_now - millis_last_update_time >= millis_servo_wait_time) {
		servo_time_on += servo_direction * servo_position_increment;
		if (servo_time_on >= SERVO_UPPER_LIMIT || servo_time_on <= SERVO_LOWER_LIMIT) {
			servo_direction *= -1;
		}
		millis_last_update_time = millis_now;
	}
}
