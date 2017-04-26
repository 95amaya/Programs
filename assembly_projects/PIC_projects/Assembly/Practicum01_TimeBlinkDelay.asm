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
 
; put a return from interrupt at the interrupt vector location 0x04
ORG 4
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
    movlw   0x02    ; bits used to set up 4 Mhz internal clock frequency b'01101010
    movwf   OSCCON  ; set up for 4MHz clock int oscilator
    
    ;Setting up interrupt control register
    BCF     INTCON,2    ; CLEAR Timer 0 FLAG (which is set when timer0 times out)
    
    BANKSEL TRISA   ; find port A tristate buffer
    clrf    TRISA   ; initialize tristate a so that PORTA pin is an output 
    BANKSEL LATA    ; find latch A
    clrf    LATA    ; Initialize Latch A as output
    
    ; Initialize button
    BANKSEL TRISB   ; find latch B
    bsf	    TRISB, 5; initialize latch B as input
    BANKSEL ANSELB  ; find analog select bit
    clrf    ANSELB  ; clear analog selct bit to set up PORTB for digital input

continue
    call TClockDelay	; Pause by initiating timer0 and waiting for it to timeout
    BANKSEL OPTION_REG	; finds option register that controls timer 0 clock.
    movlw	1<<5;	; load w with a mask
    IORWF   OPTION_REG	; set timer0 clock source select bit in order to stop
			; timer0 from counting.
    Call Blink	; Blink LED connected to RA4  
    GOTO continue  ; Blink loop
    
Blink
    BANKSEL PORTA	; find PORTA
    BSF	    PORTA, 5	; set 5th bit (RA5 High) *Turn LED ON*
    CALL    TCounterDelay	; call delay subroutine (not using timer0)
    BCF	    PORTA, 5	; clearing 5th bit (LOW) *Turn LED OFF*
    Call    TCounterDelay	; call delay subroutine (not using timer0)
  ;  Call    Tdelay
    return 
	
TClockDelay
    BANKSEL INTCON
    bcf	    INTCON, 2   ; clear timer 0 flag
    BANKSEL OPTION_REG	; finds option register that controls timer 0 clock.
   ; movlw	0x88	; This option disables prescaler incrementing timer0 each clock cycle (FOSC/4)
   ; This option uses 256 prescaler
   ; movlw   0x87	; B'10000111 or B'xx0x0111 which enables internal clock(1)
			; enables prescaler(0), and chooses 1:256 prescaler(111)
    movlw   0x85	; 0001 - 1:4 , 0010 - 1:8 , 0011 - 1:16 , 0100 - 1:32, 0101 1:64
    movwf   OPTION_REG	; set option register up with timer0 preferences
    BANKSEL TMR0	; find timer 0
    movlw   0x01	; reset timer 0 by starting it at 1
    movwf   TMR0	; start timer
timeout
    BTFSC   INTCON, 2   ; check to see if the timer 0 overflowed set means it has and exit
    return    ; return from Time Delay routine
    GOTO    timeout	; keep looping until interrupt until timer0 timesout
    
TCounterDelay			    ; delay subroutine
	BANKSEL	OUTSIDE	    ; find OUTSIDE variable
	movlw	2	    ; NUMBER OF SECONDS WITH DELAY=c800 IN 16f1829 @ 4MHZ Fosc
	movwf	OUTSIDE	    ; move w to f, put 2 in file register OUTSIDE

OuterLoop		    ; start outer delay loop
	movlw	LOW 0x0100  ; move lower 16 bits of literal into w (0x00)
	movwf	DlayLOW	    ; stores lower 16 bits in file register DlayLOW
	movlw	HIGH 0x0100 ; move upper 16 bits of literal into w (0xc8)
	movwf	DlayHIGH    ; stores upper 16 bits in file register DlayHIGH
	
InLoop			    ; start inner delay loop
	decf	DlayLOW, f  ; decrement lower 16 bits by 1 and store in file register DlayLOW
	btfsc	STATUS, Z   ; check if the z bit in the staus register is cleared (DlayLOW == 0)
	decfsz	DlayHIGH, f ; decrement DlayHIGH and get out of inner loop 
	GOTO	InLoop	    ; if that result is 0
	decfsz	OUTSIDE, f  ; decrement OUTSIDE and get out of outer loop
	GOTO	OuterLoop   ; if that result is 0
	return		    ; return from Time Delay routine
    
END			; end program
