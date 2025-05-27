/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _PARTICLE_H
#include "particle.h"
#endif


/* define widget indices */
#define FILE_MENU_IDX		0
#define CMD_MENU_IDX		1
#define OPT_MENU_IDX		2
#define VIEW_MENU_IDX		3
#define ANIM_MENU_IDX		4
#define ZOOM_MENU_IDX		5
#define LABEL_IDX		6
#define DRAW_AREA_IDX		7
#define FILE_OPEN_IDX		8
#define FILE_SAVE_IDX		9
#define FILE_SAVE_AS_IDX	10
#define FILE_CLOSE_IDX		11
#define FILE_ABOUT_IDX		12
#define FILE_HELP_IDX		13
#define FILE_QUIT_IDX		14
#define CMD_SET_SYS_IDX		15
#define CMD_EDIT_CAMERA_IDX	16
#define CMD_EDIT_ANIM_IDX	17
#define OPT_DUMP_DATA_IDX	18
#define OPT_STATUS_IDX		19
#define VIEW_ALL_IDX		20
#define VIEW_XY_IDX		21
#define VIEW_ZY_IDX		22
#define VIEW_XZ_IDX		23
#define VIEW_CAMERA_IDX		24		
#define ANIM_STOP_IDX		25
#define ANIM_RUN_FOR_IDX	26
#define ANIM_RUN_REV_IDX	27
#define ANIM_LOOP_IDX		28
#define ANIM_PING_IDX		29
#define ANIM_STEP_FOR_IDX	30
#define ANIM_STEP_REV_IDX	31
#define ANIM_FIRST_IDX		32
#define ANIM_LAST_IDX		33
#define ZOOM_IN_IDX		34
#define ZOOM_NORMAL_IDX		35
#define ZOOM_OUT_IDX		36
#define MAX_WIDGETS		37



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
   VIEW_SCREEN_T	view_screen_mode;
   double		zoom_value;
   MODEL_S_T		data;
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);
int setpart(MyProgram *data);
int edit_cam(VIEW_S_T *view);
int editanim(ANIM_S_T *anim);

extern void InitDatabase(MyProgram *data);
extern void DumpDatabase(MyProgram *data);
extern void LoadModel(MyProgram *data);
extern void SaveModel(MyProgram *data);

extern void UpdateDisplay(MyProgram *data);

extern void ComputeNextFrame(MyProgram *data);


#ifndef TRUE
#define TRUE  ((BOOLEAN_T) 1)
#define FALSE ((BOOLEAN_T) 0)
#endif


#endif /* _MAIN_H */
/* end of main.h */
