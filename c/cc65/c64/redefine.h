#include <stdint.h>
#include <conio.h>
#include <peekpoke.h>

/**
 * Sets up the C64 to allow redefining characters
 * @remarks after calling this, ONLY the redefined
 * characters work; none of the ones you didn't
 * redefine are printable anymore.
 */
static void A64_InitRedefine() {
	// copy char set ROM into RAM ($D0-$DFFF to $30-$3FFF)
	POKE(56334U, PEEK(56334U) & 254);	// interrupt off
	POKE(1, PEEK(1) & 251);				// char set ROM on
	__asm__("LDA #0");
	__asm__("LDY #$D0");
	__asm__("STA 95");
	__asm__("STY 96");
	__asm__("LDA #0");
	__asm__("LDY #$E0");
	__asm__("STA 90");
	__asm__("STY 91");
	__asm__("LDA #0");
	__asm__("LDY #$40");
	__asm__("STA 88");
	__asm__("STY 89");
	
	// When not commented out, the program ends immediately on this line.
	//__asm__("JMP $A3BF");
	// Not sure what's normally at that address, but we don't want to do that.
	
	POKE(1, PEEK(1) | 4);					// char set ROM off
	POKE(56334U, PEEK(56334U) | 1);			// interrupt on
	POKE(53272U, PEEK(53272U) & 240 | 12);	// char set RAM at $3000
	
	// This might be related to the JMP command that breaks stuff,
	// but random garbage gets printed on the screen after all of
	// the above code has run.  I don't quite get why, since there
	// isn't anything POKE'ing to 1024 or in that neighborhood, but
	// it does, so here's a workaround:
	clrscr();
}

/**
 * Redefines a character
 * @param character The character (was uint16_t - see if changing that breaks stuff)
 * @param pixels an array of 8-bit numbers to define what the character looks like
 * (0 = off, 1 = on, in an 8-by-8 grid of pixels)
 */
static void A64_Redefine(uint8_t character, uint8_t pixels[8]) {
	POKE(12288U + (character * 8), pixels[0]);
	POKE(12289U + (character * 8), pixels[1]);
	POKE(12290U + (character * 8), pixels[2]);
	POKE(12291U + (character * 8), pixels[3]);
	POKE(12292U + (character * 8), pixels[4]);
	POKE(12293U + (character * 8), pixels[5]);
	POKE(12294U + (character * 8), pixels[6]);
	POKE(12295U + (character * 8), pixels[7]);
}
