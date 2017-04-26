;Step 2 of project being able to store changed state information and relay it back
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
   CBLOCK 0x30  ; Define GPR variable register locations
DlayLOW		; Used for lower 8 bits in 16 bit counter delay
DlayHIGH        ; Used for upper 8 bits in 16 bit counter delay
OUTSIDE		; Outside loop counter (how many 16 bit countdowns)
PressCount	; used to relay input to output counting how many blinks
DOT_SLASH	; 8 bit register can hold up to 4 dots and 4 slashes
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
    bsf	    TRISB, 5; initialize PortB as input from pin RB5
    bsf	    TRISB, 6; initialize PortB as input from pin RB6
    BANKSEL ANSELB  ; find analog select bit
    clrf    ANSELB  ; clear analog selct bit to set up PORTB for digital input
    ; initializing variables
    BANKSEL PressCount  
    clrf    PressCount

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ReadIn routine reads in button presses until a max is reached or portA is pressed. 
; Once it reads in the number of button presses it goes to SendOut which 
; communicates in blinks the number of button presses there were
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  
; Make methods setDot and setSlash
    
ReadIn		    ; Reads in based on how many times button is pressed
    CALL    InputTdelay	    ; delay between input calls
    CALL    CheckPress	    ; call input to check if button is pressed
    BANKSEL PressCount	    ; find pressCount counter
    incf    PressCount, f   ; increment counter
    BTFSS   
    BTFSS   PressCount, 2   ; if second bit is set exit routine (count to 4)
    GOTO    ReadIn	    ; stay in Reading routine as long as count < 4 
    CALL    OutTdelay	    ; delay transition into sending data out
    
SendOut
    BANKSEL PressCount	    ; find counter variable
    call    BlinkOut	    ; tell it to send out a blink
    decfsz  PressCount, f   ; decrement counter
    GOTO    SendOut	    ; keep going until counter reaches 0
    
DONE		    ; finished program should stay off
    BANKSEL PORTA
    BSF	    PORTA, 2
    CALL    OutTdelay
    BCF	    PORTA, 2
    CALL    OutTdelay
    CALL    CheckPress2
    GOTO    DONE 

CheckPress2
    BANKSEL PORTB
    BTFSC   PORTB, 6
    GOTO    CheckPress2
    return

;;;;;;;;;;;;;;;;;;;;SUBROUTINE SECTION;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; ReadIn subroutines    
CheckPress
    BANKSEL PORTB
    BTFSC   PORTB, 5	; When button is pressed it clears PORTB
    GOTO    CheckPress	; If not pressed keep checking button
    BTFSC   PORTB, 6	; check if it is time to set value
    return

InputTdelay		; start Time delay loop
    movlw   LOW 0x88FF  ; move lower 16 bits of literal into w (0xFF)
    movwf   DlayLOW	; stores lower 16 bits in file register DlayLOW
    movlw   HIGH 0x88FF ; move upper 16 bits of literal into w (0x88)
    movwf   DlayHIGH    ; stores upper 16 bits in file register DlayHIGH
    GOTO    Decrement
 
; SendOut subroutines
BlinkOut
    BANKSEL PORTA	; find PORTA
    BSF	    PORTA, 5	; Set 5th bit (High) *connected to LED*
    CALL    OutTdelay	; call Time Delay routine
    BCF	    PORTA, 5	; Clearing 5th bit (LOW)
    Call    OutTdelay	; call Time Delay routine
    return
    
; Blinkout Subroutine
    OutTdelay
	movlw   LOW 0xFFFF  ; move lower 16 bits of literal into w (0xFF)
	movwf   DlayLOW	    ; stores lower 16 bits in file register DlayLOW
	movlw   HIGH 0xFFFF ; move upper 16 bits of literal into w (0x88)
	movwf   DlayHIGH    ; stores upper 16 bits in file register DlayHIGH
	GOTO    Decrement
    
; Part of In/Out Tdelay
	Decrement		; start decrementing loop
	    decf    DlayLOW, f	; decrement lower 16 bits by 1 and store in file register DlayLOW
	    btfsc   STATUS, Z	; check if the z bit in the staus register is cleared (DlayLOW == 0)
	    decfsz  DlayHIGH, f	; decrement DlayHIGH and get out of decrement loop
	    GOTO    Decrement	; if that result is 0 (DlayHIGH == 0)
	    return		; return from Tdealy subroutine
   
END			; end program
