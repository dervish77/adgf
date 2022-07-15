/*****************************************************************************
 *
 *	Soruce code for 8085 cross assembler.
 *
 *	File:	asm85.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	12/04/96
 *
 *	Revs:
 *	  0.0 	12/04/96  originated
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dev8085.h"




/*  OpenAsmSource	- opens specified asm source file
 *
 *  Parameters:
 *	filename	- file name of specified source file
 *	asm		- pointer to asm structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T 
OpenAsmSource( char *filename, ASM_S_T *asm_s )
{
   strcpy( &asm_s->src_file_name[0], filename );

   asm_s->src_fp = fopen( &asm_s->src_file_name[0], "r" );
   if ( asm_s->src_fp EQ (FILE *) NULL)
   {
      return(TRUE);
   }

   return(FALSE);
}


/*  CloseAsmSource	- closes current asm source file
 *
 *  Parameters:
 *	asm		- pointer to asm structure
 *
 *  Returns:
 *	error flag	- TRUE, if there was an error
 */
BOOLEAN_T 
CloseAsmSource( ASM_S_T *asm_s )
{
   fclose( asm_s->src_fp );

   return(FALSE);
}

  
/*  main	- main program
 *
 *  Parameters:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  Returns:
 *	none
 */
int main(int argc, char **argv)
{

   printf("Usage:  asm85 [-options] <source>\n");


   exit(0);
}


/* end of asm85.c */
