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

#define DEFAULT_ICON_X_SIZE	32
#define DEFAULT_ICON_Y_SIZE	32

#define BUTTON_UP		0	/* left button state */
#define BUTTON_DOWN		1



/* define some common types */

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
#define ICON_NONE	((ICON_TYPE_T) 0)
#define ICON_TRAIL	((ICON_TYPE_T) 1)

#define ICON_FOREST 	((ICON_TYPE_T) 10)
#define ICON_DESERT	((ICON_TYPE_T) 11)
#define ICON_MOUNTAIN	((ICON_TYPE_T) 12)

#define ICON_WATER	((ICON_TYPE_T) 20)
#define ICON_FOOD	((ICON_TYPE_T) 21)

#define ICON_PLAY_X	((ICON_TYPE_T) 30)
#define ICON_PLAYU	((ICON_TYPE_T) 31)
#define ICON_PLAYD	((ICON_TYPE_T) 32)
#define ICON_PLAYL	((ICON_TYPE_T) 33)
#define ICON_PLAYR	((ICON_TYPE_T) 34)

#define MAX_NUM_ICONS	35

#define MAX_TRAIL	10

#define MAX_FOREST	20
#define MAX_DESERT	15
#define MAX_MOUNTAIN	10

#define MAX_WATER	20
#define MAX_FOOD	10

#define SET_VALUE	0
#define INCR_HEALTH	1
#define INCR_WATER	2
#define INCR_FOOD	3
#define DECR_HEALTH	4
#define DECR_WATER	5
#define DECR_FOOD	6


/*  define icon structure 
 */ 
typedef struct icon_s_t {
   ICON_TYPE_T		type;		/* type of icon */
   pointType		size;		/* size of icon x and y */
   pointType		top_left;	/* position of top left */
   int			num_colors;
   COLORMAP_S_T		colormap;	/* color map structure */
   int			pixmap[MAX_ICON_X_SIZE][MAX_ICON_Y_SIZE];
} ICON_S_T;


/*  define icon file structure
 */
typedef struct iconfile_s_t {
   ICON_TYPE_T		type;		/* type of icon */
   FILE_STRING_T	filename;	/* file name as string */
   int			movement;
   int			water;
   int			food;
   int			health;
} ICONFILE_S_T;



#endif /* _ICON_H */
/* end of icon.h */
