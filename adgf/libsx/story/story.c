/***********************************************************************

 Top-level database functions for story board generation program.

   File:  	story.c

   Author: 	Brian Lingard

   Date:	4/8/95

   Revisions:
	0.2	02/12/96  Reduced database to two levels (removed frames)
	0.1	02/06/96  Touched up defines and typedefs
	0.0	04/08/95  Originated

***********************************************************************/

/*  include necessary files 
 */
#include <stdio.h>

#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif



/*  declare global variables
 */



/* 
 * InitDatabase() 
 *	- initialize the main database by setting the project 
 *	loaded and saved flags to FALSE, and by allocating memory for
 *	the various sub-structures for the current project, drawing info,
 * 	view info and for the printing info.
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 */
void
InitDatabase(MyProgram *data)
{
   PROJECT_S_T		*ps_p;
   DRAW_INFO_S_T	*dis_p;
   VIEW_INFO_S_T	*vis_p;
   PRINT_INFO_S_T	*pis_p;


#ifdef _DEBUG_STORY
   printf("initializing database\n");
#endif

   data->project_loaded = FALSE;
   data->project_saved = FALSE;

   data->load_file_str[0] = NULL_TERM;
   data->save_file_str[0] = NULL_TERM;

   data->load_file_p = NULL_FILE_PTR;
   data->save_file_p = NULL_FILE_PTR;

   data->proj.projname_str[0] = NULL_TERM;

   data->proj.num_of_acts = 4;
   data->proj.num_of_scenes = 60;

   data->proj.first_act_p = NULL_ACT_PTR;
   data->proj.last_act_p = NULL_ACT_PTR;

   data->draw.draw_mode = DRAW_SELECT;
   data->draw.fill_mode = FILL_NONE;
   data->draw.pattern_mode = PATTERN_V_LINE;
   data->draw.color_mode = COLOR_NONE;

   data->view.view_mode = VIEW_SINGLE;
   data->view.num_vert = 1;
   data->view.num_horiz = 1;
   data->view.delay_to_next = DEFAULT_DELAY_TO_NEXT;

   data->print.print_mode = PRINT_TO_NULL;
   data->print.filename_str[0] = NULL_TERM;
   data->print.file_p = NULL_FILE_PTR;

   OutputDatabase(data);
} /* end of InitDatabase() */


/* 
 * FreeProject() 
 *	- free all allocated memory before exiting
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 */
void
FreeProject(MyProgram *data)
{


#ifdef _DEBUG_STORY
   fprintf(stderr, "free'd all memory!\n");
#endif
} /* end of FreeDatabase() */


/* 
 * OutputDatabase() 
 *	- output main database to specified output file
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 */
void
OutputDatabase(MyProgram *data)
{
   FILE *outfile;

   outfile = fopen( DEFAULT_LOG_FILE_NAME, "w");
   if (outfile EQ NULL_FILE_PTR)
   {
      ExitError("InitDatabase:  failed to open log file");
   }

#ifdef _DEBUG_STORY
   printf("outputting log file\n");
#endif

   fprintf(outfile, "Current Project Database:\n");

   fprintf(outfile, "  project loaded  = %d\n", data->project_loaded);
   fprintf(outfile, "  project saved   = %d\n", data->project_saved);
   fprintf(outfile, "  load file       = %s\n", data->load_file_str);
   fprintf(outfile, "  save file       = %s\n", data->save_file_str);

   fprintf(outfile, "  project:\n");
   fprintf(outfile, "    project name  = %s\n", data->proj.projname_str);
   fprintf(outfile, "    num of acts   = %d\n", data->proj.num_of_acts);
   fprintf(outfile, "    num of scenes = %d\n", data->proj.num_of_scenes);

   fprintf(outfile, "  draw info:\n");
   fprintf(outfile, "    draw mode     = %d\n", data->draw.draw_mode);
   fprintf(outfile, "    fill mode     = %d\n", data->draw.fill_mode);
   fprintf(outfile, "    pattern mode  = %d\n", data->draw.pattern_mode);
   fprintf(outfile, "    color mode    = %d\n", data->draw.color_mode);

   fprintf(outfile, "  view info:\n");
   fprintf(outfile, "    view mode     = %d\n", data->view.view_mode);
   fprintf(outfile, "    num vert      = %d\n", data->view.num_vert);
   fprintf(outfile, "    num horiz     = %d\n", data->view.num_horiz);
   fprintf(outfile, "    delay to next = %d\n", data->view.delay_to_next);

   fprintf(outfile, "  print info:\n");
   fprintf(outfile, "    print mode    = %d\n", data->print.print_mode);
   fprintf(outfile, "    print file    = %s\n", data->print.filename_str);

   fclose(outfile);
} /* end of OutputDatabase() */


/* 
 * ReadProject() 
 *	- Reads in the project pointed to by initialized project
 *	file pointer.  Allocates memory for acts, scenes, and frames
 *	as necessary.
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 *
 * FORMAT
 *   File Header (48 bytes):
 *	bytes 0 - 2		file type - characters "SBM"
 *	byte  3			color flag - currently always 0
 *	bytes 4 - 35		project name - 32 characters
 *	bytes 36 - 39		total number of acts
 *	bytes 40 - 43		total number of scenes
 *
 *	bytes 44 - MMM		FFFF frame records
 *
 *   Frame Record (minimum 90 bytes - for all white 100x100 bitmap, 
 *                 with no notes):
 *	byte  0			act number
 *	byte  1			scene number
 *	bytes 2 - 3		bitmap height in pixels (min 100)
 *	bytes 4 - 5		bitmap width in pixels (min 100)
 *	bytes 6 - 25		action string - 20 characters
 *	bytes 26 - 45		dialog string - 20 characters
 *	bytes 46 - 65		sound string - 20 characters
 *	byte  66		number of lines in notes (0 - 20)
 *	bytes 67 - LLL		notes string - LL lines of 80 chars per line
 *	bytes LLL - NNNN	bitmap data (row major order, starting with
 *				top-left pixel, one byte per pixel, and
 *				RLE encoded)
 */
void
ReadProject(MyProgram *data)
{
   char		id0, id1, id2;
   BUFFER_T 	buffer;
   ULONG_T	long_temp;
   UBYTE_T	*long_ptr;
   int		i;


   /*  read and check file type code
    */
   id0 = (char) getc( data->load_file_p );
   id1 = (char) getc( data->load_file_p );
   id2 = (char) getc( data->load_file_p );

   if ( (id0 EQ 'S') AND (id1 EQ 'B') AND (id2 EQ 'M') )
   {
      /*  read color flag
       */
      data->draw.color_mode = (COLOR_MODE_T) getc( data->load_file_p );

      /*  read in project name 
       */
      for (i = 0; i < FILE_STRING_LEN; i++)
      {
         data->proj.projname_str[i] = getc( data->load_file_p );
      } 

      /*  read total number of acts
       */
      long_ptr = (UBYTE_T *)&long_temp;
      for (i = 0; i < sizeof(ULONG_T); i++)
      {
         *(long_ptr++) = getc( data->load_file_p );
      }
      data->proj.num_of_acts = long_temp;

      /*  read total number of scenes
       */
      long_ptr = (UBYTE_T *)&long_temp;
      for (i = 0; i < sizeof(ULONG_T); i++)
      {
         *(long_ptr++) = getc( data->load_file_p );
      }
      data->proj.num_of_scenes = long_temp;


      data->project_loaded = TRUE;
      data->project_saved = TRUE;
   }
   else
   {
      sprintf(buffer, "ReadProject:  file %s is not of type SBM\n", 
						data->load_file_str);
      PrintError(buffer);
   }

   OutputDatabase(data);
} /* end of ReadProject() */


/* 
 * SaveProject() 
 *	- Saves the project database to the project file pointer.  
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 *
 * FORMAT
 *   File Header (48 bytes):
 *	bytes 0 - 2		file type - characters "SBM"
 *	byte  3			color flag - currently always 0
 *	bytes 4 - 35		project name - 32 characters
 *	bytes 36 - 39		total number of acts
 *	bytes 40 - 43		total number of scenes
 *
 *	bytes 44 - MMM		FFFF frame records
 *
 *   Frame Record (minimum 90 bytes - for all white 100x100 bitmap, 
 *                 with no notes):
 *	byte  0			act number
 *	byte  1			scene number
 *	bytes 2 - 3		bitmap height in pixels (min 100)
 *	bytes 4 - 5		bitmap width in pixels (min 100)
 *	bytes 6 - 25		action string - 20 characters
 *	bytes 26 - 45		dialog string - 20 characters
 *	bytes 46 - 65		sound string - 20 characters
 *	byte  66		number of lines in notes (0 - 20)
 *	bytes 67 - LLL		notes string - LL lines of 80 chars per line
 *	bytes LLL - NNNN	bitmap data (row major order, starting with
 *				top-left pixel, one byte per pixel, and
 *				RLE encoded)
 */
void
SaveProject(MyProgram *data)
{
   BUFFER_T 	buffer;
   int		i;
   UBYTE_T	*long_ptr;

   putc('S', data->save_file_p);
   putc('B', data->save_file_p);
   putc('M', data->save_file_p);

   putc(data->draw.color_mode, data->save_file_p);

   for (i = 0; i < FILE_STRING_LEN; i++)
   {
      putc(data->proj.projname_str[i], data->save_file_p);
   }

   long_ptr = (UBYTE_T *)&data->proj.num_of_acts;
   for (i = 0; i < sizeof(ULONG_T); i++)
   {
      putc(*(long_ptr++), data->save_file_p);
   }

   long_ptr = (UBYTE_T *)&data->proj.num_of_scenes;
   for (i = 0; i < sizeof(ULONG_T); i++)
   {
      putc(*(long_ptr++), data->save_file_p);
   }

   data->project_saved = TRUE;

   OutputDatabase(data);
} /* end of SaveProject() */


/* 
 * UpdateDisplay() 
 *	- updates the main drawing area with current database
 *
 * PARAMETERS
 *	err_string	- pointer to error message string
 *
 * RETURNS
 *	nothing
 */
void
UpdateDisplay(MyProgram *data)
{

#ifdef _DEBUG_STORY
   printf("updating display\n");
#endif

   /*  start with a clean slate 
    */
   ClearDrawArea();             

   /*  update header label area 
    */
   DrawHeader(data);

   /*  drawing current scene  
    */
   DrawScene(data);
}


/* 
 * PrintError() 
 *	- prints error message to stderr (does not exit)
 *
 * PARAMETERS
 *	err_string	- pointer to error message string
 *
 * RETURNS
 *	nothing
 */
void
PrintError(char *err_string)
{
   fprintf(stderr, "%s\n", err_string);
}


/* 
 * ExitError() 
 *	- prints error message to stderr, then exits
 *
 * PARAMETERS
 *	err_string	- pointer to error message string
 *
 * RETURNS
 *	nothing
 */
void
ExitError(char *err_string)
{
   fprintf(stderr, "%s\n", err_string);
   exit(1);
}


/* 
 * ParseString() 
 *	- parses list of strings into array of strings
 *
 * PARAMETERS
 *	string	- pointer to a list of strings
 *	args	- pointer to array of substrings
 *
 * RETURNS
 *	count	- number of substrings in args
 */
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


/* end of story.c */
