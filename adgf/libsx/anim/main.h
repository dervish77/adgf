/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#include "invkine.h"


/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
  int		dataloaded;		/* data loaded flag */
  int		redraw;			/* clear drawing area flag */
  int 		button_state;		/* current state of left button */
  int		endgrabbed;		/* end effector grabbed flag */
  float		frame_rate;		/* frames per second */
  int		frame_interval;		/* time 'til next frame, milliseconds */
  int		frame_count;		/* current frame count */
  int		running_anim;		/* running animation flag */
  int		curr_mousx;		/* current mouse position x,y */
  int		curr_mousy;
  int 		num_links;		/* number of links */
  linkType 	links[MAX_NUM_LINKS];	/* array of link structures */
  endType  	end_effect;		/* end effector structure */
  animType	anim;			/* animation structure */
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);


#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif


#endif /* _MAIN_H */
/* end of main.h */
