/*************************************************************************
*  This program computes the 2-D Fast Fourier Transform of an input image
*
*  Filename:   d2ftt.c
*  Author:     Brian Lingard
*  Date:       10/12/93
*
*  Usage:      d2fft inv infile outfile     
*  Example:    d2fft 0 gaus.img gausft.img
*
*  Compile String:
*  cc d2fft.c -O -o d2fft -lm
*
**************************************************************************
*  The 1-D FFT algorithm found in fft.c is used to perform the 2-D case.
*
*  The 1-D function is defined as:
*
*    fft(real_data, imag_data, n_pts, nu, inv)
*
* where
*  real_data ... ptr. to real part of data to be transformed
*  imag_data ... ptr. to imag  "   "   "   "  "      "
*  inv ..... Switch to flag normal or inverse transform
*  n_pts ... Number of real data points
*  nu ...... logarithm in base 2 of n_pts e.g. nu = 5 if n_pts = 32.
***************************************************************************/
     
#include <stdio.h>
#include <math.h>		    /* declare math functions to use */
#include "const.h"
#include "typedef.h"
#include "imgio.h"
#include "fft.c"

/* #define	 PI 3.1419527  */
#define DEBUG 1    

/* compute integer y**x */
int compute_power(base,expon)
     int base,expon;
{
     int i,result;

     result = base;
     for (i=1; i<expon; ++i)
         result = result * base;

     return(result);
}

/* function to compute any base log of integer */
int logbase(num, base)
     int num, base;
{
     int i,result,power;

     i = 1;
     while (power < num ) {
       power = compute_power(base,i);
       ++i;
     }
     result = i - 1;
     return(result);
}
 
/*     fft( real_data, imag_data, n_pts, nu, inv )
*     double *real_data, *imag_data;
*     int n_pts, nu, inv;              */

/* function to compute 2-D FFT */
void d2_fft(in_img, out_img, inv)
     GIFF *in_img;                  /* input image pointer */
     GIFF *out_img;                 /* output image pointer */
     int inv;                       /* if 0 perform normal FFT, if 1 perform inverse FFT */
{
     int xdim,ydim;
     int log2xdim,log2ydim;
     BYTE *real_row_ptr;
     BYTE *imag_row_ptr,*init_imag_row_ptr;
     BYTE *output_row_ptr;
     int i,j;

  /* extract dimensions of input image */
     xdim = in_img->xdim;
     ydim = in_img->ydim;
     if (DEBUG == 1) printf("image size is x,y = %i,%i\n", xdim,ydim);

  /* allocate space for output image */
     out_img->xdim = xdim;
     out_img->ydim = ydim;
     out_img->bits = (BYTE *) malloc(out_img->xdim * out_img->ydim * sizeof(BYTE));
     out_img->type = in_img->type;
     if (!out_img->bits) {
         printf("memory request failed!!!\n");
         exit(1);
     }
     if (DEBUG == 1) printf("declared output image structure\n");

  /* calculate log base 2 of xdim of input image */
     log2xdim = logbase(xdim,2);
     if (DEBUG == 1) printf("completed log function\n");

  /* initialize imaginary row data to all zeros */
     if (DEBUG == 1) printf("init imag row ptr\n");
     imag_row_ptr = (BYTE *) malloc(xdim * sizeof(BYTE));
     init_imag_row_ptr = imag_row_ptr;
     for (i=0; i < xdim; ++i) {
         *(imag_row_ptr + i) = 0;
     }
     imag_row_ptr = init_imag_row_ptr;
     if (DEBUG == 1) printf("complete init imag row_ptr\n");

  /* for each row of the input image perform a 1-D FFT */
     real_row_ptr = in_img->bits;          /* initialize ptr to start of 1st row */
     output_row_ptr = out_img->bits;       /* initialize ptr to start of output image */

     if (DEBUG == 1) printf("about to perform FFT on a row\n");
     for (i=0; i < ydim; ++i) {            /* perform 1-D FFT for each row of input image */
         if (DEBUG==1)  printf("row = %i\n", i);

         fft(real_row_ptr, imag_row_ptr, xdim, log2xdim, inv);

         if (DEBUG==1) printf("did a row\n");
         for (j=0; j < xdim; ++j) {                            /* copy result data to output image */
             *(output_row_ptr++) = *(real_row_ptr++);
         }
         real_row_ptr = real_row_ptr + xdim * sizeof(BYTE);    /* advance pointer to next row */
     }

} /* end of 2-D FFT function */


/* main program */

int main(argc,argv)
     int argc;
     char *argv[];
{
    GIFF *in_img,*out_img;
    int inv;


  /* check arguments */
    if (argc != 4) {
      printf("Usage: %s inv infile outfile\n", argv[0]);
      exit(1);
    }
    inv = atoi(argv[1]);

  /* read input image */
    printf("Reading %s as input image\n", argv[2]);
    read_image(argv[2], &in_img);

  /* compute 2-D FFT of input image */
    if (inv == 0)
      printf("Computing 2-D FFT of input image ......\n");
    else
      printf("Computing inverse 2-D FFT of input image ........\n");

    d2_fft(&in_img,&out_img,inv);

  /* write output image to file */
    printf("Writing output image to %s\n", argv[3]);
    write_image(argv[3], &out_img);
  
    printf("2-D FFT complete.\n"); 
    exit(0);
}  /* end main */
