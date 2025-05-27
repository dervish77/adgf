/***********************************************************************

   A set of routines for performing vector and matrix math for use in
   computer graphics applications.

   File:  	vecmath.cpp	

   Author: 	Brian Lingard

   Date:	10/4/95

***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef _VECMATH_H
#include "vecmath.h"
#endif


/* 
 * LerpPoint() - linearly interpolation from screen point low to screen point
 *		high by amount alpha and return the resulting screen point.
 *
 * PARAMETERS
 *	pl	- pointer to screen point low
 *	ph	- pointer to screen point high
 *	alpha	- amount of linear interpolation (0 to 1)
 *
 * RETURNS
 *	res	- resulting world point screen pl and ph
 *
 */
pointType LerpPoint(pointType *pl, pointType *ph, float alpha)
{
   pointType result;

   result.x = (int) LERP(alpha, pl->x, ph->x);
   result.y = (int) LERP(alpha, pl->y, ph->y);

   return(result);
}


/* 
 * LerpWPoint() - linearly interpolation from world point low to world point
 *		high by amount alpha and return the resulting world point.
 *
 * PARAMETERS
 *	wl	- pointer to world point low
 *	wh	- pointer to world point high
 *	alpha	- amount of linear interpolation (0 to 1)
 *
 * RETURNS
 *	res	- resulting world point between wl and wh
 *
 */
wpointType LerpWPoint(wpointType *wl, wpointType *wh, float alpha)
{
   wpointType result;

   result.x = LERP(alpha, wl->x, wh->x);
   result.y = LERP(alpha, wl->y, wh->y);
   result.z = LERP(alpha, wl->z, wh->z);

   return(result);
}


/* 
 * LerpVector() - linearly interpolation from vector low to vector high by 
 *		amount alpha and return the resulting vector.
 *
 * PARAMETERS
 *	vl	- pointer to vector low
 *	vh	- pointer to vector high
 *	alpha	- amount of linear interpolation (0 to 1)
 *
 * RETURNS
 *	res	- resulting vector between vl and vh
 *
 */
vectorType LerpVector(vectorType *vl, vectorType *vh, float alpha)
{
   vectorType result;

   result.x = LERP(alpha, vl->x, vh->x);
   result.y = LERP(alpha, vl->y, vh->y);
   result.z = LERP(alpha, vl->z, vh->z);

   return(result);
}


/* 
 * MakeVector() - generates a vector from given component values.
 *
 * PARAMETERS
 *	x	- x component
 *	y	- y component
 *	z	- z component
 *
 * RETURNS
 *	vec	- new vector
 *
 */
vectorType MakeVector(float x, float y, float z)
{
   vectorType vec;

   vec.x = x;
   vec.y = y;
   vec.z = z;

   return(vec);
}


/* 
 * VecAdd() - adds vector v1 to vector v2 and returns sum vector.
 *
 * PARAMETERS
 *	v1	- pointer to vector 1
 *	v2	- pointer to vector 2
 *
 * RETURNS
 *	sum	- sum of vector 1 and vector 2
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
 *	v1	- pointer to vector 1
 *	v2	- pointer to vector 2
 *
 * RETURNS
 *	sub	- sum of vector 1 minus vector 2
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
 *	v	- pointer to vector
 *
 * RETURNS
 *	refl	- reflection of vector
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
 * VecReflectionAboutNormal() - reflects a vector about a normal (mirror reflection)
 *
 * PARAMETERS
 *	v	- pointer to vector
 *	n   - pointer to normal
 *
 * RETURNS
 *	refl	- reflection of vector
 *
 */
vectorType VecReflectionAboutNormal(vectorType *v, vectorType *n)
{
   vectorType vec;
   vectorType sNorm;
   float dotprod;

   // 
   // equation is 
   //
   // R = V - ( 2 * (V dot N) * N )
   //

   dotprod = VecDotproduct(v, n);

   sNorm = VecScale( n, (2 * dotprod) );

   vec = VecSub( v, &sNorm );

   return(vec);
}


/* 
 * VecDotproduct() - computes scalar dot product of two vectors.
 *
 * PARAMETERS
 *	v1 	- pointer to vector 1
 *	v2 	- pointer to vector 2
 *
 * RETURNS
 *	dot	- dot product of vector 1 and vector 2
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
 *	v1 	- pointer to vector 1
 *	v2 	- pointer to vector 2
 *
 * RETURNS
 *	cross	- cross product of vector 1 X vector 2
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
 *	v 	- pointer to vector
 *
 * RETURNS
 *	nv	- normalized version of vector v
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
 *	v	- pointer to vector
 *
 * RETURNS
 *	mag	- magnitude of vector v
 *
 */
float VecMagnitude(vectorType *v)
{
  return((float)sqrt(v->x*v->x + v->y*v->y + v->z*v->z));
}


/* 
 * VecScale() - scales a vector
 *
 * PARAMETERS
 *	v     - pointer to vector
 *	scale - scaling amount
 *
 * RETURNS
 *	vec	- scaled vector
 *
 */
vectorType VecScale(vectorType *v, float scale)
{
  vectorType vec;

  vec.x = v->x * scale;
  vec.y = v->y * scale;
  vec.z = v->z * scale;  

  return(vec);
}


/* 
 * MakeIdentityMatrix() - generates a 4x4 indentity matrix
 *
 * PARAMETERS
 *	none
 *
 * RETURNS
 *	matrix	- a 4x4 identity matrix
 *
 */
matrixType MakeIdentityMatrix(void)
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
 *	tx	- translation along x axis
 *	ty	- translation along y axis
 *	tz	- translation along z axis
 *
 * RETURNS
 *	tmat	- translation matrix
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
 *	sx	- scaling along x axis
 *	sy	- scaling along y axis
 *	sz	- scaling along z axis
 *
 * RETURNS
 *	smat	- scaling matrix
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
 *	axis	- rotation axis -- valid characters are 'x', 'y', and 'z'
 *	theta	- angle of rotation in degrees
 *
 * RETURNS
 *	rmat	- rotation matrix
 *
 */
matrixType MakeRotationMatrix(char axis, float theta)
{
   matrixType mat;
   double cosine_theta;		/* cosine of rotation angle */
   double sine_theta;		/* sine of rotation angle */

   mat = MakeIdentityMatrix();

   /* calculate cosines and sines of angle theta */
   cosine_theta = cos( DEG2RADS(theta) );
   sine_theta = sin( DEG2RADS(theta) );

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
 *      matrixType - a 3x3 mapping transform matrix
 *
 * NOTES
 *	The transform matrix generated has the form:
 *
 *			|  a    0    b  |
 *			|               |
 *			|  0    c    d  |
 *			|               |
 *			|  0    0    1  |
 *
 *		where:
 *
 *		  a = (umax - umin) / (xmax - xmin)
 *
 *		  b = ((-xmin) * (umax - umin) / (xmax - xmin)) + umin
 *
 *		  c = (vmax - vmin) / (ymax - ymin)
 *
 *		  d = ((-ymin) * (vmax - vmin) / (ymax - ymin)) + vmin
 *
 *
 *		NOTE:
 *		  coordinates u,v are viewport related
 *		  coordinates x,y are world related
 *
 */
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
   umax = screenbounds[2] - offset;
   vmax = screenbounds[3] - offset;

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
 *	m1	- pointer to matrix 1	- MxN
 *	m2	- pointer to matrix 2	- NxP
 *
 * RETURNS
 *	product	- matrix product of m1 x m2
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
 *	mat 	- pointer to matrix
 *
 * RETURNS
 *	(mat)T	- the transpose of mat
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


#if 0

/* 
 * MatrixInverse() - inverts a matrix if matrix has an inverse
 *
 * PARAMETERS
 *	m	- pointer to matrix to invert
 *	inv	- pointer to inverse of m
 *
 * RETURNS
 *	error	- a boolean flag which is TRUE if m has no inverse
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
 *	m 	- pointer to matrix
 *
 * RETURNS
 *	det	- determinant of matrix m
 *
 */
matrixType MatrixDeterminant(matrixType *m)
{
   matrixType det;

   return(det);
}

#endif

/* 
 * MatrixCopy() - copies one matrix to another
 *
 * PARAMETERS
 *	m1	- pointer to source matrix
 *	m2	- pointer to destination matrix
 *
 * RETURNS
 *	none
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
 *	v	- pointer to vector
 *	mat	- pointer to transform matrix
 *
 * RETURNS
 *	vector	- transformed vector
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
 *	p	- pointer to world point
 *	mat	- pointer to transform matrix
 *
 * RETURNS
 *	wpoint	- transformed world point
 *
 */
wpointType TransformWPoint(wpointType *p, matrixType *mat)
{
   wpointType pres;
   matrixType wpmat, resmat;

   wpmat = WPoint2Matrix( p, 4);
   resmat = MatrixMultiply( mat, &wpmat);
   pres = Matrix2WPoint( &resmat );

   return(pres);
}


/* 
 * Vector2Matrix() - converts a vector into a column matrix
 *
 * PARAMETERS
 *	v 		- pointer to vector
 *	num_rows	- number of rows in column matrix
 *
 * RETURNS
 *	mat		- column matrix version of vector
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
 *	m	- pointer to column matrix
 *
 * RETURNS
 *	vector	- vector version of column matrix
 *
 */
vectorType Matrix2Vector(matrixType *m)
{
   vectorType vec;

   vec.x = m->m[0][0];   vec.y = m->m[1][0];   vec.z = m->m[2][0];

   return(vec);
}


/* 
 * WPoint2Matrix() - converts a world point into a column matrix
 *
 * PARAMETERS
 *	w 		- pointer to world point
 *	num_rows	- number of rows in column matrix
 *
 * RETURNS
 *	mat		- column matrix version of world point
 *
 */
matrixType WPoint2Matrix(wpointType *w, int num_rows)
{
   matrixType mat;

   mat.r = num_rows;
   mat.c = 1;

   mat.m[0][0] = w->x;   mat.m[1][0] = w->y;   mat.m[2][0] = w->z;
   mat.m[3][0] = (float) 1.0;

   return(mat);
}


/* 
 * Matrix2WPoint() - converts a column matrix into a world point
 *
 * PARAMETERS
 *	m	- pointer to column matrix
 *
 * RETURNS
 *	wpoint	- world point version of column matrix
 *
 */
wpointType Matrix2WPoint(matrixType *m)
{
   wpointType wpt;

   wpt.x = m->m[0][0];   wpt.y = m->m[1][0];   wpt.z = m->m[2][0];

   return(wpt);
}


/* 
 * Vector2WPoint() - converts a vector type into a world point type
 *
 * PARAMETERS
 *	v	- pointer to vector
 *
 * RETURNS
 *	wpoint	- world point copy of vector
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
 *	p	- pointer to world point
 *
 * RETURNS
 *	vector	- vector copy of world point
 *
 */
vectorType WPoint2Vector(wpointType *p)
{ 
   vectorType v;

   v.x = p->x;  v.y = p->y;  v.z = p->z;

   return(v);
}


/* 
 * CopyPoint() - copies screen point from source to destination
 *
 * PARAMETERS
 *	s	- pointer to source screen point
 *	d	- pointer to destination screen point
 *
 * RETURNS
 *	none
 *
 */
void CopyPoint(pointType *s, pointType *d)
{ 
   d->x = s->x;  d->y = s->y;
}


/* 
 * CopyWPoint() - copies world point from source to destination
 *
 * PARAMETERS
 *	s	- pointer to source world point
 *	d	- pointer to destination world point
 *
 * RETURNS
 *	none
 *
 */
void CopyWPoint(wpointType *s, wpointType *d)
{ 
   d->x = s->x;  d->y = s->y;  d->z = s->z;
}


/* 
 * CopyVector() - copies vector from source to destination
 *
 * PARAMETERS
 *	s	- pointer to source vector
 *	d	- pointer to destination vector
 *
 * RETURNS
 *	none
 *
 */
void CopyVector(vectorType *s, vectorType *d)
{ 
   d->x = s->x;  d->y = s->y;  d->z = s->z;
}


/* 
 * OutputMatrix() - outputs contents of matrix to specified device
 *
 * PARAMETERS
 *	out	- file pointer
 *	m	- pointer to matrix
 *	label	- pointer to character string to use as label
 *
 * RETURNS
 *	none
 *
 */
void OutputMatrix(FILE *out, matrixType *m, char *label)
{
   int r, c;

   fprintf(out, "%s:\n", label);
   fprintf(out, "  row, cols = %d, %d\n", m->r, m->c);
   for (r = 0; r < m->r; r++)
   {
      fprintf(out, "  ");
      for (c = 0; c < m->c; c++)
      {
         fprintf(out, "%f ", m->m[r][c]);
      }
      fprintf(out, "\n");
   }
   fprintf(out, "  done\n");
}


/* 
 * OutputPoint() - outputs screen point to specified device
 *
 * PARAMETERS
 *	out	- file pointer
 *	pt	- pointer to screen point
 *	label	- pointer to character string to use as label
 *
 * RETURNS
 *	none
 *
 */
void OutputPoint(FILE *out, pointType *pt, char *label)
{
   fprintf(out, "%s -- ", label);
   fprintf(out, "%d %d\n", pt->x, pt->y);
}


/* 
 * OutputWPoint() - outputs world point to specified device
 *
 * PARAMETERS
 *	out	- file pointer
 *	pt	- pointer to world point
 *	label	- pointer to character string to use as label
 *
 * RETURNS
 *	none
 *
 */
void OutputWPoint(FILE *out, wpointType *pt, char *label)
{
   fprintf(out, "%s -- ", label);
   fprintf(out, "%f %f %f\n", pt->x, pt->y, pt->z);
}


/* 
 * OutputVector() - outputs vector to specified device
 *
 * PARAMETERS
 *	out	- file pointer
 *	v	- pointer to vector
 *	label	- pointer to character string to use as label
 *
 * RETURNS
 *	none
 *
 */
void OutputVector(FILE *out, vectorType *v, char *label)
{
   fprintf(out, "%s -- ", label);
   fprintf(out, "%f %f %f\n", v->x, v->y, v->z);
}


/* end of vecmath.c */
