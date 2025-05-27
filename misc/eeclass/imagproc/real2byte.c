/*******************************************************************
Convert real to byte format

Usage:    real2byte infile outfile
Example:  real2byte in.img out.img
Compile string:
cc real2byte.c -O -o real2byte -lm

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
  register float *in_ptr;
  register BYTE *out_ptr; 
  register long i, max_i;
  register float in_min, in_max, scale;

  if(img_in->type != FLOAT)
    {
      fprintf(stderr, "Input image not REAL\n");
      exit(1);
    }

  in_ptr = (float *) img_in->bits;
  max_i = (img_in->xdim) * (img_in->ydim);

  /* Allocate space for output image */
  img_out->xdim = img_in->xdim;
  img_out->ydim = img_in->ydim;
  img_out->type = CHAR;
  img_out->bits = (BYTE *) malloc(max_i*sizeof(BYTE));

  /* Find input min and max */
  in_min = in_max = *in_ptr;
  for(i = 0; i < max_i; i++) {
    if (*in_ptr < in_min)
      in_min = *in_ptr;
    else if (*in_ptr > in_max)
      in_max = *in_ptr;
    in_ptr++;
  }

  scale = PIXEL_MAX / (in_max - in_min);
  fprintf(stderr, "min = %f, max = %f, scale = %f\n", in_min, in_max, scale);

  /* Assign value to each pixel */
  in_ptr = (float *) img_in->bits;
  out_ptr = img_out->bits;
  for(i = 0; i < max_i; i++) *(out_ptr++) = (BYTE) scale*(*(in_ptr++)-in_min);
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

 
