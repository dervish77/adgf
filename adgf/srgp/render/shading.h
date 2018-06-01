/* 

   Typedefs and defines for shading.c

   File:   shading.h

   Author: Brian Lingard

   Rev history:
	1 - 3/18/95  restructured   
	0 - 12/4/94  originated

*/

/* illumination constants */
#define Kdiff 0.5		/* diffuse reflection coefficient */
#define Kamb 0.5		/* ambient reflection coefficient */

#define Ipoint 1.0		/* point light source intensity */
#define Iamb 1.0		/* ambient light intensity */

/* other color related constants */
#define USECOLOR 1		/* if 1 use color, else grey scales */
#define MAX_GREY_LEVELS 65535	/* max number of grey scale levels */
#define MAX_NUM_COLORS 9	/* max number of colors */
#define MAX_TABLE_SIZE 255	/* max size of local color table */
#define COLOR_MARGIN 655	/* set to 1% of MAX_GREY_LEVELS */

/* device independant color indices */
#define WHITE 0
#define BLACK 1
#define GREY 2
#define RED 3
#define GREEN 4
#define BLUE 5
#define YELLOW 6
#define CYAN 7
#define MAGENTA 8

/* typedefs for shading functions */
typedef enum {NOT_VISIBLE=0, VISIBLE} visibleType;

typedef unsigned short ush;

typedef struct {
   float IR;
   float IG;
   float IB;
} colorType;	/* color intensity triple */

typedef struct {
   ush R;
   ush G;
   ush B;
} RGBType;	/* RGB color triple */

/* end of file shading.h */
