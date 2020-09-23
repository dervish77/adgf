/**********************************************************

 File:	imagfile.h

 Date:	2/20/95

 Auth:	Brian Lingard


  This file contains header information for "imagfile.c".
 "imagfile.c" contains functions for reading and writing
 image files.  


 Currently supported types are:

	BMP	- Windows bitmap
	TIFF	- tagged image file format
	XBM	- X-windows bitmap

**********************************************************/

#define FNAMELENGTH 81


/* uniform image structure */

typedef struct {
   char fname[FNAMELENGTH];		/* file name array */
   FILE *file;				/* file pointer */
   unsigned short x_size;		/* image width in pixels */
   unsigned short y_size;		/* image height in pixels */
   unsigned short bytes_per_pixel;	/* bytes per pixel */
   unsigned short num_colors;		/* number of colors in color map */
   unsigned char *colormap;		/* pointer to color map */
   unsigned char *image;		/* pointer to pixels */
} IMAGE_STRUCT;


/* structures for BMP images */

typedef struct {
   char 	  bfch1;		/* file type -- "BM" */
   char 	  bfch2;		
   unsigned long  bfsize;		/* size of file in bytes */
   short int 	  bfres1;
   short int 	  bfres2;
   unsigned long  bfoffbits;		/* byte offset where image begins */
   unsigned long  bisize;		/* size of this header, 40 bytes */
   unsigned long  biwidth;		/* image width in pixels */
   unsigned long  biheight;		/* image height in pixels */
   unsigned short biplanes;		/* number of image planes (always 1) */
   unsigned short bibitcnt;		/* bits per pixel, 1,4,8 or 24 */
   unsigned long  bicomp;		/* compression type */
   unsigned long  bisizecomp;		/* size of compressed image */
   unsigned long  bixppm;		/* x pixels per meter */
   unsigned long  biyppm;		/* y pixels per meter */
   unsigned long  biclrused;		/* number of colors in map */
   unsigned long  biclrimp;		/* number of important colors */
   unsigned char  *colormap;		/* pointer to color map, 4*N bytes */
} BMP_HEADER;


/* end of imagfile.h */
