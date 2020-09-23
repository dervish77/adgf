/***********************************************************************

   File:  	drawgen.c

   Author: 	Brian Lingard

   Date:	9/18/95

  Generic drawing related functions.

***********************************************************************/



/* include necessary files */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#ifndef _MAIN_H
#include "main.h"              /* where program specific stuff is defined */
#endif



static void ComputeNormalVCS(int idx, MyProgram *data);



/******************************************************************

  MapToView  -- This function maps world coordinate point to the
		viewport by applying the specified mapping transform.

		This function returns a screen point.

******************************************************************/
pointType
MapToView(wpointType vertex, matrixType *mapxform)
{
   matrixType 	vertex_mat;		/* vertex as a matrix */
   matrixType 	xform_vertex_mat;	/* transformed vertex as a matrix */
   pointType 	view_p;			/* transformed screen point */


   vertex_mat = WPoint2Matrix(&vertex, 3);

   xform_vertex_mat = MatrixMultiply(mapxform, &vertex_mat);

   view_p.x = xform_vertex_mat.m[0][0];
   view_p.y = xform_vertex_mat.m[1][0];

   return(view_p);
} 


/******************************************************************

  MakeMappingXform() -- This function generates the transform matrix 
			for mapping a world coordinate point into a
			viewport point.

  Note: (for camera view)

	Calculate view bound based on maintaining a fixed field of
	view angle given the specified eye location.

	vrp - view reference point
	eye - eye location
	lap - look at point

	vpd = distance from eye to vrp, vrp may or may not equal lap

	if square field of view

		view_bound = vpd x tan (fov_angle / 2)

******************************************************************/
void
MakeMappingXform(VIEW_SCREEN_T viewport, MyProgram *data, matrixType *mapxform)
{
   matrixType 	xform;
   double 	worldbounds[4], screenbounds[4];

   float	view_bound;	/* calculated view bound */

   /* extract this view's world boundaries */
   switch(viewport) {
      case ORTH_XY_VIEW:
      case SMALL_ORTH_XY_VIEW:
         worldbounds[0] = -data->zoom_value;	/* x min */
         worldbounds[1] = -data->zoom_value;	/* y min */
         worldbounds[2] = data->zoom_value;	/* x max */
         worldbounds[3] = data->zoom_value;	/* y max */
         break;
      case ORTH_ZY_VIEW:
      case SMALL_ORTH_ZY_VIEW:
         worldbounds[0] = -data->zoom_value;	/* x min */
         worldbounds[1] = -data->zoom_value;	/* y min */
         worldbounds[2] = data->zoom_value;	/* x max */
         worldbounds[3] = data->zoom_value;	/* y max */
         break;
      case ORTH_XZ_VIEW:
      case SMALL_ORTH_XZ_VIEW:
         worldbounds[0] = -data->zoom_value;	/* x min */
         worldbounds[1] = -data->zoom_value;	/* y min */
         worldbounds[2] = data->zoom_value;	/* x max */
         worldbounds[3] = data->zoom_value;	/* y max */
         break;
      case CAMERA_VIEW:
      case SMALL_CAMERA_VIEW:
         view_bound = data->data.view.vpd * tan( DEG2RADS(DEFAULT_FOV_ANGLE) );

         worldbounds[0] = -view_bound;	/* x min */
         worldbounds[1] = -view_bound;	/* y min */
         worldbounds[2] = view_bound;	/* x max */
         worldbounds[3] = view_bound;	/* y max */
         break;
      default:
         break;
   }

   /* calculate this view's screen boundaries */
   switch(viewport) {
      case ORTH_XY_VIEW:
      case ORTH_ZY_VIEW:
      case ORTH_XZ_VIEW:
      case CAMERA_VIEW:
         screenbounds[0] = 0.0;
         screenbounds[1] = 0.0;
         screenbounds[2] = SCREEN_X_SIZE;
         screenbounds[3] = SCREEN_Y_SIZE;
         break;

      case SMALL_ORTH_XY_VIEW:
         screenbounds[0] = 0.0;
         screenbounds[1] = (SCREEN_Y_SIZE / 2);
         screenbounds[2] = (SCREEN_X_SIZE / 2);
         screenbounds[3] = SCREEN_Y_SIZE;
         break;

      case SMALL_ORTH_ZY_VIEW:
         screenbounds[0] = (SCREEN_X_SIZE / 2);
         screenbounds[1] = (SCREEN_Y_SIZE / 2);
         screenbounds[2] = SCREEN_X_SIZE;
         screenbounds[3] = SCREEN_Y_SIZE;
         break;

      case SMALL_ORTH_XZ_VIEW:
         screenbounds[0] = 0.0;
         screenbounds[1] = 0.0;
         screenbounds[2] = (SCREEN_X_SIZE / 2);
         screenbounds[3] = (SCREEN_Y_SIZE / 2);
         break;

      case SMALL_CAMERA_VIEW:
         screenbounds[0] =  (SCREEN_X_SIZE / 2);
         screenbounds[1] =  0.0;
         screenbounds[2] =  SCREEN_X_SIZE;
         screenbounds[3] =  (SCREEN_Y_SIZE / 2);

/*         screenbounds[0] =  view.vpx.min + offset;
         screenbounds[1] =  view.vpy.min + offset;
         screenbounds[2] =  view.vpx.max - offset;
         screenbounds[3] =  view.vpy.max - offset;
*/
         break;

      default:
         break;
   }

   xform = MakeMappingMatrix(worldbounds, screenbounds);

   MatrixCopy(&xform, mapxform);

} /* end of MakeMappingXform() */


/******************************************************************

  DrawView() -- This function draws all polygons seen on specified 
		viewport.  

******************************************************************/
void
DrawView(VIEW_SCREEN_T viewport, MyProgram *data)
{
   int p;			/* loop index */
   matrixType map_xform;	/* world to view mapping transform */

/*
printf("drawing view %d\n", viewport);
*/

   /* generate mapping transform for this view */
   MakeMappingXform(viewport, data, &map_xform);

   /* loop through the polygon list */
   for (p = 0; p < data->data.poly_count; p++) 
   {
      data->data.poly_list[p].visible = TRUE;

      DrawWorldPolygon(viewport,
			&data->data.vert_list[0], 
			&data->data.poly_list[p], 
			&map_xform);		
   }

   /* draw light icon */
   DrawLightLocation(viewport, data, &map_xform);

   /* draw camera icon */
   DrawCameraLocation(viewport, data, &map_xform);

} /* end of DrawView() */


/******************************************************************

  NoClipEdge() -- This function performs no clipping.  It merely 
		returns the indicated start and end vertices.

		NOTE:  used only for debug purposes!!

		CAUTION: this function modifies the contents of 
		         startv and endv.

******************************************************************/
int
NoClipEdge(VIEW_SCREEN_T viewport, 
		wpointType *startv, 
		wpointType *endv)
{
   wpointType sv, ev;		/* temp start and end vertices */

   /* temporarily return unclipped vertices */
   switch(viewport)
   {
      case ORTH_XY_VIEW:
      case SMALL_ORTH_XY_VIEW:
         sv.x = startv->x;
         sv.y = startv->y;
         sv.z = 1.0;
         ev.x = endv->x;
         ev.y = endv->y;
         ev.z = 1.0;
         break;
      case ORTH_ZY_VIEW:
      case SMALL_ORTH_ZY_VIEW:
         sv.x = startv->z;
         sv.y = startv->y;
         sv.z = 1.0;
         ev.x = endv->z;
         ev.y = endv->y;
         ev.z = 1.0;
         break;
      case ORTH_XZ_VIEW:
      case SMALL_ORTH_XZ_VIEW:
         sv.x = startv->x;
         sv.y = startv->z;
         sv.z = 1.0;
         ev.x = endv->x;
         ev.y = endv->z;
         ev.z = 1.0;
         break;
      default:
         break;
   }

   /* return temp values */
   startv->x = sv.x;
   startv->y = sv.y;
   startv->z = sv.z;
   endv->x = ev.x;
   endv->y = ev.y;
   endv->z = ev.z;

   return(TRUE);	/* always accept */
} /* end of NoClipEdge() */


/******************************************************************

  CopyVerticesArray() -- Copies modeled vertices to render array.

******************************************************************/
void
CopyVerticesArray(MyProgram *data)
{
   int v;

   for (v = 0; v < data->data.vert_count; v++)
   {
      CopyWPoint(&data->data.vert_list[v], &data->data.rend_vert_list[v]);
   }
}


/******************************************************************

  ComputeViewXformMatrix() -- computes view transform based on current
                              camera info.

  defs:
	eye 	- camera location
	lap	- look at point
	vrp	- view reference point
	vup	- initial up vector
	dop	- direction of projection
	vpn	- view plane normal
	vpd	- view plane distance
	M	- view transform

  calculations:
	dop	= normalize { eye - lap }
	vpn 	= dop
	vpd	= magnitude { eye - vrp }
	n	= normalize { vpn }
	u	= normalize { (vup cross vpn) }
	v	= normalize { n cross u }
	M	= R(v) * R(u) * R(n) * T(-vrp)

******************************************************************/
void
ComputeViewXformMatrix(MyProgram *data)
{
   vectorType	eye, lap, vrp;
   vectorType	dop, vpn, vup, vpd_vec;
   vectorType 	uvec;		/* view coord axes */
   vectorType	vvec;
   vectorType	nvec;
   matrixType	R, T, M;
   int		i;
   float	vpd;
   
   extern vectorType VecCrossproduct(vectorType *v1, vectorType *v2);


   /* compute dop */
   eye = WPoint2Vector(&data->data.view.eyeloc);
   lap = WPoint2Vector(&data->data.view.lookat);
   dop = VecSub(&eye, &lap);

   /* set vpn equal to dop */
   CopyVector(&dop, &vpn);

   /* compute n axis vector */
   VecNormalize(&vpn);
   CopyVector(&vpn, &nvec);

   /* compute u axis vector */
   CopyVector(&data->data.view.vup, &vup);
   uvec = VecCrossproduct(&vpn, &vup);
   VecNormalize(&uvec);

   /* compute v axis vector */
   vvec = VecCrossproduct(&uvec, &nvec);

   /* compute translation matrix */
   T = MakeTranslationMatrix( -data->data.view.vrp.x, 
				-data->data.view.vrp.y, 
				-data->data.view.vrp.z );

   /* compute rotation matrix */
   R = MakeIdentityMatrix();
   R.m[0][0] = uvec.x;  R.m[0][1] = uvec.y;  R.m[0][2] = uvec.z; 

   R.m[1][0] = vvec.x;  R.m[1][1] = vvec.y;  R.m[1][2] = vvec.z; 

   R.m[2][0] = nvec.x;  R.m[2][1] = nvec.y;  R.m[2][2] = nvec.z; 

   /* compute view transform */
   M = MatrixMultiply(&R, &T);

   /* copy computed transform to view structure */
   MatrixCopy(&M, &data->data.view.M);

   /* calculate view plane distance */
   vrp = WPoint2Vector(&data->data.view.vrp);
   vpd_vec = VecSub(&eye, &vrp);
   vpd = VecMagnitude(&vpd_vec);
   data->data.view.vpd = vpd;
}


/******************************************************************

  MapWorldToViewCS() -- maps world coord system into view coord system
			by applying the current view transform matrix
			on all vertices in vertex list.

******************************************************************/
void
MapWorldToViewCS(MyProgram *data)
{
   int 		v, p;
   wpointType	temp;

   /* transform each vertex into VCS */
   for (v = 0; v < data->data.vert_count; v++)
   {
       CopyWPoint(&data->data.rend_vert_list[v], &temp);

       data->data.rend_vert_list[v] = TransformWPoint( &temp, 
							&data->data.view.M);
   }

   /* recompute each polygon's normal for VCS */
   for (p = 0; p < data->data.poly_count; p++)
   {
      ComputeNormalVCS(p, data);
   }
}


/******************************************************************

  PerformProjection() -- This function performs the selected projection
			 on every vertex.

  Notes:

    Parallel

	For parallel projection simply map x to x and y to y and 
	throw away the z coordinate.


    Perspective



******************************************************************/
void
PerformProjection(MyProgram *data)
{
   int v;			/* loop index for vertices */
   matrixType Mort;		/* orthographic xform */
   wpointType temp;


   switch(data->data.view.type)
   {
      case PARALLEL_PROJ:
         Mort = MakeIdentityMatrix();
         Mort.m[2][2] = 0.0;

         for (v = 0; v < data->data.vert_count; v++) 
         {
             CopyWPoint(&data->data.rend_vert_list[v], &temp);

             data->data.rend_vert_list[v] = TransformWPoint( &temp, &Mort);
         }
         break;

      case PERSPECTIVE_PROJ:
         break;

      default:
         break;
   }
} 


/******************************************************************

  PerformBackFaceCulling() -- This function performs back facing 
			surface removal by computing the dot product 
			of the direction of projection (dop) vector and 
			the polygon's surface normal.

  Note:	use dop after transformation into view coordinates.

******************************************************************/
void
PerformBackFaceCulling(MyProgram *data)
{
   int 		p;			
   double 	dot;
   vectorType	dop;

   /* set dop to positive z-axis */
   dop.x = 0.0;  dop.y = 0.0;  dop.z = 1.0;

   for (p = 0; p < data->data.poly_count; p++)
   {
       dot = VecDotproduct(&dop, &data->data.poly_list[p].rend_normal);

       if (dot > 0.0)		/* surface is not visible */
          data->data.poly_list[p].visible = FALSE;
       else			/* surface is visible */
          data->data.poly_list[p].visible = TRUE;
   }
} 


/******************************************************************

  RenderToScreen() -- This function renders the current camera view
		      in the desired rendering mode.

******************************************************************/
void
RenderToScreen(MyProgram *data, matrixType *map_xform)
{
   int p;			/* loop index for polygons */


   switch(data->render_mode)
   {
      case WIRE_REND:		/* draw in wireframe mode */
         /* loop through the polygon list */
         for (p = 0; p < data->data.poly_count; p++) 
         {
            data->data.poly_list[p].visible = TRUE;

            DrawWorldPolygon(ORTH_XY_VIEW,
			&data->data.rend_vert_list[0], 
			&data->data.poly_list[p], 
			map_xform);		
         }
         break;

      case SOLID_REND:		/* draw in solid mode */

         PerformBackFaceCulling(data);

         /* loop through the polygon list */
         for (p = 0; p < data->data.poly_count; p++) 
         {
            DrawWorldPolygon(ORTH_XY_VIEW,
			&data->data.rend_vert_list[0], 
			&data->data.poly_list[p], 
			map_xform);		
         }
         break;

      case SHADE_REND:		/* draw in shading mode */

         PerformBackFaceCulling(data);

         /* loop through the polygon list */
         for (p = 0; p < data->data.poly_count; p++) 
         {
            DrawShadedPolygon(ORTH_XY_VIEW,
			&data->data.rend_vert_list[0], 
			&data->data.poly_list[p], 
			map_xform,
			&data->data.light);		
         }
         break;

      default:
         break;
   }
} 


/******************************************************************************
*  ComputeNormalVCS - computes a specified polygon's normal vector            *
*                                                                             *
*  computes two vectors P2P1 and P2P3 where P1, P2, and P3 are the first      *
*  three vertices of the polygon (counter-clockwise)                          *
*                                                                             *
*  then computes normal as P2P3 X P2P1  i.e.  N = (P3 - P2) X (P1 - P2)       *
*                                                                             *
******************************************************************************/
void
ComputeNormalVCS(int idx, MyProgram *data)
{
   vectorType p1, p2, p3;
   vectorType v1, v2, normal;

   /* transform world points into vectors */
   p1 = WPoint2Vector( 
	&data->data.rend_vert_list[data->data.poly_list[idx].vertices[0]]);
   p2 = WPoint2Vector( 
	&data->data.rend_vert_list[data->data.poly_list[idx].vertices[1]]);
   p3 = WPoint2Vector( 
	&data->data.rend_vert_list[data->data.poly_list[idx].vertices[2]]);

   /* compute vector V1 (P2P1) */
   v1 = VecSub(&p1, &p2);

   /* compute vector V2 (P2P3) */
   v2 = VecSub(&p3, &p2);

   /* compute cross product N = V2 X V1 */
   normal = VecCrossproduct(&v2, &v1);

   /* normalize the result */
   VecNormalize(&normal);

   /* copy into polygon's normal */
   CopyVector(&normal, &data->data.poly_list[idx].rend_normal);
}


/******************************************************************

  DrawCameraView() -- This function draws all polygons seen by the camera. 

******************************************************************/
void
DrawCameraView(VIEW_SCREEN_T viewport, MyProgram *data)
{
   matrixType map_xform;	/* world to view mapping transform */

/*
printf("drawing camera view %d \n", viewport);
*/

   /* copy model vertices to rendered vertices */
   CopyVerticesArray(data);

   /* compute view transform matrix */
   ComputeViewXformMatrix(data);

   /* map world coord vertices into view coord system */
   MapWorldToViewCS(data);

   /* perform specified projection */
   PerformProjection(data);

   /* generate mapping transform for this view */
   MakeMappingXform(viewport, data, &map_xform);

   /* render final image to screen */
   RenderToScreen(data, &map_xform);

} /* end of DrawCameraView() */


/* end of drawgen.c */
