/**************************************************************************

   A program which generates a model file for a 3D object.

   Author:    Brian Lingard

   File:      modeler.c
 
   Usage:     modeler [-i file][-o file]

   Options:
     -i file  default file "object"   input description file of object
     -o file  default file "data"     output data file of model
 
   Make string:  make all or make modeler

   Revision History:
     6  3/18/95  made more generic
     5  12/13/94 added support for colored objects
     4  10/29/94 copied from 3D_model1.c, modified to generate normals
     3  10/16/94 modified to use transform matrices
     2  10/10/94 copied from 2D_model.c
     1  9/26/94  added more comments
     0  9/18/94	 originated

   Description:

     This program reads in a descriptive file of a 3D object which is 
   constructed out of basic 3D primitives.  The primitives are converted
   into a list of vertices, list of edges, and a list of polygons.  All
   primitives are converted using triangles as the base polygons.  The
   basic 3D primitives which are supported include the rectanglar solid, 
   the parameterized cylinder, and a right triangular prism.  The format 
   of each primitive is shown below:

	rectangular solid	- rect cx cy cz sx sy sz axis angle color
	cylindrical solid	- cyld cx cy cz r ns h axis angle color
	right triangle prism	- prsm bx by bz sx sy sz axis angle color

   where: (all numbers are floats, and use the left-hand coordinate system)

	cx - center x
	cy - center y
	cz - center z
        bx - base x
        by - base y
	bz - base z
	sx - scaling in x
	sy - scaling in y
	sz - scaling in z
        axis - which axis for rotation
			x = x-axis
			y = y-axis
			z = z-axis
			n = no rotation
        angle - amount of rotation in degrees
	color - base color of object
	r  - radius of cylinder
	ns - number of sides of circular surface
	h - height of cylinder (along z-axis)

   and color index can be:

	0 - white
	1 - black
	2 - grey
	3 - red
	4 - green
	5 - blue
	6 - yellow
	7 - cyan
	8 - magenta

***************************************************************************/


/** include necessary files **/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/** define some constants **/
#define BUFLEN 81		/* text buffer length constant */
#define MAX_ARGS 5		/* max number of command arguments */
#define MAX_PARMS 10		/* max number of parameters per primitive */
#define MAX_OBJS 50		/* max number of object primitives */
#define MAX_VERTS 500		/* max number of vertices */
#define MAX_EDGES 500		/* max number of edges */
#define MAX_POLYS 500		/* max number of polygons */
#define SIZE_OF_POLY 3		/* size of core polygons - triangles */

#define NUM_RECT_VERTS 8
#define NUM_RECT_EDGES 18
#define NUM_RECT_POLYS 12
#define NUM_PRSM_VERTS 6
#define NUM_PRSM_EDGES 12
#define NUM_PRSM_POLYS 8

#define DEFCOLOR 0		/* default polygon color */
#define DEBUG 1
#define MODELER 1

/** define some typedefs **/

typedef enum {UNKN_PRIM=0, RECT_PRIM, CYLD_PRIM, PRSM_PRIM} primType;

typedef struct {
   double x;
   double y;
   double z;
} vertexType;			/* vertex array element type */

typedef struct {
   primType primitive;
   vertexType center;		/* vector to center of object primitive */
   vertexType scaling;  	/* vector for scaling object primitive */
   char axis;			/* axis of rotation (equals 'n' if none) */
   double angle;		/* amount of rotation in degrees */
   int color;			/* desired base color of object */
} objectType;			/* object array element type */

typedef struct {
   int sv;			/* start vertex index */
   int ev;			/* end vertex index */
} edgeType;			/* edge array element type */

typedef struct {
   int num_edges;
   int edge_list[SIZE_OF_POLY];	/* number of sides of polygons */
   int vert_list[3];		/* indices of vertices, counterclockwise */
   int color;			/* base color of polygon */
   vertexType normal;
} polygonType;			/* polygon array element type */


/** define some global variables **/
int object_count=0;			/* global object count */
int vertex_count=0;			/* global vertex count */
int edge_count=0;			/* global edge count */
int polygon_count=0;			/* global polygon count */

objectType object_list[MAX_OBJS];	/* array of object primitives */
vertexType vertex_list[MAX_VERTS];	/* array of vertices */
edgeType edge_list[MAX_EDGES];		/* array of edges */
polygonType polygon_list[MAX_POLYS];	/* array of polygons */

int curr_v_index=0;   			/* current vertex index */
int curr_e_index=0;   			/* current edge index */
int curr_p_index=0;   			/* current polygon index */

FILE *objfile;				/* object file pointer */
FILE *modfile;				/* model file pointer */
FILE *debugfile;			/* debug file pointer */
char format[BUFLEN];			/* generic error message string */

struct {
   vertexType verts[NUM_RECT_VERTS];
   edgeType edges[NUM_RECT_EDGES];
   polygonType polys[NUM_RECT_POLYS];
} unit_cube;				/* size 1 cube solid */

struct {
   vertexType verts[NUM_PRSM_VERTS];
   edgeType edges[NUM_PRSM_EDGES];
   polygonType polys[NUM_PRSM_POLYS];
} unit_prism;				/* size 1 prism solid */


/* include headers which contain functions used below */
#include "mathutls.h"		/* math utilities */
#include "unitutls.h"		/* unit solid functions */
#include "modlutls.h"		/* model generation functions */


/************************
*  begin main program   *
*************************/
main(argc,argv)
   int argc;
   char *argv[];
{
   char obj_file_name[BUFLEN];	/* name of object description file */
   char mod_file_name[BUFLEN];	/* name of model data file */

   int i;	/* index for arg list */

   sprintf(obj_file_name, "object");
   sprintf(mod_file_name, "data");

   /* check command line arguments */
   switch(argc) {
     case 1:	/* use defaults args */
        break;

     default:	/* check args and parse */
        if (argc > MAX_ARGS) {	/* if too many args in list? */
           sprintf(format,"usage: %s [-d objectfile][-m modelfile]", argv[0]);
           ErrPrint(format, 0);
        }

        else {	/* parse argument inputs */
           i = 1;	/* init arg index */

           while (i < argc) {
              switch(argv[i][1]) {  /* switch on dash option */

                 case 'i':	/* object description input file */

                    sprintf(obj_file_name, "%s", argv[i+1]);
                    i++;
                    break;

                 case 'o':	/* model output file */

                    sprintf(mod_file_name, "%s", argv[i+1]);
                    i++;
                    break;

                 default:
                    ErrPrint("Main: unknown option(s) specified",1);
                    break;
              } /* end switch on dash option */

              i++;		/* increment arg index */
           } /* end while */
        } /* end else */
        break;
   } /*end switch on arg count */

   /* open object description input file */
   objfile = fopen(obj_file_name,"r");
   if (objfile == (FILE *) NULL) {
      sprintf(format,"Main: can't open '%s' as object file",obj_file_name);
      ErrPrint(format, 2);
   }

   /* open model data output file */
   modfile = fopen(mod_file_name,"w");
   if (modfile == (FILE *) NULL) {
      sprintf(format,"Main: can't open '%s' as model file",mod_file_name);
      ErrPrint(format, 3);
   }

   /* open debug output file */
   debugfile = fopen("debug.log","w");
   if (debugfile == (FILE *) NULL) {
      sprintf(format, "Main: can't open 'debug.log' as debug file");
      ErrPrint(format, 0);
   }

   /* read in the object description file */
   printf("Beginning processing ...\n");

   ReadDescription();

   printf("\nDone reading '%s' as object file (read %d objects) ...\n", obj_file_name, object_count);

   /* translate object description into world coord elements */
   printf("\nTranslating Object (into triangles) ...\n");

   BuildUnitCube();
   BuildUnitPrism();
   TranslateObjects();

   printf("\nDone translating (model contains %d polygons) ...\n",
         polygon_count);

   /* output the finished model data file */
   printf("\nOutputting to '%s' as model data file ...\n", mod_file_name);

   OutputModelFile();

   Cleanup();	/* close files and deallocate memory */
} /* end of main for modeler.c */


/*****************************************************************

   ReadDescription() -- This function reads in the object description 
			file one line at a time.  Each line must 
			contain one object primitive descriptive
			statement of the following form:

			   rect cx cy cz sx sy sz axis angle
			   rect 10 15 10 50 20 20 x 35

			which indicates a rectanglar solid with center 
			at (10,15,10) and has a width(sx) of 50, a 
			height(sy) of 20, and a length(sz) of 20.  The
			solid will be rotated about the x-axis by 35
			degrees.  Note that the scaling parameters for
			a cylindrical solid are actually a radius(sx), 
			the number of sides(sy), and a height(sz).

			Each primitive line is parsed to extract the 
			parameters which are then saved in the 
			'object_list' array.  The final count of how 
			many object primitives the file contained 
			is saved to 'object_count'.

******************************************************************/
int 
ReadDescription()
{
   char tempbuf[BUFLEN];	/* temporary text buffer */
   char *buf;			/* pointer to primitive string */
   char *parm_array[MAX_PARMS];	/* array of parameter strings */

   int o_index;			/* primitive object index */
   int parm_count;		/* primitive parameter count */

   primType prim_code;		/* primitive type code */


   o_index = 0;  /* init object index */

   /* while not end of file and object index less than max objects loop */
   while((feof(objfile) == 0) && (o_index < MAX_OBJS)) {

      buf = fgets(tempbuf, BUFLEN, objfile); /* read a line from obj file */

      if (feof(objfile) == 0) {
         prim_code = UNKN_PRIM;   /* init primitive code to unknown */

         /* determine primitive type */
         if (strncmp(buf, "rect", 4) == 0) /* rectanglar solid  */
            prim_code = RECT_PRIM;
         if (strncmp(buf, "cyld", 4) == 0) /* cylindrical solid */
            prim_code = CYLD_PRIM;
         if (strncmp(buf, "prsm", 4) == 0) /* right triangle prism */
            prim_code = PRSM_PRIM;


         /* extract parameters if primitive type is known */
         if (prim_code != UNKN_PRIM) {

            /* save current primitive type */
            object_list[o_index].primitive = prim_code;

            /* parse description line into array of parameters */
            parm_count = ParseString(buf, parm_array);

            switch(prim_code) {

               case RECT_PRIM:
               case CYLD_PRIM:
               case PRSM_PRIM: /* for these cases, save these parameters */
                  object_list[o_index].center.x = atof(parm_array[1]);
                  object_list[o_index].center.y = atof(parm_array[2]);
                  object_list[o_index].center.z = atof(parm_array[3]);
                  object_list[o_index].scaling.x = atof(parm_array[4]);
                  object_list[o_index].scaling.y = atof(parm_array[5]);
                  object_list[o_index].scaling.z = atof(parm_array[6]);

                  object_list[o_index].axis = parm_array[7][0];                  

                  object_list[o_index].angle = atof(parm_array[8]);
                  object_list[o_index].color = atoi(parm_array[9]);
                  break;

               default:
                  sprintf(format, "ReadDescription: unknown prim type");
                  ErrPrint(format, 4);
                  break;
            } /* end of switch */

            o_index++;
    
            if (o_index > MAX_OBJS) {
               sprintf(format, "ReadDescription: too many objects in file");
               ErrPrint(format, 5);
            }
         }
         else { /* unknown object primitive type found */
            sprintf(format,"ReadDescription: unknown primitive type found");
            ErrPrint(format, 6);
         }

      } /* end if not feof */

   } /* end of while */

   object_count = o_index;  /* save object index as object count */

   return(0);
} /* end of ReadDescription() */


/*****************************************************************

  TranslateObjects() -- This function translates the object descriptions 
			in the 'object_list' array into a set of arrays 
			for vertices, edges, and polygons.  The function 
			loops through the 'object list' array, and 
			handles each type of primitive on a case by 
			case basis.  All primitives are converted into
			their associated vertices, edges, and polygons.
			All polygons are assumed to take on the shape 
			of triangles.  

			Rectanglar solids will produce 8 vertices, 18
			edges, and 12 triangles.  Rectangles are assumed
			to be oriented with all sides parallel to the 
			x, y and z axes. 

			Cylindrical solids are parameterized by how many
			sides the circular surface consist of and hence 
			is approximated by a many sided polygon.  If the
			number of sides is N, then a cylindrical solid 
			will produce 2N+2 vertices, 6N edges, and 
			4N triangles.  It is assumed that N is even.
			
			Right trianglar prism produce 6 vertices, 12 edges,
			and 8 triangles.  Right trianglar prisms are
			assumed to be oriented such that non-sloped sides
			are parallel to the x, y and z axes.

******************************************************************/
int 
TranslateObjects()
{
   int curr_o_index;     		/* current object index */


   /* loop through the object's primitive list */
   for (curr_o_index=0; curr_o_index < object_count; curr_o_index++) {

      switch(object_list[curr_o_index].primitive) {

         case RECT_PRIM:  /* handle rectanglar solid primitive */

            GenRectSolid(object_list[curr_o_index].center,
				object_list[curr_o_index].scaling,
				object_list[curr_o_index].axis,
				object_list[curr_o_index].angle,
				object_list[curr_o_index].color);
            break;

         case CYLD_PRIM:  /* handle parameterized cylinder primitive */

            GenCylinder(object_list[curr_o_index].center,
				object_list[curr_o_index].scaling,
				object_list[curr_o_index].axis,
				object_list[curr_o_index].angle,
				object_list[curr_o_index].color);
            break;

         case PRSM_PRIM:  /* handle right triangle prism primitive */

            GenPrism(object_list[curr_o_index].center,
				object_list[curr_o_index].scaling,
				object_list[curr_o_index].axis,
				object_list[curr_o_index].angle,
				object_list[curr_o_index].color);
            break;

         default:
            sprintf(format,"TranslateObjects: unknown primitive type found");
            ErrPrint(format, 7);
            break;
      } /* end of switch on object primitive */

   } /* end of object list loop */

   vertex_count = curr_v_index;	  /* save vertex index as vertex count */
   edge_count = curr_e_index;     /* save edge index as edge count */
   polygon_count = curr_p_index;  /* save polygon index as polygon count */

   return(0);
} /* end of TranslateObjects() */


/*****************************************************************

   OutputModelFile() -- This function writes the model file info 
			contained within the 'vertex array', 
			'edge array', and 'polygon array' as output 
			to the model data file.

******************************************************************/
int 
OutputModelFile()
{
   int v, e, p;  /* loop indices */

   /* output vertex, edge, and polygon counts */
   fprintf(modfile, "%d %d %d\n", 
      vertex_count, edge_count, polygon_count);

   /* output vertex list */
   for (v = 0; v < vertex_count; v++) {
      fprintf(modfile, "%f %f %f\n", 
         vertex_list[v].x, vertex_list[v].y, vertex_list[v].z);
   }

   /* output edge list */
   for (e = 0; e < edge_count; e++) {
      fprintf(modfile, "%d %d\n", edge_list[e].sv, edge_list[e].ev);
   }

   /* output polygon list */
   for (p = 0; p < polygon_count; p++) {
      fprintf(modfile, "%d %d %d %d %d %d %d %d %f %f %f\n", 
         polygon_list[p].num_edges,
         polygon_list[p].edge_list[0],
         polygon_list[p].edge_list[1],
         polygon_list[p].edge_list[2],
         polygon_list[p].vert_list[0],
         polygon_list[p].vert_list[1],
         polygon_list[p].vert_list[2],
         polygon_list[p].color,
         polygon_list[p].normal.x, 
         polygon_list[p].normal.y, 
         polygon_list[p].normal.z);

      if (DEBUG) {
         fprintf(debugfile, "%d %d %d %f %f %f\n",
            polygon_list[p].vert_list[0],
            polygon_list[p].vert_list[1],
            polygon_list[p].vert_list[2],
            polygon_list[p].normal.x, 
            polygon_list[p].normal.y, 
            polygon_list[p].normal.z);
      }
   }

   return(0);
} /* end of OutputModelFile() */


/*****************************************************************
*  Cleanup() -- cleanup misc pointers and allocated memory       *
******************************************************************/
int
Cleanup()
{

/* close all file pointers used */
   fclose(objfile);
   fclose(modfile);

   return(0);
} /* end of Cleanup() */


/*****************************************************************
*  ErrPrint - prints error message and exits program             *
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
*  ParseString - parses list of strings into array of strings    *
******************************************************************/
int 
ParseString(string, args)
   char *string;
   char *args[];
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of ParseString() */


/* end of file modeler.c */
