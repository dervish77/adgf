/********************************************************************

   Header file of typedefs and defines for render.c

   Author:    Brian Lingard

   File:      render.h

   Revision
      0  3/18/95 originated

********************************************************************/


/* define some constants */
#define BUFLEN 81		/* text buffer length constant */
#define MAX_ARGS 8		/* max number of command arguments */
#define MAX_VERTS 500		/* max number of vertices */
#define MAX_EDGES 500		/* max number of edges */
#define MAX_POLYS 500		/* max number of polygons */
#define SIZE_OF_POLY 3		/* size of core polygons - triangles */
#define NUM_OF_VIEWS 4		/* number of different views */

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 800
#define MAX_PLANES 8		/* max number of bit planes for color */

#define LEFT 0
#define RIGHT 1


/* define some typedefs */
typedef enum {UNKN_REND=0, WIRE_REND, SOLD_REND, FULL_REND} renderType;
typedef enum {NONE=0, PARALLEL, PERSPECTIVE} projectType;
typedef enum {ALL=0, ONLY_CAMERA, STEREO} displayType;
typedef enum {OFF=0, ON} switchType;
typedef enum {XYVIEW=0, ZYVIEW, XZVIEW, CAMERA} viewportType;
typedef enum {DONT_NORMALIZE=0, NORMALIZE_VIEW_VOLUME} normalizeType;
typedef enum {NEITHER=0, CLIP_START, CLIP_END, CLIP_BOTH} whichendType;

typedef struct {
   float x;
   float y;
   float z;
} vertexType;		/*  generic vertex or vector type */

typedef struct {
   int sv;		/* start vertex index */
   int ev;		/* end vertex index */
   int accept;		/* accept flag for clipping results */
} edgeType;

typedef struct {
   int num_edges;
   int edge_list[SIZE_OF_POLY]; /* indices of edges */
   int vert_list[SIZE_OF_POLY];	/* indices of vertices, counterclockwise */
   int color;		/* base color of surface */
   vertexType normal;	/* surface normal */
   int visible;		/* visible surface flag */
   int sorted;		/* used by depth sort */
} polygonType;

typedef struct {
   float wxmin;
   float wymin;
   float wxmax;
   float wymax;
} viewrangeType;	/* clip rectangle size */

#define MAX_MATRIX_SIZE 4

typedef struct {
   int rows;		/* number of rows in matrix */
   int cols;		/* number of columns in matrix */
   double array[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
} matrixType;

typedef struct {
   float min;
   float max;
} viewboundType;

typedef struct {
   int min;
   int max;
} viewportboundType;

typedef struct {
   viewboundType vbx;		/* view bound start and end in x */
   viewboundType vby;		/* view bound start and end in y */
   viewboundType vbz;		/* view bound start and end in z */
   viewportboundType vpx;	/* viewport bound start and end */
   viewportboundType vpy;	/* viewport bound start and end */
   vertexType vrp;		/* view reference point */
   vertexType lap;		/* look at point */
   vertexType vup;		/* view up vector */
   vertexType eyeloc;		/* eye location */
   vertexType lightloc;		/* light location */
} viewdataType;

typedef struct {
   vertexType VRP;		/* view reference point */
   vertexType PRP;		/* projection reference point */
   vertexType CW;		/* center of window */
   float umin;			/* window bounds along u axis */
   float umax;
   float vmin;			/* window bounds along v axis */
   float vmax;
   float F;			/* front and back distance for clip planes */
   float B;
   float vpd;			/* distance from PRP to CW */
   float zmin;
   vertexType scale_per;
   matrixType Uvector;		/* view plane's u axis - normalized */
   matrixType Vvector;		/* view plane's v axis - normalized */
   matrixType Nvector;		/* view plane's n axis - normalized */
   matrixType DOP;		/* direction of projection vector */
   matrixType VPN;		/* view plane normal vector */
   matrixType VUP;		/* view plane up vector */
   matrixType M;		/* view transformation matrix */
} viewplaneType;


/* end of render.h */