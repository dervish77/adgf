/*****************************************************************************
 *
 *	RPG game gscreens.
 *
 *  Description:
 *  RPG game using LibSDL.
 *
 *	File:	screens.cpp
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw-sdl.h"
#include "screens.h"
#include "main.h"


SCREEN_S_T gscreen;


SPRITE_S_T gameSprites[PIECE_COUNT];
/*
 = {
    { PIECE_NULL,     GR_NULL,     NULL },
    { PIECE_PLAYER_U, GR_PLAYER_U, NULL },
    { PIECE_PLAYER_D, GR_PLAYER_D, NULL },
    { PIECE_PLAYER_L, GR_PLAYER_L, NULL },
    { PIECE_PLAYER_R, GR_PLAYER_R, NULL },
    { PIECE_ROID,     GR_ROID,     NULL },
    { PIECE_ROIDX,    GR_ROIDX,    NULL },
    { PIECE_AMMO,     GR_AMMO,     NULL },
    { PIECE_HEALTH,   GR_HEALTH,   NULL },
    { PIECE_WARP,     GR_WARP,     NULL },
    { PIECE_UFO,      GR_UFO,      NULL }
};
*/

void ScreenOpen()
{  
    gscreen.width  = WIDTH;
    gscreen.height = HEIGHT;
    gscreen.bpp    = BPP;
    
    gscreen.grid_color          = GRID_LINE_COLOR;
    gscreen.background_color    = GRID_BK_COLOR;
    gscreen.cell_alive_color    = GRID_CELL_ALIVE_COLOR;
    gscreen.cell_dead_color     = GRID_CELL_DEAD_COLOR;
    
    gscreen.grid_cells_x = GRID_CELLS_X;
    gscreen.grid_cells_y = GRID_CELLS_Y;
    
    gscreen.grid_width  = gscreen.width  / gscreen.grid_cells_x;
    gscreen.grid_height = gscreen.height / gscreen.grid_cells_y;

    gscreen.grid_enable = 0;
    
    drawInitExtended(gscreen.width, gscreen.height, gscreen.bpp, GAME_TITLE);

    printf("Using DrawSdl version %s\n", drawGetVersion() );
}


void ScreenClear()
{  
    drawBackground(gscreen.background_color);
}


void ScreenPause(int delay)
{  
    drawWait(delay);
}


void ScreenWaitQuit()
{
    drawWaitQuit();
}


void ScreenClose()
{  
    drawQuit();
}

void ScreenLoadSprites()
{
    int ii;
    
    printf("Loading game sprites...\n");
    
    // init game sprites table
    gameSprites[0].piece_type = PIECE_NULL;
    gameSprites[0].file = GR_NULL;
    gameSprites[1].piece_type = PIECE_PLAYER_U;
    gameSprites[1].file = GR_PLAYER_U;
    gameSprites[2].piece_type = PIECE_PLAYER_D;
    gameSprites[2].file = GR_PLAYER_D;
    gameSprites[3].piece_type = PIECE_PLAYER_L;
    gameSprites[3].file = GR_PLAYER_L;
    gameSprites[4].piece_type = PIECE_PLAYER_R;
    gameSprites[4].file = GR_PLAYER_R;
    gameSprites[5].piece_type = PIECE_ROID;
    gameSprites[5].file = GR_ROID;
    gameSprites[6].piece_type = PIECE_ROIDX;
    gameSprites[6].file = GR_ROIDX;
    gameSprites[7].piece_type = PIECE_AMMO;
    gameSprites[7].file = GR_AMMO;
    gameSprites[8].piece_type = PIECE_HEALTH;
    gameSprites[8].file = GR_HEALTH;
    gameSprites[9].piece_type = PIECE_WARP;
    gameSprites[9].file = GR_WARP;
    gameSprites[10].piece_type = PIECE_UFO;
    gameSprites[10].file = GR_UFO;
    
    // load the sprites
    for (ii = 0; ii < PIECE_COUNT; ii++)
    {
        printf("... %s\n", gameSprites[ii].file);
        drawLoadSprite( &gameSprites[ii].sprite, gameSprites[ii].file );
    }
}

int ScreenAddTimer(int delay, int timer)
{
    return( drawAddTimer(delay, timer) );
}


void ScreenRemoveTimer( int id )
{
    drawRemoveTimer( id );
}


int  GetGridWidth()
{
    return( gscreen.grid_width ); 
}


int  GetGridHeight()
{
    return( gscreen.grid_height ); 
}


int GetScreenEvent(int *x, int *y, char *key)
{
    return( drawGetEvent( x, y, key ) );
}


void DoTitleScreen()
{
    int x, y;
    int w, h;    // screen width and height   
    int bw, bh;  // bitmap width and height
      
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(gscreen.background_color);
            
    // draw title bitmap
    bw = drawGetBitmapWidth(GR_TITLE);
    bh = drawGetBitmapHeight(GR_TITLE);
    
    // calculate top left x,y
    x = w/2 - bw/2;
    y = h/2 - bh/2;
    drawBitmap(GR_TITLE, x, y);

    // call this to make everything appear on the screen
    drawSwapBuffers();
}


void DoPlayScreen()
{
    ScreenDrawGrid();
    ScreenUpdate();
}


void ScreenDrawGrid()
{
    int w, h;    // screen width and height   
      
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(gscreen.cell_dead_color);

    if (gscreen.grid_enable)
    {
        // draw horizontal lines
        for (int y = 0; y < h; y = y + gscreen.grid_height)
        {
            drawLine( gscreen.grid_color,   0, y,   w, y );
        }

        // draw vertical lines
        for (int x = 0; x < w; x = x + gscreen.grid_width)
        {
            drawLine( gscreen.grid_color,   x, 0,   x, h );
        }
    }
}


void ScreenDrawCell(int piece, int cx, int cy)
{
    int x, y;
    int bw, bh;
    
    bw = GetGridWidth();
    bh = GetGridHeight();
    x = cx - bw/2;
    y = cy - bh/2;

#if 1
    // draw cell without overwriting grid lines
    if ( piece > PIECE_NULL )
    {
        drawSprite( &gameSprites[piece].sprite, x+1, y+1 );
    }
    else
    {
        drawSolidRect( gscreen.cell_dead_color, x+1,y+1, bw-1,bh-1 );
    }
#endif
    
#if 0
    // draw cell without overwriting grid lines
    if (piece >= PIECE_ALIVE)
    {
        drawSolidRect( gscreen.cell_alive_color, x+1,y+1, bw-1,bh-1 );
    }

    if (piece == PIECE_DEAD)
    {
        drawSolidRect( gscreen.cell_dead_color, x+1,y+1, bw-1,bh-1 );
    }
#endif
}


void ScreenUpdate()
{
    drawSwapBuffers();
}


/* end of screens.c */
