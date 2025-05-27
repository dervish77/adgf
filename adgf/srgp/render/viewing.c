/* 

   Misc utility functions for view related operations.

   File:   viewing.c

   Author: Brian Lingard

   Rev history: 
	1 - 11/12/94  modified for use on phase3  
	0 - 10/11/94  originated

*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "render.h"

#define DEBUG 1


/* external globals */
extern int edge_count;

extern viewrangeType view_data[];	/* used for three simul. views */
extern viewdataType view;		/* used for para & pers views */
extern viewplaneType vplane;		/* view plane information */

extern FILE *debugfile;

/* local static globals */
static vertexType lefteyeloc;
static vertexType righteyeloc;


/******************************************************************

  MakeMappingXform() -- This function generates the transform matrix 
			for mapping a world coordinate point into a
			viewport point.


		The transform matrix generated has the form:

			|  a    0    b  |
			|               |
			|  0    c    d  |
			|               |
			|  0    0    1  |

		where:

		  a = (umax - umin) / (xmax - xmin)

		  b = ((-xmin) * (umax - umin) / (xmax - xmin)) + umin

		  c = (vmax - vmin) / (ymax - ymin)

		  d = ((-ymin) * (vmax - vmin) / (ymax - ymin)) + vmin


		NOTE:
		  coordinates u,v are viewport related
		  coordinates x,y are world related

******************************************************************/
matrixType
*MakeMappingXform(viewport)
   viewportType viewport;
{
   matrixType *xform;
   double xmin, xmax, ymin, ymax;	/* world boundaries */
   double umin, umax, vmin, vmax;	/* screen boundaries */
   double a, b, c, d;			/* matrix terms */

   double offset = 10.0;		/* safety border */

   matrixType *MakeIdentityMatrix();


   /* allocate memory for transform matrix */
   xform = MakeIdentityMatrix();

   /* resize to a 3x3 matrix */
   xform->rows = 3;
   xform->cols = 3;

   /* extract this view's world boundaries */
   switch(viewport) {
      case XYVIEW:
      case ZYVIEW:
      case XZVIEW:
         xmin = view_data[viewport].wxmin;
         ymin = view_data[viewport].wymin;
         xmax = view_data[viewport].wxmax;
         ymax = view_data[viewport].wymax;
         break;
      case CAMERA:
         xmin = vplane.umin;
         ymin = vplane.vmin;
         xmax = vplane.umax;
         ymax = vplane.vmax;
         break;
      default:
         break;
   }

   /* calculate this view's screen boundaries */
   switch(viewport) {
      case XYVIEW:
         umin = 0.0 + offset;
         vmin = (SCREEN_HEIGHT / 2) + offset;
         umax = (SCREEN_WIDTH / 2) - offset;
         vmax = SCREEN_HEIGHT - offset;
         break;

      case ZYVIEW:
         umin = (SCREEN_WIDTH / 2) + offset;
         vmin = (SCREEN_HEIGHT / 2) + offset;
         umax = SCREEN_WIDTH - offset;
         vmax = SCREEN_HEIGHT - offset;
         break;

      case XZVIEW:
         umin = 0.0 + offset;
         vmin = 0.0 + offset;
         umax = (SCREEN_WIDTH / 2) - offset;
         vmax = (SCREEN_HEIGHT / 2) - offset;
         break;

      case CAMERA:
         umin =  view.vpx.min + offset;
         vmin =  view.vpy.min + offset;
         umax =  view.vpx.max - offset;
         vmax =  view.vpy.max - offset;
         break;

      default:
         break;
   }

   /* calculate matrix terms */
   a = (umax - umin) / (xmax - xmin);

   c = (vmax - vmin) / (ymax - ymin);

   b = ((-1) * xmin * a) + umin;

   d = ((-1) * ymin * c) + vmin;


   /* plug matrix terms into transform matrix */
   xform->array[0][0] = a;
   xform->array[0][2] = b;
   xform->array[1][1] = c;
   xform->array[1][2] = d;


   return(xform);
} /* end of MakeMappingXform() */


/******************************************************************

  ComputeEyeView() -- computes left/right eye view points

******************************************************************/
int
ComputeEyeView()
{
   float X, Z, xp, zp, e, d;

   d = 27.0;
   e = 0.028 * d;

   X = view.lap.x - view.eyeloc.x;
   Z = view.lap.z - view.eyeloc.z;

   if (X < 0) X = X * (-1);
   if (Z < 0) Z = Z * (-1);

   xp = Z * (e / 2) / d;
   zp = X * (e / 2) / d;

   lefteyeloc.x = view.eyeloc.x - xp;
   lefteyeloc.z = view.eyeloc.z + zp;

   righteyeloc.x = view.eyeloc.x + xp;
   righteyeloc.z = view.eyeloc.z - zp;

   return(0);
} /* end of ComputeEyeView() */


/******************************************************************

  SetEyeView() -- adjusts the view point for left/right eye views

******************************************************************/

int
SetEyeView(eye)
   int eye;
{ 
   switch(eye) {
      case LEFT:
         view.eyeloc.x = lefteyeloc.x;
         view.eyeloc.z = lefteyeloc.z;
         break;
      case RIGHT:
         view.eyeloc.x = righteyeloc.x;
         view.eyeloc.z = righteyeloc.z;
         break;
      default:
         fprintf(stderr,"ERROR - unknown eye specified\n");
         exit(1);
   }

   return(0);
} /* end of SetEyeView() */


/******************************************************************

  Draw_View() -- This function draws all lines seen on specified 
		viewport.  The function loops through the edge list
		and clips each edge against the specified viewport's
		clip rectangle.  The clipped line is then drawn on the 
		screen.

******************************************************************/
int
Draw_View(viewport)
   viewportType viewport;
{
   int e;			/* loop index */
   vertexType sv, ev;		/* start vertex and end vertex */
   matrixType *map_xform;	/* world to view mapping transform */

   int accept_flag;		/* zero indicates trivial reject */   

   matrixType *MakeMappingXform();
   int ClipEdge();
   int DrawWorldLine();


   if (DEBUG) printf("drawing view #%d\n", viewport);

   /* generate mapping transform for this view */
   map_xform = MakeMappingXform(viewport);

   /* loop through the edge list */
   for (e = 0; e < edge_count; e++) {
      accept_flag = ClipEdge(viewport, e, &sv, &ev);	/* clip this edge */

      if (accept_flag)
         DrawWorldLine(sv, ev, map_xform);		/* draw this edge */
   }

   return(0);
} /* end of Draw_View() */


/******************************************************************

  OutputViewplaneInfo() -- This function outputs the view plane info
			structure to the debug file.

******************************************************************/
int
OutputViewplaneInfo()
{
   int OutputMatrix();


   fprintf(debugfile, "VRP = %f %f %f\n", vplane.VRP.x, vplane.VRP.y, vplane.VRP.z);
   fprintf(debugfile, "PRP = %f %f %f\n", vplane.PRP.x, vplane.PRP.y, vplane.PRP.z);
   fprintf(debugfile, "CW  = %f %f %f\n\n", vplane.CW.x, vplane.CW.y, vplane.CW.z);

   fprintf(debugfile, "umin, umax = %f, %f\n", vplane.umin, vplane.umax);
   fprintf(debugfile, "vmin, vmax = %f, %f\n", vplane.vmin, vplane.vmax);
   fprintf(debugfile, "F, B = %f, %f\n", vplane.F, vplane.B);
   fprintf(debugfile, "vpd = %f\n", vplane.vpd);

   OutputMatrix(debugfile, &vplane.Uvector, "Uvector");
   OutputMatrix(debugfile, &vplane.Vvector, "Vvector");
   OutputMatrix(debugfile, &vplane.Nvector, "Nvector");

   OutputMatrix(debugfile, &vplane.DOP, "DOP");
   OutputMatrix(debugfile, &vplane.VPN, "VPN");
   OutputMatrix(debugfile, &vplane.VUP, "VUP");
   OutputMatrix(debugfile, &vplane.M, "vplane M");

} /* end of OutputViewplaneInfo() */


/* end of file viewing.c */
