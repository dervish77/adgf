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
extern void getid( void *args );
extern void blinktask( void *args );
extern void cmdtask( void *args );
extern void kbdtask( void *args );

extern ARG_STRUCT dummyargs;

#endif
/* end of tasks.h */
