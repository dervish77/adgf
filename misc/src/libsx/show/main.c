/* This demo program shows how to display a Raster Image (i.e. bitmap). 
 * It allocates a bitmap, fills it in with data from an input file, and then 
 * draws it centered in the drawing area. 
 *
 * You should notice that I've modified the main.h file so that we can
 * store information about the bitmap there instead of having all kinds
 * of ugly global variables.
 *
 *   Dominic Giampaolo
 *   dbg@sgi.com
 */
/* modified by Matt Ward (matt@cs.wpi.edu) to specify a raster file as a
 * command line argument.  Format of the file is .img format, which has
 * a six byte header:
	bytes 0-1 are the file type (in this case, the type is 2)
	bytes 2-3 is the image width	
	bytes 4-5 is the image height
	rest of file is 1 byte per pixel in row major form.
 * Matt`s raytracer outputs files of this format.
 * Color map is set to all grey scales, so while cursor is in window, rest
 * of screen goes blank.  This should be fixed some day....
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "libsx.h"             /* should come first, defines libsx stuff  */
#include "main.h"              /* where program specific stuff is defined */
#include "callbacks.h"         /* prototypes for callback functions       */


/* define's */
#define X_SIZE 600             /* default draw area size, change as desired */
#define Y_SIZE 600

/* internal prototype */
void fill_in_bitmap(MyProgram *me, short, short);

int inf;


void main(int argc, char **argv)
{
  MyProgram mydata;

  short sbuf[3];
/* open the data file */
  if(argc != 2)	{
     printf("Usage: show_img imagefile\n");
     exit(-1);
     }
  inf = open(argv[1], 2);
  if(inf < 0)	{
     printf("failed to open file %s\n", argv[1]);
     exit(-1);
     }
/* read the header */
  read(inf, sbuf, 6);
  printf("size is %d by %d\n", sbuf[1], sbuf[2]);
  
/* allocate space for image */
  mydata.bitmap = (char *)malloc(sbuf[1]*sbuf[2]);  /* a 100x100 bitmap */
  if (mydata.bitmap == NULL)
   {
     fprintf(stderr, "Fooey, no memory for bitmap.\n");
     exit(10);
   }
  mydata.bitmap_width   = sbuf[1];
  mydata.bitmap_height  = sbuf[2];

  init_display(argc, argv, &mydata);  /* setup the display */

  fill_in_bitmap(&mydata, sbuf[1], sbuf[2]); /* read data into the bitmap */

  MainLoop();                         /* go right into the main loop */
}



/* This function sets up the display.  For any kind of a real program, 
 * you'll probably want to save the values returned by the MakeXXX calls
 * so that you have a way to refer to the display widgets you have 
 * created (like if you have more than one drawing area, and want to
 * draw into both of them).
 */

void init_display(int argc, char **argv, MyProgram *me)
{
  Widget w[5];

  if (OpenDisplay(argc, argv) == FALSE)
    return;

  w[0] = MakeButton("Quit!",      quit,     me);

  w[1] = MakeLabel("Bitmap demo program");

  w[2] = MakeDrawArea(X_SIZE, Y_SIZE, redisplay, me);

  
  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE, NULL);
  SetWidgetPos(w[2], PLACE_UNDER, w[0], NO_CARE, NULL);
  

  /* This call actually causes the whole thing to be displayed on the
   * screen.  You have to call this function before doing any drawing
   * into the window.
   */
  ShowDisplay();

  
  /* Get standard (red, blue, green, yellow, black, white) colors for
   * drawing stuff.  Check libsx.h for more info. 
  GetStandardColors();
   */

/* set up a grey ramp color map */
  GetAllColors();
  SetColorMap(GREY_SCALE_2);

 /* If you wanted to get all the colors in the colormap, you'd do the
  * following :
  *
  *    GetAllColors();
  *    SetColorMap(GREY_SCALE_1);
  *
  * You can wait to do it till later if you want.  There's no need 
  * to do it here if you don't need to (because it wacks out the
  * colormap).  Check libsx.h for other colormap types you can 
  * ask for (like RAINBOW_{1,2} or GREY_SCALE_{1,2}).
  */
}



/*
 * Read the data from the input file
 */
void fill_in_bitmap(MyProgram *me, short xsz, short ysz)
{
  int i,j;
  char *ptr = me->bitmap;

  for(i=0; i < ysz; i++)	{
       read(inf, ptr, xsz);
       ptr += xsz;
     }
}
