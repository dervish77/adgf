/*************************************************************************
*  HWK #8  --   Problem #4
*
*  Filename:   rundec.c
*  Author:     Brian Lingard
*  Date:       11/12/93
*
*  Purpose:    uncompress input image via run length encoding
*
*  Assumptions:
*	- all lines start with white pixel
*	- if first pixel is black, then run length is zero
*	- maximum image size is 512x512
*	- end of line marker is 999
*	- end of file marker is 9999
*
*  Usage:      rundec infile outfile     
*  Example:    rundec hw8.cmp hw8.img		uncompress image hw8
*
*  Compile String:
*  cc rundec.c -O -o rundec -lm
*
**************************************************************************/
     
#include <stdio.h>
#include <math.h>		    /* declare math functions to use */
#include "const.h"
#include "typedef.h"
#include "imgio.h"

#define DEBUG 1

#define WHT 255
#define BLK 0


/* run length decode function */
void decode(infilename, output_img)
     char *infilename;
     GIFF *output_img;
{
     FILE *in_file;
     BYTE *img_ptr;

     int NX,NY;
     int x,y;
     int pixcount;	/* pixel count for current color */
     int count;
     int white_flag;	/* boolean flag for current color */

/* open input file */
     in_file = fopen(infilename, "r");
     if (in_file == NULL) {
	printf("ERROR - input file %f could not be opened!\n",infilename);
	exit(1);
     }

/* read size of image from compressed file */
     fscanf(in_file,"%d",&NX);
     fscanf(in_file,"%d",&NY);
     if (NX > 512 || NY > 512) {
	printf("ERROR - incorrect image size specified of %d x %d\n",NX,NY);
	exit(1);
     }
     printf("uncompressing %dx%d image\n",NX,NY);

/* allocate memory for output image */
     output_img->type = CHAR;
     output_img->xdim = NX;
     output_img->ydim = NY;
     img_ptr = (BYTE *) malloc(NX * NY * sizeof(BYTE));
     if (img_ptr == NULL) {
	printf("decode: memory request failed!\n");
	exit(1);
     }
     output_img->bits = img_ptr;

/* loop until end of image */
     x = 0;
     fscanf(in_file,"%d",&pixcount);
     /*if (DEBUG==1) printf("pix=%d\n",pixcount);*/
     while (pixcount != 9999) {
	y = 0;
	white_flag = 1;

/* loop until end of line */
	while (pixcount != 999) {

/* is first count of this line zero? */
	  if (pixcount==0)  
	    white_flag = 0;

	  else { /* must be valid run length */

/* loop for pixel count and set pixels to white */
	    if (white_flag = 1) {
	      for (count = pixcount; count > 0; count--) {
	        *(img_ptr + x*NY + y) = WHT;
	        y++;
	      }
	      white_flag = 0;
	    }
/* loop for pixel count and set pixels to black */
	    else {
	      for (count = pixcount; count > 0; count--) {
	        *(img_ptr + x*NY + y) = BLK;
	        y++;
	      }
	      white_flag = 1;
	    }

	  } /* end else pixel count is zero */
	  fscanf(in_file,"%d",&pixcount);
	  /*if (DEBUG==1) printf("pix=%d\n",pixcount);*/

	} /* end of loop until end of line */
	fscanf(in_file,"%d",&pixcount);
	/*if (DEBUG==1) printf("pix=%d\n",pixcount);*/
	x++; /* incr image line index */
	if (y != NY) {
	  printf("ERROR - pixel count for line %d is incorrect\n",x);
	  exit(1);
	}

     } /* end of loop until end of image */
     if (x != NX) {
	printf("ERROR - row count of %d for this image is incorrect\n",x);
     }

/* close compressed file */
     fclose(in_file);

} /* end of decode */


/* main program */

int main(argc,argv)
     int argc;
     char *argv[];
{
    GIFF *output_img;

  /* check arguments */
    if (argc != 3) {
      printf("Usage: %s infile outfile\n", argv[0]);
      exit(1);
    }

  /* decompress input image */
    printf("Uncompressing image using run length decoding ...\n\n");
    decode(argv[1], &output_img);

  /* write output image */
    write_image(argv[2], &output_img);

    printf("Program complete.\n"); 
    exit(0);
}  /* end main */
