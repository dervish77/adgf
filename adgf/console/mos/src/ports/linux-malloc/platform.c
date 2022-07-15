/*****************************************************************************
 *
 *	MOS library source code - platform specifc code
 *
 *  NOTE: "platform.c" requires porting to your hardware platform.
 *
 *	File:	platform.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	03/25/2009
 *
 *	Revs:
 *	  0.0 	03/25/2009  originated
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "platform.h"
#include "types.h"



#undef DEBUG



/*
 *  GLOBALS
 */



/*
 *  STATICS
 */




/* =========================================================================================== */
/*  Keyboard Device - typically a serial port based device                                     */
/* =========================================================================================== */

/*  mosOpenKeyboard - opens keyboard device 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosOpenKeyboard(void)
{

}


/*  mosReadKeyboard - reads single character from keyboard (non-blocking) 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	int     - single character from keyboard
 */
int mosReadKeyboard(void)
{
    return (0);
}


/*  mosCloseKeyboard - closes keyboard device 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosCloseKeyboard(void)
{

}


/* =========================================================================================== */
/*  LCD Device - either a serial port based device or parallel port based device               */
/* =========================================================================================== */

/*  mosOpenLcd - opens LCD device 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosOpenLcd(void)
{

}


/*  mosWriteLcd - write characters to LCD device 
 *
 *  Parameters:
 *	buf     - string of characters to write to LCD
 *
 *  Returns:
 *	int     - number of bytes written, or -1 on fail
 */
int mosWriteLcd(char *buf)
{
    return (-1);
}


/*  mosCloseLcd - closes LCD device 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosCloseLcd(void)
{

}


/* =========================================================================================== */
/*  Terminal Device - typically a serial port based device                                     */
/* =========================================================================================== */

/*  mosOpenTerminal - opens terminal device 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosOpenTerminal(void)
{

}


/*  mosReadTerminal - reads single character from terminal (non-blocking) 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	int     - single character from terminal
 */
int mosReadTerminal(char *buf)
{
    return (-1);
}


/*  mosWriteTerminal - write characters to terminal device 
 *
 *  Parameters:
 *	buf     - string of characters to write to terminal
 *
 *  Returns:
 *	int     - number of bytes written, or -1 on fail
 */
int mosWriteTerminal(char *buf)
{
    return (-1);
}


/*  mosCloseTerminal - closes terminal device 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void mosCloseTerminal(void)
{

}


/* =========================================================================================== */
/*  Debug Device - typically uses "printf" facility                                            */
/* =========================================================================================== */

/*  mosDbgPrint - debug print formatted output text 
 *
 *  Parameters:
 *	id      - debug id, allows potential control over which output is visible
 *	fmt     - formatted output string
 *
 *  Returns:
 *	none
 */
void mosDbgPrint( int id, const char *fmt, ... )
{
    const unsigned DBGPRINT_BUF_SIZE = 1024;
    char buf[DBGPRINT_BUF_SIZE];

    va_list argp;

    // Construct the variable part
    va_start(argp, fmt);
    vsnprintf( buf, DBGPRINT_BUF_SIZE, fmt, argp);
    va_end(argp);

    // Ensure null termination
    buf[DBGPRINT_BUF_SIZE-1] = 0;

    // Display the formatted output   
    printf("%03d %s", id, buf);
}

/*  mosPrint - print formatted output text
 *
 *  Parameters:
 *	fmt     - formatted output string
 *
 *  Returns:
 *	none
 */
void mosPrint( const char *fmt, ... )
{
    const unsigned DBGPRINT_BUF_SIZE = 1024;
    char buf[DBGPRINT_BUF_SIZE];

    va_list argp;

    // Construct the variable part
    va_start(argp, fmt);
    vsnprintf( buf, DBGPRINT_BUF_SIZE, fmt, argp);
    va_end(argp);

    // Ensure null termination
    buf[DBGPRINT_BUF_SIZE-1] = 0;

    // Display the formatted output   
    printf("%s", buf);
}

/* end of platform.c */
