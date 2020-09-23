/*****************************************************************************
 *
 *	Life UI game screens.
 *
 *  Description:
 *  Life UI using LibSDL.
 *
 *	File:	screens.h
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#ifndef __screens_h
#define __screens_h

#include "draw-sdl.h"


/*
 *  CONSTANTS
 */

#define GAME_TITLE             "Life"

#define WIDTH                  700
#define HEIGHT                 700
#define BPP                    BPP_16

#define GRID_CELLS_X           70
#define GRID_CELLS_Y           70

#define GRID_BK_COLOR          CLR_BLACK
#define GRID_LINE_COLOR        CLR_GRAY_DARK
#define GRID_CELL_ALIVE_COLOR  CLR_GREEN
#define GRID_CELL_DEAD_COLOR   GRID_BK_COLOR

#define GR_TITLE               "title.bmp"

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
#define PIECE_ALIVE            1
#define PIECE_DEAD             2


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
    long grid_color;
    long background_color;
    long cell_alive_color;
    long cell_dead_color;
    int grid_cells_x;
    int grid_cells_y;
    int grid_width;
    int grid_height;
    int grid_enable;
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
void DoPlayScreen();

void ScreenDrawGrid();
void ScreenDrawCell(int piece, int cx, int cy);

void ScreenUpdate();


/*
 *  STATICS
 */



#endif /* __screens_h */

