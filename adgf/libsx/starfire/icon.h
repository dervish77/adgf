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
#define ICON_UFO	((ICON_TYPE_T) 1)
#define ICON_UFO_X	((ICON_TYPE_T) 2)
#define ICON_PHOTON	((ICON_TYPE_T) 3)

#define ICON_PLANET 	((ICON_TYPE_T) 10)
#define ICON_PLANET_X	((ICON_TYPE_T) 11)
#define ICON_ROID	((ICON_TYPE_T) 12)
#define ICON_ROID_X	((ICON_TYPE_T) 13)
#define ICON_BHOLE	((ICON_TYPE_T) 14)
#define ICON_WORM	((ICON_TYPE_T) 15)

#define ICON_HEALTH	((ICON_TYPE_T) 20)
#define ICON_AMMO	((ICON_TYPE_T) 21)
#define ICON_WARP	((ICON_TYPE_T) 22)
#define ICON_SLAMMER	((ICON_TYPE_T) 23)

#define ICON_SHIP_X	((ICON_TYPE_T) 30)
#define ICON_SHIPU	((ICON_TYPE_T) 31)
#define ICON_SHIPD	((ICON_TYPE_T) 32)
#define ICON_SHIPL	((ICON_TYPE_T) 33)
#define ICON_SHIPR	((ICON_TYPE_T) 34)

#define MAX_NUM_ICONS	35

#define MAX_UFOS	5

#define MAX_PLANETS	6
#define MAX_ROIDS	15
#define MAX_BHOLES	3
#define MAX_WORM	3

#define MAX_HEALTH	5
#define MAX_AMMO	5
#define MAX_WARP	2
#define MAX_SLAMMER	2

#define SET_VALUE	0
#define INCR_SCORE	1
#define INCR_HEALTH	2
#define INCR_AMMO	3
#define INCR_WARP	4
#define INCR_SLAMMER	5
#define DECR_SCORE	6
#define DECR_HEALTH	7
#define DECR_AMMO	8
#define DECR_WARP	9
#define DECR_SLAMMER	10


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
   int			score;
   int			health;
   int			damage;
   int			ammo;
} ICONFILE_S_T;



#endif /* _ICON_H */
/* end of icon.h */
