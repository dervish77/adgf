/***********************************************************************

   File:  	modeler.h

   Author: 	Brian Lingard

   Date:	9/9/95

 Header file for 3D modeler program.

***********************************************************************/

#ifndef _MODELER_H
#define _MODELER_H


#ifndef _VECMATH_H
#include "vecmath.h"
#endif


#define SCREEN_X_SIZE   800
#define SCREEN_Y_SIZE	800

#define InvertY(y)	(SCREEN_Y_SIZE - y)

#define BUFFER_LEN	80
typedef char BUFFER_T[BUFFER_LEN];

#define BUTTON_UP	0		/* left button state */
#define BUTTON_DOWN	1


/* define some common types */
#define FILE_STRING_LEN	32
typedef char FILE_STRING_T[FILE_STRING_LEN];

#define DEFAULT_DUMP_FILE	"dumpdata.log"
#define DEFAULT_LOAD_FILE	"model.mdl"
#define DEFAULT_EXPORT_FILE	"export.rnd"

#define DEFAULT_NUM_FRAMES	((int) 20)
#define DEFAULT_FRAME_RATE	((int) 15)	/* frames per second */

#define DEFAULT_ZOOM_VALUE	((double) 20.0)

#define DEFAULT_FOV_ANGLE	((double) 30.0)	/* gives 60 degree FOV */


typedef unsigned char	UBYTE_T;

typedef UBYTE_T		BOOLEAN_T;

typedef float		LUMIN_T;

#define MAX_PRIMITIVES	50
#define MAX_VERTICES	500
#define MAX_POLYGONS	250

#define COLOR_RGB_LEN 	3
#define R_IDX 0
#define G_IDX 1
#define B_IDX 2
typedef UBYTE_T COLOR_RGB_T[COLOR_RGB_LEN];
typedef LUMIN_T COLOR_INT_T[COLOR_RGB_LEN];

#define MAX_COLOR_MAP	256	/* each primitive can have one color */

typedef struct {
   COLOR_RGB_T  map[MAX_COLOR_MAP];	/* actual rgb values */
   BOOLEAN_T	valid[MAX_COLOR_MAP];	/* TRUE if valid color */
   int		indexes[MAX_COLOR_MAP];	/* index to RBG system color */
   int          count;			/* how many colors in table */
} COLORMAP_S_T;

#define SIZE_OF_TRIA	3
#define SIZE_OF_RECT	4
#define SIZE_OF_POLY	SIZE_OF_RECT


/* define some enumerated types */
typedef enum {UNKN_ANIM,
		NO_ANIM,		  /* no animation, static picture */
		LINEAR_ANIM,		  /* follow straight line path */
		CIRCLE_ANIM,		  /* follow arc path on circle */
		BEZIER_ANIM,		  /* follow curved path */
		SPLINE_ANIM} ANIM_TYPE_T; /* follow curved path */

#define ANIM_STR_LEN 7

#define ANIM_STR_NONE	"an_none"
#define ANIM_STR_LINEAR	"an_line"
#define ANIM_STR_CIRCLE	"an_circ"
#define ANIM_STR_BEZIER	"an_bezi"
#define ANIM_STR_SPLINE	"an_spli"


typedef enum {STOP_ANIM,
		RUN_ANIM,
		LOOP_ANIM,
		PING_ANIM,
		STEP_ANIM} ANIM_MODE_T;	


typedef enum {UNKN_VIEW=0,
		ALL_VIEW,
		ORTH_XY_VIEW,
		ORTH_ZY_VIEW,
		ORTH_XZ_VIEW,
		CAMERA_VIEW,
		SMALL_ORTH_XY_VIEW,
		SMALL_ORTH_ZY_VIEW,
		SMALL_ORTH_XZ_VIEW,
		SMALL_CAMERA_VIEW} VIEW_SCREEN_T;


typedef enum {UNKN_REND,
		WIRE_REND,
		SOLID_REND,
		SHADE_REND} RENDER_MODE_T;


typedef enum {UNKN_SHADE,
		FLAT_SHADE,
		GOURAUD_SHADE,
		PHONG_SHADE} SHADING_T;


typedef enum {UNKN_PROJ,
		PARALLEL_PROJ,
		PERSPECTIVE_PROJ} PROJ_MODE_T;


typedef enum {UNKN_LIGHT=0,
		AMB_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,
		INFIN_LIGHT} LIGHT_T;

#define LT_STR_LEN	7

#define LT_STR_AMBIENT	"lt_ambi"
#define LT_STR_POINT	"lt_poin"
#define LT_STR_SPOT	"lt_spot"
#define LT_STR_INFINITE	"lt_infi"


typedef enum {UNKN_PRIM=0,
		PLANE_PRIM,
		CUBE_PRIM,
		CYLIN_PRIM,
		PYRA_PRIM,
		PRISM_PRIM,
		CONE_PRIM,
		SPHERE_PRIM} PRIM_T;

#define PT_STR_LEN	7

#define PT_STR_PLANE	"pt_plan"
#define PT_STR_CUBE	"pt_cube"
#define PT_STR_CYLINDER	"pt_cyli"
#define PT_STR_PYRAMD	"pt_pyra"
#define PT_STR_PRISM	"pt_pris"
#define PT_STR_CONE	"pt_cone"
#define PT_STR_SPHERE	"pt_sphe"


#define TYPE_STRING_LEN	8

#define PLANE_STRING	"plane   "
#define CUBE_STRING	"cube    "
#define CYLINDER_STRING	"cylinder"
#define PYRAMID_STRING	"pyramid "
#define PRISM_STRING	"prism   "
#define CONE_STRING	"cone    "
#define SPHERE_STRING	"sphere  "


/* define primitve structure */
typedef struct primitive_s_t {
   PRIM_T	type;		/* type of primitive */
   wpointType	center;		/* desired center of primitive */
   wpointType	scaling;	/* desired scale of primitve */
   char 	axis;		/* axis of rotation (equals 'n' if none) */
   double 	angle;		/* amount of rotation in degrees */
   COLOR_RGB_T	color;		/* base color of polygon */
   BOOLEAN_T	valid;		/* flag if valid primitive */
} PRIMITIVE_S_T;


/* define polygon structure */
typedef struct polygon_s_t {
   int		num_verts;	/* number of vertices in polygon (def = 3) */
   int		vertices[SIZE_OF_POLY]; /* indices of vertices, cclock wise */
   vectorType	normal;		/* surface normal */
   vectorType	rend_normal;	/* surface normal for rendering */
   COLOR_RGB_T	color;		/* base color of polygon */
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
   LUMIN_T	intensity;	/* intensity of light in lumens */
   COLOR_RGB_T	color;		/* color of light */
   vectorType	L;		/* current light vector */
   SHADING_T	shading;	/* type of shading to use */
} LIGHT_S_T;


/* define view structure */
typedef struct view_s_t {
   wpointType 	eyeloc;		/* eye location */
   wpointType	lookat;		/* look at point */
   vectorType	vup;		/* view up vector */
   wpointType 	vrp;		/* view reference point */
   matrixType	M;		/* view transform matrix */
   PROJ_MODE_T	type;		/* type of camera projection */
   float	vpd;		/* view plane distance */
} VIEW_S_T;


/* define lat/long structure */
typedef struct lat_long_s_t {
   float	latitude;	/* latitude in degrees -- -90 to +90 */
   float	longitude;	/* longitude in degrees -- 0 to 360 */
} LAT_LONG_S_T;

typedef struct lin_path_s_t {
   wpointType	curr_eye_pt;	/* current eye point along path */
   wpointType	start_eye_pt;	/* starting eye point of linear path */
   wpointType	end_eye_pt;	/* ending eye point of linear path */
   wpointType	incr_eye_pt;	/* increment eye along linear path */
   wpointType	curr_lap_pt;	/* current lap point along path */
   wpointType	start_lap_pt;	/* starting lap point of linear path */
   wpointType	end_lap_pt;	/* ending lap point of linear path */
   wpointType	incr_lap_pt;	/* increment lap along linear path */
} LIN_PATH_S_T;

/* define anim structure */
typedef struct anim_s_t {
   ANIM_TYPE_T	type;		/* anim path type */
   ANIM_MODE_T	mode;		/* anim mode type */
   BOOLEAN_T	enable_anim;	/* if TRUE run the anim to the end */
   BOOLEAN_T	forward;	/* if TRUE running forward, else reverse */
   int		num_frames;	/* number of frames to animate */
   int		frame_rate;	/* frames per second */
   int		frame_count;	/* current frame count */
   int		frame_interval;	/* time 'til next frame, milliseconds */
   LIN_PATH_S_T lpath;		/* linear path parameters */
} ANIM_S_T;


/* define model structure */ 
typedef struct model_s_t {
   int			current_prim_idx;
   int			current_vert_idx;
   int			current_poly_idx;
   int			prim_count;
   int			vert_count;
   int			poly_count;
   PRIMITIVE_S_T	prim_list[MAX_PRIMITIVES]; /* array of primitives */
   wpointType		vert_list[MAX_VERTICES];   /* array of vertices */
   wpointType		rend_vert_list[MAX_VERTICES]; 
						/* array of rendered vertices */
   POLYGON_S_T		poly_list[MAX_POLYGONS];   /* array of polygon */
   VIEW_S_T		view;			   /* view structure */
   LIGHT_S_T		light;			   /* lighting structure */
   COLORMAP_S_T		colormap;		   /* color map structure */
   ANIM_S_T		anim;			   /* anim structure */
} MODEL_S_T;


/* extern all function prototypes */
extern int ParseString(char *string, char *args[]);

extern BOOLEAN_T enable_color_render;

#endif /* _MODELER_H */
/* end of modeler.h */
