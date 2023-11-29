#include "adc.h"
#include "uart.h"
#include "Timer.h"
#include "lcd.h"





void adc_init() {
    SYSCTL_RCGCGPIO_R |= 0b10;
    SYSCTL_RCGCADC_R |= 0b01;


    GPIO_PORTB_AFSEL_R |= 0b10000;

    GPIO_PORTB_DIR_R &= 0b11101111;
    GPIO_PORTB_DEN_R &= 0b11101111;

    GPIO_PORTB_AMSEL_R |= 0b00010000;

    GPIO_PORTB_ADCCTL_R |= 0x00;

    ADC0_ACTSS_R &= 0xFFFE;


    ADC0_EMUX_R &= 0xFFF0;
    ADC0_SSMUX0_R |= 0xA;
    ADC0_SAC_R |= 0x3;

    ADC0_SSCTL0_R = 0b0110;

    ADC0_ACTSS_R |= 0x1;
}
float adc_read(void) {
    ADC0_PSSI_R |= 0x00000001;


    while ((ADC0_RIS_R & 1) == 0) {

    }

    ADC0_ISC_R = 0x01;
    return ADC0_SSFIFO0_R;

}
