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


void main(int argc, char **argv)
{
  MyProgram mydata;

  InitDatabase(&mydata);
  GenerateParticleSystem(&mydata, 0);
  SetupAnimToRun(&mydata);

printf("back in main\n");

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
  w[VIEW_MENU_IDX] = MakeMenu("   View   ");
  w[ANIM_MENU_IDX] = MakeMenu("   Anim   ");
  w[ZOOM_MENU_IDX] = MakeMenu("   Zoom   ");
  w[LABEL_IDX] = MakeLabel("  Welcome to Particle - ver 1.0");
  w[DRAW_AREA_IDX] = MakeDrawArea(SCREEN_X_SIZE, SCREEN_Y_SIZE, redisplay, me);


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
  w[CMD_SET_SYS_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Setup Systems ...", cmd_setup_system, me);
  w[CMD_EDIT_CAMERA_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Edit Camera ...", cmd_edit_camera, me);
  w[CMD_EDIT_ANIM_IDX] = MakeMenuItem(w[CMD_MENU_IDX], "Edit Anim ...", cmd_edit_anim, me);

  /*  add menu items to 'options' menu
   */
  w[OPT_DUMP_DATA_IDX] = MakeMenuItem(w[OPT_MENU_IDX], "Dump Database ...", opt_dump_database, me);
  w[OPT_STATUS_IDX] = MakeMenuItem(w[OPT_MENU_IDX], "Status ...", opt_status, me);

  /*  add menu items to 'view' menu
   */
  w[VIEW_ALL_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "All", view_all, me);
  w[VIEW_XY_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Ortho XY", view_xy, me);
  w[VIEW_ZY_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Ortho ZY", view_zy, me);
  w[VIEW_XZ_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Ortho XZ", view_xz, me);
  w[VIEW_CAMERA_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Camera", view_camera, me);

  /*  add menu items to 'anim' menu
   */
  w[ANIM_STOP_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "Stop ", anim_stop, me);
  w[ANIM_RUN_FOR_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "Run Forward ", anim_run_forward, me);
  w[ANIM_RUN_REV_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "Run Reverse ", anim_run_reverse, me);
  w[ANIM_LOOP_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "Loop ", anim_loop, me);
  w[ANIM_PING_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "Ping Pong ", anim_ping, me);
  w[ANIM_STEP_FOR_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "Step Forward ", anim_step_forward, me);
  w[ANIM_STEP_REV_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "Step Reverse ", anim_step_reverse, me);
  w[ANIM_FIRST_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "First Frame ", anim_first, me);
  w[ANIM_LAST_IDX] = MakeMenuItem(w[ANIM_MENU_IDX], "Last Frame ", anim_last, me);

  /*  add menu items to 'zoom' menu
   */
  w[ZOOM_IN_IDX] = MakeMenuItem(w[ZOOM_MENU_IDX], "Zoom In", zoom_in, me);
  w[ZOOM_NORMAL_IDX] = MakeMenuItem(w[ZOOM_MENU_IDX], "Zoom Normal", zoom_normal, me);
  w[ZOOM_OUT_IDX] = MakeMenuItem(w[ZOOM_MENU_IDX], "Zoom Out", zoom_out, me);


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
  SetWidgetPos(w[VIEW_MENU_IDX], PLACE_RIGHT, w[OPT_MENU_IDX],  NO_CARE, NULL);
  SetWidgetPos(w[ANIM_MENU_IDX], PLACE_RIGHT, w[VIEW_MENU_IDX],  NO_CARE, NULL);
  SetWidgetPos(w[ZOOM_MENU_IDX], PLACE_RIGHT, w[ANIM_MENU_IDX],  NO_CARE, NULL);
  SetWidgetPos(w[LABEL_IDX],    PLACE_RIGHT, w[ZOOM_MENU_IDX],  NO_CARE, NULL);

  SetWidgetPos(w[DRAW_AREA_IDX], PLACE_UNDER, w[FILE_MENU_IDX], NO_CARE, NULL);



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

  SetFgColor(w[VIEW_MENU_IDX], WHITE);
  SetBgColor(w[VIEW_MENU_IDX], BLUE);

  SetFgColor(w[ANIM_MENU_IDX], WHITE);
  SetBgColor(w[ANIM_MENU_IDX], BLUE);

  SetFgColor(w[ZOOM_MENU_IDX], WHITE);
  SetBgColor(w[ZOOM_MENU_IDX], BLUE);

  SetFgColor(w[LABEL_IDX], BLACK);

  SetFgColor(w[DRAW_AREA_IDX], WHITE);
  SetBgColor(w[DRAW_AREA_IDX], BLACK);

  SetFgColor(w[FILE_OPEN_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_AS_IDX], WHITE);
  SetFgColor(w[FILE_CLOSE_IDX], WHITE);
  SetFgColor(w[FILE_ABOUT_IDX], WHITE);
  SetFgColor(w[FILE_HELP_IDX], WHITE);
  SetFgColor(w[FILE_QUIT_IDX], WHITE);
  SetBgColor(w[FILE_OPEN_IDX], BLUE);

  SetFgColor(w[CMD_SET_SYS_IDX], WHITE);
  SetFgColor(w[CMD_EDIT_CAMERA_IDX], WHITE);
  SetFgColor(w[CMD_EDIT_ANIM_IDX], WHITE);
  SetBgColor(w[CMD_SET_SYS_IDX], BLUE);
  
  SetFgColor(w[OPT_DUMP_DATA_IDX], WHITE);
  SetFgColor(w[OPT_STATUS_IDX], WHITE);
  SetBgColor(w[OPT_DUMP_DATA_IDX], BLUE);

  SetFgColor(w[VIEW_ALL_IDX], WHITE);
  SetFgColor(w[VIEW_XY_IDX], WHITE);
  SetFgColor(w[VIEW_ZY_IDX], WHITE);
  SetFgColor(w[VIEW_XZ_IDX], WHITE);
  SetFgColor(w[VIEW_CAMERA_IDX], WHITE);
  SetBgColor(w[VIEW_ALL_IDX], BLUE);

  SetFgColor(w[ANIM_STOP_IDX], WHITE);
  SetFgColor(w[ANIM_RUN_FOR_IDX], WHITE);
  SetFgColor(w[ANIM_RUN_REV_IDX], WHITE);
  SetFgColor(w[ANIM_LOOP_IDX], WHITE);
  SetFgColor(w[ANIM_PING_IDX], WHITE);
  SetFgColor(w[ANIM_STEP_FOR_IDX], WHITE);
  SetFgColor(w[ANIM_STEP_REV_IDX], WHITE);
  SetFgColor(w[ANIM_FIRST_IDX], WHITE);
  SetFgColor(w[ANIM_LAST_IDX], WHITE);
  SetBgColor(w[ANIM_STOP_IDX], BLUE);

  SetFgColor(w[ZOOM_IN_IDX], WHITE);
  SetFgColor(w[ZOOM_NORMAL_IDX], WHITE);
  SetFgColor(w[ZOOM_OUT_IDX], WHITE);
  SetBgColor(w[ZOOM_IN_IDX], BLUE);


  drawarea_widget = w[DRAW_AREA_IDX];

  UpdateDisplay(me);

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

