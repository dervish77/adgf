/*
 *     Module Name:  draw-text.h
 *
 *     Author:      Brian Lingard
 *
 *     Description:
 *	   Contains extension to draw-sdl that handles drawing text 
 *	   via SDL_ttf library.
 *
 *     Notes:
 *
 *
 */

#ifndef __draw_text_h
#define __draw_text_h

#include "draw-sdl.h"


//////////////////////////////////////////////////////////////////////////////
// defines for drawing
//////////////////////////////////////////////////////////////////////////////

#define TEXT_STATE_CLOSED       0
#define TEXT_STATE_OPENED       1
#define TEXT_STATE_BUSY         2


//////////////////////////////////////////////////////////////////////////////
// define useful macros
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// define useful events
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// define useful structures
//////////////////////////////////////////////////////////////////////////////

typedef struct {
    char fontName[64];
    int state;
    int size;           // font size
    long fgColor;       // foreground color
    long bgColor;       // background color
} dtContext;


//////////////////////////////////////////////////////////////////////////////
// prototypes
//////////////////////////////////////////////////////////////////////////////

// from draw-text.c SDL dependent section

int  drawTextInit(char *font);
void drawTextQuit();

void drawTextSetFont(char *font);
char *drawTextGetFont();

void drawTextSetSize(int size);

void drawTextSetColor(long fgColor, long bgColor);

void drawText(char *string, int x, int y);
void drawText(char *string, int size, int x, int y, long fgColor, long bgColor);

void drawTextGetExtent(char *string, int size, int *w, int *h);

#endif /* __draw_text_h */

