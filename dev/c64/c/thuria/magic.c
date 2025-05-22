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
0,   5, -1, -1, "xyzzy",  "Your vision blurs momentarily, then \nclears. Apparently nothing happened.",
1,   5, 19, 19, "plugh",  "A hollow voice echoes plugh, but you \nhaven't moved an inch.", 
2,   5, 22, 25, "plover", "A flash of green light blinds you \nmomentarily. When your vision\nreturns, you find that ...", 
3,   5, 23,  0, "pillow", "A few feathers fall from the ceiling \nand land on your nose. When the \nsneezing fit ends, you find that ...", 
4,  10, 33, 33, "marcus", "Suddenly, you are floating in a \nstrange black void. After a \nfew moments reality returns.", 
5,  20, 40, 41, "neep",   "An orange mist swirls around your head.\nYou black out. When you awake, \nyou find that ...", 
-1
};


/* end of magic.c */
