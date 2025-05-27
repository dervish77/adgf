/*------------------------
   MAIN.H -- Othello game for Win95
  ------------------------*/

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _OTHELLO_H
#include "othello.h"
#endif


/* define widget indices */

#define IDM_NEW      1
#define IDM_LOAD     2
#define IDM_SAVE     3
#define IDM_EXIT     4

#define IDM_UNDO    10
#define IDM_CUT     11
#define IDM_COPY    12
#define IDM_PASTE   13
#define IDM_DEL     14

#define IDM_SINGLE   20
#define IDM_MULTI    21
#define IDM_NETWORK  22
#define IDM_DEMO     23

#define IDM_NOSKILL  30
#define IDM_RANDOM   31
#define IDM_CORNERS  32
#define IDM_MAXFLIPS 33
#define IDM_AI       34

#define IDM_BOARD8   40
#define IDM_BOARD10  41
#define IDM_BOARD12  42

#define IDM_HINT     50
#define IDM_PASS     51
#define IDM_HELP     52
#define IDM_HELPKEY  53
#define IDM_HELPRULE 54
#define IDM_STATUS   55
#define IDM_ABOUT    56


/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct _MyProgram
{
   BOOLEAN_T		game_loaded;	
   BOOLEAN_T		game_saved;
   FILE_STRING_T	load_file_name;
   FILE_STRING_T	save_file_name;
   FILE			*load_file;
   FILE			*save_file;
   pointType		mouse_pick;
   GAME_S_T		data;			/* game data structure */
   GRID_S_T		grid;			/* game grid structure */
   SCORE_S_T		score;			/* game score structure */
   HOST_S_T		host;			/* game host structure */
   SCREEN_S_T		screen;			/* game screen structure */
} MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);
void InitScreen(MyProgram *data);
void InitDatabase(MyProgram *data);
void LoadGame(MyProgram *data);
void SaveGame(MyProgram *data);
void UpdateDisplay(MyProgram *data);
void HandleBoard(MyProgram *data, int size);
void HandleNewGame(MyProgram *me);

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

void SetDrawColor(int idx);
#if 0
void DrawGrid(HDC hdc, MyProgram *data);
void DrawHint( HDC hdc, MyProgram *data, int r, int c );
#endif
void DrawPiece(MyProgram *data, int row, int col);
void DrawScore(MyProgram *data);

#if 0
void PopupWinner(HWND hwnd, MyProgram *data);
void PopupNoMoveFound(HWND hwnd, MyProgram *data);
#endif
void PopupIllegalMove(MyProgram *data);
char *PopupFileRequest(char *message);

void HandleServerOpen(MyProgram *data);
void HandleClientOpen(MyProgram *data);
int  CheckForNetwork();

#endif /* _MAIN_H */
/* end of main.h */
