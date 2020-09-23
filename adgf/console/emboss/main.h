/*****************************************************************************
 *
 *	Emboss main program.
 *
 *  Description:
 *  Embossing Demo using LibSDL.
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


#define VERSION "0.2.0"



/*
 *  CONFIGURATION
 */


#define UNUSED(x) (void)(x)


/*
 *  CONSTANTS
 */

#define WIDTH   WIDTH_1024
#define HEIGHT  (HEIGHT_768 / 2)
#define BPP     BPP_16


#define MODE_VIEW_ALL     1
#define MODE_VIEW_INPUT   2
#define MODE_VIEW_MAP     3
#define MODE_VIEW_OUTPUT  4


#define DEFAULT_INPUT_NAME    "input.bmp"
#define DEFAULT_MAP_NAME      "map.bmp"
#define DEFAULT_OUTPUT_NAME   "output.bmp"


#define CENTER_Y    (HEIGHT / 2)

#define LEFT_X      (WIDTH / 4)
#define MIDDLE_X    (WIDTH / 2)
#define RIGHT_X     (MIDDLE_X + LEFT_X)



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

typedef struct _demo_s_t {
    int view_mode;
    int screen_w;
    int screen_h;
    int bpp;
    char inputName[64];
    char mapName[64];
    char outputName[64];
    spriteContext inputSprite;
    spriteContext mapSprite;
    spriteContext outputSprite;
} DEMO_S_T;


#endif /* __main_h */

