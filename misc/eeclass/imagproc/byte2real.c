/*******************************************************************
Convert byte to real format

Usage:    byte2real infile outfile
Example:  byte2real in.img out.img
Compile string:
cc byte2real.c -O -o byte2real -lm

Author: Michael A. Gennert          created 10-5-93
*******************************************************************/
#include <stdio.h>
#include <math.h>
#include "const.h"
#include "typedef.h"
#include "imgio.h"

/*******************************************************************/

void fill_image(img_in, img_out)
     GIFF *img_in, *img_out;
{
  register BYTE *in_ptr;
  register float *out_ptr; 
  register long i, max_i;

  if(img_in->type != CHAR)
    {
      fprintf(stderr, "Input image not CHAR\n");
      exit(1);
    }

  in_ptr = img_in->bits;
  max_i = (img_in->xdim) * (img_in->ydim);

  /* Allocate space for output image */
  img_out->xdim = img_in->xdim;
  img_out->ydim = img_in->ydim;
  img_out->type = FLOAT;
  img_out->bits = (BYTE *) malloc(max_i*sizeof(float));
  out_ptr = (float *) img_out->bits;

  /* Assign value to each pixel */
  for(i = 0; i < max_i; i++) *(out_ptr++) = *(in_ptr++);
}

int main(argc, argv)
     int argc;
     char *argv[];
{
  GIFF in_img, out_img;

  /* Check arguments */
  if (argc != 3) {
    fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
    exit(1);
  }

  read_image(argv[1], &in_img);
  fill_image(&in_img, &out_img);
  write_image(argv[2], &out_img);
  exit(0);
}   /* end main */

 
