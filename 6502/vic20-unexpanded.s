/*
VIC-20 constants
For the best darn reference ever, see https://www.chibiakumas.com/6502/vic20.php
*/

/***************************************************************************/
/* BASIC "header" (writes "10 sys 4109" into BASIC RAM)                    */
/***************************************************************************/
 org $1001
 BYTE $0b, $10, $0a, $00, $9e, $34, $31, $30, $39, $00, $00, $00


/***************************************************************************/
/* Memory map                                                              */
/***************************************************************************/

SCREEN_RAM		= $1E00
COLOR_RAM		= $9600
TEXT_COLOR		= $0286
SOUND_LOW		= $900A
SOUND_MIDDLE		= $900B
SOUND_HIGH		= $900C
SOUND_NOISE		= $900D
COLOR_AND_VOLUME	= $900E
BACKGROUND_COLORS	= $900F
CHARSET			= $9005


/***************************************************************************/
/* Kernal routines                                                         */
/***************************************************************************/

CHROUT = $FFD2
PRINT = $CB1E


/***************************************************************************/
/* PETSCII character set                                                   */
/***************************************************************************/

PETSCII_ASTERISK		= $2A
PETSCII_BALL			= $51
PETSCII_HOLLOW_BALL		= $57


/***************************************************************************/
/* Other character codes (printing them does some unexpected stuff)        */
/***************************************************************************/

CHAR_LOWERCASE_CHARSET	= $0E
CHAR_CLEAR_SCREEN	= $93


/***************************************************************************/
/* Text colors                                                             */
/***************************************************************************/

COLOR_BLACK	= $00
COLOR_WHITE	= $01
COLOR_RED	= $02
COLOR_CYAN	= $03
COLOR_PURPLE	= $04
COLOR_GREEN	= $05
COLOR_BLUE	= $06
COLOR_YELLOW	= $07


/***************************************************************************/
/* Background/border colors                                                */
/***************************************************************************/

BLACK_BG_BLACK_BORDER	= $08
BLACK_BG_WHITE_BORDER	= $09
BLACK_BG_RED_BORDER	= $0A
BLACK_BG_CYAN_BORDER	= $0B
BLACK_BG_PURPLE_BORDER	= $0C
BLACK_BG_GREEN_BORDER	= $0D
BLACK_BG_BLUE_BORDER	= $0E
BLACK_BG_YELLOW_BORDER	= $0F
WHITE_BG_BLACK_BORDER	= $18
WHITE_BG_WHITE_BORDER	= $19
WHITE_BG_RED_BORDER	= $1A
WHITE_BG_CYAN_BORDER	= $1B
WHITE_BG_PURPLE_BORDER	= $1C
WHITE_BG_GREEN_BORDER	= $1D
WHITE_BG_BLUE_BORDER	= $1E
WHITE_BG_YELLOW_BORDER	= $1F
RED_BG_BLACK_BORDER	= $28
RED_BG_WHITE_BORDER	= $29
RED_BG_RED_BORDER	= $2A
RED_BG_CYAN_BORDER	= $2B
RED_BG_PURPLE_BORDER	= $2C
RED_BG_GREEN_BORDER	= $2D
RED_BG_BLUE_BORDER	= $2E
RED_BG_YELLOW_BORDER	= $2F
CYAN_BG_BLACK_BORDER	= $38
CYAN_BG_WHITE_BORDER	= $39
CYAN_BG_RED_BORDER	= $3A
CYAN_BG_CYAN_BORDER	= $3B
CYAN_BG_PURPLE_BORDER	= $3C
CYAN_BG_GREEN_BORDER	= $3D
CYAN_BG_BLUE_BORDER	= $3E
CYAN_BG_YELLOW_BORDER	= $3F
PURPLE_BG_BLACK_BORDER	= $48
PURPLE_BG_WHITE_BORDER	= $49
PURPLE_BG_RED_BORDER	= $4A
PURPLE_BG_CYAN_BORDER	= $4B
PURPLE_BG_PURPLE_BORDER	= $4C
PURPLE_BG_GREEN_BORDER	= $4D
PURPLE_BG_BLUE_BORDER	= $4E
PURPLE_BG_YELLOW_BORDER	= $4F
GREEN_BG_BLACK_BORDER	= $58
GREEN_BG_WHITE_BORDER	= $59
GREEN_BG_RED_BORDER	= $5A
GREEN_BG_CYAN_BORDER	= $5B
GREEN_BG_PURPLE_BORDER	= $5C
GREEN_BG_GREEN_BORDER	= $5D
GREEN_BG_BLUE_BORDER	= $5E
GREEN_BG_YELLOW_BORDER	= $5F
BLUE_BG_BLACK_BORDER	= $68
BLUE_BG_WHITE_BORDER	= $69
BLUE_BG_RED_BORDER	= $6A
BLUE_BG_CYAN_BORDER	= $6B
BLUE_BG_PURPLE_BORDER	= $6C
BLUE_BG_GREEN_BORDER	= $6D
BLUE_BG_BLUE_BORDER	= $6E
BLUE_BG_YELLOW_BORDER	= $6F
YELLOW_BG_BLACK_BORDER	= $78
YELLOW_BG_WHITE_BORDER	= $79
YELLOW_BG_RED_BORDER	= $7A
YELLOW_BG_CYAN_BORDER	= $7B
YELLOW_BG_PURPLE_BORDER	= $7C
YELLOW_BG_GREEN_BORDER	= $7D
YELLOW_BG_BLUE_BORDER	= $7E
YELLOW_BG_YELLOW_BORDER	= $7F
ORANGE_BG_BLACK_BORDER	= $88
ORANGE_BG_WHITE_BORDER	= $89
ORANGE_BG_RED_BORDER	= $8A
ORANGE_BG_CYAN_BORDER	= $8B
ORANGE_BG_PURPLE_BORDER	= $8C
ORANGE_BG_GREEN_BORDER	= $8D
ORANGE_BG_BLUE_BORDER	= $8E
ORANGE_BG_YELLOW_BORDER	= $8F
LIGHT_ORANGE_BG_BLACK_BORDER	= $98
LIGHT_ORANGE_BG_WHITE_BORDER	= $99
LIGHT_ORANGE_BG_RED_BORDER	= $9A
LIGHT_ORANGE_BG_CYAN_BORDER	= $9B
LIGHT_ORANGE_BG_PURPLE_BORDER	= $9C
LIGHT_ORANGE_BG_GREEN_BORDER	= $9D
LIGHT_ORANGE_BG_BLUE_BORDER	= $9E
LIGHT_ORANGE_BG_YELLOW_BORDER	= $9F
PINK_BG_BLACK_BORDER	= $A8
PINK_BG_WHITE_BORDER	= $A9
PINK_BG_RED_BORDER	= $AA
PINK_BG_CYAN_BORDER	= $AB
PINK_BG_PURPLE_BORDER	= $AC
PINK_BG_GREEN_BORDER	= $AD
PINK_BG_BLUE_BORDER	= $AE
PINK_BG_YELLOW_BORDER	= $AF
LIGHT_CYAN_BG_BLACK_BORDER	= $B8
LIGHT_CYAN_BG_WHITE_BORDER	= $B9
LIGHT_CYAN_BG_RED_BORDER	= $BA
LIGHT_CYAN_BG_CYAN_BORDER	= $BB
LIGHT_CYAN_BG_PURPLE_BORDER	= $BC
LIGHT_CYAN_BG_GREEN_BORDER	= $BD
LIGHT_CYAN_BG_BLUE_BORDER	= $BE
LIGHT_CYAN_BG_YELLOW_BORDER	= $BF
LIGHT_PURPLE_BG_BLACK_BORDER	= $C8
LIGHT_PURPLE_BG_WHITE_BORDER	= $C9
LIGHT_PURPLE_BG_RED_BORDER	= $CA
LIGHT_PURPLE_BG_CYAN_BORDER	= $CB
LIGHT_PURPLE_BG_PURPLE_BORDER	= $CC
LIGHT_PURPLE_BG_GREEN_BORDER	= $CD
LIGHT_PURPLE_BG_BLUE_BORDER	= $CE
LIGHT_PURPLE_BG_YELLOW_BORDER	= $CF
LIGHT_GREEN_BG_BLACK_BORDER	= $D8
LIGHT_GREEN_BG_WHITE_BORDER	= $D9
LIGHT_GREEN_BG_RED_BORDER	= $DA
LIGHT_GREEN_BG_CYAN_BORDER	= $DB
LIGHT_GREEN_BG_PURPLE_BORDER	= $DC
LIGHT_GREEN_BG_GREEN_BORDER	= $DD
LIGHT_GREEN_BG_BLUE_BORDER	= $DE
LIGHT_GREEN_BG_YELLOW_BORDER	= $DF
LIGHT_BLUE_BG_BLACK_BORDER	= $E8
LIGHT_BLUE_BG_WHITE_BORDER	= $E9
LIGHT_BLUE_BG_RED_BORDER	= $EA
LIGHT_BLUE_BG_CYAN_BORDER	= $EB
LIGHT_BLUE_BG_PURPLE_BORDER	= $EC
LIGHT_BLUE_BG_GREEN_BORDER	= $ED
LIGHT_BLUE_BG_BLUE_BORDER	= $EE
LIGHT_BLUE_BG_YELLOW_BORDER	= $EF
LIGHT_YELLOW_BG_BLACK_BORDER	= $F8
LIGHT_YELLOW_BG_WHITE_BORDER	= $F9
LIGHT_YELLOW_BG_RED_BORDER	= $FA
LIGHT_YELLOW_BG_CYAN_BORDER	= $FB
LIGHT_YELLOW_BG_PURPLE_BORDER	= $FC
LIGHT_YELLOW_BG_GREEN_BORDER	= $FD
LIGHT_YELLOW_BG_BLUE_BORDER	= $FE
LIGHT_YELLOW_BG_YELLOW_BORDER	= $FF


/***************************************************************************/
/* Musical notes                                                           */
/***************************************************************************/

NOTE_C1				= 135	/** C note, octave 1 */
NOTE_CS1			= 143	/** C# note, octave 1 */
NOTE_D1				= 147	/** D note, octave 1 */
NOTE_DS1			= 151	/** D# note, octave 1 */
NOTE_E1				= 159	/** E note, octave 1 */
NOTE_F1				= 163	/** F note, octave 1 */
NOTE_FS1			= 167	/** F# note, octave 1 */
NOTE_G1				= 175	/** G note, octave 1 */
NOTE_GS1			= 179	/** G# note, octave 1 */
NOTE_A1				= 183	/** A note, octave 1 */
NOTE_AS1			= 187	/** A# note, octave 1 */
NOTE_B1				= 191	/** B note, octave 1 */
NOTE_C2				= 195	/** C note, octave 2 */
NOTE_CS2			= 199	/** C# note, octave 2 */
NOTE_D2				= 201	/** D note, octave 2 */
NOTE_DS2			= 203	/** D# note, octave 2 */
NOTE_E2				= 207	/** E note, octave 2 */
NOTE_F2				= 209	/** F note, octave 2 */
NOTE_FS2			= 212	/** F# note, octave 2 */
NOTE_G2				= 215	/** G note, octave 2 */
NOTE_GS2			= 217	/** G# note, octave 2 */
NOTE_A2				= 219	/** A note, octave 2 */
NOTE_AS2			= 221	/** A# note, octave 2 */
NOTE_B2				= 223	/** B note, octave 2 */
NOTE_C3				= 225	/** C note, octave 3 */
NOTE_CS3			= 227	/** C# note, octave 3 */
NOTE_D3				= 228	/** D note, octave 3 */
NOTE_DS3			= 229	/** D# note, octave 3 */
NOTE_E3				= 231	/** E note, octave 3 */
NOTE_F3				= 232	/** F note, octave 3 */
NOTE_FS3			= 233	/** F# note, octave 3 */
NOTE_G3				= 235	/** G note, octave 3 */
NOTE_GS3			= 236	/** G# note, octave 3 */
NOTE_A3				= 237	/** A note, octave 3 */
NOTE_AS3			= 238	/** A# note, octave 3 */
NOTE_B3				= 239	/** B note, octave 3 */
NOTE_C4				= 240	/** C note, octave 4 */
NOTE_CS4			= 241	/** C# note, octave 4 */
