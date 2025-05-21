/*****************************************************************************
 *
 *	Special effect file for Dungeons of Thuria.
 *
 *	File:	special.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	12/04/96
 *
 *	Revs:
 *	  0.1	02/13/98  converted to "c" file
 *	  0.0 	12/04/96  originated
 *
 *****************************************************************************/


#ifndef MAIN_H
#include "main.h"
#endif


/* 
# special effect file for Dungeons of Thuria
#
# Format: 
# special #, score, phrase
#
*/

SPECIAL_S_T special[] = {
0,   0, "Empty treasure chest sits in corner.", 	
1,   0, "A treasure chest contains:",
2,   0, "Door is shut and padlocked.",
3,  10, "Door is shut, padlock hangs loose.",
4,   0, "Door is open, padlock dangles.",
5,   0, "Rotting skeleton sits on throne.",
6,   0, "Skeleton is attacking you.",
7,  10, "Skeleton lays crumpled on floor.",
8,   0, "One beaver looks a bit hungry.",
9,   0, "One beaver tries to bite your leg.",
10,  0, "Bloody carcass of a beaver here.",
11,  0, "Heavy wooden door is closed.",
12,  0, "Heavy wooden door is open.",
13,  0, "A sign warns against swimming.",
14,  0, "A yellow sign warns about swimming.",
15,  0, "Statue points bow/arrow to north.",
16, 10, "Statue points bow/arrow to south.",
#if 0
17,  0, "The rope is coiled neatly inside of the basket.",
18, 10, "The rope reaches from the basket all the way up to the opening.", 
19,  0, "An iron grate covers a hole to a room below, but it is locked.",
20, 10, "An iron grate covers a hole to a room below, but it is closed.",
21,  0, "An iron grate is open, revealing a room below.",
22,  0, "A black bear is snoozing peacefully on the oriental rug.",
23, 10, "Some bear fur seems to be stuck to everything.",
24,  0, "The dead carcass of a black bear is lying on the oriental rug.",
25,  0, "Leaning against the eastern wall is a large stone slab.",
26, 10, "A large stone slab partially blocks a narrow passage to the east.",
27,  0, "Your footsteps echo as you peer into the dark fissure.",
28,  0, "A cold wind chills you as you peer into the dark fissure.",
29, 10, "A crystal bridge spans the fissure.",
30,  0, "Broken shards of crystal lie about everywhere.",
31,  0, "You feel a cool breeze blowing in your face.",
32, 10, "You feel like you could walk on water.",
33,  0, "Upon seeing you, the strange man asks you \"What is your name?\"",
34,  0, "The man nods, then asks \"What is your quest?\"",
35,  0, "The man now asks \"Who wrote \'Spells and Tricks\'?\"",
36, 10, "You have successfully answered the man's questions and may now pass.",
#endif
-1
};


/* end of special.c */
