/***********************************************************************

   File:  	render.h

   Author: 	Brian Lingard

   Date:	5/26/95

 Header file for 3D modeler and rendering program.

***********************************************************************/

#ifndef _RENDER_H
#define _RENDER_H


#ifndef _VECMATH_H
#include "vecmath.h"
#endif


#define SCREEN_X_SIZE   800
#define SCREEN_Y_SIZE	800

#define InvertY(y)	(SCREEN_Y_SIZE - y)

#define LONG_SCROLL_SIZE 	((int) 800)
#define LONG_SCROLL_WHERE 	((float) 0.0)
#define LONG_SCROLL_MAX		((float) 360.0)
#define LONG_SCROLL_SHOWN	((float) 5.0)

#define LAT_SCROLL_SIZE		((int) 800)
#define LAT_SCROLL_WHERE	((float) 90.0)
#define LAT_SCROLL_MAX		((float) 180.0)
#define LAT_SCROLL_SHOWN	((float) 5.0)

#define ZOOM_SCROLL_SIZE	((int) 200)
#define ZOOM_SCROLL_WHERE	((float) 100.0)
#define ZOOM_SCROLL_MAX		((float) 200.0)
#define ZOOM_SCROLL_SHOWN	((float) 5.0)

#define BUFFER_LEN	80
typedef char BUFFER_T[BUFFER_LEN];

#define BUTTON_UP	0		/* left button state */
#define BUTTON_DOWN	1


/* define some common types */
#define FILE_STRING_LEN	32
typedef char FILE_STRING_T[FILE_STRING_LEN];

typedef unsigned char	UBYTE_T;

typedef UBYTE_T		BOOLEAN_T;

typedef float		LUMIN_T;

#define COLOR_RGB_LEN 	3
#define R_IDX 0
#define G_IDX 1
#define B_IDX 2
typedef UBYTE_T COLOR_RGB_T[COLOR_RGB_LEN];

#define SIZE_OF_POLY	3

#define DEFAULT_RANGE	((float) 10.0)

#define DEG2RADS(d)	((d / 360) * PI)


/* define some enumerated types */
typedef enum {UNKN_LIGHT=0,
		AMB_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,
		INFIN_LIGHT} LIGHT_T;

typedef enum {UNKN_SHADE=0, 
		WIRE_SHADE, 
		FLAT_SHADE, 
		GOURAUD_SHADE,
		PHONG_SHADE} SHADE_T;

typedef enum {UNKN_PROJ=0, 
		ORTH_PROJ_XY,
		ORTH_PROJ_ZY,
		ORTH_PROJ_XZ,
		PARA_PROJ, 
		PERS_PROJ} PROJECT_T;

typedef enum {UNKN_CMODE=0,
		GREY_CMODE,
		COLOR_CMODE} CMODE_T;


/* define polygon structure */
typedef struct polygon_s_t {
   int		num_edges;	/* number of edges in polygon (def = 3) */
   int		vertices[SIZE_OF_POLY]; /* indices of vertices, cclock wise */
   COLOR_RGB_T	color;		/* base color of polygon */
   vectorType	normal;		/* surface normal */
   BOOLEAN_T	visible;	/* flag if visible */
   BOOLEAN_T	sorted;		/* flag if sorted yet */
   BOOLEAN_T	rendered;	/* flag if rendered yet */
} POLYGON_S_T;


/* define lighting structure */
typedef struct light_s_t {
   LIGHT_T	type;		/* type of lighting */
   wpointType	location;	/* location of light in worlds coords */
   vectorType	direction;	/* direction of illumination, if directional */
   float	spot_size;	/* angular spot size in radians */
   LUMIN_T	intensity;	/* intensity in lumens */
   COLOR_RGB_T	color;		/* color of light */
} LIGHT_S_T;


/* define view structure */
typedef struct view_s_t {
   wpointType 	eyeloc;		/* eye location */
   wpointType	lookat;		/* look at point */
   vectorType	vup;		/* view up vector */
   wpointType 	vrp;		/* view reference point */
   LIGHT_S_T	light;		/* lighting structure */
} VIEW_S_T;


/* define render structure */ 
typedef struct render_s_t {
   SHADE_T	shading_mode;
   PROJECT_T	projection;
   CMODE_T	color_mode;
   int		vertex_count;
   int		polygon_count;
   wpointType	*init_verts;	/* initial array of vertices */
   wpointType	*vert_list;	/* array of vertices */
   POLYGON_S_T	*poly_list;	/* array of polygon */
   VIEW_S_T	view;		/* view structure */
} RENDER_S_T;


/* extern all function prototypes */
void ComputeEyeLocation(void *data);


#endif /* _RENDER_H */
/* end of render.h */
