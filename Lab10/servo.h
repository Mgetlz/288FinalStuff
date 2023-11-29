

#ifndef SERVO_H_
#define SERVO_H_
#include "Timer.h"
#include "lcd.h"

volatile signed pulseWidth;

void servo_init(void);


void servo_move(int degrees);


#endif /* SERVO_H_ */
