//----------------------------------------
//
//		author: Paolo Calao			
//		mail:	paolo.calao@gmail.com
//		
//----------------------------------------

#ifndef MILLISECONDS_H
#define MILLISECONDS_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>
#include "globals.h"

void milliseconds_start(void);

void milliseconds_stop(void);

d_word milliseconds_get(void);

void milliseconds_delay(d_word msec);

#endif
