/*****************************************************************************
 *
 *  Utility for concatenating two binary files.
 *
 *	File:	bincat.c
 *
 *	Usage:	bincat [-h] [-a file] [-b file] [-o file]
 *
 *	Options:
 *		-h	  - get options help
 *		-a file   - input file 1 name (default "file.elf")
 *		-b file   - input file 2 name (default "file.elf")
 *		-o file   - output file name (default "file.bin")
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


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


typedef char BOOLEAN_T;



/*  define global variables
 */
int		base = 0;



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
CopyData(FILE *in_file_p, FILE *out_file_p)
{
   int i;
   int count = 0;

   unsigned char c;


   fseek(in_file_p, 0L, SEEK_SET);

   while(!feof(in_file_p)) 
   {
      c = fgetc(in_file_p);

      if (!feof(in_file_p)) 
      {
         fputc(c, out_file_p);
         count++;
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
   int		i, data = 0, size = 0, count;

   char		input_file_name_1[40];	/* buffer */
   char		input_file_name_2[40];	/* buffer */
   char		output_file_name[40];	/* buffer */
   char		array_name[40];		/* buffer */

   FILE		*in_file1_p;
   FILE		*in_file2_p;
   FILE		*out_file_p;

   BOOLEAN_T	verbose = TRUE;

   switch (argc)
   {
      case 1:
         fprintf(stderr, 
		"Usage:  %s [-h] [-a file] [-b file] [-o file] [-s]\n", argv[0]);
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
			"Usage:  %s [-h] [-a file] [-b file] [-o file] [-s]\n", 
			argv[0]);
                     fprintf(stderr,"    -h        get help\n");
                     fprintf(stderr,"    -a file   input file name 1\n");
                     fprintf(stderr,"    -b file   input file name 2\n");
                     fprintf(stderr,"    -o file   output file name\n");
                     fprintf(stderr,"    -s        suppress verbose output\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'a':
                     strcpy(input_file_name_1, argv[i+1]);
                     i++;
                     break;

                  case 'b':
                     strcpy(input_file_name_2, argv[i+1]);
                     i++;
                     break;

                  case 'o':
                     strcpy(output_file_name, argv[i+1]);
                     i++;
                     break;

                  case 's':
                     verbose = FALSE;
                     break;

                  default:
                     fprintf(stderr,
			"Usage:  %s [-h] [-a file] [-b file] [-o file] [-s]\n", 
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               fprintf(stderr,
			"Usage:  %s [-h] [-a file] [-b file] [-o file] [-s]\n", 
			argv[0]);
               exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

   printf("\nbincat -- Concatenating binary files\n");

   if (verbose) printf("bincat -- Opening binary file '%s' as file 1 ...\n", input_file_name_1);

   in_file1_p = fopen(input_file_name_1, "r");
   if (in_file1_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as input\n", input_file_name_1);
      exit(1);
   }

   if (verbose) printf("bincat -- Opening binary file '%s' as file 2 ...\n", input_file_name_2);

   in_file2_p = fopen(input_file_name_2, "r");
   if (in_file2_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as input\n", input_file_name_2);
      exit(1);
   }

   if (verbose) printf("bincat -- Opening output file '%s' ...\n", output_file_name);

   out_file_p = fopen(output_file_name, "w");
   if (out_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
      exit(1);
   }

   count = CopyData(in_file1_p, out_file_p);

   if (verbose) printf("bincat -- copied %d bytes from file 1\n", count);

   count = CopyData(in_file2_p, out_file_p);

   if (verbose) printf("bincat -- copied %d bytes from file 2\n\n", count);

   fclose(in_file1_p);
   fclose(in_file2_p);
   fclose(out_file_p);

   exit(0);
}


/* end of append.c */
