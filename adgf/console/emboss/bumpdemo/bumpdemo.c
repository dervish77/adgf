/*******************************************************************

 File:	bumpdemo.c

 Date:	2/20/95

 Auth:  Brian Lingard

  This program is a demo of using the techniques of bump mapping
 for performing embossing of a "bump map" (like text) onto a 
 another texture image.  The resulting embossed texture could 
 be used as a texture map by another renderer.  Note that this 
 program makes use of some code found in "Graphics Gems IV", 
 Academic Press, 1994 called "emboss.c".  Please refer to 
 pp. 433-437 in that volume for details on its workings.  Also note
 that all image file formats are 24-bit Windows "BMP".


 Input:	
	bumpfile.bmp		- bump map file (usually text)
	texturefile.bmp		- optional texture file
	width45			- filter width (see text)
	azimuth			- light source direction
	elevation  		- light source direction

 Output:
	imagefile.bmp		- embossed image file

 Options:
	bumpdemo [-b file][-t file][-w US][-a DB][-e DB][[-o file]||[-d]]

********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imagfile.h"

/** define some globals **/
#define BUFLEN 81		/* text buffer length constant */
#define MAX_ARGS 13		/* max number of command arguments */

#define DEF_WIDTH45	3	/* default filter width */
#define DEF_AZIMUTH	45	/* default azimuth */
#define DEF_ELEVATION	15	/* default elevation */

#ifndef PI
#define PI 3.14125
#endif
#define dToR(d) ((d)*(PI/180))


/* functions prototypes */
void Emboss();			/* embossing code from "emboss.c" */

int Read_BMP();			/* BMP functions from "imagfile.c" */
int Write_BMP();

unsigned char *Alloc_Image();	/* generic image functions from "imagfile.c" */
void ConvertRGB_Grey();


/*  begin main program 
 */
main(argc, argv)
   int argc;
   char *argv[];
{
   int use_texture=0;			/* default to no texture file */
   int display_to_screen=0;		/* default to no screen display */

   char *end;

   unsigned short width45=3;		/* default width = 3 */
   double azimuth, elevation;

   unsigned short x_size, y_size;	/* size of final image */

   IMAGE_STRUCT bump;			/* struct def in imagfile.c */
   IMAGE_STRUCT greybump;
   IMAGE_STRUCT texture;
   IMAGE_STRUCT output;

   int i;


/* assign default options */
   sprintf(bump.fname, "bumptext.bmp");
   sprintf(texture.fname, "texture.bmp");
   sprintf(output.fname, "image.bmp");

   width45 = DEF_WIDTH45;
   azimuth = DEF_AZIMUTH;
   elevation = DEF_ELEVATION;


/* check command line arguments */
   switch(argc) {
     case 1:			/* use defaults args */
        break;
     default:			/* check args and parse */
        if (argc > MAX_ARGS) {
           fprintf(stderr,
              "usage: %s [-b file][-t file][[-w US][-a DB][-e DB][[-o file]||[-d]",
              argv[0]);
           exit(1);
        }
        else {                  /* parse argument inputs */
           i = 1;
           while (i < argc) {
              switch(argv[i][1]) {	/* switch on dash option */
                 case 'b':
                    sprintf(bump.fname, "%s", argv[i+1]);
                    i++;
                    break;
                 case 't':
                    sprintf(texture.fname, "%s", argv[i+1]);
                    i++;
                    use_texture = 1;
                    break;
                 case 'w':
                    width45 = (unsigned short) atoi(argv[i+1]);
                    i++;
                    break;
                 case 'a':
                    azimuth = strtod(argv[i+1], &end);
                    i++;
                    break;
                 case 'e':
                    elevation = strtod(argv[i+1], &end);
                    i++;
                    break;
                 case 'o':
                    sprintf(output.fname, "%s", argv[i+1]);
                    i++;
                    break;
                 case 'd':
                    display_to_screen = 1;
                    break;
              } /* end inner switch */
              i++;
           } /* end while */
        } /* end else */
     break;
   } /* end outer switch */

/* open bump map file */
   bump.file = fopen(bump.fname,"r");
   if (bump.file == (FILE *) NULL) {
    
      fprintf(stderr,"Main: could not open '%s' as bump map file", bump.fname);
      exit(1);
   }
   else {
      printf("Reading bump map from %s\n", bump.fname);
      Read_BMP(&bump);

      greybump.x_size = bump.x_size;
      greybump.y_size = bump.y_size;
      greybump.bytes_per_pixel = 1;
      greybump.num_colors = bump.num_colors;
      if (bump.colormap)
         greybump.colormap = bump.colormap;
      greybump.image = Alloc_Image(bump.x_size * bump.y_size);
      ConvertRGB_Grey(&bump, &greybump);
   }


/* open texture file */
   if (use_texture) {
      texture.file = fopen(texture.fname,"r");
      if (texture.file == (FILE *) NULL) {
         fprintf(stderr,"Main: could not open '%s' as texture file", texture.fname);
         exit(1);
      }
      else {
         printf("Reading texture image from %s\n", texture.fname);
         Read_BMP(&texture);
         x_size = texture.x_size;
         y_size = texture.y_size;
      }
   }
   else { /* we're just going emboss the bump map */
      printf("no texture image specified, just using bump map\n");
      texture.image = (unsigned char *) NULL;
      x_size = bump.x_size;
      y_size = bump.y_size;
   }


/* perform embossing function */
   output.x_size = x_size;
   output.y_size = y_size;
   output.bytes_per_pixel = 3;
   output.num_colors = texture.num_colors;
   output.image = Alloc_Image(x_size * y_size * 3);

   printf("Embossing image now ...\n");

   Emboss( dToR(azimuth), dToR(elevation), width45, 
	greybump.image, texture.image, output.image, x_size, y_size);


/* output embossed image */
   if (display_to_screen) {
      printf("displaying embossed image to screen ...\n");
   }
   else {
      output.file = fopen(output.fname,"w");
      if (output.file == (FILE *) NULL) {
         fprintf(stderr,"Main: could not open '%s' as output file", output.fname);
         exit(1);
      }
      else {
         printf("Writing embossed image to %s\n", output.fname);
         Write_BMP(&output);
      }
   }


/* close all files */
   fclose(bump.file);
   if (use_texture)
      fclose(texture.file);
   fclose(output.file);

} /* end of main() */
