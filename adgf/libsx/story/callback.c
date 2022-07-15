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
#include "main.h"
#endif

#ifndef _CALLBACK_H
#include "callback.h"
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


void file_new(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_project_name;

   printf("new project ...\n");

   new_project_name = GetString("Enter new project name\n", NULL);

   if ( (new_project_name != (char *) NULL) && (strlen(new_project_name) > 0) )
   {
      InitDatabase(me);

      if (strlen(new_project_name) < FILE_STRING_LEN)
         strcpy(me->proj.projname_str, new_project_name);
      else {
         strncpy(me->proj.projname_str, new_project_name, FILE_STRING_LEN);
         me->proj.projname_str[FILE_STRING_LEN - 1] = NULL_TERM;
      }

      UpdateDisplay(me);

      printf("new project is %s\n", me->proj.projname_str);
   }
   else
   {
      printf("new cancelled\n");
   }
}

void file_open(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;
   char *err_msg;

   printf("opening project ...\n");

   new_file_name = GetString("Enter file name to open (file.stb)\n", NULL);

   if ( (new_file_name != (char *) NULL) && (strlen(new_file_name) > 0) )
   {
      if (strlen(new_file_name) < FILE_STRING_LEN)
         strcpy(me->load_file_str, new_file_name);
      else {
         strncpy(me->load_file_str, new_file_name, FILE_STRING_LEN);
         me->load_file_str[FILE_STRING_LEN - 1] = NULL_TERM;
      }

      strcpy(me->save_file_str, me->load_file_str);

      me->load_file_p = fopen(me->load_file_str, "r");
      if (me->load_file_p EQ NULL_FILE_PTR)
      {
         sprintf(err_msg, "Could not open %s as input\n", me->load_file_str);
         PrintError(err_msg);
      }
      else
      {
         ReadProject(me);

         UpdateDisplay(me);

         fclose(me->load_file_p);

         printf("done opening\n");
      }
   }
   else
   {
      printf("open cancelled\n");
   }
}

void file_save(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;
   int okay;
   char *string;


   printf("saving project ...\n");

   if (strlen(me->save_file_str) == 0)
   {
      new_file_name = GetString("Enter file name to save as (file.stb)\n", NULL);

      if (new_file_name == (char *) NULL)
      {
         okay = FALSE;
      }
      else
      {
         if (strlen(new_file_name) < FILE_STRING_LEN)
            strcpy(me->save_file_str, new_file_name);
         else 
         {
            strncpy(me->save_file_str, new_file_name, FILE_STRING_LEN);
            me->save_file_str[FILE_STRING_LEN - 1] = '\0';
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
      me->save_file_p = fopen(me->save_file_str, "w");
      if (me->save_file_p == (FILE *) NULL)
      {
         fprintf(stderr, "Could not open '%s' for output\n", me->save_file_str);
      }

      SaveProject(me);

      me->project_saved = TRUE;

      fclose(me->save_file_p);

      printf("done saving to %s\n", me->save_file_str);
   }
   else
      printf("save cancelled\n");

}

void file_save_as(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;

   printf("saving project ...\n");

   new_file_name = GetString("Enter file name to save as (file.stb)\n", NULL);

   if ( (new_file_name != (char *) NULL) && (strlen(new_file_name) > 0) )
   {
      if (strlen(new_file_name) < FILE_STRING_LEN)
         strcpy(me->save_file_str, new_file_name);
      else 
      {
         strncpy(me->save_file_str, new_file_name, FILE_STRING_LEN);
         me->save_file_str[FILE_STRING_LEN - 1] = '\0';
      }

      me->save_file_p = fopen(me->save_file_str, "w");
      if (me->save_file_p == (FILE *) NULL)
      {
         fprintf(stderr, "Could not open '%s' for output\n", me->save_file_str);
      }

      SaveProject(me);

      me->project_saved = TRUE;

      fclose(me->save_file_p);

      printf("done saving to %s\n", me->save_file_str);
   }
   else
      printf("saving cancelled\n");

}

void file_print(Widget w, void *data)
{
   MyProgram *me=data;

   printf("printing\n");
}

void file_print_setup(Widget w, void *data)
{
   MyProgram *me=data;

   printf("print setup\n");
}

void file_prefs(Widget w, void *data)
{
   MyProgram *me=data;

   printf("prefs\n");
}

void file_close(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char *new_file_name;

   if (me->project_saved == FALSE)
   {
      okay = GetYesNo("Project not saved!!\n\nDo you want to save it now?");  
      if (okay)
      {
         if (strlen(me->save_file_str) == 0)
         {
            printf("saving project ...\n");

            new_file_name = GetString("Enter file name to save as (file.stb)\n", NULL);

            if ( (new_file_name != (char *) NULL) 
			&& (strlen(new_file_name) > 0) )
            {
               if (strlen(new_file_name) < FILE_STRING_LEN)
                  strcpy(me->save_file_str, new_file_name);
               else {
                  strncpy(me->save_file_str, new_file_name, FILE_STRING_LEN);
                  me->save_file_str[FILE_STRING_LEN - 1] = '\0';
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
            me->save_file_p = fopen(me->save_file_str, "w");
            if (me->save_file_p == (FILE *) NULL)
            {
               fprintf(stderr, "Could not open '%s' for output\n", me->save_file_str);
               exit(1);
            }

            SaveProject(me);

            me->project_saved = TRUE;

            fclose(me->save_file_p);
         }
      }
   }
   
   printf("project closed\n");
}

void file_quit(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char *new_file_name;

   if (me->project_saved == FALSE)
   {
      okay = GetYesNo("Project not saved!!\n\nDo you want to save it now?");  
      if (okay)
      {
         if (strlen(me->save_file_str) == 0)
         {
            printf("saving project ...\n");

            new_file_name = GetString("Enter file name to save as (file.stb)\n", NULL);

            if ( (new_file_name != (char *) NULL) 
			&& (strlen(new_file_name) > 0) )
            {
               if (strlen(new_file_name) < FILE_STRING_LEN)
                  strcpy(me->save_file_str, new_file_name);
               else {
                  strncpy(me->save_file_str, new_file_name, FILE_STRING_LEN);
                  me->save_file_str[FILE_STRING_LEN - 1] = '\0';
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
            me->save_file_p = fopen(me->save_file_str, "w");
            if (me->save_file_p == (FILE *) NULL)
            {
               fprintf(stderr, "Could not open '%s' for output\n", me->save_file_str);
               exit(1);
            }

            SaveProject(me);

            me->project_saved = TRUE;

            fclose(me->save_file_p);
         }
      }
   }

   okay = GetYesNo("Do you really want to quit?");  
   if (okay)
   {
      printf("We're out of here!!!\n");
      exit(0);
   }
}


/* edit callbacks */

void edit_undo(Widget w, void *data)
{
  MyProgram *me=data;

  printf("undo\n");
}

void edit_sel_all(Widget w, void *data)
{
  MyProgram *me=data;

  printf("select all\n");
}

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


/* view menu callbacks */

void view_all(Widget w, void *data)
{
  MyProgram *me=data;

  printf("view all\n");
}

void view_act(Widget w, void *data)
{
  MyProgram *me=data;

  printf("view act\n");
}

void view_scene(Widget w, void *data)
{
  MyProgram *me=data;

  printf("view scene\n");
}

void view_hier(Widget w, void *data)
{
  MyProgram *me=data;

  printf("view hierarchy\n");
}

void view_frames(Widget w, void *data)
{
  MyProgram *me=data;

  printf("view frames\n");
}

void view_slides(Widget w, void *data)
{
  MyProgram *me=data;

  printf("view slide show\n");
}


/* function menu callbacks */

void func_add_act(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func add act\n");
}

void func_add_scene(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func add scene\n");
}

void func_add_frame(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func add frame\n");
}

void func_del_act(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func delete act\n");
}

void func_del_scene(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func delete scene\n");
}

void func_del_frame(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func delete frame\n");
}

void func_edit_sel(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func edit selected\n");
}

void func_edit_frame(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func edit frame\n");
}

void func_rearrange(Widget w, void *data)
{
  MyProgram *me=data;

  printf("func re-arrange\n");
}


/* tools menu callbacks */

void tools_select(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools select\n");
}

void tools_line(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools line\n");
}

void tools_freehand(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools freehand\n");
}

void tools_rectangle(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools rectangle\n");
}

void tools_circle(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools circle\n");
}

void tools_arc(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools arc\n");
}

void tools_fill_rect(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools fill rectangle\n");
}

void tools_fill_circle(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools fill circle\n");
}

void tools_fill_style(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools fill style\n");
}

void tools_patt_style(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools pattern style\n");
}

void tools_import_bm(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools import bitmap\n");
}

void tools_export_bm(Widget w, void *data)
{
  MyProgram *me=data;

  printf("tools export bitmap\n");
}


/* help menu callbacks */

void help_about(Widget w, void *data)
{
   int okay;
   char string[BUFFER_LEN];

   sprintf(string, "Story Board Master\n\nby Brian Lingard\n\nversion %s", 
								VERSION);

   okay = GetYesNo(string);  
}

void help_brief(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("HELP\n----\n\nFile->Open - to load story board\nSave - to save story board\nSave As - save to new file\nClose - close current file");  
}

void help_search(Widget w, void *data)
{
  MyProgram *me=data;

  printf("help search\n");
}

void help_index(Widget w, void *data)
{
  MyProgram *me=data;

  printf("help index\n");
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


