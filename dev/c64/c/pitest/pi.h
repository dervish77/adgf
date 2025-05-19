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


#define MINCOUNT 3
#define MAXCOUNT 20



/*  declare prototypes for all functions
 */
BOOLEAN_T CalcPi64( int digits );

BOOLEAN_T CalcPiDiv( int digits );


#endif 	/* _PI_H */
