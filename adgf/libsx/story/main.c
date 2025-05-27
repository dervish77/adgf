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

  InitDatabase(&mydata);

  init_display(argc, argv, &mydata);  /* setup the display */

  UpdateDisplay(&mydata);

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

  char label_string[128];

#ifdef _DEBUG_STORY
  printf("initializing display\n");
#endif

  if (OpenDisplay(argc, argv) == FALSE)
    return;

  /*  declare all the widgets
   */
  w[FILE_MENU_IDX] = MakeMenu(" File ");
  w[EDIT_MENU_IDX] = MakeMenu(" Edit ");
  w[VIEW_MENU_IDX] = MakeMenu(" View ");
  w[FUNC_MENU_IDX] = MakeMenu(" Function ");
  w[TOOLS_MENU_IDX] = MakeMenu(" Tools ");
  w[HELP_MENU_IDX] = MakeMenu(" Help ");
  sprintf(&label_string[0], "   Welcome to Story Board Master - ver %s", VERSION);
  w[LABEL_IDX] = MakeLabel(label_string);
  w[DRAW_AREA_IDX] = MakeDrawArea(SCREEN_X_SIZE, SCREEN_Y_SIZE, redisplay, me);
#ifdef _DEBUG_STORY
  printf("created widgets\n");
#endif

  /*  add menu items to 'file' menu
   */
  w[FILE_NEW_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "New ...", file_new, me);
  w[FILE_OPEN_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Open ...", file_open, me);
  w[FILE_SAVE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save", file_save, me);
  w[FILE_SAVE_AS_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Save As ...", file_save_as, me);
  w[FILE_PRINT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Print", file_print, me);
  w[FILE_PRINT_SET_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Print Setup ...", file_print_setup, me);
  w[FILE_PREFS_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Prefs ...", file_prefs, me);
  w[FILE_CLOSE_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Close", file_close, me);
  w[FILE_QUIT_IDX] = MakeMenuItem(w[FILE_MENU_IDX], "Quit", file_quit, me);
#ifdef _DEBUG_STORY
  printf("created file menu\n");
#endif

  /*  add menu items to 'edit' menu
   */
  w[EDIT_UNDO_IDX] = MakeMenuItem(w[EDIT_MENU_IDX], "Undo", edit_undo, me);
  w[EDIT_SEL_ALL_IDX] = MakeMenuItem(w[EDIT_MENU_IDX], "Select All", edit_sel_all, me);
  w[EDIT_COPY_IDX] = MakeMenuItem(w[EDIT_MENU_IDX], "Copy", edit_copy, me);
  w[EDIT_PASTE_IDX] = MakeMenuItem(w[EDIT_MENU_IDX], "Paste", edit_paste, me);
  w[EDIT_CUT_IDX] = MakeMenuItem(w[EDIT_MENU_IDX], "Cut", edit_cut, me);
#ifdef _DEBUG_STORY
  printf("created edit menu\n");
#endif

  /*  add menu items to 'view' menu
   */
  w[VIEW_ALL_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "All", view_all, me);
  w[VIEW_ACT_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Act ...", view_act, me);
  w[VIEW_SCENE_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Scene ...", view_scene, me);
  w[VIEW_HIER_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Hierarchy", view_hier, me);
  w[VIEW_FRAMES_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Frames", view_frames, me);
  w[VIEW_SLIDES_IDX] = MakeMenuItem(w[VIEW_MENU_IDX], "Slide Show ...", view_slides, me);
#ifdef _DEBUG_STORY
  printf("created view menu\n");
#endif

  /*  add menu items to 'function' menu
   */
  w[FUNC_ADD_ACT_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Add Act", func_add_act, me);
  w[FUNC_ADD_SCENE_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Add Scene", func_add_scene, me);
  w[FUNC_ADD_FRAME_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Add Frame", func_add_frame, me);
  w[FUNC_DEL_ACT_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Delete Act", func_del_act, me);
  w[FUNC_DEL_SCENE_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Delete Scene", func_del_scene, me);
  w[FUNC_DEL_FRAME_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Delete Frame", func_del_frame, me);
  w[FUNC_EDIT_SEL_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Edit Selected", func_edit_sel, me);
  w[FUNC_EDIT_FRM_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Edit Frame", func_edit_frame, me);
  w[FUNC_REARRANGE_IDX] = MakeMenuItem(w[FUNC_MENU_IDX], "Re-arrange", func_rearrange, me);
#ifdef _DEBUG_STORY
  printf("created function menu\n");
#endif

  /*  add menu items to 'tools' menu
   */
  w[TOOLS_SELECT_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Select", tools_select, me);
  w[TOOLS_LINE_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Line", tools_line, me);
  w[TOOLS_FREE_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Freehand", tools_freehand, me);
  w[TOOLS_RECT_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Rectangle", tools_rectangle, me);
  w[TOOLS_CIRCLE_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Circle", tools_circle, me);
  w[TOOLS_ARC_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Arc", tools_arc, me);
  w[TOOLS_FRECT_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Filled Rectangle", tools_fill_rect, me);
  w[TOOLS_FCIRCLE_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Filled Circle", tools_fill_circle, me);
  w[TOOLS_FILL_STYLE_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Fill Style ...", tools_fill_style, me);
  w[TOOLS_PATT_STYLE_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Pattern Style ...", tools_patt_style, me);
  w[TOOLS_IMP_BM_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Import Bitmap ...", tools_import_bm, me);
  w[TOOLS_EXP_BM_IDX] = MakeMenuItem(w[TOOLS_MENU_IDX], "Export Bitmap ...", tools_export_bm, me);
#ifdef _DEBUG_STORY
  printf("created tools menu\n");
#endif

  /*  add menu items to 'help' menu
   */
  w[HELP_ABOUT_IDX] = MakeMenuItem(w[HELP_MENU_IDX], "About", help_about, me);
  w[HELP_BRIEF_IDX] = MakeMenuItem(w[HELP_MENU_IDX], "Brief Help", help_brief, me);
  w[HELP_SEARCH_IDX] = MakeMenuItem(w[HELP_MENU_IDX], "Search Help", help_search, me);
  w[HELP_INDEX_IDX] = MakeMenuItem(w[HELP_MENU_IDX], "Index", help_index, me);
#ifdef _DEBUG_STORY
  printf("created help menu\n");
#endif

  /*  callbacks for draw area 
   */
  SetButtonDownCB(w[DRAW_AREA_IDX], button_down);
  SetButtonUpCB(w[DRAW_AREA_IDX], button_up);
  SetMouseMotionCB(w[DRAW_AREA_IDX], motion);
  /* SetKeypressCB(w[DRAW_AREA_IDX], keypress);  -- not used !!!!! */
#ifdef _DEBUG_STORY
  printf("set callbacks\n");
#endif

  /*  set all the widgets' positions
   */
  SetWidgetPos(w[EDIT_MENU_IDX], PLACE_RIGHT, w[FILE_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[VIEW_MENU_IDX], PLACE_RIGHT, w[EDIT_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[FUNC_MENU_IDX], PLACE_RIGHT, w[VIEW_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[TOOLS_MENU_IDX], PLACE_RIGHT, w[FUNC_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[HELP_MENU_IDX], PLACE_RIGHT, w[TOOLS_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[LABEL_IDX], PLACE_RIGHT, w[HELP_MENU_IDX], NO_CARE, NULL);
  SetWidgetPos(w[DRAW_AREA_IDX], PLACE_UNDER, w[FILE_MENU_IDX], NO_CARE, NULL);
#ifdef _DEBUG_STORY
  printf("set widget positions\n");
#endif


  /* This call actually causes the whole thing to be displayed on the
   * screen.  You have to call this function before doing any drawing
   * into the window.
   */
  ShowDisplay();
#ifdef _DEBUG_STORY
  printf("showed display\n");
#endif

  
  /* Get standard (red, blue, green, yellow, black, white) colors for
   * drawing stuff.  Check libsx.h for more info. 
   */
  GetStandardColors();
 
  SetFgColor(w[FILE_MENU_IDX], WHITE);
  SetBgColor(w[FILE_MENU_IDX], BLUE);

  SetFgColor(w[EDIT_MENU_IDX], WHITE);
  SetBgColor(w[EDIT_MENU_IDX], BLUE);

  SetFgColor(w[VIEW_MENU_IDX], WHITE);
  SetBgColor(w[VIEW_MENU_IDX], BLUE);

  SetFgColor(w[FUNC_MENU_IDX], WHITE);
  SetBgColor(w[FUNC_MENU_IDX], BLUE);

  SetFgColor(w[TOOLS_MENU_IDX], WHITE);
  SetBgColor(w[TOOLS_MENU_IDX], BLUE);

  SetFgColor(w[HELP_MENU_IDX], WHITE);
  SetBgColor(w[HELP_MENU_IDX], BLUE);

  SetFgColor(w[LABEL_IDX], BLACK);

  SetFgColor(w[DRAW_AREA_IDX], WHITE);
  SetBgColor(w[DRAW_AREA_IDX], BLACK);

  SetFgColor(w[FILE_NEW_IDX], WHITE);
  SetFgColor(w[FILE_OPEN_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_IDX], WHITE);
  SetFgColor(w[FILE_SAVE_AS_IDX], WHITE);
  SetFgColor(w[FILE_PRINT_IDX], WHITE);
  SetFgColor(w[FILE_PRINT_SET_IDX], WHITE);
  SetFgColor(w[FILE_PREFS_IDX], WHITE);
  SetFgColor(w[FILE_CLOSE_IDX], WHITE);
  SetFgColor(w[FILE_QUIT_IDX], WHITE);
  SetBgColor(w[FILE_NEW_IDX], BLUE);

  SetFgColor(w[EDIT_UNDO_IDX], WHITE);
  SetFgColor(w[EDIT_SEL_ALL_IDX], WHITE);
  SetFgColor(w[EDIT_COPY_IDX], WHITE);
  SetFgColor(w[EDIT_PASTE_IDX], WHITE);
  SetFgColor(w[EDIT_CUT_IDX], WHITE);
  SetBgColor(w[EDIT_UNDO_IDX], BLUE);
  
  SetFgColor(w[VIEW_ALL_IDX], WHITE);
  SetFgColor(w[VIEW_ACT_IDX], WHITE);
  SetFgColor(w[VIEW_SCENE_IDX], WHITE);
  SetFgColor(w[VIEW_HIER_IDX], WHITE);
  SetFgColor(w[VIEW_FRAMES_IDX], WHITE);
  SetFgColor(w[VIEW_SLIDES_IDX], WHITE);
  SetBgColor(w[VIEW_ALL_IDX], BLUE);

  SetFgColor(w[FUNC_ADD_ACT_IDX], WHITE);
  SetFgColor(w[FUNC_ADD_SCENE_IDX], WHITE);
  SetFgColor(w[FUNC_ADD_FRAME_IDX], WHITE);
  SetFgColor(w[FUNC_DEL_ACT_IDX], WHITE);
  SetFgColor(w[FUNC_DEL_SCENE_IDX], WHITE);
  SetFgColor(w[FUNC_DEL_FRAME_IDX], WHITE);
  SetFgColor(w[FUNC_EDIT_SEL_IDX], WHITE);
  SetFgColor(w[FUNC_EDIT_FRM_IDX], WHITE);
  SetFgColor(w[FUNC_REARRANGE_IDX], WHITE);
  SetBgColor(w[FUNC_ADD_ACT_IDX], BLUE);

  SetFgColor(w[TOOLS_SELECT_IDX], WHITE);
  SetFgColor(w[TOOLS_LINE_IDX], WHITE);
  SetFgColor(w[TOOLS_FREE_IDX], WHITE);
  SetFgColor(w[TOOLS_RECT_IDX], WHITE);
  SetFgColor(w[TOOLS_CIRCLE_IDX], WHITE);
  SetFgColor(w[TOOLS_ARC_IDX], WHITE);
  SetFgColor(w[TOOLS_FRECT_IDX], WHITE);
  SetFgColor(w[TOOLS_FCIRCLE_IDX], WHITE);
  SetFgColor(w[TOOLS_FILL_STYLE_IDX], WHITE);
  SetFgColor(w[TOOLS_PATT_STYLE_IDX], WHITE);
  SetFgColor(w[TOOLS_IMP_BM_IDX], WHITE);
  SetFgColor(w[TOOLS_EXP_BM_IDX], WHITE);
  SetBgColor(w[TOOLS_SELECT_IDX], BLUE);

  SetFgColor(w[HELP_ABOUT_IDX], WHITE);
  SetFgColor(w[HELP_BRIEF_IDX], WHITE);
  SetFgColor(w[HELP_SEARCH_IDX], WHITE);
  SetFgColor(w[HELP_INDEX_IDX], WHITE);
  SetBgColor(w[HELP_ABOUT_IDX], BLUE);


  /*  save any widget indices
   */
  me->draw_area_widget = w[DRAW_AREA_IDX];


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

#ifdef _DEBUG_STORY
  printf("initializing display - done\n");
#endif

}

