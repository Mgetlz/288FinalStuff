#include "servo.h"





void servo_init(void) {
    SYSCTL_RCGCGPIO_R |= 0b10;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R |= 0x700000;
    GPIO_PORTB_DEN_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20;
    
    SYSCTL_RCGCTIMER_R |= 0b10;
    TIMER1_CTL_R &= 0xFEFF;
    TIMER1_CFG_R |= 0x4;
    TIMER1_TBMR_R |= 0x00A;

    TIMER1_CTL_R |= ~0x4000;
    TIMER1_TBILR_R |= (320000 & 0xFFFF);
    TIMER1_TBPR_R  |= (320000 >> 16);

   pulseWidth = 0;
   servo_move(pulseWidth);
    

    TIMER1_TBMATCHR_R |= ((320000 - pulseWidth) & 0xFFFF);
    TIMER1_TBPMR_R |= ((320000 - pulseWidth) >> 16);

    TIMER1_CTL_R |= 0x100;

}




void servo_move(int degrees) {
    pulseWidth = ((27500 * (degrees/180.0)) + 900);

    TIMER1_TBMATCHR_R = ((320000 - pulseWidth) & 0xFFFF);
    TIMER1_TBPMR_R |= ((320000 - pulseWidth) >> 16);
    timer_waitMillis(100);

}


