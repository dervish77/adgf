/*****************************************************************************
 *
 *	Breakout game logic.
 *
 *  Description:
 *  Breakout using LibSDL.
 *
 *	File:	game.cpp
 *
 *	Author: Brian Lingard
 *	Date:	11/12/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>
#include <sys/types.h>
//#include <time.h>
//#include <limits.h>

#include "game.h"
#include "screens.h"
#include "vecmath.h"
#include "random.h"


int DoGame(GAME_S_T *pGame)
{
    int state = GAME_STATE_IDLE;
    int done = 0;

    while (!done)
    {
        switch(state)
        {
            case GAME_STATE_IDLE:
                state = GameStateIdle(pGame);
                break;
                
            case GAME_STATE_TITLE:
                state = GameStateTitle(pGame);
                break;
                
            case GAME_STATE_LEVEL:
                state = GameStateLevel(pGame);
                break;
                
            case GAME_STATE_PLAY:
                state = GameStatePlay(pGame);
                break;

            case GAME_STATE_VICTORY:
                state = GameStateVictory(pGame);
                break;
                
            case GAME_STATE_QUIT:
                ScreenClose();
                done = 1;
                break;
        }
    }
    
    return(0);
}


int GameStateIdle(GAME_S_T *pGame)
{
    // open the screen for drawing
    ScreenOpen();
    
    printf("GameStateIdle\n");

    // initialize game data
    InitGame(pGame);    // must follow call to ScreenOpen() !!!

    // load sprites
    ScreenLoadBlocks();
//    ScreenLoadPaddle( &pGame->paddle );
//    ScreenLoadBall( &pGame->ball );

    return(GAME_STATE_TITLE);   
}

int GameStateTitle(GAME_S_T *pGame)
{
    int state = GAME_STATE_LEVEL;
    int done;
    int mx, my;
    char key;
    
    int id;

    UNUSED(pGame);

    printf("GameStateTitle\n");
    
    DoTitleScreen();

    id = ScreenAddTimer(TITLE_TIMEOUT, SE_TIMER1_EVENT);

    done = 0;
    while (!done)
    {
        switch( GetScreenEvent( &mx, &my, &key ) )
        {
            case SE_TIMER1_EVENT:
                done = 1;
                state = GAME_STATE_LEVEL;
                ScreenRemoveTimer( id );
                break;
            case SE_KEY_DOWN:
                switch( key )
                {           
                    case 'q':
                        done = 1;
                        state = GAME_STATE_QUIT;
                        break;
                }
                break;
            case SE_WINDOW_QUIT:
                done = 1;
                state = GAME_STATE_QUIT;
                break;
        }
    }
    return(state);   
}

int GameStateLevel(GAME_S_T *pGame)
{
    int state = GAME_STATE_PLAY;
    int done;
    int mx, my;
    char key;
    
    int id;

    printf("GameStateLevel: level %d\n", pGame->levelId);
    
    DoLevelScreen(pGame->levelId);

    id = ScreenAddTimer(LEVEL_TIMEOUT, SE_TIMER1_EVENT);

    InitPaddle(pGame, PADDLE_STATE_NORMAL);
    InitBall(pGame);

    done = 0;
    while (!done)
    {
        switch( GetScreenEvent( &mx, &my, &key ) )
        {
            case SE_TIMER1_EVENT:
                done = 1;
                state = GAME_STATE_PLAY;
                ScreenRemoveTimer( id );
                break;
            case SE_KEY_DOWN:
                switch( key )
                {           
                    case 'q':
                        done = 1;
                        state = GAME_STATE_QUIT;
                        break;
                }
                break;
            case SE_WINDOW_QUIT:
                done = 1;
                state = GAME_STATE_QUIT;
                break;
        }
    }

    if (state == GAME_STATE_PLAY)
    {    
        InitLevel(pGame);
    }

    return(state);   
}

int GameStatePlay(GAME_S_T *pGame)
{
    int state = GAME_STATE_VICTORY;
    int done;
    int mx, my;
    char key;
    
    int anim_tid;	// animation timer id

    int key_tid = 0;	// key repeat timer id
    char held_key = 0;

    UNUSED(key_tid);

    printf("GameStatePlay\n");
    
    DoPlayScreen();

    // draw initial game level
    ScreenDrawLevel( &pGame->level );
    ScreenDrawPaddle( &pGame->paddle );
    ScreenDrawBall( &pGame->ball );
    ScreenUpdate();
    
    // main game play loop
    done = 0;
    
    anim_tid = ScreenAddTimer(ANIM_TIMEOUT, SE_TIMER1_EVENT);

    while (!done)
    {
        switch( GetScreenEvent( &mx, &my, &key ) )
        {
            case SE_TIMER1_EVENT:
                MoveBall(pGame);
				if (pGame->level.blocks_count == 0)
				{
				    done = 1;
                    state = GAME_STATE_LEVEL;
                    ScreenRemoveTimer( anim_tid );
			        pGame->levelId++;
                    if (pGame->levelId > 4)
                    {
                        state = GAME_STATE_VICTORY;
                    }				
				}
				if (pGame->lives == 0)
				{
				    done = 1;
  				    state = GAME_STATE_VICTORY;
                    ScreenRemoveTimer( anim_tid );
				    printf("no more lives, you lose...\n");
				}
                break;

            case MOUSE_MOTION:
			    MovePaddle(pGame, mx, my);
                break;

            case SE_KEY_DOWN:
                switch( key )
                {           
                    case KEY_RIGHT_ARROW:
                        //MovePaddleRight(pGame);
                        //key_tid = ScreenAddTimer(KEY_TIMEOUT, SE_TIMER2_EVENT);
                        held_key = key;
                        break;
                    case KEY_LEFT_ARROW:        
                        //MovePaddleLeft(pGame);		
                        //key_tid = ScreenAddTimer(KEY_TIMEOUT, SE_TIMER2_EVENT);
                        held_key = key;
                        break;
                    case 'n':
						ScreenErasePaddle( &pGame->paddle );
					    InitPaddle( pGame, PADDLE_STATE_NORMAL );
						ScreenDrawPaddle( &pGame->paddle );
                        break;
                    case 'w':
						ScreenErasePaddle( &pGame->paddle );
                        InitPaddle( pGame, PADDLE_STATE_LONG );
						ScreenDrawPaddle( &pGame->paddle );
                        break;
					case 'q':
                        done = 1;
                        state = GAME_STATE_QUIT;
                        break;
                }
                break;
            case SE_KEY_UP:
                switch( key )
                {           
                    case KEY_RIGHT_ARROW:
                        //ScreenRemoveTimer( key_tid );
                        held_key = 0;
                        break;
                    case KEY_LEFT_ARROW:        
                        //ScreenRemoveTimer( key_tid );
                        held_key = 0;
                        break;
                }
                break;
            case SE_TIMER2_EVENT:
                switch( held_key )
                {           
                    case KEY_RIGHT_ARROW:
                        MovePaddleRight(pGame);
                        break;
                    case KEY_LEFT_ARROW:        
                        MovePaddleLeft(pGame);		
                        break;
                }
                break;

            case SE_WINDOW_QUIT:
                done = 1;
                state = GAME_STATE_QUIT;
                break;
        }
    }
    return(state);   
}

int GameStateVictory(GAME_S_T *pGame)
{
    int state = GAME_STATE_QUIT;
    int done;
    int mx, my;
    char key;

    printf("GameStateVictory\n");
    
    DoGameOverScreen();
   
    done = 0;
    while (!done)
    {
        switch( GetScreenEvent( &mx, &my, &key ) )
        {
            case SE_KEY_DOWN:
                switch( key )
                {           
                    case 'n':
                        done = 1;
                        pGame->levelId = 1;
                        state = GAME_STATE_LEVEL;
                        break;
                    case 'q':
                        done = 1;
                        state = GAME_STATE_QUIT;
                        break;
                }
                break;
            case SE_WINDOW_QUIT:
                done = 1;
                state = GAME_STATE_QUIT;
                break;
        }
    }
    return(state);   
}


void InitGame(GAME_S_T *pGame)
{
    RandomSetSeed();

    pGame->state = GAME_STATE_IDLE;
    pGame->levelId = INITIAL_LEVEL;
    pGame->lives = STARTING_LIVES;
    pGame->score = 0;

    InitPaddle(pGame, PADDLE_STATE_NORMAL);

    InitBall(pGame);

#if 0
    vectorType newdir;
    vectorType wallNormal = GetWallNormal(WALL_LEFT);
    OutputVector(stdout, &pGame->ball.direction, " original direction");
    OutputVector(stdout, &pGame->paddle.normal,  "             normal");
    newdir = VecReflectionAboutNormal( &pGame->ball.direction, &pGame->paddle.normal );
    OutputVector(stdout, &newdir, "reflected direction");
#endif
}

void InitPaddle(GAME_S_T *pGame, int state)
{
    // init paddle
    pGame->paddle.paddle_state = state;
    pGame->paddle.center_x = GetScreenWidth() / 2;
    pGame->paddle.center_y = GetScreenHeight() - 20;
    pGame->paddle.normal.x = 0;
    pGame->paddle.normal.y = -1;
    pGame->paddle.normal.z = 0;
	pGame->paddle.bounds.top_left_x = pGame->paddle.center_x - pGame->paddle.sprite.half_w;
	pGame->paddle.bounds.top_left_y = pGame->paddle.center_y - pGame->paddle.sprite.half_h;
	pGame->paddle.bounds.bottom_right_x = pGame->paddle.center_x + pGame->paddle.sprite.half_w;
	pGame->paddle.bounds.bottom_right_y = pGame->paddle.center_y + pGame->paddle.sprite.half_h;
	
	ScreenLoadPaddle( &pGame->paddle );
}

void InitBall(GAME_S_T *pGame)
{
    // init ball
    pGame->ball.ball_state = BALL_STATE_NORMAL;
    pGame->ball.collide_count = 0;
    pGame->ball.center_x = GetScreenWidth() / 2;
    pGame->ball.center_y = GetScreenHeight() / 2;
    pGame->ball.direction.x = RandomInteger(2, 4);
    pGame->ball.direction.y = -1 * RandomInteger(3, 4);
    pGame->ball.direction.z = 0;
	
    ScreenLoadBall( &pGame->ball );
}


void InitLevel(GAME_S_T *pGame)
{
    int x, y;       // grid cell x,y
    
    int tlx, tly;   // top left x,y
    int cx, cy;     // center coord x,y
    
    pGame->level.level_id = pGame->levelId;
	
	pGame->level.blocks_count = 0;    // when this is 0 then level is finished

    pGame->level.blocks_x = BLOCKS_X;
    pGame->level.blocks_y = BLOCKS_Y;

    printf("InitLevel: blocks x,y %d,%d\n", pGame->level.blocks_x, pGame->level.blocks_y);

    pGame->level.block_width = GetBlockWidth();
    pGame->level.block_height = GetBlockHeight();

    printf("InitLevel: blocks w,h %d,%d\n", pGame->level.block_width, pGame->level.block_height);

    tlx = (GetScreenWidth()/2) - ((pGame->level.block_width * pGame->level.blocks_x) / 2);
    tly = TOP_ROW_TLY;

    cx = tlx + (pGame->level.block_width / 2);
    cy = tly + (pGame->level.block_height / 2);

    for (y = 0; y < pGame->level.blocks_y; y++)
    {
        printf("InitLevel: tlx,tly %d,%d\n", tlx, tly);
        printf("InitLevel: cx,cy %d,%d\n", cx, cy);
        for (x = 0; x < pGame->level.blocks_x; x++)
        {
            pGame->level.blocks[x][y].block_state = BLOCK_STATE_BREAKABLE;
            pGame->level.blocks[x][y].block_type  = y + 1;
            pGame->level.blocks_count++;
						
            pGame->level.blocks[x][y].center_x = cx;
            pGame->level.blocks[x][y].center_y = cy;

            pGame->level.blocks[x][y].normal.x = 0;
            pGame->level.blocks[x][y].normal.y = 1;
            pGame->level.blocks[x][y].normal.z = 0;
            
            pGame->level.blocks[x][y].bounds.top_left_x = tlx;
            pGame->level.blocks[x][y].bounds.top_left_y = tly;
            
            pGame->level.blocks[x][y].bounds.bottom_right_x = tlx + pGame->level.block_width;
            pGame->level.blocks[x][y].bounds.bottom_right_y = tly + pGame->level.block_height;

            CopyBlockSprite( &pGame->level.blocks[x][y].sprite, y );

            tlx += pGame->level.block_width;   
            cx += pGame->level.block_width;
        }
        tlx = (GetScreenWidth()/2) - ((pGame->level.block_width * pGame->level.blocks_x) / 2);    
        tly += pGame->level.block_height;
        cx = tlx + (pGame->level.block_width / 2);
        cy += pGame->level.block_height;
    }
}


int IsBlockEmpty(GAME_S_T *pGame, int x, int y)
{
    int state = 0;

    if (pGame->level.blocks[x][y].block_state == BLOCK_STATE_EMPTY)
    {
        state = 1;
    }

    return(state);
}


int IsWithinBlockBounds(GAME_S_T *pGame, int x, int y, int mx, int my)
{
    int state = 0;
    
    state = IsWithinBounds( &pGame->level.blocks[x][y].bounds, mx, my );

    return(state);
}


int IsWithinBounds(BOUNDS_S_T *bounds, int mx, int my)
{
    int state = 0;
    
    int tlx = bounds->top_left_x;
    int tly = bounds->top_left_y;
    int brx = bounds->bottom_right_x;
    int bry = bounds->bottom_right_y;
    
    if ( (tlx < mx && mx < brx) && (tly < my && my < bry) )
    {
        state = 1;
    }
    
    return(state);
}


void MoveBall(GAME_S_T *pGame)
{
    vectorType oldpos;
    vectorType newpos;

    // erase ball
    ScreenEraseBall( &pGame->ball );

    // move ball
    oldpos.x = pGame->ball.center_x;
    oldpos.y = pGame->ball.center_y;
    oldpos.z = 0;

    newpos = VecAdd( &oldpos, &pGame->ball.direction );

    UpdateBallPosition( pGame, newpos );

	// handle collision with block
	int cx, cy;
	if ( IsBallCollideWithABlock(pGame, &cx, &cy) )
	{
	    printf("ball collided with block %d,%d\n", cx, cy);
		
		vectorType newDir = VecReflectionAboutNormal( &pGame->ball.direction, &pGame->level.blocks[cx][cy].normal );
        UpdateBallDirection( pGame, newDir );
		
		newpos = VecAdd( &oldpos, &pGame->ball.direction );
        UpdateBallPosition( pGame, newpos );
		
		if ( pGame->level.blocks[cx][cy].block_state == BLOCK_STATE_BREAKABLE )
		{
		    ScreenEraseBlock( &pGame->level.blocks[cx][cy] );
		    pGame->level.blocks[cx][cy].block_state = BLOCK_STATE_EMPTY;
			pGame->level.blocks_count--;
		}
	}
	
	// handle collision with paddle
	if ( IsBallCollideWithPaddle(pGame) )
	{
	    printf("ball collided with paddle\n");
		
		vectorType newDir = VecReflectionAboutNormal( &pGame->ball.direction, &pGame->paddle.normal );
        UpdateBallDirection( pGame, newDir );
		
		newpos = VecAdd( &oldpos, &pGame->ball.direction );
        UpdateBallPosition( pGame, newpos );
	}
	
	// handle collision with wall
    int whichWall;
    if ( IsBallCollideWithWall(pGame, &whichWall) )
    {
        printf("ball collided with wall %d\n", whichWall);

        vectorType wallNorm = GetWallNormal( whichWall );
        vectorType newDir = VecReflectionAboutNormal( &pGame->ball.direction, &wallNorm );
        UpdateBallDirection( pGame, newDir );

        if (pGame->ball.collide_count > COLLIDE_COUNT_TRIGGER)
        {
            pGame->ball.collide_count = 0;
			if ( VecMagnitude( &pGame->ball.direction ) < COLLIDE_MAX_SPEED )
			{
                newDir = VecScale( &pGame->ball.direction, COLLIDE_SPEED_UP );
                UpdateBallDirection( pGame, newDir );
			}
        }

        newpos = VecAdd( &oldpos, &pGame->ball.direction );
        UpdateBallPosition( pGame, newpos );
		
		if (whichWall == WALL_BOTTOM)
		{
		    pGame->lives--;
			if (pGame->lives > 0)
			{
			    printf("hit bottom but still alive (%d)\n", pGame->lives);
			    InitBall(pGame);
			}	
		}
    }

    // draw ball
	if (pGame->lives > 0)
	{
        ScreenDrawBall( &pGame->ball );
	}
    ScreenUpdate();
}


void UpdateBallPosition(GAME_S_T *pGame, vectorType newpos)
{
    // get half of width and height
    int half_w = pGame->ball.sprite.width / 2;
    int half_h = pGame->ball.sprite.height / 2;

    // set new center
    pGame->ball.center_x = (int) newpos.x;
    pGame->ball.center_y = (int) newpos.y;

    // set new bounds
    pGame->ball.bounds.top_left_x = pGame->ball.center_x - half_w;
    pGame->ball.bounds.top_left_y = pGame->ball.center_y - half_h;

    pGame->ball.bounds.bottom_right_x = pGame->ball.center_x + half_w;
    pGame->ball.bounds.bottom_right_y = pGame->ball.center_y + half_h;
}


void UpdateBallDirection(GAME_S_T *pGame, vectorType newdir)
{
    CopyVector( &newdir, &pGame->ball.direction );
}


void MovePaddleRight(GAME_S_T *pGame)
{
    int step = 10;

    // erase paddle
    ScreenErasePaddle( &pGame->paddle );

    // move paddle
    int pw = GetPaddleWidth( &pGame->paddle );
    if ( pGame->paddle.center_x <= (GetScreenWidth() - pw/2 - step) )
    {
        pGame->paddle.center_x += step;

		pGame->paddle.bounds.top_left_x = pGame->paddle.center_x - pGame->paddle.sprite.half_w;
	    pGame->paddle.bounds.bottom_right_x = pGame->paddle.center_x + pGame->paddle.sprite.half_w;
	}

    // draw paddle
    ScreenDrawPaddle( &pGame->paddle );
    ScreenUpdate();
}


void MovePaddleLeft(GAME_S_T *pGame)
{
    int step = 10;

    // erase paddle
    ScreenErasePaddle( &pGame->paddle );

    // move paddle
    int pw = GetPaddleWidth( &pGame->paddle );
    if ( pGame->paddle.center_x >= (pw/2 + step) )
    {
        pGame->paddle.center_x -= step;
		
		pGame->paddle.bounds.top_left_x = pGame->paddle.center_x - pGame->paddle.sprite.half_w;
	    pGame->paddle.bounds.bottom_right_x = pGame->paddle.center_x + pGame->paddle.sprite.half_w;
	}

    // draw paddle
    ScreenDrawPaddle( &pGame->paddle );
    ScreenUpdate();
}


void MovePaddle(GAME_S_T *pGame, int x, int y)
{
    // erase paddle
    ScreenErasePaddle( &pGame->paddle );

    // move paddle
    int pw = GetPaddleWidth( &pGame->paddle );
    if ( x >= pw/2 && x <= (GetScreenWidth() - pw/2) )
    {
        pGame->paddle.center_x = x;
		
		pGame->paddle.bounds.top_left_x = pGame->paddle.center_x - pGame->paddle.sprite.half_w;
	    pGame->paddle.bounds.bottom_right_x = pGame->paddle.center_x + pGame->paddle.sprite.half_w;
	}

    // draw paddle
    ScreenDrawPaddle( &pGame->paddle );
    ScreenUpdate();
}


int IsBallCollideWithWall(GAME_S_T *pGame, int *whichWall)
{
    int collided = 0;
    *whichWall = WALL_NONE;

    // check left wall
    if (pGame->ball.bounds.top_left_x <= 0)
    {
        collided = 1;
        *whichWall = WALL_LEFT;
    }

    // check right wall
    if (pGame->ball.bounds.bottom_right_x >= GetScreenWidth())
    {
        collided = 1;
        *whichWall = WALL_RIGHT;
    }

    // check top wall
    if (pGame->ball.bounds.top_left_y <= 0)
    {
        collided = 1;
        *whichWall = WALL_TOP;
    }

    // check bottom wall
    if (pGame->ball.bounds.bottom_right_y >= GetScreenHeight())
    {
        collided = 1;
        *whichWall = WALL_BOTTOM;
    }

    if (collided)
    {
        pGame->ball.collide_count++;
    }

    return(collided);
}


int IsBallCollideWithPaddle(GAME_S_T *pGame)
{
	int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1   = pGame->ball.bounds.top_left_x;
    left2   = pGame->paddle.bounds.top_left_x;
    right1  = pGame->ball.bounds.bottom_right_x;
    right2  = pGame->paddle.bounds.bottom_right_x;
    top1    = pGame->ball.bounds.top_left_y;
    top2    = pGame->paddle.bounds.top_left_y;
    bottom1 = pGame->ball.bounds.bottom_right_y;
    bottom2 = pGame->paddle.bounds.bottom_right_y;

    if (bottom1 < top2) return(0);
    if (top1 > bottom2) return(0);

    if (right1 < left2) return(0);
    if (left1 > right2) return(0);

    return(1);
}


int IsBallCollideWithABlock(GAME_S_T *pGame, int *cx, int *cy)
{
    int collided = 0;
    int x, y;

    for (y = 0; y < pGame->level.blocks_y; y++)
    {
        for (x = 0; x < pGame->level.blocks_x; x++)
        {
		    if ( pGame->level.blocks[x][y].block_state != BLOCK_STATE_EMPTY )
			{
		        if ( IsBallCollideWithThisBlock( pGame, x, y) )
			    {
			        collided = 1;
				    *cx = x;
				    *cy = y;
	                return(collided);
			    }
			}
		}
	}
	
	return(collided);
}


int IsBallCollideWithThisBlock(GAME_S_T *pGame, int cx, int cy)
{
	int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1   = pGame->ball.bounds.top_left_x;
    left2   = pGame->level.blocks[cx][cy].bounds.top_left_x;
    right1  = pGame->ball.bounds.bottom_right_x;
    right2  = pGame->level.blocks[cx][cy].bounds.bottom_right_x;
    top1    = pGame->ball.bounds.top_left_y;
    top2    = pGame->level.blocks[cx][cy].bounds.top_left_y;
    bottom1 = pGame->ball.bounds.bottom_right_y;
    bottom2 = pGame->level.blocks[cx][cy].bounds.bottom_right_y;

    if (bottom1 < top2) return(0);
    if (top1 > bottom2) return(0);

    if (right1 < left2) return(0);
    if (left1 > right2) return(0);

    return(1);
}


/* end of game.cpp */
