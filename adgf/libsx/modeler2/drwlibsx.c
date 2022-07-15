/***********************************************************************

   File:  	drwlibsx.c

   Author: 	Brian Lingard

   Date:	9/18/95

  Drawing related functions using the LIBSX library.

***********************************************************************/



/* include necessary files */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "libsx.h"             /* should come first, defines libsx stuff  */

#ifndef _MAIN_H
#include "main.h"              /* where program specific stuff is defined */
#endif

#ifndef _CALLBACK_H
#include "callback.h"          /* prototypes for callback functions       */
#endif


#define GREY2INTENSITY(g)	(( ((float) g) / 255.0) * 1.0)

#define INTENSITY2GREY(i)	((int) (i * 255))

#define RGB_TOL	3		/* rgb tolerance for approximating the color */

#define Kdiff 0.5		/* diffuse reflection coefficient */
#define Kamb 0.5		/* ambient reflection coefficient */

#define Ipoint 1.0		/* point light source intensity */
#define Iamb 1.0		/* ambient light intensity */


/*  extern necessary function calls 
 */
extern pointType MapToView(wpointType vertex, matrixType *mapxform);

extern Widget drawarea_widget;


/*  declare static globals
 */
static COLORMAP_S_T colormap;	/* local color map structure */




/******************************************************************************
*  ClearScreenDisplay - clears all currently drawn viewports                  *
******************************************************************************/
void
ClearScreenDisplay()
{
   ClearDrawArea();             
}


/******************************************************************************
*  ClearColorMap - clears local color map                                     *
******************************************************************************/
void
ClearColorMap()
{
   int c;
  
   for (c = 0; c < MAX_COLOR_MAP; c++)
   {
      colormap.valid[c] = FALSE;
      colormap.indexes[c] = 0;
   }   

   colormap.count = 0;
}


/******************************************************************************
*  SetCurrentColor - sets current drawing color to index specified            *
******************************************************************************/
void
SetCurrentColor(int color_idx)
{
   int idx;

   idx = colormap.indexes[color_idx];

   SetColor(idx);          
}


/******************************************************************************
*  SetDrawColor - sets current drawing color to index specified               *
******************************************************************************/
void
SetDrawColor(int color_idx)
{

   SetColor(color_idx);        
}


/******************************************************************************
*  MatchThisColor - tests if color is close to existing color in color map    *
******************************************************************************/
BOOLEAN_T
MatchThisColor(int c, COLOR_RGB_T color)
{
/*
   if (    ( ((colormap.map[c][R_IDX] - RGB_TOL) < color[R_IDX]) 
		&& (color[R_IDX] < (colormap.map[c][R_IDX] + RGB_TOL)) )

	&& ( ((colormap.map[c][R_IDX] - RGB_TOL) < color[R_IDX]) 
		&& (color[R_IDX] < (colormap.map[c][R_IDX] + RGB_TOL)) )

	&& ( ((colormap.map[c][R_IDX] - RGB_TOL) < color[R_IDX]) 
		&& (color[R_IDX] < (colormap.map[c][R_IDX] + RGB_TOL)) )   )
*/

   if ( (color[R_IDX] == colormap.map[c][R_IDX])
		&& (color[G_IDX] == colormap.map[c][G_IDX])
		&& (color[B_IDX] == colormap.map[c][B_IDX]) )
   {
      return(TRUE);
   }

   return(FALSE);
}


/******************************************************************************
*  AddDrawColor - adds a new color to the color table                         *
******************************************************************************/
void
AddDrawColor(COLOR_RGB_T color)
{
   int 		c, c_index, rgb_index;
   BOOLEAN_T	exists = FALSE;
   
 if ( enable_color_render )
 {

   for (c = 0; c < MAX_COLOR_MAP; c++)
   {
      if (colormap.valid[c])
      {
         if ( MatchThisColor(c, color) )
         {
            exists = TRUE;
            c_index = c;
         }
      }
   }

   if (!exists)
   {
      c_index = colormap.count;
   
      if (c_index >= 0 && c_index < MAX_COLOR_MAP)
      {
         if (c_index > 250) 
         {
            printf("WARNING: exceeded %d colors, c_index = %d\n", 250, c_index);
            SetDrawColor(BLACK);
         }
         else
         {
            rgb_index = GetRGBColor( (int)color[R_IDX], (int)color[G_IDX], 
							(int)color[B_IDX] );
   
            printf("Adding color %d,%d,%d as index %d - rgb %d\n", 
                  color[R_IDX], color[G_IDX], color[B_IDX], c_index, rgb_index);

            colormap.map[c_index][R_IDX] = color[R_IDX];
            colormap.map[c_index][G_IDX] = color[G_IDX];
            colormap.map[c_index][B_IDX] = color[B_IDX];

            colormap.valid[c_index] = TRUE;

            colormap.indexes[c_index] = rgb_index;

            colormap.count++;

         }
      }
      else
      {
         printf("WARNING: allocation of color failed, set to black (c_index was %d)\n", c_index);

         SetDrawColor(BLACK);
      }
   }  

/*   SetDrawColor(c_index); */
   SetCurrentColor(c_index);
 }
 else
 {
   SetDrawColor(GREEN);
 }
}


/******************************************************************************
*  DrawScreenBorders - splits screen into four viewports and labels each      *
******************************************************************************/
void
DrawScreenBorders()
{
   pointType xy_tp, zy_tp, xz_tp, camera_tp;

   SetDrawColor(WHITE);

   DrawLine( 0, InvertY(SCREEN_Y_SIZE / 2), 
		SCREEN_X_SIZE, InvertY(SCREEN_Y_SIZE / 2) );

   DrawLine( (SCREEN_X_SIZE / 2), InvertY(0), 
		(SCREEN_X_SIZE / 2), InvertY(SCREEN_Y_SIZE) );

   xy_tp.x = 10;
   xy_tp.y = (SCREEN_Y_SIZE / 2) + 10;

   zy_tp.x = (SCREEN_X_SIZE / 2) + 10;
   zy_tp.y = (SCREEN_Y_SIZE / 2) + 10;

   xz_tp.x = 10;
   xz_tp.y = 10;

   camera_tp.x = (SCREEN_X_SIZE / 2) + 10;
   camera_tp.y = 10;

   DrawText( "xy view", xy_tp.x, InvertY(xy_tp.y) );
   DrawText( "zy view", zy_tp.x, InvertY(zy_tp.y) );
   DrawText( "xz view", xz_tp.x, InvertY(xz_tp.y) );
   DrawText( "camera view", camera_tp.x, InvertY(camera_tp.y) );
}


/******************************************************************************
*  DrawScreenLabel - labels viewport when viewport is entire screen           *
******************************************************************************/
void
DrawScreenLabel(VIEW_SCREEN_T viewport)
{
   pointType xz_tp;

   SetDrawColor(WHITE);

   xz_tp.x = 10;
   xz_tp.y = 10;

   switch (viewport)
   {
      case ORTH_XY_VIEW:
         DrawText( "xy view", xz_tp.x, InvertY(xz_tp.y) );
         break;
      case ORTH_ZY_VIEW:
         DrawText( "zy view", xz_tp.x, InvertY(xz_tp.y) );
         break;
      case ORTH_XZ_VIEW:
         DrawText( "xz view", xz_tp.x, InvertY(xz_tp.y) );
         break;
      case CAMERA_VIEW:
         DrawText( "camera view", xz_tp.x, InvertY(xz_tp.y) );
         break;
      default:
         break;
   }
}


/******************************************************************************
*  DrawLightLocation - draws an icon at the current light location            *
******************************************************************************/
void
DrawLightLocation(VIEW_SCREEN_T viewport, MyProgram *data, matrixType *mapxform)
{
   wpointType	location;
   pointType 	light_pt;
   int 		text_ht, text_wd;
   XFont 	font;

   SetDrawColor(WHITE);

   font = GetWidgetFont(drawarea_widget);

   text_ht = FontHeight(font);
   text_wd = TextWidth(font, "L");

   switch(viewport)
   {
      case ORTH_XY_VIEW:
      case SMALL_ORTH_XY_VIEW:
         location.x = data->data.light.location.x;
         location.y = data->data.light.location.y;
         location.z = 1.0;
         break;
      case ORTH_ZY_VIEW:
      case SMALL_ORTH_ZY_VIEW:
         location.x = data->data.light.location.z;
         location.y = data->data.light.location.y;
         location.z = 1.0;
         break;
      case ORTH_XZ_VIEW:
      case SMALL_ORTH_XZ_VIEW:
         location.x = data->data.light.location.x;
         location.y = data->data.light.location.z;
         location.z = 1.0;
         break;
      default:
         break;
   }

   light_pt = MapToView(location, mapxform);

   DrawText( "L", light_pt.x, (InvertY(light_pt.y) - (text_ht / 2)) );

   DrawFilledBox( light_pt.x, InvertY(light_pt.y), 3, 3 );
}


/******************************************************************************
*  DrawCameraLocation - draws an icon at the current camera location          *
******************************************************************************/
void
DrawCameraLocation(VIEW_SCREEN_T viewport, MyProgram *data, matrixType *mapxform)
{
   wpointType	eyeloc, lookat;
   pointType 	camera_pt, lap_pt, new_lap_pt;
   int 		text_ht, text_wd;
   XFont 	font;

   SetDrawColor(WHITE);

   font = GetWidgetFont(drawarea_widget);

   text_ht = FontHeight(font);
   text_wd = TextWidth(font, "C");

   switch(viewport)
   {
      case ORTH_XY_VIEW:
      case SMALL_ORTH_XY_VIEW:
         eyeloc.x = data->data.view.eyeloc.x;
         eyeloc.y = data->data.view.eyeloc.y;
         eyeloc.z = 1.0;
         lookat.x = data->data.view.lookat.x;
         lookat.y = data->data.view.lookat.y;
         lookat.z = 1.0;
         break;
      case ORTH_ZY_VIEW:
      case SMALL_ORTH_ZY_VIEW:
         eyeloc.x = data->data.view.eyeloc.z;
         eyeloc.y = data->data.view.eyeloc.y;
         eyeloc.z = 1.0;
         lookat.x = data->data.view.lookat.z;
         lookat.y = data->data.view.lookat.y;
         lookat.z = 1.0;
         break;
      case ORTH_XZ_VIEW:
      case SMALL_ORTH_XZ_VIEW:
         eyeloc.x = data->data.view.eyeloc.x;
         eyeloc.y = data->data.view.eyeloc.z;
         eyeloc.z = 1.0;
         lookat.x = data->data.view.lookat.x;
         lookat.y = data->data.view.lookat.z;
         lookat.z = 1.0;
         break;
      default:
         break;
   }

   camera_pt = MapToView(eyeloc, mapxform);
   lap_pt = MapToView(lookat, mapxform);

   DrawText( "C", camera_pt.x, (InvertY(camera_pt.y) - (text_ht / 2)) );

   DrawFilledBox( camera_pt.x, InvertY(camera_pt.y), 3, 3 );

   new_lap_pt = LerpPoint( &camera_pt, &lap_pt, 0.1 );

   DrawLine( camera_pt.x, InvertY(camera_pt.y), 
				new_lap_pt.x, InvertY(new_lap_pt.y) );

   DrawFilledBox( lap_pt.x, InvertY(lap_pt.y), 3, 3 );

}


/******************************************************************

  DrawWorldLine -- This function draws the specified world coordinate 
		   line on the viewport specified by the mapping 
		   transform. 

******************************************************************/
void
DrawWorldLine(wpointType startv, wpointType endv, matrixType *mapxform)
{
   pointType start_p, end_p;

/*
printf("drawing line\n");
OutputWPoint(stdout, &startv, "from");
OutputWPoint(stdout, &endv, "to");
*/

   start_p = MapToView(startv, mapxform);
   end_p   = MapToView(endv, mapxform);

/*
printf("screen line %d %d - %d %d\n", 
start_p.x, start_p.y, 
end_p.x, end_p.y);
*/

   DrawLine(start_p.x, InvertY(start_p.y), end_p.x, InvertY(end_p.y) );
} 


/******************************************************************

  DrawWorldPolygon() -- This function draws an unshaded polygon from
			if it supposed to be visible.

******************************************************************/
void
DrawWorldPolygon(VIEW_SCREEN_T viewport, 
			wpointType *vertlist, 
			POLYGON_S_T *poly, 
			matrixType *map_xform)
{
   int v;			/* vertex index */
   wpointType sv, ev;		/* start vertex and end vertex */

   /* draw only if this polygon is visible */
   if (poly->visible) 
   {
      /* set current color to this polygon's color */
      AddDrawColor(poly->color);

      /* for all vertices of this polygon */
      for (v = 0; v < poly->num_verts; v++) 
      {
         CopyWPoint(&vertlist[poly->vertices[v]], &sv);

         if ( v < (poly->num_verts - 1) )
         {
            CopyWPoint(&vertlist[poly->vertices[v+1]], &ev);
         }
         else
         {
            CopyWPoint(&vertlist[poly->vertices[0]], &ev);
         }

         /* if clipped line is accepted */
         if (NoClipEdge(viewport, &sv, &ev))	
         {
            DrawWorldLine(sv, ev, map_xform);	/* draw the line */
         }
      }
   }
} /* end of DrawWorldPolygon() */


/******************************************************************

  ComputeLightVector() -- This function computes the vector L from
			a point on a surface to the light source.

******************************************************************/
vectorType
ComputeLightVector(wpointType *point, 	/* point on surface */
		   LIGHT_S_T *light)	/* light falling on point */
{
   vectorType pointvec, lightvec, tempvec;

   switch(light->type)
   {
      case AMB_LIGHT:
         lightvec.x = 0.0;
         lightvec.y = 0.0;
         lightvec.z = 0.0;
         break;

      case POINT_LIGHT:
      case SPOT_LIGHT:
         /* create light source vector -- points toward light source */
         pointvec = WPoint2Vector( point );
         lightvec = VecSub( &light->location, &pointvec );
         VecNormalize( &lightvec );
         break;

      case INFIN_LIGHT:
         tempvec = VecReflection( &light->direction );
         CopyVector( &tempvec, &lightvec );
         VecNormalize( &lightvec );
         break;
   }

   return(lightvec);
} /* end of ComputeLightVector() */


/******************************************************************

  ComputeIntensity() -- This function computes the intensity of the
			diffuse reflection given a surface normal N
			and the vector L using:


	I = Iamb * Kamb * Olamb(i) + Ipoint * Kdiff * Olamb(i) * (N dot L)

        where i = 0, 1, 2

	assumes	monochromatic light but possibly colored objects
	if want grey scales, set Olambda to 1.0

******************************************************************/
void
ComputeIntensity(vectorType *normal, 	/* normal of surface */
		LIGHT_S_T *light, 	/* light vector from surface */
		COLOR_INT_T color)	/* color components of surface */
{
   COLOR_INT_T 	intensity;
   double 	dot, spot_dot;
   vectorType	refl_L;		/* reflection of light vector */


   switch(light->type)
   {
      case AMB_LIGHT:
         intensity[R_IDX] = (light->intensity * Kamb) * color[R_IDX];
         intensity[G_IDX] = (light->intensity * Kamb) * color[G_IDX];
         intensity[B_IDX] = (light->intensity * Kamb) * color[B_IDX];
         break;

      case POINT_LIGHT:
      case INFIN_LIGHT:
         /* compute N dot L */
         dot = VecDotproduct(normal, &light->L);

         /* intensity of diffuse reflection */
         intensity[R_IDX] = (Iamb * Kamb 
			+ light->intensity * Kdiff * dot) * color[R_IDX];
         intensity[G_IDX] = (Iamb * Kamb 
			+ light->intensity * Kdiff * dot) * color[G_IDX];
         intensity[B_IDX] = (Iamb * Kamb 
			+ light->intensity * Kdiff * dot) * color[B_IDX];
         break;

      case SPOT_LIGHT:
         refl_L = VecReflection(&light->L);

         spot_dot = VecDotproduct(&light->direction, &refl_L);

         if ( spot_dot >= cos(DEG2RADS(light->spot_size / 2)) )
         {
            dot = VecDotproduct(normal, &light->L);

            intensity[R_IDX] = (Iamb * Kamb 
			+ light->intensity * Kdiff * dot) * color[R_IDX];
            intensity[G_IDX] = (Iamb * Kamb 
			+ light->intensity * Kdiff * dot) * color[G_IDX];
            intensity[B_IDX] = (Iamb * Kamb 
			+ light->intensity * Kdiff * dot) * color[B_IDX];
         }
         else
         {
            intensity[R_IDX] = Iamb * Kamb * color[R_IDX];
            intensity[G_IDX] = Iamb * Kamb * color[G_IDX];
            intensity[B_IDX] = Iamb * Kamb * color[B_IDX];
         }
         break;
   }

   /* clamp intensty to max of 1.0 */
   if (intensity[R_IDX] > 1.0) intensity[R_IDX] = 1.0;
   if (intensity[G_IDX] > 1.0) intensity[G_IDX] = 1.0;
   if (intensity[B_IDX] > 1.0) intensity[B_IDX] = 1.0;

   /* copy intensity values back into color */
   color[R_IDX] = intensity[R_IDX];
   color[G_IDX] = intensity[G_IDX];
   color[B_IDX] = intensity[B_IDX];

} /* end of ComputeIntensity() */


/******************************************************************

  ComputeColor() -- This function computes the actual color given a 
			base color at the specified point using lighting 
			equations.

  NOTE:	currently only supports flat shading!!

******************************************************************/
void
ComputeColor(wpointType *point, 	/* point on surface */
		vectorType *normal,	/* normal at point on surface */
		COLOR_RGB_T src_color, 	/* color of surface */
		LIGHT_S_T *lighting,	/* light falling on surface */
		COLOR_RGB_T ret_color) 	/* new color of surface */
{
   vectorType 	lightvec;	/* vector pointing to light */
   COLOR_INT_T	int_color;	/* intensity based color of surface */


   switch (lighting->shading)
   {
      case FLAT_SHADE:
         lightvec = ComputeLightVector(point, lighting);

         CopyVector( &lightvec, &lighting->L );

         int_color[R_IDX] = GREY2INTENSITY( src_color[R_IDX] );
         int_color[G_IDX] = GREY2INTENSITY( src_color[G_IDX] );
         int_color[B_IDX] = GREY2INTENSITY( src_color[B_IDX] );

         ComputeIntensity( normal, lighting, int_color );

         ret_color[R_IDX] = INTENSITY2GREY( int_color[R_IDX] );
         ret_color[G_IDX] = INTENSITY2GREY( int_color[G_IDX] );
         ret_color[B_IDX] = INTENSITY2GREY( int_color[B_IDX] );

         break;

      case GOURAUD_SHADE:
         break;

      case PHONG_SHADE:
         break;

      default:
         ret_color[R_IDX] = src_color[R_IDX];
         ret_color[G_IDX] = src_color[G_IDX];
         ret_color[B_IDX] = src_color[B_IDX];
         break;
   }
}


/******************************************************************

  DrawShadedPolygon() -- This function draws a shaded polygon from
			if it supposed to be visible.

  NOTE:	currently only supports flat shading!!

******************************************************************/
void
DrawShadedPolygon(VIEW_SCREEN_T viewport, 
			wpointType *vertlist, 
			POLYGON_S_T *poly, 
			matrixType *map_xform,
			LIGHT_S_T *lighting)
{
   int v;			/* vertex index */
   COLOR_RGB_T	color;		/* computed color of polygon */

   wpointType	vertex;		/* polygon vertex */
   pointType	point;		/* point mapped into screen */
   XPoint	pointlist[SIZE_OF_POLY];	/* array of poly vertices */


   /* draw only if this polygon is visible */
   if (poly->visible) 
   {
      ComputeColor( &vertlist[poly->vertices[0]], 
				&poly->normal, 
				poly->color, 
				lighting,
				color );

      /* set current color to this polygon's color */
      AddDrawColor(color);

      /* for all vertices of this polygon */
      for (v = 0; v < poly->num_verts; v++) 
      {
         CopyWPoint( &vertlist[poly->vertices[v]], &vertex );
         vertex.z = 1.0;

         point = MapToView(vertex, map_xform);

         pointlist[v].x = point.x;
         pointlist[v].y = InvertY(point.y);  
      }

      DrawFilledPolygon( &pointlist[0], poly->num_verts );
   }

} /* end of DrawShadedPolygon() */


/* end of drwlibsx.c */
