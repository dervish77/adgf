/* This file contains routines that are called when a button is pressed 
 * in your window or when things happen in a drawing area.
 *
 * If you add a function to this file, you should also add a function 
 * prototype for it to the callbacks.h file (unless it is an internal 
 * function, then you should just add it down below where it says 
 * "internal prototypes").
 *
 *              --  This code is under the GNU copyleft  --
 *
 *   Dominic Giampaolo
 */

#include <stdio.h>
#include <time.h>

#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"              /* where program specific stuff is defined */
#endif

#ifndef _CALLBACK_H
#include "callback.h"         /* prototypes for callback functions       */
#endif



/*
#define MOUSE_DEBUG
*/


#define KEYPRESS_DEBUG





/*  -- CALLBACK ROUTINES  --
 *
 * These functions are called when various things happen in your windows.
 * They should handle what happened and give feedback to the user.  Most
 * likely they will set options in your program (which is what the 
 * MyProgram data structure is for), and cause different things to happen, 
 * like loading and saving files, etc.
 *
 * Remember, the last argument to your callback is always a void pointer
 * to whatever data you specified when you created the widget.  You
 * must cast the pointer to be whatever type it really is.
 */


/*  file menu callbacks
 */
void file_new(Widget w, void *data)
{
   MyProgram *me=data;

   HandleNewGame(me);

   printf("New Game\n");
}

void file_load(Widget w, void *data)
{
   MyProgram *me=data;

   HandleLoadGame(me); 
} 

void file_save(Widget w, void *data)
{
   MyProgram *me=data;

   HandleSaveGame(me);
}


void file_quit(Widget w, void *data)
{
   /* Do any cleanup that is necessary for your program here */

   printf("We're out of here!!!\n");

   exit(0);
}


/*  options menu callbacks
 */

void options_single(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.network_game = FALSE;
   me->data.player_mode = PLAYER_SINGLE;
   SetFgColor(me->array_of_widgets[OPT_SINGLE_IDX], GREEN);
   SetFgColor(me->array_of_widgets[OPT_TWO_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_NET_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_DEMO_IDX], WHITE);
   printf("Single player\n");
}

void options_two(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.network_game = FALSE;
   me->data.player_mode = PLAYER_MULTI;
   SetFgColor(me->array_of_widgets[OPT_SINGLE_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_TWO_IDX], GREEN);
   SetFgColor(me->array_of_widgets[OPT_NET_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_DEMO_IDX], WHITE);
   printf("Two players\n");
}

void options_net(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.network_game = TRUE;
   me->data.player_mode = PLAYER_MULTI;
   SetFgColor(me->array_of_widgets[OPT_SINGLE_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_TWO_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_NET_IDX], GREEN);
   SetFgColor(me->array_of_widgets[OPT_DEMO_IDX], WHITE);
   printf("Two players - network game\n");

   PopupMultiPlayer(me);
}

void options_demo(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.network_game = FALSE;
   me->data.player_mode = PLAYER_DEMO;
   SetFgColor(me->array_of_widgets[OPT_SINGLE_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_TWO_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_NET_IDX], WHITE);
   SetFgColor(me->array_of_widgets[OPT_DEMO_IDX], GREEN);
   printf("Demo mode\n");

   if (me->data.player_mode == PLAYER_DEMO)
   {
      while ( GameIsOver(data) == FALSE)
      {
         HandleComputerMove(me);

         me->data.current_player = TOGGLE_PLAYER(me->data.current_player);

         UpdateDisplay(data);
      }

      PopupWinner(me);
   }
}

void options_status(Widget w, void *data)
{
   MyProgram *me=data;

   PopupStatus(me);
}


/*  skill menu callbacks
 */

void skill_1(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.skill_level = SKILL_1;
   SetFgColor(me->array_of_widgets[SKL_1_IDX], GREEN);
   SetFgColor(me->array_of_widgets[SKL_2_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_3_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_4_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_5_IDX], WHITE);
   printf("Skill 1\n");
}

void skill_2(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.skill_level = SKILL_2;
   SetFgColor(me->array_of_widgets[SKL_1_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_2_IDX], GREEN);
   SetFgColor(me->array_of_widgets[SKL_3_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_4_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_5_IDX], WHITE);
   printf("Skill 2\n");
}

void skill_3(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.skill_level = SKILL_3;
   SetFgColor(me->array_of_widgets[SKL_1_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_2_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_3_IDX], GREEN);
   SetFgColor(me->array_of_widgets[SKL_4_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_5_IDX], WHITE);
   printf("Skill 3\n");
}

void skill_4(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.skill_level = SKILL_4;
   SetFgColor(me->array_of_widgets[SKL_1_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_2_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_3_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_4_IDX], GREEN);
   SetFgColor(me->array_of_widgets[SKL_5_IDX], WHITE);
   printf("Skill 4\n");
}

void skill_5(Widget w, void *data)
{
   MyProgram *me=data;

   me->data.skill_level = SKILL_5;
   SetFgColor(me->array_of_widgets[SKL_1_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_2_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_3_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_4_IDX], WHITE);
   SetFgColor(me->array_of_widgets[SKL_5_IDX], GREEN);
   printf("Skill 5\n");
}


/*  help menu callbacks
 */

void help_about(Widget w, void *data)
{
   PopupAbout();
}

void help_menu(Widget w, void *data)
{
   PopupHelpMenu();
}

void help_keys(Widget w, void *data)
{
   PopupHelpKeys();
}

void help_rules(Widget w, void *data)
{
   PopupHelpRules();
}




/*
 * The following functions are callbacks for the drawing area widgets.
 *
 * The only required callback is redisplay().  The others are optional
 * but have been setup to be used by init_display() in main.c.
 */


/* Here is where all redrawing will take place for your program. 
 * When the window needs to be redrawn, this function will be called.
 * When your program starts up for the first time, this function will 
 * be called and you should draw anything you need to draw in here.
 */
void redisplay_score(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   DrawScore(me);
}


void redisplay(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   UpdateDisplay(me);
}


void button_down(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;

#ifdef MOUSE_DEBUG
   printf("You clicked button %d at (%d,%d)\n", which_button, x,y);
#endif

   CorrelatePick(x, y, me);
}


void button_up(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;

#ifdef MOUSE_DEBUG
   printf("You released button %d at (%d,%d)\n", which_button, x,y);
#endif

   CorrelatePick(x, y, me);
}



/*
 * The following function is called when keypresses happen in the drawing
 * area widget.
 *
 *  It is useful to know that the string returned to your program is
 * not necessarily a single ASCII character. You will get the usual
 * ASCII characters, including control characters (such as ^C or ^H).
 * But, the workstation's function keys will also be returned in a
 * string such as "F11" or "F23".  You will also get other longer
 * strings such as "Control_L", "Alt_R", or "Shift_L".  It is
 * important to understand that even if you just press the shift key to
 * get a capital letter, you will first receive the string "Shift_L"
 * or "Shift_R", then you will receive a capital letter (say, "H").
 * You should probably ignore the "Shift_L" or "Shift_R" messages (but
 * who knows, you may find some use for them).
 *
 * The argument, up_or_down, tells you whether the given key was pressed 
 * or released.  If the key was pressed down, up_or_down has a zero (0),
 * if the key was released, up_or_down contains a 1.
 *
 * NOTE WELL:
 *   The string that is returned to you can _NOT_ (I'll repeat that,
 *   can _NOT_) be modified by your program.  Got it?  Do _NOT_ modify
 *   the string.  If you want to munge with it, make a copy using
 *   strdup() or strcpy() into your own buffer space.
 */

void keypress(Widget w, char *input, int up_or_down, void *data)
{
   MyProgram *me=data;
   char *str;
   char key[20];

   if (input == NULL)
     return;

#ifdef KEYPRESS_DEBUG
   if (up_or_down == 0)
      str = "pressed";
   else
      str = "released";

   printf("You %s : <<%s>>\n", str, input);
#endif

   if (up_or_down == 0)
   {
      strcpy( &key[0], input );
      HandleKeyPress( key[0], me );
   }
}




/* Called when a DrawingArea gets mouse motion events.  The arguments
 * X and Y are the current position of the mouse in the window.
 *
 * NOTE: This routine should be _fast_ because *every* single time
 *       the mouse moves in the drawing area, this function is called. 
 *       So even if you are just moving the mouse across the drawing area,
 *       this routine is called. As it stands, it doesn't do anything.
 */
void motion(Widget w, int x, int y, void *data)
{
  MyProgram *me=data;

}


