/*****************************************************************************
 *
 *	Ranks for Dungeons of Thuria.
 *
 *	File:	rank.c
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
# ranks for Dungeons of Thuria
#
# Format: 
# rank #, title, phrase
#
*/

RANK_S_T rank[] = {
0, "Hopeless",		"Maybe you should stick to playing Doom.",
1, "Clueless",		"Well, at least you're trying.",
2, "Apprentice",	"You don't get out much, do you?",
3, "Journeyman",	"Don't you ever sleep?",
4, "Magician", 		"Hey, you're quite the wiz at this stuff!",
5, "Wizard", 		"The gods of interactive fiction bow down to you.",
-1
};


/* end of rank.c */
