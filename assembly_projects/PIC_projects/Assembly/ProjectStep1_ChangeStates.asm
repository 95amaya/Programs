;Step 1 of project being able to change port state based on button input
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
    BANKSEL OSCCON  ; oscon is where the bits are set or cleared to fix clock
    movlw   0x6A    ; bits used to set up 4 Mhz internal clock frequency
    movwf   OSCCON  ; set up for 4MHz clock int oscilator
    BANKSEL TRISA   ; find port A tristate buffer
    clrf    TRISA   ; initialize tristate a so that PORTA pin is an output 
    BANKSEL LATA    ; find latch A
    clrf    LATA    ; Initialize Latch A as output
    BANKSEL LATB    ; find latch B
    bsf	    TRISB, 5; initialize latch B as input
    BANKSEL ANSELB  ; find analog select bit
    clrf    ANSELB  ; clear analog selct bit to set up PORTB for digital input

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Button routine maintains LED state by checking if PORTB button is pressed
; through each pass in the routine. If the button on PORTB is pressed, then it
; clears the input and returns from subroutine to change the state of the LED.
; NOTE: If button is held down LED will continue blinking because it will
; enter and exit subroutine so fast that it will keep changing states.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
Button
    BANKSEL PORTA   ; find PORTA
    BCF	    PORTA, 5; clearing 5th bit (LOW) *Turn LED OFF*
    CALL    Tdelay  ; call time dealy subroutine
    CALL    CheckPress	; call check press subroutine to check if button is pressed
    BANKSEL PORTA   ; find PORTA
    BSF	    PORTA, 5; set 5th bit (RA5 High) *Turn LED ON*
    CALL    Tdelay  ; call time dealy subroutine
    CALL    CheckPress	; call check press subroutine to check if button is pressed
    GOTO    Button  ; stay in button routine if to keep alternating LED states

CheckPress
    BANKSEL PORTB
    BTFSC   PORTB, 5	; When button is pressed it clears PORTB
    GOTO    CheckPress	; If not pressed keep checking button
    return

Tdelay			; start Time delay loop
    movlw   LOW 0xFFFF  ; move lower 16 bits of literal into w (0xFF)
    movwf   DlayLOW	; stores lower 16 bits in file register DlayLOW
    movlw   HIGH 0xFFFF ; move upper 16 bits of literal into w (0xFF)
    movwf   DlayHIGH    ; stores upper 16 bits in file register DlayHIGH

Decrement		; start decrementing loop
    decf    DlayLOW, f	; decrement lower 16 bits by 1 and store in file register DlayLOW
    btfsc   STATUS, Z	; check if the z bit in the staus register is cleared (DlayLOW == 0)
    decfsz  DlayHIGH, f	; decrement DlayHIGH and get out of decrement loop
    GOTO    Decrement	; if that result is 0 (DlayHIGH == 0)
    return		; return from Tdealy subroutine
   
END			; end program
