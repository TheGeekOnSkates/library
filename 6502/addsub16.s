/*
16-bit addition and subtraction simple example by FMan/Tropyx
Modded to compile with DASM, with some additional comments
*/


/* Zero-page memory addresses to be used as variables */

num1lo = $62
num1hi = $63
num2lo = $64
num2hi = $65
resultlo = $66
resulthi = $67

/* adds numbers 1 and 2, writes result to separate location */
ADD:
	CLC		/* clear carry */
	LDA num1lo
	ADC num2lo
	STA resultlo	/* store sum of LSBs */
	LDA num1hi
	ADC num2hi	/* add the MSBs using carry from */
	STA resulthi	/* the previous calculation */
	RTS

/* subtracts number 2 from number 1 and writes result out */
SUB:
	SEC		/* set carry for borrow purpose */
	LDA num1lo
	SBC num2lo	/* perform subtraction on the LSBs */
	STA resultlo
	LDA num1hi	/* do the same for the MSBs, with carry */
	SBC num2hi	/* set according to the previous result */
	STA resulthi
	RTS


/* TESTS / EXAMPLES OF HOW TO USE

	; Store $0FFE in num1
	LDA #$0F
	STA num1hi
	LDA #$FE
	STA num1lo
	
	; Store $0002 in num2
	LDA #$00
	STA num2hi
	LDA #$02
	STA num2lo

	; Test ADD below (expected result: $1000)
	; This worked.  resultlo was $00, resulthi was $10
	JSR ADD

; ------------------------------------------

	; Store $A000 in num1
	LDA #$A0
	STA num1hi
	LDA #$00
	STA num1lo
	
	; Store $0001 in num2
	STA num2hi
	LDA #$01
	STA num2lo
	
	; Test "sub" below (expected result: $9FFF)
	; This test worked.  resultlo was $FF and resulthi was $9F
	JSR SUB
*/
