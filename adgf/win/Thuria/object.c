/*****************************************************************************
 *
 *	Object file for Dungeons of Thuria.
 *
 *	File:	object.c
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
# object file for Dungeons of Thuria
#
# Format:
# object #, score, search key, prep phrase, full name of object, examine phrase
#
*/

OBJECT_S_T object[] = {
0,   0, "lamp",     "is an",	"antique oil lamp",		"It's a genuine antique.",
1,  20, "coins",    "are",	"some gold coins",		"Behold the likeness of Queen Zamboula.",
2,   0, "skeleton", "is a",	"skeleton",			"Upon closer inspection, the skeleton turns out to be\nthe remains of the long dead King Tanuka.",
3,  10, "sword",    "is a",	"jewel encrusted sword",	"Fine workmanship.  A real treasure.",
4,  10, "bars",     "are",	"two silver bars",		"They are rather heavy.",
5,  10, "twinkies", "is a",	"sealed package of twinkies",	"The package is dated Jan 05, 1977.",
6,  10, "nail",     "is a",	"rusty nail",			"Looks like a common eight penny nail.",
7,   0, "chest",    "is a",	"heavy chest",			"Looks like it weighs over 300 pounds, and there is a \nmagic aura around it.",
8,   0, "beaver",   "are",	"several beavers",		"They are ignoring you.",
9,  10, "padlock",  "is a", 	"padlock",			"Cheap lock, easily picked.",
10, 10, "paper",    "is a",	"piece of crumpled paper",	"Scrawled in a strange script is a single sentence:\n\"Seek the hall of three questions\".",
11, 10, "flute",    "is a",	"silver flute",			"There is nothing special about the silver flute.",
12, 20, "jewels",   "are",	"three tiny purple jewels",	"To your uneducated eye they look like amythest.",
13,  0, "pillows",  "are", 	"several embroidered pillows", 	"The pillows are embroidered with pictures of flowers and fruits.",
14, 10, "vase",     "is a",	"delicate Ming vase",		"Probably made in the 4th dynasty.",
15,  0, "statue",   "is an",	"indian statue",		"Odd, the statue has a coin sized slot on its left side.",
16, 10, "rod",	    "is a",	"hollow black rod",		"The rod is about half a meter in length and about an inch thick.",
17, 20, "emerald",  "is a",	"glowing green emerald",	"The emerald is the size of a Plover's egg.",
18, 10, "boots",    "is a",	"rotting pair of boots",	"Strangely, the boots smell like rotten eggs.",
19,  0, "grate",    "is a",     "iron grate",			"Strong, no rust.  There is a small keyhole to one side.",
20, 20, "rug",      "is a",	"large oriental rug",		"Even rolled up it's about 6 feet long.",
21,  0, "bear",     "is a", 	"brown bear",			"He is sleeping soundly.",
22, 20, "diamonds", "are",	"several diamonds",		"Each one is a full carat.",
23,  0, "slab",     "is a",	"stone slab",			"A six foot high stone slab appears to be loose and could be moved.",
24, 20, "scroll",   "is a",	"rolled up scroll",		"It says: \"answer your name, answer home, and answer Marcus\".",
25, 20, "egg",	    "is a",	"golden egg",			"Seemingly hollow, it is about the size of an osterich egg.",
26, 10, "book",	    "is a",	"giant leather bound book",	"Printed on the cover is \"Spells and Tricks\" by Marcus, WhD.",
27,  0, "fissure",  "is a",	"wide deep fissure",		"The fissure is far too wide to jump across, and it appears bottomless.",
28,  0, "rope",     "is",	"some rope inside a basket",	"The rope looks good and strong for climbing.",
29,  0, "basket",   "is a",	"wicker basket",		"Hand made.  Nice workmanship.",
30, 20, "pyramid",  "is a",	"platinum pyramid",		"Etched into the bottom of the pyramid is a single word \"neep\".",
31, 20, "pearl",    "is a",	"shiny white pearl",		"There is nothing special about the white pearl.",
32,  0, "man",      "is a",	"little hooded man",		"His hood completely hides his facial features.  His robes \nare tattered and very dirty.",
33,  0, "door",     "is a",     "heavy wooden door",            "Probably made from oak, bound with strong metal bands.",
34, 10, "key",      "is a",     "shiny brass key",              "There is nothing special about the key.",
35,  0, "lake",     "is a",     "vast underground lake",        "The lake is huge and much too deep to swim across.  Some creatures\nare visible beneath the waves.",
36, 20, "oil",      "is some",  "lamp oil",			"This appears to be enough lamp oil for several more hours of exploring.",
-1
};



/* end of object.c */
