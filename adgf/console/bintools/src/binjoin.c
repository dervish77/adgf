/*****************************************************************************
 *
 *  Utility for joining a binary file from chunks.
 *
 *	File:	binjoin.c
 *
 *	Usage:	binjoin [-h] [-r file] [-o file]
 *
 *	Options:
 *		-h	  - get options help
 *		-r file   - root file name (default "file.out")
 *		-o file   - output file name (default "file.bin")
 *		-s        - suppress verbose output
 *
 *	Notes:
 *	- looks for .000 file
 *		- contains original file name, file size, and chunk size
 *	- verifies all bytes are joined
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
   int		i, data = 0, size = 256, suffix = 1, count = 0;

   int		zero_size, zero_chunk;

   char		zero_file_name[40];	/* buffer */
   char		input_file_name[40];	/* buffer */
   char		root_file_name[40];	/* buffer */
   char		output2_file_name[40];	/* buffer */
   char		output_file_name[40];	/* buffer */
   char		array_name[40];		/* buffer */

   FILE		*in_file_p;
   FILE		*out_file_p;

   BOOLEAN_T	verbose = TRUE;
   BOOLEAN_T	override = FALSE;

   output2_file_name[0] = '\0';

   switch (argc)
   {
      case 1:
         fprintf(stderr, 
		"Usage:  %s [-h] [-r file] [-o file] [-s]\n", argv[0]);
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
			"Usage:  %s [-h] [-r file] [-o file] [-s]\n", 
			argv[0]);
                     fprintf(stderr,"    -h        get help\n");
                     fprintf(stderr,"    -r file   root file name\n");
                     fprintf(stderr,"    -o file   output file name\n");
                     fprintf(stderr,"    -s        suppress verbose output\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'o':
                     strcpy(output2_file_name, argv[i+1]);
                     override = TRUE;
                     i++;
                     break;

                  case 'r':
                     strcpy(root_file_name, argv[i+1]);
                     i++;
                     break;

                  case 's':
                     verbose = FALSE;
                     break;

                  default:
                     fprintf(stderr,
			"Usage: %s [-h] [-r file] [-o file]  [-s]\n",
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               fprintf(stderr,
			"Usage: %s [-h] [-r file] [-o file]  [-s]\n",
			argv[0]);
               exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */


   printf("\nbinjoin -- Joining binary file \n");

   /* 
    *  open and read .000 file  
    */
   sprintf(input_file_name, "%s.000", root_file_name, suffix);

   if (verbose) printf("binjoin -- Opening input file '%s' ...\n", input_file_name);

   in_file_p = fopen(input_file_name, "r");
   if (in_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as input\n", input_file_name);
      exit(1);
   }

   fscanf(in_file_p, "%s %d %d\n", zero_file_name, &zero_size, &zero_chunk);
   fclose(in_file_p);

   if (verbose) printf("binjoin -- original file name - %s\n", zero_file_name);
   if (verbose) printf("binjoin -- original file size - %d\n", zero_size);
   if (verbose) printf("binjoin -- chunk size         - %d\n", zero_chunk);


   /* 
    *  open output file based on either .000 file or -o option 
    */
   if ( override )
      sprintf(output_file_name, "%s", output2_file_name);
   else
      sprintf(output_file_name, "%s", zero_file_name);

   if (verbose) printf("binjoin -- Opening output file '%s' ...\n", output_file_name);

   out_file_p = fopen(output_file_name, "w");
   if (out_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
      exit(1);
   }


   /* 
    *  copy data from split input files until all bytes copied 
    */
   while (count < zero_size )
   {
      sprintf(input_file_name, "%s.%03d", root_file_name, suffix);

      if (verbose) printf("binjoin -- Opening input file '%s' ...\n", input_file_name);

      in_file_p = fopen(input_file_name, "r");
      if (in_file_p == (FILE *)NULL)
      {
         fprintf(stderr, "Couldn't open %s as input\n", input_file_name);
         exit(1);
      }

      count = count + CopyData(in_file_p, out_file_p, zero_chunk);
   
      fclose(in_file_p);

      suffix++;
   }

   fclose(out_file_p);

   exit(0);
}


/* end of binjoin.c */
