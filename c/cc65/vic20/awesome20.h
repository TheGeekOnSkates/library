// Library:		Awesome20
// Description:		Macros and other stuff for VIC-20 programming
// Version:		1.0.1
// Last updated:	2021-01-03
// --------------------------------------------------------------------------------

#ifndef _AWESOME20_H
#define _AWESOME20_H

// --------------------------------------------------------------------------------
// DEPENDENCIES
// --------------------------------------------------------------------------------

#include <stdint.h>
#include <peekpoke.h>
#include <vic20.h>

// --------------------------------------------------------------------------------
// GRAPHICS
// --------------------------------------------------------------------------------

/**
 * Shows the blinking cursor
 */
#define A20_ShowCursor() POKE(204, 0)

/**
 * Hides the blinking cursor
 */
#define A20_HideCursor() POKE(204, 1)

/**
 * Changes the character set
 * @param n One of the A20_CHARSET_* constants
 */
#define A20_ChangeCharacterSet(n) POKE(0x9005, n)

/**
 * Sets the background and border colors
 * @param bg The background color
 * @param border The border color
 */
#define A20_SetBackgroundColors(bg, border) POKE(36879U, bg * 16 + border + 8)

#define A20_COLOR_BLACK 0               /** Black (foreground or background) */
#define A20_COLOR_WHITE 1               /** White (foreground or background) */
#define A20_COLOR_RED 2                 /** Red (foreground or background) */
#define A20_COLOR_CYAN 3                /** Cyan (foreground or background) */
#define A20_COLOR_PURPLE 4              /** Purple (foreground or background) */
#define A20_COLOR_GREEN 5               /** Green (foreground or background) */
#define A20_COLOR_BLUE 6                /** Blue (foreground or background) */
#define A20_COLOR_YELLOW 7              /** Yellow (foreground or background) */
#define A20_COLOR_ORANGE 8              /** Orange (background only) */
#define A20_COLOR_LIGHT_ORANGE 9        /** Light orange (background only) */
#define A20_COLOR_PINK 10               /** Pink (background only) */
#define A20_COLOR_LIGHT_CYAN 11         /** Light cyan (background only) */
#define A20_COLOR_LIGHT_PURPLE 12       /** Light purple (background only) */
#define A20_COLOR_LIGHT_GREEN 13        /** Light green (background only) */
#define A20_COLOR_LIGHT_BLUE 14         /** Light blue (background only) */
#define A20_COLOR_LIGHT_YELLOW 15       /** Light yellow (background only) */

#define A20_MULTICOLOR_BLACK 8          /** Black, multicolor mode on */
#define A20_MULTICOLOR_WHITE 9          /** White, multicolor mode on */
#define A20_MULTICOLOR_RED 10           /** Red, multicolor mode on */
#define A20_MULTICOLOR_CYAN 11          /** Cyan, multicolor mode on */
#define A20_MULTICOLOR_PURPLE 12        /** Purple, multicolor mode on */
#define A20_MULTICOLOR_GREEN 13         /** Green, multicolor mode on */
#define A20_MULTICOLOR_BLUE 14          /** Blue, multicolor mode on */
#define A20_MULTICOLOR_YELLOW 15        /** Yellow, multicolor mode on */

#define A20_CHARSET_UPPER 240   /** Uppercase character set with more graphics but no lowercase */
#define A20_CHARSET_LOWER 242   /** Lowercase and uppercase with fewer graphics characters  */

#define A20_SCREEN_RAM_UNEXPANDED 7680U      /** Screen memory for an unexpanded VIC-20 starts here */
#define A20_COLOR_RAM_UNEXPANDED 38400U      /** Color memory for an unexpanded VIC-20 starts here */
#define A20_SCREEN_RAM_8K 0x1000             /** Scereen memory for a VIC-20 with 8 KB (or more) of RAM starts here */
#define A20_COLOR_RAM_8K 0x9400              /** Color memory for a VIC-20 with 8 KB (or more) of RAM starts here */


// --------------------------------------------------------------------------------
// SOUND
// --------------------------------------------------------------------------------

/**
 * Sets the VIC-20's auxilary color and sound volume
 * @param color One of the A20_COLOR* constants (or 0 if not using)
 * @param volume The volume (a number from 1 to 15)
 * @remarks This is a weird quirk in the VIC-20's design, obviously an effort to
 * save memory (in other words, not really a design choice on my end lol).
 * @todo Work on a way to separate these two (some tricky bitwise
 * math involved but it's doable if I ever need/want to)
 */
#define A20_SetColor2AndVolume(color, volume) POKE(36878U, color * 15  +  volume)

/**
 * Sets the "alto" voice
 * @param n One of the A20_NOTE_ constants
 * @todo Figure which is higher (alto, soprano, tenor)
 */
#define A20_SetVoice1(n) POKE(36874U, n)

/**
 * Sets the "tenor" voice
 * @param n One of the A20_NOTE_ constants
 */
#define A20_SetVoice2(n) POKE(36875U, n)

/**
 * Sets the "soprano" voice
 * @param n One of the A20_NOTE_ constants
 */
#define A20_SetVoice3(n) POKE(36876U, n)

/**
 * Sets the noise voice
 * @param n One of the A20_NOTE_ constants
 */
#define A20_SetNoise(n) POKE(36877U, n)

#define A20_NOTE_C1 135         /** C note, octave 1 */
#define A20_NOTE_CS1 143        /** C# note, octave 1 */
#define A20_NOTE_D1 147         /** D note, octave 1 */
#define A20_NOTE_DS1 151        /** D# note, octave 1 */
#define A20_NOTE_E1 159         /** E note, octave 1 */
#define A20_NOTE_F1 163         /** F note, octave 1 */
#define A20_NOTE_FS1 167        /** F# note, octave 1 */
#define A20_NOTE_G1 175         /** G note, octave 1 */
#define A20_NOTE_GS1 179        /** G# note, octave 1 */
#define A20_NOTE_A1 183         /** A note, octave 1 */
#define A20_NOTE_AS1 187        /** A# note, octave 1 */
#define A20_NOTE_B1 191         /** B note, octave 1 */
#define A20_NOTE_C2 195         /** C note, octave 2 */
#define A20_NOTE_CS2 199        /** C# note, octave 2 */
#define A20_NOTE_D2 201         /** D note, octave 2 */
#define A20_NOTE_DS2 203        /** D# note, octave 2 */
#define A20_NOTE_E2 207         /** E note, octave 2 */
#define A20_NOTE_F2 209         /** F note, octave 2 */
#define A20_NOTE_FS2 212        /** F# note, octave 2 */
#define A20_NOTE_G2 215         /** G note, octave 2 */
#define A20_NOTE_GS2 217        /** G# note, octave 2 */
#define A20_NOTE_A2 219         /** A note, octave 2 */
#define A20_NOTE_AS2 221        /** A# note, octave 2 */
#define A20_NOTE_B2 223         /** B note, octave 2 */
#define A20_NOTE_C3 225         /** C note, octave 3 */
#define A20_NOTE_CS3 227        /** C# note, octave 3 */
#define A20_NOTE_D3 228         /** D note, octave 3 */
#define A20_NOTE_DS3 229        /** D# note, octave 3 */
#define A20_NOTE_E3 231         /** E note, octave 3 */
#define A20_NOTE_F3 232         /** F note, octave 3 */
#define A20_NOTE_FS3 233        /** F# note, octave 3 */
#define A20_NOTE_G3 235         /** G note, octave 3 */
#define A20_NOTE_GS3 236        /** G# note, octave 3 */
#define A20_NOTE_A3 237         /** A note, octave 3 */
#define A20_NOTE_AS3 238        /** A# note, octave 3 */
#define A20_NOTE_B3 239         /** B note, octave 3 */
#define A20_NOTE_C4 240         /** C note, octave 4 */
#define A20_NOTE_CS4 241        /** C# note, octave 4 */

// --------------------------------------------------------------------------------
// KEYBOARD INPUT
// --------------------------------------------------------------------------------

/**
 * Gets the currently pressed key
 * @todo
 * 1. Test MOD_CTRL (might not actually be a CTRL key on the VIC-20)
 * Figure out what KEY_UNKNOWN is
 * Check if there are any other keys not listed here (when I get my TheVIC20)
 */
#define A20_ReadKey() PEEK(197)

// These values are returned by A20_ReadKey;
// Note that these values are completely unrelated to ASCII codes,
// OR PETSCII codes (either of the 2 character sets).

#define A20_KEY_LEFT 8
#define A20_KEY_1 0
#define A20_KEY_2 56
#define A20_KEY_3 1
#define A20_KEY_4 57
#define A20_KEY_5 2
#define A20_KEY_6 58
#define A20_KEY_7 3
#define A20_KEY_8 59
#define A20_KEY_9 4
#define A20_KEY_0 60
#define A20_KEY_PLUS 5
#define A20_KEY_MINUS 61
#define A20_KEY_UNKNOWN 6       /** Run/Stop or restore maybe? */
#define A20_KEY_HOME 62
#define A20_KEY_DELETE 7
#define A20_KEY_ASTERISK 14
#define A20_KEY_UP 54
#define A20_KEY_COLON 45
#define A20_KEY_SEMICOLON 22
#define A20_KEY_DOT 37
#define A20_KEY_SLASH 30
#define A20_KEY_VCURSOR 31
#define A20_KEY_HCURSOR 23
#define A20_KEY_F1 39
#define A20_KEY_F3 47
#define A20_KEY_F5 55
#define A20_KEY_F7 63
#define A20_KEY_A 17
#define A20_KEY_B 35
#define A20_KEY_C 34
#define A20_KEY_D 18
#define A20_KEY_E 49
#define A20_KEY_F 42
#define A20_KEY_G 19
#define A20_KEY_H 43
#define A20_KEY_I 12
#define A20_KEY_J 20
#define A20_KEY_K 44
#define A20_KEY_L 21
#define A20_KEY_M 36
#define A20_KEY_N 28
#define A20_KEY_O 52
#define A20_KEY_P 13
#define A20_KEY_Q 48
#define A20_KEY_R 10
#define A20_KEY_S 41
#define A20_KEY_T 50
#define A20_KEY_U 51
#define A20_KEY_V 27
#define A20_KEY_W 9
#define A20_KEY_X 26
#define A20_KEY_Y 11
#define A20_KEY_Z 33
#define A20_KEY_SPACE 32
#define A20_KEY_NONE 64
#define A20_KEY_RETURN 15

// Borrowing some lingo from Windows,
// Shift, CTRL and Commodore key are "modifier" keys
// So, PEEK here to get which of these are pressed
#define A20_ReadModifierKeys() PEEK(653)

// And these are the possible return values of A20_ReadModifierKeys (bitwise OR'ed together)
#define A20_MOD_SHIFT 1
#define A20_MOD_COMMODORE 2
#define A20_MOD_CTRL 4

// --------------------------------------------------------------------------------
// JOYSTICK INPUT
// --------------------------------------------------------------------------------

/***
 * Reads the VIC-20's joystick (it only had one)
 * @see http://sleepingelephant.com/denial/wiki/index.php?title=Joystick
 */
static uint8_t A20_ReadJoystick() {
    uint8_t s, t, result;
    s = PEEK(37151U);
    POKE(37154U, 127);
    t = PEEK(37152U);
    POKE(37154U, 255);
    result = 0;
    if ((t & 128) == 0) result |= 1;   // right
    if ((s & 32) == 0) result |= 2;    // fire
    if ((s & 16) == 0) result |= 4;    // left
    if ((s & 8) == 0) result |= 8;     // down
    if ((s & 4) == 0) result |= 16;    // up
    return result;
}

/**
 * Checks if the joystick's axis is facing left
 * @param n A number returned by A20_ReadJoystick
 * @returns True if it is, false if it isn't
 * @remarks Will also return true for up-left and down-left
 */
#define A20_JoystickLeft(n) ((n) & 4)

/**
 * Checks if the joystick's axis is facing right
 * @param n A number returned by A20_ReadJoystick
 * @returns True if it is, false if it isn't
 * @remarks Will also return true for up-right and down-right
 */
#define A20_JoystickRight(n) ((n) & 1)

/**
 * Checks if the joystick's axis is facing up
 * @param n A number returned by A20_ReadJoystick
 * @returns True if it is, false if it isn't
 * @remarks Will also return true for up-right and up-left
 */
#define A20_JoystickUp(n) ((n) & 16)

/**
 * Checks if the joystick's axis is facing down
 * @param n A number returned by A20_ReadJoystick
 * @returns True if it is, false if it isn't
 * @remarks Will also return true for down-right and down-left
 */
#define A20_JoystickDown(n) ((n) & 8)

/**
 * Checks if the joystick's fire button is pressed
 * @param n A number returned by A20_ReadJoystick
 * @returns True if it is, false if it isn't
 */
#define A20_JoystickFire(n) ((n) & 2)

#endif

