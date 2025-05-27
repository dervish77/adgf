/***********************************************************************

   File:  	particle.h

   Author: 	Brian Lingard

   Date:	10/17/95

 Header file for particle systems demo program.

***********************************************************************/

#ifndef _PARTICLE_H
#define _PARTICLE_H


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
#define DEFAULT_LOAD_FILE	"data.prt"

#define DEFAULT_NUM_PSYS	((int) 1)
#define DEFAULT_NUM_PART	((int) 300)

#define DEFAULT_NUM_FRAMES	((int) 20)
#define DEFAULT_FRAME_RATE	((int) 15)	/* frames per second */

#define DEFAULT_ZOOM_VALUE	((double) 20.0)

#define DEFAULT_FOV_ANGLE	((double) 30.0)	/* gives 60 degree FOV */


typedef unsigned char	UBYTE_T;

typedef UBYTE_T		BOOLEAN_T;


#define MAX_PARTICLES	5000	/* max particles per system */
#define MAX_PSYSTEMS	5	/* max number of systems */

#define MAX_LIFESPAN	60	/* max life span in frames */

#define GRAVITY		((float) 1.0)



#define MAX_COLOR_MAP	256

#ifndef COLOR_S_T
typedef struct {
   unsigned char r;
   unsigned char g;
   unsigned char b;
} COLOR_S_T;
#endif

typedef struct {
   COLOR_S_T	map[MAX_COLOR_MAP];	/* actual rgb values */
   BOOLEAN_T	valid[MAX_COLOR_MAP];	/* TRUE if valid color */
   int		indexes[MAX_COLOR_MAP];	/* index to RBG system color */
   int          count;			/* how many colors in table */
} COLORMAP_S_T;


#define RASTER_X_SIZE	SCREEN_X_SIZE
#define RASTER_Y_SIZE	SCREEN_Y_SIZE

typedef UBYTE_T	RASTER_T[RASTER_X_SIZE][RASTER_Y_SIZE];



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


typedef enum {UNKN_PROJ,
		PARALLEL_PROJ,
		PERSPECTIVE_PROJ} PROJ_MODE_T;


typedef enum {UNKN_PART,
		POINT_PART,	/* single point particle */
		TRIANGLE_PART,
		SQUARE_PART,
		CUBE_PART} PART_T;

#define PARTICLE_TYPE_STR_LEN 9

#define POINT_PART_STR		"point   "
#define TRIANGLE_PART_STR	"triangle"
#define SQUARE_PART_STR		"square  "
#define CUBE_PART_STR		"cube    "



/* define individual particle structure */
typedef struct particle_s_t {
   wpointType	position;	/* current position of particle */
   vectorType	velocity;	/* direction and velocity of travel */
   COLOR_S_T	color;		/* color of particle */
   int		age;		/* current age of particle */
   int		life;		/* expected life of particle */
   BOOLEAN_T	valid;		/* flag if valid primitive */
} PARTICLE_S_T;


/* define particle system structure */
typedef struct psystem_s_t {
   PART_T	type;			/* type of particle */
   int		new_count;		/* number of new particles per iter */
   int		count;			/* actual number of particles */
   PARTICLE_S_T	plist[MAX_PARTICLES]; 	/* array of particles */
   wpointType	start_pos_mean;		/* starting position mean */
   wpointType	start_pos_var;		/* starting position variance */
   float	start_pos_radius;	/* starting position radius */
   vectorType	start_vel_mean;		/* starting velocity mean */
   vectorType	start_vel_var;		/* starting velocity variance */
   COLOR_S_T	start_col_mean;		/* starting color mean */
   COLOR_S_T	start_col_var;		/* starting color variance */
   int		start_life_mean;	/* starting lifetime mean */
   int		start_life_var;		/* starting lifetime variance */
} PSYSTEM_S_T;


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
} ANIM_S_T;


/* define model structure */ 
typedef struct model_s_t {
   int		psys_count;		 /* number of particle systems */
   PSYSTEM_S_T	psys_list[MAX_PSYSTEMS]; /* array of particle systems */
   int		current_time;		 /* time since start of simulation */
   VIEW_S_T	view;			 /* view structure */
   COLORMAP_S_T	colormap;		 /* color map structure */
   ANIM_S_T	anim;			 /* animation structure */
} MODEL_S_T;


/* extern all function prototypes */
extern void ClearColorMap();

extern RASTER_T raster;


#endif /* _PARTICLE_H */
/* end of particle.h */
