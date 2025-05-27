/***********************************************************************

  Drawing related functions using the LIBSX library.

   File:  	drwlibsx.c

   Author: 	Brian Lingard

   Date:	03/29/96

   Revisions:
	0.3	04/03/96	added demo mode
	0.0	03/29/96	Originated

***********************************************************************/



/* include necessary files */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "libsx.h"             /* should come first, defines libsx stuff  */

#ifndef _MAIN_H
#include "main.h"              /* where program specific stuff is defined */
#endif

#ifndef _CALLBACK_H
#include "callback.h"          /* prototypes for callback functions       */
#endif


/*  define global default color array 
 */
COLOR_RGB_T default_colors[MAX_COLOR_MAP] = { 0,   255,   0,
					      41,  158, 147,
					      63,  172, 243, 
					      61,  108, 255,
					      0,   0,   255,
					      185, 200, 162,
				              182, 123, 74,
					      255, 88,  112 };


/******************************************************************************
*  ClearScreenDisplay - clears the currently active display                   *
******************************************************************************/
void
ClearScreenDisplay(Widget w)
{
   SetDrawArea(w);
   ClearDrawArea();             
}


/******************************************************************************
*  SetDrawColor - sets current drawing color of the active display to the     *
*                 index specified                                             *
******************************************************************************/
void
SetDrawColor(int idx)	/* NOTE:  idx is libsx color index */
{
   SetColor(idx);
}


/******************************************************************************
*  SetCurrentColor - sets current drawing color to the index specified        *
******************************************************************************/
void
SetCurrentColor(int idx, MyProgram *data)
{
   int color_idx;

   color_idx = data->colormap.indexes[idx];

   SetDrawColor(color_idx);
}


/******************************************************************************
*  UpdateColor - updates specified entry in the colormap with modified color  *
******************************************************************************/
void
UpdateColor(int idx, COLOR_RGB_T color, MyProgram *data)
{
   int c_index;

   c_index = GetRGBColor( (int)color[R_IDX], 
				(int)color[G_IDX], 
				(int)color[B_IDX] );

   if (c_index == -1)
   {
      fprintf(stderr, "allocation of RGB color %d,%d,%d failed!\n",
				color[R_IDX], 
				color[G_IDX], 
				color[B_IDX] );
      exit(1);
   }

   data->colormap.map[idx][R_IDX] = color[R_IDX];
   data->colormap.map[idx][G_IDX] = color[G_IDX];
   data->colormap.map[idx][B_IDX] = color[B_IDX];

   data->colormap.indexes[idx] = c_index;
}


/******************************************************************************
*  InitColorMap - initializes the color map table to a set of default colors  *
*                 and sets the current drawing color to default.              *
******************************************************************************/
void
InitColorMap(MyProgram *data)
{
   int c;
   
   fprintf(stdout, "Initializing color map...\n");

   for (c = 0; c < MAX_COLOR_MAP; c++)
   {
      UpdateColor(c, default_colors[c], data);
   }

   SetCurrentColor(DEFAULT_COLOR, data);
}


/******************************************************************************
*  DrawIcon - draws game icons                                               *
******************************************************************************/
void
DrawIcon(MyProgram *data, ICON_S_T *icon_ptr, int r, int c)
{
   int 		tlx, tly;	/* top left of grid cell */
   int  	x, y;           /* pixel coordinate */
   int  	u, v;           /* loop indices */


   /*  set current drawing area
    */
   SetDrawArea(data->draw_area_widget);

   /*  set top left grid cell
    */
   tlx = data->grid.top_left[r][c].x;
   tly = data->grid.top_left[r][c].y;

/*
printf("Drawing icon %d,%d at %d,%d\n", r, c, tlx, tly);
*/

   /*  draw pixmap 
    */ 
   for (v = 0; v < data->grid.grid_size.y; v++)
   {
      y = tly + v;

      for (u = 0; u < data->grid.grid_size.x; u++)
      {
         x = tlx + u;
         SetCurrentColor( icon_ptr->pixmap[v][u], data );
         DrawPixel( x, y );
      }
   }
}


/******************************************************************************
*  DrawScore - updates displayed score                                        *
******************************************************************************/
void
DrawScore(MyProgram *data)
{
   char 	string[20];	/* score string */

   ClearScreenDisplay(data->score_area_widget);
   SetLineWidth(1);
   SetDrawColor(WHITE);

   /*  display score 
    */
   sprintf( string, "Health - %06d", data->score.health );
   DrawText( string, data->score.health_label.x, data->score.health_label.y );

   /*  display health 
    */
   sprintf( string, "Water - %03d", data->score.water );
   DrawText( string, data->score.water_label.x, data->score.water_label.y );

   /*  display ammo 
    */
   sprintf( string, "Food - %03d", data->score.food );
   DrawText( string, data->score.food_label.x, data->score.food_label.y );
}


/******************************************************************************
*  DrawStatus - updates displayed status                                      *
******************************************************************************/
void
DrawStatus(MyProgram *data)
{
   char string[128];	/* score string */

   ClearScreenDisplay(data->status_area_widget);
   SetLineWidth(1);
   SetDrawColor(GREEN);

   /*  display score 
    */
   sprintf( string, "%s", data->status.msg );
   DrawText( string, data->status.status_label.x, data->status.status_label.y );
}


/******************************************************************************
*  PopupQuit                                                                  *
******************************************************************************/
void
PopupQuit(void)
{
   int 		okay;
   BUFFER_T	string;

   sprintf(string, "Quit the game?\n\n");

   okay = GetYesNo(string);  

   if (okay)
   {
      exit(0);
   }
}


/******************************************************************************
*  PopupWinner - pops up a dialog indicating the winner of the game           *
******************************************************************************/
void
PopupWinner(MyProgram *data)
{
   int 		okay;
   BUFFER_T	string;


   /*  popup winning player message
    */
   sprintf(string, 
	"Player %d Wins!!\n\nselect okay for new game", 
	data->data.winning_player);

   okay = GetYesNo(string);  


   /*  start up new game is user selected okay 
    */
   if (okay)
   {
      InitDatabase(data);
      UpdateDisplay(data);
      UpdateScore(data);
   }
}


/******************************************************************************
*  PopupFileRequest                                                           *
******************************************************************************/
char *PopupFileRequest(char *message)
{
   char *result;

   result = GetString( message, NULL );

   return(result);
}


/******************************************************************************
*  PopupMultiPlayer                                                           *
******************************************************************************/
void
PopupMultiPlayer(MyProgram *data)
{
   char *login;
   char *ip;

   login = GetString( "Enter your login name\n", NULL );
   if (login == (char *) NULL)
      return;

   ip = GetString( "Enter IP address of Survival server\n", NULL );
   if (ip == (char *) NULL)
      return;

   data->data.player_mode = PLAYER_MULTI;

   printf("Logging into %s as %s\n", ip, login);

}


/******************************************************************************
*  PopupGameOver                                                              *
******************************************************************************/
void
PopupGameOver(MyProgram *data)
{
   int okay;
   BUFFER_T string;

   sprintf(string, 
	"You're dead!!\n\nHit Okay to start new game\n\n");

   okay = GetYesNo(string);

   if (okay)
   {
      HandleNewGame( data ); 
   } 
}


/******************************************************************************
*  PopupAbout                                                                 *
******************************************************************************/
void
PopupAbout(void)
{
   int okay;
   BUFFER_T string;

   sprintf(string, 
	"    Survival\n\nby Brian Lingard\n\n   version %1.1f\n\n", 
	VERSION);

   okay = GetYesNo(string);  
}


/******************************************************************************
*  PopupHelpMenu                                                              *
******************************************************************************/
void
PopupHelpMenu(void)
{
   int okay;
   char string[50];
   char help_text[1024];

   sprintf(help_text, "HELP Survival - Menus\n");

   sprintf(string, "---------------------\n\n");
   strcat(help_text, string); 

   sprintf(string,"File->New Game         - start new game\n");
   strcat(help_text, string); 

   sprintf(string,"File->Load Game        - load a saved game\n");
   strcat(help_text, string); 

   sprintf(string,"File->Save Game        - save game to file\n");
   strcat(help_text, string); 

   sprintf(string,"File->Quit             - quit current game\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Single Player - picks one player mode\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Multi Player  - setup for multi-player game\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Demo Mode     - picks demo mode\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Status        - shows game status\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->About            - about starfire\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->Menu Help        - help using menu items\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->Keys Help        - help using keys\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->Rules            - help on game rules\n"); 
   strcat(help_text, string); 

   sprintf(string,"\n"); 
   strcat(help_text, string); 

   okay = GetYesNo(help_text);
}


/******************************************************************************
*  PopupHelpKeys                                                              *
******************************************************************************/
void
PopupHelpKeys(void)
{
   int okay;
   char string[50];
   char help_text[1024];

   sprintf(help_text, "HELP Survival - Keys\n");

   sprintf(string, "--------------------\n\n");
   strcat(help_text, string); 

   sprintf(string,"Up arrow        - move up\n"); 
   strcat(help_text, string); 

   sprintf(string,"Down arrow      - move down\n"); 
   strcat(help_text, string); 

   sprintf(string,"Left arrow      - move left\n"); 
   strcat(help_text, string); 

   sprintf(string,"Right arrow     - move right\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"n               - new game\n"); 
   strcat(help_text, string); 

   sprintf(string,"l               - load game\n"); 
   strcat(help_text, string); 

   sprintf(string,"s               - save game\n"); 
   strcat(help_text, string); 

   sprintf(string,"q               - quit game\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"m               - start multiplayer game\n"); 
   strcat(help_text, string); 

   sprintf(string,"t               - send taunt message\n");
   strcat(help_text, string);

   sprintf(string,"\n"); 
   strcat(help_text, string); 

   okay = GetYesNo(help_text);
}


/******************************************************************************
*  PopupHelpRules                                                             *
******************************************************************************/
void
PopupHelpRules(void)
{
   int okay;
   char string[50];
   char help_text[1024];

   sprintf(help_text, "HELP Survival - Rules\n");

   sprintf(string, "---------------------\n\n");
   strcat(help_text, string); 

   sprintf(string,"\n"); 
   strcat(help_text, string); 

   okay = GetYesNo(help_text);
}


/******************************************************************************
*  PopupStatus                                                                *
******************************************************************************/
void
PopupStatus(void *data)
{
   MyProgram *me=data;
   int okay;
   char status[512], string[50];

   printf("status\n");

   sprintf(status, "Current Status\n--------------\n");

   sprintf(string, "\nLoad File = %s\n", me->load_file_name);
   strcat(status, string);

   sprintf(string, "Save File = %s\n", me->save_file_name);
   strcat(status, string);

   if (me->data.player_mode == PLAYER_SINGLE)
      sprintf(string, "\nMode = Single Player\n");
   else if (me->data.player_mode == PLAYER_MULTI)
      sprintf(string, "\nMode = Multi-Player\n");
   else if (me->data.player_mode == PLAYER_DEMO)
      sprintf(string, "\nMode = Demo\n");
   else
      sprintf(string, "\nMode = \n");
   strcat(status, string);

   if (me->data.skill_level == SKILL_NONE)
      sprintf(string, "Skill = None\n");
   else
      sprintf(string, "Skill = \n");
   strcat(status, string);

   sprintf(string, "Current player = %d\n", me->data.current_player);
   strcat(status, string);

   sprintf(string, "Health = %d\n", me->score.health);
   strcat(status, string);

   sprintf(string, "Water  = %d\n", me->score.water);
   strcat(status, string);

   sprintf(string, "Food  = %d\n", me->score.food);
   strcat(status, string);

   sprintf(string, "\n");
   strcat(status, string);

   okay = GetYesNo(status);  
}



/* end of drwlibsx.c */
