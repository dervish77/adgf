/***********************************************************************

 Header file for the classic game of Pong.

   File:  	pong.h

   Author: 	Brian Lingard

   Date:	10/29/98

   Revisions:
	0.0	10/29/98	Originated

***********************************************************************/

#ifndef _PONG_H
#define _PONG_H


#ifndef _VECMATH_H
#include "vecmath.h"
#endif

#ifndef _MULTI_H
#include "multi.h"
#endif


#define VERSION			0.1

#define PROGNAME		"Pong"


#define GRID_SIZE		50

#define MAX_GRID_ROW		8
#define MAX_GRID_COL	 	12

#define SCREEN_X_SIZE   	(MAX_GRID_COL * GRID_SIZE)
#define SCREEN_Y_SIZE		(MAX_GRID_ROW * GRID_SIZE)

#define SCORE_X_SIZE   		(MAX_GRID_COL * GRID_SIZE)
#define SCORE_Y_SIZE		50

#define PIECE_DIAMETER		(GRID_SIZE - 4)

#define TOTAL_NUM_PIECES	(MAX_GRID_ROW * MAX_GRID_COL)

#define MAX_MOVES		10


#define BUTTON_UP	0		/* left button state */
#define BUTTON_DOWN	1


/* define special keys */
#define KEY_NEWGAME	'n'
#define KEY_OPENGAME	'l'
#define KEY_SAVEGAME	's'
#define KEY_QUITGAME	'q'
#define KEY_EXITGAME	'x'
#define KEY_HINT	'h'
#define KEY_PASS	'p'


/* define some common types */
#define BUFFER_LEN	80
typedef char BUFFER_T[BUFFER_LEN];

#define FILE_STRING_LEN	32
typedef char FILE_STRING_T[FILE_STRING_LEN];

typedef unsigned char	UBYTE_T;

typedef UBYTE_T		BOOLEAN_T;

typedef unsigned int	COUNT_T;

#ifndef TRUE
#define TRUE  ((BOOLEAN_T) 1)
#define FALSE ((BOOLEAN_T) 0)
#endif


/* define some useful macros */
#define InvertY(y)	(SCREEN_Y_SIZE - y)

#ifdef _USE_IRIX
	#define SQRT_FUNC(x)	(sqrtf(x))
#else
	#define SQRT_FUNC(x)	(sqrt(x))
#endif




/* define direction type */
typedef enum {
	DIR_NONE = 0,	
	DIR_N,
	DIR_NE,
	DIR_E,
	DIR_SE, 
	DIR_S, 
	DIR_SW, 
	DIR_W, 
	DIR_NW 
} DIRECTION_T;


/* define player type */
typedef enum {
	PLAYER_NONE = 0,	
	PLAYER_SINGLE,
	PLAYER_MULTI,
	PLAYER_DEMO 
} PLAYER_T;


/* define piece type */
typedef enum {
	PIECE_EMPTY = 0,	
	PIECE_PLAYER_1,
	PIECE_PLAYER_2 
} PIECE_T;

#define TOGGLE_PLAYER(p) ((p) == PIECE_PLAYER_1 ? (PIECE_PLAYER_2) : (PIECE_PLAYER_1))


/* define default colors for players */
#define PLAYER_1_COLOR		WHITE
#define PLAYER_2_COLOR		BLACK


/* define skill levels */
typedef enum {
	SKILL_1 = 0,
	SKILL_2,
	SKILL_3,
	SKILL_4,
	SKILL_5
} SKILL_T;


/* define neighbor array */
typedef int NEIGHBOR_A_T[3][3];


/* define grid structure */
typedef struct grid_s_t {
   BOOLEAN_T	draw_grid_flag;		/* grid is drawn if TRUE */
   pointType	size;			/* size of grid x and y */
   BOOLEAN_T	pick_flag;		/* TRUE if valid pick */
   int		pick_row;
   int 		pick_col;
   int		prev_pick_row;
   int 		prev_pick_col;
   pointType	top_left[MAX_GRID_ROW][MAX_GRID_COL];
   pointType	bot_right[MAX_GRID_ROW][MAX_GRID_COL];
} GRID_S_T;


/* define game structure */ 
typedef struct game_s_t {
   BOOLEAN_T	game_in_progress;
   BOOLEAN_T	network_game;
   PLAYER_T	player_mode;
   SKILL_T	skill_level;
   PIECE_T	current_player;
   PIECE_T	winning_player;
   PIECE_T	board[MAX_GRID_ROW][MAX_GRID_COL];
} GAME_S_T;


/* define score structure */ 
typedef struct score_s_t {
   int		player1_score;
   int		player2_score;
   int		player1_color;
   int		player2_color;
   pointType	plyr1_label;
   pointType	plyr2_label;
   pointType	box1_top_left;
   pointType	box2_top_left;
   BUFFER_T	player1_name;
   BUFFER_T	player2_name;
} SCORE_S_T;

/* define screen structure */
typedef struct screen_s_t {
   int		screen_x_size;
   int		screen_y_size;
   int		score_x_size;
   int		score_y_size;
   int		max_grid_row;
   int		max_grid_col;
   int		piece_diameter;
   int		grid_size;
   int 		total_num_pieces;
} SCREEN_S_T;


#endif /* _PONG_H */
/* end of pong.h */
