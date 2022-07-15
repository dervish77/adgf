/***********************************************************************

 Multi-Player client/server code for Othello game.

   File:  	multi.c

   Author: 	Brian Lingard

   Date:	01/30/98

   Revisions:
	0.0	01/30/98	Originated

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "othello.h" */
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif




/******************************************************************************
*  CheckForNetwork - verifies networking support is present                   *
******************************************************************************/
int
CheckForNetwork()
{
   return(TRUE);
}


/******************************************************************************
*  HandleServerOpen - open a passive socket to listen                         *
******************************************************************************/
void
HandleServerOpen(MyProgram *data)
{

}


/******************************************************************************
*  HandleClientOpen - open a socket to server                                 *
******************************************************************************/
void
HandleClientOpen(MyProgram *data)
{

}


/* end of multi.c */
