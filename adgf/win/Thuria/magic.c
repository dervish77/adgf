/*****************************************************************************
 *
 *	Magic words for Dungeons of Thuria.
 *
 *	File:	magic.c
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
# magic words for Dungeons of Thuria
#
# Format: 
# magic #, score, from, to, word, phrase
#
*/

MAGIC_S_T magic[] = {
0,   5, -1, -1, "xyzzy",  "Your vision blurs momentarily, then clears.  Apparently nothing happened.",
1,   5, 15, 15, "plugh",  "A hollow voice echoes plugh, but you haven't moved an inch.", 
2,   5, 27, 20, "plover", "A flash of green light blinds you momentarily.  When your vision\nreturns, you find that ...", 
3,   5, 19,  0, "pillow", "A few feathers fall from the ceiling and land on your nose.\nWhen the sneezing fit ends, you find that ...", 
4,  10, 33, 33, "marcus", "Suddenly, you are floating in a strange black void.  After a few\nmoments reality returns.", 
5,  20, 40, 41, "neep",   "An orange mist swirls around your head.  You black out.  When you\nawake, you find that ...", 
-1
};


/* end of magic.c */
