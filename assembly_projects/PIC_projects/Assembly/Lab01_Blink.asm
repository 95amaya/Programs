;New Lab 1 blink Program
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
;put a return from interrupt at the interrupt vector location 0x04
ORG 4
    RETFIE;
;Set up any needed variables using a CBLOCK at loc 0x30  (bank 0)
   CBLOCK 0x30 ; Define GPR variable register locations
DlayLOW		; Used for lower 8 bits in 16 bit counter delay
DlayHIGH        ; Used for upper 8 bits in 16 bit counter delay
OUTSIDE		; Outside loop counter (how many 16 bit countdowns)
    ENDC
    
;Put label for main code
Start
;  Main code starts here
;  First set up clock
    BANKSEL OSCCON  ; osccon is where the bits are set or cleared to fix clock
    movlw   0x6A    ; bits used to set up 4 Mhz internal clock frequency
    movwf   OSCCON  ; set up for 4MHz clock int oscilator
    BANKSEL TRISA   ; find port A tristate buffer
    clrf    TRISA   ; initialize tristate a so that PORTA pin is an output 
    BANKSEL LATA    ; find latch A
    clrf    LATA    ; Initialize Latch A as output
    
Blink
    BANKSEL PORTA   ; find PORTA
    BSF	    PORTA, 5; Set 5th bit (High) *connected to LED*
    CALL    Tdelay  ; call Time Delay routine
    BCF	    PORTA, 5; Clearing 5th bit (LOW)
    Call    Tdelay  ; call Time Delay routine
    GOTO    Blink   ; keep blinking

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
END			    ; end program