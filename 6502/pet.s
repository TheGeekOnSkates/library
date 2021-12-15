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
SCNKEY = $FF9F			/* Scan keyboard */
GETIN = $FFE4
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
/* CHARACTER CODES & OTHER MISC. CODES                                       */
/*****************************************************************************/

CHARSET_UPPER = $0B
CHARSET_LOWER =	$0E



KEY_RETURN =	$0D
KEY_CLEAR =	$93
KEY_NONE =	$FF
