/* 

   A collection of routines used by Render.c to perform hidden 
   surface removal and surface shading.  Please note that currently
   only constant shading (in color) is supported.

   File:   shading.c

   Author: Brian Lingard

   Rev history:   
	0 - 12/4/94  originated

   NOTE:

	The functions in this file expect certain global constants
	to have been defined.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "render.h"
#include "shading.h"


#define DEBUG 1


/* external globals */
extern int vertex_count;
extern int edge_count;
extern int polygon_count;

extern vertexType vertex_list[];
extern edgeType edge_list[];
extern polygonType polygon_list[];

extern renderType render_mode;
extern projectType projection_mode;
extern normalizeType norm_flag;

extern viewrangeType view_data[];	/* used for three simul. views */
extern viewdataType view;		/* used for para & pers views */
extern viewplaneType vplane;		/* view plane information */

extern FILE *debugfile;


/* local global variables for shading functions */
static colorType colortable[MAX_NUM_COLORS];	/* device independant */

static RGBType mycolors[MAX_TABLE_SIZE];	/* my local color table */

static int color_index = 16;	/* color LUT index -- skip first 16 entries */


/******************************************************************

  InitColorTable() -- This function initializes the default device 
			independant global color table.  These colors
			represent the base color of a polygon.

******************************************************************/
int
InitColorTable()
{
   colortable[WHITE].IR = 1.0;	/* white */
   colortable[WHITE].IG = 1.0;
   colortable[WHITE].IB = 1.0;

   colortable[BLACK].IR = 0.0;	/* black */
   colortable[BLACK].IG = 0.0;
   colortable[BLACK].IB = 0.0;

   colortable[GREY].IR = 0.75;	/* grey */
   colortable[GREY].IG = 0.75;
   colortable[GREY].IB = 0.75;

   colortable[RED].IR = 1.0;	/* red */
   colortable[RED].IG = 0.0;
   colortable[RED].IB = 0.0;

   colortable[GREEN].IR = 0.0;	/* green */
   colortable[GREEN].IG = 1.0;
   colortable[GREEN].IB = 0.0;

   colortable[BLUE].IR = 0.0;	/* blue */
   colortable[BLUE].IG = 0.25;
   colortable[BLUE].IB = 1.0;

   colortable[YELLOW].IR = 1.0;	/* yellow */
   colortable[YELLOW].IG = 1.0;
   colortable[YELLOW].IB = 0.0;

   colortable[CYAN].IR = 0.0;	/* cyan */
   colortable[CYAN].IG = 1.0;
   colortable[CYAN].IB = 1.0;

   colortable[MAGENTA].IR = 1.0;	/* magenta */
   colortable[MAGENTA].IG = 0.0;
   colortable[MAGENTA].IB = 1.0;

   return(0);
} /* end of InitColorTable() */


/******************************************************************

  PickGreyLevel() -- This function picks a grey level from 0 to
		MAX_GREY_LEVELS given an intensity from 0 to 1.

******************************************************************/
ush
PickGreyLevel(intensity)
   float intensity;
{
   ush grey;

   grey = (ush) (MAX_GREY_LEVELS * intensity);

   return(grey);
} /* end of PickGreyLevel() */


/******************************************************************

  SearchColorTable() -- searches my local color table for closest color

******************************************************************/
int
SearchColorTable(color)
   RGBType color;
{
   int c, index = -1;
   int dc = COLOR_MARGIN;		/* delta color -- margin */

   for (c = 0; c < color_index; c++) {

      if ( ((mycolors[c].R - dc) < color.R) && (color.R < (mycolors[c].R + dc))
	&& ((mycolors[c].G - dc) < color.G) && (color.G < (mycolors[c].G + dc))
        && ((mycolors[c].B - dc) < color.B) && (color.B < (mycolors[c].B + dc)) )
	  index = c;
   }

   return(index);
} /* end of SearchColorTable() */


/******************************************************************

  SetNewColor() -- This function adds a new entry to the SRGP color
		table only if a good match for an existing color
		cannot be found.  
	
******************************************************************/
int
SetNewColor(color)
   RGBType color;
{
   int index;

   int AddNewColor();
   int SetDrawColor();


   /* search color table for closest match, index < 0 when no match */
   index = SearchColorTable(color);

   /* add new entry to color table if no match found */
   if (index < 0) {
      index = color_index;
      mycolors[color_index].R = color.R;	/* save to local color table */
      mycolors[color_index].G = color.G;
      mycolors[color_index].B = color.B;

      AddNewColor(color_index, color);		/* add to device color table */

      color_index++;
      if (color_index > MAX_TABLE_SIZE) {
         fprintf(stderr, "ERROR - exceeded color table size\n");
         exit(1);
      }
      else
         fprintf(debugfile, "new color entry at %d\n", color_index - 1);
   }

   /* set to new drawing color */
   SetDrawColor(index);

   return(0);
} /* end of SetNewColor() */


/******************************************************************

  ComputeLightVector() -- This function computes the vector L from
			a point on a surface to the light source.

******************************************************************/
matrixType
*ComputeLightVector(polypoint)
   vertexType polypoint;
{
   matrixType *lightvec;
   double mag;

   matrixType *MakeVector();
   double GetVecMag();


   /* create light source vector -- points toward light source */
   lightvec = MakeVector(polypoint, view.lightloc);

   /* compute magnitude of light source vector */
   mag = GetVecMag(*lightvec);
   if (mag == 0.0) {
      fprintf(stderr, "ComputeLightVector: lightvec magnitude is zero\n");
      exit(1);
   }

   /* normalize the light source vector */
   lightvec->array[0][0] = lightvec->array[0][0] / mag;
   lightvec->array[1][0] = lightvec->array[1][0] / mag;
   lightvec->array[2][0] = lightvec->array[2][0] / mag;

   return(lightvec);
} /* end of ComputeLightVector() */


/******************************************************************

  ComputeIntensity() -- This function computes the intensity of the
			diffuse reflection given a surface normal N
			and the vector L using:


	I = Iamb * Kamb * Olamb + Ipoint * Kdiff * Olamb (N dot L)


	assumes	monochromatic light but possibly colored objects
	if want grey scales, set Olambda to 1.0

******************************************************************/
float
ComputeIntensity(p_index, L, Olambda)
   int p_index;		/* index into polygon list */
   matrixType *L;	/* light vector L */
   float Olambda;	/* object's diffuse color */
{
   matrixType normal;
   float intensity;
   double dot;

   double DotProduct();


   /* convert polygon's normal into vector */
   CopyVertToMat(&polygon_list[p_index].normal, &normal);

   /* compute N dot L */
   dot = DotProduct(normal, *L);
/*   if (dot < 0.0) 
      dot = dot * -1.0;*/

   /* intensity of diffuse reflection */
   intensity = (Iamb * Kamb + Ipoint * Kdiff * dot) * Olambda;
   
   /* if exceeds max intensity, clamp it to max */
   if (intensity > 1.0)
      intensity = 1.0;

   return(intensity);
} /* end of ComputeIntensity() */


/******************************************************************

  ComputeColor() -- This function computes the current drawing color
			based upon the polygon's orientation.

******************************************************************/
int
ComputeColor(p_index, color)
   int p_index;
   RGBType *color;		/* actual color */
{
   float Olambda;		/* wavelength dependant intensity */
   float intensity;		/* total color component intensity */
   vertexType polypt;		/* point on polygon */
   matrixType *L;		/* light source vector */


   /* extract a point on polygon */
   polypt.x = vertex_list[polygon_list[p_index].vert_list[0]].x;
   polypt.y = vertex_list[polygon_list[p_index].vert_list[0]].y;
   polypt.z = vertex_list[polygon_list[p_index].vert_list[0]].z;

   L = ComputeLightVector(polypt);

   if (USECOLOR) {	/* use color calculations */

      /* compute red component */
      Olambda = colortable[polygon_list[p_index].color].IR;
      intensity = ComputeIntensity(p_index, L, Olambda);
      color->R = PickGreyLevel(intensity);

      /* compute green component */
      Olambda = colortable[polygon_list[p_index].color].IG;
      intensity = ComputeIntensity(p_index, L, Olambda);
      color->G = PickGreyLevel(intensity);

      /* compute blue component */
      Olambda = colortable[polygon_list[p_index].color].IB;
      intensity = ComputeIntensity(p_index, L, Olambda);
      color->B = PickGreyLevel(intensity);

   }
   else {	/* use grey scales */

      intensity = ComputeIntensity(p_index, L, 1.0);

      /* set all components to same intensity for grey scale */
      color->R = PickGreyLevel(intensity);
      color->G = color->R;
      color->B = color->R;
   }

   return(0);
} /* end of ComputeColor() */


/******************************************************************

  CopyVertToMat() -- This function copies something of vertexType 
			to matrixType.

******************************************************************/
int
CopyVertToMat(vert, matrix)
   vertexType *vert;
   matrixType *matrix;
{
   matrix->rows = 3;
   matrix->cols = 1;
   matrix->array[0][0] = vert->x;
   matrix->array[1][0] = vert->y;
   matrix->array[2][0] = vert->z;

   return(0);
} /* end of CopyVertToMat() */


/******************************************************************

  ComputeNormal() - This function computes the normal vector of the
			specified polygon.  This functions uses the
			first two edges of the specified polygon.

			P1       P3
			 \      /
			  \    /
			   \  /
			    P2		P2 is start of each vector

			vector P2P3 crossed with vector P2P1

			i.e.  N = (P3 - P2) X (P1 - P2)

******************************************************************/
int 
ComputeNormal(p_index)
   int p_index;
{
   vertexType p1, p2, p3;
   matrixType *vec1, *vec2, *normal;
   double mag;

   matrixType *MakeVector();
   matrixType * MakeIdentityMatrix();
   int CrossProduct();
   double GetVecMag();
   int FreeMatrix();


   /* extract needed points from polygon */
   p1 = vertex_list[polygon_list[p_index].vert_list[0]];
   p2 = vertex_list[polygon_list[p_index].vert_list[1]];
   p3 = vertex_list[polygon_list[p_index].vert_list[2]];

   /* turn points into two vectors */
   vec1 = MakeVector(p2, p3);
   vec2 = MakeVector(p2, p1);
   normal = MakeIdentityMatrix();

   /* compute cross product of these vectors */
   CrossProduct(vec2, vec1, normal);

   /* compute magnitude of the normal vector */
   mag = GetVecMag(*normal);
   if (mag == 0.0) {
      fprintf(stderr, "ComputeNormal: normal magnitude is zero\n");
      exit(1);
   }
         
   /* copy a normalized normal to this polygon */
   polygon_list[p_index].normal.x = normal->array[0][0] / mag;
   polygon_list[p_index].normal.y = normal->array[1][0] / mag;
   polygon_list[p_index].normal.z = normal->array[2][0] / mag;

   FreeMatrix(vec1);
   FreeMatrix(vec2);
   FreeMatrix(normal);
   return(0);
} /* end of ComputeNormal() */


/******************************************************************

  RecomputeNormal() -- This function recomputes a polygon's 
			surface normal.

******************************************************************/
int
RecomputeNormal(p, normal)
   int p;
   matrixType *normal;
{

   ComputeNormal(p);

   CopyVertToMat(&polygon_list[p].normal, normal);

   return(0);
} /* end of RecomputeNormal() */


/******************************************************************

  PerformBackFaceCulling() -- This function performs a simple check
			of the dot product between the surface normal
			and the direction of projection to determine
			if the surface is visible.  This check is
			performed for all polygons in the global list.
			Note that surface normals must be recomputed 
			if the projection mode is perspective.

******************************************************************/
int
PerformBackFaceCulling()
{
   int p;			/* loop index */
   double dot;			/* current dot product */

   matrixType DOP;		/* direction of projection vector */
   matrixType normal;		/* current polygon normal vector */

   double DotProduct();

   
   /* set direction of projection to positive z-axis */
   DOP.rows = 3;
   DOP.cols = 1;
   DOP.array[0][0] = 0.0;
   DOP.array[1][0] = 0.0;
   DOP.array[2][0] = 1.0;

   /* for all the polygons in list */
   for (p = 0; p < polygon_count; p++) {
      if (projection_mode == PERSPECTIVE) {
         RecomputeNormal(p, &normal);
      }
      else	/* use original surface normals */
         CopyVertToMat(&polygon_list[p].normal, &normal);

      dot = DotProduct(DOP, normal);	/* compute dot product */

      if (dot > 0.0)	/* surface is not visible */
         polygon_list[p].visible = NOT_VISIBLE;
      
      else		/* surface is visible */
         polygon_list[p].visible = VISIBLE;
   }

   return(0);
} /* end of PerformBackFaceCulling() */


/* end of file shading.c */
