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

#define BAUD 9600
#define FOSC 4000000L
#define DIVIDER ((int)(FOSC/(16UL * BAUD) -1))  //Should be 25 for 9600/4MhZ
#define NINE_BITS 0
#define SPEED 0x4
#define RX_PIN TRISC5
#define TX_PIN TRISC4
#define _XTAL_FREQ 4000000.0    /*for 4mhz*/

void setup_comms(void);
void putch(unsigned char);
unsigned char getch(void);
unsigned char getche(void);

void Display(int mode);
unsigned int Tcount, Threshold;
int i, j, Touch[3], mode;

int main(int argc, char** argv) {
    // first set up system stuff:  Fosc, T0 and t1
// The 3 touch pads numbers are stored in Touch 0,1,2
    RA5 = 1;
    APFCON0 = 0x84; //This sets pins RC5 and RC4 as RX & TX on pic16f1829
    OSCCON  = 0x68; /* b6..4 = 1101 = 4MHz */
    TXCKSEL = 1;    // Note:!!!!!  OPPOSITE FOR 1825 VS 1829
    RXDTSEL = 1;  /*makes RC4 & 5 TX & RX for USART (Allows ICSP)*/
    ANSELC  = 0;    /* all ADC pins to digital I/O */
  //  TRISC   = 0;      /* set as output */
    LATC    = 0x00;   /* zero out */
    
    Touch[0] = 3;  // RA4 pad CPS3
    Touch[1] = 7;  // RC3 pad CPS7
    Touch[2] = 9;  //RC7  pad CPS9
    
    OPTION_REG =    0XC5;  // set up timer 0, and then timer 1
    T1CON =         0XC1;
    T1GCON =        0X81;       //81 is without toggle mode A1 is toggle mode
    CPSCON0 =       0X8C;   //Set up Touch sensing module control reg 0
    TRISA   =       0X10;
    TRISC   =       0XFF;
    PORTA   =       0;
    ANSELA  =       0X10;
    setup_comms();	// set up the USART - settings defined in usart.h
    LATA |=  (0X01 << 5);       //test flash led
    for (i=0; i< 0x7000; i++) continue;  //short delay
    LATA &= ~(1<<5);
    Threshold =    0x1000;  //using the threshold for all 3 channels
   
    while (1){
        mode=3;
//  Now initialize the timer0 and 1 and scan 3 pads
       for (j=0; j<3; j++){ 
        CPSCON1 =  Touch[j];          
        TMR1ON  =       0;
        TMR0    =       0;
        TMR1H   =       0;
        TMR1L   =       0;
        TMR1ON  =       1;
        TMR0IF  =       0;      //Clear the interrupt flag for Timer 1
        TMR0    =       0;  
    
        while (!TMR0IF) continue;   //wait here till Timer 0 overflows
        Tcount  =   (TMR1H<<8)+TMR1L;       //Save 16 bit count value in timer 1
        TMR0IF  =       0;      //Clear the interrupt flag for Timer 1
           if (Tcount < Threshold) mode=j;
       }
         Display(mode);      
    }

    return (EXIT_SUCCESS);
}

void Display (int delay){
    switch(delay){
        case 0:
            printf("C: Tcount = %x Threshold = %x\r\n", Tcount, Threshold);
            LATA |=  (0X01 << 5);
            for (i=0; i< 0x7000; i++) continue;  //short delay
          //  LATA &=   (~(0X01 << 5));
          //  for (i=0; i< 0x7000; i++) continue;  //short delay
            break;
        case 1:
            printf("B: Tcount = %x Threshold = %x\r\n", Tcount, Threshold);
           // LATA |=  (0X01 << 5);
           // for (i=0; i< 0x700; i++) continue;  //short delay
            LATA &=   (~(0X01 << 5));
            for (i=0; i< 0x7000; i++) continue;  //short delay            
            break;
        case 2:
            printf("A: Tcount = %x Threshold = %x\r\n", Tcount, Threshold);
            LATA |=  (0X01 << 5);
            for (i=0; i< 0x7000; i++) continue;  //short delay
            LATA &=   (~(0X01 << 5));
            for (i=0; i< 0x7000; i++) continue;  //short delay            
            break;  
        case 3:
            printf("Press Button\r\n");
            break;   //go here if no button pushed
    }
}

void setup_comms(void){

	RX_PIN = 1;
	TX_PIN = 1;
	SPBRG = DIVIDER;
	RCSTA = (NINE_BITS|0x90);
	TXSTA = (SPEED|NINE_BITS|0x20);
        TXEN=1;
        SYNC=0;
        SPEN = 1;
        BRGH=1;
}

void putch(unsigned char byte)
{
	/* output one byte */
	while(!TXIF)	/* set when register is empty */
		continue;
	TXREG = byte;
}

unsigned char getch() {
	/* retrieve one byte */
	while(!RCIF)	/* set when register is not empty */
		continue;
	return RCREG;
}

unsigned char getche(void)
{
	unsigned char c;
	putch(c = getch());
	return c;
}



