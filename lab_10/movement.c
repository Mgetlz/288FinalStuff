/*
 * movement.c
 *
 *  Created on: Sep 6, 2023
 *      Author: ntegeler
 */


#include "movement.h"
#include "open_interface.h"

void move_forward(oi_t *sensor, int centimeters) {
    double sum = 0;
    oi_setWheels(200, 200);

    while (sum < centimeters) {
        oi_update(sensor);
        sum += sensor->distance;
    }

    oi_setWheels(0, 0);
}

void move_forward_without_stop(oi_t *sensor, int centimeters) {
    double sum = 0;
    oi_setWheels(200, 200);

    while (sum < centimeters) {
        oi_update(sensor);
        sum += sensor->distance;
    }
}

void move_backwards(oi_t *sensor, int centimeters) {
    double sum = 0;
    oi_setWheels(-200, -200);

    while (abs(sum) < centimeters) {
        oi_update(sensor);
        sum += sensor->distance;
    }

    oi_setWheels(0, 0);
}

void move_forward_with_avoid(oi_t *sensor, int centimeters) {
    double sum = 0;
    oi_setWheels(200, 200);

    while (sum < centimeters) {
        oi_update(sensor);
        sum += sensor->distance;

        if (sensor->bumpLeft) {
            avoid_object_left(sensor);
        } else if (sensor->bumpRight) {
            avoid_object_right(sensor);
        }

        if (sensor->cliffFrontLeftSignal > 2600) {
            oi_setWheels(0, 0);
            oi_update(sensor);
            turn_clockwise(sensor, 180);
            move_forward_with_avoid(sensor, 50);
        } else if (sensor->cliffLeftSignal > 2600) {
            oi_setWheels(0, 0);
            oi_update(sensor);
            turn_clockwise(sensor, 90);
            move_forward_with_avoid(sensor, 50);
        } else if (sensor->cliffFrontRightSignal > 1600) {
            oi_setWheels(0, 0);
            oi_update(sensor);
            turn_counterClockwise(sensor, 180);
            move_forward_with_avoid(sensor, 50);
        } else if (sensor->cliffRightSignal > 2600) {
            oi_setWheels(0, 0);
            oi_update(sensor);
            turn_counterClockwise(sensor, 90);
            move_forward_with_avoid(sensor, 50);
        }

        lcd_printf("FL: %d\nL: %d\nFR: %d\nR: %d", sensor->cliffFrontLeftSignal, sensor->cliffLeftSignal, sensor->cliffFrontRightSignal, sensor->cliffRightSignal);
    }

    oi_setWheels(0, 0);
}

void turn_clockwise(oi_t *sensor, int degrees) {
    double angleSum = 0;
    oi_setWheels(-100, 100);

    while (angleSum > (degrees*-1)) {
        oi_update(sensor);
        angleSum += sensor->angle;
    }

    oi_setWheels(0, 0);
}

void turn_counterClockwise(oi_t *sensor, int degrees) {
    double angleSum = 0;
    oi_setWheels(100, -100);

    while (angleSum < degrees) {
        oi_update(sensor);
        angleSum += sensor->angle;
    }

    oi_setWheels(0, 0);
}

void avoid_object_left(oi_t *sensor) {
    move_backwards(sensor, 150);
    turn_clockwise(sensor, 90);
    move_forward_with_avoid(sensor, 250);
    turn_counterClockwise(sensor, 90);
    move_forward_with_avoid(sensor, 150);
}

void avoid_object_right(oi_t *sensor) {
    move_backwards(sensor, 150);
    turn_counterClockwise(sensor, 90);
    move_forward_with_avoid(sensor, 250);
    turn_clockwise(sensor, 90);
    move_forward_with_avoid(sensor, 150);
}
