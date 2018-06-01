/* This is the main body of the program.  It is just a simple skeleton
 * and should be fleshed out as desired.  Mainly what you'll do to flesh 
 * it out is to edit the data structure defined in main.h so that it contains 
 * the information your program needs.  Then modify init_display() to create
 * the interface you want, and then just write the associated callback 
 * routines that are driven by the display.  Easy, huh?
 *
 *               --  This code is under the GNU copyleft  --
 *
 *   Dominic Giampaolo
 *   dbg@sgi.com
 */

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



void main(int argc, char **argv)
{
  MyProgram mydata;

  InitScreen(&mydata);
  InitDatabase(&mydata);

  init_display(argc, argv, &mydata);  /* setup the display */

  MainLoop();                         /* go right into the main loop */
}



/* This function sets up the display.  For any kind of a real program, 
 * you'll probably want to save the values returned by the MakeXXX calls
 * so that you have a way to refer to the display objects you have 
 * created (like if you have more than one drawing area, and want to
 * draw into both of them).
 */

void init_display(int argc, char **argv, MyProgram *me)
{
  Widget w[MAX_WIDGETS];
  int i;


  if (OpenDisplay(argc, argv) == FALSE)
    return;

  /*  declare all the widgets
   */
  w[FILE_MENU_IDX] = MakeMenu("  File  ");
  w[OPTIONS_MENU_IDX] = MakeMenu(" Options ");
  w[SKILL_MENU_IDX] = MakeMenu(" Skill  ");
  w[HELP_MENU_IDX] = MakeMenu("  Help  ");
  w[LABEL1_IDX] = MakeLabel("  ------  ");
  w[PASS_IDX] = MakeButton("  Pass  ", pass_button, me);
  w[LABEL2_IDX] = MakeLabel("  ------  ");
  w[HINT_IDX] = MakeButton("  Hint  ", hint_button, me);
  w[DRAW_AREA_IDX] = MakeDrawArea(SCREEN_X_SIZE, SCREEN_Y_SIZE, redisplay, me);
  w[SCORE_AREA_IDX] = MakeDrawArea(SCORE_X_SIZE, SCORE_Y_SIZE, redisplay_score, me);


  /*  add menu items to 'file' menu
   */
  w[FILE_NEW_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "New Game", file_new, me);
  w[FILE_LOAD_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Load Game ...", file_load, me);
  w[FILE_SAVE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save Game ...", file_save, me);
  w[FILE_QUIT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Quit", file_quit, me);


  /*  add menu items to 'options' menu
   */
  w[OPT_SINGLE_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Single Player", options_single, me);
  w[OPT_TWO_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Two Players", options_two, me);
  w[OPT_NET_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Network Game", options_net, me);
  w[OPT_DEMO_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Demo Mode", options_demo, me);
  w[OPT_BOARD8_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Board 8x8", options_board8, me);
  w[OPT_BOARD10_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Board 10x10", options_board10, me);
  w[OPT_BOARD12_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Board 12x12", options_board12, me);
  w[OPT_STAT_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Status", options_status, me);


  /*  add menu items to 'skill' menu
   */
  w[SKL_NONE_IDX] = MakeMenuItem(w[SKILL_MENU_IDX], "No Skill", skill_none, me);
  w[SKL_RANDOM_IDX] = MakeMenuItem(w[SKILL_MENU_IDX], "Random", skill_random, me);
  w[SKL_CORNERS_IDX] = MakeMenuItem(w[SKILL_MENU_IDX], "Corners", skill_corners, me);
  w[SKL_MAXFLIP_IDX] = MakeMenuItem(w[SKILL_MENU_IDX], "Max Flips", skill_maxflip, me);
  w[SKL_AI_IDX] = MakeMenuItem(w[SKILL_MENU_IDX], "AI", skill_ai, me);

  /*  add menu items to 'help' menu
   */
  w[HELP_ABOUT_IDX] = MakeMenuItem(w[HELP_MENU_IDX], "About ...", help_about, me);
  w[HELP_MENUS_IDX] = MakeMenuItem(w[HELP_MENU_IDX], "Menu Help ...", help_menu, me);
  w[HELP_KEYS_IDX] = MakeMenuItem(w[HELP_MENU_IDX], "Keys Help ...", help_keys, me);
  w[HELP_RULES_IDX] = MakeMenuItem(w[HELP_MENU_IDX], "Rules Help ...", help_rules, me);



  /*  callbacks for draw area 
   */
  SetButtonDownCB(w[DRAW_AREA_IDX], button_down);
  SetButtonUpCB(w[DRAW_AREA_IDX], button_up);
  SetMouseMotionCB(w[DRAW_AREA_IDX], motion);
  SetKeypressCB(w[DRAW_AREA_IDX], keypress);


  /*  set all the widgets' positions
   */
  SetWidgetPos(w[OPTIONS_MENU_IDX], PLACE_RIGHT, w[FILE_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[SKILL_MENU_IDX], PLACE_RIGHT, w[OPTIONS_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[HELP_MENU_IDX], PLACE_RIGHT, w[SKILL_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LABEL1_IDX], PLACE_RIGHT, w[HELP_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[PASS_IDX], PLACE_RIGHT, w[LABEL1_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LABEL2_IDX], PLACE_RIGHT, w[PASS_IDX], NO_CARE, NULL);
  SetWidgetPos(w[HINT_IDX], PLACE_RIGHT, w[LABEL2_IDX], NO_CARE, NULL);
  SetWidgetPos(w[SCORE_AREA_IDX], PLACE_UNDER, w[FILE_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[DRAW_AREA_IDX], PLACE_UNDER, w[SCORE_AREA_IDX], NO_CARE, NULL);


  /* This call actually causes the whole thing to be displayed on the
   * screen.  You have to call this function before doing any drawing
   * into the window.
   */
  ShowDisplay();

  
  /* Get standard (red, blue, green, yellow, black, white) colors for
   * drawing stuff.  Check libsx.h for more info. 
   */
  GetStandardColors();
 
  SetFgColor(w[FILE_MENU_IDX], WHITE);
  SetBgColor(w[FILE_MENU_IDX], BLUE);

  SetFgColor(w[OPTIONS_MENU_IDX], WHITE);
  SetBgColor(w[OPTIONS_MENU_IDX], BLUE);

  SetFgColor(w[SKILL_MENU_IDX], WHITE);
  SetBgColor(w[SKILL_MENU_IDX], BLUE);

  SetFgColor(w[HELP_MENU_IDX], WHITE);
  SetBgColor(w[HELP_MENU_IDX], BLUE);

  SetFgColor(w[LABEL1_IDX], BLACK);

  SetFgColor(w[PASS_IDX], WHITE);
  SetBgColor(w[PASS_IDX], BLUE);

  SetFgColor(w[LABEL2_IDX], BLACK);

  SetFgColor(w[HINT_IDX], WHITE);
  SetBgColor(w[HINT_IDX], BLUE);

  SetFgColor(w[DRAW_AREA_IDX], BLACK);
  SetBgColor(w[DRAW_AREA_IDX], GREEN);

  SetFgColor(w[SCORE_AREA_IDX], WHITE);
  SetBgColor(w[SCORE_AREA_IDX], BLACK);

  SetFgColor(w[FILE_NEW_IDX], WHITE);
  SetFgColor(w[FILE_LOAD_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_IDX], WHITE);
  SetFgColor(w[FILE_QUIT_IDX], WHITE);
  SetBgColor(w[FILE_NEW_IDX], BLUE);

  SetFgColor(w[OPT_SINGLE_IDX], GREEN);
  SetFgColor(w[OPT_TWO_IDX], WHITE);
  SetFgColor(w[OPT_NET_IDX], WHITE);
  SetFgColor(w[OPT_DEMO_IDX], WHITE);
  SetFgColor(w[OPT_BOARD8_IDX], WHITE);
  SetFgColor(w[OPT_BOARD10_IDX], WHITE);
  SetFgColor(w[OPT_BOARD12_IDX], GREEN);
  SetFgColor(w[OPT_STAT_IDX], WHITE);
  SetBgColor(w[OPT_SINGLE_IDX], BLUE);

  SetFgColor(w[SKL_NONE_IDX], GREEN);
  SetFgColor(w[SKL_RANDOM_IDX], WHITE);
  SetFgColor(w[SKL_CORNERS_IDX], WHITE);
  SetFgColor(w[SKL_MAXFLIP_IDX], WHITE);
  SetFgColor(w[SKL_AI_IDX], WHITE);
  SetBgColor(w[SKL_NONE_IDX], BLUE);

  SetFgColor(w[HELP_ABOUT_IDX], WHITE);
  SetFgColor(w[HELP_MENUS_IDX], WHITE);
  SetFgColor(w[HELP_KEYS_IDX], WHITE);
  SetFgColor(w[HELP_RULES_IDX], WHITE);
  SetBgColor(w[HELP_ABOUT_IDX], BLUE);

  /*  save drawing area widget 
   */
  me->draw_area_widget = w[DRAW_AREA_IDX];
  me->score_area_widget = w[SCORE_AREA_IDX];

  for (i = 0; i < MAX_WIDGETS; i++)
  {
     me->array_of_widgets[i] = w[i];
  }


  /* If you wanted to get all the colors in the colormap, you'd do the
   * following :
   *
   *    GetAllColors();
   *    SetColorMap(GREY_SCALE_1);
   *
   * You can wait to do it till later if you want.  There's no need 
   * to do it here if you don't need to (because it wacks out the
   * colormap).  
   */
}

