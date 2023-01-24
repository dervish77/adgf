/*****************************************************************************
 *
 *	Test program for calculating PI.
 *
 *	File:	pi.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	11/02/95
 *
 *	Revs:
 *	  0.0 	11/02/95  originated
 *
 *****************************************************************************/

#ifndef _PI_H
#define _PI_H


/*  declare common types
 */
#define EQ	==
#define AND	&&
#define OR	||

typedef int 		BOOLEAN_T;
typedef unsigned char 	UBYTE_T;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif



/*  define file name type
 */
#define FILE_NAME_LEN	30
typedef char FILENAME_T[FILE_NAME_LEN];





/*  declare prototypes for all functions
 */
extern BOOLEAN_T CalcPi( int digits );

#if 0
extern int ParseString(char *string, char *args[]);
#endif

#endif 	/* _PI_H */
