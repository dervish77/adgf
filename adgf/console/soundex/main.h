/*****************************************************************************
 *
 *	Soundex translator program - main header file.
 *
 *	File:	main.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	6/4/96
 *
 *	Revs:
 *	  0.0 	6/4/96  originated
 *
 *****************************************************************************/

#ifndef _MAIN_H
#define _MAIN_H

#include "file.h"
#include "soundex.h"


#define VERSION "0.4"


/*  declare common types
 */
#define EQ	==
#define AND	&&
#define OR	||

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef int BOOLEAN_T;


/*  declare prototypes
 */
extern void DisplayVersion( char *progname );
extern void ErrorUsage( char *progname );


#endif 	/* _MAIN_H */
