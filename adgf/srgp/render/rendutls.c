/* 

   A collection of rendering routines used by Render1.c, Render2.c
   and Render3.c

   File:   rendutls.h

   Author: Brian Lingard

   Rev history:   
	1 - 12/13/94  updated for phase4
	0 - 10/11/94  originated

   NOTE:

	The functions in this file expect certain global constants
	to have been defined.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "render.h"

/* #define DEBUG 1
*/

/* external globals */
extern int vertex_count;
extern int edge_count;
extern int polygon_count;

extern vertexType vertex_list[];
extern edgeType edge_list[];
extern polygonType polygon_list[];
extern matrixType HG_coord[];

extern renderType render_mode;
extern projectType projection_mode;
extern normalizeType norm_flag;

extern viewrangeType view_data[];	/* used for three simul. views */
extern viewdataType view;		/* used for para & pers views */
extern viewplaneType vplane;		/* view plane information */

extern FILE *debugfile;

/* local static globals */
static int saved_vertex_count=0;
static int saved_edge_count=0;
static int saved_polygon_count=0;

static vertexType saved_vertex_list[MAX_VERTS];
static edgeType saved_edge_list[MAX_EDGES];
static polygonType saved_polygon_list[MAX_POLYS];


/******************************************************************

  ComputeViewplaneInfo() -- This function computes the information
			needed to define the view plane for the up 
			coming projection.  These computations are 
			consistent with those illustrated in 
			Chapter 6 of the text book.  Compensations 
			are made for use of the left-handed coordinate
			system.

      Definitions:
	PRP = EYE location
	LAP = Look At Point
	DOP = LAP - PRP  (direction of projection)
	VPN = DOP  (they are parallel and use VCS as left handed)
	vpd = mag of DOP  (view plane distance)
	n = VPN / ||VPN||  (unit vector)
	u = (VUP X VPN) / ||VUP X VPN||  (unit vector)
	v = n X u  (unit vector)
	M = R(v) * R(u) * R(n) * T(-VRP)

******************************************************************/
int
ComputeViewplaneInfo()
{
   matrixType *R;	  /* pointer to rotation matrix */
   matrixType *T;	  /* pointer to translation matrix */
   matrixType *M;	  /* pointer to view map matrix */
   matrixType *DOP;	  /* pointer to temp DOP vector */
   matrixType *N;	  /* temp N vector */
   matrixType *U;	  /* temp U vector */

   double mag_vpn, mag_u; /* magnitudes of VPN vector and U vector */

   int i;

   matrixType *MakeVector();
   matrixType *MakeIdentityMatrix();
   matrixType *MakeTransXform();
   int CopyMatrix();
   int CrossProduct();
   int MultMatrix();
   int OutputViewplaneInfo();
   double GetVecMag();

#ifdef DEBUG
   printf("... computing view plane info\n");
#endif

   /* copy view plane window bounds from view info */
   vplane.umin = view.vbx.min;
   vplane.umax = view.vbx.max;
   vplane.vmin = view.vby.min;
   vplane.vmax = view.vby.max;
   vplane.F = view.vbz.min;
   vplane.B = view.vbz.max;

   /* copy view reference point from view file info */
   vplane.VRP.x = view.vrp.x;
   vplane.VRP.y = view.vrp.y;
   vplane.VRP.z = view.vrp.z;

   /* copy view up vector from view file info */
   vplane.VUP.rows = 3;
   vplane.VUP.cols = 1;
   vplane.VUP.array[0][0] = view.vup.x;
   vplane.VUP.array[1][0] = view.vup.y;
   vplane.VUP.array[2][0] = view.vup.z;

   /* set projection reference point to eye location */
   vplane.PRP.x = view.eyeloc.x;
   vplane.PRP.y = view.eyeloc.y;
   vplane.PRP.z = view.eyeloc.z;

   /* set center of window to look at point */
   vplane.CW.x = view.lap.x;
   vplane.CW.y = view.lap.y;
   vplane.CW.z = view.lap.z;

   /* compute direction of projection (DOP) by CW - PRP */
   DOP = MakeVector(vplane.PRP, vplane.CW);
   CopyMatrix(DOP, &vplane.DOP);

   /* compute distance to view plane - ||DOP|| */
   vplane.vpd = (float) GetVecMag(vplane.DOP);

   /* compute view plane normal (VPN) - same as DOP */
   CopyMatrix(&vplane.DOP, &vplane.VPN);

   /* compute normalized n axis - VPN / ||VPN|| */
   mag_vpn = GetVecMag(vplane.VPN);
   N = MakeIdentityMatrix();
   CopyMatrix(&vplane.VPN, N);
   N->rows = 3;
   N->cols = 1;
   N->array[0][0] /= mag_vpn;
   N->array[1][0] /= mag_vpn;
   N->array[2][0] /= mag_vpn;
   CopyMatrix(N, &vplane.Nvector);

   /* compute normalized u axis -   VUP X VPN   */
   /*                              -----------  */
   /*                             ||VUP X VPN|| */
   U = MakeIdentityMatrix();
   CrossProduct(&vplane.VUP, &vplane.VPN, U);
   CopyMatrix(U, &vplane.Uvector);
   mag_u = GetVecMag(vplane.Uvector);
   vplane.Uvector.array[0][0] /= mag_u;
   vplane.Uvector.array[1][0] /= mag_u;
   vplane.Uvector.array[2][0] /= mag_u;

   /* compute normalized v axis - n x u */
   CrossProduct(&vplane.Nvector, &vplane.Uvector, &vplane.Vvector);

   /* compute translation matrix T - (-VRP)*/
   T = MakeTransXform(-vplane.VRP.x, -vplane.VRP.y, -vplane.VRP.z);

   /* compute rotation matrix R */
   R = MakeIdentityMatrix();
   for (i = 0; i < 3; i++)
      R->array[0][i] = vplane.Uvector.array[i][0]; /* copy u axis vector */

   for (i = 0; i < 3; i++)
      R->array[1][i] = vplane.Vvector.array[i][0]; /* copy v axis vector */

   for (i = 0; i < 3; i++)
      R->array[2][i] = vplane.Nvector.array[i][0]; /* copy n axis vector */

   /* compute view transformation matrix - M = R * T  */
   M = MakeIdentityMatrix();
   MultMatrix(R, T, M);
   CopyMatrix(M, &vplane.M);

#ifdef DEBUG   
   OutputViewplaneInfo();
#endif

   return(0);
} /* end of ComputeViewplaneInfo() */


/******************************************************************

  MapWorldToViewCS() -- This function maps the object specified in 
			world coordinate system into the view 
			coordinate system.  This function applies 
			the view mapping transform M to all vertices
			of the 3D object (vertex_list array).  This 
			function also applies the view mapping 
			transform to all the normals of the polygons.

******************************************************************/
int
MapWorldToViewCS()
{
   int v, p;			/* loop index for vertices */
   vertexType norm;		/* temp normal vector */

   int Copy3D_HG();
   int XformHGcoord();
   vertexType XformPoint();

#ifdef DEBUG
   printf("... mapping world to view coords\n");
#endif

   /* copy 3D coords into HG coords */
   Copy3D_HG();			

   /* map world coord vertices into view coord vertices */
   for (v = 0; v < vertex_count; v++)
      XformHGcoord(v, &vplane.M);
   
   /* map world coord normals into view coord normals */
   for (p = 0; p < polygon_count; p++) {
      norm.x = polygon_list[p].normal.x;
      norm.y = polygon_list[p].normal.y;
      norm.z = polygon_list[p].normal.z;
      polygon_list[p].normal = XformPoint(norm, &vplane.M);
   }

   return(0);
} /* end of MapWorldToViewCS() */


/******************************************************************

  ApplyNormalizingXform() -- This function applies the appropriate 
			normalizing transformation on the object to 
			to force into canonical view volume.
			A parallel projection does TBD.
			The perspective projection assumes that the 
			view plane is at z = d.
      Definitions:
	Npar = Spar * Tpar

	Nper = Sper * T(-PRP)

******************************************************************/
int
ApplyNormalizingXform()
{
   int v;			/* loop index for vertices */
   float tparx, tpary, tparz;	/* translation parms for parallel */
   float sparx, spary, sparz;	/* scaling parms for parallel */
   matrixType *Tpar;		/* translation xform for parallel */
   matrixType *Spar;		/* scaling xform for parallel */

   matrixType *Tper;		/* translation xform for perspective */
   float sperx, spery, sperz;	/* scaling parms for perspective */
   matrixType *Sper;		/* scaling xform for perspective */
   vertexType vrp_p;		/* VRP prime */
   float zmin, zproj;

   matrixType *MakeTransXform();
   matrixType *MakeScaleXform();
   int XformHGcoord();
   vertexType XformPoint();

#ifdef DEBUG
   int OutputHGcoord();

   printf("... applying normalizing\n");
#endif

   /* perform normalizing operations for specified projection type */
   switch(projection_mode) {
      case PARALLEL:
         /* make translation xform to move view volume */
         tparx = -(vplane.umax + vplane.umin) / 2;
         tpary = -(vplane.vmax + vplane.vmin) / 2;
         tparz = -vplane.F;
         Tpar = MakeTransXform(tparx, tpary, tparz);

         /* make scaling xform to make canonical view volume */
         sparx = 2 / (vplane.umax - vplane.umin);
         spary = 2 / (vplane.vmax - vplane.vmin);
         sparz = 1 / (vplane.B - vplane.F);
         Spar = MakeScaleXform(sparx, spary, sparz);

         /* xform each vertex */
         for (v = 0; v < vertex_count; v++) {
            XformHGcoord(v, Tpar);
            XformHGcoord(v, Spar);
         }
#ifdef DEBUG
         OutputHGcoord(debugfile,"HG coords after Spar * Tpar");
#endif
         break;

      case PERSPECTIVE:
         /* make translation xform to move PRP to origin */
/*         Tper = MakeTransXform(-vplane.PRP.x, -vplane.PRP.y, -vplane.PRP.z);*/
         Tper = MakeTransXform(0.0, 0.0, vplane.vpd);

         /* make scaling xform to make canonical view volume */
         vrp_p = XformPoint(vplane.VRP, Tper);	/* translate view ref pt */
         sperx = (2 * vrp_p.z) / ((vplane.umax - vplane.umin) * (vrp_p.z + vplane.B));
         spery = (2 * vrp_p.z) / ((vplane.vmax - vplane.vmin) * (vrp_p.z + vplane.B));
         sperz = 1 / (vrp_p.z + vplane.B);
         Sper = MakeScaleXform(sperx, spery, sperz);

         if (norm_flag == NORMALIZE_VIEW_VOLUME) {  /* scale as well */
            zmin = (vrp_p.z + vplane.F) / (vrp_p.z + vplane.B);
            zproj = vrp_p.z / (vrp_p.z + vplane.B);
         }
         else {					    /* don't scale */
            zmin = vrp_p.z + vplane.F;
            zproj = vrp_p.z;
         }

         vplane.scale_per.x = sperx;
         vplane.scale_per.y = spery;
         vplane.scale_per.z = sperz;
         vplane.zmin = zmin;
         vplane.vpd = zproj;	/* set to new distance to view plane */

         /* xform each vertex */
         for (v = 0; v < vertex_count; v++)
            XformHGcoord(v, Tper);

         for (v = 0; v < vertex_count; v++) {
            if (norm_flag == NORMALIZE_VIEW_VOLUME)
               XformHGcoord(v, Sper);
         }
         break;

      default:
         fprintf(stderr, "ApplyProjectionXform: unknown projection mode\n");
         exit(1);
   }

   return(0);
} /* end of ApplyNormalizingXform() */


/******************************************************************

  ClipViewVolume() -- This function clips the 3D coords within the 
			canonical view volume appropriate to the 
			type of projection desired.  This is only 
			performed upon normalize view coordinates.

      Parallel view volume:
	x = -1, x = 1, y = -1, y = 1, z = 0, z = 1

      Perspective View volume:
	x = -z, x = z, y = -z, y = z, z = zmin, z = 1

******************************************************************/
int
ClipViewVolume()
{
   int e, v;			/* loop index */
   vertexType sv, ev;		/* start and end vertex of edge */
   int accept_flag;		/* zero indicates trivial reject */   
   matrixType *Mper2par;	/* xform per vv to par vv */

   int CopyHG_3D();
   int Copy3D_HG();
   int Clip3DEdge();
   matrixType *MakeIdentityMatrix();
   int XformVertex();

#ifdef DEBUG
   printf("... clipping\n");
#endif

   if (norm_flag == NORMALIZE_VIEW_VOLUME) {

      CopyHG_3D();		/* convert back to 3D coords */

      switch(projection_mode) {
         case PARALLEL:
            /* clip all edges in 3D */
            for (e = 0; e < edge_count; e++) {
               accept_flag = Clip3DEdge(e, &sv, &ev);
            }
            break;

         case PERSPECTIVE:
            Mper2par = MakeIdentityMatrix();
            Mper2par->array[2][2] = 1 / (1 + vplane.zmin);
            Mper2par->array[2][3] = (-vplane.zmin) / (1 + vplane.zmin);
            Mper2par->array[3][2] = -1;
            Mper2par->array[3][3] = 0;

            /* transform perspective view vol into parallel view vol */
            for (v = 0; v < vertex_count; v++) 
               XformVertex(v, Mper2par);

            /* clip all edges in 3D */
            for (e = 0; e < edge_count; e++) {
               accept_flag = Clip3DEdge(e, &sv, &ev);
            }
            break;

         default:
            fprintf(stderr, "ClipViewVolume: unknown projection mode\n");
            exit(1);
      }

      Copy3D_HG();		/* copy 3D coords into HG coords */

   }
   else {	/* don't clip, just accept them all */
      for (e = 0; e < edge_count; e++)
         edge_list[e].accept = 1;
   }

   return(0);
} /* end of ClipViewVolume() */


/******************************************************************

  PerformProjection() -- This function performs the selected projection
			xform on every HG coordinates.

******************************************************************/
int
PerformProjection()
{
   int v;			/* loop index for vertices */
   matrixType *Mper;		/* perspective xform */
   matrixType *Mort;		/* orthographic xform */

   matrixType *MakeIdentityMatrix();
   int XformHGcoord();

#ifdef DEBUG
   printf("... performing projection = %d\n", projection_mode);
#endif

   switch(projection_mode) {
      case PARALLEL:
         Mort = MakeIdentityMatrix();
         Mort->array[2][2] = 0.0;

         for (v = 0; v < vertex_count; v++) {
            XformHGcoord(v, Mort);
         }
         break;

      case PERSPECTIVE:
         Mper = MakeIdentityMatrix();
         Mper->array[3][2] = 1 / vplane.vpd;
         if (norm_flag == NORMALIZE_VIEW_VOLUME)	/* vplane @ z=d */
            Mper->array[3][3] = 0.0;
         else						/* vplane @ z=0 */
            Mper->array[2][2] = 0.0;

         for (v = 0; v < vertex_count; v++) {
            XformHGcoord(v, Mper);
         }
         break;

      default:
         fprintf(stderr, "PerformProjection: unknown projection mode\n");
         exit(1);
   }

   return(0);
} /* end of PerformProjection() */


/******************************************************************

  RenderToScreen() -- This function transforms the 3D object into 
		viewport coordinates for display.  If coords were
		normalized, the 3D viewport is resized accordingly 
		before creating mapping xform.  All lines
		are then drawn on the display.

******************************************************************/
int
RenderToScreen()
{
   int p, e, v;			/* loop index */
   int accept_flag;
   vertexType sv, ev;		/* start vertex and end vertex */
   matrixType *map_xform;	/* viewport mapping xform */

   int CopyHG_3D();
   matrixType *MakeMappingXform();
   int NoClip3DEdge();
   int DrawWorldLine();
   int PerformBackFaceCulling();
   int DrawPolygon();
   int InitColorTable();
   int DrawShadedPolygon();

#ifdef DEBUG
   printf("... rendering to screen\n");
#endif 

   /* convert back to 3D coords */
   CopyHG_3D();			

#ifdef DEBUG
   OutputVertices(debugfile, "final 3D coords");
#endif

   /* generate mapping transform for this view */
   if (norm_flag == NORMALIZE_VIEW_VOLUME) {
      vplane.umin = -1.0;	/* set window to canon. view volume */
      vplane.umax = 1.0;
      vplane.vmin = -1.0;
      vplane.vmax = 1.0;
   }
   map_xform = MakeMappingXform(CAMERA);
   
   /* render to screen based on render mode selected */
   switch(render_mode) {
      case WIRE_REND:	/* draw in wireframe mode */
         /* loop through the edge list */
         for (e = 0; e < edge_count; e++) {
            accept_flag = NoClip3DEdge(e, &sv, &ev);  /* get sv and ev */
            if (accept_flag)
               DrawWorldLine(sv, ev, map_xform);      /* draw this edge */
         }
         break;

      case SOLD_REND:	/* draw in unshaded solids */
         PerformBackFaceCulling();

         /* for all polygons on global list */
         for (p = 0; p < polygon_count; p++)
            DrawPolygon(p, map_xform);	/* draw on screen if visible */
         break;

      case FULL_REND:	/* draw in shaded solids */
         PerformBackFaceCulling();

         InitColorTable();   /* initialize device independant color table */

         /* for all polygons on global list */
         for (p = 0; p < polygon_count; p++)
            DrawShadedPolygon(p, map_xform);
         break;

      default:
         fprintf(stderr, "RenderToScreen: Unknown render mode\n");
         exit(1);
   }

   return(0);
} /* end of RenderToScreen() */


/******************************************************************

  RenderCameraView() -- This function renders the model from the 
			camera's viewpoint as specified in the 
			view file.  The functions are treated as a
			rendering pipeline.

******************************************************************/
int
RenderCameraView()
{
   int PerformDepthSort();


   ComputeViewplaneInfo();	/* compute VCS and M */

   MapWorldToViewCS();		/* convert WCS into VCS */

   if (render_mode == FULL_REND)
      PerformDepthSort();	/* sort polygons far to near */

   if (norm_flag == NORMALIZE_VIEW_VOLUME)
      ApplyNormalizingXform();	/* apply normalizing xform to all verts */

   ClipViewVolume();		/* clip in 3D against view volume */

   PerformProjection();		/* perform projection */

   RenderToScreen();		/* render object on display */

   return(0);
} /* end of RenderCameraView() */


/******************************************************************

  SaveVertexList() -- saves the original vertex list array for
	later reuse.

******************************************************************/
int
SaveVertexList()
{
   int v;

   for (v = 0; v < vertex_count; v++) {
      saved_vertex_list[v].x = vertex_list[v].x;
      saved_vertex_list[v].y = vertex_list[v].y;
      saved_vertex_list[v].z = vertex_list[v].z;
   }

   saved_vertex_count = vertex_count;

   return(0);
} /* end of SaveVertexList() */


/*****************************************************************

  RestoreVertexList() -- restores the original vertex list array

*****************************************************************/
int
RestoreVertexList()
{
   int v;

   for (v = 0; v < saved_vertex_count; v++) {
      vertex_list[v].x = saved_vertex_list[v].x;
      vertex_list[v].y = saved_vertex_list[v].y;
      vertex_list[v].z = saved_vertex_list[v].z;
   }

   vertex_count = saved_vertex_count;

   return(0);
} /* end of RestoreVertexList() */


/******************************************************************

  OutputVertices() -- Outputs vertex list array to file descriptor. 

******************************************************************/
int
OutputVertices(outfile, label)
   FILE *outfile;
   char *label;
{
   int v;

   fprintf(outfile, "%s:\n", label);
   for (v = 0; v < vertex_count; v++) {
      fprintf(outfile, "%f %f %f\n", vertex_list[v].x, 
				vertex_list[v].y, vertex_list[v].z);
   }
   fprintf(outfile, "\n");

   return(0);
} /* end of OutputVertices() */


/* end of file rendutls.h */
