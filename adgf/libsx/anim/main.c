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
#include "main.h"              /* where program specific stuff is defined */
#include "callbcks.h"         /* prototypes for callback functions       */


/* define's */
#define SCROLL_SIZE 	((int) 200)
#define SCROLL_WHERE 	((float) 15.0)
#define SCROLL_MAX	((float) 30.0)
#define SCROLL_SHOWN	((float) 1.0)


void main(int argc, char **argv)
{
  MyProgram mydata;

  mydata.dataloaded = FALSE;          /* do your initializations here */
  mydata.redraw = TRUE;
  mydata.button_state = BUTTON_UP;
  mydata.endgrabbed = FALSE;
  mydata.frame_rate = SCROLL_WHERE;
  mydata.frame_interval = (int) ((1 / SCROLL_WHERE) * (1000));
  mydata.end_effect.type = ENDEFF_SQUARE;
  mydata.end_effect.motion = ENDMOT_MANUAL;

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
  Widget w[9];
  Widget file_mi[4];
  Widget mode_mi[6];

  if (OpenDisplay(argc, argv) == FALSE)
    return;

  /*  declare all the widgets
   */
  w[0] = MakeMenu(" File ");
  w[1] = MakeMenu(" Anim Mode ");
  w[2] = MakeButton(" Run ", run_anim, me);
  w[3] = MakeButton(" Stop ", stop_anim, me);
  w[4] = MakeButton(" Toggle Redraw ", toggle_redraw, me);
  w[5] = MakeLabel("    Slower");
  w[6] = MakeHorizScrollbar(SCROLL_SIZE, frame_rate, me);
  w[7] = MakeLabel("Faster    ");
  w[8] = MakeDrawArea(SCREEN_X_SIZE, SCREEN_Y_SIZE, redisplay, me);

  /*  add menu items to 'file' menu
   */
  file_mi[0] = MakeMenuItem(w[0], "Open ...", open_file, me);
  file_mi[1] = MakeMenuItem(w[0], "About ...", about, me);
  file_mi[2] = MakeMenuItem(w[0], "Help ...", help, me);
  file_mi[3] = MakeMenuItem(w[0], "Quit", quit, me);

  /*  add menu items to 'mode' menu
   */
  mode_mi[0] = MakeMenuItem(w[1], "Manual", mode_manual, me);
  mode_mi[1] = MakeMenuItem(w[1], "Linear", mode_linear, me);
  mode_mi[2] = MakeMenuItem(w[1], "Circle", mode_circle, me);
  mode_mi[3] = MakeMenuItem(w[1], "Random", mode_random, me); 
  mode_mi[4] = MakeMenuItem(w[1], "Forward Table", mode_fw_table, me); 
  mode_mi[5] = MakeMenuItem(w[1], "Forward Random", mode_fw_random, me); 

  /*  callbacks for draw area 
   */
  SetButtonDownCB(w[8], button_down);
  SetButtonUpCB(w[8], button_up);
  SetMouseMotionCB(w[8], motion);
  /* SetKeypressCB(w[8], keypress);  -- not used !!!!! */

  /*  set all the widgets' positions
   */
  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE, NULL);
  SetWidgetPos(w[2], PLACE_RIGHT, w[1], NO_CARE, NULL);
  SetWidgetPos(w[3], PLACE_RIGHT, w[2], NO_CARE, NULL);
  SetWidgetPos(w[4], PLACE_RIGHT, w[3], NO_CARE, NULL);
  SetWidgetPos(w[5], PLACE_RIGHT, w[4], NO_CARE, NULL);
  SetWidgetPos(w[6], PLACE_RIGHT, w[5], NO_CARE, NULL);
  SetWidgetPos(w[7], PLACE_RIGHT, w[6], NO_CARE, NULL);
  SetWidgetPos(w[8], PLACE_UNDER, w[0], NO_CARE, NULL);
  
  /*  set scroll bar's initial state and range
   */
  SetScrollbar(w[6], SCROLL_WHERE, SCROLL_MAX, SCROLL_SHOWN);


  /* This call actually causes the whole thing to be displayed on the
   * screen.  You have to call this function before doing any drawing
   * into the window.
   */
  ShowDisplay();

  
  /* Get standard (red, blue, green, yellow, black, white) colors for
   * drawing stuff.  Check libsx.h for more info. 
   */
  GetStandardColors();
 
  SetFgColor(w[0], WHITE);
  SetBgColor(w[0], BLUE);

  SetFgColor(w[1], WHITE);
  SetBgColor(w[1], BLUE);

  SetFgColor(w[2], WHITE);
  SetBgColor(w[2], BLUE);

  SetFgColor(w[3], WHITE);
  SetBgColor(w[3], BLUE);

  SetFgColor(w[4], WHITE);
  SetBgColor(w[4], BLUE);

  SetFgColor(w[6], RED);
  SetBgColor(w[6], GetNamedColor("grey75"));

  SetFgColor(w[8], GREEN);
  SetBgColor(w[8], BLACK);

  SetFgColor(file_mi[0], WHITE);
  SetFgColor(file_mi[1], WHITE);
  SetFgColor(file_mi[2], WHITE);
  SetFgColor(file_mi[3], WHITE);
  SetBgColor(file_mi[0], BLUE);

  SetFgColor(mode_mi[0], WHITE);
  SetFgColor(mode_mi[1], WHITE);
  SetFgColor(mode_mi[2], WHITE);
  SetFgColor(mode_mi[3], WHITE);
  SetFgColor(mode_mi[4], WHITE);
  SetFgColor(mode_mi[5], WHITE);
  SetBgColor(mode_mi[0], BLUE);
  
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

