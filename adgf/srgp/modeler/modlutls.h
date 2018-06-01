/*****************************************************************

   A set of functions used by 3D_model1.c to generate 3D solid 
   primitives.

   Author:    Brian Lingard

   File:      modlutls.c

   Revision:
      2  11/03/94  added computation of normal vectors
      1  10/16/94  modified to use transforms to build solids
      0  10/10/94  originated

   Functions contained in this file:
	GenRectSolid(), GenCylinder(), GenPrism(), 
	CopyVertex(), CopyEdge(), CopyPolygon()

******************************************************************/


#define MAX_CIRCLE_SIDES 20


/******************************************************************

  GenRectSolid() - This function generates a rectangular solid 
		based upon a center vector, a scaling vector, and
		a rotation axis and angle.  The rectangular solid 
		is built by applying a scaling transform, a rotation
		transform, and finally a translation transform to a
		unit cube which has been pre-defined.

		Rectanglar solids will produce 8 vertices, 18
		edges, and 12 triangles.  Rectangles are assumed
		to be initially oriented with all sides parallel to 
		the x, y and z axes. 

******************************************************************/
int 
GenRectSolid(center, scaling, axis, angle, color)
   vertexType center;
   vertexType scaling;
   char axis;
   double angle;
   int color;
{
   int start_v_index;
   int start_e_index;
   int start_p_index;
   int v, e, p;			/* loop indices */

   matrixType *translate_xform;
   matrixType *scale_xform;
   matrixType *rotate_xform;


   /* save current list indices as starting points */
   start_v_index = curr_v_index;
   start_e_index = curr_e_index;
   start_p_index = curr_p_index;

   /* check if too many vertices */
   if ((curr_v_index + NUM_RECT_VERTS) <= MAX_VERTS) {

     /* copy unit cube's vertices to current vertex list */
     for (v = 0; v < NUM_RECT_VERTS; v++) { 
        CopyVertex(v, unit_cube.verts, curr_v_index, vertex_list);
        curr_v_index++;
     }
   }
   else {
      sprintf(format,"TranslateObjects: too many vertices");
      ErrPrint(format, 8);
   }

   /* check if too many edges */
   if ((curr_e_index + NUM_RECT_EDGES) <= MAX_EDGES) {

     /* copy unit cube's edges to current edge list */
     for (e = 0; e < NUM_RECT_EDGES; e++) { 
        CopyEdge(e, unit_cube.edges, curr_e_index, edge_list, start_v_index);
        curr_e_index++;
     }
   }
   else {
      sprintf(format,"TranslateObjects: too many edges");
      ErrPrint(format, 9); 
   }

   /* check if too many polygons */
   if ((curr_p_index + NUM_RECT_POLYS) <= MAX_POLYS) {

      /* copy unit cube's polygons to current polygon list */
      for (p = 0; p < NUM_RECT_POLYS; p++) { 
         CopyPolygon(p, unit_cube.polys, curr_p_index, 
                              polygon_list, start_e_index, start_v_index);
         curr_p_index++;
      }
   }
   else {
      sprintf(format,"TranslateObjects: too many polygons");
      ErrPrint(format, 10);
   }

   /* scale this primitive to desired size */
   scale_xform = MakeScaleXform(scaling.x, scaling.y, scaling.z);
   for (v = start_v_index; v < (start_v_index + NUM_RECT_VERTS); v++)
      XformVertex(v, scale_xform); 
 
   /* rotate this primitive by desired amount about desired axis */
   if (axis != 'n') {
      rotate_xform = MakeRotateXform(axis, angle);
      for (v = start_v_index; v < (start_v_index + NUM_RECT_VERTS); v++)
         XformVertex(v, rotate_xform); 
   }

   /* translate center of primitive to desired center */
   translate_xform = MakeTransXform(center.x, center.y, center.z);
   for (v = start_v_index; v < (start_v_index + NUM_RECT_VERTS); v++)
      XformVertex(v, translate_xform); 

   /* compute normals of primitive's polygons -- and set color */
   for (p = start_p_index; p < (start_p_index + NUM_RECT_POLYS); p++)
      ComputeNormal(p, color);

   return(0);
} /* end of GenRectSolid() */


/******************************************************************

  GenCylinder() - This function initially generates a cylindrical 
		solid based upon the radius of the circular
		surface, the number of sides of the cylindrical
		surface, and the length of the cylinder.  The initial
		cylinder is oriented so that its lengthwise axis is 
		coincident with the z-axis.  

		The function applies a scaling transform to scale it
		to the desired length, then a rotation transform to 
		the cylinder's vertices, and then applies a 
		translation transform to move the center to the 
		desired location.

		Cylindrical solids are parameterized by how many
		sides the circular surface consist of and hence 
		is approximated by a many sided polygon.  If the
		number of sides is N, then a cylindrical solid 
		will produce 2N+2 vertices, 6N edges, and 
		4N triangles.  It is assumed that N is even.

		It is assumed that the cylinder is oriented such 
		that the length of the cylinder is parallel with 
		the z axis.  The circular surface lies parallel 
		with x,y plane.

******************************************************************/
int 
GenCylinder(center, scaling, axis, angle, color)
   vertexType center;
   vertexType scaling;
   char axis;
   double angle;
   int color;
{
   int start_v_index;	/* starting vertex index */
   int start_e_index;	/* starting edge index */
   int start_p_index;	/* starting polygon index */
   int i, v, p;		/* other loop indicies */

   double r, ns, l;	/* radius, num sides, length */
   double delta_l;	/* displacement along length */

   matrixType *translate_xform;
   matrixType *rotate_xform;

   vertexType circle_points[MAX_CIRCLE_SIDES];


   /* extract scaling info */
   r = scaling.x;	/* radius */
   ns = scaling.y;	/* number of sides N */
   l = scaling.z;	/* length along z-axis */

   if (ns > MAX_CIRCLE_SIDES) {
      fprintf(stderr, "GenCylinder: too many sides\n");
      exit(1);
   }

   /* save current list indices as starting points */
   start_v_index = curr_v_index;
   start_e_index = curr_e_index;
   start_p_index = curr_p_index;

   /* calculate displacement along length */
   delta_l = l / 2;

   /* check if too many vertices */
   if ((curr_v_index + ((2 * ns) + 2)) <= MAX_VERTS) {

      /* calculate circle points */
      CalcCirclePoints(circle_points, r, ns);

      /* set front surface vertices */
      vertex_list[curr_v_index].x = 0;		/* vertex 1 */
      vertex_list[curr_v_index].y = 0;
      vertex_list[curr_v_index].z = -delta_l;
      curr_v_index++;

      for (i = 0; i < ns; i++) {		/* vertices 2 to N+1 */
         vertex_list[curr_v_index].x = circle_points[i].x;
         vertex_list[curr_v_index].y = circle_points[i].y;
         vertex_list[curr_v_index].z = -delta_l;
         curr_v_index++;
      }

      /* set back surface vertices */
      vertex_list[curr_v_index].x = 0;		/* vertex N+2 */
      vertex_list[curr_v_index].y = 0;
      vertex_list[curr_v_index].z = delta_l;
      curr_v_index++;

      for (i = 0; i < ns; i++) {		/* vertices N+3 to 2N+2 */
         vertex_list[curr_v_index].x = circle_points[i].x;
         vertex_list[curr_v_index].y = circle_points[i].y;
         vertex_list[curr_v_index].z = delta_l;
         curr_v_index++;
      }

   }
   else {
      sprintf(format,"TranslateObjects: too many vertices");
      ErrPrint(format, 8);
   }

   /* check if too many edges */
   if ((curr_e_index + (6 * ns)) <= MAX_EDGES) {

      /* make edges 1 to N */
      for (i = 1; i <= ns; i++) {
         edge_list[curr_e_index].sv = start_v_index;	 /* vertex 1 */
         edge_list[curr_e_index].ev = start_v_index + i; /* vertex 2 to N+1 */
         curr_e_index++;
      }

      /* make edges N+1 to 2N */
      for (i = 1; i <= ns; i++) {
         edge_list[curr_e_index].sv = start_v_index + i;
         if (i == ns)
            edge_list[curr_e_index].ev = start_v_index + 1;
         else
            edge_list[curr_e_index].ev = start_v_index + i + 1;
         curr_e_index++;
      }

      /* make edges 2N+1 to 3N */
      for (i = 1; i <= ns; i++) {
         edge_list[curr_e_index].sv = start_v_index + ns + 1;	 /* vertex N+2 */
         edge_list[curr_e_index].ev = start_v_index + ns + 1 + i; /* vertex N+3 to 2N */
         curr_e_index++;
      }

      /* make edges 3N+1 to 4N */
      for (i = 1; i <= ns; i++) {
         edge_list[curr_e_index].sv = start_v_index + ns + 1 + i;
         if (i == ns)
            edge_list[curr_e_index].ev = start_v_index + ns + 2;
         else
            edge_list[curr_e_index].ev = start_v_index + ns + 2 + i;
         curr_e_index++;
      }

      /* make edges 4N+1 to 5N -- along z-axis */
      for (i = 1; i <= ns; i++) {
         edge_list[curr_e_index].sv = start_v_index + i;
         edge_list[curr_e_index].ev = start_v_index + ns + 1 + i;
         curr_e_index++;
      }

      /* make edges 5N+1 to 6N -- diagonals along z-axis */
      for (i = 1; i <= ns; i++) {
         edge_list[curr_e_index].sv = start_v_index + i;
         if (i == ns)
            edge_list[curr_e_index].ev = start_v_index + ns + 2;
         else
            edge_list[curr_e_index].ev = start_v_index + ns + 2 + i;
         curr_e_index++;
      }

   }
   else {
      sprintf(format,"TranslateObjects: too many edges");
      ErrPrint(format, 9); 
   }

   /* check if too many polygons */
   if ((curr_p_index + (4 * ns)) <= MAX_POLYS) {

      /* make polygons 1 to N */
      for (i = 0; i < ns; i++) {
         polygon_list[curr_p_index].edge_list[0] = start_e_index + i;
         if (i == (ns - 1))
            polygon_list[curr_p_index].edge_list[1] = start_e_index;
         else
            polygon_list[curr_p_index].edge_list[1] = start_e_index + 1 + i;
         polygon_list[curr_p_index].edge_list[2] = start_e_index + ns + i;

         if (i == (ns - 1))
            polygon_list[curr_p_index].vert_list[0] = start_v_index + 1;
         else
            polygon_list[curr_p_index].vert_list[0] = start_v_index + i + 2;
         polygon_list[curr_p_index].vert_list[1] = start_v_index;
         polygon_list[curr_p_index].vert_list[2] = start_v_index + i + 1;
         curr_p_index++;
      }

      /* make polygons N+1 to 2N */
      for (i = 0; i < ns; i++) {
         polygon_list[curr_p_index].edge_list[0] = start_e_index + 2*ns + i;
         if (i == (ns - 1))
            polygon_list[curr_p_index].edge_list[1] = start_e_index + 2*ns;
         else
            polygon_list[curr_p_index].edge_list[1] = start_e_index + 2*ns + 1 + i;
         polygon_list[curr_p_index].edge_list[2] = start_e_index + 2*ns + ns + i;
                
         polygon_list[curr_p_index].vert_list[0] = start_v_index + ns + 2 + i;
         polygon_list[curr_p_index].vert_list[1] = start_v_index + ns + 1;
         if (i == (ns - 1))
            polygon_list[curr_p_index].vert_list[2] = start_v_index + ns + 2;
         else
            polygon_list[curr_p_index].vert_list[2] = start_v_index + ns + 3 + i;
         curr_p_index++;
      }

      /* make polygons 2N+1 to 3N */
      for (i = 0; i < ns; i++) {
         polygon_list[curr_p_index].edge_list[0] = start_e_index + 4*ns + i;
         polygon_list[curr_p_index].edge_list[1] = start_e_index + 5*ns + i;
         polygon_list[curr_p_index].edge_list[2] = start_e_index + 3*ns + i;

         polygon_list[curr_p_index].vert_list[0] = start_v_index + i + 1;
         polygon_list[curr_p_index].vert_list[1] = start_v_index + i + ns + 2;
         if (i == (ns - 1))
            polygon_list[curr_p_index].vert_list[2] = start_v_index + ns + 2;
         else
            polygon_list[curr_p_index].vert_list[2] = start_v_index + i + ns + 3;
         curr_p_index++;
      }

      /* make polygons 3N+1 to 4N */
      for (i = 0; i < ns; i++) {
         polygon_list[curr_p_index].edge_list[0] = start_e_index + 5*ns + i;
         if (i == (ns - 1))
            polygon_list[curr_p_index].edge_list[1] = start_e_index + 4*ns;
         else
            polygon_list[curr_p_index].edge_list[1] = start_e_index + 4*ns + 1 + i;
         polygon_list[curr_p_index].edge_list[2] = start_e_index + ns + i;

         if (i == (ns - 1)) {
           polygon_list[curr_p_index].vert_list[0] = start_v_index + ns + 2;
           polygon_list[curr_p_index].vert_list[1] = start_v_index + 1;
         } 
         else {
           polygon_list[curr_p_index].vert_list[0] = start_v_index + i + ns + 3;
           polygon_list[curr_p_index].vert_list[1] = start_v_index + i + 2;
         }
         polygon_list[curr_p_index].vert_list[2] = start_v_index + i + 1;
         curr_p_index++;
      }

       /* set other fields of polygon list data */
      for (i = start_p_index; i < (start_p_index + 4*ns); i++) {
         polygon_list[i].num_edges = 3; 
         polygon_list[i].color = DEFCOLOR; 
         polygon_list[i].normal.x = 0.0; 
         polygon_list[i].normal.y = 0.0; 
         polygon_list[i].normal.z = 0.0; 
      }

   }
   else {
      sprintf(format,"TranslateObjects: too many polygons");
      ErrPrint(format, 10);
   }

   /* rotate this primitive by desired amount about desired axis */
   if (axis != 'n') {
      rotate_xform = MakeRotateXform(axis, angle);
      for (v = start_v_index; v < (start_v_index + 2*ns + 2); v++)
         XformVertex(v, rotate_xform); 
   }

   /* translate center of primitive to desired center */
   translate_xform = MakeTransXform(center.x, center.y, center.z);
   for (v = start_v_index; v < (start_v_index + 2*ns + 2); v++)
      XformVertex(v, translate_xform); 

   /* compute normals of primitive's polygons -- and set color */
   for (p = start_p_index; p < (start_p_index + 4*ns); p++)
      ComputeNormal(p, color);

   return(0);
} /* end of GenCylinder() */


/******************************************************************

   GenPrism() - This function generates a right triangular prism 
		based upon a center vector, a scaling vector, and
		a rotation axis and angle.  The right triangular solid 
		is built by applying a scaling transform, a rotation
		transform, and finally applying a translation transform 
		to a unit prism which has been pre-defined.

		Right trianglar prism will produce 6 vertices, 
		12 edges, and 8 triangles.  Right trianglar prisms 
		are assumed to be initially oriented such that the
		non-sloped sides are parallel to the x, y and z axes.

******************************************************************/
int 
GenPrism(center, scaling, axis, angle, color)
   vertexType center;
   vertexType scaling;
   char axis;
   double angle;
   int color;
{
   int start_v_index;
   int start_e_index;
   int start_p_index;
   int v, e, p;			/* loop indices */

   matrixType *translate_xform;
   matrixType *scale_xform;
   matrixType *rotate_xform;


   /* save current list indices as starting points */
   start_v_index = curr_v_index;
   start_e_index = curr_e_index;
   start_p_index = curr_p_index;


   /* check if too many vertices */
   if ((curr_v_index + NUM_PRSM_VERTS) <= MAX_VERTS) {

     /* copy unit prism's vertices to current vertex list */
     for (v = 0; v < NUM_PRSM_VERTS; v++) { 
        CopyVertex(v, unit_prism.verts, curr_v_index, vertex_list);
        curr_v_index++;
     }
   }
   else {
      sprintf(format,"TranslateObjects: too many vertices");
      ErrPrint(format, 8);
   }

   /* check if too many edges */
   if ((curr_e_index + NUM_PRSM_EDGES) <= MAX_EDGES) {

     /* copy unit prism's edges to current edge list */
     for (e = 0; e < NUM_PRSM_EDGES; e++) { 
        CopyEdge(e, unit_prism.edges, curr_e_index, edge_list, start_v_index);
        curr_e_index++;
     }
   }
   else {
      sprintf(format,"TranslateObjects: too many edges");
      ErrPrint(format, 9); 
   }

   /* check if too many polygons */
   if ((curr_p_index + NUM_PRSM_POLYS) <= MAX_POLYS) {

     /* copy unit prism's polygons to current polygon list */
     for (p = 0; p < NUM_PRSM_POLYS; p++) { 
        CopyPolygon(p, unit_prism.polys, curr_p_index, 
                             polygon_list, start_e_index, start_v_index);
        curr_p_index++;
     }
   }
   else {
      sprintf(format,"TranslateObjects: too many polygons");
      ErrPrint(format, 10);
   }

   /* scale this primitive to desired size */
   scale_xform = MakeScaleXform(scaling.x, scaling.y, scaling.z);
   for (v = start_v_index; v < (start_v_index + NUM_PRSM_VERTS); v++)
      XformVertex(v, scale_xform); 
 
   /* rotate this primitive by desired amount about desired axis */
   if (axis != 'n') {
      rotate_xform = MakeRotateXform(axis, angle);
      for (v = start_v_index; v < (start_v_index + NUM_PRSM_VERTS); v++)
         XformVertex(v, rotate_xform); 
   }

   /* translate center of primitive to desired center */
   translate_xform = MakeTransXform(center.x, center.y, center.z);
   for (v = start_v_index; v < (start_v_index + NUM_PRSM_VERTS); v++)
      XformVertex(v, translate_xform); 

   /* compute normals of primitive's polygons -- and set color */
   for (p = start_p_index; p < (start_p_index + NUM_PRSM_POLYS); p++)
      ComputeNormal(p, color);

   return(0);
} /* end of GenPrism() */


/******************************************************************

  CopyVertex() - This function copies a vertex from one array to another.

******************************************************************/
int
CopyVertex(src_i, src_list, dest_i, dest_list)
   int src_i;
   vertexType src_list[];
   int dest_i;
   vertexType dest_list[];
{
   /* copy each coordinate */
   dest_list[dest_i].x = src_list[src_i].x;
   dest_list[dest_i].y = src_list[src_i].y;
   dest_list[dest_i].z = src_list[src_i].z;

   return(0);
} /* end of CopyVertex() */


/******************************************************************

  CopyEdge() - This function copies an edge from one array to another.
		The endpoint vertex indices are copied relative to the 
		start of this primitive's vertices.

******************************************************************/
int
CopyEdge(src_i, src_list, dest_i, dest_list, start_vert_index)
   int src_i;
   edgeType src_list[];
   int dest_i;
   edgeType dest_list[];
   int start_vert_index;
{

   /* copy the relative start and end vertex indices */
   dest_list[dest_i].sv = start_vert_index + src_list[src_i].sv;
   dest_list[dest_i].ev = start_vert_index + src_list[src_i].ev;

   return(0);
} /* end of CopyEdge() */


/******************************************************************

  CopyPolygon() - This function copies a polygon from one array to 
		another.  The edge indices are copied relative to 
		the start of this primitive's edges.  The vertex indices
		are also copied relative to the start of this 
		primitive's vertices.

******************************************************************/
int
CopyPolygon(src_i, src_list, dest_i, dest_list, start_edge_index, start_vert_index)
   int src_i;
   polygonType src_list[];
   int dest_i;
   polygonType dest_list[];
   int start_edge_index;
   int start_vert_index;
{
   int i;	/* edge list index */

   /* copy this polygon's edge count */
   dest_list[dest_i].num_edges = src_list[src_i].num_edges;

   /* copy this polygon's edge links */
   for (i = 0; i < SIZE_OF_POLY; i++) {
      dest_list[dest_i].edge_list[i] = start_edge_index 
                                          + src_list[src_i].edge_list[i];
   }

   /* copy this polygon's vertex indices */
   for (i = 0; i < 3; i++) {
      dest_list[dest_i].vert_list[i] = start_vert_index 
                                          + src_list[src_i].vert_list[i];
   }

   /* copy misc info */
   dest_list[dest_i].color = src_list[src_i].color;
   dest_list[dest_i].normal.x = src_list[src_i].normal.x;
   dest_list[dest_i].normal.y = src_list[src_i].normal.y;
   dest_list[dest_i].normal.z = src_list[src_i].normal.z;

   return(0);
} /* end of CopyPolygon() */


/* end of file modlutls.h */
