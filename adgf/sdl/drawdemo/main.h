/*****************************************************************************
 *
 *	Draw Demo main program.
 *
 *  Description:
 *  Draw Demo using LibSDL.
 *
 *	File:	main.h
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#ifndef __main_h
#define __main_h

#include "draw-sdl.h"


#define VERSION "0.2.3"



/*
 *  CONFIGURATION
 */

#define ENABLE_MOUSE_MOTION


/*
 *  CONSTANTS
 */

#define WIDTH   WIDTH_1024
#define HEIGHT  HEIGHT_768
#define BPP     BPP_16


#define MODE_PIXELS     1
#define MODE_RECTS      2
#define MODE_CIRCLES    3


/*
 *  PROTOTYPES
 */

void PrintBanner();
void PrintUsage();


/*
 *  STATICS
 */



/*
 *  STRUCTURES
 */



#endif /* __main_h */

