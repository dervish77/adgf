/*****************************************************************************
 *
 *	SicDacLoe game screens.
 *
 *  Description:
 *  Tic Tac Toe using LibSDL.
 *
 *	File:	screens.c
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
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


void ScreenOpen()
{  
    gscreen.width  = WIDTH;
    gscreen.height = HEIGHT;
    gscreen.bpp    = BPP;
    
    gscreen.background_color = CLR_BLACK;
    gscreen.grid_color       = CLR_YELLOW;
    
    gscreen.grid_cells_x = 3;
    gscreen.grid_cells_y = 3;
    
    gscreen.grid_width  = gscreen.width  / gscreen.grid_cells_x;
    gscreen.grid_height = gscreen.height / gscreen.grid_cells_y;
    
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

void DoPlayerScreen(BOUNDS_S_T *p1bounds, BOUNDS_S_T *p2bounds)
{
    int x, y;
    int w, h;    // screen width and height   
    int bw, bh;  // bitmap width and height
      
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(gscreen.background_color);
            
    // draw single player bitmap
    bw = drawGetBitmapWidth(GR_ONE_PLAYER);
    bh = drawGetBitmapHeight(GR_ONE_PLAYER);
    x = w/2 - bw/2;
    y = h/2 - bh - 30;
    p1bounds->top_left_x = x;
    p1bounds->top_left_y = y;
    p1bounds->bottom_right_x = x + bw;
    p1bounds->bottom_right_y = y + bh;
    drawBitmap(GR_ONE_PLAYER, x, y);
    
    // draw two player bitmap
    bw = drawGetBitmapWidth(GR_TWO_PLAYER);
    bh = drawGetBitmapHeight(GR_TWO_PLAYER);
    x = w/2 - bw/2;
    y = h/2 + 30;
    p2bounds->top_left_x = x;
    p2bounds->top_left_y = y;
    p2bounds->bottom_right_x = x + bw;
    p2bounds->bottom_right_y = y + bh;
    drawBitmap(GR_TWO_PLAYER, x, y);
    
    // call this to make everything appear on the screen
    drawSwapBuffers();
}


void ScreenDrawGrid()
{
    int w, h;    // screen width and height   
      
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(gscreen.background_color);

    // draw horizontal lines
    drawLine( gscreen.grid_color, 0, h/gscreen.grid_cells_y,       w, h/gscreen.grid_cells_y     );
    drawLine( gscreen.grid_color, 0, 2 * h/gscreen.grid_cells_y,   w, 2 * h/gscreen.grid_cells_y );

    // draw vertical lines
    drawLine( gscreen.grid_color, w/gscreen.grid_cells_x, 0,           w/gscreen.grid_cells_x, h );
    drawLine( gscreen.grid_color, 2 * w/gscreen.grid_cells_x, 0,   2 * w/gscreen.grid_cells_x, h );
}


void ScreenDrawPiece(int piece, int cx, int cy)
{
    int x, y;
    int bw, bh;
    
    if (piece == PIECE_X)
    {
        bw = drawGetBitmapWidth(GR_X);
        bh = drawGetBitmapHeight(GR_X);
        x = cx - bw/2;
        y = cy - bh/2;
        drawBitmap(GR_X, x, y);
    }
    
    if (piece == PIECE_O)
    {
        bw = drawGetBitmapWidth(GR_O);
        bh = drawGetBitmapHeight(GR_O);
        x = cx - bw/2;
        y = cy - bh/2;
        drawBitmap(GR_O, x, y);        
    }
}


void ScreenUpdate()
{
    drawSwapBuffers();
}


void DoVictoryScreen(int player)
{
    int x, y;
    int w, h;    // screen width and height   
    int bw, bh;  // bitmap width and height
    
    char filename[20];
      
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(gscreen.background_color);
    
    // select correct bitmap for winning player
    switch(player)
    {
        case 0:
            sprintf(filename, "%s", GR_NO_WINS);
            break;
        case 1:
            sprintf(filename, "%s", GR_P1_WINS);
            break;
        case 2:
            sprintf(filename, "%s", GR_P2_WINS);
            break;
    }    

    // draw victory bitmap
    bw = drawGetBitmapWidth(filename);
    bh = drawGetBitmapHeight(filename);
    x = w/2 - bw/2;
    y = h/2 - bh/2;
    drawBitmap(filename, x, y);
    
    // call this to make everything appear on the screen
    drawSwapBuffers();
}

/* end of screens.c */
