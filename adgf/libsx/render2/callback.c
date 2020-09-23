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
#include "callback.h"          /* prototypes for callback functions       */
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


void file_open(Widget w, void *data)
{
   MyProgram *me=data;

   char *new_file_name;

   new_file_name = GetString("Enter file name to open (file.mdl)\n", "");

}

void file_save(Widget w, void *data)
{
   MyProgram *me=data;

   printf("model saved\n");
}

void file_save_as(Widget w, void *data)
{
   MyProgram *me=data;

   char *new_file_name;

   new_file_name = GetString("Enter file name to save as (file.mdl)\n", "");

}

void file_close(Widget w, void *data)
{
   MyProgram *me=data;

   printf("model closed\n");
}

void file_about(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("Render\n\nversion 1.0");  
}

void file_help(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("HELP\n----\n\nFile->Open - to load model\nSave - to save model\nSave As - save to new file\nClose - close current file");  
}

void file_quit(Widget w, void *data)
{
  /* Do any cleanup that is necessary for your program here */

  printf("We're out of here!!!\n");

  exit(0);
}


/* edit callbacks */

void edit_copy(Widget w, void *data)
{
  MyProgram *me=data;

  printf("copy\n");
}

void edit_paste(Widget w, void *data)
{
  MyProgram *me=data;

  printf("paste\n");
}

void edit_cut(Widget w, void *data)
{
  MyProgram *me=data;

  printf("cut\n");
}


/* tools menu callbacks */

void render_wire(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.shading_mode = WIRE_SHADE;

  printf("render wireframe\n");
}

void render_flat(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.shading_mode = FLAT_SHADE;

  printf("render flat shading\n");
}

void render_gouraud(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.shading_mode = GOURAUD_SHADE;

  printf("render gouraud shading\n");
}

void render_phong(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.shading_mode = PHONG_SHADE;

  printf("render phong shading\n");
}



/* view menu callbacks */

void view_orth_xy(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.projection = ORTH_PROJ_XY;

  printf("view orthographic xy\n");
}

void view_orth_zy(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.projection = ORTH_PROJ_ZY;

  printf("view orthographic zy\n");
}

void view_orth_xz(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.projection = ORTH_PROJ_XZ;

  printf("view orthographic xz\n");
}

void view_para(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.projection = PARA_PROJ;

  printf("view parallel\n");
}

void view_pers(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.projection = PERS_PROJ;

  printf("view perspective\n");
}


/* scroll bar callbacks */

void long_scroll(Widget w, float longitude, void *data)
{
  MyProgram *me=data;

  me->longitude = longitude;

  printf("long scroll at %f\n", me->longitude);

  ComputeEyeLocation(me);

  printf("    eye is at (x,y,z): %f, %f, %f\n", 
	me->data.view.eyeloc.x, me->data.view.eyeloc.y, me->data.view.eyeloc.z);
}

void lat_scroll(Widget w, float latitude, void *data)
{
  MyProgram *me=data;

  me->latitude = (latitude - 90.0) * (-1.0);

  printf("lat scroll at %f\n", me->latitude);

  ComputeEyeLocation(me);

  printf("    eye is at (x,y,z): %f, %f, %f\n", 
	me->data.view.eyeloc.x, me->data.view.eyeloc.y, me->data.view.eyeloc.z);
}

void zoom_scroll(Widget w, float zoom, void *data)
{
  MyProgram *me=data;

  me->zoom = zoom;

  printf("zoom scroll at %f percent\n", me->zoom);

  ComputeEyeLocation(me);

  printf("    eye is at (x,y,z): %f, %f, %f\n", 
	me->data.view.eyeloc.x, me->data.view.eyeloc.y, me->data.view.eyeloc.z);
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
void redisplay(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   ClearDrawArea();             /* start with a clean slate */
}


void button_down(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;

   printf("You clicked button %d at (%d,%d)\n", which_button, x,y);
}


void button_up(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;

   printf("You released button %d at (%d,%d)\n", which_button, x,y);
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
   char *str;

   if (input == NULL)
     return;

   if (up_or_down == 0)
      str = "pressed";
   else
      str = "released";

   printf("You %s : <<%s>>\n", str, input);
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


