;New Lab 3 Interupt Blink Program
;First include header file
#include "p16F1829.inc"
; Id processor and set radix to decimal
list p=16F1829,  R=DEC

; PIC16F1829 Configuration Bit Settings
; CONFIG1
; __config 0xC9E4
 __CONFIG _CONFIG1, _FOSC_INTOSC & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_OFF & _CLKOUTEN_OFF & _IESO_OFF & _FCMEN_OFF
; CONFIG2
; __config 0xDEFF
 __CONFIG _CONFIG2, _WRT_OFF & _PLLEN_OFF & _STVREN_ON & _BORV_LO & _LVP_OFF
;Establish Jump to start at program address 0x00
ORG 0
    goto    Start
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Interrupt Service Routine
;   Functionality:
;	- Invoked when an interrupt flag has been set. The primary register 
;	controlling when and how this routine will be invoked is the interrupt 
;	control register. In this method the flag bit that sets it off has to be
;	cleared. The timer0 enable interrupt bit is cleared too so that timer0
;	cannot keep interrupting while it is in the interrupt service routine.
;	Timer 0 is also stopped by the option register so that it cannot be running
;	while the interupt service routine is executing. Finally, the hellow world
;	LED is toggled to show that an interrupt has been called.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; put a return from interrupt at the interrupt vector location 0x04
ORG 4
;  Here is the Interrupt Service Routine (ISR)
;  First check the source and then clear the flag1`
;  Don't need to do banksel since INTCON is in the core registers
    BANKSEL INTCON
    BTFSS   INTCON,2    ; make sure timer 0 invoked interrupt service routine
    RESET		; if it is not timer 0 reset the microcontroller
    BCF     INTCON,2	; clear timer0 flag so interrupt routine can be exited
    BCF	    INTCON,5	; clear the timer0 interrupt enable bit so that timer 0
			; will not continue interrupting while it is running.
    ; Need to disable timer0
    BANKSEL OPTION_REG	; finds option register that controls timer 0 clock.
    movlw	1<<5;	; load w with a mask
    IORWF   OPTION_REG	; set timer0 clock source select bit in order to stop
			; timer0 from counting.

    ; Toggle Hello World LED
    BANKSEL LATA	; find latch A
    MOVLW   1<<5	; load the mask into W
    XORWF   LATA, f	; toggle LATCH A without affecting other latches
    
    RETFIE		; Return from interrupt
    
;Set up any needed variables using a CBLOCK at loc 0x30  (bank 0)
   CBLOCK 0x30	; Define GPR variable register locations
DlayLOW		; Used for lower 8 bits in 16 bit counter delay
DlayHIGH        ; Used for upper 8 bits in 16 bit counter delay
OUTSIDE		; Outside loop counter (how many 16 bit countdowns)
    ENDC
    
; Put label for main code
Start
;  Main code starts here
;  First set up clock
    BANKSEL OSCCON  ; osccon is where the bits are set or cleared to fix clock
    movlw   0x6A    ; bits used to set up 4 Mhz internal clock frequency
    movwf   OSCCON  ; set up for 4MHz clock int oscilator
    
    ;Setting up interrupt control register
    BCF     INTCON,2    ; CLEAR Timer 0 FLAG (which is set when timer0 times out)
    BSF     INTCON,7    ; SET the Global interrupt enable bit, which enables all interrupts
			; to be allowed
    
    BANKSEL TRISA   ; find port A tristate buffer
    clrf    TRISA   ; initialize tristate a so that PORTA pin is an output 
    BANKSEL LATA    ; find latch A
    clrf    LATA    ; Initialize Latch A as output
    
    ; Initialize button
    BANKSEL TRISB   ; find latch B
    bsf	    TRISB, 5; initialize latch B as input
    BANKSEL ANSELB  ; find analog select bit
    clrf    ANSELB  ; clear analog selct bit to set up PORTB for digital input

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Continue MAIN routine
;   Purpose:
;	Practice using interrupt service routine by interrupting LED after
;	each LED blink.
;   Functionality:    
;	2 LEDs are being controlled, one on RA4 and the Hellow World LED on RA5.
;	After the LED on RA4 is told to blink using a counter delay. The pause
;	subroutine is invoked that enables timer0 to run off the internal clock
;	and when it times out the interrupt service routine is invoked clearing
;	timer 0 flag and timer enable flag bits as well as stopping the use of 
;	timer 0 until the pause subroutine is called again.
;    
;   I/O pins:
;	RA4 - Regular blinking LED
;	RA5 - Inerrupt blinking LED
;   Special Function Registers:
;	Oscillator Control Register (OSCCON) 
;	    - control what clock you are using and frequency it is running at
;	Interrupt Control Register (INTCON)
;	    - enables interrupt servicing, what kind of interrupt you are using,
;	    and the flag bits associated with each type of interrupt
;	Option Register (OPTION_REG)
;	    - Controls timer0 functionality and prescaler
;	Timer 0 (TMR0) 
;	    - 8 bit clock register that can run off of internal or external
;	    oscillators. A flag bit is set in INTCON when it times out.
;	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

continue
    Call Blink	; Blink LED connected to RA4
    BANKSEL PORTB   ; find PORTB
    BTFSC   PORTB, 5; when button is pressed bit 5 on PORTB is cleared
    call pause	; Pause by initiating timer0 and waiting for it to timeout
    ; When timer0 times out go to interrupt and toggle LED on RA5
    GOTO continue  ; Repeat interrupt loop
    
Blink
    BANKSEL PORTA	; find PORTA
    BSF	    PORTA, 4	; set 5th bit (RA5 High) *Turn LED ON*
    CALL    Tdelay	; call delay subroutine (not using timer0)
    BCF	    PORTA, 4	; clearing 5th bit (LOW) *Turn LED OFF*
    Call    Tdelay	; call delay subroutine (not using timer0)
    return
    
 Tdelay			    ; delay subroutine
	BANKSEL	OUTSIDE	    ; find OUTSIDE variable
	movlw	2	    ; NUMBER OF SECONDS WITH DELAY=c800 IN 16f1829 @ 4MHZ Fosc
	movwf	OUTSIDE	    ; move w to f, put 2 in file register OUTSIDE

OuterLoop		    ; start outer delay loop
	movlw	LOW 0xc800  ; move lower 16 bits of literal into w (0x00)
	movwf	DlayLOW	    ; stores lower 16 bits in file register DlayLOW
	movlw	HIGH 0xc800 ; move upper 16 bits of literal into w (0xc8)
	movwf	DlayHIGH    ; stores upper 16 bits in file register DlayHIGH
	
InLoop			    ; start inner delay loop
	decf	DlayLOW, f  ; decrement lower 16 bits by 1 and store in file register DlayLOW
	btfsc	STATUS, Z   ; check if the z bit in the staus register is cleared (DlayLOW == 0)
	decfsz	DlayHIGH, f ; decrement DlayHIGH and get out of inner loop 
	GOTO	InLoop	    ; if that result is 0
	decfsz	OUTSIDE, f  ; decrement OUTSIDE and get out of outer loop
	GOTO	OuterLoop   ; if that result is 0
	return		    ; return from Time Delay routine   

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Pause subroutine
;   Purpose:
;	- Enable timer0 overflow flag. Configure timer0 with option register. 
;	Start timer0 and have it continue executing until it overflows, invoking 
;	the interrupt service routine and pausing program execution.
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
pause
    BANKSEL OPTION_REG	; finds option register that controls timer 0 clock.
   ; movlw	0x88	; This option disables prescaler incrementing timer0 each clock cycle (FOSC/4)
   ; This option uses 256 prescaler
    ; movlw   0x87	; B'10000111 or B'xx0x0111 which enables internal clock(1)
			; enables prescaler(0), and chooses 1:256 prescaler(111)
   ; This option uses 16 count prescaler refer to pg. 187 for more options
    movlw   0x83
    movwf   OPTION_REG	; set option register up with timer0 preferences
    BANKSEL INTCON	; find interrupt control register
    BSF     INTCON,5    ; SET timer0 INTERRUPT ENABLE BIT
    BANKSEL TMR0	; find timer 0
    movlw   0x01	; reset timer 0 by starting it at 1
    movwf   TMR0	; start timer
timeout
    BTFSS   INTCON, 5   ; check to see if the timer 0 overflow interrupt enable
    ; bit has been set. If so, keep looping until timer0 overflows in which the
    ; interrupt command will be invoked clearing the timer0 overflow intterupt
    ; enable bit and allowing the subrouting to return to blinking the LED.
    return    ; return from Time Delay routine
    GOTO    timeout	; keep looping until interrupt until timer0 timesout
    
END			; end program
