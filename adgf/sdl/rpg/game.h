/*****************************************************************************
 *
 *	RPG game logic.
 *
 *  Description:
 *  RPG game using LibSDL.
 *
 *	File:	game.h
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
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

#define PIECE_TYPE_NULL             0
#define PIECE_TYPE_PLAYER_U         1
#define PIECE_TYPE_PLAYER_D         2
#define PIECE_TYPE_PLAYER_L         3
#define PIECE_TYPE_PLAYER_R         4
#define PIECE_TYPE_ROID             5
#define PIECE_TYPE_ROIDX            6
#define PIECE_TYPE_AMMO             7
#define PIECE_TYPE_HEALTH           8
#define PIECE_TYPE_WARP             9
#define PIECE_TYPE_UFO              10

#define PIECE_TYPE_ALIVE    PIECE_TYPE_PLAYER_U
#define PIECE_TYPE_DEAD     0
#define PIECE_TYPE_EMPTY    PIECE_TYPE_DEAD

#define PLAYER_NONE         0
#define PLAYER_1            1
#define PLAYER_2            2

#define GRID_SIZE_X         GRID_CELLS_X
#define GRID_SIZE_Y         GRID_CELLS_Y

#define DIAG_LEFT           1
#define DIAG_RIGHT          2

#define GAME_STATE_IDLE     0
#define GAME_STATE_TITLE    1
#define GAME_STATE_PLAY     2
#define GAME_STATE_QUIT     3

#define TICK_SPEED_SLOW     500
#define TICK_SPEED_FAST     100

#define PATTERN_NONE		0
#define PATTERN_SPIN		1
#define PATTERN_BEACON		2
#define PATTERN_GLIDER		3
#define PATTERN_LWSS		4
#define PATTERN_PULSAR		5
#define PATTERN_LINE		6
#define PATTERN_QUEENBEE	7
#define PATTERN_GUN		    8
#define PATTERN_MAX		    PATTERN_GUN


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
    int grid_size_x;
    int grid_size_y;
    int grid_width;
    int grid_height;
    PIECE_S_T board[GRID_SIZE_X][GRID_SIZE_Y];
    PIECE_S_T prev_board[GRID_SIZE_X][GRID_SIZE_Y];
    int ticks;
    int tick_speed;
    int pattern;
} GAME_S_T;


/*
 *  PROTOTYPES
 */

int DoGame(GAME_S_T *pGame, int play_mode);

int GameStateIdle(GAME_S_T *pGame, int mode);
int GameStateTitle(GAME_S_T *pGame);
int GameStatePlay(GAME_S_T *pGame);
int GameStateQuit(GAME_S_T *pGame);

void InitGame(GAME_S_T *pGame);
void SetPlayMode(GAME_S_T *pGame, int mode);

void LoadGameSprites(void);

void InitBoard(GAME_S_T *pGame);
void ClearBoard(GAME_S_T *pGame);
void RandomBoard(GAME_S_T *pGame);

int RandomAlive(int x, int y);

int IsGridEmpty(GAME_S_T *pGame, int x, int y);
int IsWithinGridBounds(GAME_S_T *pGame, int x, int y, int mx, int my);

void UpdateBoard(GAME_S_T *pGame, int x, int y, int piece);
void RedrawBoard(GAME_S_T *pGame);

void GameTick(GAME_S_T *pGame);
void CopyBoardToPrevious(GAME_S_T *pGame);

int IsCellAlive(GAME_S_T *pGame, int x, int y);

int CountNeighbors(GAME_S_T *pGame, int x, int y);

void GamePattern(GAME_S_T *pGame);


/*
 *  STATICS
 */



#endif /* __game_h */

