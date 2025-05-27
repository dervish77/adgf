/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _ICON_H
#include "icon.h"
#endif


/* define widget indices */
#define FILE_MENU_IDX		0
#define OPTIONS_MENU_IDX	1
#define LABEL_IDX		2
#define DRAW_AREA_IDX		3
#define COLOR_BUTTON_01_IDX	4
#define COLOR_BUTTON_02_IDX	5
#define COLOR_BUTTON_03_IDX	6
#define COLOR_BUTTON_04_IDX	7
#define COLOR_BUTTON_05_IDX	8
#define COLOR_BUTTON_06_IDX	9
#define COLOR_BUTTON_07_IDX	10
#define COLOR_BUTTON_08_IDX	11
#define PAD_LABEL_1_IDX		12
#define CURRENT_COLOR_LABEL_IDX	13
#define CURRENT_DRAW_COLOR_IDX	14
#define PAD_LABEL_2_IDX		15
#define EDIT_DRAW_COLOR_IDX	16
#define PAD_LABEL_3_IDX		17
#define PAD_LABEL_4_IDX		18
#define PREVIEW_AREA_IDX	19
#define FILE_OPEN_IDX		20
#define FILE_SAVE_IDX		21
#define FILE_SAVE_AS_IDX	22
#define FILE_CLOSE_IDX		23
#define FILE_ABOUT_IDX		24
#define FILE_HELP_IDX		25
#define FILE_QUIT_IDX		26
#define OPT_SETUP_IDX		27
#define OPT_CLEAR_ICON_IDX	28
#define OPT_CLR_PALETTE_IDX	29
#define OPT_FLIP_VERT_IDX	30
#define OPT_FLIP_HORIZ_IDX	31
#define OPT_ROT_LEFT_IDX	32
#define OPT_ROT_RIGHT_IDX	33
#define MAX_WIDGETS		34


#define COLOR_BUTTON_LABEL	"     "


/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
   BOOLEAN_T		project_loaded;	
   BOOLEAN_T		project_saved;
   FILE_STRING_T	load_file_name;
   FILE_STRING_T	save_file_name;
   FILE			*load_file;
   FILE			*save_file;
   int			current_draw_color;
   int			current_grid_color;
   ICON_S_T		data;
   GRID_S_T		grid;
   Widget		work_draw_area;
   Widget		current_color_area;
   Widget		color_buttons[MAX_COLOR_MAP];
   Widget		preview_area;
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);

extern void InitDatabase(MyProgram *data);
extern void LoadIcon(MyProgram *data);
extern void SaveIcon(MyProgram *data);

extern void UpdateDisplay(MyProgram *data);
extern void UpdatePreview(MyProgram *data);


#ifndef TRUE
#define TRUE  ((BOOLEAN_T) 1)
#define FALSE ((BOOLEAN_T) 0)
#endif


#endif /* _MAIN_H */
/* end of main.h */
