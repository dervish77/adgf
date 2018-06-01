/*****************************************************************************
 *
 *	Soundex translator program - file routines header file.
 *
 *	File:	file.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	6/4/96
 *
 *	Revs:
 *	  0.0 	6/4/96  originated
 *
 *****************************************************************************/

#ifndef _FILE_H
#define _FILE_H

#include "main.h"
#include "soundex.h"


/*  declare prototypes for all functions
 */
extern int OpenSurnameListFile( char *filename, DATABASE_S_T *data );

extern int ReadSurnameListFile( DATABASE_S_T *data );

extern int OutputSurnameList( DATABASE_S_T *data );

extern int CloseSurnameListFile( DATABASE_S_T *data );

extern void ErrorOpenFile(char *string);


#endif 	/* _FILE_H */
