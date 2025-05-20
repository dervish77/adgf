/*****************************************************************************
 *
 *	MOS library source code - platform specifc code
 *
 *  NOTE: "platform.c" requires porting to your hardware platform.
 *
 *	File:	platform.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	03/25/2009
 *
 *	Revs:
 *	  0.0 	03/25/2009  originated
 *
 *****************************************************************************/

#ifndef _PLATFORM_H
#define _PLATFORM_H

#include <stdlib.h>
#include <stdarg.h>

#define PLATFORM "Linux"


/*  declare prototypes for PUBLIC "platform.c" functions
 */
extern void mosOpenKeyboard(void);
extern int  mosReadKeyboard(void);
extern void mosCloseKeyboard(void);

extern void mosOpenLcd(void);
extern int  mosWriteLcd(char *buf);
extern void mosCloseLcd(void);

extern void mosOpenTerminal(void);
extern int  mosReadTerminal(char *buf);
extern int  mosWriteTerminal(char *buf);
extern void mosCloseTerminal(void);

extern void mosDbgPrint( int id, const char *fmt, ... );
extern void mosPrint( const char *fmt, ... );


/*  declare prototypes for PRIVATE "hw.c" functions
 */
extern void hwInitBoard(void);

extern void hwInitTaskTimer(int tickTime);
extern void hwStartTaskTimer(void);
extern void hwCheckTaskTimer(int tickTime);
extern void hwStopTaskTimer(void);

extern void hwInitDevice(int deviceId);


#endif /* _PLATFORM_H */
