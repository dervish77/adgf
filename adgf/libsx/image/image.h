/***********************************************************************

   File:  	image.h

   Author: 	Brian Lingard

   Date:	10/20/95

 Header file for image processing demo program.

***********************************************************************/

#ifndef _IMAGE_H
#define _IMAGE_H


#ifndef _VECMATH_H
#include "vecmath.h"
#endif

#ifndef _PPM_H
#include "ppm.h"	/* has COLOR_S_T */
#endif

#ifndef COLOR_S_T
typedef struct {
   unsigned char r;
   unsigned char g;
   unsigned char b;
} COLOR_S_T;
#endif

/*  define some common types 
 */
#define SCREEN_C_SIZE   400
#define SCREEN_R_SIZE	320

#define HIST_X_SIZE	300
#define HIST_Y_SIZE	100

#define HIST_ORIG_X_OFFSET	20
#define HIST_ORIG_Y_OFFSET	10

#define HIST_X_AXIS_LEN		256
#define HIST_Y_AXIS_LEN		100

#define LUT_X_SIZE	128
#define LUT_Y_SIZE	128


#define MAX_GRADIENT_LEVELS	256

#define BUFFER_LEN	80
typedef char BUFFER_T[BUFFER_LEN];

#define BUTTON_UP	0			/* mouse button state */
#define BUTTON_DOWN	1

#define FILE_STRING_LEN	32
typedef char FILE_STRING_T[FILE_STRING_LEN];

typedef unsigned char	UBYTE_T;

typedef UBYTE_T		BOOLEAN_T;



/*  define some useful macros
 */
#define InvertY(y)		(SCREEN_R_SIZE - (y))

#define GREY2INTENSITY(g)	( ( ((float) g) / 255.0) * 1.0 )

#define INTENSITY2GREY(i)	((int) (i * 255))

#define RGB2GREY(r,g,b)		( (int) ((r + g + b) / (3.0)))



/*  define some default values
 */
#define DEFAULT_DUMP_FILE	"dumpdata.log"



/*  define color map structure 
 */
#define MAX_COLOR_MAP	256

typedef struct {
   COLOR_S_T	map[MAX_COLOR_MAP];	/* actual rgb values */
   BOOLEAN_T	valid[MAX_COLOR_MAP];	/* TRUE if valid color */
   int		indexes[MAX_COLOR_MAP];	/* index to RBG system color */
   int          count;			/* how many colors in table */
} COLORMAP_S_T;



/*  define RGB raster array type 
 */
#define RASTER_R_SIZE	SCREEN_R_SIZE
#define RASTER_C_SIZE	SCREEN_C_SIZE

typedef UBYTE_T 	RASTER_IND_T[RASTER_R_SIZE][RASTER_C_SIZE];

typedef COLOR_S_T 	RASTER_RGB_T[RASTER_R_SIZE][RASTER_C_SIZE];



/*  define some enumerated types 
 */
typedef enum {UNKN_OPER,
		REVERT_OPER,
		HISTOGRAM_OPER,
		COL2GREY_OPER,
		NEGATIVE_OPER,
		BLUR_OPER,
		SHARPEN_OPER,
		EDGEDETECT_OPER} OPERATION_T;
		


/*  define image structure 
 */
typedef struct image_s_t {
   int			rsize;		/* number of rows */
   int			csize;		/* number of columns */
   RASTER_RGB_T		raster;
} IMAGE_S_T;



/*  define filter structure 
 */
#define MAX_FILTER_SIZE	10

typedef struct filter_s_t {
   int 		r;
   int 		c;
   float	divisor;
   float	m[MAX_FILTER_SIZE][MAX_FILTER_SIZE];
} FILTER_S_T;



/*  define histogram structure 
 */
typedef struct histogram_s_t {
   BOOLEAN_T		computed;	/* flag, TRUE if has been computed */
   unsigned int		max_count;
   unsigned int		max_index;
   unsigned int		min_count;
   unsigned int		min_index;
   unsigned int		array[MAX_GRADIENT_LEVELS];
} HISTOGRAM_S_T;



/*  define database structure 
 */ 
typedef struct data_s_t {
   OPERATION_T		oper;
   IMAGE_S_T		current;	/* current image buffer */
   IMAGE_S_T		temp;		/* temporary image buffer */
   IMAGE_S_T		original;	/* original image buffer */
   COLORMAP_S_T		colormap;	/* color map structure */
   FILTER_S_T		blur;		/* current blur filter */
   FILTER_S_T		sharp;		/* current sharpen filter */
   HISTOGRAM_S_T	hist;		/* histogram structure */
   UBYTE_T		lut[MAX_GRADIENT_LEVELS];
   BOOLEAN_T		image_is_grey;	/* flag, TRUE if image is grey scale */
} DATA_S_T;



#endif /* _IMAGE_H */
/* end of image.h */
