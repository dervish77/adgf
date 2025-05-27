/***********************************************************************

   File:  	translat.c

   Author: 	Brian Lingard

   Date:	9/16/95

  Database translation functions for 3D modeling program.  Converts
primitive types into lists of vertices and polygons.

  All coordinate manipulations assume a left-handed coordinate system
for both the world coord system and the view coord system.  Thus all
polygons are set up to have their vertices specified in clockwise 
order.

  Please note that a plane primitive will be visible on only one
surface.  Thus if the plane should be visible from both sides, you 
should create two planes rotated 180 degrees from each other.

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "modeler.h" */
#endif



#define TRANSLAT_DEBUG 1


#define DEFAULT_COORD	((float) 0.5)

#define MAX_CIRCLE_POINTS	20

#define NUM_PLANE_VERTS		4
#define NUM_CUBE_VERTS		8
#define NUM_CYLINDER_VERTS	((MAX_CIRCLE_POINTS * 2) + 2)
#define NUM_PYRAMID_VERTS	5
#define NUM_PRISM_VERTS		6
#define NUM_CONE_VERTS		(MAX_CIRCLE_POINTS + 2)
#define NUM_SPHERE_VERTS	((((MAX_CIRCLE_POINTS / 2) + 1) * 2) * MAX_CIRCLE_POINTS)

#define NUM_PLANE_POLYS		1
#define NUM_CUBE_POLYS		6
#define NUM_CYLINDER_POLYS	(MAX_CIRCLE_POINTS * 3)
#define NUM_PYRAMID_POLYS	5
#define NUM_PRISM_POLYS		5
#define NUM_CONE_POLYS		(MAX_CIRCLE_POINTS * 2)
#define NUM_SPHERE_POLYS	((MAX_CIRCLE_POINTS / 2) * MAX_CIRCLE_POINTS)

#define MAX_WEDGE_POINTS	(MAX_CIRCLE_POINTS * 2)
#define MAX_WEDGE_POLYS		(MAX_CIRCLE_POINTS * 2)


typedef struct {
   wpointType	unit_plane_vert[NUM_PLANE_VERTS];
   POLYGON_S_T	unit_plane_poly[NUM_PLANE_POLYS];
   wpointType	unit_cube_vert[NUM_CUBE_VERTS];
   POLYGON_S_T	unit_cube_poly[NUM_CUBE_POLYS];
   wpointType	unit_cylinder_vert[NUM_CYLINDER_VERTS];
   POLYGON_S_T	unit_cylinder_poly[NUM_CYLINDER_POLYS];
   wpointType	unit_pyramid_vert[NUM_PYRAMID_VERTS];
   POLYGON_S_T	unit_pyramid_poly[NUM_PYRAMID_POLYS];
   wpointType	unit_prism_vert[NUM_PRISM_VERTS];
   POLYGON_S_T	unit_prism_poly[NUM_PRISM_POLYS];
   wpointType	unit_cone_vert[NUM_CONE_VERTS];
   POLYGON_S_T	unit_cone_poly[NUM_CONE_POLYS];
   wpointType	unit_sphere_vert[NUM_SPHERE_VERTS];
   POLYGON_S_T	unit_sphere_poly[NUM_SPHERE_POLYS];
} UNIT_SHAPE_DATA_S_T;



/* define global data */
UNIT_SHAPE_DATA_S_T	unit_data;


/* static function declarations */
static void TranslatePlane(int idx, MyProgram *data);
static void TranslateCube(int idx, MyProgram *data);
static void TranslateCylinder(int idx, MyProgram *data);
static void TranslatePyramid(int idx, MyProgram *data);
static void TranslatePrism(int idx, MyProgram *data);
static void TranslateCone(int idx, MyProgram *data);
static void TranslateSphere(int idx, MyProgram *data);

static void MakeUnitCylinder(int sides);
static void MakeUnitCone(int sides);
static void MakeUnitSphere(int sides);

static void SetVertex(float x, float y, float z, wpointType *v);

static void CopyVertex(wpointType *src, wpointType *dst);
static void CopyPolygon(int sv_idx, POLYGON_S_T *src, POLYGON_S_T *dst);
static void XformVertex(int idx, MyProgram *data, matrixType *xform);
static void ComputeNormal(int idx, MyProgram *data);


/******************************************************************************
*  TranslateDatabase - translate primitives into vertices and polygons        *
******************************************************************************/
void
TranslateDatabase(MyProgram *data)
{
   int i;

   /* re-init vert and poly counts */
   data->data.current_vert_idx = 0;
   data->data.current_poly_idx = 0;
   data->data.vert_count = 0;
   data->data.poly_count = 0;

   /* translate all the valid primitives */
   for (i = 0; i < data->data.prim_count; i++)
   {
      if (data->data.prim_list[i].valid)
      {
         switch (data->data.prim_list[i].type)
         {
            case PLANE_PRIM:
               TranslatePlane(i, data);
               break;
            case CUBE_PRIM:
               TranslateCube(i, data);
               break;
            case CYLIN_PRIM:
               TranslateCylinder(i, data);
               break;
            case PYRA_PRIM:
               TranslatePyramid(i, data);
               break;
            case PRISM_PRIM:
               TranslatePrism(i, data);
               break;
            case CONE_PRIM:
               TranslateCone(i, data);
               break;
            case SPHERE_PRIM:
               TranslateSphere(i, data);
               break;
            default:
               break;
         }
      }
   }
}


/******************************************************************************
*  TranslatePlane - translate plane primitive                                 *
*                                                                             *
*  assume default plane                                                       *
*		lies in xy plane                                              *
*		center is at (0,0,0)                                          *
*		top right at (0.5,0.5,0), bottom left at (-0.5,-0.5,0)        *
******************************************************************************/
void
TranslatePlane(int idx, MyProgram *data)
{
   int 		start_vert_idx, start_poly_idx;
   int 		v, p, c;

   matrixType	scale_mat;
   matrixType	rotate_mat;
   matrixType	translate_mat;


   /* save starting position in vert and poly lists */
   start_vert_idx = data->data.current_vert_idx;
   start_poly_idx = data->data.current_poly_idx;

   /* copy over unit plane vertices */
   for (v = 0; v < NUM_PLANE_VERTS; v++)
   {
      CopyVertex(&unit_data.unit_plane_vert[v], 
				&data->data.vert_list[start_vert_idx + v]);

      data->data.current_vert_idx++;
      data->data.vert_count++;
   }

   /* copy over unit plane polygons */
   for (p = 0; p < NUM_PLANE_POLYS; p++)
   {
      CopyPolygon(start_vert_idx,
			&unit_data.unit_plane_poly[p], 
			&data->data.poly_list[start_poly_idx + p]);

      data->data.poly_list[start_poly_idx + p].visible = TRUE;

      for (c = 0; c < COLOR_RGB_LEN; c++)
         data->data.poly_list[start_poly_idx + p].color[c] = 
				data->data.prim_list[idx].color[c];

      data->data.current_poly_idx++;
      data->data.poly_count++;
   }

   /* scale to desired size */
   scale_mat = MakeScaleMatrix(data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.y,
				data->data.prim_list[idx].scaling.z);
   for (v = start_vert_idx; v < (start_vert_idx + NUM_PLANE_VERTS); v++)
       XformVertex(v, data, &scale_mat);

   /* rotate to desired angle */
   if (data->data.prim_list[idx].axis != 'n') {
      rotate_mat = MakeRotationMatrix(data->data.prim_list[idx].axis, 
					data->data.prim_list[idx].angle);
      for (v = start_vert_idx; v < (start_vert_idx + NUM_PLANE_VERTS); v++)
         XformVertex(v, data, &rotate_mat); 
   }

   /* translate to desired location */
   translate_mat = MakeTranslationMatrix(data->data.prim_list[idx].center.x,
				data->data.prim_list[idx].center.y,
				data->data.prim_list[idx].center.z);
   for (v = start_vert_idx; v < (start_vert_idx + NUM_PLANE_VERTS); v++)
       XformVertex(v, data, &translate_mat);

   /* compute normals of the polygons */
   for (p = start_poly_idx; p < (start_poly_idx + NUM_PLANE_POLYS); p++)
      ComputeNormal(p, data);
}


/******************************************************************************
*  TranslateCube - translate cube primitive                                   *
******************************************************************************/
void
TranslateCube(int idx, MyProgram *data)
{
   int 		start_vert_idx, start_poly_idx;
   int 		v, p, c;

   matrixType	scale_mat;
   matrixType	rotate_mat;
   matrixType	translate_mat;


   /* save starting position in vert and poly lists */
   start_vert_idx = data->data.current_vert_idx;
   start_poly_idx = data->data.current_poly_idx;

   /* copy over unit cube vertices */
   for (v = 0; v < NUM_CUBE_VERTS; v++)
   {
      CopyVertex(&unit_data.unit_cube_vert[v], 
				&data->data.vert_list[start_vert_idx + v]);

      data->data.current_vert_idx++;
      data->data.vert_count++;
   }

   /* copy over unit cube polygons */
   for (p = 0; p < NUM_CUBE_POLYS; p++)
   {
      CopyPolygon(start_vert_idx,
			&unit_data.unit_cube_poly[p], 
			&data->data.poly_list[start_poly_idx + p]);

      data->data.poly_list[start_poly_idx + p].visible = TRUE;

      for (c = 0; c < COLOR_RGB_LEN; c++)
         data->data.poly_list[start_poly_idx + p].color[c] = 
				data->data.prim_list[idx].color[c];

      data->data.current_poly_idx++;
      data->data.poly_count++;
   }

   /* scale to desired size */
   scale_mat = MakeScaleMatrix(data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.y,
				data->data.prim_list[idx].scaling.z);
   for (v = start_vert_idx; v < (start_vert_idx + NUM_CUBE_VERTS); v++)
       XformVertex(v, data, &scale_mat);

   /* rotate to desired angle */
   if (data->data.prim_list[idx].axis != 'n') {
      rotate_mat = MakeRotationMatrix(data->data.prim_list[idx].axis, 
					data->data.prim_list[idx].angle);
      for (v = start_vert_idx; v < (start_vert_idx + NUM_CUBE_VERTS); v++)
         XformVertex(v, data, &rotate_mat); 
   }

   /* translate to desired location */
   translate_mat = MakeTranslationMatrix(data->data.prim_list[idx].center.x,
				data->data.prim_list[idx].center.y,
				data->data.prim_list[idx].center.z);
   for (v = start_vert_idx; v < (start_vert_idx + NUM_CUBE_VERTS); v++)
       XformVertex(v, data, &translate_mat);

   /* compute normals of the polygons */
   for (p = start_poly_idx; p < (start_poly_idx + NUM_CUBE_POLYS); p++)
      ComputeNormal(p, data);
}


/******************************************************************************
*  TranslateCylinder - translate cylinder primitive                           *
******************************************************************************/
void
TranslateCylinder(int idx, MyProgram *data)
{
   int 		start_vert_idx, start_poly_idx;
   int 		v, p, c;
   int		ns, num_verts, num_polys;

   matrixType	scale_mat;
   matrixType	rotate_mat;
   matrixType	translate_mat;


   /* save starting position in vert and poly lists */
   start_vert_idx = data->data.current_vert_idx;
   start_poly_idx = data->data.current_poly_idx;

   /* make unit sized cylinder, use scaling.y as number of sides */
   ns = (int) data->data.prim_list[idx].scaling.y;
   num_verts = ((ns * 2) + 2);
   num_polys = (ns * 3);
   MakeUnitCylinder( ns );

   /* copy over unit cylinder vertices */
   for (v = 0; v < num_verts; v++)
   {
      CopyVertex(&unit_data.unit_cylinder_vert[v], 
				&data->data.vert_list[start_vert_idx + v]);

      data->data.current_vert_idx++;
      data->data.vert_count++;
   }

   /* copy over unit cylinder polygons */
   for (p = 0; p < num_polys; p++)
   {
      CopyPolygon(start_vert_idx,
			&unit_data.unit_cylinder_poly[p], 
			&data->data.poly_list[start_poly_idx + p]);

      data->data.poly_list[start_poly_idx + p].visible = TRUE;

      for (c = 0; c < COLOR_RGB_LEN; c++)
         data->data.poly_list[start_poly_idx + p].color[c] = 
				data->data.prim_list[idx].color[c];

      data->data.current_poly_idx++;
      data->data.poly_count++;
   }

   /* scale to desired size */
   scale_mat = MakeScaleMatrix(data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.z);
   for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
       XformVertex(v, data, &scale_mat);

   /* rotate to desired angle */
   if (data->data.prim_list[idx].axis != 'n') {
      rotate_mat = MakeRotationMatrix(data->data.prim_list[idx].axis, 
					data->data.prim_list[idx].angle);
      for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
         XformVertex(v, data, &rotate_mat); 
   }

   /* translate to desired location */
   translate_mat = MakeTranslationMatrix(data->data.prim_list[idx].center.x,
				data->data.prim_list[idx].center.y,
				data->data.prim_list[idx].center.z);
   for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
       XformVertex(v, data, &translate_mat);

   /* compute normals of the polygons */
   for (p = start_poly_idx; p < (start_poly_idx + num_polys); p++)
      ComputeNormal(p, data);
}


/******************************************************************************
*  TranslatePyramid - translate pyramid primitive                             *
******************************************************************************/
void
TranslatePyramid(int idx, MyProgram *data)
{
   int 		start_vert_idx, start_poly_idx;
   int 		v, p, c;

   matrixType	scale_mat;
   matrixType	rotate_mat;
   matrixType	translate_mat;


   /* save starting position in vert and poly lists */
   start_vert_idx = data->data.current_vert_idx;
   start_poly_idx = data->data.current_poly_idx;

   /* copy over unit pyramid vertices */
   for (v = 0; v < NUM_PYRAMID_VERTS; v++)
   {
      CopyVertex(&unit_data.unit_pyramid_vert[v], 
				&data->data.vert_list[start_vert_idx + v]);

      data->data.current_vert_idx++;
      data->data.vert_count++;
   }

   /* copy over unit pyramid polygons */
   for (p = 0; p < NUM_PYRAMID_POLYS; p++)
   {
      CopyPolygon(start_vert_idx,
			&unit_data.unit_pyramid_poly[p], 
			&data->data.poly_list[start_poly_idx + p]);

      data->data.poly_list[start_poly_idx + p].visible = TRUE;

      for (c = 0; c < COLOR_RGB_LEN; c++)
         data->data.poly_list[start_poly_idx + p].color[c] = 
				data->data.prim_list[idx].color[c];

      data->data.current_poly_idx++;
      data->data.poly_count++;
   }

   /* scale to desired size */
   scale_mat = MakeScaleMatrix(data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.y,
				data->data.prim_list[idx].scaling.z);
   for (v = start_vert_idx; v < (start_vert_idx + NUM_PYRAMID_VERTS); v++)
       XformVertex(v, data, &scale_mat);

   /* rotate to desired angle */
   if (data->data.prim_list[idx].axis != 'n') {
      rotate_mat = MakeRotationMatrix(data->data.prim_list[idx].axis, 
					data->data.prim_list[idx].angle);
      for (v = start_vert_idx; v < (start_vert_idx + NUM_PYRAMID_VERTS); v++)
         XformVertex(v, data, &rotate_mat); 
   }

   /* translate to desired location */
   translate_mat = MakeTranslationMatrix(data->data.prim_list[idx].center.x,
				data->data.prim_list[idx].center.y,
				data->data.prim_list[idx].center.z);
   for (v = start_vert_idx; v < (start_vert_idx + NUM_PYRAMID_VERTS); v++)
       XformVertex(v, data, &translate_mat);

   /* compute normals of the polygons */
   for (p = start_poly_idx; p < (start_poly_idx + NUM_PYRAMID_POLYS); p++)
      ComputeNormal(p, data);
}


/******************************************************************************
*  TranslatePrism - translate prism primitive                                 *
******************************************************************************/
void
TranslatePrism(int idx, MyProgram *data)
{
   int 		start_vert_idx, start_poly_idx;
   int 		v, p, c;

   matrixType	scale_mat;
   matrixType	rotate_mat;
   matrixType	translate_mat;


   /* save starting position in vert and poly lists */
   start_vert_idx = data->data.current_vert_idx;
   start_poly_idx = data->data.current_poly_idx;

   /* copy over unit prism vertices */
   for (v = 0; v < NUM_PRISM_VERTS; v++)
   {
      CopyVertex(&unit_data.unit_prism_vert[v], 
				&data->data.vert_list[start_vert_idx + v]);

      data->data.current_vert_idx++;
      data->data.vert_count++;
   }

   /* copy over unit prism polygons */
   for (p = 0; p < NUM_PRISM_POLYS; p++)
   {
      CopyPolygon(start_vert_idx,
			&unit_data.unit_prism_poly[p], 
			&data->data.poly_list[start_poly_idx + p]);

      data->data.poly_list[start_poly_idx + p].visible = TRUE;

      for (c = 0; c < COLOR_RGB_LEN; c++)
         data->data.poly_list[start_poly_idx + p].color[c] = 
				data->data.prim_list[idx].color[c];

      data->data.current_poly_idx++;
      data->data.poly_count++;
   }

   /* scale to desired size */
   scale_mat = MakeScaleMatrix(data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.y,
				data->data.prim_list[idx].scaling.z);
   for (v = start_vert_idx; v < (start_vert_idx + NUM_PRISM_VERTS); v++)
       XformVertex(v, data, &scale_mat);

   /* rotate to desired angle */
   if (data->data.prim_list[idx].axis != 'n') {
      rotate_mat = MakeRotationMatrix(data->data.prim_list[idx].axis, 
					data->data.prim_list[idx].angle);
      for (v = start_vert_idx; v < (start_vert_idx + NUM_PRISM_VERTS); v++)
         XformVertex(v, data, &rotate_mat); 
   }

   /* translate to desired location */
   translate_mat = MakeTranslationMatrix(data->data.prim_list[idx].center.x,
				data->data.prim_list[idx].center.y,
				data->data.prim_list[idx].center.z);
   for (v = start_vert_idx; v < (start_vert_idx + NUM_PRISM_VERTS); v++)
       XformVertex(v, data, &translate_mat);

   /* compute normals of the polygons */
   for (p = start_poly_idx; p < (start_poly_idx + NUM_PRISM_POLYS); p++)
      ComputeNormal(p, data);
}


/******************************************************************************
*  TranslateCone - translate cone primitive                                   *
******************************************************************************/
void
TranslateCone(int idx, MyProgram *data)
{
   int 		start_vert_idx, start_poly_idx;
   int 		v, p, c;
   int		ns, num_verts, num_polys;

   matrixType	scale_mat;
   matrixType	rotate_mat;
   matrixType	translate_mat;


   /* save starting position in vert and poly lists */
   start_vert_idx = data->data.current_vert_idx;
   start_poly_idx = data->data.current_poly_idx;

   /* make unit sized cone, use scaling.y as number of sides */
   ns = (int) data->data.prim_list[idx].scaling.y;
   num_verts = (ns + 2);
   num_polys = (ns * 2);
   MakeUnitCone( ns );

   /* copy over unit cone vertices */
   for (v = 0; v < num_verts; v++)
   {
      CopyVertex(&unit_data.unit_cone_vert[v], 
				&data->data.vert_list[start_vert_idx + v]);

      data->data.current_vert_idx++;
      data->data.vert_count++;
   }

   /* copy over unit cone polygons */
   for (p = 0; p < num_polys; p++)
   {
      CopyPolygon(start_vert_idx,
			&unit_data.unit_cone_poly[p], 
			&data->data.poly_list[start_poly_idx + p]);

      data->data.poly_list[start_poly_idx + p].visible = TRUE;

      for (c = 0; c < COLOR_RGB_LEN; c++)
         data->data.poly_list[start_poly_idx + p].color[c] = 
				data->data.prim_list[idx].color[c];

      data->data.current_poly_idx++;
      data->data.poly_count++;
   }

   /* scale to desired size */
   scale_mat = MakeScaleMatrix(data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.z);
   for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
       XformVertex(v, data, &scale_mat);

   /* rotate to desired angle */
   if (data->data.prim_list[idx].axis != 'n') {
      rotate_mat = MakeRotationMatrix(data->data.prim_list[idx].axis, 
					data->data.prim_list[idx].angle);
      for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
         XformVertex(v, data, &rotate_mat); 
   }

   /* translate to desired location */
   translate_mat = MakeTranslationMatrix(data->data.prim_list[idx].center.x,
				data->data.prim_list[idx].center.y,
				data->data.prim_list[idx].center.z);
   for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
       XformVertex(v, data, &translate_mat);

   /* compute normals of the polygons */
   for (p = start_poly_idx; p < (start_poly_idx + num_polys); p++)
      ComputeNormal(p, data);
}


/******************************************************************************
*  TranslateSphere - translate sphere primitive                               *
******************************************************************************/
void
TranslateSphere(int idx, MyProgram *data)
{
   int 		start_vert_idx, start_poly_idx;
   int 		v, p, c;
   int		ns, num_verts, num_polys;

   matrixType	scale_mat;
   matrixType	rotate_mat;
   matrixType	translate_mat;


   /* save starting position in vert and poly lists */
   start_vert_idx = data->data.current_vert_idx;
   start_poly_idx = data->data.current_poly_idx;

   /* make unit sized sphere, use scaling.y as number of sides */
   ns = (int) data->data.prim_list[idx].scaling.y;
   num_verts = (((ns / 2) + 1) * 2) * ns;
   num_polys = ((int) (ns / 2)) * ns;
   MakeUnitSphere( ns );

   /* copy over unit sphere vertices */
   for (v = 0; v < num_verts; v++)
   {
      CopyVertex(&unit_data.unit_sphere_vert[v], 
				&data->data.vert_list[start_vert_idx + v]);

      data->data.current_vert_idx++;
      data->data.vert_count++;
   }

   /* copy over unit sphere polygons */
   for (p = 0; p < num_polys; p++)
   {
      CopyPolygon(start_vert_idx,
			&unit_data.unit_sphere_poly[p], 
			&data->data.poly_list[start_poly_idx + p]);

      data->data.poly_list[start_poly_idx + p].visible = TRUE;

      for (c = 0; c < COLOR_RGB_LEN; c++)
         data->data.poly_list[start_poly_idx + p].color[c] = 
				data->data.prim_list[idx].color[c];

      data->data.current_poly_idx++;
      data->data.poly_count++;
   }

   /* scale to desired size */
   scale_mat = MakeScaleMatrix(data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.x,
				data->data.prim_list[idx].scaling.x);
   for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
       XformVertex(v, data, &scale_mat);

   /* rotate to desired angle */
   if (data->data.prim_list[idx].axis != 'n') {
      rotate_mat = MakeRotationMatrix(data->data.prim_list[idx].axis, 
					data->data.prim_list[idx].angle);
      for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
         XformVertex(v, data, &rotate_mat); 
   }

   /* translate to desired location */
   translate_mat = MakeTranslationMatrix(data->data.prim_list[idx].center.x,
				data->data.prim_list[idx].center.y,
				data->data.prim_list[idx].center.z);
   for (v = start_vert_idx; v < (start_vert_idx + num_verts); v++)
       XformVertex(v, data, &translate_mat);

   /* compute normals of the polygons */
   for (p = start_poly_idx; p < (start_poly_idx + num_polys); p++)
      ComputeNormal(p, data);
}


/******************************************************************************
*  MakeUnitPlane - build vertices and polygons for unit sized plane           *
******************************************************************************/
void
MakeUnitPlane()
{
   /* set vertices 1 to 4 */
   SetVertex( -DEFAULT_COORD, -DEFAULT_COORD, 0.0, 
					&unit_data.unit_plane_vert[0]);
   SetVertex( DEFAULT_COORD, -DEFAULT_COORD, 0.0, 
					&unit_data.unit_plane_vert[1]);
   SetVertex( DEFAULT_COORD, DEFAULT_COORD, 0.0, 
					&unit_data.unit_plane_vert[2]);
   SetVertex( -DEFAULT_COORD, DEFAULT_COORD, 0.0, 
					&unit_data.unit_plane_vert[3]);

   /* set vertices of polygon 1 */
   unit_data.unit_plane_poly[0].vertices[0] = 3; /* clockwise for left hand */
   unit_data.unit_plane_poly[0].vertices[1] = 2; /* coordinate system       */
   unit_data.unit_plane_poly[0].vertices[2] = 1;
   unit_data.unit_plane_poly[0].vertices[3] = 0;
   unit_data.unit_plane_poly[0].num_verts = SIZE_OF_RECT;
}


/******************************************************************************
*  MakeUnitCube - build vertices and polygons for unit sized cube             *
******************************************************************************/
void
MakeUnitCube()
{
   /* set vertices 1 to 8 */
   SetVertex( -DEFAULT_COORD, -DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_cube_vert[0]);
   SetVertex( DEFAULT_COORD, -DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_cube_vert[1]);
   SetVertex( DEFAULT_COORD, DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_cube_vert[2]);
   SetVertex( -DEFAULT_COORD, DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_cube_vert[3]);
   SetVertex( -DEFAULT_COORD, -DEFAULT_COORD, DEFAULT_COORD, 
					&unit_data.unit_cube_vert[4]);
   SetVertex( DEFAULT_COORD, -DEFAULT_COORD, DEFAULT_COORD, 
					&unit_data.unit_cube_vert[5]);
   SetVertex( DEFAULT_COORD, DEFAULT_COORD, DEFAULT_COORD, 
					&unit_data.unit_cube_vert[6]);
   SetVertex( -DEFAULT_COORD, DEFAULT_COORD, DEFAULT_COORD, 
					&unit_data.unit_cube_vert[7]);

   /* set vertices of polygon 1 */
   unit_data.unit_cube_poly[0].vertices[0] = 3;	/* clockwise for left hand */
   unit_data.unit_cube_poly[0].vertices[1] = 2; /* coordinate system       */
   unit_data.unit_cube_poly[0].vertices[2] = 1;
   unit_data.unit_cube_poly[0].vertices[3] = 0;
   unit_data.unit_cube_poly[0].num_verts = SIZE_OF_RECT;

   /* set vertices of polygon 2 */
   unit_data.unit_cube_poly[1].vertices[0] = 0;
   unit_data.unit_cube_poly[1].vertices[1] = 1;
   unit_data.unit_cube_poly[1].vertices[2] = 5;
   unit_data.unit_cube_poly[1].vertices[3] = 4;
   unit_data.unit_cube_poly[1].num_verts = SIZE_OF_RECT;

   /* set vertices of polygon 3 */
   unit_data.unit_cube_poly[2].vertices[0] = 2;
   unit_data.unit_cube_poly[2].vertices[1] = 6;
   unit_data.unit_cube_poly[2].vertices[2] = 5;
   unit_data.unit_cube_poly[2].vertices[3] = 1;
   unit_data.unit_cube_poly[2].num_verts = SIZE_OF_RECT;

   /* set vertices of polygon 4 */
   unit_data.unit_cube_poly[3].vertices[0] = 7;
   unit_data.unit_cube_poly[3].vertices[1] = 6;
   unit_data.unit_cube_poly[3].vertices[2] = 2;
   unit_data.unit_cube_poly[3].vertices[3] = 3;
   unit_data.unit_cube_poly[3].num_verts = SIZE_OF_RECT;

   /* set vertices of polygon 5 */
   unit_data.unit_cube_poly[4].vertices[0] = 7;
   unit_data.unit_cube_poly[4].vertices[1] = 3;
   unit_data.unit_cube_poly[4].vertices[2] = 0;
   unit_data.unit_cube_poly[4].vertices[3] = 4;
   unit_data.unit_cube_poly[4].num_verts = SIZE_OF_RECT;

   /* set vertices of polygon 6 */
   unit_data.unit_cube_poly[5].vertices[0] = 6;
   unit_data.unit_cube_poly[5].vertices[1] = 7;
   unit_data.unit_cube_poly[5].vertices[2] = 4;
   unit_data.unit_cube_poly[5].vertices[3] = 5;
   unit_data.unit_cube_poly[5].num_verts = SIZE_OF_RECT;
}


/******************************************************************************

  CalcCirclePoints() - This function generates a set of N points which
		lie on a circle of the specified radius(r).

******************************************************************************/
void 
CalcCirclePoints(wpointType circle_pts[], double radius, int sides)
{
   int i;			/* loop index */
   double pie_angle;		/* rotation angle to next point */
   matrixType rotate_xform;	/* rotation transform */

   /* calculate rotation angle to next point */
   pie_angle = 360.0 / ((double) sides);

   /* initialize first point on circle */
   circle_pts[0].x = radius;
   circle_pts[0].y = 0.0;
   circle_pts[0].z = 0.0;

   /* create necessary transform for rotating about z-axis */
   rotate_xform = MakeRotationMatrix('z', pie_angle);

   /* successively generate next circle point from previous circle point */
   for (i = 1; i < sides; i++) 
   {   
      circle_pts[i] = TransformWPoint(&circle_pts[i-1], &rotate_xform);
   } 
}


/******************************************************************************
*  MakeUnitCylinder - build vertices and polygons for unit sized cylinder     *
******************************************************************************/
void
MakeUnitCylinder(int sides)
{
   int v, p;
   wpointType circle_pts[MAX_CIRCLE_POINTS];


   /* calculate points lying on circle */
   CalcCirclePoints(circle_pts, DEFAULT_COORD, sides);

   /* set up all cylinder vertices */
   SetVertex(0.0, 0.0, -DEFAULT_COORD, 
				&unit_data.unit_cylinder_vert[0]);

   for (v = 1; v < (sides + 1); v++)
   {
      SetVertex(circle_pts[v - 1].x, circle_pts[v - 1].y, -DEFAULT_COORD,
				&unit_data.unit_cylinder_vert[v]);
   }

   SetVertex(0.0, 0.0, DEFAULT_COORD,
				&unit_data.unit_cylinder_vert[(sides + 1)]);

   for (v = (sides + 2); v < ((sides * 2) + 2); v++)
   {
      SetVertex(circle_pts[v - (sides + 2)].x, 
				circle_pts[v - (sides + 2)].y, DEFAULT_COORD,
				&unit_data.unit_cylinder_vert[v]);
   }


   /* set up front face polygons */
   for (p = 0; p < sides; p++)
   {
      if (p < (sides - 1))
      {
         unit_data.unit_cylinder_poly[p].vertices[0] = p + 2;
         unit_data.unit_cylinder_poly[p].vertices[1] = p + 1;
         unit_data.unit_cylinder_poly[p].vertices[2] = 0;
      }
      else
      {
         unit_data.unit_cylinder_poly[p].vertices[0] = 1;
         unit_data.unit_cylinder_poly[p].vertices[1] = p + 1;
         unit_data.unit_cylinder_poly[p].vertices[2] = 0;
      }
      unit_data.unit_cylinder_poly[p].num_verts = SIZE_OF_TRIA;
   }

   /* set up back face polygons */
   for (p = sides; p < (sides * 2); p++)
   {
      if (p < ((sides * 2) - 1) )
      {
         unit_data.unit_cylinder_poly[p].vertices[0] = (sides + 1);
         unit_data.unit_cylinder_poly[p].vertices[1] = p + 2;
         unit_data.unit_cylinder_poly[p].vertices[2] = p + 3;
      }
      else
      {
         unit_data.unit_cylinder_poly[p].vertices[0] = (sides + 1);
         unit_data.unit_cylinder_poly[p].vertices[1] = p + 2;
         unit_data.unit_cylinder_poly[p].vertices[2] = (sides + 1) + 1;
      }
      unit_data.unit_cylinder_poly[p].num_verts = SIZE_OF_TRIA;
   }

   /* set up sides polygons */
   for (p = (sides * 2); p < (sides * 3); p++)
   {
      if (p < ((sides * 3) - 1) )
      {
         unit_data.unit_cylinder_poly[p].vertices[0] = p - (sides * 2) + 2;
         unit_data.unit_cylinder_poly[p].vertices[1] = p - (sides) + 3;
         unit_data.unit_cylinder_poly[p].vertices[2] = p - (sides) + 2;
         unit_data.unit_cylinder_poly[p].vertices[3] = p - (sides * 2) + 1;
      }
      else
      {
         unit_data.unit_cylinder_poly[p].vertices[0] = 1;
         unit_data.unit_cylinder_poly[p].vertices[1] = (sides + 1) + 1;
         unit_data.unit_cylinder_poly[p].vertices[2] = p - (sides) + 2;
         unit_data.unit_cylinder_poly[p].vertices[3] = p - (sides * 2) + 1;
      }
      unit_data.unit_cylinder_poly[p].num_verts = SIZE_OF_RECT;
   }
}


/******************************************************************************
*  MakeUnitPyramid - build vertices and polygons for unit sized pyramid       *
******************************************************************************/
void
MakeUnitPyramid()
{
   int i;

   /* set vertices 1 to 5 */
   SetVertex( -DEFAULT_COORD, -DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_pyramid_vert[0]);
   SetVertex( DEFAULT_COORD, -DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_pyramid_vert[1]);
   SetVertex( DEFAULT_COORD, DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_pyramid_vert[2]);
   SetVertex( -DEFAULT_COORD, DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_pyramid_vert[3]);
   SetVertex( 0.0, 0.0, DEFAULT_COORD,
					&unit_data.unit_pyramid_vert[4]);

   /* set vertices of polygon 1 */
   unit_data.unit_pyramid_poly[0].vertices[0] = 3;
   unit_data.unit_pyramid_poly[0].vertices[1] = 2;
   unit_data.unit_pyramid_poly[0].vertices[2] = 1;
   unit_data.unit_pyramid_poly[0].vertices[3] = 0;
   unit_data.unit_pyramid_poly[0].num_verts = SIZE_OF_RECT;

   /* set vertices of polygons 2 to 5 */
   for (i = 0; i < 4; i++)
   {
      if (i < 3)
      {
         unit_data.unit_pyramid_poly[i + 1].vertices[0] = i + 1;
         unit_data.unit_pyramid_poly[i + 1].vertices[1] = 4;
         unit_data.unit_pyramid_poly[i + 1].vertices[2] = i;
      }
      else
      {
         unit_data.unit_pyramid_poly[i + 1].vertices[0] = 0;
         unit_data.unit_pyramid_poly[i + 1].vertices[1] = 4;
         unit_data.unit_pyramid_poly[i + 1].vertices[2] = i;

      }
      unit_data.unit_pyramid_poly[i + 1].num_verts = SIZE_OF_TRIA;
   }
}


/******************************************************************************
*  MakeUnitPrism - build vertices and polygons for unit sized prism           *
******************************************************************************/
void
MakeUnitPrism()
{
   int i;

   /* set vertices 1 to 6 */
   SetVertex( -DEFAULT_COORD, -DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_prism_vert[0]);
   SetVertex( DEFAULT_COORD, -DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_prism_vert[1]);
   SetVertex( -DEFAULT_COORD, DEFAULT_COORD, -DEFAULT_COORD, 
					&unit_data.unit_prism_vert[2]);
   SetVertex( -DEFAULT_COORD, -DEFAULT_COORD, DEFAULT_COORD, 
					&unit_data.unit_prism_vert[3]);
   SetVertex( DEFAULT_COORD, -DEFAULT_COORD, DEFAULT_COORD, 
					&unit_data.unit_prism_vert[4]);
   SetVertex( -DEFAULT_COORD, DEFAULT_COORD, DEFAULT_COORD, 
					&unit_data.unit_prism_vert[5]);

   /* set vertices of polygon 1 */
   unit_data.unit_prism_poly[0].vertices[0] = 0;
   unit_data.unit_prism_poly[0].vertices[1] = 2;
   unit_data.unit_prism_poly[0].vertices[2] = 1;
   unit_data.unit_prism_poly[0].num_verts = SIZE_OF_TRIA;

   /* set vertices of polygon 2 */
   unit_data.unit_prism_poly[1].vertices[0] = 4;
   unit_data.unit_prism_poly[1].vertices[1] = 5;
   unit_data.unit_prism_poly[1].vertices[2] = 3;
   unit_data.unit_prism_poly[1].num_verts = SIZE_OF_TRIA;

   /* set vertices of polygons 3 to 5 */
   for (i = 0; i < 3; i++)
   {
      if (i < 2)
      {
         unit_data.unit_prism_poly[i + 2].vertices[0] = i;
         unit_data.unit_prism_poly[i + 2].vertices[1] = i + 1;
         unit_data.unit_prism_poly[i + 2].vertices[2] = i + 4;
         unit_data.unit_prism_poly[i + 2].vertices[3] = i + 3;
         unit_data.unit_prism_poly[i + 2].num_verts = SIZE_OF_RECT;
      }
      else
      {
         unit_data.unit_prism_poly[i + 2].vertices[0] = 3;
         unit_data.unit_prism_poly[i + 2].vertices[1] = i + 3;
         unit_data.unit_prism_poly[i + 2].vertices[2] = i;
         unit_data.unit_prism_poly[i + 2].vertices[3] = 0;
         unit_data.unit_prism_poly[i + 2].num_verts = SIZE_OF_RECT;
      }
   }
}


/******************************************************************************
*  MakeUnitCone - build vertices and polygons for unit sized cone             *
******************************************************************************/
void
MakeUnitCone(int sides)
{
   int v, p;
   wpointType circle_pts[MAX_CIRCLE_POINTS];


   /* calculate points lying on circle */
   CalcCirclePoints(circle_pts, DEFAULT_COORD, sides);

   /* set up all cone vertices */
   SetVertex(0.0, 0.0, -DEFAULT_COORD,
				&unit_data.unit_cone_vert[0]);

   for (v = 1; v < (sides + 1); v++)
   {
      SetVertex(circle_pts[v - 1].x, circle_pts[v - 1].y, -DEFAULT_COORD,
				&unit_data.unit_cone_vert[v]);
   }

   SetVertex(0.0, 0.0, DEFAULT_COORD,
				&unit_data.unit_cone_vert[(sides + 1)]);


   /* set up front face polygons */
   for (p = 0; p < sides; p++)
   {
      if (p < (sides - 1))
      {
         unit_data.unit_cone_poly[p].vertices[0] = p + 2;
         unit_data.unit_cone_poly[p].vertices[1] = p + 1;
         unit_data.unit_cone_poly[p].vertices[2] = 0;
      }
      else
      {
         unit_data.unit_cone_poly[p].vertices[0] = 1;
         unit_data.unit_cone_poly[p].vertices[1] = p + 1;
         unit_data.unit_cone_poly[p].vertices[2] = 0;
      }
      unit_data.unit_cone_poly[p].num_verts = SIZE_OF_TRIA;
   }

   /* set up side slope polygons */
   for (p = 1; p < (sides + 1); p++)
   {
      if (p < sides)
      {
         unit_data.unit_cone_poly[p + sides - 1].vertices[0] = p + 1;
         unit_data.unit_cone_poly[p + sides - 1].vertices[1] = sides + 1;
         unit_data.unit_cone_poly[p + sides - 1].vertices[2] = p;
      }
      else
      {
         unit_data.unit_cone_poly[p + sides - 1].vertices[0] = 1;
         unit_data.unit_cone_poly[p + sides - 1].vertices[1] = sides + 1;
         unit_data.unit_cone_poly[p + sides - 1].vertices[2] = p;
      }
      unit_data.unit_cone_poly[p + sides - 1].num_verts = SIZE_OF_TRIA;
   }
}


/******************************************************************************
*  MakeUnitSphere - build vertices and polygons for unit sized sphere         *
*                                                                             *
*  algorithm:                                                                 *
*	generate circle points
* 	put initial wedge points in wedge point list
*	generate remaining wedge points and add them to the list
*	link up the wedge polygons
*	add current wedge points and polygons to unit sphere lists
*	for each wedge slice loop
*		rotate wedge points by (360 / sides) about y axis
*		add points and polys to unit sphere lists
*	end loop
*                                                                             *
******************************************************************************/
void
MakeUnitSphere(int sides)
{
   int 		v, p, w;
   int		poly_count, half_num_wedge_pts, num_wedge_pts;

   wpointType 	circle_pts[MAX_CIRCLE_POINTS];

   wpointType	temp_vertex;

   float	wedge_angle;
   wpointType 	wedge_pts[MAX_WEDGE_POINTS];
   POLYGON_S_T 	wedge_polys[MAX_WEDGE_POLYS];

   matrixType	wedge_rot_mat;	/* rotate by wedge_angle about y axis */


   /* compute wedge rotation matrix */
   wedge_angle = 360 / sides;
   wedge_rot_mat = MakeRotationMatrix( 'x', wedge_angle );

   /* calculate points lying on circle */
   CalcCirclePoints(circle_pts, DEFAULT_COORD, sides);

   /* add initial wedge points to wedge point list */
   half_num_wedge_pts = ((int) (sides / 2)) + 1;
   num_wedge_pts = half_num_wedge_pts * 2;

   for (v = 0; v < half_num_wedge_pts; v++)
      CopyVertex( &circle_pts[v], &wedge_pts[v] );

   /* rotate initial wedge points about x axis and add them to wedge points */
   for (v = 0; v < half_num_wedge_pts; v++)
   {
      temp_vertex = TransformWPoint(&wedge_pts[v], &wedge_rot_mat);
      CopyWPoint(&temp_vertex, &wedge_pts[v + half_num_wedge_pts]);
   }

   /* make wedge polygons */
   poly_count = (int) (sides / 2);

   wedge_polys[0].vertices[0] = half_num_wedge_pts;
   wedge_polys[0].vertices[1] = half_num_wedge_pts + 1;
   wedge_polys[0].vertices[2] = 1;
   wedge_polys[0].num_verts = SIZE_OF_TRIA;

   for (w = 1; w < (poly_count - 1); w++)
   {
      wedge_polys[w].vertices[0] = half_num_wedge_pts + w;
      wedge_polys[w].vertices[1] = half_num_wedge_pts + w + 1;
      wedge_polys[w].vertices[2] = w + 1;
      wedge_polys[w].vertices[3] = w;
      wedge_polys[w].num_verts = SIZE_OF_RECT;
   }

   wedge_polys[poly_count - 1].vertices[0] = num_wedge_pts - 2;
   wedge_polys[poly_count - 1].vertices[1] = num_wedge_pts - 1;
   wedge_polys[poly_count - 1].vertices[2] = half_num_wedge_pts - 2;
   wedge_polys[poly_count - 1].num_verts = SIZE_OF_TRIA;

   /* add initial wedge points and polygons to unit sphere lists */
   for (v = 0; v < num_wedge_pts; v++)
      CopyVertex( &wedge_pts[v], &unit_data.unit_sphere_vert[v] );

   for (p = 0; p < poly_count; p++)
      CopyPolygon(0, &wedge_polys[p], &unit_data.unit_sphere_poly[p]);

   /* rotate wedge pts about x axis and then add to unit sphere lists */
   for (w = 1; w < sides; w++)
   {
      for (v = 0; v < num_wedge_pts; v++)
      {
         temp_vertex = TransformWPoint(&wedge_pts[v], &wedge_rot_mat);
         CopyWPoint(&temp_vertex, &wedge_pts[v]);
      }

      for (v = 0; v < num_wedge_pts; v++)
         CopyVertex( &wedge_pts[v], 
		&unit_data.unit_sphere_vert[v + (w * num_wedge_pts)] );

      for (p = 0; p < poly_count; p++)
         CopyPolygon((w * num_wedge_pts), &wedge_polys[p], 
		&unit_data.unit_sphere_poly[p + (w * poly_count)]);
   }
}


/******************************************************************************
*  SetVertex - sets a vertex to specified coordinate values                   *
******************************************************************************/
void
SetVertex(float x, float y, float z, wpointType *v)
{ 
   v->x = x;  v->y = y;  v->z = z;
}


/******************************************************************************
*  CopyVertex - copies source vertex to destination vertex                    *
******************************************************************************/
void
CopyVertex(wpointType *src, wpointType *dst)
{
   CopyWPoint(src, dst);
}


/******************************************************************************
*  CopyPolygon - copies source polygon to destination polygon                 *
******************************************************************************/
void
CopyPolygon(int sv_idx, POLYGON_S_T *src, POLYGON_S_T *dst)
{
   int i;

   dst->num_verts = src->num_verts;

   for (i = 0; i < src->num_verts; i++)
      dst->vertices[i] = sv_idx + src->vertices[i];

   CopyVector(&src->normal, &dst->normal);

   for (i = 0; i < COLOR_RGB_LEN; i++)
      dst->color[i] = src->color[i];

   dst->visible = src->visible;
   dst->sorted = src->sorted;
   dst->rendered = src->rendered;
}



/******************************************************************************
*  XformVertex - transforms a specified vertex by given xform matrix          *
******************************************************************************/
void
XformVertex(int idx, MyProgram *data, matrixType *xform)
{
   wpointType	temp_vertex;

   temp_vertex = TransformWPoint(&data->data.vert_list[idx], xform);

   CopyWPoint(&temp_vertex, &data->data.vert_list[idx]);
}


/******************************************************************************
*  ComputeNormal - computes a specified polygon's normal vector               *
*                                                                             *
*  computes two vectors P2P1 and P2P3 where P1, P2, and P3 are the first      *
*  three vertices of the polygon (counter-clockwise)                          *
*                                                                             *
*  then computes normal as P2P3 X P2P1  i.e.  N = (P3 - P2) X (P1 - P2)       *
*                                                                             *
******************************************************************************/
void
ComputeNormal(int idx, MyProgram *data)
{
   vectorType p1, p2, p3;
   vectorType v1, v2, normal;

   /* transform world points into vectors */
   p1 = WPoint2Vector( 
		&data->data.vert_list[data->data.poly_list[idx].vertices[0]]);
   p2 = WPoint2Vector( 
		&data->data.vert_list[data->data.poly_list[idx].vertices[1]]);
   p3 = WPoint2Vector( 
		&data->data.vert_list[data->data.poly_list[idx].vertices[2]]);

   /* compute vector V1 (P2P1) */
   v1 = VecSub(&p1, &p2);

   /* compute vector V2 (P2P3) */
   v2 = VecSub(&p3, &p2);

   /* compute cross product N = V2 X V1 */
   normal = VecCrossproduct(&v2, &v1);

   /* normalize the result */
   VecNormalize(&normal);

   /* copy into polygon's normal */
   CopyVector(&normal, &data->data.poly_list[idx].normal);
}


/* end of translat.c */
