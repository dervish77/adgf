/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _EMU_H
#include "emu.h"
#endif


/* define widget indices */
#define FILE_MENU_IDX		0
#define OPTIONS_MENU_IDX	1
#define DISPLAY_MENU_IDX	2
#define CONTROL_MENU_IDX	3
#define HELP_MENU_IDX		4
#define LABEL_IDX		5
#define DRAW_AREA_IDX		6
#define STATUS_AREA_IDX		7

#define FILE_LOAD_IDX		8
#define FILE_SAVE_IDX		9
#define FILE_QUIT_IDX		10

#define OPT_RAM_IDX		11
#define OPT_ROM_IDX		12
#define OPT_CLOCK_IDX		13
#define OPT_STAT_IDX		14

#define DIS_MPU_IDX		15
#define DIS_SYS_IDX		16
#define DIS_BOTH_IDX		17
#define DIS_IMAGE_IDX		18

#define CON_RESET_IDX		19
#define CON_STEP_IDX		20
#define CON_GO_IDX		21
#define CON_HALT_IDX		22

#define HELP_ABOUT_IDX		23
#define HELP_MENUS_IDX		24
#define HELP_KEYS_IDX		25

#define MAX_WIDGETS		26



/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
   BOOLEAN_T		file_loaded;	
   BOOLEAN_T		file_saved;
   FILE_STRING_T	load_file_name;
   FILE_STRING_T	save_file_name;
   FILE			*load_file;
   FILE			*save_file;
   Widget		draw_area_widget;
   Widget		status_area_widget;
   pointType		mouse_pick;
   STATUS_S_T		status;			/* status structure */
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);
void InitDatabase(MyProgram *data);
void LoadImage(MyProgram *data);
void UpdateDisplay(MyProgram *data);
void UpdateStatus(MyProgram *data);

void HandleControl(MyProgram *data);

int  seed_random();
int  int_random(int min_value, int max_value);
int  ParseString(char *string, char *args[]);

void ClearScreenDisplay(Widget w);
void SetDrawColor(int idx);
char *PopupFileRequest(char *message);

#endif /* _MAIN_H */
/* end of main.h */
