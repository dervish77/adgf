/*****************************************************************************
 *
 *  Utility for splitting a binary file into chunk of specified size.
 *
 *	File:	binsplit.c
 *
 *	Usage:	binsplit [-h] [-n bytes] [-i file] [-r file]
 *
 *	Options:
 *		-h	  - get options help
 *		-n bytes  - chunk size in bytes (default "256")
 *		-i file   - input file name (default "file.bin")
 *		-r file   - root file name (default "file.out")
 *		-s        - suppress verbose output
 *
 *	Notes:
 *	- splits input file into chunks of "bytes"
 *	- creates .000 file that contains original file name and file size
 *	- last chunk will either be the remaining bytes or size 0
 *
 *
 *	Date:	08/24/2000
 *
 *	Revisions:
 *	  0.0 08/24/2000  Originated
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


typedef char BOOLEAN_T;



/*  define global variables
 */
int		base = 0;


/*  CountData	- counts bytes in binary file
 *
 *  PARAMETERS:
 *	in_file_p	- input file pointer
 *
 *  RETURNS:
 *	size		- number of bytes converted
 */
int
CountData(FILE *in_file_p)
{
   int c;
   int size = 0;

   while ( (c = getc(in_file_p)) != EOF )
   {
      size++;
   }

   return(size);
}


/*  CopyData	- copy binary data to appended file
 *
 *  PARAMETERS:
 *	in_file_p	- input file pointer
 *	out_file_p	- output file pointer
 *
 *  RETURNS:
 *	count		- number of bytes copied
 */
int
CopyData(FILE *in_file_p, FILE *out_file_p, int size)
{
   int i;
   int count = 0;

   unsigned char c;

   while(!feof(in_file_p) && (count < size))
   {
      c = fgetc(in_file_p);

      if (!feof(in_file_p))
      {
         fputc(c, out_file_p);
         count++;
      }
      else
      {
         return(count);
      }
   }

   return(count);
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
   int		i, data = 0, size = 256, suffix = 1, count = 256;

   char		input_file_name[40];	/* buffer */
   char		root_file_name[40];	/* buffer */
   char		output_file_name[40];	/* buffer */
   char		array_name[40];		/* buffer */

   FILE		*in_file_p;
   FILE		*out_file_p;

   BOOLEAN_T	verbose = TRUE;

   switch (argc)
   {
      case 1:
         fprintf(stderr,
		"Usage:  %s [-h] [-n bytes] [-i file] [-r file] [-s]\n", argv[0]);
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
			"Usage:  %s [-h] [-n bytes] [-i file] [-r file] [-s]\n",
			argv[0]);
                     fprintf(stderr,"    -h        get help\n");
                     fprintf(stderr,"    -n bytes  chunk size\n");
                     fprintf(stderr,"    -i file   input file name\n");
                     fprintf(stderr,"    -r file   root file name\n");
                     fprintf(stderr,"    -s        suppress verbose output\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'i':
                     strcpy(input_file_name, argv[i+1]);
                     i++;
                     break;

                  case 'r':
                     strcpy(root_file_name, argv[i+1]);
                     i++;
                     break;

                  case 'n':
                     size = atoi(argv[i+1]);
                     count = size;
                     i++;
                     break;

                  case 's':
                     verbose = FALSE;
                     break;

                  default:
                     fprintf(stderr,
			"Usage: %s [-h] [-n bytes] [-i file] [-r file]  [-s]\n",
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               fprintf(stderr,
			"Usage: %s [-h] [-n bytes] [-i file] [-r file]  [-s]\n",
			argv[0]);
               exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

   printf("\nbinsplit -- Splitting binary file with %d bytes\n",
	size );

   if (verbose) printf("binsplit -- Opening binary file '%s' ...\n", input_file_name);

   in_file_p = fopen(input_file_name, "r");
   if (in_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as input\n", input_file_name);
      exit(1);
   }

   /*
    *  output file name, file size, and chunk size to .000 file
    */
   sprintf(output_file_name, "%s.000", root_file_name);

   if (verbose) printf("binsplit -- Opening output file '%s' ...\n", output_file_name);

   out_file_p = fopen(output_file_name, "w");
   if (out_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
      exit(1);
   }

   fprintf(out_file_p, "%s %d %d\n", input_file_name, CountData( in_file_p ), size );
   fclose(out_file_p);

   /*
    *  reset input file to start of file
    */
   fseek(in_file_p, 0L, SEEK_SET);

   /*
    *  copy data to split output files until no more input
    */
   while (count == size )
   {
      if (feof(in_file_p))
         break;

      sprintf(output_file_name, "%s.%03d", root_file_name, suffix);

      if (verbose) printf("binsplit -- Opening output file '%s' ...\n", output_file_name);

      out_file_p = fopen(output_file_name, "w");
      if (out_file_p == (FILE *)NULL)
      {
         fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
         exit(1);
      }

      count = CopyData(in_file_p, out_file_p, size);

      fclose(out_file_p);

      suffix++;
   }

   fclose(in_file_p);

   exit(0);
}


/* end of binsplit.c */
