/********************************************************************

   This program renders an image of a 3D object.  This program 
   assumes that thte model file contains a particular format listing
   vertices, edges and polygons.  All polygons must be triangles.

   Author:    Brian Lingard

   File:      render.c
 
   Usage:     render [-m file][-v file][[-w]||[-s]||[-f]][-a][[-l]||[-p]]

   Options:
     -m file  default "data"   	       input model data file of object
     -v file  default "view"           input view file
     -w       default off              wireframe render enable
     -s       default off              solid render enable
     -f       default enabled          shaded render enable
     -a       default off              shows all views - front, top, side
     -l       default enabled          shows parallel view
     -p       default off              shows perspective view
     -n       default on               disable coord normalizing
     -t       default off              enable stereo viewing

   Make string:  make all or make render

   Revision History:
     5 3/18/95   modified for stereo viewing
     4 12/3/94   copied from render2.c, modified for shading calcs
     3 10/29/94  copied from render1.c, modified for perspective
     2 10/18/94  added functions to clip and draw lines
     1 10/10/94  added functions to divide screen into quadrants
     0  9/20/94  originated

*********************************************************************/


/* include necessary files */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "render.h"

#define DEBUG 1


/*  define some global variables 
 */

/* model data array counts */
int vertex_count=0;
int edge_count=0;
int polygon_count=0;

/* main model data arrays */
vertexType vertex_list[MAX_VERTS];	/* list of vertices - 3D coords */
edgeType edge_list[MAX_EDGES];		/* list of edges */
polygonType polygon_list[MAX_POLYS];	/* list of polygons */
matrixType HG_coord[MAX_VERTS];		/* list of homogeneous coords */

/* mode flags */
renderType render_mode = FULL_REND;
projectType projection_mode = PARALLEL;
displayType display_mode = ONLY_CAMERA;
normalizeType norm_flag = NORMALIZE_VIEW_VOLUME;

/* view related info */
viewrangeType view_data[NUM_OF_VIEWS];	/* used for three simul. views */
viewdataType view;			/* used for para & pers views */
viewplaneType vplane;			/* view plane information */

/* various file pointers */
FILE *modfile;			/* pointer to model data file */
FILE *viewfile;			/* pointer to view file */
FILE *debugfile;		/* pointer to debug file */



/******************************************************************

  main()  

******************************************************************/
main(argc,argv)
   int argc;
   char *argv[];
{

   char mod_file_name[BUFLEN];		/* input model data file */
   char view_file_name[BUFLEN];		/* input view file */
   char debug_file_name[BUFLEN];	/* output debug file */
   char format[BUFLEN];

   int i;

   int InitDisplayScreen();
   int DrawScreenBorders();
   int DrawScreenText();
   int DrawAxes();
   int CheckForQuit();


/* set up file names */
   sprintf(mod_file_name, "data");
   sprintf(view_file_name, "view");
   sprintf(debug_file_name, "vwdebug.log");

/* check command line arguments */
   switch(argc) {
     case 1:			/* use defaults args */
        break;
     default:			/* check args and parse */
        if (argc > MAX_ARGS) {
           sprintf(format,
              "usage: %s [-m file][-v file][[-w]||[-s]||[-f]][-t][-a][[-l]||[-p]]",
              argv[0]);
           ErrPrint(format, 0);
        }
        else {                  /* parse argument inputs */
           i = 1;
           while (i < argc) {
              switch(argv[i][1]) {	/* switch on dash option */
                 case 'm':
                    sprintf(mod_file_name, "%s", argv[i+1]);
                    i++;
                    break;
                 case 'v':
                    sprintf(view_file_name, "%s", argv[i+1]);
                    i++;
                    break;
                 case 'w':
                    render_mode = WIRE_REND;
                    break;
                 case 's':
                    render_mode = SOLD_REND;
                    break;
                 case 'f':
                    render_mode = FULL_REND;
                    break;
                 case 't':
                    display_mode = STEREO;
                    break;
                 case 'a':
                    display_mode = ALL;
                    break;
                 case 'l':
                    projection_mode = PARALLEL;
                    break;
                 case 'p':
                    projection_mode = PERSPECTIVE;
                    break;
                 case 'n':
                    norm_flag = DONT_NORMALIZE;
                    break;
                 default:
                    ErrPrint("Main: unknown option(s) specified",1);
              } /* end inner switch */
              i++;
           } /* end while */
        } /* end else */
     break;
   } /*end outer switch */

/* open model input file */
   modfile = fopen(mod_file_name,"r");
   if (modfile == (FILE *) NULL) {
      sprintf(format,"Main: could not open '%s' as model input file", mod_file_name);
      ErrPrint(format, 3);
   }

/* open view input file */
   viewfile = fopen(view_file_name,"r");
   if (viewfile == (FILE *) NULL) {
      sprintf(format,"Main: could not open '%s' as view input file", view_file_name);
      ErrPrint(format, 3);
   }

/* open debug output file */
   if (DEBUG) {
      debugfile = fopen(debug_file_name,"w");
      if (debugfile == (FILE *) NULL) {
         sprintf(format,"Main: could not open '%s' as debug output file", debug_file_name);
         ErrPrint(format, 99);
      }
   }

/* declare display screen and other init stuff */
   InitDisplayScreen();

/* read in the model's data file and view file */
   printf("\nReading '%s' as Model Data File\n", mod_file_name);
   ReadModelData();
   printf("\nReading '%s' as View File\n", view_file_name);
   ReadViewFile();

/* begin rendering object here */
   printf("\nRendering model -");
   switch(display_mode) {
      case ALL:
         printf(" showing all views ...\n");
         DrawScreenBorders();
         DrawScreenText();
         Draw_View(XYVIEW);
         Draw_View(ZYVIEW);
         Draw_View(XZVIEW);
         if (projection_mode == NONE)
            DrawAxes();
         else {
            view.vpx.min = SCREEN_WIDTH / 2;
            view.vpy.min = 0.0;
            view.vpx.max = SCREEN_WIDTH;
            view.vpy.max = SCREEN_HEIGHT / 2;
            RenderCameraView();
         }
         break;
      case ONLY_CAMERA:
         switch(projection_mode) {
            case PARALLEL:
               printf(" showing parallel view ...\n");
               break;
            case PERSPECTIVE:
               printf(" showing perspective view ...\n");
               break;
            default:
               fprintf(stderr, "\nERROR - must select projection mode\n");
               exit(1);
         }
         DrawScreenText();
         RenderCameraView();
         break;
      case STEREO:
         switch(projection_mode) {
            case PARALLEL:
               printf(" showing parallel view ...\n");
               break;
            case PERSPECTIVE:
               printf(" showing perspective view ...\n");
               break;
            default:
               fprintf(stderr, "\nERROR - must select projection mode\n");
               exit(1);
         }
         DrawScreenBorders();
         DrawScreenText();
         ComputeEyeView();

         /* render left eye view */
         SaveVertexList();
         view.vpx.min = 0.0;
         view.vpy.min = 0.0;
         view.vpx.max = SCREEN_WIDTH / 2;
         view.vpy.max = SCREEN_HEIGHT / 2;
         SetEyeView(LEFT);
         RenderCameraView();

         /* render right eye view */
         RestoreVertexList();
         view.vpx.min = SCREEN_WIDTH / 2;
         view.vpy.min = 0.0;
         view.vpx.max = SCREEN_WIDTH;
         view.vpy.max = SCREEN_HEIGHT / 2;
         SetEyeView(RIGHT);
         RenderCameraView();
         break;
      default:
         sprintf(format, "MAIN: unknown display mode - %d\n", display_mode);
         ErrPrint(format, 0);
         break;
   }

/* loop forever, until QUIT selected */
   printf("\nHit 'q' or 'Q' to quit program\n");
   while (1) {
      if (CheckForQuit() > 0) break;
   } /* end of forever loop */

   Cleanup();	/* close file pointers and deallocate memory */
} /* end of main */


/******************************************************************

  ReadModelData() -- This function reads in the model's data file
	(please note that the file is currently assumed to consist
	of triangles for the polygons) 

	file format is

	vert count, edge count, polygon count - all ints
	list of float triplets
	list of int doublets
	list of polygons
	    each line is
		number of edges - int
		list of edge indices - 3 ints
		list of vertex indices - 3 ints
		color index - int
		normal vector - float triplet

******************************************************************/
int
ReadModelData()
{
   int v, e, p;  /* loop indices */
   float x, y, z;
   int sv, ev;
   int numedges, edge1, edge2, edge3, color;
   int vert1, vert2, vert3;
   float normx, normy, normz;

   /* input vertex, edge, and polygon counts */
   fscanf(modfile, "%d %d %d\n", 
      &vertex_count, &edge_count, &polygon_count);

   /* input vertex list */
   for (v = 0; v < vertex_count; v++) {
      fscanf(modfile, "%f %f %f\n", &x, &y, &z);
      vertex_list[v].x = x;
      vertex_list[v].y = y;
      vertex_list[v].z = z;
   }

   /* input edge list */
   for (e = 0; e < edge_count; e++) {
      fscanf(modfile, "%d %d\n", &sv, &ev);
      edge_list[e].sv = sv;
      edge_list[e].ev = ev;
   }

   /* input polygon list */
   for (p = 0; p < polygon_count; p++) {
      fscanf(modfile, "%d %d %d %d %d %d %d %d %f %f %f\n", 
         &numedges,
         &edge1, &edge2, &edge3,
         &vert1, &vert2, &vert3,
         &color,
         &normx, &normy, &normz);
      polygon_list[p].num_edges = numedges;
      polygon_list[p].edge_list[0] = edge1;
      polygon_list[p].edge_list[1] = edge2;
      polygon_list[p].edge_list[2] = edge3;
      polygon_list[p].vert_list[0] = vert1;
      polygon_list[p].vert_list[1] = vert2;
      polygon_list[p].vert_list[2] = vert3;
      polygon_list[p].color = color;
      polygon_list[p].normal.x = normx; 
      polygon_list[p].normal.y = normy;
      polygon_list[p].normal.z = normz;
   }

   return(0);
} /* end of ReadModelData() */


/******************************************************************

  ReadViewFile() -- This function reads in the view file for this model.

	file format is

	world bounds - x,y,z mins then x,y,z maxs all floats
	viewport bounds - x,y mins then x,y maxs all ints
	view reference point - float triplet
	look at point - float triplet
	view up vector - float triplet
	eye location - float triplet
	light location - float triplet

******************************************************************/
int
ReadViewFile()
{
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

   /* read in view boundaries */
   fscanf(viewfile, "%f %f %f %f %f %f\n", 
   			&view.vbx.min, &view.vby.min, &view.vbz.min,
   			&view.vbx.max, &view.vby.max, &view.vbz.max);

   /* read in viewport boundaries */
   fscanf(viewfile, "%d %d %d %d\n", &view.vpx.min, &view.vpy.min, &view.vpx.max,  &view.vpy.max);

   /* read in view reference point */
   fscanf(viewfile, "%f %f %f\n", &view.vrp.x, &view.vrp.y, &view.vrp.z);

   /* read in view look at point */
   fscanf(viewfile, "%f %f %f\n", &view.lap.x, &view.lap.y, &view.lap.z);

   /* read in view up vector */
   fscanf(viewfile, "%f %f %f\n", &view.vup.x, &view.vup.y, &view.vup.z);

   /* read in eye location */
   fscanf(viewfile, "%f %f %f\n", &view.eyeloc.x, &view.eyeloc.y, &view.eyeloc.z);

   /* read in light location */
   fscanf(viewfile, "%f %f %f\n", &view.lightloc.x, &view.lightloc.y, &view.lightloc.z);

   /* read view for xy-plane, then zy-plane, then xz-plane */
/*   for (i = 0; i < (NUM_OF_VIEWS - 1); i++) {
      fscanf(viewfile, "%f %f %f %f\n", 
             &view_data[i].wxmin, &view_data[i].wymin,
             &view_data[i].wxmax, &view_data[i].wymax);
   }*/

   view_data[0].wxmin = view.vbx.min;
   view_data[0].wymin = view.vby.min;
   view_data[0].wxmax = view.vbx.max;
   view_data[0].wymax = view.vby.max;

   view_data[1].wxmin = view.vbz.min;
   view_data[1].wymin = view.vby.min;
   view_data[1].wxmax = view.vbz.max;
   view_data[1].wymax = view.vby.max;

   view_data[2].wxmin = view.vbx.min;
   view_data[2].wymin = view.vbz.min;
   view_data[2].wxmax = view.vbx.max;
   view_data[2].wymax = view.vbz.max;

   return(0);
} /* end of ReadViewFile() */


/******************************************************************

  ErrPrint - prints error message and exits program

******************************************************************/
int
ErrPrint(format, code)
   char *format;	/* error message string */
   int code;		/* error code */
{
   fprintf(stderr,"Error %d: %s\n", code, format);
   exit(1);
   return(0);
} /* end of ErrPrint() */


/*****************************************************************
*  Cleanup() -- cleanup misc pointers and allocated memory       *
******************************************************************/
int
Cleanup()
{

/* close all file pointers used */
   fclose(modfile);
   fclose(viewfile);
   if (DEBUG)
      fclose(debugfile);

   return(0);
} /* end of Cleanup() */

/* end of file render.c */
