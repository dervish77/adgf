/***********************************************************************

 Header file for story board generation program.

   File:  	story.h

   Author: 	Brian Lingard

   Date:	5/26/95

   Revisions:
	0.2	02/12/96  Reduced database to two levels (removed frames)
	0.1	02/06/96  Touched up defines and typedefs
	0.0	05/26/95  Originated

***********************************************************************/

#ifndef _STORY_H
#define _STORY_H


#ifndef _VECMATH_H
#include "vecmath.h"
#endif


#define _DEBUG_STORY


#define DEFAULT_LOG_FILE_NAME	"story.log"


#define VERSION		"0.1"


/*  define screen size
 */
#define SCREEN_X_SIZE   	640
#define SCREEN_Y_SIZE		480


/*  define maximum scene size
 */
#define MAX_SCENE_X_SIZE	640
#define MAX_SCENE_Y_SIZE	480


/*  define minimum scene size
 */
#define MIN_SCENE_X_SIZE	100
#define MIN_SCENE_Y_SIZE	100


/*  define useful macros
 */
#define InvertY(y)	(SCREEN_Y_SIZE - y)


/*  define common types 
 */
#define EQ		==
#define NEQ		!=
#define AND		&&
#define OR		||
#define GEQ		>=
#define LEQ		<=

#define BUTTON_UP	0		/* left button state */
#define BUTTON_DOWN	1

#define BUFFER_LEN	80
typedef char BUFFER_T[BUFFER_LEN];

#define FILE_STRING_LEN	32
typedef char FILE_STRING_T[FILE_STRING_LEN];

#define STANDARD_STRING_LEN	80
typedef char STANDARD_STRING_T[STANDARD_STRING_LEN];

#define NOTES_STRING_LEN	(STANDARD_STRING_LEN*20)
typedef char NOTES_STRING_T[NOTES_STRING_LEN];

typedef unsigned char	UBYTE_T;

typedef unsigned short	UWORD_T;

typedef unsigned long	ULONG_T;

typedef UBYTE_T		BOOLEAN_T;

typedef int		SECONDS_T;



/*  define bitmap structure
 */
typedef struct bitmap_s_t {
   int			height;		/* height in pixels */
   int			width;		/* width in pixels */
   UBYTE_T		*bitmap_p;	/* pointer to B&W bitmap */
} BITMAP_S_T;


/*  define scene structure 
 */
struct {
   struct SCENE_S	*prev_scene_p;
   struct SCENE_S	*next_scene_p;
   UBYTE_T		scene_num;
   BITMAP_S_T		bm;		/* bitmap structure */
   STANDARD_STRING_T	action_str;
   STANDARD_STRING_T	dialog_str;
   STANDARD_STRING_T	sound_str;
   NOTES_STRING_T	notes_str;
} SCENE_S;


/*  define act structure 
 */
struct {
   struct ACT_S		*prev_act_p;
   struct ACT_S		*next_act_p;
   UBYTE_T		act_num;
   struct SCENE_S	*first_scene_p;
   struct SCENE_S	*last_scene_p;
   ULONG_T		num_scenes;
} ACT_S;


/*  define project structure 
 */
typedef struct project_s_t {
   FILE_STRING_T	projname_str;
   ULONG_T		num_of_acts;
   ULONG_T		num_of_scenes;
   struct ACT_S		*first_act_p;
   struct ACT_S		*last_act_p;
} PROJECT_S_T;


/*  define drawing types and drawing info structure 
 */
typedef UBYTE_T DRAW_MODE_T;
#define DRAW_SELECT		((DRAW_MODE_T) 0)
#define DRAW_POINT		((DRAW_MODE_T) 1)
#define DRAW_LINE		((DRAW_MODE_T) 2)
#define DRAW_FREE		((DRAW_MODE_T) 3)
#define DRAW_RECT		((DRAW_MODE_T) 4)
#define DRAW_CIRCLE		((DRAW_MODE_T) 5)
#define DRAW_ARC		((DRAW_MODE_T) 6)
#define DRAW_FILLED_RECT	((DRAW_MODE_T) 7)
#define DRAW_FILLED_CIRCLE	((DRAW_MODE_T) 8)

typedef UBYTE_T FILL_MODE_T;
#define FILL_NONE		((FILL_MODE_T) 0)
#define FILL_SOLID		((FILL_MODE_T) 1)
#define FILL_PATTERN		((FILL_MODE_T) 2)

typedef UBYTE_T PATTERN_MODE_T;
#define PATTERN_V_LINE		((PATTERN_MODE_T) 0)
#define PATTERN_H_LINE		((PATTERN_MODE_T) 1)
#define PATTERN_CROSS		((PATTERN_MODE_T) 2)
#define PATTERN_LD_LINE		((PATTERN_MODE_T) 3)
#define PATTERN_RD_LINE		((PATTERN_MODE_T) 4)

typedef UBYTE_T COLOR_MODE_T;
#define COLOR_NONE		((COLOR_MODE_T) 0)
#define COLOR_COLOR		((COLOR_MODE_T) 1)

typedef struct draw_info_s_t {
   DRAW_MODE_T		draw_mode;
   FILL_MODE_T		fill_mode;
   PATTERN_MODE_T	pattern_mode;
   COLOR_MODE_T		color_mode;
} DRAW_INFO_S_T;


/*  define view types and view info structure 
 */
typedef UBYTE_T VIEW_MODE_T;
#define VIEW_SINGLE		((VIEW_MODE_T) 0)	/* single scenes */
#define VIEW_THUMB		((VIEW_MODE_T) 1)	/* thumb nails */
#define VIEW_SLIDE_SHOW		((VIEW_MODE_T) 2)	/* as slide show */

#define DEFAULT_DELAY_TO_NEXT	((SECONDS_T) 5)

typedef struct view_info_s_t {
   VIEW_MODE_T		view_mode;
   int			num_vert;	/* number displayed vertically */
   int			num_horiz;	/* number displayed horizontally */
   SECONDS_T		delay_to_next;	/* time delay until next slide */
} VIEW_INFO_S_T;


/*  define print format structure 
 */
typedef UBYTE_T PRINT_MODE_T;
#define PRINT_TO_NULL		((PRINT_MODE_T) 0)
#define PRINT_TO_PRINTER	((PRINT_MODE_T) 1)
#define PRINT_TO_FILE		((PRINT_MODE_T) 2)

typedef struct print_info_s_t {
   PRINT_MODE_T		print_mode;
   FILE_STRING_T	filename_str;	/* name of file to print to */
   FILE			*file_p;	/* pointer to print file */
} PRINT_INFO_S_T;


/*  define some null pointer types
 */
#define NULL_FILE_PTR		((FILE *) NULL)
#define NULL_ACT_PTR		((struct ACT_S *) NULL)
#define NULL_SCENE_PTR		((struct SCENE_S *) NULL)

#define NULL_TERM		'\0'


/*  extern globals
 */
#ifdef _DEBUG_STORY
   extern FILE *logfile;
#endif


#endif /* _STORY_H */
/* end of story.h */
