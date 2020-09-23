/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _STARFIRE_H
#include "starfire.h"
#endif

#ifndef _ICON_H
#include "icon.h"
#endif


/* define widget indices */
#define FILE_MENU_IDX		0
#define OPTIONS_MENU_IDX	1
#define HELP_MENU_IDX		2
#define LABEL_IDX		3
#define DRAW_AREA_IDX		4
#define SCORE_AREA_IDX		5
#define STATUS_AREA_IDX		6

#define FILE_NEW_IDX		7
#define FILE_LOAD_IDX		8
#define FILE_SAVE_IDX		9
#define FILE_QUIT_IDX		10

#define OPT_SINGLE_IDX		11
#define OPT_MULTI_IDX		12
#define OPT_DEMO_IDX		13
#define OPT_STAT_IDX		14

#define HELP_ABOUT_IDX		15
#define HELP_MENUS_IDX		16
#define HELP_KEYS_IDX		17
#define HELP_RULES_IDX		18

#define MAX_WIDGETS		19



/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
   BOOLEAN_T		game_loaded;	
   BOOLEAN_T		game_saved;
   FILE_STRING_T	load_file_name;
   FILE_STRING_T	save_file_name;
   FILE			*load_file;
   FILE			*save_file;
   Widget		draw_area_widget;
   Widget		score_area_widget;
   Widget		status_area_widget;
   pointType		mouse_pick;
   GAME_S_T		data;			/* game data structure */
   GRID_S_T		grid;			/* game grid structure */
   SCORE_S_T		score;			/* game score structure */
   STATUS_S_T		status;			/* game status structure */
   ANIM_S_T		anim;			/* anim structure */
   COLORMAP_S_T		colormap;		/* color map structure */
   ICON_S_T		icons[MAX_NUM_ICONS];	/* array of icon structure */
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);
void InitDatabase(MyProgram *data);
void LoadGame(MyProgram *data);
void SaveGame(MyProgram *data);
void UpdateDisplay(MyProgram *data);
void UpdateScore(MyProgram *data);
void UpdateStatus(char *msg, MyProgram *data);

BOOLEAN_T GameIsOver(MyProgram *data);

void      HandleComputerMove(MyProgram *data);
void      HandleSkillNone(MyProgram *data);
void      MovePlayerIcon(MyProgram *data);
void      HandleWrap( int *row, int *col );

void CorrelatePick(int x, int y, MyProgram *data);
int  seed_random();
int  int_random(int min_value, int max_value);
int  ParseString(char *string, char *args[]);

void ClearScreenDisplay(Widget w);
void SetDrawColor(int idx);
void DrawGrid(MyProgram *data);
void DrawPiece(MyProgram *data, int row, int col);
void DrawScore(MyProgram *data);
void DrawHint(MyProgram *data, int row, int col);
void PopupWinner(MyProgram *data);
char *PopupFileRequest(char *message);

#endif /* _MAIN_H */
/* end of main.h */
