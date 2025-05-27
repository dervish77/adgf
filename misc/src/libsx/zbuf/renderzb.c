/* 3-D renderer of models from the model program, using z-buffering for hidden
   surface removal and scan-line filling.  Matt Ward, 7/23/92 */
/* model file format is:
   num_vertices num_edges num_polygons (3 ints)
   vertex_list (3 floats each)
   edge_list (2 ints each)
   polygon_list (int edge_count, int edge_list, int color, 3 floats for normal)

   view file is:
   world bounds (6 floats - mins then maxs)
   viewport bounds (4 ints - mins then maxs)
   view reference point (3 floats)
   look at point (3 floats)
   up vector point (3 floats)
   eye point (3 floats)
   light point (3 floats)
   */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "libsx.h"               /* should come first, defines gfx stuff    */
#include "main.h"              /* where program specific stuff is defined */
#include "callbacks.h"         /* prototypes for callback functions       */


/* define's */
#define PI 3.1459
#define X_SIZE 600     /* default window size, change as desired */
#define Y_SIZE 600
#define MAXLIGHT 250	/* lighting limits for grey scale */
#define AMBIENT 80
#define BACKGROUND 40
#define MAXOBJ	1000
#define MIN(a,b)	(((a) < (b))? (a):(b))
#define MAX(a,b)	(((a) > (b))? (a):(b))

/* these return index of point at each end of polygon a, edge b */
#define POLY2PTS(a, b)	e_buf[p_buf[a].edge[b]].start
#define POLY2PTE(a, b)	e_buf[p_buf[a].edge[b]].end

/* useful data types */
typedef int INDEX;
typedef float VECTOR[4];
typedef float MATRIX[4][4];

/* point, edge, and polygon structures */
struct WPoint
{
  float x, y, z;
};
typedef struct WPoint WPOINT;

struct Extent 
{
  float min, max;
};
typedef struct Extent EXTENT;

struct MyEdge
{
/* indices into point/vertex list */
  INDEX start, end;
};
typedef struct MyEdge EDGE;

struct Poly
{
/* size of edge list, values (indices into edge list), and normal */
  int size;
  INDEX *edge;
  INDEX color;
  VECTOR norm, tnorm;	/* original and transformed normal */
};
typedef struct Poly POLY;

/* buffers for various data and index into them */
EDGE e_buf[MAXOBJ];
POLY p_buf[MAXOBJ];
INDEX v_count = 0, e_count = 0, p_count = 0;
/* original vertex list, transformed list, and important points for viewing */
WPOINT v_buf[MAXOBJ], tv_buf[MAXOBJ], vrp, look, up, eye, light;
VECTOR u, v, n;	/* view vectors */
MATRIX viewmat;	/* viewing matrix */
/* world and viewport bounds */
WPOINT low_w, hi_w;
XPoint low_v, hi_v;
float *z_buffer;
INDEX *v_index;		/* index of points in a polygon */

FILE *inf, *view;	/* model and viewing files - see README for formats */
MyProgram mydata;

void main(int argc, char **argv)
{
  char *malloc();
  if(argc < 3)	{
	printf("usage: render modelfile viewfile\n");
	exit(-1);
	}

/* open files for input */
   inf = fopen(argv[1], "r");
   if(inf == NULL)      {
        printf("failed to open %s\n", argv[1]);
        exit(-1);
        }
   view = fopen(argv[2], "r");
   if(view == NULL)      {
        printf("failed to open %s\n", argv[2]);
        exit(-1);
        }
/* read data, transform points to viewing system, and perform scan fill and
   z-buffer */
  file_in();
  view_in();
  trans_pts();

/* make space of bitmap and z-buffer */
  mydata.bitmap = (char *)malloc(X_SIZE*Y_SIZE);
  if (mydata.bitmap == NULL)
   {
     fprintf(stderr, "Fooey, no memory for bitmap.\n");
     exit(10);
   }
  z_buffer = (float *)malloc(X_SIZE*Y_SIZE * sizeof(float));  
  if (z_buffer == NULL)
   {
     fprintf(stderr, "Fooey, no memory for z_buffer.\n");
     exit(10);
   }
  mydata.bitmap_width   = X_SIZE;
  mydata.bitmap_height  = Y_SIZE;
 
  fill_buf(X_SIZE, Y_SIZE);

  init_display(argc, argv, &mydata);  /* setup the display */

  MainLoop();                         /* go right into the main loop */
}



/* This function sets up the display.  For any kind of a real program, 
 * you'll probably want to save the values returned by the MakeXXX calls
 * so that you have a way to refer to the display objects you have 
 * created (like if you have more than one drawing area, and want to
 * draw into both of them).
 */

void init_display(int argc, char **argv, MyProgram *me)
{
  Widget w[5];

  if (OpenDisplay(argc, argv) == FALSE)
    return;

  w[0] = MakeButton("Quit!",     quit,    me);

  w[1] = MakeLabel("This is a label");

  w[2] = MakeDrawArea(X_SIZE, Y_SIZE, redisplay, me);

  
  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE, NULL);
  SetWidgetPos(w[2], PLACE_UNDER, w[0], NO_CARE, NULL);
  

  /* This call actually causes the whole thing to be displayed on the
   * screen.  You have to call this function before doing any drawing
   * into the window.
   */
  ShowDisplay();
  
  GetAllColors();
  SetColorMap(GREY_SCALE_2);
}

/* read in the model file, allocating space for edge list for polygons */

file_in()
{
   int i, j;
   char *malloc();
   fscanf(inf, "%d %d %d", &v_count, &e_count, &p_count);

   for(i = 0;i < v_count;i++)	/* vertices */
        fscanf(inf, "%f %f %f", &v_buf[i].x, &v_buf[i].y, &v_buf[i].z);

   for(i = 0;i < e_count;i++)	/* edge list */
        fscanf(inf, "%d %d", &e_buf[i].start, &e_buf[i].end);

   for(i = 0;i < p_count;i++)   {	/* polygon structure */
        fscanf(inf, "%d", &p_buf[i].size);
	p_buf[i].edge = (INDEX *)malloc(p_buf[i].size * sizeof(INDEX));
	if(p_buf[i].edge == NULL)	{
	   printf("failed to allocate space for edges\n");
	   exit(-1);
	   }
        for(j = 0;j < p_buf[i].size;j++)
           fscanf(inf, "%d", &p_buf[i].edge[j]);
        fscanf(inf, "%d", &p_buf[i].color);
        fscanf(inf, "%f %f %f", &p_buf[i].norm[0], &p_buf[i].norm[1],
           &p_buf[i].norm[2]);
        }
   fclose(inf);
}

/* read in viewing data, compute viewing transformation matrix */

view_in()
{
   int lx, ly, hx, hy, i, j;
   VECTOR tempv;
   MATRIX tmpview;
/* read world and viewport boundaries */
   fscanf(view, "%f %f %f %f %f %f", &low_w.x, &low_w.y, &low_w.z, &hi_w.x,
	&hi_w.y, &hi_w.z);
   fscanf(view, "%d %d %d %d", &lx, &ly, &hx, &hy);
   low_v.x = lx;
   low_v.y = ly;
   hi_v.x = hx;
   hi_v.y = hy;
/* read vectors for viewing coordinate system, eye and light location */
   fscanf(view, "%f %f %f", &vrp.x, &vrp.y, &vrp.z);
   fscanf(view, "%f %f %f", &look.x, &look.y, &look.z);
   fscanf(view, "%f %f %f", &up.x, &up.y, &up.z);
   fscanf(view, "%f %f %f", &eye.x, &eye.y, &eye.z);
   fscanf(view, "%f %f %f", &light.x, &light.y, &light.z);
   fclose(view);
/* compute n, u, and v vectors */
   n[0] = look.x - vrp.x;
   n[1] = look.y - vrp.y;
   n[2] = look.z - vrp.z;
   n[3] = 1.0;
/* up vector is approximate - we make it orthogonal thru cross products */
   tempv[0] = up.x - vrp.x;
   tempv[1] = up.y - vrp.y;
   tempv[2] = up.z - vrp.z;
   tempv[3] = 1.0;
   cross_prod(n, tempv, v);	/* check this for rhs or lhs */
   cross_prod(n, v, u);
/* normalize everything and create viewing transformation matrix */
   normalize(n);  normalize(u);  normalize(v);
   identity(viewmat);
   for(i = 0;i < 3;i++)	{
	viewmat[0][i] = n[i];
	viewmat[1][i] = u[i];
	viewmat[2][i] = v[i];
	}
   }

/* transform all points and normals according to viewing matrix */

trans_pts()
{
   int i;
   float d;
   VECTOR vin, vout;
   d = -eye.z;
   for(i = 0;i < v_count;i++)	{
/* change points to vectors, subtracting view reference point first */
	vin[0] = v_buf[i].x - vrp.x;
	vin[1] = v_buf[i].y - vrp.y;
	vin[2] = v_buf[i].z - vrp.z;
	vin[3] = 1.0;
/* multiply by viewing matrix, then adjust x and y to give perspective view */
	vecmult(vin, viewmat, vout);
	tv_buf[i].x = vout[0] * d / (d + vout[2]);
	tv_buf[i].y = vout[1] * d / (d + vout[2]);;
	tv_buf[i].z = vout[2];
	}
/* compute transformed normal and normalize it for later use */
   for(i = 0;i < 3;i++)
	viewmat[3][i] = 0.0;
   for(i = 0;i < p_count;i++)	{
	vecmult(p_buf[i].norm, viewmat, p_buf[i].tnorm);
	normalize(p_buf[i].tnorm);
	}
   }


/* create polylines and do scan-line fill and z_buffering */

int fill_buf(int width, int height)
{
   int i, j, k, col;
   char *cptr = mydata.bitmap;
   char *malloc();
   float *zb = z_buffer;
   XPoint *poly;
/* initialize image and z-buffer */
   for(i = 0;i < height;i++)
	for(j = 0;j < width;j++)	{
		*(zb++) = hi_w.z;
		*(cptr++) = BACKGROUND;
		}

/* for each polygon... */
  for(i = 0;i < p_count; i++)	{
/* ignore if transformed normal is positive (in viewing direction) */
	if(p_buf[i].tnorm[2] > 0.0)
	   continue;
/* compute and set color */
   	col = FindColor(i);             
	k = 0;
	poly = (XPoint *)malloc((p_buf[i].size+1) * sizeof(XPoint));
	if(poly == NULL)	{
	   printf("failed to allocate space for polygons\n");
	   return;
	   }
	v_index = (INDEX *)malloc((p_buf[i].size+1) * sizeof(INDEX));
	if(v_index == NULL)	{
	   printf("failed to allocate space for indices\n");
	   return;
	   }
/* create a polyline, switching order of points on edge as needed */
	for(j = 0;j < p_buf[i].size;j++)	{
	   if(inorder(i,j) == 1)	{
    		wv_convert(tv_buf[POLY2PTE(i,j)], &poly[k]);
		v_index[k] = POLY2PTE(i,j);
/* note we have to flip the Y to make up be positive */
		poly[k].y = Y_SIZE - poly[k].y;
		k++;
		}
	   if(inorder(i,j) == -1)	{
    		wv_convert(tv_buf[POLY2PTS(i,j)], &poly[k]);
		v_index[k] = POLY2PTS(i,j);
		poly[k].y = Y_SIZE - poly[k].y;
		k++;
		}
/* somehow, we don't have edges in the proper order if this is reached */
	   if(inorder(i,j) == 0)
		printf("OOPS - broken polygon %d\n", i);
	   }
/* output filled polygon */
	poly[k].x = poly[0].x;
	poly[k].y = poly[0].y;
	v_index[k] = v_index[0];
	scan_line(i, poly, k, col);
	free(poly);
	free(v_index);
	}
   }

/* check if the start and end of the edge are in the right order */

inorder(int p, int e)
{
   int next;
/* get index to next edge in polygon */
   if(e == p_buf[p].size-1)
	next = 0;
   else
	next = e + 1;
/* if the end of the current one is the same point as one of the next, we
   are in order */
   if(POLY2PTE(p,e) == POLY2PTS(p,next) || POLY2PTE(p,e) == 
	POLY2PTE(p,next))
	return(1);
/* if the start of the current one is the same point as one of the next, we
   need to flip the order */
   if(POLY2PTS(p,e) == POLY2PTS(p,next) || POLY2PTS(p,e) == 
	POLY2PTE(p,next))
	return(-1);
/* if neither in current is contained in next, we are in trouble */
   return(0);
   }

/* compute the proper shading as cosine of transformed normal with light
   source.  NOTE: light source is enterred in viewing coordinates */

FindColor(int p)
{
   VECTOR tolight;
   float dotprod();
   int res;
/* compute vector from first point of polygon to light source */
   tolight[0] = light.x - tv_buf[POLY2PTS(p, 0)].x;
   tolight[1] = light.y - tv_buf[POLY2PTS(p, 0)].y;
   tolight[2] = light.z - tv_buf[POLY2PTS(p, 0)].z;
   tolight[3] = 1.0;
/* normalize and compute cosine, scaled into color range */
   normalize(tolight);
   res = (int)((float)(p_buf[p].color) * dotprod(tolight, p_buf[p].tnorm));
/* adjust accordingly with ambient intensity */
   if(res < 0)
	return(AMBIENT);
   if((res+AMBIENT) > MAXLIGHT)
	return(MAXLIGHT);
   return(res + AMBIENT);
   }

/* draw all lines and also lines from center of polygons in direction of
   normal */

void draw_lines(int width, int height)
{
  int i, j;
  XPoint p1, p2;
  WPOINT n1, n2;
  
  SetColor(WHITE);             
/* convert each end of an edge to device coordinates */
  for(i=0; i < e_count; i++)	{
    wv_convert(tv_buf[e_buf[i].start], &p1);
    wv_convert(tv_buf[e_buf[i].end], &p2);
/* draw line after adjusting y value to get up to be positive */
    DrawLine(p1.x, Y_SIZE - p1.y, p2.x, Y_SIZE - p2.y);
    }
/* make normals red */
  SetColor(RED);
/* for each polygon, find average of vertices involved */
  for(i = 0;i < p_count; i++)	{
	n1.x = n1.y = n1.z = 0.0;
	for(j = 0;j < p_buf[i].size;j++)	{
	   n1.x += tv_buf[e_buf[p_buf[i].edge[j]].start].x;
	   n1.x += tv_buf[e_buf[p_buf[i].edge[j]].end].x;
	   n1.y += tv_buf[e_buf[p_buf[i].edge[j]].start].y;
	   n1.y += tv_buf[e_buf[p_buf[i].edge[j]].end].y;
	   n1.z += tv_buf[e_buf[p_buf[i].edge[j]].start].z;
	   n1.z += tv_buf[e_buf[p_buf[i].edge[j]].end].z;
	   }
/* divide by twice the number of points, since each encounterred twice */
	n1.x = n1.x / ((float)(2 * p_buf[i].size));
	n1.y = n1.y / ((float)(2 * p_buf[i].size));
	n1.z = n1.z / ((float)(2 * p_buf[i].size));
/* second point is the first offset by the transformed normal */
	n2.x = n1.x + p_buf[i].tnorm[0];
	n2.y = n1.y + p_buf[i].tnorm[1];
	n2.z = n1.x + p_buf[i].tnorm[2];
/* convert to device coordinates and output */
    	wv_convert(n1, &p1);
    	wv_convert(n2, &p2);
    	DrawLine(p1.x, Y_SIZE - p1.y, p2.x, Y_SIZE - p2.y);
	}
}

/* window to viewport conversion routine */

wv_convert(WPOINT wp, XPoint *vp)
{
  vp->x = low_v.x + (int)(((float)(hi_v.x - low_v.x)*(wp.x - low_w.x)) /
	(hi_w.x - low_w.x));
  vp->y = low_v.y + (int)(((float)(hi_v.y - low_v.y)*(wp.y - low_w.y)) /
	(hi_w.y - low_w.y));
  }

/* multiply a vector by a matrix, giving a vector */

int matmult(MATRIX m1, MATRIX m2, MATRIX matres)
{

  int i,j, k;    /*  counter loop indicies                   */
  float sum;  /*  a temp value to hold intermediate sums  */

     for (i=0; i<4; i++) {
	for(j = 0;j < 4;j++)	{
           sum= 0.0;
           for (k=0; k<4; k++) {
           sum= sum + m1[i][k]*m2[k][j];
           }
        matres[i][j] = sum;
	}
     }
}

int vecmult(VECTOR vec,MATRIX m,VECTOR vecres)
{

  int i,j;    /*  counter loop indicies                   */
  float sum;  /*  a temp value to hold intermediate sums  */

     for (i=0; i<4; i++) {
        sum= 0.0;
        for (j=0; j<4; j++) {
           sum= sum + m[j][i]*vec[j];
        }
        vecres[i]= sum;
     }
}

/* create an identity matrix */

int identity(MATRIX m)
{
  int i,j;     /*   counter loop indicies  */
  for (i= 0; i<4; i++)
     for (j= 0; j<4; j++)
        if (i==j)
             m[i][j]= 1.0;
        else
             m[i][j]= 0.0;
  }

/* perform cross product of 2 vectors */

cross_prod(VECTOR v1,VECTOR v2,VECTOR cp)
{
   cp[0] = v1[1]*v2[2] - v1[2]*v2[1];
   cp[1] = v1[2]*v2[0] - v1[0]*v2[2];
   cp[2] = v1[0]*v2[1] - v1[1]*v2[0];
   cp[3] = 1.;
   }

/* normalize a vector */

normalize(VECTOR v)
{
   float size;
   int i;
   size = sqrt((double)(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
   for(i = 0;i < 3;i++)
	v[i] = v[i] / size;
   }

/* compute dot product of 2 vectors */

float dotprod(VECTOR v1,VECTOR v2)
{
   float res;
   res = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
   return(res);
   }

#define ACTIVE 1
#define INACTIVE 0

int             numedges;
struct EdgeInfo
{
  int             x, y;
  float           fx;
  float		  z, deltaz;
  char            active;
  int             deltay;
  float           deltax;
};            
struct EdgeInfo *edge;

/*****************************************************************************/

sortactive(int *list)
{

  int             cnt, i, flg, tmp;

  /* determine number of active edges */

  cnt = 0;
  for (i = 0; i < numedges; i++)
    if (edge[i].active == ACTIVE)
      list[cnt++] = i;

  /* sort active edges on increasing x */
  flg = 1;
  while(flg == 1)	{
	flg = 0;
  	for (i = 0; i < cnt-1; i++) {
            if (edge[list[i]].x > edge[list[i+1]].x)	{
		tmp = list[i];
		list[i] = list[i+1];
		list[i+1] = tmp;
		flg = 1;
		}
	   }
	}
  return (cnt);
}

/*****************************************************************************/

/* print out scan-line for a given y value, checking z-buffer for each pixel */

outpairs(int p, int *list, int num, int y, int col)
{
  int             i = 0, j;
  int x1, x2;
  float z1, z2, zch;

  /* go through list 2 at a time, scale points, and print out */
  if(y < 0 || y >= Y_SIZE)
	return;
  if((num%2) != 0)	{
	printf("WOOPS - odd number of points in active edge list %d\n", num);
	return;
	}
  while (i < num)
  {
/* make sure end points are within the proper range */
    x1 = edge[list[i]].x;
    if(x1 < 0) x1 = 0;
    if(x1 >= X_SIZE) 	{
	i += 2;
	continue;
	}
    x2 = edge[list[i + 1]].x;
    if(x2 < 0) 
	x2 = 0;
    if(x2 >= X_SIZE) 
	x2 = X_SIZE-1;
/* get the z values and compute amount of interpolation across row */
    z1 = edge[list[i]].z;
    z2 = edge[list[i+1]].z;
    zch = (z2 - z1) / ((float)(x2 - x1));
    for(j = x1;j < x2;j++)	{
/* if the point is closest, update z-buffer and store pixel */
	if(z1 < *(z_buffer + y * X_SIZE + j))	{
	   *(z_buffer + y*X_SIZE + j) = z1;
	   *(mydata.bitmap + y * X_SIZE + j) = (char)col;
	   }
	z1 = z1 + zch;
	}
/* go to next pair of points */
    i = i + 2;
  }

}

/*****************************************************************************/

/* update active edge table */

updateedge(int y)
{

  int             i, j;

  /* for each edge ... */

  for (i = 0; i < numedges; i++)
  {
    /* if it was active and we are beyond it, make it inactive */
    if (edge[i].active == ACTIVE && edge[i].deltay <= 0)
      edge[i].active = INACTIVE;

    /*
     * if it is still active, decrement count for number of scanlines it is
     * active and update both the the float and integer (rounded) x coords
     */
    if (edge[i].active == ACTIVE)
    {
      edge[i].deltay--;
      edge[i].fx = edge[i].fx + edge[i].deltax;
      edge[i].x = (int) (edge[i].fx + 0.5);
      edge[i].z = edge[i].z + edge[i].deltaz;
    }

    /*
     * if it had been inactive and scanline at start of edge, make active
     */
    if (edge[i].active == INACTIVE && edge[i].y == y)
      edge[i].active = ACTIVE;
  }

}


/*****************************************************************************/

/*
 * get edges and store by maximum y value, returning min and max y; modify
 * length of redges whose next (or prev) edge goes in same direction
 */

inputlist(int *start, int *end, XPoint *points, int num)
{

  int             i, j, next, nextnext, prev;
  char *malloc();
  *end = Y_SIZE+1;
  *start = 0;
  numedges = num;
/* compute minimum and maximum y */

  edge = (struct EdgeInfo *)malloc((num+1) * sizeof(struct EdgeInfo));
  if(edge == NULL)	{
	printf("failed to malloc space for edge info\n");
	return;
	}
  for (i = 0; i < num + 1; i++)
  {
    if (points[i].y < (*end))
      *end = points[i].y;
    else if (points[i].y > (*start))
      *start = points[i].y;

  }
  j = 0;

  /* store according to max y for each edge */

  for (i = 1; i < num + 1; i++)
  {
    edge[j].active = INACTIVE;	/* all are initially inactive */

    /*
     * need next, one beyond, and previous edge to determine maxn and point
     * of local min/max.  NOte mod function used to wrap around to first edge
     */
    next = (i + 1) % (num);
    nextnext = (i + 2) % (num);
    prev = i - 1;
    /* if current is bigger than next... */
    if (points[i].y > points[next].y)
    {
      edge[j].y = points[i].y;
      edge[j].x = points[i].x;
      edge[j].fx = (float) (points[i].x);

      /* compute change in x and z for each scanline */

      edge[j].deltax = ((float) (points[next].x - points[i].x)) /
	((float) (points[i].y - points[next].y));
      edge[j].z = v_buf[v_index[i]].z;
      edge[j].deltaz = (v_buf[v_index[next]].z - v_buf[v_index[i]].z) /
	((float) (points[i].y - points[next].y));

      /*
       * compute total change in y, shortening by 1 if not a minima or maxima
       */

      edge[j].deltay = points[i].y - points[next].y;
      if (points[next].y > points[nextnext].y)
	edge[j].deltay--;
      j++;
    }
    else if (points[i].y < points[next].y)
    {
      /*
       * same as above if current is less than next.  Note horizontal lines are
       * ignored.  Note check of previous instead of nextnext to determine if
       * minima or maxima
       */
      edge[j].y = points[next].y;
      edge[j].x = points[next].x;
      edge[j].fx = (float) (points[next].x);
      edge[j].deltax = ((float) (points[i].x - points[next].x)) /
	((float) (points[next].y - points[i].y));
      edge[j].deltay = points[next].y - points[i].y;
      edge[j].z = v_buf[v_index[next]].z;
      edge[j].deltaz = (v_buf[v_index[i]].z - v_buf[v_index[next]].z) /
	((float) (points[next].y - points[i].y));
      if (points[prev].y < points[i].y)
	edge[j].deltay--;
      j++;
    }
  }

  numedges = j;

}

/*****************************************************************************/

int scan_line(int p, XPoint *points, int n, int col)
{

  int             curry, endy;
  int             active, *xlist;
  char *malloc();

  /* enter edges and initialize structure, saving start and end y */

  inputlist(&curry, &endy, points, n);
  curry++;
/* allocate space for list of x values */
  xlist = (int *)malloc((n+1) * sizeof(int));
  if(xlist == NULL)	{
	printf("failed to allocate space for x list\n");
	return;
	}

  /* until we are beyond the end of the region... */
  while (curry >= endy)
  {
    /* get sorted list of x values of active edges */
    active = sortactive(xlist);
    /* print out lines between pairs o fcoordinates... */
    outpairs(p, xlist, active, curry, col);
    /* move to next scan line... */
    curry--;
    /* update the active edge list */
    updateedge(curry);
  }
  free(edge);
  free(xlist);
}
