/*****************************************************************************
 *
 *	SicDacLoe game logic.
 *
 *  Description:
 *  Tic Tac Toe using LibSDL.
 *
 *	File:	game.h
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/

#ifndef __game_h
#define __game_h

#include "screens.h"


/*
 *  CONSTANTS
 */

#define MODE_UNKNOWN        0
#define MODE_ONE_PLAYER     1
#define MODE_TWO_PLAYER     2

#define PIECE_TYPE_EMPTY    0
#define PIECE_TYPE_X        1
#define PIECE_TYPE_O        2

#define PLAYER_NONE         0
#define PLAYER_1            1
#define PLAYER_2            2

#define GRID_SIZE_X         3
#define GRID_SIZE_Y         3

#define DIAG_LEFT           1
#define DIAG_RIGHT          2

#define GAME_STATE_IDLE     0
#define GAME_STATE_TITLE    1
#define GAME_STATE_PLAYERS  2
#define GAME_STATE_PLAY     3
#define GAME_STATE_VICTORY  4
#define GAME_STATE_QUIT     5

#define MAX_MOVES           (GRID_SIZE_X * GRID_SIZE_Y)

#define SKILL_NONE          0
#define SKILL_RANDOM        1
#define SKILL_BEST          2

//#ifndef RAND_MAX
//#define RAND_MAX 32767
//#endif

#define POSITION_CORNER     1
#define POSITION_CENTER     2
#define POSITION_OTHER      3


/*
 *  STRUCTURES
 */

typedef struct _move_s_t {
    int row;
    int column;
    int position_type;
} MOVE_S_T;

typedef struct _piece_s_t {
    int piece_type;
    int center_x;
    int center_y;
    BOUNDS_S_T bounds;
} PIECE_S_T;

typedef struct _game_s_t {
    int state;
    int play_mode;
    int player1_piece_type;
    int player2_piece_type;
    int current_player;
    int used_grid_count;
    int winner;
    int grid_size_x;
    int grid_size_y;
    int grid_width;
    int grid_height;
    PIECE_S_T board[GRID_SIZE_X][GRID_SIZE_Y];
    MOVE_S_T moves[MAX_MOVES];
    int move_count;
    MOVE_S_T computer_move;
    int skill;
} GAME_S_T;


/*
 *  PROTOTYPES
 */

int DoGame(GAME_S_T *pGame, int play_mode, int comp_skill);

void ComputerMove(GAME_S_T *pGame);
void HandleMoveNone(GAME_S_T *pGame);
void HandleMoveRandom(GAME_S_T *pGame);
void HandleMoveBest(GAME_S_T *pGame);

void FindEmptyCells(GAME_S_T *pGame);

int GameStateIdle(GAME_S_T *pGame, int mode, int skill);
int GameStateTitle(GAME_S_T *pGame);
int GameStatePlayers(GAME_S_T *pGame);
int GameStatePlay(GAME_S_T *pGame);
int GameStateVistory(GAME_S_T *pGame);
 
void InitGame(GAME_S_T *pGame);
void SetPlayMode(GAME_S_T *pGame, int mode);
void SetPlaySkill(GAME_S_T *pGame, int skill);
void InitBoard(GAME_S_T *pGame);

int IsGridEmpty(GAME_S_T *pGame, int x, int y);
int IsWithinGridBounds(GAME_S_T *pGame, int x, int y, int mx, int my);
int IsWithinPlayerBounds(BOUNDS_S_T *bounds, int mx, int my);

void UpdateBoard(GAME_S_T *pGame, int x, int y, int piece);

int CountBoard(GAME_S_T *pGame);
int CountRow(GAME_S_T *pGame, int row);
int CountColumn(GAME_S_T *pGame, int column);
int CountDiagonal(GAME_S_T *pGame, int diag);


/*
 *  STATICS
 */

float nrand(void);
int int_random(int min_value, int max_value);


#endif /* __game_h */

