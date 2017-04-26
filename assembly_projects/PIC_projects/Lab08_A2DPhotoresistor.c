/*
 * File:   Lab08_A2DPhotoresistor.c
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

int main(int argc, char** argv) {

    int Temp, j, Pot, Photo;
    int i = 1;
    TRISA5 = 0;
    RA5 = 1;
    APFCON0 = 0x84; //This sets pins RC5 and RC4 as RX & TX on pic16f1829
    OSCCON  = 0x68; /* b6..4 = 1101 = 4MHz */
    ANSELA  = 0;
    ANSELC  = 0xC8;    /* all ADC pins to digital I/O x RC6,7*/
    TRISC   = 0xC8;      /* set as output x 6,7 */
    LATC    = 0x00;   /* zero out */
    INTCON  =0;	// purpose of disabling the interrupts.
    setup_comms();	// set up the USART - settings defined in usart.h
//  Set up for the Temp Sensor
    TSEN = 1;
    TSRNG = 0;
//  Get set up for A2D
    ADFM=1;		//Right justify

    while (1){
        ADCON0  = 0x21;	// apply the new channel select (0D an3 / 75 temp)
        //   AN8 (RC6) 0x21  and AN9 (RC7) 0x25 and AN7 (RC3) 0x1D
        for (j=0; j<0x03; j++); //allows the sampling capacitor to charge
            ADGO  = 1;	// initiate conversion on the selected channel
        while(ADGO)
            continue;
        Temp = ((ADRESH<<8)+(ADRESL));   /*((ADRESH<<8)+(ADRESL))  */
        
        //  Now switch to the Pot Chanel
        ADCON0  = 0x25;	// apply the new channel select (0D an3 / 75 temp)
        //   AN8 (RC6) 0x21  and AN9 (RC7) 0x25
         for (j=0; j<0x03; j++); //allows the sampling capacitor to charge
        ADGO  = 1;	// initiate conversion on the selected channel
        while(ADGO)
            continue;
        Pot = ((ADRESH<<8)+(ADRESL));   /*((ADRESH<<8)+(ADRESL))  */
        
        //  Now for Photo resistor
        ADCON0  = 0x1D;	// apply the new channel select
        //   AN8 (RC6) 0x21  and AN9 (RC7) 0x25 and AN7 (RC3) 0x1D
        for (j=0; j<0x03; j++); //allows the sampling capacitor to charge
        ADGO  = 1;	// initiate conversion on the selected channel
        while(ADGO)
            continue;
        Photo = ((ADRESH<<8)+(ADRESL));   /*((ADRESH<<8)+(ADRESL))  */        
        
        //(i%100 == 0)
            printf(" Temp = %4d   Pot = %4d  Photo = %4d\n\r",  Temp, Pot, Photo);
        if(Photo>Pot)
        {
            RA5 ^= 0x01;    //Toggles the LED to help with debugging
            for (j=0; j<0x05; j++);  //  Add a bit of delay here
        }
        else RA5 =0;
        i++;
    }

    return 0;
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



