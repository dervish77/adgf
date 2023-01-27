/*****************************************************************************
 *
 *  Utility for dumping contents of a binary file to screen.
 *
 *	File:	bindump.c
 *
 *	Usage:	bindump [-h] [-a] [-n NNN] [-r BB] file
 *
 *	Options:
 *		-h	- get options help
 *		-a	- suppress ascii interpretation
 *		-n NNN	- specify block size of NNN bytes (default 256)
 *		-r BB	- specify BB bytes per row (default 16)
 *
 *	Date:	02/12/96
 *
 *	Revisions:
 *	  0.8  02/21/96  added column dividers for binary section
 *	  0.6  02/21/96  fixed bug in binary output
 *	  0.0  02/12/96  Originated
 *****************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


#define DEFAULT_BLOCK_SIZE	256		/* 256 bytes */

#define DEFAULT_BYTES_PER_ROW	16

typedef char BOOLEAN_T;



/*  define global variables
 */
FILE		*in_file_p;
BOOLEAN_T	suppress_ascii = FALSE;

int		base = 0;


/*  DumpBlock	- read a block of size bytes from input file
 *		and send to output file
 *
 *  PARAMETERS:
 *	size		- size of block in bytes
 *	bytes_per_row	- bytes per row
 *	out_file_p	- output file pointer
 *
 *  RETURNS:
 *	eof		- TRUE if at EOF
 */
BOOLEAN_T
DumpBlock(int size, int bytes_per_row, FILE *out_file_p)
{
   int r, b;
   int num_rows;
   int actual_bytes_in_row;

   unsigned char row_array[DEFAULT_BYTES_PER_ROW];
   int c;

   int at_eof;


   num_rows = size / bytes_per_row;

   fprintf(out_file_p, "\nByte        Data");

   if (suppress_ascii)
      fprintf(out_file_p, "\n");
   else
   {
      for (b = 2; b < bytes_per_row; b++)
      {
         fprintf(out_file_p, "  ");
         if ( ((b+1) % 4) == 0 )
            fprintf(out_file_p, " ");
      }

      fprintf(out_file_p, "    Ascii\n");
   }



   at_eof = FALSE;

   for (r = 0; r < num_rows; r++)
   {
      fprintf(out_file_p, "%08d    ", ((r * bytes_per_row) + base));

      actual_bytes_in_row = 0;

      for (b = 0; b < bytes_per_row; b++)
      {
         c = getc(in_file_p);
         if (c == EOF)
         {
            at_eof = TRUE;
            break;
         }

         row_array[b] = (unsigned char) c;

         fprintf(out_file_p, "%02X", row_array[b]);

         if ( ((b+1) % 4) == 0 )
            fprintf(out_file_p, " ");

         actual_bytes_in_row++;
      }

      if (!suppress_ascii)
      {
         if (actual_bytes_in_row < bytes_per_row)
         {
            for (b = actual_bytes_in_row; b < bytes_per_row; b++)
            {
               fprintf(out_file_p, "  ");
               if ( ((b+1) % 4) == 0 )
                  fprintf(out_file_p, " ");
            }
         }

         fprintf(out_file_p, "    ");

         for (b = 0; b < actual_bytes_in_row; b++)
         {
            if ( isprint( row_array[b] ) )
               fprintf(out_file_p, "%c", row_array[b]);
            else
               fprintf(out_file_p, ".");
         }
      }

      fprintf(out_file_p, "\n");

      if (at_eof)
         return(TRUE);
   }

   base += size;

   return(FALSE);
}


/*  main	- main program
 *
 *  PARAMETERS:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  RETURNS:
 *	none
 */
int
main(int argc, char **argv)
{
   int		i;

   int		block_size = DEFAULT_BLOCK_SIZE;
   int		bytes_per_row = DEFAULT_BYTES_PER_ROW;

   BOOLEAN_T	done;

   char		response[20];		/* response buffer */



   switch (argc)
   {
      case 1:
         fprintf(stderr,
		"Usage:  %s [-h] [-a] [-n NNN] [-r BB] file\n", argv[0]);
         exit(1);

      default:
         i = 1;
         while (i < argc)
         {
            if (argv[i][0] == '-')
            {
               switch(argv[i][1])
               {
                  case 'h':
                     fprintf(stderr,
			"Usage:  %s [-h] [-a] [-n NNN] [-r BB] file\n",
			argv[0]);
                     fprintf(stderr,"    -h      get help\n");
                     fprintf(stderr,"    -a      suppress ascii\n");
                     fprintf(stderr,"    -n NNN  set block size\n");
                     fprintf(stderr,"    -r BB   bytes per row\n");
                     fprintf(stderr,"    file    any binary or ascii\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'a':
                     suppress_ascii = TRUE;
                     break;

                  case 'n':
                     block_size = atoi(argv[i+1]);
                     i++;
                     break;

                  case 'r':
                     bytes_per_row = atoi(argv[i+1]);
                     i++;
                     break;

                  default:
                     fprintf(stderr,
			"Usage: %s [-h] [-a] [-n NNN] [-r BB] file\n",
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               in_file_p = fopen(argv[i], "r");
               if (in_file_p == (FILE *)NULL)
               {
                  fprintf(stderr, "Couldn't open %s as input\n", argv[i]);
                  exit(1);
               }
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */


   done = FALSE;

   while ( !done )
   {
      /* if DumpBlock returns EOF, set done flag */
      if ( DumpBlock( block_size, bytes_per_row, stdout) )
      {
         done = TRUE;
      }

      /* else, prompt for next block */
      else
      {
         printf("\nDump next block (Y/n)? ");

         if ( fgets( &response[0], 20, stdin ) == NULL )
         {
            exit(1);
         }

         if ( (response[0] == 'n') || (response[0] == 'N'))
         {
            done = TRUE;
         }
      }
   }

   printf("\n");

   exit(0);
}


/* end of bindump.c */
