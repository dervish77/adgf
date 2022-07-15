/*****************************************************************************
 *
 *  Utility for diff'ing two binary files
 *
 *	File:	bindiff.c
 *
 *	Usage:	bindiff file1 file2
 *
 *	Options:
 *		-h	  - get options help
 *		-s        - suppress verbose output
 *
 *	Date:	08/24/2000
 *
 *	Revisions:
 *	  0.0 08/24/2000  Originated
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>

#define  MAX_ROM_SIZE            524288
#define  CRC_SIZE                   4

static unsigned char array1[MAX_ROM_SIZE], array2[MAX_ROM_SIZE];


int 
main(int argc, char *argv[])
{
   int i;
   FILE *input1, *input2;
   int differ = 0;

   printf("\nbindiff -- Diff'ing binary files\n");

   if((input1=fopen(argv[1], "rb")) == NULL) 
      return;

   if((input2=fopen(argv[2], "rb")) == NULL) 
     return;

   fread(array1, 1, MAX_ROM_SIZE, input1);
   fread(array2, 1, MAX_ROM_SIZE, input2);

   for (i=0; i <  MAX_ROM_SIZE; i++)
   {
      if (array1[i] != array2[i]) 
      {
         printf("OFFSET = %08d, FILE1 = %02x, FILE2 = %02x\n", i, array1[i], array2[i]);
         differ = 1;
      }
   }

   if (differ)
      printf("Files are different.\n");
   else
      printf("Files are identical.\n");

   fclose(input1);
   fclose(input2);

   return 0;
}  /*end main*/


