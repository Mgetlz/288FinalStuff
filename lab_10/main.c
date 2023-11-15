/*
 * main.c
 *
 *  Created on: Nov 1, 2023
 *      Author: jddwight
 */

#include "servo.h"
#include "movement.h"
#include "open_interface.h"
#include "lcd.h"
#include "timer.h"

volatile extern int button_event;
volatile extern int button_num;

/*
void main() {
    servo_init();
    lcd_init();
    button_init();
    init_button_interrupts();
    lcd_init();
    uart_init();

    //servo_cal_vals cal = servo_cal();


    int degrees = servo_move(90);

    int direction = 1;
    while (1) {
        if (direction == 1) {
            lcd_printf("1: right 1 deg\n2: right 5 deg\n3: swap dir\n4: turn to 0 deg");
        } else {
            lcd_printf("1: left 1 deg\n2: left 5 deg\n3: swap dir\n4: turn to 180 deg");
        }

        if (button_event == 1) {
            if (direction == 1) {
                if (button_num == 1) {
                    degrees--;
                    servo_move(degrees);
                } else if (button_num == 2) {
                    degrees -= 5;
                    servo_move(degrees);
                } else if (button_num == 3) {
                    direction = 2;
                } else if (button_num == 4) {
                    degrees = 0;
                    servo_move(0);
                }
            } else {
                if (button_num == 1) {
                    degrees++;
                    servo_move(degrees);
                } else if (button_num == 2) {
                    degrees += 5;
                    servo_move(degrees);
                } else if (button_num == 3) {
                    direction = 1;
                } else if (button_num == 4) {
                    degrees = 180;
                    servo_move(degrees);
                }
            }

            if (degrees < 0) {
                degrees = 0;
                servo_move(0);
            } else if (degrees > 180) {
                degrees = 180;
                servo_move(180);
            }

            char message[50];

            int angle = ((320000 - ((TIMER1_TBPMR_R << 16) + TIMER1_TBMATCHR_R)) / 156) - 50;
            int match = (TIMER1_TBPMR_R << 16) + TIMER1_TBMATCHR_R;

            sprintf(message, "Angle: %d\n\rMATCHR Val: %d\n\r\n", angle, match);

            int i;
            for (i = 0; i < strlen(message); i++) {
                uart_sendChar(message[i]);
            }

            button_event = 0;
        }
    }

}
//*/

