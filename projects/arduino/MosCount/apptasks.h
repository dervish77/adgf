/*****************************************************************************
 *
 *	MOS test program - tasks
 *
 *	File:	apptasks.h
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

#include "mos.h"


/*
 *  EXTERNS
 */
extern void counttask( void *args );
extern void printtask( void *args );

extern ARG_STRUCT dummyargs;

#endif
/* end of apptasks.h */
