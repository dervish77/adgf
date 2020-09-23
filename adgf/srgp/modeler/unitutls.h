 /*****************************************************************

   A set functions to generate unit-sized solids.

   Author:    Brian Lingard

   File:      unitutls.c

   Revision:
	1  11/03/94  added ComputeNormal()
	0  10/16/94  originated

   Functions contained in this file:
	BuildUnitCube(), BuildUnitPrism(), 
	CalcCirclePoints(), ComputeNormal() 

******************************************************************/


/******************************************************************

  BuildUnitCube() - This function generates a cubic solid which is 
		one unit in all three dimensions, and is centered
		on the origin.

		This solid has 8 vertices, 18 edges, and 12 triangles. 

		The unit cube's components are stored in a global
		structure called unit_cube.

******************************************************************/
int 
BuildUnitCube()
{
   int v_index = 0;
   int e_index = 0;
   int p_index = 0;
   double delta = 0.5;

   /**** define vertices ****/
   /* calc vertex 1 */
   unit_cube.verts[v_index].x = -delta;
   unit_cube.verts[v_index].y = -delta;
   unit_cube.verts[v_index].z = -delta;
   v_index++;

   /* calc vertex 2 */
   unit_cube.verts[v_index].x = delta;
   unit_cube.verts[v_index].y = -delta;
   unit_cube.verts[v_index].z = -delta;
   v_index++;

   /* calc vertex 3 */
   unit_cube.verts[v_index].x = -delta;
   unit_cube.verts[v_index].y = delta;
   unit_cube.verts[v_index].z = -delta;
   v_index++;

   /* calc vertex 4 */
   unit_cube.verts[v_index].x = delta;
   unit_cube.verts[v_index].y = delta;
   unit_cube.verts[v_index].z = -delta;
   v_index++;

   /* calc vertex 5 */
   unit_cube.verts[v_index].x = -delta;
   unit_cube.verts[v_index].y = -delta;
   unit_cube.verts[v_index].z = delta;
   v_index++;

   /* calc vertex 6 */
   unit_cube.verts[v_index].x = delta;
   unit_cube.verts[v_index].y = -delta;
   unit_cube.verts[v_index].z = delta;
   v_index++;

   /* calc vertex 7 */
   unit_cube.verts[v_index].x = -delta;
   unit_cube.verts[v_index].y = delta;
   unit_cube.verts[v_index].z = delta;
   v_index++;

   /* calc vertex 8 */
   unit_cube.verts[v_index].x = delta;
   unit_cube.verts[v_index].y = delta;
   unit_cube.verts[v_index].z = delta;
   v_index++;


   /**** link up edges ****/
   /* calc edge 1 */
   unit_cube.edges[e_index].sv = 0; /* vertex 1 */
   unit_cube.edges[e_index].ev = 1; /* vertex 2 */
   e_index++;

   /* calc edge 2 */
   unit_cube.edges[e_index].sv = 0; /* vertex 1 */
   unit_cube.edges[e_index].ev = 2; /* vertex 3 */
   e_index++;

   /* calc edge 3 */
   unit_cube.edges[e_index].sv = 1; /* vertex 2 */
   unit_cube.edges[e_index].ev = 3; /* vertex 4 */
   e_index++;

   /* calc edge 4 */
   unit_cube.edges[e_index].sv = 2; /* vertex 3 */
   unit_cube.edges[e_index].ev = 3; /* vertex 4 */
   e_index++;

   /* calc edge 5 */
   unit_cube.edges[e_index].sv = 4; /* vertex 5 */
   unit_cube.edges[e_index].ev = 5; /* vertex 6 */
   e_index++;

   /* calc edge 6 */
   unit_cube.edges[e_index].sv = 4; /* vertex 5 */
   unit_cube.edges[e_index].ev = 6; /* vertex 7 */
   e_index++;

   /* calc edge 7 */
   unit_cube.edges[e_index].sv = 5; /* vertex 6 */
   unit_cube.edges[e_index].ev = 7; /* vertex 8 */
   e_index++;

   /* calc edge 8 */
   unit_cube.edges[e_index].sv = 6; /* vertex 7 */
   unit_cube.edges[e_index].ev = 7; /* vertex 8 */
   e_index++;

   /* calc edge 9 */
   unit_cube.edges[e_index].sv = 0; /* vertex 1 */
   unit_cube.edges[e_index].ev = 4; /* vertex 5 */
   e_index++;

   /* calc edge 10 */
   unit_cube.edges[e_index].sv = 1; /* vertex 2 */
   unit_cube.edges[e_index].ev = 5; /* vertex 6 */
   e_index++;

   /* calc edge 11 */
   unit_cube.edges[e_index].sv = 2; /* vertex 3 */
   unit_cube.edges[e_index].ev = 6; /* vertex 7 */
   e_index++;

   /* calc edge 12 */
   unit_cube.edges[e_index].sv = 3; /* vertex 4 */
   unit_cube.edges[e_index].ev = 7; /* vertex 8 */
   e_index++;

   /* calc edge 13 -- diagonal */
   unit_cube.edges[e_index].sv = 0; /* vertex 1 */
   unit_cube.edges[e_index].ev = 3; /* vertex 4 */
   e_index++;

   /* calc edge 14 -- diagonal */
   unit_cube.edges[e_index].sv = 5; /* vertex 6 */
   unit_cube.edges[e_index].ev = 6; /* vertex 7 */
   e_index++;

   /* calc edge 15 -- diagonal */
   unit_cube.edges[e_index].sv = 4; /* vertex 5 */
   unit_cube.edges[e_index].ev = 2; /* vertex 3 */
   e_index++;

   /* calc edge 16 -- diagonal */
   unit_cube.edges[e_index].sv = 1; /* vertex 2 */
   unit_cube.edges[e_index].ev = 7; /* vertex 8 */
   e_index++;

   /* calc edge 17 -- diagonal */
   unit_cube.edges[e_index].sv = 4; /* vertex 5 */
   unit_cube.edges[e_index].ev = 1; /* vertex 2 */
   e_index++;

   /* calc edge 18 -- diagonal */
   unit_cube.edges[e_index].sv = 2; /* vertex 3 */
   unit_cube.edges[e_index].ev = 7; /* vertex 8 */
   e_index++;


   /**** link up edges to form polygons (triangles) ****/
   /* calc polygon 1 - edges 1, 3 and 13 */
   unit_cube.polys[p_index].edge_list[0] = 0;
   unit_cube.polys[p_index].edge_list[1] = 2;
   unit_cube.polys[p_index].edge_list[2] = 12;
   unit_cube.polys[p_index].vert_list[0] = 0;
   unit_cube.polys[p_index].vert_list[1] = 1;
   unit_cube.polys[p_index].vert_list[2] = 3;
   p_index++;

   /* calc polygon 2 - edges 4, 2 and 13 */
   unit_cube.polys[p_index].edge_list[0] = 3;
   unit_cube.polys[p_index].edge_list[1] = 1;
   unit_cube.polys[p_index].edge_list[2] = 12;
   unit_cube.polys[p_index].vert_list[0] = 3;
   unit_cube.polys[p_index].vert_list[1] = 2;
   unit_cube.polys[p_index].vert_list[2] = 0;
   p_index++;

   /* calc polygon 3 - edges 5, 6 and 14 */
   unit_cube.polys[p_index].edge_list[0] = 4;
   unit_cube.polys[p_index].edge_list[1] = 5;
   unit_cube.polys[p_index].edge_list[2] = 13;
   unit_cube.polys[p_index].vert_list[0] = 5;
   unit_cube.polys[p_index].vert_list[1] = 4;
   unit_cube.polys[p_index].vert_list[2] = 6;
   p_index++;

   /* calc polygon 4 - edges 14, 7 and 8 */
   unit_cube.polys[p_index].edge_list[0] = 13;
   unit_cube.polys[p_index].edge_list[1] = 6;
   unit_cube.polys[p_index].edge_list[2] = 7;
   unit_cube.polys[p_index].vert_list[0] = 6;
   unit_cube.polys[p_index].vert_list[1] = 7;
   unit_cube.polys[p_index].vert_list[2] = 5;
   p_index++;

   /* calc polygon 5 - edges 15, 9 and 2 */
   unit_cube.polys[p_index].edge_list[0] = 14;
   unit_cube.polys[p_index].edge_list[1] = 8;
   unit_cube.polys[p_index].edge_list[2] = 1;
   unit_cube.polys[p_index].vert_list[0] = 4;
   unit_cube.polys[p_index].vert_list[1] = 0;
   unit_cube.polys[p_index].vert_list[2] = 2;
   p_index++;

   /* calc polygon 6 - edges 11, 15 and 6 */
   unit_cube.polys[p_index].edge_list[0] = 10;
   unit_cube.polys[p_index].edge_list[1] = 14;
   unit_cube.polys[p_index].edge_list[2] = 5;
   unit_cube.polys[p_index].vert_list[0] = 2;
   unit_cube.polys[p_index].vert_list[1] = 6;
   unit_cube.polys[p_index].vert_list[2] = 4;
   p_index++;

   /* calc polygon 7 - edges 16, 7 and 10 */
   unit_cube.polys[p_index].edge_list[0] = 15;
   unit_cube.polys[p_index].edge_list[1] = 6;
   unit_cube.polys[p_index].edge_list[2] = 9;
   unit_cube.polys[p_index].vert_list[0] = 1;
   unit_cube.polys[p_index].vert_list[1] = 5;
   unit_cube.polys[p_index].vert_list[2] = 7;
   p_index++;

   /* calc polygon 8 - edges 16, 3 and 12 */
   unit_cube.polys[p_index].edge_list[0] = 15;
   unit_cube.polys[p_index].edge_list[1] = 2;
   unit_cube.polys[p_index].edge_list[2] = 11;
   unit_cube.polys[p_index].vert_list[0] = 7;
   unit_cube.polys[p_index].vert_list[1] = 3;
   unit_cube.polys[p_index].vert_list[2] = 1;
   p_index++;

   /* calc polygon 9 - edges 17, 10 and 5 */
   unit_cube.polys[p_index].edge_list[0] = 16;
   unit_cube.polys[p_index].edge_list[1] = 9;
   unit_cube.polys[p_index].edge_list[2] = 4;
   unit_cube.polys[p_index].vert_list[0] = 4;
   unit_cube.polys[p_index].vert_list[1] = 5;
   unit_cube.polys[p_index].vert_list[2] = 1;
   p_index++;

   /* calc polygon 10 - edges 17, 9 and 1 */
   unit_cube.polys[p_index].edge_list[0] = 16;
   unit_cube.polys[p_index].edge_list[1] = 8;
   unit_cube.polys[p_index].edge_list[2] = 0;
   unit_cube.polys[p_index].vert_list[0] = 1;
   unit_cube.polys[p_index].vert_list[1] = 0;
   unit_cube.polys[p_index].vert_list[2] = 4;
   p_index++;

   /* calc polygon 11 - edges 18, 12 and 4 */
   unit_cube.polys[p_index].edge_list[0] = 17;
   unit_cube.polys[p_index].edge_list[1] = 11;
   unit_cube.polys[p_index].edge_list[2] = 3;
   unit_cube.polys[p_index].vert_list[0] = 2;
   unit_cube.polys[p_index].vert_list[1] = 3;
   unit_cube.polys[p_index].vert_list[2] = 7;
   p_index++;

   /* calc polygon 12 - edges 18, 11 and 8 */
   unit_cube.polys[p_index].edge_list[0] = 17;
   unit_cube.polys[p_index].edge_list[1] = 10;
   unit_cube.polys[p_index].edge_list[2] = 7;
   unit_cube.polys[p_index].vert_list[0] = 7;
   unit_cube.polys[p_index].vert_list[1] = 6;
   unit_cube.polys[p_index].vert_list[2] = 2;
   p_index++;


   /**** initialize remaining fields in polygon array ****/
   for (p_index = 0; p_index < NUM_RECT_POLYS; p_index++) {
      unit_cube.polys[p_index].num_edges = SIZE_OF_POLY;
      unit_cube.polys[p_index].color = DEFCOLOR;
      unit_cube.polys[p_index].normal.x = 0.0;
      unit_cube.polys[p_index].normal.y = 0.0;
      unit_cube.polys[p_index].normal.z = 0.0;
   }


   return(0);
} /* end of BuildUnitCube() */


/******************************************************************

  BuildUnitPrism() - This function generates a right triangular prism
		solid with a height, base and length of one unit.  
		The solid is centered such that the sloping side passes
		through the origin.

		Right trianglar prism will produce 6 vertices, 
		12 edges, and 8 triangles.  Right trianglar prisms 
		are assumed to be oriented such that non-sloped sides
		are parallel to the x, y and z axes.

******************************************************************/
int 
BuildUnitPrism()
{
   int v_index = 0;
   int e_index = 0;
   int p_index = 0;
   double delta = 0.5;

   /**** define vertices ****/
   /* calc vertex 1 */
   unit_prism.verts[v_index].x = -delta;
   unit_prism.verts[v_index].y = -delta;
   unit_prism.verts[v_index].z = -delta;
   v_index++;

   /* calc vertex 2 */
   unit_prism.verts[v_index].x = delta;
   unit_prism.verts[v_index].y = -delta;
   unit_prism.verts[v_index].z = -delta;
   v_index++;

   /* calc vertex 3 */
   unit_prism.verts[v_index].x = -delta;
   unit_prism.verts[v_index].y = delta;
   unit_prism.verts[v_index].z = -delta;
   v_index++;

   /* calc vertex 4 */
   unit_prism.verts[v_index].x = -delta;
   unit_prism.verts[v_index].y = -delta;
   unit_prism.verts[v_index].z = delta;
   v_index++;

   /* calc vertex 5 */
   unit_prism.verts[v_index].x = delta;
   unit_prism.verts[v_index].y = -delta;
   unit_prism.verts[v_index].z = delta;
   v_index++;

   /* calc vertex 6 */
   unit_prism.verts[v_index].x = -delta;
   unit_prism.verts[v_index].y = delta;
   unit_prism.verts[v_index].z = delta;
   v_index++;


   /**** link up edges ****/
   /* calc edge 1 */
   unit_prism.edges[e_index].sv = 0; /* vertex 1 */
   unit_prism.edges[e_index].ev = 1; /* vertex 2 */
   e_index++;

   /* calc edge 2 */
   unit_prism.edges[e_index].sv = 0; /* vertex 1 */
   unit_prism.edges[e_index].ev = 2; /* vertex 3 */
   e_index++;

   /* calc edge 3 */
   unit_prism.edges[e_index].sv = 2; /* vertex 3 */
   unit_prism.edges[e_index].ev = 1; /* vertex 2 */
   e_index++;

   /* calc edge 4 */
   unit_prism.edges[e_index].sv = 3; /* vertex 4 */
   unit_prism.edges[e_index].ev = 4; /* vertex 5 */
   e_index++;

   /* calc edge 5 */
   unit_prism.edges[e_index].sv = 3; /* vertex 4 */
   unit_prism.edges[e_index].ev = 5; /* vertex 6 */
   e_index++;

   /* calc edge 6 */
   unit_prism.edges[e_index].sv = 5; /* vertex 6 */
   unit_prism.edges[e_index].ev = 4; /* vertex 5 */
   e_index++;

   /* calc edge 7 */
   unit_prism.edges[e_index].sv = 0; /* vertex 1 */
   unit_prism.edges[e_index].ev = 3; /* vertex 4 */
   e_index++;

   /* calc edge 8 */
   unit_prism.edges[e_index].sv = 1; /* vertex 2 */
   unit_prism.edges[e_index].ev = 4; /* vertex 5 */
   e_index++;

   /* calc edge 9 */
   unit_prism.edges[e_index].sv = 2; /* vertex 3 */
   unit_prism.edges[e_index].ev = 5; /* vertex 6 */
   e_index++;

   /* calc edge 10 -- diagonal */
   unit_prism.edges[e_index].sv = 1; /* vertex 2 */
   unit_prism.edges[e_index].ev = 5; /* vertex 6 */
   e_index++;

   /* calc edge 11 -- diagonal */
   unit_prism.edges[e_index].sv = 3; /* vertex 4 */
   unit_prism.edges[e_index].ev = 2; /* vertex 3 */
   e_index++;

   /* calc edge 12 -- diagonal */
   unit_prism.edges[e_index].sv = 3; /* vertex 4 */
   unit_prism.edges[e_index].ev = 1; /* vertex 2 */
   e_index++;


   /**** link up edges to form polygons (triangles) ****/
   /* calc polygon 1 - edges 3, 2 and 1 */
   unit_prism.polys[p_index].edge_list[0] = 2;
   unit_prism.polys[p_index].edge_list[1] = 1;
   unit_prism.polys[p_index].edge_list[2] = 0;
   unit_prism.polys[p_index].vert_list[0] = 2;
   unit_prism.polys[p_index].vert_list[1] = 0;
   unit_prism.polys[p_index].vert_list[2] = 1;
   p_index++;

   /* calc polygon 2 - edges 6, 5 and 4 */
   unit_prism.polys[p_index].edge_list[0] = 5;
   unit_prism.polys[p_index].edge_list[1] = 4;
   unit_prism.polys[p_index].edge_list[2] = 3;
   unit_prism.polys[p_index].vert_list[0] = 4;
   unit_prism.polys[p_index].vert_list[1] = 3;
   unit_prism.polys[p_index].vert_list[2] = 5;
   p_index++;

   /* calc polygon 3 - edges 11, 2 and 7 */
   unit_prism.polys[p_index].edge_list[0] = 10;
   unit_prism.polys[p_index].edge_list[1] = 1;
   unit_prism.polys[p_index].edge_list[2] = 6;
   unit_prism.polys[p_index].vert_list[0] = 3;
   unit_prism.polys[p_index].vert_list[1] = 0;
   unit_prism.polys[p_index].vert_list[2] = 2;
   p_index++;

   /* calc polygon 4 - edges 11, 5 and 9 */
   unit_prism.polys[p_index].edge_list[0] = 10;
   unit_prism.polys[p_index].edge_list[1] = 4;
   unit_prism.polys[p_index].edge_list[2] = 8;
   unit_prism.polys[p_index].vert_list[0] = 2;
   unit_prism.polys[p_index].vert_list[1] = 5;
   unit_prism.polys[p_index].vert_list[2] = 3;
   p_index++;

   /* calc polygon 5 - edges 12, 8 and 4 */
   unit_prism.polys[p_index].edge_list[0] = 11;
   unit_prism.polys[p_index].edge_list[1] = 7;
   unit_prism.polys[p_index].edge_list[2] = 3;
   unit_prism.polys[p_index].vert_list[0] = 3;
   unit_prism.polys[p_index].vert_list[1] = 4;
   unit_prism.polys[p_index].vert_list[2] = 1;
   p_index++;

   /* calc polygon 6 - edges 12, 7 and 1 */
   unit_prism.polys[p_index].edge_list[0] = 11;
   unit_prism.polys[p_index].edge_list[1] = 6;
   unit_prism.polys[p_index].edge_list[2] = 0;
   unit_prism.polys[p_index].vert_list[0] = 1;
   unit_prism.polys[p_index].vert_list[1] = 0;
   unit_prism.polys[p_index].vert_list[2] = 3;
   p_index++;

   /* calc polygon 7 - edges 10, 6 and 8 */
   unit_prism.polys[p_index].edge_list[0] = 9;
   unit_prism.polys[p_index].edge_list[1] = 5;
   unit_prism.polys[p_index].edge_list[2] = 7;
   unit_prism.polys[p_index].vert_list[0] = 1;
   unit_prism.polys[p_index].vert_list[1] = 4;
   unit_prism.polys[p_index].vert_list[2] = 5;
   p_index++;

   /* calc polygon 8 - edges 10, 3 and 9 */
   unit_prism.polys[p_index].edge_list[0] = 9;
   unit_prism.polys[p_index].edge_list[1] = 2;
   unit_prism.polys[p_index].edge_list[2] = 8;
   unit_prism.polys[p_index].vert_list[0] = 5;
   unit_prism.polys[p_index].vert_list[1] = 2;
   unit_prism.polys[p_index].vert_list[2] = 1;
   p_index++;


   /**** initialize remaining fields in polygon array ****/
   for (p_index = 0; p_index < NUM_PRSM_POLYS; p_index++) {
      unit_prism.polys[p_index].num_edges = SIZE_OF_POLY;
      unit_prism.polys[p_index].color = DEFCOLOR;
      unit_prism.polys[p_index].normal.x = 0.0;
      unit_prism.polys[p_index].normal.y = 0.0;
      unit_prism.polys[p_index].normal.z = 0.0;
   }


   return(0);
} /* end of BuildUnitPrism() */


/******************************************************************

  CalcCirclePoints() - This function generates a set of N points which
		lie on a circle of the specified radius(r).

******************************************************************/
int 
CalcCirclePoints(circle_pts, radius, sides)
   vertexType circle_pts[];
   double radius;
   double sides;
{
   int i;			/* loop index */
   double pie_angle;		/* rotation angle to next point */
   matrixType *rotate_xform;	/* rotation transform */

   /* calculate rotation angle to next point */
   pie_angle = 360.0 / sides;

   /* initialize first point on circle */
   circle_pts[0].x = radius;
   circle_pts[0].y = 0.0;
   circle_pts[0].z = 0.0;

   /* create necessary transform for rotating about z-axis */
   rotate_xform = MakeRotateXform('z', pie_angle);

   /* successively generate next circle point from previous circle point */
   for (i = 1; i < sides; i++) {
      
      circle_pts[i] = XformPoint(circle_pts[i-1], rotate_xform);

   } 

   return(0);
} /* end of CalcCirclePoints() */


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
ComputeNormal(p_index, color)
   int p_index;
   int color;
{
   vertexType p1, p2, p3;
   matrixType *vec1, *vec2, *normal;
   double mag;

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

   /* set this polygon's base color */
   polygon_list[p_index].color = color;

   FreeMatrix(vec1);
   FreeMatrix(vec2);
   FreeMatrix(normal);
   return(0);
} /* end of ComputeNormal() */


/* end of file unitutls.h */
