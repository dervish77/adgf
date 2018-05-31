/*******************************************************************
Create a test image

Usage:    test xdim ydim nbits outfile
Example:  test 256 256 gray.img
Compile string:
cc test.c -O -o test -lm

Author: Michael A. Gennert          created 9-23-93
*******************************************************************/
#include <stdio.h>
#include <math.h>
#include "const.h"
#include "typedef.h"
#include "imgio.h"

/*********************************************************************/

void fill_image(img_out)
     GIFF *img_out;
{
  register int i, j;
  register BYTE *out_ptr; 
	
  /* The image center */
  int x0, y0; 

  x0 = (img_out->xdim)/2;
  y0 = (img_out->ydim)/2;

  /* Allocate space for image */
  img_out->bits = (BYTE *) malloc(img_out->xdim*img_out->ydim*sizeof(BYTE));
  out_ptr = img_out->bits;

  /* Assign value to each pixel */
  for (j=0; j<img_out->ydim; j++) 
    for (i=0; i<img_out->xdim; i++) 
      *(out_ptr++) = abs(i-x0) + abs(j-y0);
}

int main(argc, argv)
     int argc;
     char *argv[];
{
  GIFF out_img;

  /* Check arguments */
  if (argc != 4) {
    fprintf(stderr, "Usage: %s xdim ydim outfile\n", argv[0]);
    exit(1);
  }

  out_img.xdim = atoi(argv[1]);
  out_img.ydim = atoi(argv[2]);
  out_img.type = CHAR;

  fill_image(&out_img);
  write_image(argv[3], &out_img);
  exit(0);
}   /* end main */

 
