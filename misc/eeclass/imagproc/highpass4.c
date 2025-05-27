From rayssd!SUD2.ED.RAY.COM!LINGARD@uunet.UU.NET Wed Oct 20 13:37:36 1993
Received: from relay2.UU.NET (relay2.UU.NET [192.48.96.7]) by bigboote (8.6.2/8.6) with SMTP id NAA07668 for <lingard@wpi.edu>; Wed, 20 Oct 1993 13:36:34 -0400
Received: from spool.uu.net (via LOCALHOST) by relay2.UU.NET with SMTP 
	(5.61/UUNET-internet-primary) id AA11923; Wed, 20 Oct 93 13:35:20 -0400
Received: from rayssd.UUCP by uucp4.uu.net with UUCP/RMAIL
	(queueing-rmail) id 133341.21935; Wed, 20 Oct 1993 13:33:41 EDT
Received: from SUD2.ED.RAY.COM by rayssd.ssd.ray.com with SMTP id AA05213
  (5.65c/IDA-1.5 for <lingard@wpi.edu>); Wed, 20 Oct 1993 12:37:04 -0400
Received: from SUD2.ED.RAY.COM by SUD2.ED.RAY.COM (PMDF #2325 ) id
 <01H4C3M667CG8WXHVW@SUD2.ED.RAY.COM>; Wed, 20 Oct 1993 12:39:01 EDT
Date: 20 Oct 1993 12:39:00 -0400 (EDT)
From: LINGARD@SUD2.ED.RAY.COM
To: lingard@wpi.edu
Message-Id: <01H4C3M667CI8WXHVW@SUD2.ED.RAY.COM>
X-Envelope-To: lingard@wpi.edu
X-Vms-To: RM"lingard@wpi.edu"
Mime-Version: 1.0
Content-Transfer-Encoding: 7BIT
Status: R

/*************************************************************************
*  Problem #4 Solution:
*
*  This program performs a high or low pass filter operation on an input
*  image using an nxn filter.  The filter size is assumed to be odd and 
*  at least 3x3.  This program also assumes that xdim is vertical and 
*  ydim is horizontal.
*
*  Filename:   highpass.c
*  Author:     Brian Lingard
*  Date:       10/18/93
*
*  Usage:      highpass horl n infile outfile     
*  Example:    highpass 0 3 cronk.img cronkhigh.img	low pass 3x3 filter
*  Example:    highpass 1 5 cronk.img cronkhigh.img	high pass 5x5 filter
*
*  Compile String:
*  cc highpass.c -O -o highpass -lm
*
**************************************************************************/
     
#include <stdio.h>
#include <math.h>		    /* declare math functions to use */
#include "const.h"
#include "typedef.h"
#include "imgio.h"

#define DEBUG 1    
#define BORDER_VALUE 128	/* mid point on gray scale */


/* procedure to perform low pass filter operation using 
the following algorithm:

	for x=n/2 to NX - 1 + n/2 
	  for y=n/2 to NY - 1 + n/2
	     if first element then
	       compute average over nxn filter
	       g(x-n/2,y-n/2) = average
	     else
	       compute revised average using new leading edge values
	       g(x-n/2,y-n/2) = average
	     end if
	  end for 
	end for
*/
void lowpass(n,img_in,img_out)
	int n;
	GIFF *img_in,*img_out;
{
	BYTE *z_ptr,*in_ptr,*out_ptr;
	int NX,NY,x,y,i,j;
	int avg,psum;
	int bpp;

if (DEBUG == 1) printf("lowpass: starting low pass operation\n");

     /* extract dimensions of input image */
	NX = img_in->xdim;
	NY = img_in->ydim;
	in_ptr = img_in->bits;
if (DEBUG == 1) printf("lowpass: image size is %d by %d\n",NX,NY);

     /* allocate memory for temp image and output image */
	bpp = bytes_per_pixel(img_in->type);
	z_ptr = (BYTE *) malloc((NX + 2*(n/2)) * (NY + 2*(n/2)) * bpp);
	if (!z_ptr) {
	  printf("lowpass: z img mem request failed!\n");
	  exit(1);
	}
	out_ptr = (BYTE *) malloc(NX * NY * bpp);
	if (!out_ptr) {
	  printf("lowpass: out img mem request failed!\n");
	  exit(1);
	}

     /* copy results to output image */
	img_out->type = img_in->type;
	img_out->xdim = NX;
	img_out->ydim = NY;
	img_out->bits = out_ptr;

     /* copy f(x,y) into z(x,y) */
	for (x = n/2; x <= (NX - 1 + (n/2)); x++) {
	  for (y = n/2; y <= (NY - 1 + (n/2)); y++) {
	    *(z_ptr + x*NY + y) = *(in_ptr + (x - (n/2))*NY + (y - (n/2)));
	  }
	}

     /* initialize top and bottom borders of z(x,y) */
	for (x = 0; x <= n/2; x++) {
	  for (y = 0; y <= (NY - 1 + 2*(n/2)); y++) {
	    *(z_ptr + x*NY + y) = BORDER_VALUE;
	    *(z_ptr + (x + NX + n/2)*NY + y) = BORDER_VALUE;
	  }
	}

     /* initialize left and right borders of z(x,y) */
	for (y = 0; y <= n/2; y++) {
	  for (x = 0; x <= (NX - 1 + 2*(n/2)); x++) {
	    *(z_ptr + x*NY + y) = BORDER_VALUE;
	    *(z_ptr + x*NY + (y + NY + (n/2))) = BORDER_VALUE;
	  }
	}

     /* compute moving average of z(x,y) storing result in g(x,y) */
	for (x = n/2; x <= (NX - 1 + n/2); x++) {
	  for (y = n/2; y <= (NY - 1 + n/2); y++) {
	    if (x == n/2 && y == n/2) {	/* if first element */
	      psum = 0;
	      /* compute average over nxn filter */
	      for (i = -n/2; i <= n/2; i++) {
	        for (j = -n/2; j <= n/2; j++) {
	          /* psum = psum + z(x+i,y+j) */
	          psum = psum + *(z_ptr + (x+i)*NY + (y+j));
	        }
	      }
	      avg = psum / (n*n);
	      /* g(x-n/2,y-n/2) = average */
	      *(out_ptr + (x - n/2)*NY + (y - n/2)) = avg;
	    }

	    else { /* else all other elements */
	      /* compute revised average using updated leading edge values */
	      for (i = -n/2; i <= n/2; i++) {
	        /* psum = psum - z(x+i,y-n/2-1) + z(x+i,y+n/2) */
	        psum = psum - *(z_ptr + (x+i)*NY + (y - n/2 - 1));
	        psum = psum + *(z_ptr + (x+i)*NY + (y + n/2));
	      }
	      /* g(x-n/2,y-n/2) = average */
	      *(out_ptr + (x - n/2)*NY + (y - n/2)) = psum / (n*n);
	    } /* end if first element */

	  } /* end for y */
	} /* end for x */
} /* end of lowpass() */

/* procedure for computing high pass image from low pass image and original */
void highpass(img_orig,img_low,img_out)
	GIFF *img_orig,*img_low,*img_out;
{
	BYTE *orig_ptr,*low_ptr,*out_ptr;
	int NX,NY,x,y;
	int bpp;

if (DEBUG == 1) printf("highpass: starting high pass operation\n");

     /* extract dimensions of original input image */
	NX = img_orig->xdim;
	NY = img_orig->ydim;
	orig_ptr = img_orig->bits;
if (DEBUG == 1) printf("highpass: image size is %d by %d\n",NX,NY);

     /* setup low pass image pointer */
	low_ptr = img_low->bits;

     /* allocate memory for output image */
	bpp = bytes_per_pixel(img_orig->type);
	out_ptr = (BYTE *) malloc(NX * NY * bpp);
	if (!out_ptr) {
	  printf("highpass: out img mem request failed!\n");
	  exit(1);
	}

     /* copy results to output image */
	img_out->type = img_orig->type;
	img_out->xdim = NX;
	img_out->ydim = NY;
	img_out->bits = out_ptr;

     /* perform highpass = original - lowpass */
	for (x = 0; x <= NX - 1; x++) {
	  for (y = 0; y <= NY - 1; y++) {
	    *(out_ptr+x*NY+y) = *(orig_ptr+x*NY+y) - *(low_ptr+x*NY+y);
	  } /* end for y */
	} /* end for x */
} /* end of highpass */

/* main program */

int main(argc,argv)
     int argc;
     char *argv[];
{
    GIFF *input_img;
    GIFF *output_img;
    GIFF *lowpass_img;

  /* check arguments */
    if (argc != 5) {
      printf("Usage: %s horl n infile outfile\n", argv[0]);
      exit(1);
    }

  /* read input image */
    printf("Reading %s as input image\n", argv[3]);
    read_image(argv[3], &input_img);

  /* compute low or high pass of input image */
    if (atoi(argv[1]) == 0){
      printf("Computing low pass of input image ......\n");
      printf("... using %dx%d filter\n",atoi(argv[2]),atoi(argv[2]));
    }
    else
      printf("Computing high pass of input image ........\n");

    lowpass(atoi(argv[2]),&input_img,&lowpass_img);

    if (atoi(argv[1]) == 0) {
      /* write lowpass as output image to file */
      printf("Writing low pass as output image to %s\n", argv[4]);
      write_image(argv[4], &lowpass_img);
    }
    else {
      highpass(&input_img,&lowpass_img,&output_img);
      /* write highpass as output image to file */
      printf("Writing high pass as output image to %s\n", argv[4]);
      write_image(argv[4], &output_img);
    }

    printf("Program complete.\n"); 
    exit(0);
}  /* end main */

