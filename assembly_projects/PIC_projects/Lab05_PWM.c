/*
 * File:   Lab05_PWM.c
 * Author: MichaelAAmaya
 *
 * Created on March 4, 2016, 5:54 PM
 */
// PIC16LF1825 Configuration Bit Settings
// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#include <stdio.h>
#include <stdlib.h>

void delay();       // Function prototype for the delay function
unsigned int Dycy;  // Holds duty cycle for PWM signal

int main(int argc, char** argv) {
    APFCON1 = 0X01;     // This reassigns CCP module #2 to use RA5
    OSCCON = 0X6A;      // Sets CPU clock Fosc=4MHz
    ANSELA = 0;         // Turns off analog ins on portA (not really needed)
    TRISA |= (1 << 5);  // This sets our PWM pin to input (in off mode for now)
    PORTA = 0;          // Clear PortA
    Dycy = 0x80;        // sets max duty cycle
    PR2 = 0xFF;         // Sets the Timer 2 to count down from FF to 0
    CCP2CON = 0x0C;     // configures CCP#2 for PWM single wire mode
    CCPR2L = Dycy;      // loads upper 8 bits of duty cycle
    CCPTMRS = 0x00;     // Selects timer #2 to be used with CCP #2 module
    PIR1 &= 0XFF;       // Clear the flag, gets set at start of pwm period
    T2CON = 0X07;       // Sets Timer #2 on and prescaler for 1:64
    while (!(PIR1 & (1 << 1)))continue; //wait for start of next period
    TRISA = 0;          //  Now turn on the PWM at the start

    Dycy = 0xF0;        // set initial duty cycle
    
    while (1) {                  // infinite while loop
        // Decrement until duty cycle == 0
        while (Dycy > 0) {
            CCPR2L = Dycy--;    // CCPRxL gets duty cycle and then decrements
            delay();
        }
        delay();
        delay();
        // Increment until duty cycle == 0xF0
        while (Dycy <= 0xF0) {
            CCPR2L = Dycy++;    // CCPRxL gets duty cycle and then increments
            delay();
        }
    }

    return (EXIT_SUCCESS);
}

//  Delay function so it can be called
void delay(void) {
    int i;
    for (i = 0; i < 0xD0; i++) continue;
    return;
}


