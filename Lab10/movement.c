#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "open_interface.h"


int move_forward(oi_t *sensor_data, int millimeters, int velocity) {
    double travelled = 0;
    oi_setWheels(velocity, velocity); // move forward
    while (travelled < millimeters) {
            oi_update(sensor_data);
            travelled += sensor_data->distance;
        }
    oi_setWheels(0, 0); // stop
    //oi_free(sensor);
    return travelled;
}

int move_backward(oi_t *sensor_data, int millimeters, int velocity) {
    double travelled = 0;
    oi_setWheels(-velocity, -velocity);
    while (travelled < millimeters) {
        oi_update(sensor_data);
        travelled -= sensor_data->distance;
    }
    oi_setWheels(0, 0);
    return travelled;
}

void turn_clockwise(oi_t *sensor_data, short degrees) {
        double botAngle = 0;
        //degrees += -2.24 - .658218;
        oi_setWheels(-100, 100); // move forward, max vel

        while (botAngle < degrees) {
            oi_update(sensor_data);
            botAngle -= sensor_data->angle;
            //degrees = degrees * (180 / M_PI);
        }

        oi_setWheels(0, 0);
        //oi_free(sensor);


}

void turn_counterclockwise(oi_t *sensor_data, short degrees) {
    double botAngle = 0;
    oi_setWheels(100, -100);
    while (botAngle < degrees) {
        oi_update(sensor_data);
        botAngle += sensor_data->angle;
    }
    oi_setWheels(0, 0);

}

void lab_part_three(oi_t *sensor_data, int millimeters, int velocity) {
    int totDistance = 0;
    int bumps = 0;
    oi_setWheels(velocity, velocity);
    while (totDistance <= millimeters) {
        oi_update(sensor_data);
        totDistance += sensor_data->distance;

        if (sensor_data->bumpLeft != 0) {
            move_backward(sensor_data, 150, 100);
            totDistance -= 150;
            turn_clockwise(sensor_data, 0);
            move_forward(sensor_data, 250, 100);
            turn_counterclockwise(sensor_data, 0);
            oi_setWheels(velocity, velocity);
            bumps++;
        }
        if (sensor_data->bumpRight != 0) {
            move_backward(sensor_data, 150, 100);
            totDistance -= 150;
            turn_counterclockwise(sensor_data, 0);
            move_forward(sensor_data, 250, 100);
            turn_clockwise(sensor_data, 0);
            oi_setWheels(velocity, velocity);
            bumps++;
        }
        lcd_printf("%d", totDistance);
    }
    lcd_printf("%d millimeters \ntraveled, %d\nobstacles avoided\n", totDistance, bumps);
    oi_free(sensor_data);
    oi_setWheels(0, 0);
}





