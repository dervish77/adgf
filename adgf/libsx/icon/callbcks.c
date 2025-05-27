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

#ifndef _CALLBCKS_H
#include "callbcks.h"         /* prototypes for callback functions       */
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


/* file callbacks */

void file_open(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;

   printf("loading icon ...\n");

   new_file_name = GetString("Enter file name to open (file.icon)\n", "");

   if ( (new_file_name != (char *) NULL) && (strlen(new_file_name) > 0) )
   {
      if (strlen(new_file_name) < FILE_STRING_LEN)
         strcpy(me->load_file_name, new_file_name);
      else {
         strncpy(me->load_file_name, new_file_name, FILE_STRING_LEN);
         me->load_file_name[FILE_STRING_LEN - 1] = '\0';
      }

      strcpy(me->save_file_name, me->load_file_name);

      me->load_file = fopen(me->load_file_name, "r");
      if (me->load_file == (FILE *) NULL)
      {
         fprintf(stderr, "file_open: can't open '%s' as icon file\n", me->load_file_name);
         exit(1);
      }

      LoadIcon(me);

      fclose(me->load_file);

      printf("done loading\n");
   }
   else
      printf("loading cancelled\n");
}


void file_save(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;
   int okay;
   char *string;

   printf("saving icon ...\n");

   if (strlen(me->save_file_name) == 0)
   {
      new_file_name = GetString("Enter file name to save as (file.icon)\n", NULL);

      if (new_file_name == (char *) NULL)
      {
         okay = FALSE;
      }
      else
      {
         if (strlen(new_file_name) < FILE_STRING_LEN)
            strcpy(me->save_file_name, new_file_name);
         else 
         {
            strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
            me->save_file_name[FILE_STRING_LEN - 1] = '\0';
         }

         okay = TRUE;
      }
   }
   else
   {
      okay = TRUE;
   }

   if (okay)
   {
      me->save_file = fopen(me->save_file_name, "w");
      if (me->save_file == (FILE *) NULL)
      {
         fprintf(stderr, "file_save: can't open '%s' as icon file\n", me->save_file_name);
         exit(1);
      }

      SaveIcon(me);

      me->project_saved = TRUE;

      fclose(me->save_file);

      printf("done saving\n");
   }
   else
      printf("save cancelled\n");
}


void file_save_as(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;

   printf("saving icon ...\n");

   new_file_name = GetString("Enter file name to save as (file.icon)\n", NULL);

   if ( (new_file_name != (char *) NULL) && (strlen(new_file_name) > 0) )
   {
      if (strlen(new_file_name) < FILE_STRING_LEN)
         strcpy(me->save_file_name, new_file_name);
      else 
      {
         strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
         me->save_file_name[FILE_STRING_LEN - 1] = '\0';
      }

      me->save_file = fopen(me->save_file_name, "w");
      if (me->save_file == (FILE *) NULL)
      {
         fprintf(stderr, "file_save_as: can't open '%s' as icon file\n", me->save_file_name);
         exit(1);
      }

      SaveIcon(me);

      me->project_saved = TRUE;

      fclose(me->save_file);

      printf("done saving\n");
   }
   else
      printf("saving cancelled\n");
}


void file_close(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char *new_file_name;
   int c;

   if (me->project_saved == FALSE)
   {
      okay = GetYesNo("Model file not saved!!\n\nDo you want to save it now?");  
      if (okay)
      {
         if (strlen(me->save_file_name) == 0)
         {
            new_file_name = GetString("Enter file name to save as (file.icon)\n", NULL);

            if ( (new_file_name != (char *) NULL) 
			&& (strlen(new_file_name) > 0) )
            {
               if (strlen(new_file_name) < FILE_STRING_LEN)
                  strcpy(me->save_file_name, new_file_name);
               else {
                  strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
                  me->save_file_name[FILE_STRING_LEN - 1] = '\0';
               }
            }
            else
            {
               printf("saving cancelled\n");
               okay = FALSE;
            }
         }

         if (okay)
         {
            me->save_file = fopen(me->save_file_name, "w");
            if (me->save_file == (FILE *) NULL)
            {
               fprintf(stderr, "file_close: can't open '%s' as icon file\n", me->save_file_name);
               exit(1);
            }

            SaveIcon(me);

            me->project_saved = TRUE;

            fclose(me->save_file);
         }
      }
   }

   me->project_loaded = FALSE;
   me->project_saved = FALSE;

   me->load_file_name[0] = '\0';
   me->save_file_name[0] = '\0';

   me->load_file = (FILE *) NULL;
   me->save_file = (FILE *) NULL;

   InitColorMap(me);
   ClearIcon(me);
   for (c = 0; c < MAX_COLOR_MAP; c++)
      UpdateButtonColor(c, me);
   UpdateDisplay(me);
   UpdatePreview(me);

   printf("files closed\n");
}


void file_about(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("Icon Edit\n\n  by Brian Lingard\n\nversion 1.0");  
}


void file_help(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("HELP\n----\n\nFile->Open - to load icon\nFile->Save - to save icon\nFile->Save As - save to new file\nFile->Close - close current file");  
}


void file_quit(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char *new_file_name;

   /* Do any cleanup that is necessary for your program here */

   if (me->project_saved == FALSE)
   {
      okay = GetYesNo("Icon file not saved!!\n\nDo you want to save it now?");  
      if (okay)
      {
         printf("saving icon ...\n");

         if (strlen(me->save_file_name) == 0)
         {
            new_file_name = GetString("Enter file name to save as (file.icon)\n", "");

            if (strlen(new_file_name) < FILE_STRING_LEN)
               strcpy(me->save_file_name, new_file_name);
            else {
               strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
               me->save_file_name[FILE_STRING_LEN - 1] = '\0';
            }
         }

         me->save_file = fopen(me->save_file_name, "w");
         if (me->save_file == (FILE *) NULL)
         {
            fprintf(stderr, "file_quit: can't open '%s' as icon file", me->save_file_name);
            exit(1);
         }

         SaveIcon(me);

         me->project_saved = TRUE;

         fclose(me->save_file);

         printf("done saving\n");
      }
   }

   okay = GetYesNo("Do you really want to quit?");  
   if (okay)
   {
      printf("We're out of here!!!\n");
      exit(0);
   }
}


/* options menu callbacks */

void icon_setup(Widget w, void *data)
{
  MyProgram *me=data;

  printf("setting up icon\n");

  if (iconset(&me->data))
  {
     printf("Cancelled!\n");
  }
  else
  {
     UpdateDisplay(me);
     UpdatePreview(me);
  }
}

void icon_clear(Widget w, void *data)
{
  int c;
  MyProgram *me=data;

  printf("clearing icon\n");

  ClearIcon(me);
  UpdateDisplay(me);
  UpdatePreview(me);
}

void palette_clear(Widget w, void *data)
{
  int c;
  MyProgram *me=data;

  printf("clearing palette\n");

  InitColorMap(me);
  for (c = 0; c < MAX_COLOR_MAP; c++)
     UpdateButtonColor(c, me);
  UpdateDisplay(me);
  UpdatePreview(me);
}

void flip_vert(Widget w, void *data)
{
  MyProgram *me=data;

  printf("flipping vertical\n");

  FlipIcon(FLIP_VERT, me);
  UpdateDisplay(me);
  UpdatePreview(me);
}

void flip_horiz(Widget w, void *data)
{
  MyProgram *me=data;

  printf("flipping horizontal\n");

  FlipIcon(FLIP_HORIZ, me);
  UpdateDisplay(me);
  UpdatePreview(me);
}

void rot_left(Widget w, void *data)
{
  MyProgram *me=data;

  printf("rotating left\n");

  RotateIcon(ROTATE_LEFT, me);
  UpdateDisplay(me);
  UpdatePreview(me);
}

void rot_right(Widget w, void *data)
{
  MyProgram *me=data;

  printf("rotating right\n");

  RotateIcon(ROTATE_RIGHT, me);
  UpdateDisplay(me);
  UpdatePreview(me);
}


/* color selection */

void color_1_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("current color is %d\n", COLOR_1_IDX);

  SetCurrentColor(COLOR_1_IDX, me);
}

void color_2_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("current color is %d\n", COLOR_2_IDX);

  SetCurrentColor(COLOR_2_IDX, me);
}

void color_3_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("current color is %d\n", COLOR_3_IDX);

  SetCurrentColor(COLOR_3_IDX, me);
}

void color_4_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("current color is %d\n", COLOR_4_IDX);

  SetCurrentColor(COLOR_4_IDX, me);
}

void color_5_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("current color is %d\n", COLOR_5_IDX);

  SetCurrentColor(COLOR_5_IDX, me);
}

void color_6_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("current color is %d\n", COLOR_6_IDX);

  SetCurrentColor(COLOR_6_IDX, me);
}

void color_7_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("current color is %d\n", COLOR_7_IDX);

  SetCurrentColor(COLOR_7_IDX, me);
}

void color_8_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("current color is %d\n", COLOR_8_IDX);

  SetCurrentColor(COLOR_8_IDX, me);
}


/* callback for edit color */
void edit_color(Widget w, void *data)
{
  MyProgram *me=data;
  unsigned char r, g, b;
  COLOR_RGB_T newcolor;

  printf("edit color\n");

  r = me->data.colormap.map[me->current_draw_color][R_IDX];
  g = me->data.colormap.map[me->current_draw_color][G_IDX];
  b = me->data.colormap.map[me->current_draw_color][B_IDX];

  if ( GetColor(&r, &g, &b) )
     printf("Cancelled!\n");
  else
  {
     newcolor[R_IDX] = r;
     newcolor[G_IDX] = g;
     newcolor[B_IDX] = b;

     UpdateColor(me->current_draw_color, newcolor, me);

     SetCurrentColor(me->current_draw_color, me);

     UpdateButtonColor(me->current_draw_color, me);

     UpdatePreview(me);

     UpdateDisplay(me);
  }
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

   UpdateDisplay(me);
}

void redisplay_preview(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   UpdatePreview(me);
}

void button_down(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;

/*
   printf("You clicked button %d at (%d,%d)\n", which_button, x,y);
*/

   CorrelatePick(x, y, me);
}


void button_up(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;
   int r, c;


/*
   printf("You released button %d at (%d,%d)\n", which_button, x,y);
*/

   CorrelatePick(x, y, me);

   if (me->grid.pick_flag) 
   {
      me->current_grid_color = me->current_draw_color;

      PaintGridCell(me->grid.pick_row, me->grid.pick_col, me);

      PaintPixel(me->grid.pick_row, me->grid.pick_col, me);
   }
   else
   {
      /* if user picked a box, then fill the box in */
      if ( (me->grid.pick_row >= me->grid.prev_pick_row) 
			&& (me->grid.pick_col >= me->grid.prev_pick_col) )
      {
         for (r = me->grid.prev_pick_row; r <= me->grid.pick_row; r++)
         {
            for (c = me->grid.prev_pick_col; c <= me->grid.pick_col; c++)
            {
               me->current_grid_color = me->current_draw_color;

               PaintGridCell(r, c, me);

               PaintPixel(r, c, me);
            }
         }
      }
   }
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
