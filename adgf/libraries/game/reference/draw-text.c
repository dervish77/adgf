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

/*
 *  INCLUDES
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include "draw-text.h"

#include <SDL/SDL.h>
#ifdef DRAWSDL_ENABLE_TEXT
#include <SDL/SDL_ttf.h>
#endif

#include "draw-sdl.h"


//#define DEBUG


//***************************************************************************//
// BEGIN SDL dependent section
//***************************************************************************//

//////////////////////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////////////////////

dtContext text;


//////////////////////////////////////////////////////////////////////////////
// color functions
//////////////////////////////////////////////////////////////////////////////

SDL_Color CreateSDLColorFromLongColor(long color)
{
    SDL_Color value;

    // ignore most significant byte
    value.r   = (color & 0x00FF0000) >> 16;
    value.g   = (color & 0x0000FF00) >> 8;
    value.b   = (color & 0x000000FF) >> 0;
    value.unused = 0;

    return value;
}


//////////////////////////////////////////////////////////////////////////////
// control functions
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// event functions
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// init functions
//////////////////////////////////////////////////////////////////////////////

int drawTextInit(char *font)
{
#ifdef DEBUG
    printf("drawTextInit: calling TTF_Init...\n");
#endif

    text.state = TEXT_STATE_CLOSED;

#ifdef DRAWSDL_ENABLE_TEXT
    sprintf(text.fontName, "%s", font);

    TTF_Init();

    text.state = TEXT_STATE_OPENED;
#endif

    return(0);
}

void drawTextQuit()
{
#ifdef DEBUG
    printf("drawTextQuit: calling TTF_Quit...\n");
#endif

#ifdef DRAWSDL_ENABLE_TEXT
    TTF_Quit();
#endif
        
    text.state = TEXT_STATE_CLOSED;
}


//////////////////////////////////////////////////////////////////////////////
// text functions
//////////////////////////////////////////////////////////////////////////////

void drawText(char *string, int size, int x, int y, long fgColor, long bgColor)
{    
#ifdef DEBUG
    printf("drawText: started...\n");
#endif

    SDL_Surface *myScreen = drawGetScreen();

#ifdef DRAWSDL_ENABLE_TEXT
    TTF_Font *font = TTF_OpenFont( text.fontName, size );
    if (!font)
    {
        printf("ERROR: drawText - TTF_OpenFont failed!\n");
    }
    else
    {
        SDL_Color foreColor = CreateSDLColorFromLongColor( fgColor );
        SDL_Color backColor = CreateSDLColorFromLongColor( bgColor );

        SDL_Surface *textSurface = TTF_RenderText_Shaded(font, string, foreColor, backColor);

        SDL_Rect textLocation = {x, y, 0, 0 };

        if (myScreen)
        {
            text.state = TEXT_STATE_BUSY;
            SDL_BlitSurface(textSurface, NULL, myScreen, &textLocation);
            text.state = TEXT_STATE_OPENED;
        }

        SDL_FreeSurface(textSurface);

        TTF_CloseFont(font);
    }
#endif

#ifdef DEBUG
    printf("drawText: done...\n");
#endif
}

void drawTextGetExtent(char *string, int size, int *w, int *h)
{    
#ifdef DEBUG
    printf("drawTextGetExtent: started...\n");
#endif

#ifdef DRAWSDL_ENABLE_TEXT
    TTF_Font *font = TTF_OpenFont( text.fontName, size );
    if (!font)
    {
        printf("ERROR: drawTextGetExtent - TTF_OpenFont failed!\n");
    }
    else
    {
        SDL_Color foreColor = CreateSDLColorFromLongColor( CLR_WHITE );
        SDL_Color backColor = CreateSDLColorFromLongColor( CLR_BLACK );

        SDL_Surface *textSurface = TTF_RenderText_Shaded(font, string, foreColor, backColor);

        // get width and height of rendered text surface
        *w = textSurface->w;
        *h = textSurface->h;

        SDL_FreeSurface(textSurface);

        TTF_CloseFont(font);
    }
#else
    *w = 0;
    *h = 0;
#endif

#ifdef DEBUG
    printf("drawTextGetExtent: done...\n");
#endif
}

void drawTextSetFont(char *font)
{
    sprintf(text.fontName, "%s", font);
}

char *drawTextGetFont()
{
    return(text.fontName);
}

//***************************************************************************//
// END platform independent section
//***************************************************************************//

/* end of draw-text.c */

