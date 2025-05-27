/***********************************************************************

 Header file for the game of StarFire.

   File:  	starfire.h

   Author: 	Brian Lingard

   Date:	10/05/97

   Revisions:
	0.0	10/05/97 Originated

***********************************************************************/

#ifndef _STARFIRE_H
#define _STARFIRE_H


#ifndef _VECMATH_H
#include "vecmath.h"
#endif


#define VERSION			0.3


#define GRID_SIZE		32

#define MAX_GRID_ROW		12
#define MAX_GRID_COL	 	20

#define SCREEN_X_SIZE   	(MAX_GRID_COL * GRID_SIZE)
#define SCREEN_Y_SIZE		(MAX_GRID_ROW * GRID_SIZE)

#define SCORE_X_SIZE   		(MAX_GRID_COL * GRID_SIZE)
#define SCORE_Y_SIZE		(GRID_SIZE + 5)

#define STATUS_X_SIZE   	(MAX_GRID_COL * GRID_SIZE)
#define STATUS_Y_SIZE		(GRID_SIZE + 5)


#define DEFAULT_FRAME_RATE	5	/* frames per second */


#define BUTTON_UP	0		/* left button state */
#define BUTTON_DOWN	1


/* define special keys */
#define KEY_UP		'U'
#define KEY_DOWN	'D'
#define KEY_LEFT	'L'
#define KEY_RIGHT	'R'

#define KEY_FIRE	' '
#define KEY_WARP	'w'

#define KEY_NEWGAME	'n'
#define KEY_OPENGAME	'l'
#define KEY_SAVEGAME	's'
#define KEY_QUITGAME	'q'
#define KEY_EXITGAME	'x'
#define KEY_MULTI	'm'

#define KEY_ANIM	'a'
#define KEY_INVENTORY	'i'
#define KEY_SLAMMER	'p'



/* define some common types */
#define BUFFER_LEN	80
typedef char BUFFER_T[BUFFER_LEN];

#define FILE_STRING_LEN	32
typedef char FILE_STRING_T[FILE_STRING_LEN];

typedef unsigned char	UBYTE_T;

typedef UBYTE_T		BOOLEAN_T;


#ifndef TRUE
#define TRUE  ((BOOLEAN_T) 1)
#define FALSE ((BOOLEAN_T) 0)
#endif



/* define some useful macros */
#define InvertY(y)	(SCREEN_Y_SIZE - y)



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


/* define grid structure */
typedef struct grid_s_t {
   pointType	screen_size;		/* size of grid x and y */
   pointType	grid_size;		/* size of grid x and y */
   pointType	top_left[MAX_GRID_ROW][MAX_GRID_COL];
   pointType	bot_right[MAX_GRID_ROW][MAX_GRID_COL];
} GRID_S_T;


/* define anim structure */
typedef struct anim_s_t {
   BOOLEAN_T	enable_anim;	/* if TRUE run the anim */
   int		frame_rate;	/* frames per second */
   int		frame_count;	/* current frame count */
   int		frame_interval;	/* time until next frame, milliseconds */
   void		*callback;	/* pointer to next frame callback function */
} ANIM_S_T;


/* define photon structure */ 
typedef struct photon_s_t {
   BOOLEAN_T	enable_anim;	/* if TRUE, run the anim */
   BOOLEAN_T	erase_trail;	/* if TRUE, erase photon trail */
   BOOLEAN_T	hit_target;	/* if TRUE, photon has hit target */
   char		direction;	/* using KEY #defines */
   int		frame_count;	/* current frame count */
   int		current_row;
   int		current_col;
   int		previous_row;
   int		previous_col;
} PHOTON_S_T;


/* define player structure */ 
typedef struct player_s_t {
   PIECE_T	current_player;
   PIECE_T	winning_player;
   int		current_row;
   int		current_col;
   int		previous_row;
   int		previous_col;
} PLAYER_S_T;


/* define game structure */ 
typedef struct game_s_t {
   BOOLEAN_T	game_in_progress;
   PLAYER_T	player_mode;
   PLAYER_S_T	player;
   PHOTON_S_T	photon;
   PIECE_T	map[MAX_GRID_ROW][MAX_GRID_COL];
   PIECE_T	board[MAX_GRID_ROW][MAX_GRID_COL];
} GAME_S_T;


/* define score structure */ 
typedef struct score_s_t {
   pointType	screen_size;		/* size of score x and y */
   int		score;
   int		health;
   int		ammo;
   int		warp;
   int		slammer;
   pointType	score_label;
   pointType	health_label;
   pointType	ammo_label;
   pointType	warp_label;
   pointType	slammer_label;
} SCORE_S_T;


/* define status structure */ 
typedef struct status_s_t {
   pointType	screen_size;		/* size of status x and y */
   char		*msg;
   pointType	status_label;
} STATUS_S_T;



#endif /* _STARFIRE_H */
/* end of starfire.h */
