/*****************************************************************************
 *
 *	SicDacLoe game screens.
 *
 *  Description:
 *  Tic Tac Toe using LibSDL.
 *
 *	File:	screens.h
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/

#ifndef __screens_h
#define __screens_h

#include "draw-sdl.h"


/*
 *  CONSTANTS
 */

#define GAME_TITLE             "SicDacLoe"

#define WIDTH                  500
#define HEIGHT                 500
#define BPP                    BPP_16

#define GRID_COLOR             CLR_YELLOW

#define GR_TITLE               "art/titleb.bmp"
#define GR_ONE_PLAYER          "art/p1c.bmp"
#define GR_TWO_PLAYER          "art/p2c.bmp"
#define GR_NO_WINS             "art/p0winc.bmp"
#define GR_P1_WINS             "art/p1winc.bmp"
#define GR_P2_WINS             "art/p2winc.bmp"

#define GR_X                   "art/x.bmp"
#define GR_O                   "art/o.bmp"

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

// note: these values need to match those in game.h
#define PIECE_X                1
#define PIECE_O                2


/*
 *  STRUCTURES
 */
 
typedef struct _bounds_s_t {
    int top_left_x;
    int top_left_y;
    int bottom_right_x;
    int bottom_right_y;
} BOUNDS_S_T;

typedef struct _screen_s_t {
    int width;
    int height;
    int bpp;
    long background_color;
    long grid_color;
    int grid_cells_x;
    int grid_cells_y;
    int grid_width;
    int grid_height;
} SCREEN_S_T;


/*
 *  PROTOTYPES
 */

void ScreenOpen();
void ScreenClear();
void ScreenPause(int delay);
void ScreenWaitQuit();
void ScreenClose();

int  ScreenAddTimer(int delay, int timer);
void ScreenRemoveTimer(int id);

int  GetGridWidth();
int  GetGridHeight();

int  GetScreenEvent(int *x, int *y, char *key);

void DoTitleScreen();
void DoPlayerScreen(BOUNDS_S_T *p1bounds, BOUNDS_S_T *p2bounds);

void ScreenDrawGrid();
void ScreenDrawPiece(int piece, int cx, int cy);

void ScreenUpdate();

void DoVictoryScreen(int player);


/*
 *  STATICS
 */



#endif /* __screens_h */

