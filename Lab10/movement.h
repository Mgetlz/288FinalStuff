#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "open_interface.h"


void move_forward(oi_t *sensor, int centimeters, int velocity);
void move_backward(oi_t *sensor_data, int millimeters, int velocity);
void turn_clockwise(oi_t *sensor, short degrees);
void turn_counterclockwise(oi_t *sensor_data, short degrees);
void lab_part_three(oi_t *sensor_data, int millimeters, int velocity);
