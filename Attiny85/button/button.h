//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include "globals.h"

void button_init(void);

byte button_is_pressed(void);

void button_update(d_word millis_now);

#endif
