/* Commodore PET 6502 Assembly constants */

/*****************************************************************************/
/* KERNAL ROUTINES                                                            */
/*****************************************************************************/

/* Docs: https://www.commodore.ca/manuals/pdfs/commodore_pet_vic-20_c64_kernal_subroutines.pdf */
BASIC1_PRINT = $CA27	/* BASIC v1 "PRINT" routine */
BASIC2_PRINT = $CA1C	/* BASIC v2 "PRINT" routine */
BASIC4_PRINT = $BB1D	/* BASIC v4 "PRINT" broken (at least in VICE).  See https://stackoverflow.com/questions/50451743/commodore-basic-4-routine */
MOVE_CURSOR = $BB3A
CHROUT = $FFD2			/* Print a character */
CHRIN = $FFE4			/* Read a character */
SCNKEY = $FF9F			/* Scan keyboard */
STOP = $FFE1
PLOT = $FFF0
SYNTAX_ERROR = $BF00		/* Print BASIC "syntax error" message and exit */


/*****************************************************************************/
/* MEMORY MAP                                                                */
/*****************************************************************************/

SCREEN_RAM_START =	32768
KEYBOARD =		151
WHICH_CHARSET =		59468



/*****************************************************************************/
/* CHR$ CODES                                                                */
/*****************************************************************************/

CHAR_UPPERCASE =		$0B /* Switch to uppercase character set */
CHAR_RETURN =			$0D
CHAR_LOWERCASE =		$0E /* Switch to lowercase character set */
CHAR_CURSOR_DOWN =		$11
CHAR_REVERSE =			$12
CHAR_HOME =			$13
CHAR_BACKSPACE =		$20
CHAR_CURSOR_LEFT =	29
CHAR_SPACE =		$20
CHAR_MINUS =		45
CHAR_0 =			48
CHAR_1 =			49
CHAR_2 =			50
CHAR_3 =			51
CHAR_4 =			52
CHAR_5 =			53
CHAR_6 =			54
CHAR_7 =			55
CHAR_8 =			56
CHAR_9 =			57
CHAR_A =			65
CHAR_B =			66
CHAR_C =			67
CHAR_D =			68
CHAR_E =			69
CHAR_F =			70
CHAR_G =			71
CHAR_H =			72
CHAR_I =			73
CHAR_J =			74
CHAR_K =			75
CHAR_L =			76
CHAR_M =			77
CHAR_N =			78
CHAR_O =			79
CHAR_P =			80
CHAR_Q =			81
CHAR_R =			82
CHAR_S =			83
CHAR_T =			84
CHAR_U =			85
CHAR_V =			86
CHAR_W =			87
CHAR_X =			88
CHAR_Y =			89
CHAR_Z =			90
CHAR_LEFT_BRACKET =	91
CHAR_BACKSLASH =		92
CHAR_RIGFT_BRACKET =	93
CHAR_W =			87
CHAR_CLEAR =		$93
CHAR_NONE =		$FF
