/*****************************************************************************
 *
 *	Breakout game screens.
 *
 *  Description:
 *  Breakout using LibSDL.
 *
 *	File:	screens.cpp
 *
 *	Author: Brian Lingard
 *	Date:	11/12/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw-sdl.h"
#include "screens.h"
#include "main.h"


//
// Globals
//

SCREEN_S_T gscreen;

spriteContext blockSprites[NUM_BLOCK_TYPES];       // array of block sprites


//
// Initialization and utility functions
//

void ScreenOpen()
{  
    gscreen.width  = WIDTH;
    gscreen.height = HEIGHT;
    gscreen.bpp    = BPP;
    
    gscreen.background_color = CLR_BLACK;
    
    drawInitExtended(gscreen.width, gscreen.height, gscreen.bpp, GAME_TITLE);

    printf("Using DrawSdl version %s\n", drawGetVersion() );
}


void ScreenLoadBlocks()
{
    int i;
    char filename[20];

    for (i = 0; i < NUM_BLOCK_TYPES; i++)
    {
        sprintf(filename, "%s%d.bmp", GR_BLOCK, (i+1));

        drawLoadSprite( &blockSprites[i], filename );
    }
}


void ScreenLoadPaddle(PADDLE_S_T *paddle)
{
    switch(paddle->paddle_state)
    {
        case PADDLE_STATE_SHORT:
            drawLoadSprite( &paddle->sprite, GR_PADSHORT );
            break;
        case PADDLE_STATE_NORMAL:
            drawLoadSprite( &paddle->sprite, GR_PADNORMAL );
            break;
        case PADDLE_STATE_LONG:
            drawLoadSprite( &paddle->sprite, GR_PADLONG );
            break;
    }
}


void ScreenLoadBall(BALL_S_T *ball)
{
    switch(ball->ball_state)
    {
        case BALL_STATE_NORMAL:
            drawLoadSprite( &ball->sprite, GR_BALL_NORMAL );
            break;
        case BALL_STATE_SPECIAL:
            drawLoadSprite( &ball->sprite, GR_BALL_SPECIAL );
            break;
    }
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


void ScreenUpdate()
{
    drawSwapBuffers();
}


void CopyBlockSprite(spriteContext *sprite, int index)
{
    spriteContext *source = &blockSprites[index];

    sprite->image        = source->image;
    sprite->width        = source->width;
    sprite->height       = source->height;
    sprite->half_w       = source->half_w;
    sprite->half_h       = source->half_h;
    sprite->bpp          = source->bpp;
    sprite->alphaEnabled = source->alphaEnabled;
}


int  GetScreenWidth()
{
    return( drawGetWidth() ); 
}


int  GetScreenHeight()
{
    return( drawGetHeight() ); 
}


int GetPaddleWidth(PADDLE_S_T *paddle)
{
    char filename[20];

    switch(paddle->paddle_state)
    {
        case PADDLE_STATE_SHORT:
            sprintf(filename, "%s", GR_PADSHORT);
            break;
        case PADDLE_STATE_NORMAL:
            sprintf(filename, "%s", GR_PADNORMAL);
            break;
        case PADDLE_STATE_LONG:
            sprintf(filename, "%s", GR_PADLONG);
            break;
    }    

    return( drawGetBitmapWidth(filename) );
}


int  GetBlockWidth()
{
    return( drawGetBitmapWidth(GR_BLOCK1) ); 
}


int  GetBlockHeight()
{
    return( drawGetBitmapHeight(GR_BLOCK1) ); 
}


int GetScreenEvent(int *x, int *y, char *key)
{
    return( drawGetEvent( x, y, key ) );
}


vectorType GetWallNormal(int whichWall)
{
    vectorType vec = MakeVector(0, 0, 0);

    switch(whichWall)
    {
        case WALL_TOP:
            vec = MakeVector(0, 1.0, 0);
            break;
        case WALL_LEFT:
            vec = MakeVector(1.0, 0, 0);
            break;
        case WALL_RIGHT:
            vec = MakeVector(-1.0, 0, 0);
            break;
        case WALL_BOTTOM:
            vec = MakeVector(0, -1.0, 0);
            break;
    }

    return(vec);
}


//
// Static screens functions
//

void DoTitleScreen()
{
    int x, y;
    int w, h;    // screen width and height   
    int bw, bh;  // bitmap width and height
        
    spriteContext tempBlock;

    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(gscreen.background_color);

    // draw row of blocks
    bw = drawGetBitmapWidth(GR_BLOCK1);     
    bh = drawGetBitmapHeight(GR_BLOCK1);

    x = (w/2) - ((bw * 10) / 2);
    y = 70;

    for (int i = 0; i < 10; i++)
    {
        CopyBlockSprite( &tempBlock, i);
        drawSprite( &tempBlock, x, y);
        x += bw;
    }

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

void DoLevelScreen(int level)
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
           
    // select correct bitmap for current level
    switch(level)
    {
        case 1:
            sprintf(filename, "%s", GR_LEVEL1);
            break;
        case 2:
            sprintf(filename, "%s", GR_LEVEL2);
            break;
        case 3:
            sprintf(filename, "%s", GR_LEVEL3);
            break;
        case 4:
            sprintf(filename, "%s", GR_LEVEL4);
            break;
    }    

    // draw single player bitmap
    bw = drawGetBitmapWidth(filename);
    bh = drawGetBitmapHeight(filename);
    x = w/2 - bw/2;
    y = h/2 - bh/2;
    drawBitmap(filename, x, y);
    
    // call this to make everything appear on the screen
    drawSwapBuffers();
}


void DoPlayScreen()
{
    // clear the background
    drawBackground(gscreen.background_color);

    // draw walls
#if 0
    drawLine(WALL_COLOR, 0,   gscreen.height,               0, 0);
    drawLine(WALL_COLOR, 0,                0, gscreen.width-1, 0);
    drawLine(WALL_COLOR, gscreen.width-1,  0, gscreen.width-1, gscreen.height);
#endif
}


void DoGameOverScreen()
{
    int x, y;
    int w, h;    // screen width and height   
    int bw, bh;  // bitmap width and height
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(gscreen.background_color);
    
    // draw victory bitmap
    bw = drawGetBitmapWidth(GR_GAMEOVER);
    bh = drawGetBitmapHeight(GR_GAMEOVER);
    x = w/2 - bw/2;
    y = h/2 - bh/2;
    drawBitmap(GR_GAMEOVER, x, y);
    
    // call this to make everything appear on the screen
    drawSwapBuffers();
}


//
// Screen functions for game play screen
//

void ScreenDrawLevel(LEVEL_S_T *level)
{
    int x, y;

    printf("ScreenDrawLevel\n");

    for (y = 0; y < level->blocks_y; y++)
    {
        for (x = 0; x < level->blocks_x; x++)
        {
            if ( level->blocks[x][y].block_state != BLOCK_STATE_EMPTY )
            {
                ScreenDrawBlock( &level->blocks[x][y] );
            }
        }
    }
}


void ScreenDrawBlock(BLOCK_S_T *block)
{
    int x, y;
    int bw, bh;  // bitmap width and height
      
    bw = block->sprite.width;     
    bh = block->sprite.height;

    x = block->center_x - bw/2;
    y = block->center_y - bh/2;

    drawSprite(&block->sprite, x, y);
}


void ScreenEraseBlock(BLOCK_S_T *block)
{
    int x, y;
    int bw, bh;  // bitmap width and height

    bw = block->sprite.width;     
    bh = block->sprite.height;

    x = block->center_x - bw/2;
    y = block->center_y - bh/2;

    drawSolidRect(gscreen.background_color, x, y, bw, bh);
}


void ScreenDrawPaddle(PADDLE_S_T *paddle)
{
    int x, y;
    int bw, bh;  // bitmap width and height
      
    bw = paddle->sprite.width;     
    bh = paddle->sprite.height;

    x = paddle->center_x - bw/2;
    y = paddle->center_y - bh/2;

    drawSprite(&paddle->sprite, x, y);
}


void ScreenErasePaddle(PADDLE_S_T *paddle)
{
    int x, y;
    int bw, bh;  // bitmap width and height

    bw = paddle->sprite.width;     
    bh = paddle->sprite.height;

    x = paddle->center_x - bw/2;
    y = paddle->center_y - bh/2;

    drawSolidRect(gscreen.background_color, x, y, bw, bh);
}


void ScreenDrawBall(BALL_S_T *ball)
{
    int x, y;
    int bw, bh;  // bitmap width and height
      
    bw = ball->sprite.width;     
    bh = ball->sprite.height;

    x = ball->center_x - bw/2;
    y = ball->center_y - bh/2;

    drawSprite(&ball->sprite, x, y);
}


void ScreenEraseBall(BALL_S_T *ball)
{
    int x, y;
    int bw, bh;  // bitmap width and height

    bw = ball->sprite.width;     
    bh = ball->sprite.height;

    x = ball->center_x - bw/2;
    y = ball->center_y - bh/2;

    drawSolidRect(gscreen.background_color, x, y, bw, bh);
}


void ScreenDrawSprite(SPRITE_S_T *sprite)
{
    int x, y;

    x = sprite->bounds.top_left.x;
    y = sprite->bounds.top_left.y;

    drawSprite(&sprite->sprite, x, y);
}


void ScreenEraseSprite(SPRITE_S_T *sprite)
{
    int x, y;
    int sw, sh;  // sprite width and height

	x = sprite->bounds.top_left.x;
    y = sprite->bounds.top_left.y;

    sw = sprite->sprite.width;     
    sh = sprite->sprite.height;

    drawSolidRect(gscreen.background_color, x, y, sw, sh);
}


int  ScreenIsSpriteCollision(SPRITE_S_T *sprite1, SPRITE_S_T *sprite2)
{
	int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1   = sprite1->bounds.top_left.x;
    left2   = sprite2->bounds.top_left.x;
    right1  = sprite1->bounds.bottom_right.x;
    right2  = sprite2->bounds.bottom_right.x;
    top1    = sprite1->bounds.top_left.y;
    top2    = sprite2->bounds.top_left.y;
    bottom1 = sprite1->bounds.bottom_right.y;
    bottom2 = sprite2->bounds.bottom_right.y;

    if (bottom1 < top2) return(0);
    if (top1 > bottom2) return(0);

    if (right1 < left2) return(0);
    if (left1 > right2) return(0);

    return(1);
}


/* end of screens.cpp */
