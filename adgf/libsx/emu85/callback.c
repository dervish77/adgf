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
void file_load(Widget w, void *data)
{
   MyProgram *me=data;

   HandleLoadImage(me);
} 

void file_save(Widget w, void *data)
{
   MyProgram *me=data;

}

void file_quit(Widget w, void *data)
{
   /* Do any cleanup that is necessary for your program here */

   printf("We're out of here!!!\n");

   PopupQuit();
}


/*  options menu callbacks
 */

void options_rom_setup(Widget w, void *data)
{
   MyProgram *me=data;

   printf("ROM Setup\n");
}

void options_ram_setup(Widget w, void *data)
{
   MyProgram *me=data;

   printf("RAM Setup\n");
}

void options_clock_setup(Widget w, void *data)
{
   MyProgram *me=data;

   printf("Clock Setup\n");
}

void options_status(Widget w, void *data)
{
   MyProgram *me=data;

   PopupStatus(me);
}


/*  display menu callbacks
 */

void display_mpu(Widget w, void *data)
{
   MyProgram *me=data;

   me->status.display = DISPLAY_MPU;

   printf("Display MPU\n");

   UpdateDisplay(me);
}

void display_system(Widget w, void *data)
{
   MyProgram *me=data;

   me->status.display = DISPLAY_SYSTEM;

   printf("Display system\n");

   UpdateDisplay(me);
}

void display_both(Widget w, void *data)
{
   MyProgram *me=data;

   me->status.display = DISPLAY_BOTH;

   printf("Display both\n");

   UpdateDisplay(me);
}

void display_image(Widget w, void *data)
{
   MyProgram *me=data;

   me->status.display = DISPLAY_IMAGE;

   printf("Display image\n");

   UpdateDisplay(me);
}


/*  control menu callbacks
 */

void control_reset(Widget w, void *data)
{
   MyProgram *me=data;

   me->status.control = CONTROL_RESET;

   printf("Control reset\n");

   HandleControl(me);
}

void control_step(Widget w, void *data)
{
   MyProgram *me=data;

   me->status.control = CONTROL_STEP;

   printf("Control step\n");

   HandleControl(me);
}

void control_go(Widget w, void *data)
{
   MyProgram *me=data;

   me->status.control = CONTROL_GO;

   printf("Control go\n");

   HandleControl(me);
}

void control_halt(Widget w, void *data)
{
   MyProgram *me=data;

   me->status.control = CONTROL_HALT;

   printf("Control halt\n");

   HandleControl(me);
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

void redisplay_status(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   UpdateStatus(me);
}


void redisplay(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   UpdateDisplay(me);
}


void button_down(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;

/*
   printf("You clicked button %d at (%d,%d)\n", which_button, x,y);
*/


}


void button_up(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;
   int r, c;

/*
   printf("You released button %d at (%d,%d)\n", which_button, x,y);
*/


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

/*
   if (up_or_down == 0)
      str = "pressed";
   else
      str = "released";

   printf("You %s : <<%s>>\n", str, input);
*/

   if (up_or_down == 0)
   {
      strcpy( &key[0], input );
/*
      HandleKeyPress( key[0], me );
*/
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

}


