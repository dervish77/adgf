/*****************************************************************************
 *
 *	Breakout game logic.
 *
 *  Description:
 *  Breakout using LibSDL.
 *
 *	File:	game.h
 *
 *	Author: Brian Lingard
 *	Date:	11/12/2010
 *
 *
 *****************************************************************************/

#ifndef __game_h
#define __game_h

#include "vecmath.h"
#include "screens.h"


/*
 *  CONSTANTS
 */

#define TITLE_TIMEOUT           2000
#define LEVEL_TIMEOUT           1000
#define ANIM_TIMEOUT            50
#define KEY_TIMEOUT             100

#define GAME_STATE_IDLE         0
#define GAME_STATE_TITLE        1
#define GAME_STATE_LEVEL        2
#define GAME_STATE_PLAY         3
#define GAME_STATE_VICTORY      4
#define GAME_STATE_QUIT         5

#define KEY_RIGHT_ARROW         19
#define KEY_LEFT_ARROW          20

#define COLLIDE_COUNT_TRIGGER   4
#define COLLIDE_SPEED_UP        2
#define COLLIDE_MAX_SPEED		15

#define INITIAL_LEVEL			1

#define STARTING_LIVES			4


#define UNUSED(x) (void)(x)



/*
 *  STRUCTURES
 */

typedef struct _game_s_t {
    int state;
    int levelId;
    int lives;
    int score;
    LEVEL_S_T level;
    PADDLE_S_T paddle;
    BALL_S_T ball;
} GAME_S_T;


/*
 *  PROTOTYPES
 */

int DoGame(GAME_S_T *pGame);

void FindEmptyCells(GAME_S_T *pGame);

int GameStateIdle(GAME_S_T *pGame);
int GameStateTitle(GAME_S_T *pGame);
int GameStateLevel(GAME_S_T *pGame);
int GameStatePlay(GAME_S_T *pGame);
int GameStateVictory(GAME_S_T *pGame);
 
void InitGame(GAME_S_T *pGame);
void InitPaddle(GAME_S_T *pGame, int state);
void InitBall(GAME_S_T *pGame);

void InitLevel(GAME_S_T *pGame);

int IsBlockEmpty(GAME_S_T *pGame, int x, int y);
int IsWithinBlockBounds(GAME_S_T *pGame, int x, int y, int mx, int my);
int IsWithinBounds(BOUNDS_S_T *bounds, int mx, int my);

int IsBallCollideWithWall(GAME_S_T *pGame, int *whichWall);
int IsBallCollideWithPaddle(GAME_S_T *pGame);
int IsBallCollideWithABlock(GAME_S_T *pGame, int *cx, int *cy);
int IsBallCollideWithThisBlock(GAME_S_T *pGame, int cx, int cy);

void MoveBall(GAME_S_T *pGame);

void UpdateBallPosition(GAME_S_T *pGame, vectorType newpos);
void UpdateBallDirection(GAME_S_T *pGame, vectorType newdir);

void MovePaddleRight(GAME_S_T *pGame);
void MovePaddleLeft(GAME_S_T *pGame);

void MovePaddle(GAME_S_T *pGame, int x, int y);


/*
 *  STATICS
 */



#endif /* __game_h */

