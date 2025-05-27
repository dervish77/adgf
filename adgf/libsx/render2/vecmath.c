/***********************************************************************

   A set of routines for performing vector and matrix math.

   File:  	vecmath.c	

   Author: 	Brian Lingard

   Date:	4/12/95

***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vecmath.h"


/* 
 * nrand() - normalized rand(), returns floating point random number
 *		between -1.0 and 1.0
 *
 * PARAMETERS
 *
 * RETURNS
 */
float nrand(void)
{
   return(2.0*(rand() / (float)RAND_MAX) - 1.0);
}


/* 
 * nrands() - sinusoid distributed nrand(), returns floating point random 
 *		number between -1.0 and 1.0 in a sinusoidal distribution.
 *
 * PARAMETERS
 *
 * RETURNS
 */
float nrands(void)
{
   return((float)sin(2.0 * PI * nrand()));
}


/* 
 * VecAdd() - adds vector v1 to vector v2 and returns sum vector.
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
vectorType VecAdd(vectorType *v1, vectorType *v2)
{
   vectorType vec;

   vec.x = v1->x + v2->x;
   vec.y = v1->y + v2->y;
   vec.z = v1->z + v2->z;

   return(vec);
}
 

/* 
 * VecSub() - subtracts vector v2 from vector v1 and returns result vector.
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
vectorType VecSub(vectorType *v1, vectorType *v2)
{
   vectorType vec;

   vec.x = v1->x - v2->x;
   vec.y = v1->y - v2->y;
   vec.z = v1->z - v2->z;

   return(vec);
}


/* 
 * VecReflection() - reflects a vector to point in opposite direction
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
vectorType VecReflection(vectorType *v)
{
   vectorType vec;

   vec.x = -v->x;	/* negate vector components */
   vec.y = -v->y;
   vec.z = -v->z;

   return(vec);
}


/* 
 * VecDotproduct() - computes scalar dot product of two vectors.
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
float VecDotproduct(vectorType *v1, vectorType *v2)
{
  return(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}


/* 
 * VecCrossproduct() - computes vector cross product of v1 X v2
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
vectorType VecCrossproduct(vectorType *v1, vectorType *v2)
{
  vectorType vec;

  vec.x = v1->y * v2->z - v1->z * v2->y;
  vec.y = v1->z * v2->x - v1->x * v2->z;
  vec.z = v1->x * v2->y - v1->y * v2->x;

  return(vec);
}


/* 
 * VecNormalize() - normalizes the vector
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
void VecNormalize(vectorType *v)
{
  double mag;
  
  mag = VecMagnitude(v);
  if (mag < 0.00001)
    return;

  v->x /= mag;
  v->y /= mag;
  v->z /= mag;
}


/* 
 * VecMagnitude() - computes the magnitude of a vector
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
float VecMagnitude(vectorType *v)
{
  return((float)sqrt(v->x*v->x + v->y*v->y + v->z*v->z));
}


/* 
 * MakeIdentityMatrix() - generates a 4x4 indentity matrix
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
matrixType MakeIdentityMatrix()
{
   matrixType mat;
   int r, c;

   mat.r = MAX_MAT_SIZE;
   mat.c = MAX_MAT_SIZE;

   for (r = 0; r < mat.r; r++)
      for (c = 0; c < mat.c; c++)
         if (r == c)
            mat.m[r][c] = (float) 1.0;
         else
            mat.m[r][c] = (float) 0.0;

   return(mat);   
}


/* 
 * MakeTranslationMatrix() - generates a translation matrix 
 *                           (assumes column vectors)
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
matrixType MakeTranslationMatrix(float tx, float ty, float tz)
{
   matrixType mat;

   mat = MakeIdentityMatrix();

   mat.m[0][3] = tx;
   mat.m[1][3] = ty;
   mat.m[2][3] = tz;

   return(mat);
}


/* 
 * MakeScaleMatrix() - generates a scale matrix 
 *                     (assumes column vectors)
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
matrixType MakeScaleMatrix(float sx, float sy, float sz)
{
   matrixType mat;

   mat = MakeIdentityMatrix();

   mat.m[0][0] = sx;
   mat.m[1][1] = sy;
   mat.m[2][2] = sz;

   return(mat);
}


/* 
 * MakeRotationMatrix() - generates a rotation matrix for the specified axis
 *                        (assumes column vectors)
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
matrixType MakeRotationMatrix(char axis, float theta)
{
   matrixType mat;
   double angle_radians;
   double cosine_theta;		/* cosine of rotation angle */
   double sine_theta;		/* sine of rotation angle */

   mat = MakeIdentityMatrix();

   /* convert angle theta from degrees to radians */
   angle_radians = (2 * PI) * (theta / 360);

   /* calculate cosines and sines of angle theta */
   cosine_theta = cos(angle_radians);
   sine_theta = sin(angle_radians);

   /* build rotation xform based on which axis is desired */
   switch(axis) {

      case 'x':	/* about the x-axis */
         mat.m[1][1] = cosine_theta;
         mat.m[1][2] = sine_theta;
         mat.m[2][1] = -1 * sine_theta;
         mat.m[2][2] = cosine_theta;
         break;

      case 'y':	/* about the y-axis */
         mat.m[0][0] = cosine_theta;
         mat.m[0][2] = -1 * sine_theta;
         mat.m[2][0] = sine_theta;
         mat.m[2][2] = cosine_theta;
         break;

      case 'z': /* about the z-axis */
         mat.m[0][0] = cosine_theta;
         mat.m[0][1] = -1 * sine_theta;
         mat.m[1][0] = sine_theta;
         mat.m[1][1] = cosine_theta;
         break;

      default:
         fprintf(stderr, "MakeRotateMatrix: unknown axis\n");
         exit(1);
         break;
   }

   return(mat);
}


/* 
 * MakeMappingMatrix() -- This function generates the 3x3 transform matrix 
 *			for mapping a world coordinate point into a
 *			viewport point.
 *
 * PARAMETERS
 *	worldbounds[0] = x min		4 element array of double
 *	worldbounds[1] = y min
 *	worldbounds[2] = x max
 *	worldbounds[3] = y max
 *
 *	screenbounds[0] = u min		4 element array of double
 *	screenbounds[1] = v min
 *	screenbounds[2] = u max
 *	screenbounds[3] = v max
 *
 * RETURNS
 *
		The transform matrix generated has the form:

			|  a    0    b  |
			|               |
			|  0    c    d  |
			|               |
			|  0    0    1  |

		where:

		  a = (umax - umin) / (xmax - xmin)

		  b = ((-xmin) * (umax - umin) / (xmax - xmin)) + umin

		  c = (vmax - vmin) / (ymax - ymin)

		  d = ((-ymin) * (vmax - vmin) / (ymax - ymin)) + vmin


		NOTE:
		  coordinates u,v are viewport related
		  coordinates x,y are world related

******************************************************************/
matrixType
MakeMappingMatrix(double worldbounds[], double screenbounds[])
{
   matrixType xform;
   double xmin, xmax, ymin, ymax;	/* world boundaries */
   double umin, umax, vmin, vmax;	/* screen boundaries */
   double a, b, c, d;			/* matrix terms */

   double offset = 10.0;		/* safety border */


   /*  make identity matrix
    */
   xform = MakeIdentityMatrix();

   /*  resize to a 3x3 matrix 
    */
   xform.r = 3;
   xform.c = 3;

   /*  set world bounds
    */
   xmin = worldbounds[0];
   ymin = worldbounds[1];
   xmax = worldbounds[2];
   ymax = worldbounds[3];

   /*  set viewport bounds
    */
   umin = screenbounds[0] + offset;
   vmin = screenbounds[1] + offset;
   umax = screenbounds[2] + offset;
   vmax = screenbounds[3] + offset;

   /* calculate matrix terms */
   a = (umax - umin) / (xmax - xmin);

   c = (vmax - vmin) / (ymax - ymin);

   b = ((-1) * xmin * a) + umin;

   d = ((-1) * ymin * c) + vmin;

   /* plug matrix terms into transform matrix */
   xform.m[0][0] = a;
   xform.m[0][2] = b;
   xform.m[1][1] = c;
   xform.m[1][2] = d;

   return(xform);
} /* end of MakeMappingMatrix() */


/* 
 * MatrixMultiply() - multiplies an MxN matrix by a NxP matrix and
 *                    returns a MxP matrix
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
matrixType MatrixMultiply(matrixType *m1, matrixType *m2)
{
   matrixType product;
   int m, n, p;
   double sum;

   /* setup resultant matrix size */
   product.r = m1->r;
   product.c = m2->c;

   /* test if legal multiply operation */
   if (m1->c == m2->r) {

      for (m = 0; m < m1->r; m++) {

         for (p = 0; p < m2->c; p++) {

            /* form resultant element[m][p] */
            sum = 0.0;

            for (n = 0; n < m1->c; n++)
               sum = sum + (m1->m[m][n] * m2->m[n][p]);

            product.m[m][p] = sum;
         }
      }
   }
   else {
      fprintf(stderr, "MatrixMultiply: illegal matrix sizes\n");
      exit(1);
   }

   return(product);
}


/* 
 * MatrixTranspose() - transposes the given matrix
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
void MatrixTranspose(matrixType *mat)
{
   int r, c;
   matrixType tmat;

   for (r = 0; r < mat->r; r++) 
      for (c = 0; c < mat->c; c++) 
         tmat.m[c][r] = mat->m[r][c];	/* transpose it */

   for (r = 0; r < mat->r; r++) 
      for (c = 0; c < mat->c; c++) 
         mat->m[r][c] = tmat.m[r][c];	/* copy back to original */
}



/* 
 * MatrixInverse() - inverts a matrix if matrix has an inverse
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
int MatrixInverse(matrixType *m, matrixType *inv)
{
   int error=0;

   return(error);
}

/* 
 * MatrixDeterminant() - calculates the determinant of a matrix
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
matrixType MatrixDeterminant(matrixType *m)
{
   matrixType det;

   return(det);
}


/* 
 * MatrixCopy() - copies one matrix to another
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
void MatrixCopy(matrixType *m1, matrixType *m2)
{
   int r, c;

   m2->r = m1->r;
   m2->c = m1->c;

   for (r = 0; r < m1->r; r++) 
      for (c = 0; c < m1->c; c++) 
         m2->m[r][c] = m1->m[r][c];
}


/* 
 * TransformVector() - tranforms a vector by the given xform matrix
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
vectorType TransformVector(vectorType *v, matrixType *mat)
{
   vectorType vres;
   matrixType vmat, resmat;

   vmat = Vector2Matrix( v, 4);
   resmat = MatrixMultiply( mat, &vmat);
   vres = Matrix2Vector( &resmat );

   return(vres);
}


/* 
 * TransformWPoint() - transforms a world point by the given xform matrix
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
wpointType TransformWPoint(wpointType *p, matrixType *mat)
{
   wpointType pres;
   vectorType tempv, resv;

   tempv = WPoint2Vector( p );
   resv = TransformVector( &tempv, mat);
   pres = Vector2WPoint( &resv );

   return(pres);
}


/* 
 * Vector2Matrix() - converts a vector into a column matrix
 *
 * PARAMETERS
 *	v 		- vector
 *	num_rows	- number of rows in column
 *
 * RETURNS
 *
 */
matrixType Vector2Matrix(vectorType *v, int num_rows)
{
   matrixType mat;

   mat.r = num_rows;
   mat.c = 1;

   mat.m[0][0] = v->x;   mat.m[1][0] = v->y;   mat.m[2][0] = v->z;
   mat.m[3][0] = (float) 1.0;

   return(mat);
}


/* 
 * Matrix2Vector() - converts a column matrix into a vector
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
vectorType Matrix2Vector(matrixType *m)
{
   vectorType vec;

   vec.x = m->m[0][0];   vec.y = m->m[1][0];   vec.z = m->m[2][0];

   return(vec);
}


/* 
 * Vector2WPoint() - converts a vector type into a world point type
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
wpointType Vector2WPoint(vectorType *v)
{
   wpointType p;
   
   p.x = v->x;  p.y = v->y;  p.z = v->z;

   return(p);
}


/* 
 * WPoint2Vector() - converts a world point type into a vector type
 *
 * PARAMETERS
 *
 * RETURNS
 *
 */
vectorType WPoint2Vector(wpointType *p)
{ 
   vectorType v;

   v.x = p->x;  v.y = p->y;  v.z = p->z;

   return(v);
}


/* end of vecmath.c */
