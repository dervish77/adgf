/*****************************************************************************
 *
 *  Utility for converting a raw binary file to C language array.
 *
 *	File:	bintoc.c
 *
 *	Usage:	bintoc [-h] [-i file] [-o file] [-a name]
 *
 *	Options:
 *		-h	  - get options help
 *		-i file   - input file name (default "input.bit")
 *		-o file   - output file name (default "output.c")
 *		-a name   - C array name (default "input_array")
 *
 *	Date:	09/22/98
 *
 *	Revisions:
 *	  0.0  09/22/98  Originated
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


#define DEFAULT_ARRAY_SIZE	256		/* 256 bytes */

#define DEFAULT_BYTES_PER_ROW	8

typedef char BOOLEAN_T;



/*  define global variables
 */
int		base = 0;


/*  OutputHeader - outputs C language header 
 *
 *  PARAMETERS:
 *	out_file_p	- output file pointer
 *	in		- input file name
 *	out		- output file name
 *	name		- C array name
 *
 *  RETURNS:
 */
void 
OutputHeader(FILE *out_file_p, char *in, char *out, char *name)
{
   fprintf(out_file_p, "/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   fprintf(out_file_p, " *   FileName:   %s\n", out);
   fprintf(out_file_p, " *   Input file: %s\n", in);
   fprintf(out_file_p, " *   \n");
   fprintf(out_file_p, " *   ArrayName:  %s\n", name);
   fprintf(out_file_p, " *   \n");
   fprintf(out_file_p, " *   see file footer for array size\n");
   fprintf(out_file_p, " * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   fprintf(out_file_p, " */\n");
}


/*  OutputFooter - outputs C language header 
 *
 *  PARAMETERS:
 *	out_file_p	- output file pointer
 *	size		- number of byte converted
 *
 *  RETURNS:
 */
void 
OutputFooter(FILE *out_file_p, int size)
{
   fprintf(out_file_p, "\n");
   fprintf(out_file_p, "/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   fprintf(out_file_p, " *     finis -- converted %d bytes \n", size);
   fprintf(out_file_p, " * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   fprintf(out_file_p, " */\n");
}



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



/*  ConvertData	- converts binary data to C language array 
 *
 *  PARAMETERS:
 *	in_file_p	- input file pointer
 *	out_file_p	- output file pointer
 *	name		- C array name
 *	size		- size of array
 *
 *  RETURNS:
 *	count		- number of bytes converted
 */
int 
ConvertData(FILE *in_file_p, FILE *out_file_p, char *name, int size)
{
   int i;
   int count = 0;

   unsigned char c;

   fprintf(out_file_p, "\n\n");
   fprintf(out_file_p, "unsigned long %s_Size = %d;\n", name, size);

   fprintf(out_file_p, "\n\n");
   fprintf(out_file_p, "unsigned char %s[%d] = \n", name, size);
   fprintf(out_file_p, "              {");

   fseek(in_file_p, 0L, SEEK_SET);

   for (i = 0; i < size; i++) 
   {
      if ( (i % 8 == 0) )
      {
         fprintf(out_file_p, "\n");
      }

      c = getc(in_file_p);
      count++;

      fprintf(out_file_p, "0x%02X", c);

      if ( i < (size - 1) )
      {
         fprintf(out_file_p, ", ");
      }

   }

   fprintf(out_file_p, "\n              };\n");

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
   int		i, size, count;

   char		input_file_name[40];	/* buffer */
   char		output_file_name[40];	/* buffer */
   char		array_name[40];		/* buffer */

   FILE		*in_file_p;
   FILE		*out_file_p;


   switch (argc)
   {
      case 1:
         fprintf(stderr, 
		"Usage:  %s [-h] [-i file] [-o file] [-a name]\n", argv[0]);
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
			"Usage:  %s [-h] [-i file] [-o file] [-a name]\n", 
			argv[0]);
                     fprintf(stderr,"    -h        get help\n");
                     fprintf(stderr,"    -i file   input file name\n");
                     fprintf(stderr,"    -o file   output file name\n");
                     fprintf(stderr,"    -a name   C array name\n");
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

                  case 'a':
                     strcpy(array_name, argv[i+1]);
                     i++;
                     break;

                  default:
                     fprintf(stderr,
			"Usage: %s [-h] [-i file] [-o file] [-a name]\n",
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               fprintf(stderr,
			"Usage: %s [-h] [-i file] [-o file] [-a name]\n",
			argv[0]);
               exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

   printf("\nbintoc -- Converting binary file to C array\n");

   printf("bintoc -- Opening binary file '%s' ...\n", input_file_name);

   in_file_p = fopen(input_file_name, "r");
   if (in_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as input\n", input_file_name);
      exit(1);
   }

   printf("bintoc -- Opening output file '%s' ...\n", output_file_name);

   out_file_p = fopen(output_file_name, "w");
   if (out_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
      exit(1);
   }

   OutputHeader(out_file_p, input_file_name, output_file_name, array_name);

   size = CountData(in_file_p);

   printf("bintoc -- counted %d bytes\n", size);

   count = ConvertData(in_file_p, out_file_p, array_name, size);

   printf("bintoc -- processed %d bytes\n\n", count);

   OutputFooter(out_file_p, count);

   fclose(in_file_p);
   fclose(out_file_p);

   exit(0);
}


/* end of bintoc.c */
