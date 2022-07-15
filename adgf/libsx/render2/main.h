/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _RENDER_H
#include "render.h"
#endif


/* define widget indices */
#define FILE_MENU_IDX		0
#define EDIT_MENU_IDX		1
#define RENDER_MENU_IDX		2
#define VIEW_MENU_IDX		3
#define LABEL_IDX		4
#define ZOOM_LABEL1_IDX		5
#define ZOOM_SCROLL_IDX		6
#define ZOOM_LABEL2_IDX		7
#define DRAW_AREA_IDX		8
#define LONG_SCROLL_IDX		9
#define LAT_SCROLL_IDX		10
#define FILE_OPEN_IDX		11
#define FILE_SAVE_IDX		12
#define FILE_SAVE_AS_IDX	13
#define FILE_CLOSE_IDX		14
#define FILE_ABOUT_IDX		15
#define FILE_HELP_IDX		16
#define FILE_QUIT_IDX		17
#define EDIT_COPY_IDX		18
#define EDIT_PASTE_IDX		19
#define EDIT_CUT_IDX		20
#define RENDER_WIRE_IDX		21
#define RENDER_FLAT_IDX		22
#define RENDER_GOUR_IDX		23
#define RENDER_PHONG_IDX	24
#define VIEW_ORTH_XY_IDX	25
#define VIEW_ORTH_ZY_IDX	26
#define VIEW_ORTH_XZ_IDX	27
#define VIEW_PARA_IDX		28
#define VIEW_PERS_IDX		29
#define MAX_WIDGETS		30



/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
   BOOLEAN_T		project_loaded;	
   BOOLEAN_T		project_saved;
   float		longitude;		/* degrees */
   float 		latitude;		/* degrees */
   float		zoom;			/* distance units */
   RENDER_S_T		data;			/* project data */
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);


#ifndef TRUE
#define TRUE  ((BOOLEAN_T) 1)
#define FALSE ((BOOLEAN_T) 0)
#endif


#endif /* _MAIN_H */
/* end of main.h */
