/* 
 * File: Lab07_TempSensor.c  RS232F14c.c
 * Author: Paul
 *
 * Created on October 24, 2014, 10:39 PM
 */
// PIC16F1829 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

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

#define BAUD 9600
#define FOSC 4000000L
#define DIVIDER ((int)(FOSC/(16UL * BAUD) -1))  //Should be 25 for 9600/4MhZ
#define NINE_BITS 0
#define SPEED 0x4
#define RX_PIN TRISC5
#define TX_PIN TRISC4
#define _XTAL_FREQ 4000000.0    /*for 4mhz*/
//  Function Prototypes:  Actual functions after main.
void setup_comms(void);
void putch(unsigned char);
unsigned char getch(void);
unsigned char getche(void);
int Temp;
double Ftemp, Ctemp;

int j,i;

int main(int argc, char** argv) 
{
    TRISA5 = 0;
    RA5 = 1;
    OSCCON  = 0x68;         /* b6..4 = 1101 = 4MHz */
    TXCKSEL = 1;            // Note:!!!!!  OPPOSITE FOR 1825 VS 1829
    RXDTSEL = 1;            /*makes RC4 & 5 TX & RX for USART (Allows ICSP)*/
    ANSELA  = 0;
    ANSELC  = 0;            /* all ADC pins to digital I/O */
    TRISC   = 0;            /* set as output */
    LATC    = 0x00;         /* zero out */
    INTCON  =0;             // purpose of disabling the interrupts.
    setup_comms();          // set up the USART - settings defined in usart.h
//  Set up for the Temp Sensor
    TSEN = 1;               // Enable internal temp sensor
    TSRNG = 0;  //
//  Get set up for A2D
    ADFM=1;                 // Right justify temp in two register
	ADCON0  = 0x75;         // apply the new channel select (0D an3 / 75 temp)
    for (j=0; j<0x05; j++); // allows the sampeling capacitor to charge
    while (1)
    {
        ADGO  = 1;              // initiate conversion on the selected channel
        while(ADGO)continue;    // wait until conversion is finished before continuing
        Temp = ((ADRESH<<8)+(ADRESL));   /*((ADRESH<<8)+(ADRESL))  */
//        Ctemp = ((0.659 - ((3.3/2.0)(1-(Temp/1023)))/.00132)-40);
        Ctemp = 1.0-(((float)Temp)/1023.);
        Ctemp = ((0.659 -(3.3/2.0)*Ctemp)/0.00132)-40;
        printf("Temp is %f   Raw value is %d\n\r", Ctemp, Temp);
        RA5 ^= 0x01;                // Toggles the LED to help with debugging
        for (j=0; j<0x05; j++);     // Add a bit of delay here
    }
    return (EXIT_SUCCESS);
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