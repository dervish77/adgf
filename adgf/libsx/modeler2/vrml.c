/***********************************************************************

   File:  	vrml.c

   Author: 	Brian Lingard

   Date:	9/30/96

  VRML related functions for exporting database as VMRL file.

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "modeler.h" */
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif


/* #define MODELER_DEBUG 1
*/


/******************************************************************************
*  Color2Float - converts RBG integers into floating representation           *
*                                                                             *
******************************************************************************/
void
Color2Float(COLOR_RGB_T color, float *red, float *green, float *blue)
{
   *red   = ((float) color[R_IDX]) / 255;
   *green = ((float) color[G_IDX]) / 255;
   *blue  = ((float) color[B_IDX]) / 255;
}


/******************************************************************************
*  SaveVRML - saves current database as a VMRL 1.0 compatible file            *
*                                                                             *
*  output format:                                                             *
*                                                                             *
*                                                                             *
******************************************************************************/
void
SaveVRML(MyProgram *data)
{
   int i;

   FILE *outfile;

   float tbd = 1.0;
   float temp1, temp2, temp3;


   /* set file, and export VRML file type */
   outfile = data->export_vrml_file;
   fprintf(outfile, "#VMRL V1.0 ascii\n");

   /* export light source */
/*
   fprintf(outfile, "PointLight {\n");
   Color2Float(data->data.light.color, &temp1, &temp2, &temp3);
   fprintf(outfile, "    color    %f %f %f\n", temp1, temp2, temp3);
   fprintf(outfile, "    location %f %f %f\n", 
		data->data.light.location.x, 
		data->data.light.location.y, 
		data->data.light.location.z);
   fprintf(outfile, "}\n");
*/
   
   /* export all object primitives */
   for (i = 0; i < data->data.prim_count; i++)
   {
      fprintf(outfile, "Separator {\n");

      fprintf(outfile, "    Transform {\n");
      fprintf(outfile, "        translation     %f %f %f\n", 
		data->data.prim_list[i].center.x, 
		data->data.prim_list[i].center.y, 
		data->data.prim_list[i].center.z);
/*
      fprintf(outfile, "        rotation        %f %f %f\n", tbd, tbd, tbd);
*/
      fprintf(outfile, "        scaleFactor     %f %f %f\n", 
		data->data.prim_list[i].scaling.x, 
		data->data.prim_list[i].scaling.y, 
		data->data.prim_list[i].scaling.z);
      fprintf(outfile, "    }\n");
      fprintf(outfile, "    Material {\n");
      fprintf(outfile, "        ambientColor    %f %f %f\n", 0.5, 0.5, 0.5);
      Color2Float(data->data.prim_list[i].color, &temp1, &temp2, &temp3);
      fprintf(outfile, "        diffuseColor    %f %f %f\n", temp1, temp2, temp3);
      fprintf(outfile, "        specularColor   %f %f %f\n", 0.1, 0.1, 0.1);
      fprintf(outfile, "        shininess       %f\n", 0.1);
      fprintf(outfile, "    }\n");

      switch(data->data.prim_list[i].type)
      {
         case PLANE_PRIM:
            break;

         case CUBE_PRIM:
            fprintf(outfile, "    Cube {\n");
            fprintf(outfile, "        width    %f\n", 1.0);
            fprintf(outfile, "        height   %f\n", 1.0);
            fprintf(outfile, "        depth    %f\n", 1.0);
            fprintf(outfile, "    }\n");
            break;

         case CYLIN_PRIM:
            fprintf(outfile, "    Cylinder {\n");
            fprintf(outfile, "    }\n");
            break;

         case PYRA_PRIM:
            break;

         case PRISM_PRIM:
            break;

         case CONE_PRIM:
            fprintf(outfile, "    Cone {\n");
            fprintf(outfile, "    }\n");
            break;

         case SPHERE_PRIM:
            fprintf(outfile, "    Sphere {\n");
            fprintf(outfile, "    }\n");
            break;

         default:
            break;
      }

      fprintf(outfile, "}\n");
   }
}




/* end of vrml.c */
