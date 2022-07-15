/*****************************************************************************
 *
 *	Introduction for Dungeons of Thuria.
 *
 *	File:	intro.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	03/06/98
 *
 *	Revs:
 *	  0.0 	03/06/98  originated
 *
 *****************************************************************************/

#include <stdio.h>

#ifndef MAIN_H
#include "main.h"
#endif



/* 
# Introduction for Dungeon
#
# Format:
#
# Line #, Intro Line,
*/

INTRO_S_T intro[] = {
0, "  How's this for luck?  You slept through your alarm this morning.  Your",
0, "shower had only cold water.  Then your car wouldn't start.  Dead Battery.",
0, "The garage mechanic said that a 20 car pile up on the freeway will",
0, "delay him towing your car for at least 3 hours.", 
0, " ",
0, "  So you decide to sit back and enjoy a second cup of coffee and read the",
0, "morning's paper.  As usual, you skip to the comics section first.  But",
0, "before you can even read the first strip, you notice a strange orange",
0, "cloud swirling outside your window.  It envelopes your house and makes ",
0, "you feel dizzy.  You pass out.  Upon awakening you find that...",
-1
};


/* end of intro.c */
