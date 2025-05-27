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


/* file callbacks */

void file_open(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;

   printf("loading image ...\n");

   new_file_name = GetString("Enter file name to open (file.ppm)\n", "");

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
         fprintf(stderr, "file_open: can't open '%s' as image file\n", me->load_file_name);
         exit(1);
      }

      LoadImage(me);

      me->project_loaded = TRUE;

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

   printf("saving image ...\n");

   if (strlen(me->save_file_name) == 0)
   {
      new_file_name = GetString("Enter file name to save as (file.ppm)\n", NULL);

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
         fprintf(stderr, "file_save: can't open '%s' as image file\n", me->save_file_name);
         exit(1);
      }

      SaveImage(me);

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

   printf("saving image ...\n");

   new_file_name = GetString("Enter file name to save as (file.ppm)\n", NULL);

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
         fprintf(stderr, "file_save_as: can't open '%s' as image file\n", me->save_file_name);
         exit(1);
      }

      SaveImage(me);

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

   if (me->project_saved == FALSE)
   {
      okay = GetYesNo("Image file not saved!!\n\nDo you want to save it now?");  
      if (okay)
      {
         if (strlen(me->save_file_name) == 0)
         {
            new_file_name = GetString("Enter file name to save as (file.ppm)\n", NULL);

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
               fprintf(stderr, "file_close: can't open '%s' as image file\n", me->save_file_name);
               exit(1);
            }

            SaveImage(me);

            me->project_saved = TRUE;

            fclose(me->save_file);
         }
      }
   }

   InitDatabase(me);
   UpdateDisplay(me);
   
   printf("files closed\n");
}


void file_about(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("Image\n\n  by Brian Lingard\n\nversion 1.0");  
}


void file_help(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("HELP\n----\n\nFile->Open - load image\nFile->Save - save image\nFile->Save As - save to new image file\nFile->Close - close current image file");  
}


void file_quit(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char *new_file_name;

   /* Do any cleanup that is necessary for your program here */

   if (me->project_saved == FALSE)
   {
      okay = GetYesNo("Image file not saved!!\n\nDo you want to save it now?");  
      if (okay)
      {
         printf("saving image ...\n");

         if (strlen(me->save_file_name) == 0)
         {
            new_file_name = GetString("Enter file name to save as (file.ppm)\n", "");

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
            fprintf(stderr, "file_quit: can't open '%s' as image file", me->save_file_name);
            exit(1);
         }

         SaveImage(me);

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


/* command callbacks */

void cmd_revert(Widget w, void *data)
{
  MyProgram *me=data;

  printf("reverting to original image ...\n");

  CopyImageBuff(&me->data.original, &me->data.current);

  me->project_saved = TRUE;

  me->data.image_is_grey = FALSE;

  InitializeLUT(me);

  UpdateDisplay(me);
}

void cmd_histogram(Widget w, void *data)
{
  MyProgram *me=data;

  printf("computing histogram ...\n");

  GenerateHistogram(me);

  printf("   max value = %d, max index = %d\n", me->data.hist.max_count, me->data.hist.max_index);
  printf("   min value = %d, min index = %d\n", me->data.hist.min_count, me->data.hist.min_index);

  DrawHistogram(me);

}

void cmd_threshold(Widget w, void *data)
{
  MyProgram *me=data;
  char *string;
  int threshold;

  printf("thresholding ...\n");

  string = GetString("Enter threshold (default 128)\n", "");

  if (strlen(string) < 1)
     threshold = 128;
  else
     threshold = atoi(string);

  SetBWThreshold(me, threshold);

  PointProcessImageBuff(me);

  me->project_saved = FALSE;

  UpdateDisplay(me);
}

void cmd_brighten(Widget w, void *data)
{
  MyProgram *me=data;
  char *string;
  int factor;

  printf("brightening ...\n");

  string = GetString("Enter brightness factor (default 10)\n", "");

  if (strlen(string) < 1)
     factor = 10;
  else
     factor = atoi(string);

  SetBrightnessFactor(me, factor);

  PointProcessImageBuff(me);

  me->project_saved = FALSE;

  UpdateDisplay(me);
}

void cmd_color2grey(Widget w, void *data)
{
  MyProgram *me=data;

  printf("converting from color to grey ...\n");

  Color2GreyImageBuff(me);

  me->project_saved = FALSE;

  me->data.image_is_grey = TRUE;

  UpdateDisplay(me);
}

void cmd_negative(Widget w, void *data)
{
  MyProgram *me=data;

  printf("negating image ...\n");

  SetNegate(me);

  PointProcessImageBuff(me);

  me->project_saved = FALSE;

  UpdateDisplay(me);
}

void cmd_median(Widget w, void *data)
{
  MyProgram *me=data;

  printf("computing median ...\n");

  MedianFilterImageBuff(me);

  me->project_saved = FALSE;

  UpdateDisplay(me);
}

void cmd_blur(Widget w, void *data)
{
  MyProgram *me=data;

  printf("blurring image ...\n");

  SetDefaultBlurFilter(me);

  BlurImageBuff(me);

  me->project_saved = FALSE;

  UpdateDisplay(me);
}

void cmd_sharpen(Widget w, void *data)
{
  MyProgram *me=data;

  printf("sharpening image ...\n");

  SetDefaultSharpenFilter(me);

  SharpenImageBuff(me);

  me->project_saved = FALSE;

  UpdateDisplay(me);
}

void cmd_edge_detect(Widget w, void *data)
{
  MyProgram *me=data;

  printf("detecting edges ...\n");

  me->project_saved = FALSE;
}



/* options callbacks */

void opt_dump_database(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;

   okay = GetYesNo("Do you really want to\ndump the entire database?"); 

   if (okay == TRUE)
   {
      printf("dumping database ... ");
      DumpDatabase(me);
      printf("done dumping\n");
   }
}

void opt_status(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char status[200], string[50];

   sprintf(status, "Current Status\n--------------\n");

   sprintf(string, "\nLoad File = %s\n", me->load_file_name);
   strcat(status, string);

   sprintf(string, "Save File = %s\n", me->save_file_name);
   strcat(status, string);

   sprintf(string, "\nWidth = %d\n", me->data.original.csize);
   strcat(status, string);

   sprintf(string, "Height = %d\n", me->data.original.rsize);
   strcat(status, string);

   okay = GetYesNo(status); 
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




void redisplay_hist(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   DrawHistogram(me);
}


void redisplay_lut(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   DrawLUT(me);
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
