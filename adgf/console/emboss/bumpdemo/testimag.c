/**********************************************************

 File:	testimag.c

 Date:	2/20/95

 Auth:	Brian Lingard


 This program tests some of the functions found in "imagfile.c".


**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAMELENGTH 81


/* uniform image structure */

typedef struct {
   char fname[FNAMELENGTH];		/* file name array */
   FILE *file;				/* file pointer */
   unsigned short x_size;		/* image width */
   unsigned short y_size;		/* image height */
   unsigned short num_colors;		/* number of colors in color map */
   unsigned char *colormap;		/* pointer to color map */
   unsigned char *image;		/* pointer to pixels */
} IMAGE_STRUCT;


int Read_Raw(input, num_bytes)	/* reads a raw binary file */
   IMAGE_STRUCT *input;
   int num_bytes;		/* number of bytes to read */
{
   unsigned char *rawdata;

   rawdata = (unsigned char *) calloc(num_bytes, sizeof(unsigned char));
   if (rawdata == (unsigned char *) NULL) {
      fprintf(stderr, "couldn't allocate memory for raw data\n");
      exit(1);
   }

   input->image = rawdata;

   if (fgets(rawdata, num_bytes, input->file) == NULL) {
      fprintf(stderr, "error while reading raw data from %s\n", input->fname);
      exit(1);
   }

   return(0);
} /* end of Read_Raw() */


main(argc, argv)
   int argc;
   char *argv[];
{
   IMAGE_STRUCT input;

   int i, c, num_bytes;


   if ( argc != 3 )
   {
      fprintf(stderr, "Usage: %s filename bytes\n", argv[0]);
      exit(1);
   }

   sprintf(input.fname, "%s", argv[1]);

   num_bytes = (int) atoi(argv[2]);

/* open input file */
   input.file = fopen(input.fname, "r");
   if (input.file == (FILE *) NULL) {
      fprintf(stderr, "error while opening %s\n", input.fname);
      exit(1);
   }


/* read num_bytes from input file */
   printf("\nReading %d bytes from file - %s\n\n", num_bytes, input.fname);

   Read_Raw(&input, num_bytes);


/* output bytes read to screen */
   c = 0;
   for (i=0; i < num_bytes; i++) {

      printf("%x ", *input.image++);
      c++;

      if ( c == 8 ) {
         printf("\n");
         c = 0;
      }
   }
   printf("\n");
   

   fclose(input.file);

} /* end of main */

/** end of testimag.c **/
