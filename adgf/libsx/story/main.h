/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif


#ifndef _STORY_H
#include "story.h"
#endif


/*  define widget indices 
 */
#define FILE_MENU_IDX		0
#define EDIT_MENU_IDX		1
#define VIEW_MENU_IDX		2
#define FUNC_MENU_IDX		3
#define TOOLS_MENU_IDX		4
#define HELP_MENU_IDX		5
#define LABEL_IDX		6
#define DRAW_AREA_IDX		7

#define FILE_NEW_IDX		8
#define FILE_OPEN_IDX		9
#define FILE_SAVE_IDX		10
#define FILE_SAVE_AS_IDX	11
#define FILE_PRINT_IDX		12
#define FILE_PRINT_SET_IDX	13
#define FILE_PREFS_IDX		14
#define FILE_CLOSE_IDX		15
#define FILE_QUIT_IDX		16

#define EDIT_UNDO_IDX		17
#define EDIT_SEL_ALL_IDX	18
#define EDIT_COPY_IDX		19
#define EDIT_PASTE_IDX		20
#define EDIT_CUT_IDX		21

#define VIEW_ALL_IDX		22
#define VIEW_ACT_IDX		23
#define VIEW_SCENE_IDX		24
#define VIEW_HIER_IDX		25
#define VIEW_FRAMES_IDX		26
#define VIEW_SLIDES_IDX		27

#define FUNC_ADD_ACT_IDX	28
#define FUNC_ADD_SCENE_IDX	29
#define FUNC_ADD_FRAME_IDX	30
#define FUNC_DEL_ACT_IDX	31
#define FUNC_DEL_SCENE_IDX	32
#define FUNC_DEL_FRAME_IDX	33
#define FUNC_EDIT_SEL_IDX	34
#define FUNC_EDIT_FRM_IDX	35
#define FUNC_REARRANGE_IDX	36

#define TOOLS_SELECT_IDX	37
#define TOOLS_LINE_IDX		38
#define TOOLS_FREE_IDX		39
#define TOOLS_RECT_IDX		40
#define TOOLS_CIRCLE_IDX	41
#define TOOLS_ARC_IDX		42
#define TOOLS_FRECT_IDX		43
#define TOOLS_FCIRCLE_IDX	44
#define TOOLS_FILL_STYLE_IDX	45
#define TOOLS_PATT_STYLE_IDX	46
#define TOOLS_IMP_BM_IDX	47
#define TOOLS_EXP_BM_IDX	48

#define HELP_ABOUT_IDX		49
#define HELP_BRIEF_IDX		50
#define HELP_SEARCH_IDX		51
#define HELP_INDEX_IDX		52

#define MAX_WIDGETS		53



/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
   BOOLEAN_T		project_loaded;	
   BOOLEAN_T		project_saved;
   FILE_STRING_T	load_file_str;
   FILE_STRING_T	save_file_str;
   FILE			*load_file_p;
   FILE			*save_file_p;
   PROJECT_S_T		proj;		/* project database pointer */
   DRAW_INFO_S_T	draw;		/* drawing info pointer */
   VIEW_INFO_S_T	view;		/* view info pointer */
   PRINT_INFO_S_T	print;		/* printing info pointer */
   Widget		draw_area_widget;
}MyProgram;


/*  extern all function prototypes 
 */

/* from main.c */
void init_display(int argc, char **argv, MyProgram *me);


/* from story.c */
extern void InitDatabase(MyProgram *data);
extern void FreeProject(MyProgram *data);
extern void OutputDatabase(MyProgram *data);
extern void ReadProject(MyProgram *data);
extern void SaveProject(MyProgram *data);
extern void UpdateDisplay(MyProgram *data);
extern void PrintError(char *err_string);
extern void ExitError(char *err_string);
extern int  ParseString(char *string, char *args[]);

/* from drawing.c */
extern void DrawHeader(MyProgram *data);


#endif /* _MAIN_H */
/* end of main.h */
