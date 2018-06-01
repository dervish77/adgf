/***********************************************************************

   File:  	modeler.c

   Author: 	Brian Lingard

   Date:	9/9/95

  High level functions for 3D modeling program.

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

extern void ClearColorMap();

extern void MakeUnitPlane();
extern void MakeUnitCube();

BOOLEAN_T enable_color_render = FALSE;


/******************************************************************************
*  InitDatabase - initializes pointers to global database arrays              *
******************************************************************************/
void
InitDatabase(MyProgram *data)
{
   data->project_loaded = FALSE;
   data->project_saved = FALSE;
   data->project_exported = FALSE;
   data->project_vrml = FALSE;

   data->load_file_name[0] = '\0';
   data->save_file_name[0] = '\0';
   data->export_raw_file_name[0] = '\0';
   data->export_vrml_file_name[0] = '\0';

   data->load_file = (FILE *) NULL;
   data->save_file = (FILE *) NULL;
   data->export_raw_file = (FILE *) NULL;
   data->export_vrml_file = (FILE *) NULL;

   data->view_screen_mode = ALL_VIEW;

   data->render_mode = WIRE_REND;

   data->data.current_prim_idx = 0;
   data->data.current_vert_idx = 0;
   data->data.current_poly_idx = 0;

   data->data.prim_count = 0;
   data->data.vert_count = 0;
   data->data.poly_count = 0;

   data->data.view.type = PARALLEL_PROJ;
   data->data.view.eyeloc.x = -10.0;
   data->data.view.eyeloc.y = 10.0;
   data->data.view.eyeloc.z = -10.0;
   data->data.view.lookat.x = 0.0;
   data->data.view.lookat.y = 0.0;
   data->data.view.lookat.z = 0.0;
   data->data.view.vup.x = 0.0;
   data->data.view.vup.y = 1.0;
   data->data.view.vup.z = 0.0;
   data->data.view.vrp.x = 0.0;
   data->data.view.vrp.y = 0.0;
   data->data.view.vrp.z = 0.0;

   data->data.light.type = AMB_LIGHT;
   data->data.light.shading = FLAT_SHADE;
   data->data.light.location.x = 30.0;
   data->data.light.location.y = 30.0;
   data->data.light.location.z = 30.0;
   data->data.light.direction.x = 0.0;
   data->data.light.direction.y = 0.0;
   data->data.light.direction.z = 0.0;
   data->data.light.spot_size = 30.0;
   data->data.light.intensity = 1.0;
   data->data.light.color[R_IDX] = 253;
   data->data.light.color[G_IDX] = 253;
   data->data.light.color[B_IDX] = 253;

   data->data.anim.type = NO_ANIM;
   data->data.anim.mode = STOP_ANIM;
   data->data.anim.enable_anim = FALSE;
   data->data.anim.num_frames = DEFAULT_NUM_FRAMES;
   data->data.anim.frame_rate = DEFAULT_FRAME_RATE;
   data->data.anim.frame_count = 0;
   data->data.anim.lpath.start_eye_pt.x = -10.0;
   data->data.anim.lpath.start_eye_pt.y = 5.0;
   data->data.anim.lpath.start_eye_pt.z = -20.0;
   data->data.anim.lpath.end_eye_pt.x = -10.0;
   data->data.anim.lpath.end_eye_pt.y = 5.0;
   data->data.anim.lpath.end_eye_pt.z = 20.0;
   data->data.anim.lpath.start_lap_pt.x = 0.0;
   data->data.anim.lpath.start_lap_pt.y = 0.0;
   data->data.anim.lpath.start_lap_pt.z = 0.0;
   data->data.anim.lpath.end_lap_pt.x = 0.0;
   data->data.anim.lpath.end_lap_pt.y = 0.0;
   data->data.anim.lpath.end_lap_pt.z = 0.0;

   data->zoom_value = DEFAULT_ZOOM_VALUE;

   ClearColorMap();

   MakeUnitPlane();
   MakeUnitCube();
   MakeUnitPyramid();
   MakeUnitPrism();
}


/******************************************************************************
*  DumpDatabase - ouputs entire database to a file called "dumpdata.log"      *
******************************************************************************/
void
DumpDatabase(MyProgram *data)
{
   FILE_STRING_T	dumpname;
   FILE			*dumpfile;
   int 			i, j;
   char		type_string[TYPE_STRING_LEN+1];

 
   sprintf(dumpname, "%s", DEFAULT_DUMP_FILE);

   dumpfile = fopen(dumpname,"w");
   if (dumpfile == (FILE *) NULL) {
      fprintf(stderr, "DumpDatabase: can't open '%s' as dump file", dumpname);
      exit(1);
   }

   fprintf(dumpfile, "project loaded   = %d\n", data->project_loaded);
   fprintf(dumpfile, "project saved    = %d\n", data->project_saved);
   fprintf(dumpfile, "project exported = %d\n\n", data->project_exported);

   fprintf(dumpfile, "load file name   = %s\n", data->load_file_name);
   fprintf(dumpfile, "save file name   = %s\n", data->save_file_name);
   fprintf(dumpfile, "export raw file name = %s\n", data->export_raw_file_name);
   fprintf(dumpfile, "export vrml file name = %s\n\n", data->export_vrml_file_name);

   fprintf(dumpfile, "view screen mode = %d\n\n", data->view_screen_mode);

   fprintf(dumpfile, "curr prim idx = %d\n", data->data.current_prim_idx);
   fprintf(dumpfile, "curr vert idx = %d\n", data->data.current_vert_idx);
   fprintf(dumpfile, "curr poly idx = %d\n\n", data->data.current_poly_idx);

   fprintf(dumpfile, "prim count = %d\n", data->data.prim_count);
   fprintf(dumpfile, "vert count = %d\n", data->data.vert_count);
   fprintf(dumpfile, "poly count = %d\n\n", data->data.poly_count);

   fprintf(dumpfile, "prim data:\n");
   for (i = 0; i < data->data.prim_count; i++)
   {
      if (data->data.prim_list[i].valid)
      {
         switch(data->data.prim_list[i].type)
         {
           case PLANE_PRIM:
              sprintf(&type_string[0], "%s", PLANE_STRING);
              break;
           case CUBE_PRIM:
              sprintf(&type_string[0], "%s", CUBE_STRING);
              break;
           case CYLIN_PRIM:
              sprintf(&type_string[0], "%s", CYLINDER_STRING);
              break;
           case PYRA_PRIM:
              sprintf(&type_string[0], "%s", PYRAMID_STRING);
              break;
           case PRISM_PRIM:
              sprintf(&type_string[0], "%s", PRISM_STRING);
              break;
           case CONE_PRIM:
              sprintf(&type_string[0], "%s", CONE_STRING);
              break;
           case SPHERE_PRIM:
              sprintf(&type_string[0], "%s", SPHERE_STRING);
              break;
           default:
              sprintf(&type_string[0], "unknown ");
              break;
         }

         fprintf(dumpfile, "  #%d is type %s\n", i, type_string);
         fprintf(dumpfile, "    center  = %f %f %f\n", data->data.prim_list[i].center.x, data->data.prim_list[i].center.y, data->data.prim_list[i].center.z);
         fprintf(dumpfile, "    scaling = %f %f %f\n", data->data.prim_list[i].scaling.x, data->data.prim_list[i].scaling.y, data->data.prim_list[i].scaling.z);
         fprintf(dumpfile, "    axis and angle = %c at %f\n", data->data.prim_list[i].axis, data->data.prim_list[i].angle);
         fprintf(dumpfile, "    color   = %d %d %d\n", data->data.prim_list[i].color[R_IDX], data->data.prim_list[i].color[G_IDX], data->data.prim_list[i].color[B_IDX]);
      }
      else
         fprintf(dumpfile, "  #%d has been deleted\n", i);
   }

   fprintf(dumpfile, "\nvert data:\n");
   for (i = 0; i < data->data.vert_count; i++)
   {
      fprintf(dumpfile, "  #%d vert = %f %f %f\n", i, data->data.vert_list[i].x, data->data.vert_list[i].y, data->data.vert_list[i].z);
   }

   fprintf(dumpfile, "\npoly data:\n");
   for (i = 0; i < data->data.poly_count; i++)
   {
      fprintf(dumpfile, "  #%d has %d verts\n", i, data->data.poly_list[i].num_verts);
      fprintf(dumpfile, "    verts  =");
      for (j = 0; j < data->data.poly_list[i].num_verts; j++)
         fprintf(dumpfile, " %d", data->data.poly_list[i].vertices[j]);
      fprintf(dumpfile, "\n");
      fprintf(dumpfile, "    color  = %d %d %d\n", data->data.poly_list[i].color[R_IDX], data->data.poly_list[i].color[G_IDX], data->data.poly_list[i].color[B_IDX]);
      fprintf(dumpfile, "    normal = %f %f %f\n", data->data.poly_list[i].normal.x, data->data.poly_list[i].normal.y, data->data.poly_list[i].normal.z);
      fprintf(dumpfile, "    visible  = %d\n", data->data.poly_list[i].visible);
      fprintf(dumpfile, "    sorted   = %d\n", data->data.poly_list[i].sorted);
      fprintf(dumpfile, "    rendered = %d\n", data->data.poly_list[i].rendered);
   }

   fprintf(dumpfile, "\nview structure:\n");
   fprintf(dumpfile, "  type = %d\n", data->data.view.type);
   fprintf(dumpfile, "  eyeloc = %f %f %f\n", data->data.view.eyeloc.x, data->data.view.eyeloc.y, data->data.view.eyeloc.z);
   fprintf(dumpfile, "  lookat = %f %f %f\n", data->data.view.lookat.x, data->data.view.lookat.y, data->data.view.lookat.z);
   fprintf(dumpfile, "  vup    = %f %f %f\n", data->data.view.vup.x, data->data.view.vup.y, data->data.view.vup.z);
   fprintf(dumpfile, "  vrp    = %f %f %f\n", data->data.view.vrp.x, data->data.view.vrp.y, data->data.view.vrp.z);

   fprintf(dumpfile, "\nlight structure:\n");
   fprintf(dumpfile, "  type      = %d\n", data->data.light.type);
   fprintf(dumpfile, "  location  = %f %f %f\n", data->data.light.location.x, data->data.light.location.y, data->data.light.location.z);
   fprintf(dumpfile, "  direction = %f %f %f\n", data->data.light.direction.x, data->data.light.direction.y, data->data.light.direction.z);
   fprintf(dumpfile, "  spot size = %f\n", data->data.light.spot_size);
   fprintf(dumpfile, "  intensity = %f\n", data->data.light.intensity);
   fprintf(dumpfile, "  color     = %d %d %d\n", data->data.light.color[R_IDX], data->data.light.color[G_IDX], data->data.light.color[B_IDX]);

   fprintf(dumpfile, "\nanim structure:\n");
   fprintf(dumpfile, "  type         = %d\n", data->data.anim.type);
   fprintf(dumpfile, "  mode         = %d\n", data->data.anim.mode);
   fprintf(dumpfile, "  num frames   = %d\n", data->data.anim.num_frames);
   fprintf(dumpfile, "  frame rate   = %d\n", data->data.anim.frame_rate);
   fprintf(dumpfile, "  start eye pt = %f %f %f\n", data->data.anim.lpath.start_eye_pt.x, data->data.anim.lpath.start_eye_pt.y, data->data.anim.lpath.start_eye_pt.z);
   fprintf(dumpfile, "  end eye pt   = %f %f %f\n", data->data.anim.lpath.end_eye_pt.x, data->data.anim.lpath.end_eye_pt.y, data->data.anim.lpath.end_eye_pt.z);

   fprintf(dumpfile, "\n END OF FILE\n");

   fclose(dumpfile);
}


/******************************************************************************
*  SetupAnimToRun - calc initial values of anim parameters to get it ready    *
*                   for execution and calls UpdateDisplay.                    *
*                                                                             *
******************************************************************************/
void
SetupAnimToRun(MyProgram *data)
{
  wpointType temp_eye_pt;
  wpointType temp_lap_pt;
  float alpha;

  /* compute frame interval */
  data->data.anim.frame_interval = (int) ((1.0 / (float)data->data.anim.frame_rate) * (1000));
  data->data.anim.frame_count = 0;
  data->data.anim.mode = STOP_ANIM;
  data->data.anim.enable_anim = FALSE;

printf("  interval = %d ms\n", data->data.anim.frame_interval);

  /* compute incremental eye position based on path type */
  switch(data->data.anim.type)
  {
     case LINEAR_ANIM:
        alpha = 1.0 / ((float) data->data.anim.num_frames);

printf("  alpha = %f\n", alpha);

        temp_eye_pt = LerpWPoint( &data->data.anim.lpath.start_eye_pt, 
				&data->data.anim.lpath.end_eye_pt, 
				alpha );
        temp_lap_pt = LerpWPoint( &data->data.anim.lpath.start_lap_pt, 
				&data->data.anim.lpath.end_lap_pt, 
				alpha );

OutputWPoint(stdout, &temp_eye_pt, "  temp eye pt:");
OutputWPoint(stdout, &temp_lap_pt, "  temp lap pt:");

        data->data.anim.lpath.incr_eye_pt.x = temp_eye_pt.x - data->data.anim.lpath.start_eye_pt.x;
        data->data.anim.lpath.incr_eye_pt.y = temp_eye_pt.y - data->data.anim.lpath.start_eye_pt.y;
        data->data.anim.lpath.incr_eye_pt.z = temp_eye_pt.z - data->data.anim.lpath.start_eye_pt.z;

        data->data.anim.lpath.incr_lap_pt.x = temp_lap_pt.x - data->data.anim.lpath.start_lap_pt.x;
        data->data.anim.lpath.incr_lap_pt.y = temp_lap_pt.y - data->data.anim.lpath.start_lap_pt.y;
        data->data.anim.lpath.incr_lap_pt.z = temp_lap_pt.z - data->data.anim.lpath.start_lap_pt.z;

OutputWPoint(stdout, &data->data.anim.lpath.incr_eye_pt, "  calc'd eye incr:");
OutputWPoint(stdout, &data->data.anim.lpath.incr_lap_pt, "  calc'd lap incr:");

        CopyWPoint( &data->data.anim.lpath.start_eye_pt, 
				&data->data.anim.lpath.curr_eye_pt );
        CopyWPoint( &data->data.anim.lpath.start_eye_pt, 
				&data->data.view.eyeloc );

        CopyWPoint( &data->data.anim.lpath.start_lap_pt, 
				&data->data.anim.lpath.curr_lap_pt );
        CopyWPoint( &data->data.anim.lpath.start_lap_pt, 
				&data->data.view.lookat );
        CopyWPoint( &data->data.anim.lpath.start_lap_pt, 
				&data->data.view.vrp );
        UpdateDisplay(data);
        break;

     default:
        break;
  }
}


/******************************************************************************
*  LoadModel - loads model file and begins processing into polygons           *
*                                                                             *
*  expected format:                                                           *
*                                                                             *
*  pcount                                                                     *
*  pr_type cx cy cz sx sy sz axis angle cr cg cb                              *
*   ...                                                                       *
*  pr_type cx cy cz sx sy sz axis angle cr cg cb                              *
*  vw_mode ex ey ez lx ly lz ux uy uz vx vy vz                                *
*  lt_type lx ly lz dx dy dz ss in cr cg cb                                   *
*  an_type nf fr sx sy sz ex ey ez                                            *
*                                                                             *
******************************************************************************/
void
LoadModel(MyProgram *data)
{
   int i, count;
   char type[8];
   float cx, cy, cz, sx, sy, sz, angle, ux, uy, uz, vx, vy, vz;
   char axis;
   int c0, c1, c2;

   /* input count of number of primitives */
   fscanf(data->load_file, "%d\n", &count);

   data->data.prim_count = count;

   /* load primitive data */
   for (i = 0; i < data->data.prim_count; i++)
   {
      fscanf(data->load_file, "%s %f %f %f %f %f %f %c %f %d %d %d\n",
	type, &cx, &cy, &cz, &sx, &sy, &sz, &axis, &angle, &c0, &c1, &c2);

      if (strncmp(type, PT_STR_PLANE, PT_STR_LEN) == 0)
         data->data.prim_list[i].type = PLANE_PRIM;
      else if (strncmp(type, PT_STR_CUBE, PT_STR_LEN) == 0)
         data->data.prim_list[i].type = CUBE_PRIM;
      else if (strncmp(type, PT_STR_CYLINDER, PT_STR_LEN) == 0)
         data->data.prim_list[i].type = CYLIN_PRIM;
      else if (strncmp(type, PT_STR_PYRAMD, PT_STR_LEN) == 0)
         data->data.prim_list[i].type = PYRA_PRIM;
      else if (strncmp(type, PT_STR_PRISM, PT_STR_LEN) == 0)
         data->data.prim_list[i].type = PRISM_PRIM;
      else if (strncmp(type, PT_STR_CONE, PT_STR_LEN) == 0)
         data->data.prim_list[i].type = CONE_PRIM;
      else if (strncmp(type, PT_STR_SPHERE, PT_STR_LEN) == 0)
         data->data.prim_list[i].type = SPHERE_PRIM;
      else
         data->data.prim_list[i].type = UNKN_PRIM;

      data->data.prim_list[i].center.x = cx;
      data->data.prim_list[i].center.y = cy;
      data->data.prim_list[i].center.z = cz;

      data->data.prim_list[i].scaling.x = sx;
      data->data.prim_list[i].scaling.y = sy;
      data->data.prim_list[i].scaling.z = sz;

      data->data.prim_list[i].axis = axis;
      data->data.prim_list[i].angle = angle;

      data->data.prim_list[i].color[R_IDX] = c0;
      data->data.prim_list[i].color[G_IDX] = c1;
      data->data.prim_list[i].color[B_IDX] = c2;

      data->data.prim_list[i].valid = TRUE;
   }

   /* load view structure data */
   fscanf(data->load_file, "%s %f %f %f %f %f %f %f %f %f %f %f %f\n",
	type, &cx, &cy, &cz, &sx, &sy, &sz, &ux, &uy, &uz, &vx, &vy, &vz);
   data->data.view.eyeloc.x = cx;
   data->data.view.eyeloc.y = cy;
   data->data.view.eyeloc.z = cz;
   data->data.view.lookat.x = sx;
   data->data.view.lookat.y = sy;
   data->data.view.lookat.z = sz;
   data->data.view.vup.x = ux;
   data->data.view.vup.y = uy;
   data->data.view.vup.z = uz;
   data->data.view.vrp.x = vx;
   data->data.view.vrp.y = vy;
   data->data.view.vrp.z = vz;

   /* load light structure data */
   fscanf(data->load_file, "%s %f %f %f %f %f %f %f %f %d %d %d\n",
	type, &cx, &cy, &cz, &sx, &sy, &sz, &angle, &ux, &c0, &c1, &c2);
   if (strncmp(type, LT_STR_AMBIENT, LT_STR_LEN) == 0)
      data->data.light.type = AMB_LIGHT;
   else if (strncmp(type, LT_STR_POINT, LT_STR_LEN) == 0)
      data->data.light.type = POINT_LIGHT;
   else if (strncmp(type, LT_STR_SPOT, LT_STR_LEN) == 0)
      data->data.light.type = SPOT_LIGHT;
   else if (strncmp(type, LT_STR_INFINITE, LT_STR_LEN) == 0)
      data->data.light.type = INFIN_LIGHT;
   else
      data->data.light.type = UNKN_LIGHT;
   data->data.light.location.x = cx;
   data->data.light.location.y = cy;
   data->data.light.location.z = cz;
   data->data.light.direction.x = sx;
   data->data.light.direction.y = sy;
   data->data.light.direction.z = sz;
   data->data.light.spot_size = angle;
   data->data.light.intensity = ux;
   data->data.light.color[R_IDX] = c0;
   data->data.light.color[G_IDX] = c1;
   data->data.light.color[B_IDX] = c2;

   /* load anim structure data */
   fscanf(data->load_file, "%s %d %d %f %f %f %f %f %f \n",
	type, &c0, &c1, &cx, &cy, &cz, &sx, &sy, &sz);
   if (strncmp(type, ANIM_STR_LINEAR, ANIM_STR_LEN) == 0)
      data->data.anim.type = LINEAR_ANIM;
   else if (strncmp(type, ANIM_STR_CIRCLE, ANIM_STR_LEN) == 0)
      data->data.anim.type = CIRCLE_ANIM;
   else if (strncmp(type, ANIM_STR_BEZIER, ANIM_STR_LEN) == 0)
      data->data.anim.type = BEZIER_ANIM;
   else if (strncmp(type, ANIM_STR_SPLINE, ANIM_STR_LEN) == 0)
      data->data.anim.type = SPLINE_ANIM;
   else
      data->data.anim.type = NO_ANIM;
   data->data.anim.num_frames = c0;
   data->data.anim.frame_rate = c1;
   data->data.anim.lpath.start_eye_pt.x = cx;
   data->data.anim.lpath.start_eye_pt.y = cy;
   data->data.anim.lpath.start_eye_pt.z = cz;
   data->data.anim.lpath.end_eye_pt.x = sx;
   data->data.anim.lpath.end_eye_pt.y = sy;
   data->data.anim.lpath.end_eye_pt.z = sz;

   SetupAnimToRun(data);

   data->project_loaded = TRUE;
   data->project_saved = TRUE;
   data->project_exported = FALSE;

   TranslateDatabase(data);
   UpdateDisplay(data);
}


/******************************************************************************
*  SaveModel - saves current array of primitives as model file                *
*                                                                             *
*  output format:                                                             *
*                                                                             *
*  pcount                                                                     *
*  pr_type cx cy cz sx sy sz axis angle cr cg cb                              *
*   ...                                                                       *
*  pr_type cx cy cz sx sy sz axis angle cr cg cb                              *
*  vw_mode ex ey ez lx ly lz ux uy uz vx vy vz                                *
*  lt_type lx ly lz dx dy dz ss in cr cg cb                                   *
*  an_type nf fr sx sy sz ex ey ez                                            *
*                                                                             *
******************************************************************************/
void
SaveModel(MyProgram *data)
{
   int i;

   /* output primitive count */
   fprintf(data->save_file, "%d\n", data->data.prim_count);

   /* output primitive array */
   for (i = 0; i < data->data.prim_count; i++)
   {
      if (data->data.prim_list[i].valid)
      {
         switch (data->data.prim_list[i].type)
         {
            case PLANE_PRIM:
               fprintf(data->save_file, "%s ", PT_STR_PLANE);
               break;
            case CUBE_PRIM:
               fprintf(data->save_file, "%s ", PT_STR_CUBE);
               break;
            case CYLIN_PRIM:
               fprintf(data->save_file, "%s ", PT_STR_CYLINDER);
               break;
            case PYRA_PRIM:
               fprintf(data->save_file, "%s ", PT_STR_PYRAMD);
               break;
            case PRISM_PRIM:
               fprintf(data->save_file, "%s ", PT_STR_PRISM);
               break;
            case CONE_PRIM:
               fprintf(data->save_file, "%s ", PT_STR_CONE);
               break;
            case SPHERE_PRIM:
               fprintf(data->save_file, "%s ", PT_STR_SPHERE);
               break;
            default:
               break;
         }
         fprintf(data->save_file, 
		"%3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %c %3.3f %d %d %d\n",
		data->data.prim_list[i].center.x,
		data->data.prim_list[i].center.y,
		data->data.prim_list[i].center.z,
		data->data.prim_list[i].scaling.x,
		data->data.prim_list[i].scaling.y,
		data->data.prim_list[i].scaling.z,
		data->data.prim_list[i].axis,
		data->data.prim_list[i].angle,
		data->data.prim_list[i].color[R_IDX],
		data->data.prim_list[i].color[G_IDX],
		data->data.prim_list[i].color[B_IDX]);
      }
   }

   /* output view structure */
   fprintf(data->save_file, 
	"vw_mode %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f\n", 
		data->data.view.eyeloc.x, 
		data->data.view.eyeloc.y, 
		data->data.view.eyeloc.z, 
		data->data.view.lookat.x, 
		data->data.view.lookat.y, 
		data->data.view.lookat.z, 
		data->data.view.vup.x, 
		data->data.view.vup.y, 
		data->data.view.vup.z, 
		data->data.view.vrp.x, 
		data->data.view.vrp.y, 
		data->data.view.vrp.z);

   /* output light structure */
   switch (data->data.light.type)
   {
      case AMB_LIGHT:
         fprintf(data->save_file, "%s ", LT_STR_AMBIENT);
         break;
      case POINT_LIGHT:
         fprintf(data->save_file, "%s ", LT_STR_POINT);
         break;
      case SPOT_LIGHT:
         fprintf(data->save_file, "%s ", LT_STR_SPOT);
         break;
      case INFIN_LIGHT:
         fprintf(data->save_file, "%s ", LT_STR_INFINITE);
         break;
      default:
         break;
   }
   fprintf(data->save_file, 
		"%3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f %d %d %d\n",
		data->data.light.location.x, 
		data->data.light.location.y, 
		data->data.light.location.z, 
		data->data.light.direction.x, 
		data->data.light.direction.y, 
		data->data.light.direction.z, 
		data->data.light.spot_size, 
		data->data.light.intensity, 
		data->data.light.color[R_IDX],
		data->data.light.color[G_IDX],
		data->data.light.color[B_IDX]);

   /* output anim structure */
   switch (data->data.anim.type)
   {
      case NO_ANIM:
         fprintf(data->save_file, "%s ", ANIM_STR_NONE);
         break;
      case LINEAR_ANIM:
         fprintf(data->save_file, "%s ", ANIM_STR_LINEAR);
         break;
      case CIRCLE_ANIM:
         fprintf(data->save_file, "%s ", ANIM_STR_CIRCLE);
         break;
      case BEZIER_ANIM:
         fprintf(data->save_file, "%s ", ANIM_STR_BEZIER);
         break;
      case SPLINE_ANIM:
         fprintf(data->save_file, "%s ", ANIM_STR_SPLINE);
         break;
      default:
         break;
   }
   fprintf(data->save_file, 
		"%d %d %3.3f %3.3f %3.3f %3.3f %3.3f %3.3f\n",
		data->data.anim.num_frames, 
		data->data.anim.frame_rate, 
		data->data.anim.lpath.start_eye_pt.x, 
		data->data.anim.lpath.start_eye_pt.y, 
		data->data.anim.lpath.start_eye_pt.z, 
		data->data.anim.lpath.end_eye_pt.x, 
		data->data.anim.lpath.end_eye_pt.y, 
		data->data.anim.lpath.end_eye_pt.z);
}


/******************************************************************************
*  ExportModel - exports current database in form Renderer can use.           *
*                                                                             *
*  output format:                                                             *
*                                                                             *
*  vertcount polycount                                                        *
*  x y z                                                                      *
*   ...                                                                       *
*  x y z                                                                      *
*  ns v1 ... vn nx ny nz cr cg cb                                             *
*   ...                                                                       *
*  ns v1 ... vn nx ny nz cr cg cb                                             *
*                                                                             *
******************************************************************************/
void
ExportModel(MyProgram *data)
{
   int i, j;

   /* output vert count and poly count */
   fprintf(data->export_raw_file, "%d %d\n", 
		data->data.vert_count, data->data.poly_count);

   /* output vert array */
   for (i = 0; i < data->data.vert_count; i++)
   {
      fprintf(data->export_raw_file, "%f %f %f\n",
		data->data.vert_list[i].x, 
		data->data.vert_list[i].y, 
		data->data.vert_list[i].z);
   }

   /* output poly array */
   for (i = 0; i < data->data.poly_count; i++)
   {
      fprintf(data->export_raw_file, "%d ", 
		data->data.poly_list[i].num_verts);

      for (j = 0; j < data->data.poly_list[i].num_verts; j++)
      {
         fprintf(data->export_raw_file, "%d ",
		data->data.poly_list[i].vertices[j]);
      }

      fprintf(data->export_raw_file, "%f %f %f %d %d %d\n",
		data->data.poly_list[i].normal.x,
		data->data.poly_list[i].normal.y,
		data->data.poly_list[i].normal.z,
		data->data.poly_list[i].color[R_IDX],
		data->data.poly_list[i].color[G_IDX],
		data->data.poly_list[i].color[B_IDX]);
   }
}


/******************************************************************************
*  ExportVRML - exports current database as a VMRL 1.0 compatible file        *
*                                                                             *
*  output format:                                                             *
*                                                                             *
*                                                                             *
******************************************************************************/
void
ExportVRML(MyProgram *data)
{
   SaveVRML( data );
}


/******************************************************************************
*  AddPrimitiveToDatabase - adds new primitive to database                    *
******************************************************************************/
void
AddPrimitiveToDatabase(PRIMITIVE_S_T *new, MyProgram *data)
{
   int idx;

   idx = data->data.current_prim_idx;

   data->data.prim_list[idx].type = new->type;
   data->data.prim_list[idx].center.x = new->center.x;
   data->data.prim_list[idx].center.y = new->center.y;
   data->data.prim_list[idx].center.z = new->center.z;
   data->data.prim_list[idx].scaling.x = new->scaling.x;
   data->data.prim_list[idx].scaling.y = new->scaling.y;
   data->data.prim_list[idx].scaling.z = new->scaling.z;
   data->data.prim_list[idx].axis = new->axis;
   data->data.prim_list[idx].angle = new->angle;
   data->data.prim_list[idx].color[R_IDX] = new->color[R_IDX];
   data->data.prim_list[idx].color[G_IDX] = new->color[G_IDX];
   data->data.prim_list[idx].color[B_IDX] = new->color[B_IDX];

   data->data.prim_list[idx].valid = TRUE;

   data->data.current_prim_idx++;
   data->data.prim_count++;

   if (!data->project_loaded)
   {
      data->project_loaded = TRUE;
   }

   data->project_saved = FALSE;

   TranslateDatabase(data);
   UpdateDisplay(data);
}


/******************************************************************************
*  DeletePrimitiveFromDatabase - deletes specified primitive from database    *
******************************************************************************/
void
DeletePrimitiveFromDatabase(int index, MyProgram *data)
{
   data->data.prim_list[index].valid = FALSE;

   data->project_saved = FALSE;

   TranslateDatabase(data);
   UpdateDisplay(data);
}


/******************************************************************************
*  UpdateDisplay - updates screen display following changes in the database   *
******************************************************************************/
void
UpdateDisplay(MyProgram *data)
{

   ClearScreenDisplay();

/*
printf("updating display\n");
*/

   switch(data->view_screen_mode)
   {
      case ALL_VIEW:
         DrawScreenBorders();

         if (data->project_loaded)
         {
            DrawView(SMALL_ORTH_XY_VIEW, data);
            DrawView(SMALL_ORTH_ZY_VIEW, data);
            DrawView(SMALL_ORTH_XZ_VIEW, data);
            DrawCameraView(SMALL_CAMERA_VIEW, data);
         }
         break;

      case ORTH_XY_VIEW:
         DrawScreenLabel(ORTH_XY_VIEW);
         DrawView(ORTH_XY_VIEW, data);
         break;

      case ORTH_ZY_VIEW:
         DrawScreenLabel(ORTH_ZY_VIEW);
         DrawView(ORTH_ZY_VIEW, data);
         break;

      case ORTH_XZ_VIEW:
         DrawScreenLabel(ORTH_XZ_VIEW);
         DrawView(ORTH_XZ_VIEW, data);
         break;

      case CAMERA_VIEW:
         DrawScreenLabel(CAMERA_VIEW);
         DrawCameraView(CAMERA_VIEW, data);
         break;

     default:
         break;
   }
}


/******************************************************************************
*  ComputeNextFrame - computes next frame of camera path animation            *
*                     and updates display for new camera position.            *
******************************************************************************/
void 
ComputeNextFrame(MyProgram *data)
{

   switch(data->data.anim.type)
   {
      case LINEAR_ANIM:
         if (data->data.anim.forward)
         {
            data->data.anim.lpath.curr_eye_pt.x += data->data.anim.lpath.incr_eye_pt.x;
            data->data.anim.lpath.curr_eye_pt.y += data->data.anim.lpath.incr_eye_pt.y;
            data->data.anim.lpath.curr_eye_pt.z += data->data.anim.lpath.incr_eye_pt.z;

            data->data.anim.lpath.curr_lap_pt.x += data->data.anim.lpath.incr_lap_pt.x;
            data->data.anim.lpath.curr_lap_pt.y += data->data.anim.lpath.incr_lap_pt.y;
            data->data.anim.lpath.curr_lap_pt.z += data->data.anim.lpath.incr_lap_pt.z;

            data->data.anim.frame_count += 1;
         }
         else
         {
            data->data.anim.lpath.curr_eye_pt.x -= data->data.anim.lpath.incr_eye_pt.x;
            data->data.anim.lpath.curr_eye_pt.y -= data->data.anim.lpath.incr_eye_pt.y;
            data->data.anim.lpath.curr_eye_pt.z -= data->data.anim.lpath.incr_eye_pt.z;

            data->data.anim.lpath.curr_lap_pt.x -= data->data.anim.lpath.incr_lap_pt.x;
            data->data.anim.lpath.curr_lap_pt.y -= data->data.anim.lpath.incr_lap_pt.y;
            data->data.anim.lpath.curr_lap_pt.z -= data->data.anim.lpath.incr_lap_pt.z;

            data->data.anim.frame_count -= 1;
         }

         CopyWPoint( &data->data.anim.lpath.curr_eye_pt, 
					&data->data.view.eyeloc );
         CopyWPoint( &data->data.anim.lpath.curr_lap_pt, 
					&data->data.view.lookat );
         CopyWPoint( &data->data.anim.lpath.curr_lap_pt, 
					&data->data.view.vrp );
         break;

      case CIRCLE_ANIM:
          break;

      case BEZIER_ANIM:
          break;

      case SPLINE_ANIM:
          break;

     default:
         break;
   }

   UpdateDisplay(data);
}


/******************************************************************************
*  ParseString - parses list of strings into array of strings                 *
******************************************************************************/
int 
ParseString(char *string, char *args[])
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



/* end of modeler.c */
