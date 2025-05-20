/*****************************************************************************
 *
 *	MOS test program - tasks
 *
 *	File:	tasks.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *****************************************************************************/

#ifndef _TASKS_H
#define _TASKS_H

#include <stdio.h>
#include <string.h>

#include "mos.h"


/*
 *  EXTERNS
 */
extern void dummy( void *args );
extern void dummygetid( void *args );
extern void dummysuspend( void *args );
extern void dummymemory( void *args );
extern void dummymsg1( void *args );
extern void dummymsg2( void *args );
extern void dummybroadcast( void *args );

extern ARG_STRUCT dummyargs;

#endif
/* end of tasks.h */
