/*****************************************************************************
 *
 *  Utility for concatenating two binary files.
 *
 *	File:	bin2hex.c
 *
 *	Usage:	bin2hex [-h] [-a addr] [-r NN] [-i file] [-o file] [-s]
 *
 *	Options:
 *		-h	      - get options help
 *      -a addr   - starting address (default 0)
 *		-r NN     - bytes per record (default 16)
 *		-i file   - input file name (default "file.bin")
 *		-o file   - output file name (default "file.hex")
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


#define DEBUG 0


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


typedef char BOOLEAN_T;

#define DEFAULT_BYTES_PER_REC	16
#define MAX_BYTES_PER_REC		64

#define TYPE_DAT	0
#define TYPE_EOF	1
#define TYPE_ESA	2
#define TYPE_SSA	3
#define TYPE_ELA	4
#define TYPE_SLA	5


/*  define global variables
 */
int		base = 0;



/*  ConvertData	- copy binary data to appended file 
 *
 *  PARAMETERS:
 *	in_file_p	- input file pointer
 *	out_file_p	- output file pointer
 *  bytes_rec   - bytes per record
 *
 *  RETURNS:
 *	count		- number of bytes copied
 */
int 
ConvertData(FILE *in_file_p, FILE *out_file_p, int start, int bytes_rec)
{
   int i;
   int count = 0;
   int bytes = 0;
   int address = start;
   
   unsigned char sum = 0;
   unsigned char c;
   unsigned char checksum = 0;

	// hex format -- :bbaaaatt[data]cc
	// bb - bytes in record
	// aaaa - address
	// tt - record type
	// cc - checksum

   fseek(in_file_p, 0L, SEEK_SET);

   while(!feof(in_file_p)) 
   {
	   // copy data for current record
	   for (i = 0; i < bytes_rec; i++)
	   {
		    c = fgetc(in_file_p);
		    if (!feof(in_file_p))
		    {	   
				if (i == 0)
				{
					if (DEBUG) printf("start rec addr %d\n", address);
					// start new record
					fprintf(out_file_p, ":%02X", bytes_rec);
					fprintf(out_file_p, "%04X", address);
					fprintf(out_file_p, "%02X", TYPE_DAT);
				}


				fprintf(out_file_p, "%02X", c);
				sum += c;
				address++;
				count++;
			}
	   }
	   
	   if (!feof(in_file_p))
	   {
			// end of current record
			if (DEBUG) printf("..end rec count %d sum %02x\n", count, sum);
			checksum = (~sum) + 1;  // calculate checksum as 2's complement
			fprintf(out_file_p,"%02X", checksum);
			fprintf(out_file_p,"\n");
			sum = 0;
	   }
   }

   // end of file
   fprintf(out_file_p, ":%02X", 0);
   fprintf(out_file_p, "%04X", 0);
   fprintf(out_file_p, "%02X", TYPE_EOF);
   fprintf(out_file_p, "%02X", 255);
   fprintf(out_file_p,"\n");

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

   FILE		*in_file_p;
   FILE		*out_file_p;

   int		bytes_per_rec = DEFAULT_BYTES_PER_REC;
   int		start_addr = 0;

   BOOLEAN_T	verbose = TRUE;

   switch (argc)
   {
      case 1:
         fprintf(stderr, 
		"Usage:  %s [-h] [-a addr] [-r NN] [-i file] [-o file] [-s]\n", argv[0]);
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
			"Usage:  %s [-h] [-a addr] [-r NN] [-i file] [-o file] [-s]\n", 
			argv[0]);
                     fprintf(stderr,"    -h        get help\n");
                     fprintf(stderr,"    -a addr   starting address\n");
                     fprintf(stderr,"    -r NN     bytes per record\n");
                     fprintf(stderr,"    -i file   input file name\n");
                     fprintf(stderr,"    -o file   output file name\n");
                     fprintf(stderr,"    -s        suppress verbose output\n");
                     if (argc == 2)
                        exit(0);
                     else
                        break;

                  case 'a':
                     start_addr = atoi(argv[i+1]);
                     i++;
                     break;

                  case 'r':
                     bytes_per_rec = atoi(argv[i+1]);
                     i++;
                     break;
					 
                  case 'i':
                     strcpy(input_file_name, argv[i+1]);
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
			"Usage:  %s [-h] [-a addr] [-r NN] [-i file] [-o file] [-s]\n", 
			argv[0]);
                     exit(1);
               }	/* end of inner switch */
            }
            else
            {
               fprintf(stderr,
			"Usage:  %s [-h] [-a addr] [-r NN] [-i file] [-o file] [-s]\n", 
			argv[0]);
               exit(1);
            }

            i++;	/* increment arg index */
         } 	/* end while */
         break;
   } /* end of outer switch */

   printf("\nbin2hex -- Converting binary to hex file\n");

   if (verbose) printf("bin2hex -- Opening binary file '%s' ...\n", input_file_name);

   in_file_p = fopen(input_file_name, "r");
   if (in_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as input\n", input_file_name);
      exit(1);
   }

   if (verbose) printf("bin2hex -- Opening output file '%s' ...\n", output_file_name);

   out_file_p = fopen(output_file_name, "w");
   if (out_file_p == (FILE *)NULL)
   {
      fprintf(stderr, "Couldn't open %s as output\n", output_file_name);
      exit(1);
   }

   count = ConvertData(in_file_p, out_file_p, start_addr, bytes_per_rec);

   if (verbose) printf("bin2hex -- converted %d bytes from binary to hex\n\n", count);

   fclose(in_file_p);
   fclose(out_file_p);

   exit(0);
}


/* end of bin2hex.c */
