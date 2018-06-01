/*****************************************************************************
 *
 *	SicDacLoe game logic.
 *
 *  Description:
 *  Tic Tac Toe using LibSDL.
 *
 *	File:	game.c
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
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
#include "random.h"


int DoGame(GAME_S_T *pGame, int play_mode, int comp_skill)
{
    int state = GAME_STATE_IDLE;
    int done = 0;

    while (!done)
    {
        switch(state)
        {
            case GAME_STATE_IDLE:
                state = GameStateIdle(pGame, play_mode, comp_skill);
                break;
                
            case GAME_STATE_TITLE:
                state = GameStateTitle(pGame);
                break;
                
            case GAME_STATE_PLAYERS:
                state = GameStatePlayers(pGame);
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


int GameStateIdle(GAME_S_T *pGame, int mode, int skill)
{
    // open the screen for drawing
    ScreenOpen();
    
    // initialize game data
    InitGame(pGame);    // must follow call to ScreenOpen() !!!
    SetPlayMode( pGame, mode );
    SetPlaySkill( pGame, skill );

    return(GAME_STATE_TITLE);   
}

int GameStateTitle(GAME_S_T *pGame)
{
    int state;
    int done;
    int mx, my;
    char key;
    
    int id;
    
    // show title screen for a couple of seconds
    DoTitleScreen();
    id = ScreenAddTimer(2000, SE_TIMER1_EVENT);

    done = 0;
    while (!done)
    {
        switch( GetScreenEvent( &mx, &my, &key ) )
        {
            case SE_TIMER1_EVENT:
                done = 1;
                if (pGame->play_mode == MODE_UNKNOWN)
                {
                    state = GAME_STATE_PLAYERS;
                }
                else
                {
                    state = GAME_STATE_PLAY;
                }
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

int GameStatePlayers(GAME_S_T *pGame)
{
    int state = GAME_STATE_PLAY;
    int done;
    int mx, my;
    char key;
    
    int mode = MODE_UNKNOWN;
    
    // show player mode selection screen
    // and then determine which player mode the user has selected
    if (pGame->play_mode == MODE_UNKNOWN)
    {
        BOUNDS_S_T p1bounds;
        BOUNDS_S_T p2bounds;
        DoPlayerScreen( &p1bounds, &p2bounds );
        done = 0;
        while (!done)
        {
            switch( GetScreenEvent( &mx, &my, &key ) )
            {
                case SE_MOUSE_LEFT_DOWN:
                    if ( IsWithinPlayerBounds( &p1bounds, mx, my ) )
                    {
                        printf("Single Player Selected\n");
                        mode = MODE_ONE_PLAYER;
                        done = 1;
                        state = GAME_STATE_PLAY;
                    }
                    if ( IsWithinPlayerBounds( &p2bounds, mx, my ) )
                    {
                        printf("Two Players Selected\n");
                        mode = MODE_TWO_PLAYER;
                        done = 1;
                        state = GAME_STATE_PLAY;
                    }
                    break;
                case SE_KEY_DOWN:
                    switch( key )
                    {
                        case '1':
                            mode = MODE_ONE_PLAYER;
                            done = 1;
                            state = GAME_STATE_PLAY;
                            break;
                        case '2':
                            mode = MODE_TWO_PLAYER;
                            done = 1;
                            state = GAME_STATE_PLAY;
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
        SetPlayMode( pGame, mode );
    }
    return(state);   
}

int GameStatePlay(GAME_S_T *pGame)
{
    int state = GAME_STATE_VICTORY;
    int done;
    int mx, my;
    char key;
    
    int x, y;
    
    // initialize the game board
    InitBoard(pGame);

    // draw initial game board
    ScreenDrawGrid();
    ScreenUpdate();
    
    // main game play loop
    done = 0;
    while (!done)
    {
        switch( GetScreenEvent( &mx, &my, &key ) )
        {
            case SE_MOUSE_LEFT_DOWN:
                for (y = 0; y < pGame->grid_size_y; y++)
                {
                    for (x = 0; x < pGame->grid_size_x; x++)
                    {
                        // determine which grid cell was clicked
                        if ( IsWithinGridBounds( pGame, x, y, mx, my ) )
                        {
                            // determine if grid cell is empty
                            if ( IsGridEmpty( pGame, x, y ) )
                            {
                                
                                // handle single player game action
                                if (pGame->play_mode == MODE_ONE_PLAYER)
                                {
                                    // update with human player's move
                                    UpdateBoard(pGame, x, y, pGame->player1_piece_type);
                                    pGame->current_player = PLAYER_1;
                                    ScreenUpdate();

                                    // scan the board to see if there's a winner
                                    if ( CountBoard(pGame) || (pGame->used_grid_count == 9) )
                                    {
                                        done = 1;
                                        state = GAME_STATE_VICTORY;
                                        ScreenPause( 500 );  // pause to let player see board update
                                    }
                                    
                                    if (!done)
                                    {
                                        // let the computer take his move
                                        ComputerMove(pGame);

                                        // scan the board to see if there's a winner
                                        if ( CountBoard(pGame) || (pGame->used_grid_count == 9) )
                                        {
                                            done = 1;
                                            state = GAME_STATE_VICTORY;
                                            ScreenPause( 500 );  // pause to let player see board update
                                        }
                                    }
                                } // end if one player

                                // handle two player game action
                                if (pGame->play_mode == MODE_TWO_PLAYER)
                                {
                                    // update with current player's move
                                    if (pGame->current_player == PLAYER_1)
                                    {
                                        UpdateBoard(pGame, x, y, pGame->player1_piece_type);
                                        pGame->current_player = PLAYER_2;
                                        ScreenUpdate();
                                    }
                                    else if (pGame->current_player == PLAYER_2)
                                    {
                                        UpdateBoard(pGame, x, y, pGame->player2_piece_type);
                                        pGame->current_player = PLAYER_1;
                                        ScreenUpdate();
                                    }

                                    // scan the board to see if there's a winner
                                    if ( CountBoard(pGame) || (pGame->used_grid_count == 9) )
                                    {
                                        done = 1;
                                        state = GAME_STATE_VICTORY;
                                        ScreenPause( 500 );  // pause to let player see board update
                                    }
                                } // end if two player
                                                                
                            } // end if empty
                        } // end if within grid cell
                    } // end for x
                } // end for y
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

int GameStateVictory(GAME_S_T *pGame)
{
    int state;
    int done;
    int mx, my;
    char key;
    
    DoVictoryScreen( pGame->winner );
    
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
                        pGame->used_grid_count = 0;
                        pGame->winner = PLAYER_NONE;
                        state = GAME_STATE_PLAY;
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

    pGame->play_mode = MODE_UNKNOWN;
    pGame->player1_piece_type = PIECE_TYPE_X;
    pGame->player2_piece_type = PIECE_TYPE_O;
    pGame->current_player = PLAYER_1;
    pGame->used_grid_count = 0;
    pGame->winner = PLAYER_NONE;
    pGame->grid_size_x = GRID_SIZE_X;
    pGame->grid_size_y = GRID_SIZE_Y;
    pGame->grid_width = GetGridWidth();
    pGame->grid_height = GetGridHeight();
    pGame->skill = SKILL_BEST;
}


void SetPlayMode(GAME_S_T *pGame, int mode)
{
    pGame->play_mode = mode;  
}


void SetPlaySkill(GAME_S_T *pGame, int skill)
{
    pGame->skill = skill;  
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

            tlx += pGame->grid_width;   
            cx += pGame->grid_width;
        }
        tlx = 0;    
        tly += pGame->grid_height;
        cx = pGame->grid_width / 2;
        cy += pGame->grid_height;
    }
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


int IsWithinPlayerBounds(BOUNDS_S_T *bounds, int mx, int my)
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


void UpdateBoard(GAME_S_T *pGame, int x, int y, int piece)
{
    pGame->used_grid_count++;
//    printf("UpdateBoard: x,y / piece = %d,%d / %d\n", x, y, piece);
    pGame->board[x][y].piece_type = piece;   
//    printf("UpdateBoard: cx,cy = %d,%d\n", pGame->board[x][y].center_x, pGame->board[x][y].center_y);
    ScreenDrawPiece( piece, pGame->board[x][y].center_x, pGame->board[x][y].center_y );
}


int CountBoard(GAME_S_T *pGame)
{
    int winner = 0;
    int i;
     
    for (i = 0; i < pGame->grid_size_y; i++)
    {
        winner = winner || CountRow(pGame, i);
    }
    
    for (i = 0; i < pGame->grid_size_x; i++)
    {
        winner = winner || CountColumn(pGame, i);
    }
    
    winner = winner || CountDiagonal(pGame, DIAG_LEFT);
    winner = winner || CountDiagonal(pGame, DIAG_RIGHT);
    
    return(winner);
}


int CountRow(GAME_S_T *pGame, int row)
{
    int winner = 0;
    int p1count = 0;
    int p2count = 0;
    int c;
    
    for (c = 0; c < pGame->grid_size_x; c++)
    {
        // if p1 piece, then count it
        if ( pGame->board[c][row].piece_type == pGame->player1_piece_type )
        {
            p1count++;
        }
        
        // if p2 piece, then count it
        if ( pGame->board[c][row].piece_type == pGame->player2_piece_type )
        {
            p2count++;
        }
    }

    // did p1 win?
    if (p1count == pGame->grid_size_x)
    {
        pGame->winner = PLAYER_1;
        winner = 1;
    }
        
    // did p2 win?
    if (p2count == pGame->grid_size_x)
    {
        pGame->winner = PLAYER_2;
        winner = 1;
    }
    
    return(winner);   
}


int CountColumn(GAME_S_T *pGame, int column)
{
    int winner = 0;
    int p1count = 0;
    int p2count = 0;
    int r;
    
    for (r = 0; r < pGame->grid_size_y; r++)
    {
        // if p1 piece, then count it
        if ( pGame->board[column][r].piece_type == pGame->player1_piece_type )
        {
            p1count++;
        }
        
        // if p2 piece, then count it
        if ( pGame->board[column][r].piece_type == pGame->player2_piece_type )
        {
            p2count++;
        }
    }
    
    // did p1 win?
    if (p1count == pGame->grid_size_y)
    {
        pGame->winner = PLAYER_1;
        winner = 1;
    }
        
    // did p2 win?
    if (p2count == pGame->grid_size_y)
    {
        pGame->winner = PLAYER_2;
        winner = 1;
    }
        
    return(winner);   
}


int CountDiagonal(GAME_S_T *pGame, int diag)
{   
    int winner = 0;
    int p1count = 0;
    int p2count = 0;
    int i;
    
    switch(diag)
    {
        case DIAG_LEFT:
            for (i = 0; i < pGame->grid_size_y; i++)
            {
                if ( pGame->board[i][i].piece_type == pGame->player1_piece_type )
                {
                    p1count++;
                }
                if ( pGame->board[i][i].piece_type == pGame->player2_piece_type )
                {
                    p2count++;
                }                
            }
            break;
        
        case DIAG_RIGHT:
            for (i = 0; i < pGame->grid_size_y; i++)
            {
                if ( pGame->board[i][pGame->grid_size_y-1-i].piece_type == pGame->player1_piece_type )
                {
                    p1count++;
                }
                if ( pGame->board[i][pGame->grid_size_y-1-i].piece_type == pGame->player2_piece_type )
                {
                    p2count++;
                }                
            }
            break;
    }
    
    // did p1 win?
    if (p1count == pGame->grid_size_y)
    {
        pGame->winner = PLAYER_1;
        winner = 1;
    }
        
    // did p2 win?
    if (p2count == pGame->grid_size_y)
    {
        pGame->winner = PLAYER_2;
        winner = 1;
    }
    
    return(winner);   
}


void ComputerMove(GAME_S_T *pGame)
{
    switch(pGame->skill)
    {
        case SKILL_NONE:
            HandleMoveNone(pGame);
            break;
        case SKILL_RANDOM:
            HandleMoveRandom(pGame);
            break;
        case SKILL_BEST:
            HandleMoveBest(pGame);
            break;
    }

    // show computer's move on screen
    UpdateBoard(pGame, pGame->computer_move.column, pGame->computer_move.row, pGame->player2_piece_type);
    ScreenUpdate();    
}


void HandleMoveNone(GAME_S_T *pGame)
{    
    FindEmptyCells(pGame);
    
    // pick first available move in the empty cells list
    if (pGame->move_count > 0)
    {
        pGame->computer_move.row = pGame->moves[0].row;
        pGame->computer_move.column = pGame->moves[0].column;
        printf("None: computer move r,c = %d,%d\n", pGame->computer_move.row, pGame->computer_move.column);
    }
}


void HandleMoveRandom(GAME_S_T *pGame)
{
    int i = 0;
    
    FindEmptyCells(pGame);
    
    // randomly pick a move from empty cells list
    if (pGame->move_count > 0)
    {
        i = RandomInteger( 1, pGame->move_count );
        printf("random index = %d\n", i);
        pGame->computer_move.row = pGame->moves[i-1].row;
        pGame->computer_move.column = pGame->moves[i-1].column;
        printf("Random: computer move r,c = %d,%d\n", pGame->computer_move.row, pGame->computer_move.column);
    }
}


void HandleMoveBest(GAME_S_T *pGame)
{
    int done = 0;
    int i = 0;

    FindEmptyCells(pGame);

    // find best move in the empty cells list
    if (pGame->move_count > 0)
    {
        while (!done)
        {
            // look for center move
            for (i = 0; i < pGame->move_count; i++)
            {
                if (pGame->moves[i].position_type == POSITION_CENTER)
                {
                    pGame->computer_move.row = pGame->moves[i].row;
                    pGame->computer_move.column = pGame->moves[i].column;
                    done = 1;
                    break;
                }
            }
            // if no center, look for corner move
            if (!done)
            {
                for (i = 0; i < pGame->move_count; i++)
                {
                    if (pGame->moves[i].position_type == POSITION_CORNER)
                    {
                        pGame->computer_move.row = pGame->moves[i].row;
                        pGame->computer_move.column = pGame->moves[i].column;
                        done = 1;
                        break;
                    }
                }
            }
            // if no center or corner, take remaining move
            if (!done)
            {
                for (i = 0; i < pGame->move_count; i++)
                {
                    if (pGame->moves[i].position_type == POSITION_OTHER)
                    {
                        pGame->computer_move.row = pGame->moves[i].row;
                        pGame->computer_move.column = pGame->moves[i].column;
                        done = 1;
                        break;
                    }
                }
            }
        } // end while
        printf("Random: computer move r,c = %d,%d\n", pGame->computer_move.row, pGame->computer_move.column);
    }
}


void FindEmptyCells(GAME_S_T *pGame)
{
    int x, y;
    int i = 0;

    // find all the empty grid cells
    for (y = 0; y < pGame->grid_size_y; y++)
    {
        for (x = 0; x < pGame->grid_size_x; x++)
        {
            if ( IsGridEmpty( pGame, x, y ) )
            {
                pGame->moves[i].row = y;
                pGame->moves[i].column = x;
                
                // determine relative position on the board
                if ( (x == 0 && y == 0) || (x == 2 && y == 0) || (x == 0 && y == 2) || (x == 2 && y == 2) )
                {
                    pGame->moves[i].position_type = POSITION_CORNER;
                }
                else if (x == 1 && y == 1)
                {
                    pGame->moves[i].position_type = POSITION_CENTER;                    
                }
                else
                {
                    pGame->moves[i].position_type = POSITION_OTHER;
                }
                
                i++;
            }
        }
    }
    pGame->move_count = i;   
}


/* end of game.c */
