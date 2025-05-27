/***********************************************************************

   A set of typedefs and defines for use in vector and matrix math for 
   computer graphics applications.

   File:  	vecmath.h	-- types and defines for vecmath.c

   Author: 	Brian Lingard

   Date:	10/4/95

***********************************************************************/

#ifndef _VECMATH_H
#define _VECMATH_H

/************************/
/* constant definitions */
/************************/

#ifndef PI
#define PI 	3.141592
#endif

#ifndef TWO_PI
#define TWO_PI 	6.283184
#endif

#define E	2.718282
#define SQRT2	1.414214
#define SQRT3	1.732051

#ifndef RAND_MAX
#define RAND_MAX 32767
#endif

#define MAX_MAT_SIZE	4


/************************/
/*  macro definitions   */
/************************/

/* convert between degrees and radians */
#define DEG2RADS(d)	(d * 0.017453)		/* (d / 360) * 2PI) */
#define RADS2DEG(r)	(r * 57.295791)		/* (r / 2PI) * 360) */

/* find minimum of a and b */
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))

/* find maximum of a and b */
#define MAX(a,b)	(((a) > (b)) ? (a) : (b))

/* swap a and b */
#define SWAP(a,b)	{ a^=b; b^=a; a^=b; }

/* linear interpolation from l (when a=0) to h (when a=1) */
/* (equal to (a*h) + ((l-a)*l) */
#define LERP(a,l,h)	((l) + (((h) - (l)) * (a)))

/* clamp the input to a specified range */
#define CLAMP(v,l,h)	((v) < (l) ? (l) : (v) > (h) ? (h) : v)


/************************/
/*  structure typedefs  */
/************************/

typedef struct {			/* world coordinate point and vector */
   float x;
   float y;
   float z;
} wpointType, vectorType;

typedef struct {			/* screen point */
   int x;
   int y;
} pointType;

typedef struct {
   int r;
   int c;
   float m[MAX_MAT_SIZE][MAX_MAT_SIZE];
} matrixType;


/************************/
/*  function prototypes */
/************************/

float      nrand(void);
float      nrands(void);

pointType  LerpPoint(pointType *pl, pointType *ph, float alpha);
wpointType LerpWPoint(wpointType *wl, wpointType *wh, float alpha);
vectorType LerpVector(vectorType *vl, vectorType *vh, float alpha);

vectorType VecAdd(vectorType *v1, vectorType *v2);
vectorType VecSub(vectorType *v1, vectorType *v2);
vectorType VecReflection(vectorType *v);
float      VecDotproduct(vectorType *v1, vectorType *v2);
vectorType VecCrossproduct(vectorType *v1, vectorType *v2);
void       VecNormalize(vectorType *v);
float      VecMagnitude(vectorType *v);

matrixType Vector2Matrix(vectorType *v, int num_rows);
vectorType Matrix2Vector(matrixType *m);

matrixType WPoint2Matrix(wpointType *w, int num_rows);
wpointType Matrix2WPoint(matrixType *m);

wpointType Vector2WPoint(vectorType *v);
vectorType WPoint2Vector(wpointType *p);

matrixType MakeIdentityMatrix(void);
matrixType MakeTranslationMatrix(float tx, float ty, float tz);
matrixType MakeScaleMatrix(float sx, float sy, float sz);
matrixType MakeRotationMatrix(char axis, float theta);
matrixType MakeMappingMatrix(double worldbounds[], double screenbounds[]);

matrixType MatrixMultiply(matrixType *m1, matrixType *m2);
void       MatrixTranspose(matrixType *mat);
int        MatrixInverse(matrixType *m, matrixType *inv);
matrixType MatrixDeterminant(matrixType *m);
void       MatrixCopy(matrixType *m1, matrixType *m2);

void       CopyPoint(pointType *s, pointType *d);
void       CopyWPoint(wpointType *s, wpointType *d);
void       CopyVector(vectorType *s, vectorType *d);

vectorType TransformVector(vectorType *v, matrixType *mat);
wpointType TransformWPoint(wpointType *p, matrixType *mat);

void       OutputMatrix(FILE *out, matrixType *m, char *label);
void       OutputPoint(FILE *out, pointType *pt, char *label);
void       OutputWPoint(FILE *out, wpointType *m, char *label);
void       OutputVector(FILE *out, vectorType *m, char *label);


#endif /* _VECMATH_H */
/* end of vecmath.h */
