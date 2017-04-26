;New Lab 4 LED PWM Program
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
DlayHIGH	; Used for upper 8 bits in 16 bit counter delay
OUTSIDE		; Outside loop counter (how many 16 bit countdowns)
DutyCycle	; PWM 8-bit Duty Cycle
    ENDC
    
PulseFrequency	EQU 0xFF	; setting PWM frequency as a constant
MAX_DUTY_CYCLE	EQU 0xD0	; setting PWM maximum duty cycle as a constant
	
    
; Put label for main code
Start
;  Main code starts here
;  First set up clock
    BANKSEL OSCCON  ; osccon is where the bits are set or cleared to fix clock
    movlw   0x6A    ; bits used to set up 4 Mhz internal clock frequency
    movwf   OSCCON  ; set up for 4MHz clock int oscilator

    ; Reconfigure pin RA5 to be able to do PWM by enabling CCP2
    BANKSEL APFCON1
    bsf	    APFCON1, 0	; Set the 0 bit in order to connect RA5 to CCP2
 
    ; Initialize Port A pins as digital inputs NOT Analog (default)
    BANKSEL ANSELA  ; find analog select register for PortA
    clrf    ANSELA  ; turn off analog inputs
    BANKSEL TRISA   ; find port A tristate buffer
    clrf    TRISA   ; disable A as output until we have PWM setup 
    BANKSEL LATA    ; find latch A
    clrf    LATA    ; Initialize Latch A as output
    
    ; Configure PWM function for RA5 PWM
    movlw   PulseFrequency
    BANKSEL PR2		    ; find period 2 register
    movwf   PR2		    ; sets PR2 to desired pulse frequency
    BANKSEL CCP2CON	    ; find capture/compare 2 control register
    movlw   0x0C	    ; bits needed to set PWM mode
    movwf   CCP2CON	    ; enables PWM mode
    BANKSEL CCPR2L	    ; find capture/compare period register 2 Lower byte
    movf    DutyCycle, w    ; put duty cycle into w register
    movwf   CCPR2L	    ; instantiate duty cycle MSbits
    BANKSEL CCPTMRS	    ; find PWM timer selection control register
    movlw   0x00	    ; going to load in bits to select timer2 for PWM
    movwf   CCPTMRS	    ; enable timer2 for PWM
    BANKSEL PIR1	    ; find peripheral interrupt request 1 register
    bcf	    PIR1, 1	    ; clear the timer 2 interrupt flag bit
    BANKSEL T2CON	    ; find timer 2 control register
    movlw   0x07	    ; loading bits needed to turn timer 2 on as well as
    movwf   T2CON	    ; set the prescaler 1:64 for timer 2
    
    ; small loop to make sure PWM does not start in the middle of 1st period
    PWMsafetyCheck
	btfss	PIR1, 1	    ; check if timer 2 interrupt flag bit is set
	bra	PWMsafetyCheck
    BANKSEL TRISA	    ; find tristate buffer for portA
    bcf	    TRISA, 5	    ; sets RA5 as output (Hello World LED)
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; main routine
;   Purpose:
;	Practice using PWM module changing the brightness of the Hello World LED
;	on the PIC board.
;   Functionality:    
;	Hello World LED brightness control with PWM signal. The PWM signal is  
;	generated with a period, a duty cycle, and a timer. The period controls 
;	the PWM frequency, while the duty cycle is controlled by CCPRxL register. 
;	The signal stays on while the timer < CCPRxH register and resets when
;	the timer == PRx register. 
;    
;   I/O pins:
;	RA5 - Hello World dimming/brightening LED
;   Special Function Registers:
;	Oscillator Control Register (OSCCON) 
;	    - control what clock you are using and frequency it is running at
;	Period Register (PRx)
;	    - controls the frequency of pulse width modulated signal
;	    and the flag bits associated with each type of interrupt
;	Capture Compare Control Register (CCPxCON)
;	    - Enable PWM mode to be used with timer 2
;	Capture Compare Timer Selectin Register (CCPTMRS)
;	    - Selects which timer will be used with PWM
;	Peripheral Interupt Register (PIRx)
;	    - Holds timer 2 interrupt flag bit
;	Timer Control Register (TxCON)
;	    - Turns timer on as well as sets timer prescaler
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
main
    Banksel DutyCycle
    movlw   MAX_DUTY_CYCLE  ; put the maximum duty cycle into w
    movwf   DutyCycle	    ; initialize dutyc cycle variable to max duty cycle
    call    DutyMinus	    ; decrement duty cycle dimming the LED
    call    DutyPlus	    ; increment duty cycle brightening LED
    GOTO    main

; Purpose is to count down duty cycle
DutyMinus
    call    Tdelay	    ; counter timer delay
    call    LoadPWM	    ; load duty cycle in CCPR2L to set new duty cycle
    BANKSEL DutyCycle	    ; find DutyCycle register
    decfsz  DutyCycle, f    ; decrement duty cycle by one and store it into itself (duty--)
    GOTO    DutyMinus	    ; repeat until DutyCycle == 0
    return
    
; Purpose is to count up duty cycle
DutyPlus  
    call    Tdelay	    ; counter timer delay
    call    LoadPWM	    ; load duty cycle again
    BANKSEL DutyCycle	
    incfsz  DutyCycle, f    ; increment DutyCycle to brighten LED
    GOTO    DutyPlus	    ; repeat until overflow
    return

; Purpose is to set PWM duty cycle
LoadPWM    
    BANKSEL DutyCycle	     
    movf    DutyCycle, w    ; move new DutyCycle into w
    BANKSEL CCPR2L  
    movwf   CCPR2L	    ; set new duty cycle in PIC 
    return		   
    
 
 Tdelay			    ; delay subroutine
	BANKSEL	OUTSIDE	    ; find OUTSIDE variable
	movlw	2	    ; NUMBER OF SECONDS WITH DELAY=c800 IN 16f1829 @ 4MHZ Fosc
	movwf	OUTSIDE	    ; move w to f, put 2 in file register OUTSIDE

OuterLoop		    ; start outer delay loop
	movlw	LOW 0x01FF  ; move lower 16 bits of literal into w (0x00) 0x05FF
	movwf	DlayLOW	    ; stores lower 16 bits in file register DlayLOW
	movlw	HIGH 0x01FF ; move upper 16 bits of literal into w (0xc8)
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
