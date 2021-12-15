/*
*****************************************************************************
This writes text on the screen, similar to "PRINT" in BASIC.
Most systems do have a PRINT routine; this is for the ones that don't.
For example, it seems it might be broken on some Commodore PET versions:
see https://stackoverflow.com/questions/50451743/commodore-basic-4-routine

Example:
 LDA #<STRING
 LDY #>STRING
 JSR WRITE

NOTE: This uses zero-page memory, and also expects a variable "CHROUT" to
point to the right memory address, so it might require some tweaking
depending on the system you're using it for.
*****************************************************************************
*/
WRITE:
 STA $00
 STY $01		/* So $0000 now points to the string to be written */
 LDY #$00
WRITE_CONTINUE:
 LDA ($00),Y
 BEQ WRITE_DONE		/* If A == 0, then return */
 JSR CHROUT
 INY
 JMP WRITE_CONTINUE	/* else, print the character and continue the loop */
WRITE_DONE:
 RTS
