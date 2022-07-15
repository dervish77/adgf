/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _MODELER_H
#include "modeler.h"
#endif


/* define widget indices */
#define FILE_MENU_IDX		0
#define CMD_MENU_IDX		1
#define OPT_MENU_IDX		2
#define VIEW_MENU_IDX		3
#define REND_MENU_IDX		4
#define ANIM_MENU_IDX		5
#define ZOOM_MENU_IDX		6
#define LABEL_IDX		7
#define DRAW_AREA_IDX		8
#define FILE_OPEN_IDX		9
#define FILE_SAVE_IDX		10
#define FILE_SAVE_AS_IDX	11
#define FILE_CLOSE_IDX		12
#define FILE_EXPORT_RAW_IDX	13
#define FILE_EXPORT_VRML_IDX	14
#define FILE_ABOUT_IDX		15
#define FILE_HELP_IDX		16
#define FILE_QUIT_IDX		17
#define CMD_ADD_PRIM_IDX	18
#define CMD_DEL_PRIM_IDX	19
#define CMD_EDIT_PRIM_IDX	20
#define CMD_EDIT_CAMERA_IDX	21
#define CMD_EDIT_LIGHT_IDX	22
#define CMD_EDIT_ANIM_IDX	23
#define OPT_DEF_SETUP_IDX	24
#define OPT_DUMP_DATA_IDX	25
#define OPT_STATUS_IDX		26
#define OPT_TOGGLE_COLOR_IDX    27
#define VIEW_ALL_IDX		28
#define VIEW_XY_IDX		29
#define VIEW_ZY_IDX		30
#define VIEW_XZ_IDX		31
#define VIEW_CAMERA_IDX		32		
#define REND_WIRE_IDX		33
#define REND_SOLID_IDX		34
#define REND_FLAT_IDX		35
#define ANIM_STOP_IDX		36
#define ANIM_RUN_FOR_IDX	37
#define ANIM_RUN_REV_IDX	38
#define ANIM_LOOP_IDX		39
#define ANIM_PING_IDX		40
#define ANIM_STEP_FOR_IDX	41
#define ANIM_STEP_REV_IDX	42
#define ANIM_FIRST_IDX		43
#define ANIM_LAST_IDX		44
#define ZOOM_IN_IDX		45
#define ZOOM_NORMAL_IDX		46
#define ZOOM_OUT_IDX		47
#define MAX_WIDGETS		48



/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
   BOOLEAN_T		project_loaded;	
   BOOLEAN_T		project_saved;
   BOOLEAN_T		project_exported;
   BOOLEAN_T		project_vrml;
   FILE_STRING_T	load_file_name;
   FILE_STRING_T	save_file_name;
   FILE_STRING_T	export_raw_file_name;
   FILE_STRING_T	export_vrml_file_name;
   FILE			*load_file;
   FILE			*save_file;
   FILE			*export_raw_file;
   FILE			*export_vrml_file;
   VIEW_SCREEN_T	view_screen_mode;
   RENDER_MODE_T	render_mode;
   double		zoom_value;
   MODEL_S_T		data;
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);
int add_prim(BOOLEAN_T edit_flag, PRIMITIVE_S_T *new);
int del_prim(BOOLEAN_T delete_flag, int *index, MyProgram *data);
int edit_lit(LIGHT_S_T *light);
int edit_cam(VIEW_S_T *view);
int view_set(MyProgram *data);


extern void InitDatabase(MyProgram *data);
extern void DumpDatabase(MyProgram *data);
extern void LoadModel(MyProgram *data);
extern void SaveModel(MyProgram *data);
extern void ExportModel(MyProgram *data);
extern void ExportVRML(MyProgram *data);
extern void AddPrimitiveToDatabase(PRIMITIVE_S_T *new, MyProgram *data);
extern void DeletePrimitiveFromDatabase(int index, MyProgram *data);

extern void TranslateDatabase(MyProgram *data);
extern void UpdateDisplay(MyProgram *data);

extern void ComputeNextFrame(MyProgram *data);

extern void SaveVRML(MyProgram *data);


#ifndef TRUE
#define TRUE  ((BOOLEAN_T) 1)
#define FALSE ((BOOLEAN_T) 0)
#endif


#endif /* _MAIN_H */
/* end of main.h */
