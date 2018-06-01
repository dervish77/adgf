/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _PONG_H
#include "pong.h"
#endif


/* define widget indices */
#define FILE_MENU_IDX		0
#define OPTIONS_MENU_IDX	1
#define SKILL_MENU_IDX		2
#define HELP_MENU_IDX		3
#define DRAW_AREA_IDX		4
#define SCORE_AREA_IDX		5

#define FILE_NEW_IDX		6
#define FILE_LOAD_IDX		7
#define FILE_SAVE_IDX		8
#define FILE_ABOUT_IDX		9
#define FILE_HELP_IDX		10
#define FILE_QUIT_IDX		11

#define OPT_SINGLE_IDX		12
#define OPT_TWO_IDX		13
#define OPT_NET_IDX		14
#define OPT_DEMO_IDX		15
#define OPT_STAT_IDX		16

#define SKL_1_IDX		17
#define SKL_2_IDX		18
#define SKL_3_IDX		19
#define SKL_4_IDX		20
#define SKL_5_IDX		21

#define HELP_ABOUT_IDX		22
#define HELP_MENUS_IDX		23
#define HELP_KEYS_IDX		24
#define HELP_RULES_IDX		25

#define MAX_WIDGETS		26



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
   Widget		array_of_widgets[MAX_WIDGETS];
   pointType		mouse_pick;
   GAME_S_T		data;			/* game data structure */
   GRID_S_T		grid;			/* game grid structure */
   SCORE_S_T		score;			/* game score structure */
   HOST_S_T		host;			/* game host structure */
   SCREEN_S_T		screen;			/* game screen structure */
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);
void InitDatabase(MyProgram *data);
void LoadGame(MyProgram *data);
void SaveGame(MyProgram *data);
void UpdateDisplay(MyProgram *data);

BOOLEAN_T GameIsOver(MyProgram *data);

BOOLEAN_T HandlePlayerMove(MyProgram *data, int pr, int pc);
int       HandleGetMoveList(MyProgram *data, int row[], int col[], int max_moves);
void      HandleHint(MyProgram *data);
void      HandleSkillNone(MyProgram *data);
void      HandleSkillRandom(MyProgram *data);
int       PickMinDistance( float dist[], int count );
float     CalcDistance2Corner(MyProgram *data, int r, int c);
void      HandleSkillCorners(MyProgram *data);
void      HandleSkillMaxFlip(MyProgram *data);
void      HandleSkillAI(MyProgram *data);
void      HandleComputerMove(MyProgram *data);
void      HandleFlip(MyProgram *data, int pr, int pc);
int       HandleCount(MyProgram *data, int pr, int pc);

BOOLEAN_T ScanBoard(MyProgram *data, int sr, int sc);
BOOLEAN_T ScanNeighbors(MyProgram *data, int sr, int sc, NEIGHBOR_A_T nba);
BOOLEAN_T ScanRow(MyProgram *data, int sr, int sc, DIRECTION_T dir);
BOOLEAN_T ScanColumn(MyProgram *data, int sr, int sc, DIRECTION_T dir);
BOOLEAN_T ScanDiag(MyProgram *data, int sr, int sc, DIRECTION_T dir);

void FlipRow(MyProgram *data, int pr, int pc, DIRECTION_T dir);
void FlipColumn(MyProgram *data, int pr, int pc, DIRECTION_T dir);
void FlipDiag(MyProgram *data, int pr, int pc, DIRECTION_T dir);

int  CountRow(MyProgram *data, int pr, int pc, DIRECTION_T dir);
int  CountColumn(MyProgram *data, int pr, int pc, DIRECTION_T dir);
int  CountDiag(MyProgram *data, int pr, int pc, DIRECTION_T dir);

void CorrelatePick(int x, int y, MyProgram *data);
int  int_random(int min_value, int max_value);
int  ParseString(char *string, char *args[]);

void ClearScreenDisplay(Widget w);
void SetDrawColor(int idx);
void DrawGrid(MyProgram *data);
void DrawPiece(MyProgram *data, int row, int col);
void DrawScore(MyProgram *data);
void DrawHint(MyProgram *data, int row, int col);
void PopupWinner(MyProgram *data);
void PopupNoMoveFound(MyProgram *data);
void PopupIllegalMove(MyProgram *data);
char *PopupFileRequest(char *message);

void HandleServerOpen(MyProgram *data);
void HandleClientOpen(MyProgram *data);
int  CheckForNetwork();


#endif /* _MAIN_H */
/* end of main.h */
