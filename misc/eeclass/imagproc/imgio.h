/*******************************************************************
   This include file imgio.h contains two procedures:
   one that reads, from input specified by filename, an image file
   and one that writes to the output file specified by filename.

   Along with each image is a head which contains the image type, ie.
   a gray level image or a binary image, and the dimensions.
  
   Usage:    #include "include/imgio1.h"
            
   Author: ggu                               Created:  July 1988

 *******************************************************************/
    
int bytes_per_pixel(img_type)
WORD img_type;
{
	switch(img_type) {
		case CHAR: 	return(sizeof(BYTE)); break;
		case SHORT: 	return(sizeof(short)); break;
		case INT: 	return(sizeof(int)); break;
		case FLOAT: 	return(sizeof(float)); break;
		case DOUBLE: 	return(sizeof(double)); break;
		case COMPLEX: 	return(sizeof(complex)); break;
	}
}

/********************************************************************
********************************************************************/

void read_image(filename,img)
char *filename;
GIFF *img;
{
  	int fd;
	int bpp; 		/* bytes per pixel */

  	if ((fd = open(filename,0)) == -1){
		printf("Error open file %s", filename);
		exit(1);
  	}
     
	/* read GIFF file head */
	read(fd, &img->type, 2);
	read(fd, &img->xdim, 2);
	read(fd, &img->ydim, 2);

	bpp = bytes_per_pixel(img->type);
	img->bits = (BYTE *) malloc(img->xdim * img->ydim * bpp);
	if (!img->bits) {
		printf("read_image: memory request failed!\n");
		exit(1);
	}
 	/* allocates memory */

  	/* get image data */
	read(fd, img->bits, img->xdim*img->ydim*bpp);

  	close(fd);
  	fprintf(stderr, "OUT <- read_image()\n");
}  /* end of read_image */

/*******************************************************************
*******************************************************************/

void write_image(filename,img)
char *filename;
GIFF *img;
{
  	int fd;
	int bpp; 		/* bytes per pixel */

  	if ((fd = creat(filename,PMODE)) == -1){
		printf("Error open file %s", filename);
		exit(2);
  	}
     
	/* write GIFF file head */
	write(fd, &img->type, 2);
	write(fd, &img->xdim, 2);
	write(fd, &img->ydim, 2);
 
  	/* put image data */
	bpp = bytes_per_pixel(img->type);
	write(fd, img->bits, img->xdim*img->ydim*bpp);

	close(fd);
	fprintf(stderr, "OUT: <- write_image()\n");
}   /* end write_image */
