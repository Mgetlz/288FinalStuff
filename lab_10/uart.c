/*
*
*   uart.c
*
*
*
*
*
*   @author
*   @date
*/

#include "uart.h"
volatile char uart_data;
volatile char flag;

void uart_init(void){
    SYSCTL_RCGCGPIO_R |= 0b000010;
    SYSCTL_RCGCUART_R |= 0b00000010;
    timer_waitMillis(1);            // Small delay before accessing device after turning on clock
    GPIO_PORTB_AFSEL_R |= 0b00000011;
    //GPIO_PORTB_PCTL_R &= 0x00000011;     // Force 0's in the disired locations
    GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the disired locations
    GPIO_PORTB_DEN_R |= 0x03;
    //GPIO_PORTB_DIR_R &= 0b00000010;      // Force 0's in the disired locations
    GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the disired locataions

    //compute baud values [UART clock = 16 MHz]
    double brd;
    double fbrd;
    int ibrd;

    brd = 16000000 / (16 * 115200);
    ibrd = (int)brd;
    fbrd = brd - ibrd;

    UART1_CTL_R &= 0xFFFE;
    UART1_IBRD_R = 0b00001000;
    UART1_FBRD_R = 0b00101100;
    UART1_LCRH_R |= 0b01100000;
    UART1_CC_R |= 0x00;
    UART1_CTL_R |= 0x0001;
}

void uart_sendChar(char data){
	while (UART1_FR_R & 0b00100000);
    UART1_DR_R = data;
}

char uart_receive(void){
	while (UART1_FR_R & 0b00010000);

	char data;
	data = UART1_DR_R;

	return data;
}

void uart_sendStr(const char *data){
	//TODO for reference see lcd_puts from lcd.c file
}

void uart_interrupt_init(void) {
    // Enable interrupts for receiving bytes through UART1
    UART1_IM_R |= 0x0010; //enable interrupt on receive - page 924

    // Find the NVIC enable register and bit responsible for UART1 in table 2-9
    // Note: NVIC register descriptions are found in chapter 3.4
    NVIC_EN0_R |= 0x0040; //enable uart1 interrupts - page 104

    // Find the vector number of UART1 in table 2-9 ! UART1 is 22 from vector number page 104
    IntRegister(INT_UART1, uart_interrupt_handler); //give the microcontroller the address of our interrupt handler - page 104 22 is the vector number
}

void uart_interrupt_handler(void) {
    // STEP1: Check the Masked Interrupt Status
    if (UART1_MIS_R & 0x0010) {
        //STEP2:  Copy the data
        flag = 1;
        uart_data = uart_receive();


        //STEP3:  Clear the interrupt
        UART1_ICR_R |= 0x0010;
    }
}
