/*****************************************************************************
 *
 *	RPG game screens.
 *
 *  Description:
 *  RPG game using LibSDL.
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

#define GAME_TITLE             "RPG"

#define GRID_WIDTH             33       // size of each game tile
#define GRID_HEIGHT            33

#define GRID_CELLS_X           30       // number of tiles x and y
#define GRID_CELLS_Y           22

#define WIDTH                  (GRID_WIDTH * GRID_CELLS_X)
#define HEIGHT                 (GRID_HEIGHT * GRID_CELLS_Y)
#define BPP                    BPP_16

#define GRID_BK_COLOR          CLR_BLACK
#define GRID_LINE_COLOR        CLR_GRAY_DARK
#define GRID_CELL_ALIVE_COLOR  CLR_GREEN
#define GRID_CELL_DEAD_COLOR   GRID_BK_COLOR

#define GR_TITLE               "art/title.bmp"


#define GR_NULL                "art/null.bmp"
#define GR_PLAYER_U            "art/shipu.bmp"
#define GR_PLAYER_D            "art/shipd.bmp"
#define GR_PLAYER_L            "art/shipl.bmp"
#define GR_PLAYER_R            "art/shipr.bmp"
#define GR_ROID                "art/roid.bmp"
#define GR_ROIDX               "art/roidx.bmp"
#define GR_AMMO                "art/ammo.bmp"
#define GR_HEALTH              "art/health.bmp"
#define GR_WARP                "art/warp.bmp"
#define GR_UFO                 "art/ufo.bmp"

#define PIECE_NULL             0
#define PIECE_PLAYER_U         1
#define PIECE_PLAYER_D         2
#define PIECE_PLAYER_L         3
#define PIECE_PLAYER_R         4
#define PIECE_ROID             5
#define PIECE_ROIDX            6
#define PIECE_AMMO             7
#define PIECE_HEALTH           8
#define PIECE_WARP             9
#define PIECE_UFO              10
#define PIECE_COUNT            11

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
#define PIECE_DEAD             0


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
    int piece_type;
    char *file;
    spriteContext sprite;
} SPRITE_S_T;

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

void ScreenLoadSprites();

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

