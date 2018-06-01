/***********************************************************************

  Drawing related functions using the LIBSX library.

   File:  	drwlibsx.c

   Author: 	Brian Lingard

   Date:	03/29/96

   Revisions:
	0.3	04/03/96	added demo mode
	0.0	03/29/96	Originated

***********************************************************************/



/* include necessary files */
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




/******************************************************************************
*  ClearScreenDisplay - clears the currently active display                   *
******************************************************************************/
void
ClearScreenDisplay(Widget w)
{
   SetDrawArea(w);
   ClearDrawArea();             
}


/******************************************************************************
*  SetDrawColor - sets current drawing color of the active display to the     *
*                 index specified                                             *
******************************************************************************/
void
SetDrawColor(int idx)	/* NOTE:  idx is libsx color index */
{
   SetColor(idx);
}


/******************************************************************************
*  PopupQuit                                                                  *
******************************************************************************/
void
PopupQuit(void)
{
   int 		okay;
   BUFFER_T	string;

   sprintf(string, "Quit Emu85?\n\n");

   okay = GetYesNo(string);  

   if (okay)
   {
      exit(0);
   }
}


/******************************************************************************
*  PopupFileRequest                                                           *
******************************************************************************/
char *PopupFileRequest(char *message)
{
   char *result;

   result = GetString( message, NULL );

   return(result);
}


/******************************************************************************
*  PopupAbout                                                                 *
******************************************************************************/
void
PopupAbout(void)
{
   int okay;
   BUFFER_T string;

   sprintf(string, 
	"    Emu85\n\nby Brian Lingard\n\n   version %1.1f\n\n", 
	VERSION);

   okay = GetYesNo(string);  
}


/******************************************************************************
*  PopupHelpMenu                                                              *
******************************************************************************/
void
PopupHelpMenu(void)
{
   int okay;
   char string[50];
   char help_text[1024];

   sprintf(help_text, "HELP Emu85 - Menus\n");

   sprintf(string,    "------------------\n\n");
   strcat(help_text, string); 

   sprintf(string,"File->Load Image       - load image file\n");
   strcat(help_text, string); 

   sprintf(string,"File->Quit             - quit program\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->ROM Setup     - setup ROM parameters\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->RAM Setup     - setup RAM parameters\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Clock Setup   - setup clock parameters\n"); 
   strcat(help_text, string); 

   sprintf(string,"Options->Status        - shows current status\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Display->MPU           - display MPU only\n"); 
   strcat(help_text, string); 

   sprintf(string,"Display->System        - display System only\n"); 
   strcat(help_text, string); 

   sprintf(string,"Display->MPU & System  - display MPU and System\n"); 
   strcat(help_text, string); 

   sprintf(string,"Display->Code Image    - display code image\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Control->Reset         - reset emulation\n"); 
   strcat(help_text, string); 

   sprintf(string,"Control->Step          - single step\n"); 
   strcat(help_text, string); 

   sprintf(string,"Control->Go            - run emulation\n"); 
   strcat(help_text, string); 

   sprintf(string,"Control->Halt          - stop emulation\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->About            - about Emu85\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->Menu Help        - help using menu items\n"); 
   strcat(help_text, string); 

   sprintf(string,"Help->Keys Help        - help using keys\n"); 
   strcat(help_text, string); 

   sprintf(string,"\n"); 
   strcat(help_text, string); 

   okay = GetYesNo(help_text);
}


/******************************************************************************
*  PopupHelpKeys                                                              *
******************************************************************************/
void
PopupHelpKeys(void)
{
   int okay;
   char string[50];
   char help_text[1024];

   sprintf(help_text, "HELP Emu85 - Keys\n");

   sprintf(string,    "-----------------\n\n");
   strcat(help_text, string); 

   sprintf(string,"Up arrow        - move up\n"); 
   strcat(help_text, string); 

   sprintf(string,"Down arrow      - move down\n"); 
   strcat(help_text, string); 

   sprintf(string,"Left arrow      - move left\n"); 
   strcat(help_text, string); 

   sprintf(string,"Right arrow     - move right\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"r               - reset\n"); 
   strcat(help_text, string); 

   sprintf(string,"s               - step\n"); 
   strcat(help_text, string); 

   sprintf(string,"g               - go\n"); 
   strcat(help_text, string); 

   sprintf(string,"h               - halt\n\n"); 
   strcat(help_text, string); 

   sprintf(string,"\n"); 
   strcat(help_text, string); 

   okay = GetYesNo(help_text);
}


/******************************************************************************
*  PopupStatus                                                                *
******************************************************************************/
void
PopupStatus(void *data)
{
   MyProgram *me=data;
   int okay;
   char status[512], string[50];

   printf("status\n");

   sprintf(status, "Current Status\n--------------\n");

   sprintf(string, "\nLoad File = %s\n", me->load_file_name);
   strcat(status, string);

   sprintf(string, "Save File = %s\n", me->save_file_name);
   strcat(status, string);

   sprintf(string, "\n");
   strcat(status, string);

   okay = GetYesNo(status);  
}



/* end of drwlibsx.c */
