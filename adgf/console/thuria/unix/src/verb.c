/*****************************************************************************
 *
 *	Verbs for Dungeons of Thuria.
 *
 *	File:	verb.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	11/06/98
 *
 *	Revs:
 *	  0.0 	11/06/98  originated
 *
 *****************************************************************************/


#ifndef MAIN_H
#include "main.h"
#endif


/* 
# verbs for Dungeons of Thuria
#
# Format: 
# verb #, word, type
#
*/

VERB_S_T verb[] = {
0, "north",	VB_NORTH,
1, "south",	VB_SOUTH,
2, "east",	VB_EAST,
3, "west",	VB_WEST,
-1
};


/* end of verb.c */
