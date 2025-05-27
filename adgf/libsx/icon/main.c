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

#ifndef _CALLBCKS_H
#include "callbcks.h"         /* prototypes for callback functions       */
#endif



void main(int argc, char **argv)
{
  MyProgram mydata;

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
  int c;

  Widget w[MAX_WIDGETS];


  if (OpenDisplay(argc, argv) == FALSE)
    return;

  /*  declare all the widgets
   */
  w[FILE_MENU_IDX] = MakeMenu("    File    ");
  w[OPTIONS_MENU_IDX] = MakeMenu(" Commands ");
  w[LABEL_IDX] = MakeLabel("  Welcome to Icon Edit - ver 1.0");
  w[DRAW_AREA_IDX] = MakeDrawArea(SCREEN_X_SIZE, SCREEN_Y_SIZE, redisplay, me);

  w[COLOR_BUTTON_01_IDX] = MakeButton(COLOR_BUTTON_LABEL, color_1_sel, me);
  w[COLOR_BUTTON_02_IDX] = MakeButton(COLOR_BUTTON_LABEL, color_2_sel, me);
  w[COLOR_BUTTON_03_IDX] = MakeButton(COLOR_BUTTON_LABEL, color_3_sel, me);
  w[COLOR_BUTTON_04_IDX] = MakeButton(COLOR_BUTTON_LABEL, color_4_sel, me);
  w[COLOR_BUTTON_05_IDX] = MakeButton(COLOR_BUTTON_LABEL, color_5_sel, me);
  w[COLOR_BUTTON_06_IDX] = MakeButton(COLOR_BUTTON_LABEL, color_6_sel, me);
  w[COLOR_BUTTON_07_IDX] = MakeButton(COLOR_BUTTON_LABEL, color_7_sel, me);
  w[COLOR_BUTTON_08_IDX] = MakeButton(COLOR_BUTTON_LABEL, color_8_sel, me);

  w[PAD_LABEL_1_IDX] = MakeLabel(COLOR_BUTTON_LABEL);
  w[CURRENT_COLOR_LABEL_IDX] = MakeLabel("Current Color");
  w[CURRENT_DRAW_COLOR_IDX] = MakeButton(COLOR_BUTTON_LABEL, NULL, me);

  w[PAD_LABEL_2_IDX] = MakeLabel(COLOR_BUTTON_LABEL);
  w[EDIT_DRAW_COLOR_IDX] = MakeButton("Edit Color", edit_color, me);

  w[PAD_LABEL_3_IDX] = MakeLabel(COLOR_BUTTON_LABEL);
  w[PAD_LABEL_4_IDX] = MakeLabel(COLOR_BUTTON_LABEL);
  w[PREVIEW_AREA_IDX] = MakeDrawArea(MAX_ICON_X_SIZE, MAX_ICON_Y_SIZE, redisplay_preview, me);


  /*  add menu items to 'file' menu
   */
  w[FILE_OPEN_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Open ...", file_open, me);
  w[FILE_SAVE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save", file_save, me);
  w[FILE_SAVE_AS_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save As ...", file_save_as, me);
  w[FILE_CLOSE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Close", file_close, me);
  w[FILE_ABOUT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "About ...", file_about, me);
  w[FILE_HELP_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Help ...", file_help, me);
  w[FILE_QUIT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Quit", file_quit, me);

  /*  add menu items to 'options' menu
   */
  w[OPT_SETUP_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Setup Icon ...", icon_setup, me);
  w[OPT_CLEAR_ICON_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Clear Icon", icon_clear, me);
  w[OPT_CLR_PALETTE_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Clear Palette", palette_clear, me);
  w[OPT_FLIP_VERT_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Flip Vertical", flip_vert, me);
  w[OPT_FLIP_HORIZ_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Flip Horizontal", flip_horiz, me);
  w[OPT_ROT_LEFT_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Rotate Left", rot_left, me);
  w[OPT_ROT_RIGHT_IDX] = MakeMenuItem(w[OPTIONS_MENU_IDX], "Rotate Right", rot_right, me);


  /*  callbacks for draw area 
   */
  SetButtonDownCB(w[DRAW_AREA_IDX], button_down);
  SetButtonUpCB(w[DRAW_AREA_IDX], button_up);
  SetMouseMotionCB(w[DRAW_AREA_IDX], motion);
  /* SetKeypressCB(w[DRAW_AREA_IDX], keypress);  -- not used !!!!! */


  /*  set all the widgets' positions
   */
  SetWidgetPos(w[OPTIONS_MENU_IDX], PLACE_RIGHT, w[FILE_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LABEL_IDX], PLACE_RIGHT, w[OPTIONS_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[DRAW_AREA_IDX], PLACE_UNDER, w[FILE_MENU_IDX], NO_CARE, NULL);

  SetWidgetPos(w[COLOR_BUTTON_01_IDX], PLACE_UNDER, w[FILE_MENU_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[COLOR_BUTTON_02_IDX], PLACE_UNDER, w[COLOR_BUTTON_01_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[COLOR_BUTTON_03_IDX], PLACE_UNDER, w[COLOR_BUTTON_02_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[COLOR_BUTTON_04_IDX], PLACE_UNDER, w[COLOR_BUTTON_03_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[COLOR_BUTTON_05_IDX], PLACE_UNDER, w[COLOR_BUTTON_04_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[COLOR_BUTTON_06_IDX], PLACE_UNDER, w[COLOR_BUTTON_05_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[COLOR_BUTTON_07_IDX], PLACE_UNDER, w[COLOR_BUTTON_06_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[COLOR_BUTTON_08_IDX], PLACE_UNDER, w[COLOR_BUTTON_07_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);

  SetWidgetPos(w[PAD_LABEL_1_IDX], PLACE_UNDER, w[COLOR_BUTTON_08_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[CURRENT_COLOR_LABEL_IDX], PLACE_UNDER, w[PAD_LABEL_1_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[CURRENT_DRAW_COLOR_IDX], PLACE_UNDER, w[CURRENT_COLOR_LABEL_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);

  SetWidgetPos(w[PAD_LABEL_2_IDX], PLACE_UNDER, w[CURRENT_DRAW_COLOR_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[EDIT_DRAW_COLOR_IDX], PLACE_UNDER, w[PAD_LABEL_2_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);

  SetWidgetPos(w[PAD_LABEL_3_IDX], PLACE_UNDER, w[EDIT_DRAW_COLOR_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[PAD_LABEL_4_IDX], PLACE_UNDER, w[PAD_LABEL_3_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);
  SetWidgetPos(w[PREVIEW_AREA_IDX], PLACE_UNDER, w[PAD_LABEL_4_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX]);


  /* This call actually causes the whole thing to be displayed on the
   * screen.  You have to call this function before doing any drawing
   * into the window.
   */
  ShowDisplay();
  
  /* Get standard (red, blue, green, yellow, black, white) colors for
   * drawing stuff.  Check libsx.h for more info. 
   */
  GetStandardColors();

  /* save useful widgets */
  me->work_draw_area = w[DRAW_AREA_IDX];
  for (c = 0; c < MAX_COLOR_MAP; c++)
  {
     me->color_buttons[c] = w[COLOR_BUTTON_01_IDX + c];
  }
  me->current_color_area = w[CURRENT_DRAW_COLOR_IDX];
  me->preview_area = w[PREVIEW_AREA_IDX];

  InitColorMap(me);

  SetFgColor(w[FILE_MENU_IDX], WHITE);			/* menu button */
  SetBgColor(w[FILE_MENU_IDX], BLUE);

  SetFgColor(w[OPTIONS_MENU_IDX], WHITE);		/* menu button */
  SetBgColor(w[OPTIONS_MENU_IDX], BLUE);

  SetFgColor(w[LABEL_IDX], BLACK);

  SetDrawArea(w[DRAW_AREA_IDX]);
  SetFgColor(w[DRAW_AREA_IDX], WHITE);			/* draw area */
  SetBgColor(w[DRAW_AREA_IDX], BLACK);

  SetFgColor(w[FILE_OPEN_IDX], WHITE);			/* pd menu */
  SetFgColor(w[FILE_SAVE_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_AS_IDX], WHITE);
  SetFgColor(w[FILE_CLOSE_IDX], WHITE);
  SetFgColor(w[FILE_ABOUT_IDX], WHITE);
  SetFgColor(w[FILE_HELP_IDX], WHITE);
  SetFgColor(w[FILE_QUIT_IDX], WHITE);
  SetBgColor(w[FILE_OPEN_IDX], BLUE);

  SetFgColor(w[OPT_SETUP_IDX], WHITE);
  SetFgColor(w[OPT_CLEAR_ICON_IDX], WHITE);
  SetFgColor(w[OPT_CLR_PALETTE_IDX], WHITE);
  SetFgColor(w[OPT_FLIP_VERT_IDX], WHITE);
  SetFgColor(w[OPT_FLIP_HORIZ_IDX], WHITE);
  SetFgColor(w[OPT_ROT_LEFT_IDX], WHITE);
  SetFgColor(w[OPT_ROT_RIGHT_IDX], WHITE);
  SetBgColor(w[OPT_SETUP_IDX], BLUE);

  SetFgColor(w[CURRENT_DRAW_COLOR_IDX], WHITE);		/* button */
  SetBgColor(w[CURRENT_DRAW_COLOR_IDX], me->data.colormap.indexes[me->current_draw_color]);

  SetFgColor(w[COLOR_BUTTON_01_IDX], WHITE);		/* buttons */
  SetBgColor(w[COLOR_BUTTON_01_IDX], me->data.colormap.indexes[COLOR_1_IDX]);
  SetFgColor(w[COLOR_BUTTON_02_IDX], WHITE);		
  SetBgColor(w[COLOR_BUTTON_02_IDX], me->data.colormap.indexes[COLOR_2_IDX]);
  SetFgColor(w[COLOR_BUTTON_03_IDX], WHITE);		
  SetBgColor(w[COLOR_BUTTON_03_IDX], me->data.colormap.indexes[COLOR_3_IDX]);
  SetFgColor(w[COLOR_BUTTON_04_IDX], WHITE);		
  SetBgColor(w[COLOR_BUTTON_04_IDX], me->data.colormap.indexes[COLOR_4_IDX]);
  SetFgColor(w[COLOR_BUTTON_05_IDX], WHITE);		
  SetBgColor(w[COLOR_BUTTON_05_IDX], me->data.colormap.indexes[COLOR_5_IDX]);
  SetFgColor(w[COLOR_BUTTON_06_IDX], WHITE);		
  SetBgColor(w[COLOR_BUTTON_06_IDX], me->data.colormap.indexes[COLOR_6_IDX]);
  SetFgColor(w[COLOR_BUTTON_07_IDX], WHITE);		
  SetBgColor(w[COLOR_BUTTON_07_IDX], me->data.colormap.indexes[COLOR_7_IDX]);
  SetFgColor(w[COLOR_BUTTON_08_IDX], WHITE);		
  SetBgColor(w[COLOR_BUTTON_08_IDX], me->data.colormap.indexes[COLOR_8_IDX]);

  SetFgColor(w[EDIT_DRAW_COLOR_IDX], WHITE);		/* button */
  SetBgColor(w[EDIT_DRAW_COLOR_IDX], BLUE);

  SetDrawArea(w[PREVIEW_AREA_IDX]);
  SetFgColor(w[PREVIEW_AREA_IDX], WHITE);		/* draw area */
  SetBgColor(w[PREVIEW_AREA_IDX], BLACK);


  UpdateDisplay(me);
  UpdatePreview(me);

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

