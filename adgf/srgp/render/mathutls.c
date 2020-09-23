/* 

   Description:  collection of transforms and matrix routines

   File:    mathutls.c

   Author:  Brian Lingard

   Rev history:

	0 - 10/14/94 	originated


   NOTE!! -- all matrix calculations and rotations are for a 
		left-handed coordinate system!!!

*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "render.h"

/* external globals */
extern int vertex_count;

extern vertexType vertex_list[];
extern matrixType HG_coord[];


#ifndef PI
  #define PI 3.1415926
#endif


/***************************************************************

  MultMatrix() -- This function multiplies an MxN matrix by 
		an NxP matrix forming an MxP matrix.

		If the N's of each matrix are not equal, the function
		will cause the program to exit on a error.

***************************************************************/ 
int
MultMatrix(matrix1, matrix2, product)
   matrixType *matrix1, *matrix2, *product;
{
   int m, n, p;
   double sum;

   /* setup resultant matrix size */
   product->rows = matrix1->rows;
   product->cols = matrix2->cols;

   /* test if legal multiply operation */
   if (matrix1->cols == matrix2->rows) {

      for (m = 0; m < matrix1->rows; m++) {

         for (p = 0; p < matrix2->cols; p++) {

            /* form resultant element[m][p] */
            sum = 0.0;

            for (n = 0; n < matrix1->cols; n++) {

               sum = sum + (matrix1->array[m][n] * matrix2->array[n][p]);

            }

            product->array[m][p] = sum;
         }
      }
   }
   else {
      fprintf(stderr, "MultMatrix: illegal matrix sizes\n");
      exit(1);
   }

   return(0);
} /* end of MultMatrix() */


/***************************************************************

  AllocMatrix() -- This function allocates memory for a 4x4 matrix
		and returns the pointer to it.

***************************************************************/ 
matrixType
*AllocMatrix()
{
   matrixType *matrix;

   /* allocate memory for one 4x4 matix */
   matrix = (matrixType *) calloc(1, sizeof(matrixType));

   if (matrix == NULL) {
      fprintf(stderr, "AllocMatrix: calloc failed\n");
      exit(1);
   }

   return(matrix);
} /* end of AllocMatrix() */


/***************************************************************

  FreeMatrix() -- This function deallocates memory for a 4x4 matrix.

***************************************************************/ 
int
FreeMatrix(matrix)
   matrixType *matrix;
{
   void free();

   free(matrix);

   return(0);
} /* end of FreeMatrix() */


/***************************************************************

  CopyMatrix() -- This function copies one matrix into another.  
		The source matrix must be the same size as the 
		destination matrix.

***************************************************************/ 
int
CopyMatrix(srcmat, destmat)
   matrixType *srcmat, *destmat;
{
   int r, c;

   destmat->rows = srcmat->rows;
   destmat->cols = srcmat->cols;

   for (r = 0; r < srcmat->rows; r++)
      for (c = 0; c < srcmat->cols; c++)
         destmat->array[r][c] = srcmat->array[r][c];

   return(0);
} /* end of CopyMatrix() */


/***************************************************************

  DotProduct() -- This function computes and returns the dot product
		of two vectors.

***************************************************************/ 
double
DotProduct(vec1, vec2)
   matrixType vec1, vec2;
{
   double result;
   int r;

   result = 0.0;
   for (r = 0; r < 3; r++)
      result = result + vec1.array[r][0] * vec2.array[r][0];

   return(result);
} /* end of DotProduct() */


/***************************************************************

  CrossProduct() -- This function computes the cross product of two
		vectors and stores the results in a third vector 
		pointed to by v3.

***************************************************************/ 
int
CrossProduct(v1, v2, v3)
   matrixType *v1, *v2, *v3;
{
   v3->rows = 3;
   v3->cols = 1;

   v3->array[0][0] = v1->array[1][0] * v2->array[2][0] 
			- v1->array[2][0] * v2->array[1][0];

   v3->array[1][0] = v1->array[2][0] * v2->array[0][0] 
			- v1->array[0][0] * v2->array[2][0];

   v3->array[2][0] = v1->array[0][0] * v2->array[1][0] 
			- v1->array[1][0] * v2->array[0][0];

   return(0);
} /* end of CrossProduct() */


/***************************************************************

  GetVecMag() -- This function computes the magnitude of a 3D vector.

***************************************************************/ 
double
GetVecMag(vec)
   matrixType vec;
{
   double result;

   result = vec.array[0][0] * vec.array[0][0]
		+ vec.array[1][0] * vec.array[1][0]
		+ vec.array[2][0] * vec.array[2][0];

   return(sqrt(result));
} /* end of GetVecMag() */


/***************************************************************

  MakeIdentityMatrix() -- This function builds a 4x4 identity matrix.

***************************************************************/ 
matrixType
*MakeIdentityMatrix()
{
   matrixType *xform;
   int r,c;

   /* allocate memory for a new matrix */
   xform = AllocMatrix();

   xform->rows = MAX_MATRIX_SIZE;
   xform->cols = MAX_MATRIX_SIZE;

   for (r = 0; r < MAX_MATRIX_SIZE; r++) {
      for (c = 0; c < MAX_MATRIX_SIZE; c++) {
         if (r == c)
            xform->array[r][c] = 1;	/* make diagonal one's */
         else
            xform->array[r][c] = 0;
      }
   }

   return(xform);
} /* end of MakeIdentityMatrix() */


/***************************************************************

  MakeVector() -- This function builds a 3D vector from a starting
		vertex and an ending vertex.

***************************************************************/ 
matrixType
*MakeVector(sv, ev)
   vertexType sv, ev;
{
   matrixType *vector;

   vector = AllocMatrix();

   vector->rows = 3;
   vector->cols = 1;

   vector->array[0][0] = ev.x - sv.x;
   vector->array[1][0] = ev.y - sv.y;
   vector->array[2][0] = ev.z - sv.z;

   return(vector);
} /* end of MakeVector() */


/***************************************************************

  MakeTransXform() -- This function builds a 3D translation matrix.

***************************************************************/ 
matrixType
*MakeTransXform(Tx, Ty, Tz)
   double Tx, Ty, Tz;
{
   matrixType *xform;

   /* create identity matrix */
   xform = MakeIdentityMatrix();

   /* insert translation deltas into matrix */
   xform->array[0][3] = Tx;
   xform->array[1][3] = Ty;
   xform->array[2][3] = Tz;

   return(xform);
} /* end of MakeTransXform() */


/***************************************************************

  MakeScaleXform() -- This function builds a 3D scaling matrix.

***************************************************************/ 
matrixType
*MakeScaleXform(Sx, Sy, Sz)
   double Sx, Sy, Sz;
{
   matrixType *xform;

   /* create identity matrix */
   xform = MakeIdentityMatrix();

   /* insert scaling parameters into matrix */
   xform->array[0][0] = Sx;
   xform->array[1][1] = Sy;
   xform->array[2][2] = Sz;

   return(xform);
} /* end of MakeScaleXform() */


/***************************************************************

  MakeRotateXform() -- This function builds a 3D rotation matrix
		for the specified axis of rotation.

***************************************************************/ 
matrixType
*MakeRotateXform(axis, theta)
   char axis;		/* rotation about which axis */
   double theta;	/* angle of rotation in degrees */
{
   matrixType *xform;
   double angle_radians;
   double cosine_theta;	/* cosine of rotation angle */
   double sine_theta;	/* sine of rotation angle */

   /* create identity matrix */
   xform = MakeIdentityMatrix();

   /* convert angle theta from degrees to radians */
   angle_radians = (2 * PI) * (theta / 360);

   /* calculate cosines and sines of angle theta */
   cosine_theta = cos(angle_radians);
   sine_theta = sin(angle_radians);

   /* build rotation xform based on which axis is desired */
   switch(axis) {

      case 'x':	/* about the x-axis */
         xform->array[1][1] = cosine_theta;
         xform->array[1][2] = sine_theta;
         xform->array[2][1] = -1 * sine_theta;
         xform->array[2][2] = cosine_theta;
         break;

      case 'y':	/* about the y-axis */
         xform->array[0][0] = cosine_theta;
         xform->array[0][2] = -1 * sine_theta;
         xform->array[2][0] = sine_theta;
         xform->array[2][2] = cosine_theta;
         break;

      case 'z': /* about the z-axis */
         xform->array[0][0] = cosine_theta;
         xform->array[0][1] = -1 * sine_theta;
         xform->array[1][0] = sine_theta;
         xform->array[1][1] = cosine_theta;
         break;

      default:
         fprintf(stderr, "MakeRotateXform: unknown axis\n");
         exit(1);
         break;
   }

   return(xform);
} /* end of MakeRotateXform() */


/***************************************************************

  MakePerspXform() -- This function builds a 3D perspective matrix.

***************************************************************/ 
matrixType
*MakePerspXform(mode, distance)
   int mode;		/* 0 = viewplane @ z=d, 1 = viewplane @ z=o */
   double distance;	/* distance to viewplane */
{
   matrixType *xform;
   double parameter;

   /* create identity matrix */
   xform = MakeIdentityMatrix();

   /* compute perspective parameter and insert into xform matrix */
   switch(mode) {
      case 0:	/* view plane at z=d */
         parameter = 1 / distance;
         xform->array[3][2] = parameter;  /* assumes along z axis */
         xform->array[3][3] = 0.0;
         break;

      case 1:	/* view plane at z=0 */
         parameter = 1 / distance;
         xform->array[3][2] = parameter;  /* assumes along z axis */
         xform->array[2][2] = 0.0;
         break;

      default:
         fprintf(stderr, "MakePerspXform: unknown mode\n");
         exit(1);
   }

   return(xform);
} /* end of MakePerspXform() */


/***************************************************************

  XformVertex() -- This function applies the specified transform 
		matrix on the vertex point indicated by the index
		into the global vertex list array.

***************************************************************/ 
int
XformVertex(v_index, xform)
   int v_index;
   matrixType *xform;
{
   matrixType point_matrix;
   matrixType new_point;

   /* convert point p into a matrix form */
   point_matrix.rows = 4;
   point_matrix.cols = 1;
   point_matrix.array[0][0] = vertex_list[v_index].x;
   point_matrix.array[1][0] = vertex_list[v_index].y;
   point_matrix.array[2][0] = vertex_list[v_index].z;
   point_matrix.array[3][0] = 1;

   /* apply transform to the point */
   MultMatrix(xform, &point_matrix, &new_point);

   /* copy transformed point back to vertex list array */
   vertex_list[v_index].x = new_point.array[0][0];
   vertex_list[v_index].y = new_point.array[1][0];
   vertex_list[v_index].z = new_point.array[2][0];

   return(0);
} /* end of XformVertex() */


/***************************************************************

  XformPoint() -- This function applies the specified transform 
		matrix a point and returns the transformed point.

***************************************************************/ 
vertexType
XformPoint(p, xform)
   vertexType p;
   matrixType *xform;
{
   matrixType point_matrix;
   matrixType new_point;
   vertexType p_prime;

   /* convert point p into a matrix form */
   point_matrix.rows = 4;
   point_matrix.cols = 1;
   point_matrix.array[0][0] = p.x;
   point_matrix.array[1][0] = p.y;
   point_matrix.array[2][0] = p.z;
   point_matrix.array[3][0] = 1;

   /* apply transform to the point */
   MultMatrix(xform, &point_matrix, &new_point);

   /* convert back into vertex form */
   p_prime.x = new_point.array[0][0];
   p_prime.y = new_point.array[1][0];
   p_prime.z = new_point.array[2][0];

   return(p_prime);
} /* end of XformPoint() */


/***************************************************************

  OutputMatrix() -- This function outputs the specified matrix
			to the file descriptor given.

			Note:  mostly used for debug purposes!!

***************************************************************/ 
int
OutputMatrix(outfile, matrix, label)
   FILE *outfile;
   matrixType *matrix;
   char *label;
{
   int r, c;	/* row and column indices */

   /* output matrix size as 'row space column' */
   fprintf(outfile, "%s:\n", label);

   /* output matrix size as 'row space column' */
   fprintf(outfile, "%d %d\n", matrix->rows, matrix->cols);

   /* output matrix elements by rows and columns */
   for (r = 0; r < matrix->rows; r++) {

      for (c = 0; c < matrix->cols; c++) {

         fprintf(outfile, "%f ", matrix->array[r][c]);

      }
      fprintf(outfile, "\n");
   }
   fprintf(outfile, "\n");	/* extra blank line as separator */

   return(0);
} /* end of OutputMatrix() */


/***************************************************************

  XformHGcoord() -- This function applies the specified transform 
		matrix to the homogeneous coordinate indicated by 
		the index into the HG coord list array.

***************************************************************/ 
int
XformHGcoord(v_index, xform)
   int v_index;
   matrixType *xform;
{
   matrixType new_coord;

   /* apply transform to the HG coordinate */
   MultMatrix(xform, &HG_coord[v_index], &new_coord);

   /* copy transformed point back to vertex list array */
   CopyMatrix(&new_coord, &HG_coord[v_index]);

   return(0);
} /* end of XformHGcoord() */


/***************************************************************

  Copy3D_HG() -- This function copies entire 3D vertex list into
			the HG coord list array.

***************************************************************/ 
int
Copy3D_HG()
{
   int v;

   for (v = 0; v < vertex_count; v++) {
      HG_coord[v].rows = 4;
      HG_coord[v].cols = 1;
      HG_coord[v].array[0][0] = vertex_list[v].x;
      HG_coord[v].array[1][0] = vertex_list[v].y;
      HG_coord[v].array[2][0] = vertex_list[v].z;
      HG_coord[v].array[3][0] = 1.0;
   }

   return(0);
}  /* end of Copy3D_HG() */


/***************************************************************

  CopyHG_3D() -- This function copies the HG coord list array back 
			into the vertex list array converting
			back to 3D coordinates.

***************************************************************/ 
int
CopyHG_3D()
{
   int v;

   for (v = 0; v < vertex_count; v++) {
      vertex_list[v].x = HG_coord[v].array[0][0] / HG_coord[v].array[3][0];
      vertex_list[v].y = HG_coord[v].array[1][0] / HG_coord[v].array[3][0];
      vertex_list[v].z = HG_coord[v].array[2][0] / HG_coord[v].array[3][0];
      /*vertex_list[v].x = HG_coord[v].array[0][0];
      vertex_list[v].y = HG_coord[v].array[1][0];
      vertex_list[v].z = HG_coord[v].array[2][0];*/
   }

   return(0);
}  /* end of CopyHG_3D() */


/***************************************************************

  OutputHGcoord() -- This function outputs the HG coord list
			to the specified file descriptor.

			Note:  mostly used for debug purposes!!

***************************************************************/ 
int
OutputHGcoord(outfile, label)
   FILE *outfile;
   char *label;
{
   int v, i;

   fprintf(outfile, "%s:\n", label);

   for (v = 0; v < vertex_count; v++) {
      for (i = 0; i < HG_coord[v].rows; i++) {
         fprintf(outfile, "%f ", HG_coord[v].array[i][0]);
      }
      fprintf(outfile, "\n");
   }
   fprintf(outfile, "\n");	/* extra blank line as separator */

   return(0);
} /* end of OutputHGcoord() */

/* end of file mathutls.c */
