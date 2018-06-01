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


Widget drawarea_widget;
Widget histarea_widget;
Widget lutarea_widget;


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
  Widget w[MAX_WIDGETS];

  if (OpenDisplay(argc, argv) == FALSE)
    return;

  /*  declare all the widgets
   */
  w[FILE_MENU_IDX] = MakeMenu("   File   ");
  w[CMD_MENU_IDX] = MakeMenu(" Command ");
  w[OPT_MENU_IDX] = MakeMenu(" Options ");
  w[LABEL_IDX] = MakeLabel("  Welcome to Image - ver 1.0");
  w[DRAW_AREA_IDX] = MakeDrawArea(SCREEN_C_SIZE, SCREEN_R_SIZE, redisplay, me);
  w[HIST_LABEL_IDX] = MakeLabel("Histogram");
  w[HIST_AREA_IDX] = MakeDrawArea(HIST_X_SIZE, HIST_Y_SIZE, redisplay_hist, me);
  w[LUT_LABEL_IDX] = MakeLabel("LUT");
  w[LUT_AREA_IDX] = MakeDrawArea(LUT_X_SIZE, LUT_Y_SIZE, redisplay_lut, me);


  /*  add menu items to 'file' menu
   */
  w[FILE_OPEN_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Open ...", file_open, me);
  w[FILE_SAVE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save", file_save, me);
  w[FILE_SAVE_AS_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save As ...", file_save_as, me);
  w[FILE_CLOSE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Close", file_close, me);
  w[FILE_ABOUT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "About ...", file_about, me);
  w[FILE_HELP_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Help ...", file_help, me);
  w[FILE_QUIT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Quit", file_quit, me);

  /*  add menu items to 'command' menu
   */
  w[CMD_REVERT_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Revert ", cmd_revert, me);
  w[CMD_HISTOGRAM_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Histogram ...", cmd_histogram, me);
  w[CMD_THRESHOLD_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Threshold ...", cmd_threshold, me);
  w[CMD_BRIGHTEN_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Brighten ...", cmd_brighten, me);
  w[CMD_COL2GREY_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Color to Grey ", cmd_color2grey, me);
  w[CMD_NEGATIVE_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Negative ", cmd_negative, me);
  w[CMD_MEDIAN_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Median ... ", cmd_median, me);
  w[CMD_BLUR_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Blur ...", cmd_blur, me);
  w[CMD_SHARPEN_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Sharpen ...", cmd_sharpen, me);
  w[CMD_EDGE_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Edge Detect ...", cmd_edge_detect, me);

  /*  add menu items to 'options' menu
   */
  w[OPT_DUMP_DATA_IDX] = MakeMenuItem(w[OPT_MENU_IDX], "Dump Database ...", opt_dump_database, me);
  w[OPT_STATUS_IDX] = MakeMenuItem(w[OPT_MENU_IDX], "Status ...", opt_status, me);

  /*  callbacks for draw area 
   */
  SetButtonDownCB(w[DRAW_AREA_IDX], button_down);
  SetButtonUpCB(w[DRAW_AREA_IDX], button_up);
  SetMouseMotionCB(w[DRAW_AREA_IDX], motion);
  /* SetKeypressCB(w[DRAW_AREA_IDX], keypress);  -- not used !!!!! */

  /*  set all the widgets' positions
   */
  SetWidgetPos(w[CMD_MENU_IDX], PLACE_RIGHT, w[FILE_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[OPT_MENU_IDX], PLACE_RIGHT, w[CMD_MENU_IDX],  NO_CARE, NULL);
  SetWidgetPos(w[LABEL_IDX],    PLACE_RIGHT, w[OPT_MENU_IDX],  NO_CARE, NULL);

  SetWidgetPos(w[DRAW_AREA_IDX], PLACE_UNDER, w[FILE_MENU_IDX], NO_CARE, NULL);

  SetWidgetPos(w[HIST_LABEL_IDX], PLACE_UNDER, w[DRAW_AREA_IDX], NO_CARE, NULL);
  SetWidgetPos(w[HIST_AREA_IDX], PLACE_UNDER, w[HIST_LABEL_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LUT_LABEL_IDX], PLACE_UNDER, w[DRAW_AREA_IDX], PLACE_RIGHT, w[HIST_AREA_IDX]);
  SetWidgetPos(w[LUT_AREA_IDX], PLACE_UNDER, w[LUT_LABEL_IDX], PLACE_RIGHT, w[HIST_AREA_IDX]);



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

  SetFgColor(w[CMD_MENU_IDX], WHITE);
  SetBgColor(w[CMD_MENU_IDX], BLUE);

  SetFgColor(w[OPT_MENU_IDX], WHITE);
  SetBgColor(w[OPT_MENU_IDX], BLUE);

  SetFgColor(w[LABEL_IDX], BLACK);

  SetFgColor(w[DRAW_AREA_IDX], WHITE);
  SetBgColor(w[DRAW_AREA_IDX], BLACK);

  SetFgColor(w[HIST_LABEL_IDX], BLACK);

  SetFgColor(w[HIST_AREA_IDX], WHITE);
  SetBgColor(w[HIST_AREA_IDX], BLACK);

  SetFgColor(w[LUT_LABEL_IDX], BLACK);

  SetFgColor(w[LUT_AREA_IDX], WHITE);
  SetBgColor(w[LUT_AREA_IDX], BLACK);

  SetFgColor(w[FILE_OPEN_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_AS_IDX], WHITE);
  SetFgColor(w[FILE_CLOSE_IDX], WHITE);
  SetFgColor(w[FILE_ABOUT_IDX], WHITE);
  SetFgColor(w[FILE_HELP_IDX], WHITE);
  SetFgColor(w[FILE_QUIT_IDX], WHITE);
  SetBgColor(w[FILE_OPEN_IDX], BLUE);

  SetFgColor(w[CMD_REVERT_IDX], WHITE);
  SetFgColor(w[CMD_HISTOGRAM_IDX], WHITE);
  SetFgColor(w[CMD_THRESHOLD_IDX], WHITE);
  SetFgColor(w[CMD_BRIGHTEN_IDX], WHITE);
  SetFgColor(w[CMD_COL2GREY_IDX], WHITE);
  SetFgColor(w[CMD_NEGATIVE_IDX], WHITE);
  SetFgColor(w[CMD_MEDIAN_IDX], WHITE);
  SetFgColor(w[CMD_BLUR_IDX], WHITE);
  SetFgColor(w[CMD_SHARPEN_IDX], WHITE);
  SetFgColor(w[CMD_EDGE_IDX], WHITE);
  SetBgColor(w[CMD_REVERT_IDX], BLUE);
  
  SetFgColor(w[OPT_DUMP_DATA_IDX], WHITE);
  SetFgColor(w[OPT_STATUS_IDX], WHITE);
  SetBgColor(w[OPT_DUMP_DATA_IDX], BLUE);

  drawarea_widget = w[DRAW_AREA_IDX];
  histarea_widget = w[HIST_AREA_IDX];
  lutarea_widget = w[LUT_AREA_IDX];

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

