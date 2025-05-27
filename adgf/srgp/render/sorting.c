/* 

   A collection of routines used by Render.c to perform depth sorting
   of polygons.  The depth sort must be performed while 'z' coordinate
   information still exists (i.e. before perspective transformation).
   The best time to sort appears to be right after converting to view
   coordinates.

   File:   sorting.c

   Author: Brian Lingard

   Rev history:   
	0 - 12/12/94  originated

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "render.h"

/* #define DEBUG 1
*/

/* external global variables */
extern int vertex_count;
extern int polygon_count;

extern vertexType vertex_list[];
extern polygonType polygon_list[];

extern viewplaneType vplane;

/* global only to be used within this header */
static polygonType newpolylist[MAX_POLYS];


/******************************************************************

  InitSortedFlag() -- Initialize flag to not sorted.

******************************************************************/
int
InitSortedFlag()
{
   int p;

   for (p = 0; p < polygon_count; p++) 
      polygon_list[p].sorted = 0;	/* set flag to not sorted */

   return(0);
} /* end of InitSortedFlag() */


/******************************************************************

  PickMaxZ() -- This function determines the max z coordinate from 
		all the polygon's vertices.

******************************************************************/
float
PickMaxZ(p)
   int p;
{
   float zvalue, maxz;
   int v;

   for (v = 0; v < SIZE_OF_POLY; v++) {

      zvalue = vertex_list[polygon_list[p].vert_list[v]].z;

      if (v == 0)
         maxz = zvalue;

      else
         if (zvalue > maxz)	/* new max z? */
            maxz = zvalue;
   }

   return(maxz);
} /* end of PickMaxZ() */


/******************************************************************

  FindFarthestPoly() -- This function determines which polygon remaining
			in the global list is the farthest from the 
			viewer and returns its index.

******************************************************************/
int
FindFarthestPoly()
{
   int p, index;	/* loop index, farthest index */
   float max_z;		/* z value of farthest poly */
   float zvalue;	/* current poly's max z */

   /* init max z to closest to viewer */
   max_z = -vplane.vpd;

   /* loop through entire polygon list */
   for (p = 0; p < polygon_count; p++) {
      
      if (polygon_list[p].sorted == 0) {   /* check if not sorted yet */
         zvalue = PickMaxZ(p);		   /* get this poly's max z */

         if (zvalue > max_z) {		   /* greater than curr max z */
            max_z = zvalue;
            index = p;
         }
      }

   } /* end for loop */

   polygon_list[index].sorted = 1;	/* set flag to has been sorted */

   return(index);	/* return index of farthest polygon */
} /* end of FindFarthestPoly() */


/******************************************************************

  CopyToNewlist() -- This function copies a polygon from the original 					polygon list to the sorted new list of polygons.

******************************************************************/
int
CopyToNewlist(orig, new)
   int orig;		/* original poly index */
   int new;		/* new list poly index */
{
   int e, v;		/* loop index */

   newpolylist[new].num_edges = polygon_list[orig].num_edges;
   for (e = 0; e < SIZE_OF_POLY; e++)
      newpolylist[new].edge_list[e] = polygon_list[orig].edge_list[e];
   for (v = 0; v < SIZE_OF_POLY; v++)
      newpolylist[new].vert_list[v] = polygon_list[orig].vert_list[v];
   newpolylist[new].color = polygon_list[orig].color;
   newpolylist[new].normal.x = polygon_list[orig].normal.x;
   newpolylist[new].normal.y = polygon_list[orig].normal.y;
   newpolylist[new].normal.z = polygon_list[orig].normal.z;
   newpolylist[new].visible = polygon_list[orig].sorted;
   newpolylist[new].sorted = polygon_list[orig].sorted;

   return(0);
} /* end of CopyToNewlist() */


/******************************************************************

  CopyNewToOriginal() -- This function copies the sorted polygon
			list back into the original polygon list.

******************************************************************/
int
CopyNewToOriginal()
{
   int p, i;		/* loop index */

   for (p = 0; p < polygon_count; p++) {

      polygon_list[p].num_edges = newpolylist[p].num_edges;
      for (i = 0; i < SIZE_OF_POLY; i++)
         polygon_list[p].edge_list[i] = newpolylist[p].edge_list[i];
      for (i = 0; i < SIZE_OF_POLY; i++)
         polygon_list[p].vert_list[i] = newpolylist[p].vert_list[i];
      polygon_list[p].color = newpolylist[p].color;
      polygon_list[p].normal.x = newpolylist[p].normal.x;
      polygon_list[p].normal.y = newpolylist[p].normal.y;
      polygon_list[p].normal.z = newpolylist[p].normal.z;
      polygon_list[p].visible = newpolylist[p].visible;
      polygon_list[p].sorted = newpolylist[p].sorted;

   }

   return(0);
} /* end of CopyNewToOriginal() */


/******************************************************************

  PerformDepthSort() -- This function performs a depth sort of the 
			polygons within the global list "polygon_list".
			The final order of the polygons within the 
			global list is from farthest to nearest.

	NOTE: this is rough depth sort, overlapping polygons might still
		have problems depending upon viewing angle.

******************************************************************/
int
PerformDepthSort()
{
   int done_sorting;		/* done sorting flag */
   int current_far;		/* current farthest polygon */
   int newlist_index;		/* current position in new polygon list */

   /* allocate memory for new polygon list */
   /* NOT REALLY DONE YET */

   /* loop until done performing sort */
   newlist_index = 0;
   done_sorting = 0;

#ifdef DEBUG
   printf("... performing depth sort\n");
#endif

   InitSortedFlag();	/* set all poly's flags to not sorted */

   while (!done_sorting) {

      current_far = FindFarthestPoly();

      CopyToNewlist(current_far, newlist_index);

      newlist_index++;

      if (newlist_index >= polygon_count)
         done_sorting = 1;
   }

   /* copy sorted list back into original list */
   CopyNewToOriginal();

   return(0);
} /* end of PerformDepthSort() */


/******************************************************************

  OutputPolyList() -- This function outputs the polygon list to device.

******************************************************************/
int
OutputPolyList(device, label)
   FILE *device;
   char *label;
{
   int p, i;

   fprintf(device, "%s:\n", label);

   for (p = 0; p < polygon_count; p++) {

      fprintf(device, "%d\n", polygon_list[p].num_edges);
      for (i = 0; i < SIZE_OF_POLY; i++)
         fprintf(device, "%d ", polygon_list[p].edge_list[i]);
      fprintf(device, "\n");
      for (i = 0; i < SIZE_OF_POLY; i++)
         fprintf(device, "%d ", polygon_list[p].vert_list[i]);
      fprintf(device, "\n");
      fprintf(device, "%d\n", polygon_list[p].color);
      fprintf(device, "%f %f %f\n", polygon_list[p].normal.x, polygon_list[p].normal.y, polygon_list[p].normal.z);
      fprintf(device, "%d\n", polygon_list[p].visible);
      fprintf(device, "%d\n\n", polygon_list[p].sorted);

   }

   return(0);
} /* end of OutputPolyList() */


/* end of file sorting.c */
