;New Lab 2 StopBlink Program using timer0
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
    goto    Start;
; put a return from interrupt at the interrupt vector location 0x04
ORG 4
    RETFIE;
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
    
    BANKSEL OPTION_REG	; finds option register that controls timer 0 clock.
    movlw	0x87	; B'10000111 or B'xx0x0111 which enables internal clock(1),
    movwf   OPTION_REG	; enables prescaler(0), and chooses 1:256 prescaler(111)
    
    BANKSEL TRISA   ; find port A tristate buffer
    clrf    TRISA   ; initialize tristate a so that PORTA pin is an output 
    BANKSEL LATA    ; find latch A
    clrf    LATA    ; Initialize Latch A as output
    BANKSEL TRISB   ; find latch B
    bsf	    TRISB, 5; initialize latch B as input
    BANKSEL ANSELB  ; find analog select bit
    clrf    ANSELB  ; clear analog selct bit to set up PORTB for digital input

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Blink routine is broken up into two routines, which it maintaines while the
; the button is being pressed. If the button is pressed while the LED is on
; it maintains the on state if it is pressed while it's off it maintains off 
; state. NOTE: LED will switch states if button is not pressed.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
StayON
    BANKSEL PORTA   ; find PORTA
    BSF	    PORTA, 5; set 5th bit (RA5 High) *Turn LED ON*
    CALL    Tdelay  ; call delay subroutine
    BANKSEL PORTB   ; find PORTB
    BTFSS   PORTB, 5; check if 5th bit (RB5) on PORTB is set skip next line
    GOTO    StayON  ; same as checking if the button is pressed (stay in blink)

StayOFF
    BCF	    PORTA, 5; clearing 5th bit (LOW) *Turn LED OFF*
    Call    Tdelay  ; call delay subroutine
    BANKSEL PORTB   ; find PORTB
    BTFSS   PORTB, 5; when button is pressed bit 5 on PORTB is cleared
    GOTO    StayOFF ; stay in StayOFF routine if button is cleared (pressed)
    GOTO    StayON  ; keep looping between ON and OFF states

Tdelay			    ; delay subroutine
    BANKSEL OUTSIDE
    movlw   8
    movwf   OUTSIDE
	
OutsideLoop
    BANKSEL INTCON
    bcf	    INTCON, 2   ; clear timer 0 flag
    BANKSEL TMR0	; find timer 0
    movlw   0x01
    movwf   TMR0	; start timer
    CALL    InLoop	; call inner loop of going into timer and 
    BANKSEL OUTSIDE
    decfsz  OUTSIDE
    GOTO    OutsideLoop
    return
	
InLoop			    ; start inner delay loop
    BTFSC	INTCON, 2   ; check for flag (after timer0 rolls over)
    return		    ; return from Time Delay routine
    GOTO	InLoop
END			    ; end program
