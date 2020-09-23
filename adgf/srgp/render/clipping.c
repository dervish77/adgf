/* 

   A collection of routines used for clipping by routines in
   rendutls.h.  This file contains routines for both 2D and 
   3D clipping.

   File:   clipping.c

   Author: Brian Lingard

   Rev history:   
	0 - 11/15/94  originated

   NOTE:
	The functions in this file expect certain global constants
	to have been defined.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "render.h"

/* external globals */
extern int vertex_count;
extern int edge_count;
extern int polygon_count;

extern vertexType vertex_list[];
extern edgeType edge_list[];
extern polygonType polygon_list[];

extern viewrangeType view_data[];	/* used for three simul. views */
extern viewdataType view;		/* used for para & pers views */
extern viewplaneType vplane;		/* view plane information */

extern FILE *debugfile;


/* define typedefs used in 2D clipping */
typedef struct {
   unsigned all;
   unsigned left:4;
   unsigned right:4;
   unsigned bottom:4;
   unsigned top:4;
} clipcodeType;

/* define typedefs used in 3D clipping */
typedef struct {
   unsigned all;
   unsigned above:6;
   unsigned below:6;
   unsigned right:6;
   unsigned left:6;
   unsigned behind:6;
   unsigned infront:6;
} clip3DcodeType;


/******************************************************************

  GenClipCode() -- This function generates the 2D Cohen-Sutherland 
		clipping code for determining whether a vertex is 
		within the clipping rectangle.

		Bit 3 - above top edge 		y > wymax
		Bit 2 - below bottom edge	y < wymin
		Bit 1 - right of right edge	x > wxmax 
		Bit 0 - left of left edge	x < wxmin 

******************************************************************/
clipcodeType
GenClipCode(viewport, x, y)
   viewportType viewport;
   double x, y;			/* x and y coords of vertex */
{
   clipcodeType code;		/* clipping code for this vertex */

   /* initialize the clip code */
   code.top = 0;
   code.bottom = 0;
   code.right = 0;
   code.left = 0;
   code.all = 0;

   /* check against top and bottom of clip rectangle */
   if (y > view_data[viewport].wymax) {
      code.top = 8;
      code.all += code.top;
   } else if (y < view_data[viewport].wymin) {
      code.bottom = 4;
      code.all += code.bottom;
   }

   /* check against right and left of clip rectangle */
   if (x > view_data[viewport].wxmax) {
      code.right = 2;
      code.all += code.right;
   } else if (x < view_data[viewport].wxmin) {
      code.left = 1;
      code.all += code.left;
   }

   return(code);
} /* end of GenClipCode() */


/******************************************************************

  ClipEdge() -- This function clips the specified edge against the 
		selected view port boundaries, and returns the 
		clipped edge's start vertex and end vertex.  This 
		function does not create closed polygons if lines 
		are clipped.

		NOTE:
		    This function performs clipping via the 2D 
		  Cohen-Stutherland clipping algorithm as described 
		  in section 3.9.3 of the text book.  Though it is
		  not the highest performance technique, it should 
		  serve the purpose.

******************************************************************/
int
ClipEdge(viewport, e_index, startv, endv)
   viewportType viewport;	/* which viewport for clip boundary */
   int e_index;			/* index into edge list */
   vertexType *startv;		/* clipped start vertex */
   vertexType *endv;		/* clipped end vertex */
{
   clipcodeType sv_code;	/* start vertex's clipping code */
   clipcodeType ev_code;	/* end vertex's clipping code */
   clipcodeType outcode;	/* clip code for intersection point */

   int accept, done;		/* accept and done flags */
   double x, y;			/* temp coord values */
   double svx, svy;		/* start coord adjusted by which viewport */
   double evx, evy;		/* end coord adjusted by which viewport */

   double xmin, xmax, ymin, ymax;


   /* extract adjusted start and end based on which viewport */
   switch(viewport) {
      case XYVIEW:
         svx = vertex_list[edge_list[e_index].sv].x;
         svy = vertex_list[edge_list[e_index].sv].y;
         evx = vertex_list[edge_list[e_index].ev].x;
         evy = vertex_list[edge_list[e_index].ev].y;
         break;
      case ZYVIEW:
         svx = vertex_list[edge_list[e_index].sv].z;
         svy = vertex_list[edge_list[e_index].sv].y;
         evx = vertex_list[edge_list[e_index].ev].z;
         evy = vertex_list[edge_list[e_index].ev].y;
         break;
      case XZVIEW:
         svx = vertex_list[edge_list[e_index].sv].x;
         svy = vertex_list[edge_list[e_index].sv].z;
         evx = vertex_list[edge_list[e_index].ev].x;
         evy = vertex_list[edge_list[e_index].ev].z;
         break;
      default:
         fprintf(stderr, "ClipEdge: unknown viewport specified!\n");
         exit(1);
         break;
   }

   /* extract clip rectangle bounds from view file data */
   xmin = view_data[viewport].wxmin;
   xmax = view_data[viewport].wxmax;
   ymin = view_data[viewport].wymin;
   ymax = view_data[viewport].wymax;


   /* init flags and compute clipping codes */
   accept = 0;			/* set accept flag to FALSE */
   done = 0;			/* set done flag to FALSE */
   
   sv_code = GenClipCode(viewport, svx, svy);
   ev_code = GenClipCode(viewport, evx, evy);

   /* loop until done clipping */
   do {
      if (sv_code.all == 0 && ev_code.all == 0) {
         accept = 1;		/* trivial accept */
         done = 1;
      } 
      else {

         if ((sv_code.all & ev_code.all) != 0)
            done = 1;		/* trivial reject */

         else {			/* subdivide the line */

            /* init clip code for intersection */
            if (sv_code.all != 0)
               outcode = sv_code;
            else
               outcode = ev_code;

            /* determine where to divide line */
            if (outcode.top) {			/* divide line at top */
               x = svx + (evx - svx) * (ymax - svy) / (evy - svy);
               y = ymax;

            } else if (outcode.bottom) {	/* divide line at bottom */
               x = svx + (evx - svx) * (ymin - svy) / (evy - svy);
               y = ymin;

            } else if (outcode.right) {		/* divide line at right */
               y = svy + (evy - svy) * (xmax - svx) / (evx - svx);
               x = xmax;

            } else if (outcode.left) {		/* divide line at left */
               y = svy + (evy - svy) * (xmin - svx) / (evx - svx);
               x = xmin;
            }

            /* set new vertex and recompute clip code */
            if (outcode.all == sv_code.all) {	/* we clipped start */
               svx = x;
               svy = y;
               sv_code = GenClipCode(viewport, svx, svy);
            }
            else {				/* we clipped end */
               evx = x;
               evy = y;
               ev_code = GenClipCode(viewport, evx, evy);
            }
         }
      }
   } while (!done);	/* while not done clipping */


   if (accept) {
      startv->x = svx;	/* clipped start vertex */
      startv->y = svy;
      startv->z = 1.0;

      endv->x = evx;	/* clipped end vertex */
      endv->y = evy;
      endv->z = 1.0;
   }

   return(accept);
} /* end of ClipEdge() */


/******************************************************************

  NoClipEdge() -- This function performs no clipping.  It merely 
		returns the indicated start and end vertices.

		NOTE:  used only for debug purposes!!

******************************************************************/
int
NoClipEdge(viewport, e_index, startv, endv)
   viewportType viewport;	/* which viewport for clip boundary */
   int e_index;			/* index into edge list */
   vertexType *startv;		/* clipped start vertex */
   vertexType *endv;		/* clipped end vertex */
{

   /* temporarily return unclipped vertices */
   switch(viewport) {
      case XYVIEW:
         startv->x = vertex_list[edge_list[e_index].sv].x;
         startv->y = vertex_list[edge_list[e_index].sv].y;
         startv->z = 1.0;
         endv->x = vertex_list[edge_list[e_index].ev].x;
         endv->y = vertex_list[edge_list[e_index].ev].y;
         endv->z = 1.0;
         break;
      case ZYVIEW:
         startv->x = vertex_list[edge_list[e_index].sv].z;
         startv->y = vertex_list[edge_list[e_index].sv].y;
         startv->z = 1.0;
         endv->x = vertex_list[edge_list[e_index].ev].z;
         endv->y = vertex_list[edge_list[e_index].ev].y;
         endv->z = 1.0;
         break;
      case XZVIEW:
         startv->x = vertex_list[edge_list[e_index].sv].x;
         startv->y = vertex_list[edge_list[e_index].sv].z;
         startv->z = 1.0;
         endv->x = vertex_list[edge_list[e_index].ev].x;
         endv->y = vertex_list[edge_list[e_index].ev].z;
         endv->z = 1.0;
         break;
      default:
         fprintf(stderr, "NoClipEdge: unknown viewport specified!\n");
         exit(1);
         break;
   }

   return(1);	/* always accept */
} /* end of NoClipEdge() */


/***  all routines below here are for 3D viewing ***/


/******************************************************************

  Gen3DClipCode() -- This function generates the 3D Cohen-Sutherland 
		clipping code for determining whether a vertex is 
		within the clipping view volume.

		Bit 5 - in front view volume 	z < 0
		Bit 4 - behind view volume	z > 1
		Bit 3 - right of view volume 	x > 1
		Bit 2 - left of view volume	x < -1
		Bit 1 - above view volume	y > 1 
		Bit 0 - below view volume	y < -1 

******************************************************************/
clip3DcodeType
Gen3DClipCode(x, y, z)
   double x, y, z;		/* x, y and z coords of vertex */
{
   clip3DcodeType code;		/* clipping code for this vertex */

   /* initialize the clip code */
   code.infront = 0;
   code.behind = 0;
   code.right = 0;
   code.left = 0;
   code.above = 0;
   code.below = 0;
   code.all = 0;

   /* check against infront and behind view volume */
   if (z < 0) {
      code.infront = 32;
      code.all += code.infront;
   } else if (z > 1) {
      code.behind = 16;
      code.all += code.behind;
   }

   /* check against right and left of view volume */
   if (x > 1) {
      code.right = 8;
      code.all += code.right;
   } else if (x < -1) {
      code.left = 4;
      code.all += code.left;
   }

   /* check against above and below view volume */
   if (y > 1) {
      code.above = 2;
      code.all += code.above;
   } else if (y < -1) {
      code.below = 1;
      code.all += code.below;
   }

   return(code);
} /* end of Gen3DClipCode() */


/******************************************************************

  Clip3DEdge() -- This function clips the specified edge against the 
		canonical view volume, and returns the 
		clipped edge's start vertex and end vertex.  This 
		function does not create closed polygons if lines 
		are clipped.

		NOTE:
		    This function performs clipping via the 3D 
		  Cohen-Stutherland clipping algorithm similar to 
		  that described in section 3.9.3 of the text book.
		  Though it is not the highest performance technique,
		  it should serve the purpose.

******************************************************************/
int
Clip3DEdge(e_index, startv, endv)
   int e_index;			/* index into edge list */
   vertexType *startv;		/* clipped start vertex */
   vertexType *endv;		/* clipped end vertex */
{
   clip3DcodeType sv_code;	/* start vertex's clipping code */
   clip3DcodeType ev_code;	/* end vertex's clipping code */
   clip3DcodeType outcode;	/* clip code for intersection point */

   whichendType whichend;	/* current end of line being clipped */
   int accept, done;		/* accept and done flags */
   double x, y, z;		/* temp coord values */
   double svx, svy, svz;	/* start coord */
   double evx, evy, evz;	/* end coord */

   double t;			/* plane parameter */

   double xmin, xmax, ymin, ymax;


   /* extract the start and end vertices */
   svx = vertex_list[edge_list[e_index].sv].x;
   svy = vertex_list[edge_list[e_index].sv].y;
   svz = vertex_list[edge_list[e_index].sv].z;

   evx = vertex_list[edge_list[e_index].ev].x;
   evy = vertex_list[edge_list[e_index].ev].y;
   evz = vertex_list[edge_list[e_index].ev].z;

   /* init flags and compute clipping codes */
   accept = 0;			/* set accept flag to FALSE */
   done = 0;			/* set done flag to FALSE */
   
   sv_code = Gen3DClipCode(svx, svy, svz);
   ev_code = Gen3DClipCode(evx, evy, evz);

   whichend = NEITHER;		/* init to neither end being clipped */

   /* loop until done clipping */
   do {
      if (sv_code.all == 0 && ev_code.all == 0) {
         accept = 1;		/* trivial accept */
         done = 1;
      } 
      else {

         if ((sv_code.all & ev_code.all) != 0)
            done = 1;		/* trivial reject */

         else {			/* subdivide the line */

            /* init clip code for intersection */
            if (sv_code.all != 0) {
               outcode = sv_code;
               whichend = CLIP_START;
            }
            else {
               outcode = ev_code;
               if (whichend == CLIP_START)
                  whichend = CLIP_BOTH;
               else
                  whichend = CLIP_END;
            }

            /* determine where to divide line */
            if (outcode.infront) {	/* divide line at infront */
               t = -svz / (evz - svz);
               x = svx + t * (evx - svx);
               y = svy + t * (evy - svy);
               z = 0;

            } else if (outcode.behind) { /* divide line at below */
               t = (1 - svz) / (evz - svz);
               x = svx + t * (evx - svx);
               y = svy + t * (evy - svy);
               z = 1;

            } else if (outcode.right) {	/* divide line at right */
               t = (1 - svx) / (evx - svx);
               x = 1;
               y = svy + t * (evy - svy);
               z = svz + t * (evz - svz);

            } else if (outcode.left) {	/* divide line at left */
               t = (-1 - svx) / (evx - svx);
               x = -1;
               y = svy + t * (evy - svy);
               z = svz + t * (evz - svz);

            } else if (outcode.above) {	/* divide line at above */
               t = (1 - svy) / (evy - svy);
               x = svx + t * (evx - svx);
               y = 1;
               z = svz + t * (evz - svz);

            } else if (outcode.below) {	/* divide line at below */
               t = (1 - svy) / (evy - svy);
               x = svx + t * (evx - svx);
               y = 1;
               z = svz + t * (evz - svz);
            }

            /* set new vertex and recompute clip code */
            if (outcode.all == sv_code.all) {	/* we clipped start */
               svx = x;
               svy = y;
               svz = z;
               sv_code = Gen3DClipCode(svx, svy, svz);
            }
            else {				/* we clipped end */
               evx = x;
               evy = y;
               evz = z;
               ev_code = Gen3DClipCode(evx, evy, evz);
            }
         }
      }
   } while (!done);	/* while not done clipping */


   if (accept) {
      switch(whichend) {
         case NEITHER:		/* use original vertices */
            startv->x = svx;
            startv->y = svy;
            startv->z = svz;
            endv->x = svx;
            endv->y = svy;
            endv->z = svz;
            break;

         case CLIP_START:	/* replace start vertex of this line */
            edge_list[e_index].sv = vertex_count;
            vertex_list[vertex_count].x = svx;
            vertex_list[vertex_count].y = svy;
            vertex_list[vertex_count].z = svz;
            vertex_count++;
            break;

         case CLIP_END:		/* replace end vertex of this line */
            edge_list[e_index].ev = vertex_count;
            vertex_list[vertex_count].x = evx;
            vertex_list[vertex_count].y = evy;
            vertex_list[vertex_count].z = evz;
            vertex_count++;
            break;

         case CLIP_BOTH:	/* replace both vertices of this line */
            edge_list[e_index].sv = vertex_count;
            vertex_list[vertex_count].x = svx;
            vertex_list[vertex_count].y = svy;
            vertex_list[vertex_count].z = svz;
            vertex_count++;

            edge_list[e_index].ev = vertex_count;
            vertex_list[vertex_count].x = evx;
            vertex_list[vertex_count].y = evy;
            vertex_list[vertex_count].z = evz;
            vertex_count++;
            break;

         default:
            fprintf(stderr, "Clip3DEdge: unknown end being clipped\n");
            exit(1);
      }
   }

   edge_list[e_index].accept = accept;

   return(accept);
} /* end of Clip3DEdge() */


/******************************************************************

  NoClip3DEdge() -- This function performs no clipping.  It merely 
		returns the indicated start and end vertices.

******************************************************************/
int
NoClip3DEdge(e_index, startv, endv)
   int e_index;			/* index into edge list */
   vertexType *startv;		/* clipped start vertex */
   vertexType *endv;		/* clipped end vertex */
{

   startv->x = vertex_list[edge_list[e_index].sv].x;
   startv->y = vertex_list[edge_list[e_index].sv].y;
   startv->z = 1.0;
   endv->x = vertex_list[edge_list[e_index].ev].x;
   endv->y = vertex_list[edge_list[e_index].ev].y;
   endv->z = 1.0;

   return(edge_list[e_index].accept);	/* return accept flag */
} /* end of NoClip3DEdge() */


/* end of file clipping.c */
