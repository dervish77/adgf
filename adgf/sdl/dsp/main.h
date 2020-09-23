/*****************************************************************************
 *
 *  DspDemo main program.
 *
 *  Description:
 *      DspDemo using LibSDL.
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


#define VERSION "0.1.2"



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


#define MODE_NONE       1
#define MODE_LOWPASS    2
#define MODE_HIGHPASS   3


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

