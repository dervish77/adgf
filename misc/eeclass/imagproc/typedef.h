/* this file contains global type definitions for all programs that
   were written by Gary Gu for computer vision & image processing

   Notation convention: all capital variable names are ggu-defined.
*/
 
typedef unsigned char BYTE;
typedef short  WORD;
typedef enum {FALSE, TRUE} BOOLEAN;
typedef struct
     {
        WORD type,
             xdim,
             ydim;
       BYTE *bits;
     } GIFF;         /* Gu's Image File Format */
typedef struct
     {
        WORD type,
             xdim,
             ydim;
      float *bits;
     } GIFF_F;         /* Gu's Image File Format, floating point */

/*
typedef float image_float_t[XMAX][YMAX];
typedef struct
{
	image_float_t alpha;
	image_float_t beta;
	image_float_t gamma;
	image_float_t error;
} haralick_t;
*/

typedef struct
{
  float re, im;
} complex;
