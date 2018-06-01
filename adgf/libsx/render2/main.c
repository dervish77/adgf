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
  w[FILE_MENU_IDX] = MakeMenu(" File ");
  w[EDIT_MENU_IDX] = MakeMenu(" Edit ");
  w[RENDER_MENU_IDX] = MakeMenu(" Render ");
  w[VIEW_MENU_IDX] = MakeMenu(" View ");
  w[LABEL_IDX] = MakeLabel("  Welcome to Render - ver 1.0");
  w[ZOOM_LABEL1_IDX] = MakeLabel("          Zoom In ");
  w[ZOOM_SCROLL_IDX] = MakeHorizScrollbar(ZOOM_SCROLL_SIZE, zoom_scroll, me);
  w[ZOOM_LABEL2_IDX] = MakeLabel(" Zoom Out");
  w[DRAW_AREA_IDX] = MakeDrawArea(SCREEN_X_SIZE, SCREEN_Y_SIZE, redisplay, me);
  w[LONG_SCROLL_IDX] = MakeHorizScrollbar(LONG_SCROLL_SIZE, long_scroll, me);
  w[LAT_SCROLL_IDX] = MakeVertScrollbar(LAT_SCROLL_SIZE, lat_scroll, me);


  /*  add menu items to 'file' menu
   */
  w[FILE_OPEN_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Open ...", file_open, me);
  w[FILE_SAVE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save", file_save, me);
  w[FILE_SAVE_AS_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save As ...", file_save_as, me);
  w[FILE_CLOSE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Close", file_close, me);
  w[FILE_ABOUT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "About ...", file_about, me);
  w[FILE_HELP_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Help ...", file_help, me);
  w[FILE_QUIT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Quit", file_quit, me);

  /*  add menu items to 'edit' menu
   */
  w[EDIT_COPY_IDX] = MakeMenuItem(w[EDIT_MENU_IDX], "Copy", edit_copy, me);
  w[EDIT_PASTE_IDX] = MakeMenuItem(w[EDIT_MENU_IDX], "Paste", edit_paste, me);
  w[EDIT_CUT_IDX] = MakeMenuItem(w[EDIT_MENU_IDX], "Cut", edit_cut, me);

  /*  add menu items to 'render' menu
   */
  w[RENDER_WIRE_IDX] = MakeMenuItem(w[RENDER_MENU_IDX], "Wireframe", render_wire, me);
  w[RENDER_FLAT_IDX] = MakeMenuItem(w[RENDER_MENU_IDX], "Flat Shading", render_flat, me);
  w[RENDER_GOUR_IDX] = MakeMenuItem(w[RENDER_MENU_IDX], "Gouraud Shading", render_gouraud, me);
  w[RENDER_PHONG_IDX] = MakeMenuItem(w[RENDER_MENU_IDX], "Phong Shading", render_phong, me);

  /*  add menu items to 'view' menu
   */
  w[VIEW_ORTH_XY_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Orthographic XY", view_orth_xy, me);
  w[VIEW_ORTH_ZY_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Orthographic YZ", view_orth_zy, me);
  w[VIEW_ORTH_XZ_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Orthographic XZ", view_orth_xz, me);
  w[VIEW_PARA_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Parallel", view_para, me);
  w[VIEW_PERS_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Perspective", view_pers, me);

  /*  callbacks for draw area 
   */
  SetButtonDownCB(w[DRAW_AREA_IDX], button_down);
  SetButtonUpCB(w[DRAW_AREA_IDX], button_up);
  SetMouseMotionCB(w[DRAW_AREA_IDX], motion);
  /* SetKeypressCB(w[DRAW_AREA_IDX], keypress);  -- not used !!!!! */

  /*  set all the widgets' positions
   */
  SetWidgetPos(w[EDIT_MENU_IDX], PLACE_RIGHT, w[FILE_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[RENDER_MENU_IDX], PLACE_RIGHT, w[EDIT_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[VIEW_MENU_IDX], PLACE_RIGHT, w[RENDER_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LABEL_IDX], PLACE_RIGHT, w[VIEW_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[ZOOM_LABEL1_IDX], PLACE_RIGHT, w[LABEL_IDX], NO_CARE, NULL);
  SetWidgetPos(w[ZOOM_SCROLL_IDX], PLACE_RIGHT, w[ZOOM_LABEL1_IDX], NO_CARE, NULL);
  SetWidgetPos(w[ZOOM_LABEL2_IDX], PLACE_RIGHT, w[ZOOM_SCROLL_IDX], NO_CARE, NULL);

  SetWidgetPos(w[DRAW_AREA_IDX], PLACE_UNDER, w[FILE_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LONG_SCROLL_IDX], PLACE_UNDER, w[DRAW_AREA_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LAT_SCROLL_IDX], PLACE_RIGHT, w[DRAW_AREA_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LAT_SCROLL_IDX], PLACE_UNDER, w[FILE_MENU_IDX], NO_CARE, NULL);


  /*  set scroll bars' initial state and range
   */
  SetScrollbar(w[LONG_SCROLL_IDX], LONG_SCROLL_WHERE, LONG_SCROLL_MAX, LONG_SCROLL_SHOWN);
  SetScrollbar(w[LAT_SCROLL_IDX], LAT_SCROLL_WHERE, LAT_SCROLL_MAX, LAT_SCROLL_SHOWN);
  SetScrollbar(w[ZOOM_SCROLL_IDX], ZOOM_SCROLL_WHERE, ZOOM_SCROLL_MAX, ZOOM_SCROLL_SHOWN);


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

  SetFgColor(w[EDIT_MENU_IDX], WHITE);
  SetBgColor(w[EDIT_MENU_IDX], BLUE);

  SetFgColor(w[RENDER_MENU_IDX], WHITE);
  SetBgColor(w[RENDER_MENU_IDX], BLUE);

  SetFgColor(w[VIEW_MENU_IDX], WHITE);
  SetBgColor(w[VIEW_MENU_IDX], BLUE);

  SetFgColor(w[LABEL_IDX], BLACK);

  SetFgColor(w[ZOOM_LABEL1_IDX], BLACK);
  SetFgColor(w[ZOOM_SCROLL_IDX], RED);
  SetBgColor(w[ZOOM_SCROLL_IDX], GetNamedColor("grey75"));
  SetFgColor(w[ZOOM_LABEL2_IDX], BLACK);

  SetFgColor(w[DRAW_AREA_IDX], WHITE);
  SetBgColor(w[DRAW_AREA_IDX], BLACK);

  SetFgColor(w[LONG_SCROLL_IDX], RED);
  SetBgColor(w[LONG_SCROLL_IDX], GetNamedColor("grey75"));

  SetFgColor(w[LAT_SCROLL_IDX], RED);
  SetBgColor(w[LAT_SCROLL_IDX], GetNamedColor("grey75"));

  SetFgColor(w[FILE_OPEN_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_AS_IDX], WHITE);
  SetFgColor(w[FILE_CLOSE_IDX], WHITE);
  SetFgColor(w[FILE_ABOUT_IDX], WHITE);
  SetFgColor(w[FILE_HELP_IDX], WHITE);
  SetFgColor(w[FILE_QUIT_IDX], WHITE);
  SetBgColor(w[FILE_OPEN_IDX], BLUE);

  SetFgColor(w[EDIT_COPY_IDX], WHITE);
  SetFgColor(w[EDIT_PASTE_IDX], WHITE);
  SetFgColor(w[EDIT_CUT_IDX], WHITE);
  SetBgColor(w[EDIT_COPY_IDX], BLUE);
  
  SetFgColor(w[RENDER_WIRE_IDX], WHITE);
  SetFgColor(w[RENDER_FLAT_IDX], WHITE);
  SetFgColor(w[RENDER_GOUR_IDX], WHITE);
  SetFgColor(w[RENDER_PHONG_IDX], WHITE);
  SetBgColor(w[RENDER_WIRE_IDX], BLUE);

  SetFgColor(w[VIEW_ORTH_XY_IDX], WHITE);
  SetFgColor(w[VIEW_ORTH_ZY_IDX], WHITE);
  SetFgColor(w[VIEW_ORTH_XZ_IDX], WHITE);
  SetFgColor(w[VIEW_PARA_IDX], WHITE);
  SetFgColor(w[VIEW_PERS_IDX], WHITE);
  SetBgColor(w[VIEW_ORTH_XY_IDX], BLUE);

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

