/***********************************************************************

 Main routines for the 8085 Emulator.

   File:  	emu.c

   Author: 	Brian Lingard

   Date:	02/02/98

   Revisions:
	0.0	02/02/98	Originated

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>

#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "emu.h" */
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif




/* 
 *  LOCAL STATIC GLOBALS
 */
BOOLEAN_T init_once = FALSE;	/* init control flag */





/******************************************************************************
*  InitDatabase - initializes pointers to global database arrays              *
******************************************************************************/
void
InitDatabase(MyProgram *data)
{
   fprintf(stdout, "Initializing database...\n");

   /*  init general items 
    */
   data->file_loaded = FALSE;
   data->file_saved = FALSE;
   data->load_file_name[0] = '\0';
   data->save_file_name[0] = '\0';
   data->load_file = (FILE *) NULL;
   data->save_file = (FILE *) NULL;
   data->mouse_pick.x = 0;
   data->mouse_pick.y = 0;

   data->status.display = DISPLAY_MPU;
   data->status.control = CONTROL_RESET;



}


/******************************************************************************
*  LoadImage - loads emu image file                                           *
*                                                                             *
*  expected format:                                                           *
*                                                                             *
*                                                                             *
******************************************************************************/
void
LoadImage(MyProgram *data)
{
   FILE *infile;
   int r, c;
   BUFFER_T string;


   infile = data->load_file;

   fscanf(infile, "%s\n", string);

   if ( strncmp( string, "survival", 8) == 0)
   {


      UpdateDisplay(data);
   }
   else
   {
      fprintf(stderr, "LoadImage:  unknown file format\n");
      exit(1);
   }
}



/******************************************************************************
*  UpdateDisplay - updates screen display following changes in the database   *
******************************************************************************/
void
UpdateDisplay(MyProgram *data)
{
   int r, c;			/* loop indices */
   int idx;

   ClearScreenDisplay(data->draw_area_widget);

}


/******************************************************************************
*  UpdateStatus - updates status display following changes in the database   *
******************************************************************************/
void
UpdateStatus(MyProgram *data)
{
   int r, c;			/* loop indices */
   int idx;

   ClearScreenDisplay(data->status_area_widget);

}


/******************************************************************************
*  HandleLoadImage  - handle processing for load image                        *
******************************************************************************/
void
HandleLoadImage(MyProgram *me)
{
   char *new_file_name;
   int okay;


   if (strlen(me->load_file_name) == 0)
   {
      new_file_name = PopupFileRequest("Enter file name to load as (file.emu)\n");

      if (new_file_name == (char *) NULL)
      {
         okay = FALSE;
      }
      else
      {
         if (strlen(new_file_name) < FILE_STRING_LEN)
            strcpy(me->load_file_name, new_file_name);
         else 
         {
            strncpy(me->load_file_name, new_file_name, FILE_STRING_LEN);
            me->load_file_name[FILE_STRING_LEN - 1] = '\0';
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
      me->load_file = fopen(me->load_file_name, "r");
      if (me->load_file == (FILE *) NULL)
      {
         fprintf(stderr, 
		"file_load: can't open '%s' as game save file\n", 
		me->load_file_name);
         exit(1);
      }

      LoadImage(me);

      me->file_loaded = TRUE;

      fclose(me->load_file);

      printf("done loading\n");
   }
   else
   {
      printf("load cancelled\n");
   }
}


/******************************************************************************
*  HandleControl  - handle processing for control                             *
******************************************************************************/
void
HandleControl(MyProgram *data)
{



}



/* 
 * nrand() - normalized rand(), returns floating point random number
 *		between -1.0 and 1.0
 *
 * PARAMETERS
 *	none
 *
 * RETURNS
 *	rand	- normalized random number
 *
 */
float nrand(void)
{
   return(2.0*(rand() / (float)RAND_MAX) - 1.0);
}


/* 
 * seed_random() - seed random number generator 
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
int seed_random()
{
   srand((unsigned int)time(NULL));
}


/* 
 * int_random() - scaled integer random number 
 *
 * PARAMETERS
 *	min_value	- minimum value
 *	max_value	- maximum value
 *
 * RETURNS
 *	int_rand_num	- scaled random number
 *
 */
int int_random(int min_value, int max_value)
{
   float rand_raw, rand_num;
   int int_rand_num;

   /*  get raw random number
    */
   rand_raw = nrand();

   /*  make it positive
    */
   if (rand_raw < 0)
   {
      rand_raw = rand_raw * (-1);
   }
 
   /*  scale by min and max values
    */
   rand_num = ((max_value - min_value) * rand_raw) + min_value;

   /*  convert to integer and output
    */
   int_rand_num = (int) rand_num;

   return(int_rand_num);
}


/******************************************************************************
*  ParseString - parses list of strings into array of strings                 *
******************************************************************************/
int 
ParseString(char *string, char *args[])
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of ParseString() */



/* end of emu.c */
