/*****************************************************************************
 *
 *  Utility for prepending a binary file with specified number of bytes.
 *
 *	File:	prepend.c
 *
 *	Usage:	prepend [-h] [-n bytes] [-d data] [-i file] [-o file]
 *
 *	Options:
 *		-h	  - get options help
 *		-n bytes  - num bytes to prepend (default "256")
 *		-d data   - prepend data (default "0x00")
 *		-i file   - input file name (default "file.elf")
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


/*  PrependData	- counts bytes in binary file 
 *
 *  PARAMETERS:
 *	in_file_p	- input file pointer
 *	size		- num bytes to prepend
 *	data		- prepend data
 *
 *  RETURNS:
 *	size		- number of bytes converted
 */
int 
PrependData(FILE *out_file_p, int size, int data)
{
   int i, c, count = 0;

   for (i = 0; i < size; i++) 
   {
      c = data;
      fputc(c, out_file_p);
      count++;
   }

   return(count);
}



/*  CopyData	- copy binary data to prepended file 
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

   char		input_file_name[40];	/* buffer */
   char		output_file_name[40];	/* buffer */
   char		array_name[40];		/* buffer */

   FILE		*in_file_p;
   FILE		*out_file_p;

   BOOLEAN_T	verbose = TRUE;

   switch (argc)
   {
      case 1:
         fprintf(stderr, 
		"Usage:  %s [-h] [-n bytes] [-d data] [-i file] [-o file] [-s]\n", argv[0]);
         exit(1);

      default:
         i = 1;
         while (i < argc)
         {
            if (argv[i][0] == '-')
            {
               switch(argv[i][1])
               {
                  case 'd':
                     data = atoi(argv[i+1]);
                     i++;
                     break;

                  case 'h':
                     fprintf(stderr, 
			"Usage:  %s [-h] [-n bytes] [-d data] [-i file] [-o file] [-s]\n", 
			argv[0]);
                     fprintf(stderr,"    -h        get help\n");
                     fprintf(stderr,"    -n bytes  num bytes to prepend\n");
                     fprintf(stderr,"    -d data   prepend data\n");
                     fprintf(stderr,"    -i file   input file name\n");
                     fprintf(stderr,"    -o file   output file name\n");
                     fprintf(stderr,"    -s        suppress verbose output\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'i':
                     strcpy(input_file_name, argv[i+1]);
                     i++;
                     break;

                  case 'o':
                     strcpy(output_file_name, argv[i+1]);
                     i++;
                     break;

                  case 'n':
                     size = atoi(argv[i+1]);
                     i++;
                     break;

                  case 's':
                     verbose = FALSE;
                     break;

                  default:
                     fprintf(stderr,
			"Usage: %s [-h] [-n bytes] [-d data] [-i file] [-o file]  [-s]\n",
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               fprintf(stderr,
			"Usage: %s [-h] [-n bytes] [-d data] [-i file] [-o file]  [-s]\n",
			argv[0]);
               exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

   printf("\nprepend -- Prepending binary file with %d bytes of 0x%02x\n",
	size, data );

   if (verbose) printf("prepend -- Opening binary file '%s' ...\n", input_file_name);

   in_file_p = fopen(input_file_name, "r");
   if (in_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as input\n", input_file_name);
      exit(1);
   }

   if (verbose) printf("prepend -- Opening output file '%s' ...\n", output_file_name);

   out_file_p = fopen(output_file_name, "w");
   if (out_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
      exit(1);
   }

   count = PrependData(out_file_p, size, data);

   if (verbose) printf("prepend -- prepended %d bytes\n", count);

   count = CopyData(in_file_p, out_file_p);

   if (verbose) printf("prepend -- copied %d bytes\n\n", count);

   fclose(in_file_p);
   fclose(out_file_p);

   exit(0);
}


/* end of prepend.c */
