/***********************************************************************

   File:  	icon.h

   Author: 	Brian Lingard

   Date:	9/29/95

 Header file for icon editor program.

***********************************************************************/

#ifndef _ICON_H
#define _ICON_H


#ifndef _VECMATH_H
#include "vecmath.h"
#endif

#define MIN_GRID_SIZE		4	/* grid width and height */

#define MAX_ICON_X_SIZE		128
#define MAX_ICON_Y_SIZE 	128

#define DEFAULT_ICON_X_SIZE	16
#define DEFAULT_ICON_Y_SIZE	16

#define SCREEN_X_SIZE   	(MAX_ICON_X_SIZE * MIN_GRID_SIZE)
#define SCREEN_Y_SIZE		(MAX_ICON_Y_SIZE * MIN_GRID_SIZE)

#define BUFFER_LEN	80
typedef char BUFFER_T[BUFFER_LEN];

#define BUTTON_UP	0		/* left button state */
#define BUTTON_DOWN	1


/* define some common types */
#define FILE_STRING_LEN	32
typedef char FILE_STRING_T[FILE_STRING_LEN];

typedef unsigned char	UBYTE_T;

typedef UBYTE_T		BOOLEAN_T;

#define FLIP_VERT	1
#define FLIP_HORIZ	2
#define ROTATE_LEFT	3
#define ROTATE_RIGHT	4

#define MAX_COLORS	8

#define COLOR_1_IDX	0
#define COLOR_2_IDX	1
#define COLOR_3_IDX	2
#define COLOR_4_IDX	3
#define COLOR_5_IDX	4
#define COLOR_6_IDX	5
#define COLOR_7_IDX	6
#define COLOR_8_IDX	7

#define DEFAULT_COLOR	COLOR_1_IDX

#define COLOR_RGB_LEN 	3
#define R_IDX 0
#define G_IDX 1
#define B_IDX 2
typedef UBYTE_T COLOR_RGB_T[COLOR_RGB_LEN];

#define MAX_COLOR_MAP	MAX_COLORS

typedef struct {
   COLOR_RGB_T  map[MAX_COLOR_MAP];	/* actual rgb values */
   int		indexes[MAX_COLOR_MAP];	/* libsx index of color */
} COLORMAP_S_T;


typedef int ICON_TYPE_T;


#define DEG2RADS(d)	((d / 360) * PI)


/* define icon structure */ 
typedef struct icon_s_t {
   ICON_TYPE_T		type;		/* type of icon */
   pointType		size;		/* size of icon x and y */
   pointType		top_left;	/* position of top left */
   int			num_colors;
   COLORMAP_S_T		colormap;	/* color map structure */
   int			pixmap[MAX_ICON_X_SIZE][MAX_ICON_Y_SIZE];
} ICON_S_T;


typedef struct grid_s_t {
   BOOLEAN_T		draw_grid_flag;	/* grid is drawn if TRUE */
   pointType		size;		/* size of grid x and y */
   BOOLEAN_T		pick_flag;	/* TRUE if valid pick */
   int			pick_row;
   int 			pick_col;
   int			prev_pick_row;
   int 			prev_pick_col;
   pointType		top_left[MAX_ICON_X_SIZE][MAX_ICON_Y_SIZE];
   pointType		bot_right[MAX_ICON_X_SIZE][MAX_ICON_Y_SIZE];
} GRID_S_T;


/* extern all function prototypes */
extern int ParseString(char *string, char *args[]);


#endif /* _ICON_H */
/* end of icon.h */
