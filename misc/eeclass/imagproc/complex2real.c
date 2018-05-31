/*******************************************************************
Convert complex to real format

Usage:    complex2real -{rima} infile outfile
          use only 1 flag at a time:
	  -r extract real part 
	  -i extract imaginary part 
	  -m compute magnitude
	  -a compute phase angle 
Example:  complex2real -r in.img out.img
Compile string:
cc complex2real.c -O -o complex2real -lm

Author: Michael A. Gennert          created 10-5-93
*******************************************************************/
#include <stdio.h>
#include <math.h>
#include "const.h"
#include "typedef.h"
#include "imgio.h"

/*********************************************************************/

void fill_image(conv_type, img_in, img_out)
     char conv_type;
     GIFF *img_in, *img_out;
{
  register complex *in_ptr;
  register float *out_ptr; 
  register long i, max_i;
	
  if(img_in->type != COMPLEX)
    {
      fprintf(stderr, "Input image not COMPLEX\n");
      exit(1);
    }

  in_ptr = (complex *) img_in->bits;
  max_i = (img_in->xdim) * (img_in->ydim);

  /* Allocate space for output image */
  img_out->xdim = img_in->xdim;
  img_out->ydim = img_in->ydim;
  img_out->type = FLOAT;
  img_out->bits = (BYTE *) malloc(max_i*sizeof(float));
  out_ptr = (float *) img_out->bits;

  /* Assign value to each pixel */
  switch(conv_type) {
  case 'r':
    for(i = 0; i < max_i; i++) *(out_ptr++) = (in_ptr++)->re; break;
  case 'i':
    for(i = 0; i < max_i; i++) *(out_ptr++) = (in_ptr++)->im; break;
  case 'm':
    for(i = 0; i < max_i; i++) {
      *(out_ptr++) = sqrt((in_ptr->re)*(in_ptr->re)+(in_ptr->im)*(in_ptr->im));
      in_ptr++;
    }
    break;
  case 'a':
    for(i = 0; i < max_i; i++) {
      *(out_ptr++) = atan2(in_ptr->im, in_ptr->re);
      in_ptr++;
    }
    break;
  }
}

int main(argc, argv)
     int argc;
     char *argv[];
{
  GIFF in_img, out_img;

  /* Check arguments */
  if ((argc != 4) ||
      (argv[1][0] != '-') ||
      ((argv[1][1] != 'r') &&
       (argv[1][1] != 'i') &&
       (argv[1][1] != 'm') &&
       (argv[1][1] != 'a')))
    {
      fprintf(stderr, "Usage: %s -{rima} infile outfile\n", argv[0]);
      exit(1);
    }

  read_image(argv[2], &in_img);
  fill_image(argv[1][1], &in_img, &out_img);
  write_image(argv[3], &out_img);
  exit(0);
}   /* end main */

 
