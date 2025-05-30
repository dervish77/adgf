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
         break;

      default:
         break;
   }

   xform = MakeMappingMatrix(worldbounds, screenbounds);

   MatrixCopy(&xform, mapxform);

} /* end of MakeMappingXform() */


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

  NoClipPoint() -- This function performs no clipping.  It merely 
		returns the indicated vertices.

		NOTE:  used only for debug purposes!!

		CAUTION: this function modifies the contents of 
		         point.

******************************************************************/
int
NoClipPoint(VIEW_SCREEN_T viewport, 
		wpointType *point)
{
   wpointType p;		/* temp vertices */

   /* temporarily return unclipped vertices */
   switch(viewport)
   {
      case ORTH_XY_VIEW:
      case SMALL_ORTH_XY_VIEW:
         p.x = point->x;
         p.y = point->y;
         p.z = 1.0;
         break;
      case ORTH_ZY_VIEW:
      case SMALL_ORTH_ZY_VIEW:
         p.x = point->z;
         p.y = point->y;
         p.z = 1.0;
         break;
      case ORTH_XZ_VIEW:
      case SMALL_ORTH_XZ_VIEW:
         p.x = point->x;
         p.y = point->z;
         p.z = 1.0;
         break;
      default:
         break;
   }

   /* return temp values */
   point->x = p.x;
   point->y = p.y;
   point->z = p.z;

   return(TRUE);	/* always accept */
} /* end of NoClipPoint() */


/******************************************************************

  MapPointToViewCS() -- maps world coord point into view coord
			system, and returns 

******************************************************************/
void
MapPointToViewCS(wpointType *point, MyProgram *data)
{
   wpointType	temp;

/*
printf("point was %f, %f, %f  ", point.x, point,y, point.z);
*/

   temp = TransformWPoint( point, &data->data.view.M);

   CopyWPoint(&temp, point);

/*
printf(" is %f, %f, %f\n", point.x, point,y, point.z);
*/
}


/******************************************************************

  DrawParticleSystem -- This function draws the particle at its current 
			position in the current drawing color.

******************************************************************/
void
DrawParticleSystem(VIEW_SCREEN_T viewport, 
			int s, MyProgram *data, matrixType *mapxform)
{
   int p;
   wpointType point;
   int drawn;

   drawn = 0;

   for (p = 0; p < data->data.psys_list[s].count; p++)
   {
      if (data->data.psys_list[s].plist[p].age <= data->data.psys_list[s].plist[p].life)
      {
         CopyWPoint(&data->data.psys_list[s].plist[p].position, &point);

         switch(viewport) 
         {
            case ORTH_XY_VIEW:
            case ORTH_ZY_VIEW:
            case ORTH_XZ_VIEW:
            case SMALL_ORTH_XY_VIEW:
            case SMALL_ORTH_ZY_VIEW:
            case SMALL_ORTH_XZ_VIEW:
               /* if clipped point is accepted */
               if (NoClipPoint(viewport, &point))	
               {
                  DrawParticle(&point, 
			&data->data.psys_list[s].plist[p].color, mapxform);
               }
               break;

            case CAMERA_VIEW:
            case SMALL_CAMERA_VIEW:
               MapPointToViewCS(&point, data);

               point.z = 1.0;

               DrawParticle(&point, 
			&data->data.psys_list[s].plist[p].color, mapxform);

               drawn++;
               break;

            default:
               break;
         }

      }
   }

/*
printf("done drawing system %d, drew %d particles\n", s, drawn);
*/

} 


/******************************************************************

  DrawView() -- This function draws all polygons seen on specified 
		viewport.  

******************************************************************/
void
DrawView(VIEW_SCREEN_T viewport, MyProgram *data)
{
   int i;			/* loop index */
   matrixType map_xform;	/* world to view mapping transform */

/*
printf("drawing view %d\n", viewport);
*/

   /* generate mapping transform for this view */
   MakeMappingXform(viewport, data, &map_xform);

   /* draw each particle system for this view */
   for (i = 0; i < data->data.psys_count; i++)
   {
      DrawParticleSystem(viewport, i, data, &map_xform);
   }

   /* draw camera icon */
   DrawCameraLocation(viewport, data, &map_xform);

} /* end of DrawView() */


/******************************************************************

  DrawCameraView() -- This function draws all polygons seen by the camera. 

******************************************************************/
void
DrawCameraView(VIEW_SCREEN_T viewport, MyProgram *data)
{
   matrixType map_xform;	/* world to view mapping transform */
   int i;

/*
printf("drawing camera view %d\n", viewport);
*/

   /* compute view transform matrix */
   ComputeViewXformMatrix(data);

   /* generate mapping transform for this view */
   MakeMappingXform(viewport, data, &map_xform);

   /* draw each particle system for this view */
   for (i = 0; i < data->data.psys_count; i++)
   {
      DrawParticleSystem(viewport, i, data, &map_xform);
   }

} /* end of DrawCameraView() */




/* end of drawgen.c */
