/**********************************************************

 File:	imagfile.c

 Date:	2/20/95

 Auth:	Brian Lingard


  This file contains functions to read and write image 
 files.  Each function uses a standard intermediate image
 structure as defined in "imagfile.h".  


 Currently supported types are:

	BMP	- Windows bitmap
	TIFF	- tagged image file format
	XBM	- X-windows bitmap

**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "imagfile.h"

/* #define DEBUG 1 */

/*
 *
 *  BMP functions 
 *
 */

int Read_BMP(input)
   IMAGE_STRUCT *input;
{
   BMP_HEADER filehdr;

   unsigned long getlong();
   unsigned short getshort();
   unsigned char *Alloc_Image();

   unsigned char *color_map;		/* temp color map ptr */
   unsigned char *image_data;		/* temp image ptr */

   int bytes_in_image, bytes_in_clrmap;
   int i, b, c;
   int padb;				/* num pad bytes */
   int bprow;				/* bytes per row */
   int bpp;				/* bytes per pixel */
   unsigned char mung;


   /* read in header information */
   filehdr.bfch1 = fgetc(input->file);
   filehdr.bfch2 = fgetc(input->file);

   if ((filehdr.bfch1 != 'B') || (filehdr.bfch2 != 'M')) {
      fprintf(stderr, "File %s is not of type BMP\n", input->fname);
      exit(1);
   }
 
   filehdr.bfsize = getlong(input->file);

   fseek(input->file, 10L, 0L);			/* skip reserved words */
   filehdr.bfoffbits = getlong(input->file);

   filehdr.bisize = getlong(input->file);

   if (filehdr.bisize != 40) {
      fprintf(stderr, "BMP file is corrupted\n");
      exit(1);
   }

   filehdr.biwidth = getlong(input->file);
   filehdr.biheight = getlong(input->file);
   filehdr.biplanes = getshort(input->file);
   filehdr.bibitcnt = getshort(input->file);
   filehdr.bicomp = getlong(input->file);
   filehdr.bisizecomp = getlong(input->file);
   filehdr.bixppm = getlong(input->file);
   filehdr.biyppm = getlong(input->file);
   filehdr.biclrused = getlong(input->file);
   filehdr.biclrimp = getlong(input->file);


   /* copy relevant info into image structure */
   input->x_size = filehdr.biwidth;
   input->y_size = filehdr.biheight;
   input->num_colors = filehdr.biclrused;

#if DEBUG
   printf("bfsize = %u\n", filehdr.bfsize);
   printf("bfoffbits = %u\n", filehdr.bfoffbits);
   printf("bisize = %u\n", filehdr.bisize);
   printf("biwidth = %u\n", filehdr.biwidth);
   printf("biheight = %u\n", filehdr.biheight);
   printf("biplanes = %u\n", filehdr.biplanes);
   printf("bibitcnt = %u\n", filehdr.bibitcnt);
   printf("bicomp = %u\n", filehdr.bicomp);
   printf("bisizecomp = %u\n", filehdr.bisizecomp);
   printf("bixppm = %u\n", filehdr.bixppm);
   printf("biyppm = %u\n", filehdr.biyppm);
   printf("biclrused = %u\n", filehdr.biclrused);
   printf("biclrimp = %u\n", filehdr.biclrimp);
#endif

   /* 
    * if less than 24 bits per pixel, must read in color map 
    */
   if (filehdr.bibitcnt != 24) { 

      bytes_in_clrmap = filehdr.biclrused * 4;

      input->colormap = Alloc_Image(filehdr.biclrused * 3);

      /* read in color map */
      input->colormap = color_map;
      if (fgets(color_map, bytes_in_clrmap, input->file) == NULL) {
         fprintf(stderr, "Error while reading color map of '%s'\n", input->fname);
         exit(1);
      }

      /*
       * strip out padded zero bytes 
       */

      color_map = input->colormap;



      bpp = 1;
   }
   else { /* no color map is present */
      bytes_in_clrmap = 0;
      bpp = 3;
   }
   

   /*  finally read in image itself
    *
    *  stripping out padded zeros at end of rows and reorder pixel
    *  data so that the data starts at the top left pixel 
    */

   input->image = Alloc_Image(input->x_size * input->y_size * bpp);

   /* set temp image pointer */
   image_data = input->image;			

   /* position at start of image */
/*   fseek(input->file, filehdr.bfoffbits, 0L);	*/

   /* calculate number  of pad bytes */
   bytes_in_image = filehdr.bfsize - (14 + filehdr.bisize + bytes_in_clrmap);

   bprow = bytes_in_image / input->y_size;	/* bytes per row */

   padb = bprow - ((bprow / 4) * 4);		/* padb = bprow mod 4 */  

   b = 0;

   image_data += ((input->x_size * input->y_size * 3) - (input->x_size * 3));

   /* while not eof and all bytes not read yet */
   while ((!feof(input->file)) && (b < bytes_in_image)) { 

      for (i=0; i < input->x_size; i++) {	/* read one row's worth */

         for (c=0; c < bpp; c++) {
            *(image_data + (i * bpp) + c) = fgetc(input->file);;
            b++;
         }

      }

      image_data -= (input->x_size * bpp);	/* go up one row */

      if (padb > 0) {				/* if padded */
         for (i=0; i<padb; i++) {			/* read in pad bytes */
            mung = fgetc(input->file);
            b++;
         }
      }
   } 


   fprintf(stdout, "  ... read %d bytes from image\n", b);

   input->bytes_per_pixel = bpp;

   return(0);
} /* end of Read_BMP() */


int Write_BMP(output)
   IMAGE_STRUCT *output;
{
   BMP_HEADER filehdr;

   unsigned char *Alloc_Image();

   unsigned char *color_map;		/* temp color map ptr */
   unsigned char *image_data;		/* temp image ptr */

   int bytes_in_image, bytes_in_clrmap;
   int x, y, b;
   int padb;				/* num pad bytes */
   int bprow;				/* bytes per row */
   int bpp;				/* bytes per pixel */
   int req_bprow;			/* required bytes per row */
   unsigned char mung=0;


   /*  calculate some necessary numbers
    */
   bpp = output->bytes_per_pixel;

   bprow = output->x_size * bpp;

   padb = ((((output->x_size * bpp) / 4) + 1) * 4) - (output->x_size * bpp);

   if (padb == 4)	/* if (X * bpp) was evenly divisible by 4 */
      padb = 0;		/* then no pad bytes required */

   req_bprow = bprow + padb;

   bytes_in_image = (req_bprow * output->y_size) + 54;


   /*  set up all file header info   
    */
   filehdr.bfsize = bytes_in_image;
   filehdr.bfres1 = (unsigned short) 0;		/* short */
   filehdr.bfres2 = (unsigned short) 0;		/* short */
   filehdr.bfoffbits = 54L;
   filehdr.bisize = 40L;
   filehdr.biwidth = output->x_size;
   filehdr.biheight = output->y_size;
   filehdr.biplanes = (unsigned short) 1;	/* short */
   filehdr.bibitcnt = (unsigned short) 24;	/* short */
   filehdr.bicomp = 0;
   filehdr.bisizecomp = bprow * output->y_size;
   filehdr.bixppm = 0;
   filehdr.biyppm = 0;
   filehdr.biclrused = output->num_colors;
   filehdr.biclrimp = output->num_colors;

#if DEBUG
   printf("bfsize = %u\n", filehdr.bfsize);
   printf("bfoffbits = %u\n", filehdr.bfoffbits);
   printf("bisize = %u\n", filehdr.bisize);
   printf("biwidth = %u\n", filehdr.biwidth);
   printf("biheight = %u\n", filehdr.biheight);
   printf("biplanes = %u\n", filehdr.biplanes);
   printf("bibitcnt = %u\n", filehdr.bibitcnt);
   printf("bicomp = %u\n", filehdr.bicomp);
   printf("bisizecomp = %u\n", filehdr.bisizecomp);
   printf("bixppm = %u\n", filehdr.bixppm);
   printf("biyppm = %u\n", filehdr.biyppm);
   printf("biclrused = %u\n", filehdr.biclrused);
   printf("biclrimp = %u\n", filehdr.biclrimp);
#endif

   /*  output header to file 
    */
   fputc('B', output->file);
   fputc('M', output->file);
   putlong(output->file, filehdr.bfsize);
   putshort(output->file, filehdr.bfres1);
   putshort(output->file, filehdr.bfres2);
   putlong(output->file, filehdr.bfoffbits);
   putlong(output->file, filehdr.bisize);
   putlong(output->file, filehdr.biwidth);
   putlong(output->file, filehdr.biheight);
   putshort(output->file, filehdr.biplanes);
   putshort(output->file, filehdr.bibitcnt);
   putlong(output->file, filehdr.bicomp);
   putlong(output->file, filehdr.bisizecomp);
   putlong(output->file, filehdr.bixppm);
   putlong(output->file, filehdr.biyppm);
   putlong(output->file, filehdr.biclrused);
   putlong(output->file, filehdr.biclrimp);


   /*  output color map, if there is one
    */
   if (filehdr.bibitcnt != 24) {


   }


   /*  output image, padding rows to a 4 byte boundary
    */
   image_data = output->image;

   for (y = output->y_size - 1; y >= 0; y--) {	/* write row y from bottom up */

      for (x = 0; x < output->x_size; x++) {	/* write RGB for each row pixel */

         fputc(*(image_data + ((y * output->x_size + x) * bpp) + 0), output->file);
         fputc(*(image_data + ((y * output->x_size + x) * bpp) + 1), output->file);
         fputc(*(image_data + ((y * output->x_size + x) * bpp) + 2), output->file);
      }

      if (padb > 0)
         fputc(mung, output->file);
   }

   return(0);
} /* end of Write_BMP() */


/*
 * 
 *  TIFF functions
 *
 */

int Read_TIFF(input)
   IMAGE_STRUCT *input;
{

   return(0);
} /* end of Read_TIFF() */


int Write_TIFF(output)
   IMAGE_STRUCT *output;
{

   return(0);
} /* end of Write_TIFF() */


/*
 * 
 *  XBM functions
 *
 */

int Read_XBM(input)
   IMAGE_STRUCT *input;
{

   return(0);
} /* end of Read_XBM() */


int Write_XBM(output)
   IMAGE_STRUCT *output;
{

   return(0);
} /* end of Write_XBM() */


/*
 * 
 *  miscellaneous functions
 *
 */

/*  reads num_bytes from a raw binary file 
 */
int Read_Raw(input, num_bytes)	
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

 
/*  read 4 bytes from current position in file 
 *  and convert little endian to long int 
 */
unsigned long getlong(fileptr)	
   FILE *fileptr;
{
   unsigned char chr[4];
   unsigned long number;
   int i;

   number = 0;

   for (i=0; i < 4; i++) {
      chr[i] = fgetc(fileptr);
   }

   number = chr[0];
   number += chr[1] * 256;
   number += chr[2] * 256 * 256;
   number += chr[3] * 256 * 256 * 256;

   return(number);
} /* end of getlong() */


/*  read 2 bytes from current position in file 
 *  and convert little endian to short int 
 */
unsigned short getshort(fileptr)	
   FILE *fileptr;
{
   unsigned char chr[2];
   unsigned short number;
   int i;

   number = 0;

   for (i=0; i < 2; i++) {
      chr[i] = fgetc(fileptr);
   }

   number = chr[0];
   number += chr[1] * 256;

   return(number);
} /* end of getshort() */


/*  write 4 bytes to current position in file 
 *  and convert from long int to little endian
 */
int putlong(fileptr, number)	
   FILE *fileptr;
   unsigned long number;
{
   unsigned char chr;
   int i;
   unsigned long num, idiv, imod;

   num = number;

   for (i=0; i < 4; i++) {

      idiv = num / 256;

      imod = num - (idiv * 256);

      num = idiv;

      chr = (unsigned char) imod;

      fputc(chr, fileptr);
   }

   return(0);
} /* end of putlong() */

 
/*  write 2 bytes to current position in file 
 *  and convert from short int to little endian 
 */
int putshort(fileptr, number)	
   FILE *fileptr;
   unsigned short number;
{
   unsigned char chr;
   int i;
   unsigned short num, idiv, imod;

   num = number;

   for (i=0; i < 2; i++) {

      idiv = num / 256;

      imod = num - (idiv * 256);

      num = idiv;

      chr = (unsigned char) imod;

      fputc(chr, fileptr);
   }

   return(0);
} /* end of putshort() */


/*  allocate memory for images and color maps 
 */
unsigned char *Alloc_Image(num_bytes)
   int num_bytes;
{
   unsigned char *ptr;

   ptr = (unsigned char *) calloc(num_bytes, sizeof(unsigned char));
   if (ptr == (unsigned char *) NULL) {
      fprintf(stderr, "couldn't allocate memory for image space\n");
      exit(1);
   }

   return(ptr);
} /* end of Alloc_Image() */


/*  convert an RGB image into a greyscale image
 */
int ConvertRGB_Grey(rgb, grey)
   IMAGE_STRUCT *rgb;		/* assumes 3 bytes per pixel */
   IMAGE_STRUCT *grey;		/* assumes 1 byte per pixel */
{
   int x, y;
   unsigned char r, g, b;	/* color components */
   unsigned char intensity;
   unsigned char *rgbptr, *greyptr;

   unsigned char maxrgb();


   rgbptr = rgb->image;			/* copy temp pointers */
   greyptr = grey->image;

   for (y = 0; y < rgb->y_size; y++) {	/* for each row of pixels */

      for (x = 0; x < rgb->x_size; x++) {  /* for each pixel in a row */

         r = *(rgbptr + 0);
         g = *(rgbptr + 1);
         b = *(rgbptr + 2);

         /*  ideally want to convert to HSV and use those components
          *  to actually determine the relative grey scale
          */
         intensity = maxrgb(r, g, b);

         *greyptr++ = intensity;

         rgbptr += rgb->bytes_per_pixel;	/* incr by bpp */
      }
   }

   return(0);
} /* end of ConvertRGB_Grey() */


/*  function to find max RGB color component
*/
unsigned char maxrgb(r, g, b)
   unsigned char r, g, b;
{
   unsigned char maxval;

   maxval = r;

   if (maxval < g)
      maxval = g;

   if (maxval < b)
      maxval = b;

   return(maxval);
} /* end of maxrgb() */

/** end of imagfile.c **/
