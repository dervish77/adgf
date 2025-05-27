/*****************************************************************************
 *
 *	Code for PPM image file writer and reader functions.
 *
 *	File:	ppm.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/19/95
 *
 *	Revisions:
 *	  2.0   03/22/96  replaced x,y with r,c
 *	  1.0	01/30/96  header cleaned up
 * 	  0.0	10/19/95  originated
 *
 *	Note:
 *		Assumes that raster_p points to a raster pixel array
 *		the pixels are stored by rows from top to bottom, left
 *		to right within each row.  Each pixel consists of three
 *		bytes in RGB order.
 *
 *****************************************************************************/

#include <stdio.h>

#ifndef _PPM_H
#include "ppm.h"
#endif


/*  PPM_write	- Write out PPM formated image file
 *
 *  Parameters:
 *	fp		- pointer to input file
 *	raster_p	- pointer to 2D raster array
 *	maxr		- pointer to size of image in X (rows)
 *	maxc		- pointer to size of image in Y (columns)
 *
 *  Returns:
 *	none
 */
void
PPM_write(FILE *fp, char *raster_p, int maxr, int maxc, char *comment)
{
   int r, c;
   char *ras_p;


   ras_p = (char *) raster_p;

   fprintf(fp, "P6\n");
   fprintf(fp, "# %s\n", comment);
   fprintf(fp, "%d %d\n", maxc, maxr);
   fprintf(fp, "%d\n", MAX_PIXEL_VALUE);  /* assume 8-bit color components */

   for (r = 0; r < maxr; r++)
   {
      for (c = 0; c < maxc; c++)
      {
         fprintf(fp, "%c%c%c", *(ras_p++), *(ras_p++), *(ras_p++));
      }
   }
}



/*  PPM_read	- Read in PPM formated image file
 *
 *		  Assumes raster points to a 2D array which can hold the
 *		  entire image.
 *
 *  Parameters:
 *	fp	- pointer to input file
 *	raster	- pointer to raster array
 *	maxr	- pointer to max size of image in Y (rows)
 *	maxc	- pointer to max size of image in X (columns)
 * 
 *  Returns:
 *	raster	- points to pixel data read in from file
 *	maxr	- pointer to actual size of image in Y (rows)
 *	maxc	- pointer to actual size of image in X (columns)
 *
 *	0	- if read of file was successful
 *	1	- else there was an error
 */
int
PPM_read(FILE *fp, char *raster_p, int *maxr, int *maxc)
{
   char id0, id1;
   int r, c;		/* loop indices */
   int R, C;		/* size of image */
   int max_pix_value;
   char buffer[80];
   char rv, gv, bv, *ras_p;


   ras_p = (char *) raster_p;

   fscanf(fp, "%c%c\n", &id0, &id1);

   if (id0 == 'P' && id1 == '6')
   {
      fgets(buffer, 80, fp);
      if (buffer[0] == '#')
      {
         fscanf(fp, "%d %d\n", &C, &R);
      }
      else
      {
         sscanf(buffer, "%d %d\n", &C, &R);
      }

      if ((R <= *maxr) && (C <= *maxc))
      {
         fscanf(fp, "%d\n", &max_pix_value);

         if (max_pix_value <= MAX_PIXEL_VALUE)
         {
            for (r = 0; r < R; r++)
            {
               for (c = 0; c < C; c++)
               {
                  fscanf(fp, "%c%c%c", &rv, &gv, &bv);

                  *(ras_p++) = rv; *(ras_p++) = gv; *(ras_p++) = bv;
               }
            }

            *maxr = R;
            *maxc = C;
         }
         else
         {
            fprintf(stderr, "PPM_read: exceeded max pixel value of %d\n", 
   							MAX_PIXEL_VALUE);
            return(1);
         }
      }
      else
      {
         fprintf(stderr, 
"PPM_read: image size exceeds available raster space - %d %d, %d %d\n",
		C, R, *maxc, *maxr);
         return(1);
      }
   }
   else
   {
      fprintf(stderr, "PPM_read: file is not a PPM image file\n");
      return(1);
   }

   return(0);	/* no errors while reading */
}
