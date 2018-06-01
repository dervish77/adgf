/*****************************************************************************
 *
 *	Life UI game logic.
 *
 *  Description:
 *  Life UI using LibSDL.
 *
 *	File:	game.cpp
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "game.h"
#include "screens.h"
#include "random.h"


int DoGame(GAME_S_T *pGame, int play_mode)
{
    int state = GAME_STATE_IDLE;
    int done = 0;

    while (!done)
    {
        switch(state)
        {
            case GAME_STATE_IDLE:
                state = GameStateIdle(pGame, play_mode);
                break;
                
            case GAME_STATE_TITLE:
                state = GameStateTitle(pGame);
                break;
                
            case GAME_STATE_PLAY:
                state = GameStatePlay(pGame);
                break;
                
            case GAME_STATE_QUIT:
                state = GameStateQuit(pGame);
                done = 1;
                break;
        }
    }
    
    return(0);
}


int GameStateIdle(GAME_S_T *pGame, int mode)
{
    printf("GameStateIdle\n");

    // open the screen for drawing
    ScreenOpen();
    
    // initialize game data
    InitGame(pGame);    // must follow call to ScreenOpen() !!!
    SetPlayMode( pGame, mode );

    return(GAME_STATE_TITLE);   
}

int GameStateTitle(GAME_S_T *pGame)
{
    int state = GAME_STATE_PLAY;
    int done;
    int mx, my;
    char key;
    
    int id;

    printf("GameStateTitle\n");

    // show title screen for a couple of seconds
    DoTitleScreen();

    // timeout for title screen
    id = ScreenAddTimer(3000, SE_TIMER1_EVENT);

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
                        ScreenRemoveTimer( id );
                        break;
                    default:
                        done = 1;
                        state = GAME_STATE_PLAY;
                        ScreenRemoveTimer( id );
                        break;
                }
                break;
            case SE_WINDOW_QUIT:
                done = 1;
                state = GAME_STATE_QUIT;
                ScreenRemoveTimer( id );
                break;
	        default:
                break;
        }
    }
    return(state);   
}


int GameStatePlay(GAME_S_T *pGame)
{
    int state = GAME_STATE_QUIT;
    int done;
    int mx, my;
    char key;
    int x, y;

    int id = 0;
    int timer_running = 0;
    int mouse_down = 0;
    
    printf("GameStatePlay\n");

    // initialize the game board
    InitBoard(pGame);

    // draw initial game board
    DoPlayScreen();

    // main game play loop
    done = 0;
    while (!done)
    {
        switch( GetScreenEvent( &mx, &my, &key ) )
        {
            case SE_TIMER1_EVENT:
                GameTick(pGame);
                printf("Timer tick %d\n", pGame->ticks);
                RedrawBoard(pGame);
                ScreenUpdate();
                break;

            case SE_MOUSE_LEFT_DOWN:
                mouse_down = 1;
			    
                // determine which grid cell was clicked
                x = mx / pGame->grid_width;
                y = my / pGame->grid_height;
                if ( IsWithinGridBounds( pGame, x, y, mx, my ) )
                {
                    // if grid cell is empty, make alive
                    if ( IsGridEmpty( pGame, x, y ) )
                    {
                        UpdateBoard(pGame, x, y, PIECE_TYPE_ALIVE);
                        ScreenUpdate();      
                    } 
                    else // else not empty, make dead
                    {
                        UpdateBoard(pGame, x, y, PIECE_TYPE_DEAD);
                        ScreenUpdate();     
                    }
                } // end if within grid cell
                break;

	        case SE_MOUSE_LEFT_UP:
                mouse_down = 0;
                break;

	        case SE_MOUSE_MOTION:
                if (mouse_down)
                {
                    // determine which grid cell was clicked
                    x = mx / pGame->grid_width;
                    y = my / pGame->grid_height;
                    if ( IsWithinGridBounds( pGame, x, y, mx, my ) )
                    {
                        UpdateBoard(pGame, x, y, PIECE_TYPE_ALIVE);
                        ScreenUpdate();      
                    } 
                }
                break;

            case SE_KEY_DOWN:
                switch( key )
                {    
                    case 'h':
                        printf("Help --- short cut keys:\n");
                        printf("  s - start cell sim\n");
                        printf("  x - stop cell sim\n");
                        printf("  c - clear cell sim\n");			
                        printf("  r - random pattern\n");			
                        printf("  p - cycle through default patterns\n");	
                        printf("  f - toggle tick speed fast/slow\n");
                        printf("  q - quit\n");			
                        break;	
                    case 's':
                        printf("Start\n");
                        if ( !timer_running )
                        {
                            pGame->ticks = 0;
                            id = ScreenAddTimer(pGame->tick_speed, SE_TIMER1_EVENT);
                            timer_running = 1;
                        }
                        break;
                    case 'x':
                        printf("Stop\n");
                        if ( timer_running )
                        {
                            ScreenRemoveTimer( id );
                            timer_running = 0;
                        }
                        break;
                    case 'c':
                        printf("Clear\n");
                        if ( timer_running )
                        {
                            ScreenRemoveTimer( id );
                            timer_running = 0;
                        }
                        pGame->pattern = PATTERN_NONE;
                        InitBoard(pGame);
                        ScreenDrawGrid();
                        ScreenUpdate();
                        break;
                    case 'r':
                        printf("Random\n");
                        if ( timer_running )
                        {
                            ScreenRemoveTimer( id );
                            timer_running = 0;
                        }
                        RandomBoard(pGame);
                        RedrawBoard(pGame);
                        ScreenUpdate();
                        break;
                    case 'p':
                        printf("Pattern Toggle\n");
                        if ( timer_running )
                        {
                            ScreenRemoveTimer( id );
                            timer_running = 0;
                        }
                        GamePattern(pGame);
                        RedrawBoard(pGame);
                        ScreenUpdate();
                        break;
                    case 'f':
                        printf("Fast/Slow, ");
                        if (pGame->tick_speed == TICK_SPEED_SLOW)
                        {
                             pGame->tick_speed = TICK_SPEED_FAST;
                        }
                        else
                        {
                             pGame->tick_speed = TICK_SPEED_SLOW;
                        }
                        printf("speed = %d\n", pGame->tick_speed);                	
                        if ( timer_running )
                        {
                            // restart timer at new speed
                            ScreenRemoveTimer( id );
                            id = ScreenAddTimer(pGame->tick_speed, SE_TIMER1_EVENT);
                        }
                        break;
                    case 'q':
                        printf("Quit\n");
                        done = 1;
                        state = GAME_STATE_QUIT;
                        ScreenRemoveTimer( id );
                        timer_running = 0;
                        break;
                }
                break;

            case SE_WINDOW_QUIT:
                done = 1;
                state = GAME_STATE_QUIT;
                ScreenRemoveTimer( id );
                break;

            default:
                break;
        }
    }
    return(state);   
}


int GameStateQuit(GAME_S_T *pGame)
{
    printf("GameStateQuit\n");
               
    ScreenClose();

    return(GAME_STATE_QUIT);
}


void InitGame(GAME_S_T *pGame)
{
    RandomSetSeed();
 
    pGame->state = GAME_STATE_IDLE;
    pGame->play_mode = MODE_ONE_PLAYER;
    pGame->player1_piece_type = PIECE_TYPE_ALIVE;
    pGame->player2_piece_type = PIECE_TYPE_DEAD;
    pGame->current_player = PLAYER_1;
    pGame->used_grid_count = 0;
    pGame->grid_size_x = GRID_SIZE_X;
    pGame->grid_size_y = GRID_SIZE_Y;
    pGame->grid_width = GetGridWidth();
    pGame->grid_height = GetGridHeight();
    pGame->tick_speed = TICK_SPEED_SLOW;
    pGame->ticks = 0;
    pGame->pattern = PATTERN_NONE;
}


void SetPlayMode(GAME_S_T *pGame, int mode)
{
    pGame->play_mode = mode;  
}


void InitBoard(GAME_S_T *pGame)
{
    int x, y;       // grid cell x,y
    
    int tlx, tly;   // top left x,y
    int cx, cy;     // center coord x,y
    
    tlx = 0;
    tly = 0;
    
    cx = pGame->grid_width / 2;
    cy = pGame->grid_height / 2;
    
    for (y = 0; y < pGame->grid_size_y; y++)
    {
        for (x = 0; x < pGame->grid_size_x; x++)
        {
            pGame->board[x][y].piece_type = PIECE_TYPE_EMPTY;
            pGame->board[x][y].center_x = cx;
            pGame->board[x][y].center_y = cy;
            pGame->board[x][y].bounds.top_left_x = tlx;
            pGame->board[x][y].bounds.top_left_y = tly;
            pGame->board[x][y].bounds.bottom_right_x = tlx + pGame->grid_width;
            pGame->board[x][y].bounds.bottom_right_y = tly + pGame->grid_height;
	               
            pGame->prev_board[x][y].piece_type = PIECE_TYPE_EMPTY;
            pGame->prev_board[x][y].center_x = cx;
            pGame->prev_board[x][y].center_y = cy;
            pGame->prev_board[x][y].bounds.top_left_x = tlx;
            pGame->prev_board[x][y].bounds.top_left_y = tly;
            pGame->prev_board[x][y].bounds.bottom_right_x = tlx + pGame->grid_width;
            pGame->prev_board[x][y].bounds.bottom_right_y = tly + pGame->grid_height;

            tlx += pGame->grid_width;   
            cx += pGame->grid_width;
        }
        tlx = 0;    
        tly += pGame->grid_height;
        cx = pGame->grid_width / 2;
        cy += pGame->grid_height;
    }
}


void ClearBoard(GAME_S_T *pGame)
{
    int x, y;       // grid cell x,y
    
    for (y = 0; y < pGame->grid_size_y; y++)
    {
        for (x = 0; x < pGame->grid_size_x; x++)
        {
            pGame->board[x][y].piece_type = PIECE_TYPE_EMPTY;
        }
    }
}


void RandomBoard(GAME_S_T *pGame)
{
    int x, y;       // grid cell x,y

    ClearBoard(pGame);

    for (y = 0; y < pGame->grid_size_y; y++)
    {
        for (x = 0; x < pGame->grid_size_x; x++)
        {
            if ( RandomAlive( x, y ) )
            {
                pGame->board[x][y].piece_type = PIECE_TYPE_ALIVE;
            }
        }
    }
}


int RandomAlive(int x, int y)
{
    int alive = 0;
   
    int i = RandomInteger( 1, 100 );

    if ( i < 21 )
    {
        alive = 1;
    }

    return(alive);
}


int IsGridEmpty(GAME_S_T *pGame, int x, int y)
{
    int state = 0;
        
    if (pGame->board[x][y].piece_type == PIECE_TYPE_EMPTY)
    {
        state = 1;
    }
    
    return(state);
}


int IsWithinGridBounds(GAME_S_T *pGame, int x, int y, int mx, int my)
{
    int state = 0;
    
    int tlx = pGame->board[x][y].bounds.top_left_x;
    int tly = pGame->board[x][y].bounds.top_left_y;
    int brx = pGame->board[x][y].bounds.bottom_right_x;
    int bry = pGame->board[x][y].bounds.bottom_right_y;
    
    if ( (tlx < mx && mx < brx) && (tly < my && my < bry) )
    {
        state = 1;
    }
    
    return(state);
}


void UpdateBoard(GAME_S_T *pGame, int x, int y, int piece)
{
    pGame->used_grid_count++;
    pGame->board[x][y].piece_type = piece;   

    ScreenDrawCell( piece, pGame->board[x][y].center_x, pGame->board[x][y].center_y );
}


void RedrawBoard(GAME_S_T *pGame)
{
    int x, y;
     
    ScreenDrawGrid();
       
    for (y = 0; y < pGame->grid_size_y; y++)
    {
        for (x = 0; x < pGame->grid_size_x; x++)
        {
            ScreenDrawCell( pGame->board[x][y].piece_type, 
                    pGame->board[x][y].center_x, 
                    pGame->board[x][y].center_y );
        }
    }
}


void GameTick(GAME_S_T *pGame)
{
    int x, y;
    
    // save current state of board
    CopyBoardToPrevious(pGame);    
    ClearBoard(pGame);

    // apply Conway's rules
    for (y = 0; y < pGame->grid_size_y; y++)
    {
        for (x = 0; x < pGame->grid_size_x; x++)
        {
            if ( IsCellAlive(pGame, x, y) )
            {
                pGame->board[x][y].piece_type = PIECE_TYPE_ALIVE;
            }
        }
    }

    pGame->ticks++;
}


void CopyBoardToPrevious(GAME_S_T *pGame)
{
    int x, y;

    for (y = 0; y < pGame->grid_size_y; y++)
    {
        for (x = 0; x < pGame->grid_size_x; x++)
        {
            pGame->prev_board[x][y].piece_type = pGame->board[x][y].piece_type;   
        }
    }
}


int IsCellAlive(GAME_S_T *pGame, int x, int y)
{
    int alive = 0;
    int count;
    
    //
    // apply Conway's rules
    // 
    
    count = CountNeighbors(pGame, x, y);

    // if previous cell was alive, check if died
    if ( pGame->prev_board[x][y].piece_type == PIECE_TYPE_ALIVE )
    {
        if ( count == 2 || count == 3 )
        {
            alive = 1;
        }
    }
    else // else previous cell was dead, check if birth
    {
        if ( count == 3 )
        {
            alive = 1;
        }
    }

    return(alive);
}


int CountNeighbors(GAME_S_T *pGame, int x, int y)
{
    int count = 0;

    // if top left corner
    if (y == 0 && x == 0)
    {
        if ( pGame->prev_board[x][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
    }
    // else if top right corner
    else if (y == 0 && x == pGame->grid_size_x-1)
    {
        if ( pGame->prev_board[x-1][y].piece_type   == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x-1][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
    }
    // else if bottom left corner
    else if (y == pGame->grid_size_y-1 && x == 0)
    {
        if ( pGame->prev_board[x][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y].piece_type == PIECE_TYPE_ALIVE ) count++;
    }
    // else if bottom right corner
    else if (y == pGame->grid_size_y-1 && x == pGame->grid_size_x-1)
    {
        if ( pGame->prev_board[x-1][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x-1][y].piece_type   == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
    }
    // else if top edge
    else if (y == 0)
    {
        if ( pGame->prev_board[x-1][y].piece_type   == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x-1][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
    }
    // else if bottom edge
    else if (y == pGame->grid_size_y-1)
    {
        if ( pGame->prev_board[x-1][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x-1][y].piece_type   == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y].piece_type == PIECE_TYPE_ALIVE ) count++;
    }
    // else if left edge
    else if (x == 0)
    {
        if ( pGame->prev_board[x][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
    }
    // else if right edge
    else if (x == pGame->grid_size_x-1)
    {
        if ( pGame->prev_board[x][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;	    
    }
    // else middle
    else
    {
        if ( pGame->prev_board[x-1][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x-1][y].piece_type   == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x-1][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y-1].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y].piece_type == PIECE_TYPE_ALIVE ) count++;
        if ( pGame->prev_board[x+1][y+1].piece_type == PIECE_TYPE_ALIVE ) count++;
    }

    return(count);
}


void GamePattern(GAME_S_T *pGame)
{
    pGame->pattern++;
    if (pGame->pattern > PATTERN_MAX)
    {
        pGame->pattern = PATTERN_NONE;
    }

    printf("  pattern %d\n", pGame->pattern);
    
    ClearBoard(pGame);

    switch( pGame->pattern )
    {
        case PATTERN_SPIN:
            pGame->board[11][10].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[11][11].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[11][12].piece_type = PIECE_TYPE_ALIVE;
            break;
        case PATTERN_BEACON:
            pGame->board[10][10].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[11][10].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[10][11].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[13][12].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[12][13].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[13][13].piece_type = PIECE_TYPE_ALIVE;
            break;
        case PATTERN_GLIDER:
            pGame->board[1][0].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[2][1].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[0][2].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[1][2].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[2][2].piece_type = PIECE_TYPE_ALIVE;
            break;
        case PATTERN_LWSS:
            pGame->board[0][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[3][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[4][21].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[0][22].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[4][22].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[1][23].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[2][23].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[3][23].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[4][23].piece_type = PIECE_TYPE_ALIVE;
            break;
        case PATTERN_PULSAR:
            pGame->board[11][10].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[11][11].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[11][13].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[11][14].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[10][11].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[10][12].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[10][13].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[12][11].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[12][12].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[12][13].piece_type = PIECE_TYPE_ALIVE;
            break;
        case PATTERN_LINE:
            pGame->board[10][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[11][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[12][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[13][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[14][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[15][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[16][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[17][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[18][20].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[19][20].piece_type = PIECE_TYPE_ALIVE;
            break;
        case PATTERN_QUEENBEE:
            pGame->board[20][30].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[21][30].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[22][31].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[23][32].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[23][33].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[23][34].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[22][35].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[21][36].piece_type = PIECE_TYPE_ALIVE;
            pGame->board[20][36].piece_type = PIECE_TYPE_ALIVE;
            break;
        default:
            break;
    }
}


/* end of game.c */
