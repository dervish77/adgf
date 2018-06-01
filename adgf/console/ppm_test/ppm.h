/*****************************************************************************
 *
 *	Header file for PPM image file functions.
 *
 *	File:	ppm.h
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
 *****************************************************************************/

#ifndef _PPM_H
#define _PPM_H


#define MAX_PIXEL_VALUE	255


extern 
void PPM_write(FILE *fp, char *raster_p, int maxr, int maxc, char *comment);

extern 
int PPM_read(FILE *fp, char *raster_p, int *maxr, int *maxc);


#endif /* _PPM_H */
