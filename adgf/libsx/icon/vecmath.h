/***********************************************************************

   File:  	vecmath.h	-- types and defines for vecmath.c

   Author: 	Brian Lingard

   Date:	4/12/95

***********************************************************************/

#ifndef _VECMATH_H
#define _VECMATH_H

/*  constant definitions
 */
#define MAX_MAT_SIZE	4

#ifndef PI
#define PI 3.1415926
#endif

#ifndef RAND_MAX
#define RAND_MAX 32767
#endif

/*  typedefs for structures
 */
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


/*  function prototypes
 */
float      nrand(void);
float      nrands(void);
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
wpointType Matrix2Wpoint(matrixType *m);

wpointType Vector2WPoint(vectorType *v);
vectorType WPoint2Vector(wpointType *p);

matrixType MakeIdentityMatrix();
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

void OutputMatrix(FILE *out, matrixType *m, char *label);
void OutputWPoint(FILE *out, wpointType *m, char *label);
void OutputVector(FILE *out, vectorType *m, char *label);


#endif /* _VECMATH_H */
/* end of vecmath.h */
