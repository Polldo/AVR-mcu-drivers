//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#include "button.h"

#define PIN_BTN 3
#define BTN_MASK (1 << PIN_BTN)
#define COUNT_VALUE 50
#define CHECK_FREQ 10

static d_word last_check;
static byte is_pressed;
static byte count_press;

void button_init(void) {
	DDRB &= ~BTN_MASK;
	PORTB |= BTN_MASK;
	last_check = 0;
	count_press = COUNT_VALUE;
	is_pressed = 0;
}

byte button_is_pressed(void) {
	byte temp_pressed = is_pressed;
	is_pressed = 0;
	return temp_pressed;
}

void button_update(d_word millis_now) {
	d_word delta = millis_now - last_check;
	if (delta > CHECK_FREQ) {
		last_check = millis_now;
		if (!(PINB & BTN_MASK)) {
			if(!(--count_press)) {
				is_pressed = 1;
				count_press = COUNT_VALUE;
			}
		} else {
			count_press = COUNT_VALUE;
		}			
	}
}

