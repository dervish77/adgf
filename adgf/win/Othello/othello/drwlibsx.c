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
*  DrawGrid - draws grid in working draw area                                 *
******************************************************************************/
void
DrawGrid(MyProgram *data)
{
   int 	i, j;			/* loop indices */
   int 	startx, starty;		/* starting x,y coordinates for grid lines */


   /*  set current drawing area and foreground color
    */
   SetDrawArea(data->draw_area_widget);
   SetDrawColor(BLACK);
   SetLineWidth(1);


   /*  draw vertical grid lines 
    */
   startx = 0;

   for (i = 0; i < data->screen.max_grid_col; i++)
   {
      if ( startx < (data->screen.screen_x_size - 1) )
      {
         DrawLine(startx, 0, startx, data->screen.screen_y_size);
      }

      startx += data->grid.size.x;	/* increment by grid size in x */
   }


   /*  draw horizontal grid lines 
    */
   starty = 0;

   for (j = 0; j < data->screen.max_grid_row; j++)
   {
      if ( starty < (data->screen.screen_y_size - 1) )
      {
         DrawLine(0, starty, data->screen.screen_x_size, starty);
      }

      starty += data->grid.size.y;	/* increment by grid size in y*/
   }
}


/******************************************************************************
*  DrawPiece - draws players game piece                                       *
******************************************************************************/
void
DrawPiece(MyProgram *data, int row, int col)
{
   int 	x, y;		/* top left of bounding box of circle */
   int 	w, h;		/* width and height of bounding box if circle */


   /*  set current drawing area and foreground color
    */
   SetDrawArea(data->draw_area_widget);
   SetLineWidth(1);

   /*  set drawing color based on player's piece at row, col
    */
   if (data->data.board[row][col] == PIECE_PLAYER_1)
   {
      SetDrawColor(WHITE);
   }
   else
   {
      SetDrawColor(BLACK);
   }


   /*  set top left of circle bounding box
    */
   x = data->grid.top_left[row][col].x + 2;
   y = data->grid.top_left[row][col].y + 2;


   /*  set size of circle bounding box
    */
   w = h = data->screen.piece_diameter;


   /*  draw piece as a filled circle
    */
   DrawFilledArc(x, y, w, h, 0, 360);
}


/******************************************************************************
*  DrawScore - updates displayed score for both players                       *
******************************************************************************/
void
DrawScore(MyProgram *data)
{
   char 	score[20];	/* score string */
   int 		w, h;		/* width and height of highlight box */


   ClearScreenDisplay(data->score_area_widget);
   SetLineWidth(1);

   /*  display player 1 score position 
    */
   SetDrawColor(WHITE);
   sprintf(score, "Player 1 - %03d", data->score.player1_score);
   DrawText( score, data->score.plyr1_label.x, data->score.plyr1_label.y );


   /*  display player 2 score position 
    */
   SetDrawColor(WHITE);
   sprintf(score, "Player 2 - %03d", data->score.player2_score);
   DrawText( score, data->score.plyr2_label.x, data->score.plyr2_label.y );


   /*  display current player's highlight bounding box 
    */
   SetDrawColor(RED);
   w = (data->screen.score_x_size / 2) - 10;
   h = data->screen.score_y_size - 10;

   if (data->data.current_player == PIECE_PLAYER_1)
   {
      DrawBox( data->score.box1_top_left.x, data->score.box1_top_left.y, w, h);
   }
   else
   {
      DrawBox( data->score.box2_top_left.x, data->score.box2_top_left.y, w, h);
   }
}


/******************************************************************************
*  DrawHint - shows a hint to current player                                  *
******************************************************************************/
void
DrawHint(MyProgram *data, int row, int col)
{
   int 	x, y;		/* top left of bounding box of circle */
   int 	w, h;		/* width and height of bounding box if circle */
   int  d;

   SetDrawArea(data->draw_area_widget);
   SetLineWidth(2);

   if (data->data.current_player == PIECE_PLAYER_1)
   {
      SetDrawColor(WHITE);
   }
   else
   {
      SetDrawColor(BLACK);
   }

   /*  set top left of circle bounding box
    */
   x = data->grid.top_left[row][col].x + 2;
   y = data->grid.top_left[row][col].y + 2;

   /*  set size of circle bounding box
    */
   w = h = data->screen.piece_diameter;

   /*  draw hint piece as an outlined circle
    */
   DrawArc(x, y, w, h, 0, 360);
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
*  PopupNoMoveFound - pops up a dialog indicating no legal move found         *
******************************************************************************/
void
PopupNoMoveFound(MyProgram *data)
{
   int 		okay;
   BUFFER_T	string;

   sprintf(string, 
	"No Move Found for Player %d !!\n\n", 
	data->data.current_player);

   okay = GetYesNo(string);
}


/******************************************************************************
*  PopupIllegalMove - pops up a dialog indicating illegal move                *
******************************************************************************/
void
PopupIllegalMove(MyProgram *data)
{
   int 		okay;
   BUFFER_T	string;

   sprintf(string, "Illegal Move !!\n\n");
   okay = GetYesNo(string);
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
	"    Othello\n\nby Brian Lingard\n\n   version %1.1f\n\n", 
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

   sprintf(help_text, "HELP Othello - Menus\n");

   sprintf(string, "--------------------\n\n");
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

   sprintf(string,"Options->Two Players   - picks two player mode\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Demo Mode     - picks demo mode\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Board 8x8     - picks board size 8x8\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Board 10x10   - picks board size 10x10\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Board 12x12   - picks board size 12x12\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Status        - shows game status\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Skill->No Skill        - computer takes first move\n"); 
   strcat(help_text, string); 

   sprintf(string,"Skill->Random          - computer takes random move\n"); 
   strcat(help_text, string); 
 
   sprintf(string,"Skill->Corners         - computer moves toward corner\n"); 
   strcat(help_text, string); 

   sprintf(string,"Skill->Max Flips       - computer tries for max flips\n");
   strcat(help_text, string);

   sprintf(string,"Skill->AI              - computer uses AI\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->About            - about starfire\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->Menu Help        - help using menu items\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->Rules            - help on game rules\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Pass                   - current player passes\n"); 
   strcat(help_text, string); 

   sprintf(string,"Hint                   - current player gets a hint\n\n"); 
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

   sprintf(help_text, "HELP Othello - Keys\n");

   sprintf(string, "--------------------\n\n");
   strcat(help_text, string); 

   sprintf(string,"n         - new game\n"); 
   strcat(help_text, string); 

   sprintf(string,"l         - load game\n"); 
   strcat(help_text, string); 

   sprintf(string,"s         - save game\n"); 
   strcat(help_text, string); 

   sprintf(string,"q         - quit game\n"); 
   strcat(help_text, string); 

   sprintf(string,"x         - exit game\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"h         - show hint\n"); 
   strcat(help_text, string); 

   sprintf(string,"p         - pass on turn\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"m         - start multiplayer game\n"); 
   strcat(help_text, string); 

   sprintf(string,"t         - send taunt message\n");
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
   char help_text[512];

   sprintf(help_text, "HELP Othello - Rules\n");

   sprintf(string, "--------------------\n\n");
   strcat(help_text, string); 

   sprintf(string,"\n"); 
   strcat(help_text, string); 

   okay = GetYesNo(help_text);
}


/******************************************************************************
*  PopupStatus                                                                *
******************************************************************************/
void
PopupStatus(MyProgram *me)
{
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
      sprintf(string, "\nMode = Two Players\n");
   else if (me->data.player_mode == PLAYER_DEMO)
      sprintf(string, "\nMode = Demo\n");
   else
      sprintf(string, "\nMode = \n");
   strcat(status, string);

   if (me->data.skill_level == SKILL_NONE)
      sprintf(string, "Skill = None\n");
   else if (me->data.skill_level == SKILL_RANDOM)
      sprintf(string, "Skill = Random\n");
   else if (me->data.skill_level == SKILL_CORNERS)
      sprintf(string, "Skill = Corners\n");
   else if (me->data.skill_level == SKILL_MAXFLIP)
      sprintf(string, "Skill = Max Flips\n");
   else if (me->data.skill_level == SKILL_AI)
      sprintf(string, "Skill = AI\n");
   else
      sprintf(string, "Skill = \n");
   strcat(status, string);

   sprintf(string, "Current player = %d\n", me->data.current_player);
   strcat(status, string);

   sprintf(string, "Player 1 count = %d\n", me->score.player1_score);
   strcat(status, string);

   sprintf(string, "Player 1 color = %d\n", me->score.player1_color);
   strcat(status, string);

   sprintf(string, "Player 2 count = %d\n", me->score.player2_score);
   strcat(status, string);

   sprintf(string, "Player 2 color = %d\n", me->score.player2_color);
   strcat(status, string);

   sprintf(string,"\n"); 
   strcat(status, string); 

   okay = GetYesNo(status); 
}


/******************************************************************************
*  PopupMultiPlayer                                                           *
******************************************************************************/
void
PopupMultiPlayer(MyProgram *data)
{
   char string[50];
   char *login;
   char *ip;
   int okay;


   if ( !CheckForNetwork() )
   {
      sprintf(string, "Sorry, no network support in this version of Othello.\n\n");
      okay = GetYesNo(string);
      return;
   }

   sprintf(string, "Are we the server?\n\n");
   okay = GetYesNo(string);

   if ( okay )
   {
      data->host.client = FALSE;
      data->host.server = TRUE;
      printf("We are the server\n");

      printf("Opening server port...\n");

      HandleServerOpen(data);
   }
   else 
   {
      data->host.client = TRUE;
      data->host.server = FALSE;
      printf("We are the client\n");

      login = GetString( "Enter your login name\n", NULL );
      if (login == (char *) NULL)
         return;

      ip = GetString( "Enter IP address of Othello server\n", NULL );
      if (ip == (char *) NULL)
         return;

      printf("Logging into %s as %s\n", ip, login);

      strcpy( data->host.login_name, login );
      strcpy( data->host.remote_host_ip, ip );

      HandleClientOpen(data);
   }
}


/* end of drwlibsx.c */
