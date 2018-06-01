/*****************************************************************************
 *
 *	Breakout game screens.
 *
 *  Description:
 *  Breakout using LibSDL.
 *
 *	File:	screens.h
 *
 *	Author: Brian Lingard
 *	Date:	11/12/2010
 *
 *
 *****************************************************************************/

#ifndef __screens_h
#define __screens_h

#include "draw-sdl.h"
#include "vecmath.h"


/*
 *  CONSTANTS
 */

#define GAME_TITLE             "Breakout"

#define WIDTH                  800
#define HEIGHT                 600
#define BPP                    BPP_16

#define GRID_COLOR             CLR_YELLOW
#define WALL_COLOR             CLR_YELLOW

#define BLOCKS_X               12
#define BLOCKS_Y               3

#define TOP_ROW_TLY            70       // fixed position of top row of blocks


//
// assets
//

#define GR_TITLE               "art/titleb.bmp"

#define GR_LEVEL1              "art/level1.bmp"
#define GR_LEVEL2              "art/level2.bmp"
#define GR_LEVEL3              "art/level3.bmp"
#define GR_LEVEL4              "art/level4.bmp"

#define GR_GAMEOVER            "art/gameover.bmp"

#define GR_BLOCK               "art/block"
#define GR_BLOCK1              "art/block1.bmp"
#define GR_BLOCK2              "art/block2.bmp"
#define GR_BLOCK3              "art/block3.bmp"
#define GR_BLOCK4              "art/block4.bmp"
#define GR_BLOCK5              "art/block5.bmp"
#define GR_BLOCK6              "art/block6.bmp"
#define GR_BLOCK7              "art/block7.bmp"
#define GR_BLOCK8              "art/block8.bmp"
#define GR_BLOCK9              "art/block9.bmp"
#define GR_BLOCK10             "art/block10.bmp"
#define GR_BLOCK11             "art/block11.bmp"    // unbreakable
#define GR_BLOCK12             "art/block12.bmp"    // special

#define NUM_BLOCK_TYPES        12

#define GR_BALL_NORMAL         "art/ball.bmp"
#define GR_BALL_SPECIAL        "art/ball.bmp"

#define GR_PADSHORT            "art/padshort.bmp"
#define GR_PADNORMAL           "art/padnormal.bmp"
#define GR_PADLONG             "art/padlong.bmp"


// walls
#define WALL_NONE                 0
#define WALL_TOP                  1
#define WALL_LEFT                 2
#define WALL_RIGHT                3
#define WALL_BOTTOM               4

// paddle states
#define PADDLE_STATE_UNKNOWN      0
#define PADDLE_STATE_SHORT        1
#define PADDLE_STATE_NORMAL       2
#define PADDLE_STATE_LONG         3

// block states
#define BLOCK_STATE_EMPTY         0
#define BLOCK_STATE_BREAKABLE     1
#define BLOCK_STATE_UNBREAKABLE   2
#define BLOCK_STATE_SPECIAL       3

// ball states
#define BALL_STATE_UNKNOWN        0
#define BALL_STATE_NORMAL         1
#define BALL_STATE_SPECIAL        2


// note: redefine these so that events in game.c are independent of SDL
#define SE_MOUSE_MOTION        MOUSE_MOTION
#define SE_MOUSE_LEFT_DOWN     MOUSE_LEFT_DOWN
#define SE_MOUSE_LEFT_UP       MOUSE_LEFT_UP
#define SE_MOUSE_MIDDLE_DOWN   MOUSE_MIDDLE_DOWN
#define SE_MOUSE_MIDDLE_UP     MOUSE_MIDDLE_UP
#define SE_MOUSE_RIGHT_DOWN    MOUSE_RIGHT_DOWN
#define SE_MOUSE_RIGHT_UP      MOUSE_RIGHT_UP
#define SE_KEY_DOWN            KEY_DOWN
#define SE_KEY_UP              KEY_UP
#define SE_WINDOW_QUIT         WINDOW_QUIT
#define SE_TIMER1_EVENT        TIMER1_EVENT
#define SE_TIMER2_EVENT        TIMER2_EVENT



/*
 *  STRUCTURES
 */


typedef struct _bounds_s_t {
    int top_left_x;
    int top_left_y;
    int bottom_right_x;
    int bottom_right_y;
} BOUNDS_S_T;

typedef struct _sprite_s_t {
    int state;                  // state of this sprite
    int type;                   // type of this sprite (which graphic to show)
    pointType center;           // center position
	vectorType velocity;        // movement speed and direction
    vectorType normal;          // surface normal (aka orientation)
    boundsType bounds;          // bounding box
    spriteContext sprite;       // the loaded sprite image
} SPRITE_S_T;

typedef struct _block_s_t {
    int block_state;            // state of this block
    int block_type;             // type of block (which graphic to show)
    int center_x;
    int center_y;
    vectorType normal;
    BOUNDS_S_T bounds;
    spriteContext sprite;
} BLOCK_S_T;

typedef struct _paddle_s_t {
    int paddle_state;
    int center_x;
    int center_y;
    vectorType normal;
    BOUNDS_S_T bounds;
    spriteContext sprite;
} PADDLE_S_T;

typedef struct _ball_s_t {
    int ball_state;
    int collide_count;
    int center_x;
    int center_y;
    vectorType direction;
    BOUNDS_S_T bounds;
    spriteContext sprite;
} BALL_S_T;

typedef struct _level_s_t {
    int level_id;
	int blocks_count;
    int blocks_x;
    int blocks_y;
    int block_width;
    int block_height;
    BLOCK_S_T blocks[BLOCKS_X][BLOCKS_Y];
} LEVEL_S_T;

typedef struct _screen_s_t {
    int width;
    int height;
    int bpp;
    long background_color;
} SCREEN_S_T;


/*
 *  PROTOTYPES
 */

void ScreenOpen();
void ScreenClear();
void ScreenPause(int delay);
void ScreenWaitQuit();
void ScreenClose();

void ScreenUpdate();

void ScreenLoadBlocks();
void ScreenLoadPaddle(PADDLE_S_T *paddle);
void ScreenLoadBall(BALL_S_T *ball);

int  ScreenAddTimer(int delay, int timer);
void ScreenRemoveTimer(int id);

void CopyBlockSprite( spriteContext *sprite, int index);

int  GetBlockWidth();
int  GetBlockHeight();

int  GetScreenWidth();
int  GetScreenHeight();

int  GetPaddleWidth(PADDLE_S_T *paddle);

int  GetScreenEvent(int *x, int *y, char *key);

vectorType GetWallNormal(int whichWall);

void DoTitleScreen();
void DoLevelScreen(int level);
void DoPlayScreen();
void DoGameOverScreen();

void ScreenDrawLevel(LEVEL_S_T *level);

void ScreenDrawBlock(BLOCK_S_T *block);
void ScreenEraseBlock(BLOCK_S_T *block);

void ScreenDrawPaddle(PADDLE_S_T *paddle);
void ScreenErasePaddle(PADDLE_S_T *paddle);

void ScreenDrawBall(BALL_S_T *ball);
void ScreenEraseBall(BALL_S_T *ball);


// sprite functions

void ScreenDrawSprite(SPRITE_S_T *sprite);
void ScreenEraseSprite(SPRITE_S_T *sprite);

int  ScreenIsSpriteCollision(SPRITE_S_T *sprite1, SPRITE_S_T *sprite2);



#endif /* __screens_h */

