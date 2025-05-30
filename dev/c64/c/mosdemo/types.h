/*****************************************************************************
 *
 *	MOS library source code - common types
 *
 *	File:	types.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	03/25/2009
 *
 *	Revs:
 *	  0.0 	03/25/2009  originated
 *
 *****************************************************************************/

#ifndef _TYPES_H
#define _TYPES_H


/*  declare common types
 */
#define EQ	==
#define AND	&&
#define OR	||

typedef int BOOLEAN_T;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


/*  define buffer type
 */
#define SHORT_BUFF_LEN      20
#define LONG_BUFF_LEN       40

typedef char SHORT_BUFFER_T[SHORT_BUFF_LEN];
typedef char LONG_BUFFER_T[LONG_BUFF_LEN];


#define UNUSED(x) (void)(x)


#endif /* _TYPES_H */
