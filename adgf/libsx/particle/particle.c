/***********************************************************************

   File:  	particle.c

   Author: 	Brian Lingard

   Date:	10/17/95

  High level functions for particle systems demo program.

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"		/* already includes "particle.h" */
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif


/* 
#define PARTICLE_DEBUG 1
*/

/*  declare function protos 
 */
void GenerateParticleSystem(MyProgram *data, int frame);


/*  declare global raster array 
 */
RASTER_T raster;	/* color indexed raster */


/******************************************************************************
*  InitDatabase - initializes global particle system database                 *
******************************************************************************/
void
InitDatabase(MyProgram *data)
{

   printf("initializing database\n");

   data->project_loaded = TRUE;
   data->project_saved = FALSE;

   data->load_file_name[0] = '\0';
   data->save_file_name[0] = '\0';

   data->load_file = (FILE *) NULL;
   data->save_file = (FILE *) NULL;

   data->view_screen_mode = CAMERA_VIEW;

   data->data.psys_count = DEFAULT_NUM_PSYS;
   data->data.psys_list[0].type = POINT_PART;
   data->data.psys_list[0].new_count = 5000; /* DEFAULT_NUM_PART */
   data->data.psys_list[0].count = 0;
   data->data.psys_list[0].start_pos_mean.x = 0.0;
   data->data.psys_list[0].start_pos_mean.y = 0.0;
   data->data.psys_list[0].start_pos_mean.z = 0.0;
   data->data.psys_list[0].start_pos_var.x = 1.0;
   data->data.psys_list[0].start_pos_var.y = 0.0;
   data->data.psys_list[0].start_pos_var.z = 1.0;
   data->data.psys_list[0].start_pos_radius = 0.1;
   data->data.psys_list[0].start_vel_mean.x = 0.0;
   data->data.psys_list[0].start_vel_mean.y = 3.0;
   data->data.psys_list[0].start_vel_mean.z = 0.0;
   data->data.psys_list[0].start_vel_var.x = 1.0;
   data->data.psys_list[0].start_vel_var.y = 2.0;
   data->data.psys_list[0].start_vel_var.z = 1.0;
   data->data.psys_list[0].start_col_mean.r = 220;
   data->data.psys_list[0].start_col_mean.g = 100;
   data->data.psys_list[0].start_col_mean.b = 50;
   data->data.psys_list[0].start_col_var.r = 0;
   data->data.psys_list[0].start_col_var.g = 0;
   data->data.psys_list[0].start_col_var.b = 0;
   data->data.psys_list[0].start_life_mean = 10;
   data->data.psys_list[0].start_life_var = 2;

   data->data.view.type = PARALLEL_PROJ;
   data->data.view.eyeloc.x = 0.0;
   data->data.view.eyeloc.y = 10.0;
   data->data.view.eyeloc.z = -30.0;
   data->data.view.lookat.x = 0.0;
   data->data.view.lookat.y = 0.0;
   data->data.view.lookat.z = 0.0;
   data->data.view.vup.x = 0.0;
   data->data.view.vup.y = 1.0;
   data->data.view.vup.z = 0.0;
   data->data.view.vrp.x = 0.0;
   data->data.view.vrp.y = 0.0;
   data->data.view.vrp.z = 0.0;

   data->data.anim.type = LINEAR_ANIM;
   data->data.anim.mode = STOP_ANIM;
   data->data.anim.enable_anim = FALSE;
   data->data.anim.num_frames = DEFAULT_NUM_FRAMES;
   data->data.anim.frame_rate = DEFAULT_FRAME_RATE;
   data->data.anim.frame_count = 0;

   data->zoom_value = DEFAULT_ZOOM_VALUE;

   ClearColorMap();

   GenerateParticleSystem(data, 0);
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


   sprintf(dumpname, "%s", DEFAULT_DUMP_FILE);

   dumpfile = fopen(dumpname,"w");
   if (dumpfile == (FILE *) NULL) {
      fprintf(stderr, "DumpDatabase: can't open '%s' as dump file", dumpname);
      exit(1);
   }

   fprintf(dumpfile, "project loaded   = %d\n", data->project_loaded);
   fprintf(dumpfile, "project saved    = %d\n", data->project_saved);

   fprintf(dumpfile, "load file name   = %s\n", data->load_file_name);
   fprintf(dumpfile, "save file name   = %s\n", data->save_file_name);

   fprintf(dumpfile, "view screen mode = %d\n\n", data->view_screen_mode);

   fprintf(dumpfile, "system count = %d\n", data->data.psys_count);

   fprintf(dumpfile, "\nview structure:\n");
   fprintf(dumpfile, "  type = %d\n", data->data.view.type);
   fprintf(dumpfile, "  eyeloc = %f %f %f\n", data->data.view.eyeloc.x, data->data.view.eyeloc.y, data->data.view.eyeloc.z);
   fprintf(dumpfile, "  lookat = %f %f %f\n", data->data.view.lookat.x, data->data.view.lookat.y, data->data.view.lookat.z);
   fprintf(dumpfile, "  vup    = %f %f %f\n", data->data.view.vup.x, data->data.view.vup.y, data->data.view.vup.z);
   fprintf(dumpfile, "  vrp    = %f %f %f\n", data->data.view.vrp.x, data->data.view.vrp.y, data->data.view.vrp.z);

   fprintf(dumpfile, "\nanim structure:\n");
   fprintf(dumpfile, "  type         = %d\n", data->data.anim.type);
   fprintf(dumpfile, "  mode         = %d\n", data->data.anim.mode);
   fprintf(dumpfile, "  num frames   = %d\n", data->data.anim.num_frames);
   fprintf(dumpfile, "  frame rate   = %d\n", data->data.anim.frame_rate);

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
}


/******************************************************************************
*  LoadModel - loads model file and begins processing                         *
*                                                                             *
*  expected format:                                                           *
*                                                                             *
*  psys_count                                                                 *
*  type count btype bcx bcy bcz brad edx edy edz icr icg icb fcr fcg fcb      *
*   ...                                                                       *
*  type count btype bcx bcy bcz brad edx edy edz icr icg icb fcr fcg fcb      *
*  vw_mode ex ey ez lx ly lz ux uy uz vx vy vz                                *
*  an_type nf fr                                                              *
*                                                                             *
******************************************************************************/
void
LoadModel(MyProgram *data)
{
   int i, ps_count, count;
   int type, btype;
   float bcx, bcy, bcz, brad, edx, edy, edz;
   int ic0, ic1, ic2, fc0, fc1, fc2;
   char string[8];
   float ex, ey, ez, lx, ly, lz, ux, uy, uz, vx, vy, vz;
   int nf, fr;

   /* input count of number of particle systems */
   fscanf(data->load_file, "%d\n", &ps_count);

   data->data.psys_count = ps_count;


   /* load view structure data */
   fscanf(data->load_file, "%s %f %f %f %f %f %f %f %f %f %f %f %f\n",
	type, &ex, &ey, &ez, &lx, &ly, &lz, &ux, &uy, &uz, &vx, &vy, &vz);
   data->data.view.eyeloc.x = ex;
   data->data.view.eyeloc.y = ey;
   data->data.view.eyeloc.z = ez;
   data->data.view.lookat.x = lx;
   data->data.view.lookat.y = ly;
   data->data.view.lookat.z = lz;
   data->data.view.vup.x = ux;
   data->data.view.vup.y = uy;
   data->data.view.vup.z = uz;
   data->data.view.vrp.x = vx;
   data->data.view.vrp.y = vy;
   data->data.view.vrp.z = vz;

   /* load anim structure data */
   fscanf(data->load_file, "%s %d %d\n",
	type, &nf, &fr);
   if (strncmp(string, ANIM_STR_LINEAR, ANIM_STR_LEN) == 0)
      data->data.anim.type = LINEAR_ANIM;
   else if (strncmp(string, ANIM_STR_CIRCLE, ANIM_STR_LEN) == 0)
      data->data.anim.type = CIRCLE_ANIM;
   else if (strncmp(string, ANIM_STR_BEZIER, ANIM_STR_LEN) == 0)
      data->data.anim.type = BEZIER_ANIM;
   else if (strncmp(string, ANIM_STR_SPLINE, ANIM_STR_LEN) == 0)
      data->data.anim.type = SPLINE_ANIM;
   else
      data->data.anim.type = NO_ANIM;
   data->data.anim.num_frames = nf;
   data->data.anim.frame_rate = fr;

   SetupAnimToRun(data);

   data->project_loaded = TRUE;
   data->project_saved = TRUE;

   GenerateParticleSystem(data, 0);
   UpdateDisplay(data);
}


/******************************************************************************
*  SaveModel - saves current particle systems data to file                    *
*                                                                             *
*  output format:                                                             *
*                                                                             *
*  psys_count                                                                 *
*  type count btype bcx bcy bcz brad edx edy edz icr icg icb fcr fcg fcb      *
*   ...                                                                       *
*  type count btype bcx bcy bcz brad edx edy edz icr icg icb fcr fcg fcb      *
*  vw_mode ex ey ez lx ly lz ux uy uz vx vy vz                                *
*  an_type nf fr                                                              *
*                                                                             *
******************************************************************************/
void
SaveModel(MyProgram *data)
{
   int i;

   /* output primitive count */
   fprintf(data->save_file, "%d\n", data->data.psys_count);

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
		"%d %d\n",
		data->data.anim.num_frames, 
		data->data.anim.frame_rate);
}


/******************************************************************************
*  UpdateDisplay - updates screen display following changes in the database   *
******************************************************************************/
void
UpdateDisplay(MyProgram *data)
{
/*
printf("updating display...\n");
*/

   ClearScreenDisplay();

/*
printf("cleared screen\n");
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

/*
printf("done updating display\n");
*/

}


/******************************************************************************
*  GetPosition - generates a particle's initial position based on frame       *
*                number and some random offset                                *
******************************************************************************/
void 
GetPosition(int frame, wpointType *p, PSYSTEM_S_T *psys)
{
   static int old_frame = -1;
   double theta;
   float rad;
 
   double cos(), sin();


   /* check if location needs to be updated */
   if (frame != old_frame)
   {
      old_frame = frame;
      psys->start_pos_mean.x = 20.0 * nrand();
      psys->start_pos_mean.z = 20.0 * nrand();
   }

   theta = (double) (nrand() * TWO_PI);
   rad = psys->start_pos_radius * nrand();

   p->x = psys->start_pos_mean.x + rad * cos(theta);
   p->y = psys->start_pos_mean.y + nrand() * psys->start_pos_var.y;
   p->z = psys->start_pos_mean.z + rad * sin(theta);
}


/******************************************************************************
*  GetVelocity - generates a particle's initial velocity based on frame number*
******************************************************************************/
void 
GetVelocity(int frame, vectorType *v, PSYSTEM_S_T *psys)
{
  double theta;
  float rad;

  theta = TWO_PI * nrand();
  rad = nrand() * (psys->start_vel_var.x + psys->start_vel_var.z) / 2.0;
  
  v->x = psys->start_vel_mean.x + rad * cos(theta);
  v->y = psys->start_vel_mean.y + nrand() * psys->start_vel_var.y;
  v->z = psys->start_vel_mean.z + rad * sin(theta);
}


/******************************************************************************
*  GenerateParticle - generates a new particle for a given particle system.   *
******************************************************************************/
void 
GenerateParticle(PARTICLE_S_T *p, PSYSTEM_S_T *psys, int frame)
{
  GetPosition(frame, &p->position, psys);
  
  GetVelocity(frame, &p->velocity, psys);

  p->color.r = psys->start_col_mean.r + nrand() * psys->start_col_var.r;
  p->color.g = psys->start_col_mean.g + nrand() * psys->start_col_var.g;
  p->color.b = psys->start_col_mean.b + nrand() * psys->start_col_var.b;
  
  p->age = 0;
  p->life = psys->start_life_mean + nrand() * psys->start_life_var;
}


/******************************************************************************
*  GenerateParticleSystem - generates initial sets of particles for each      *
*                           defined particle system.                          *
******************************************************************************/
void 
GenerateParticleSystem(MyProgram *data, int frame)
{
   int i, p;
   int old_num_parts;

   printf("generating system on frame %d\n", frame);

   for (i = 0; i < data->data.psys_count; i++)
   {
      old_num_parts = data->data.psys_list[i].count;

      data->data.psys_list[i].count = MIN(old_num_parts + 
					data->data.psys_list[i].new_count, 
					MAX_PARTICLES - 1);

      for (p = old_num_parts; p < data->data.psys_list[i].count; p++)
      {
         GenerateParticle( &data->data.psys_list[i].plist[p], 
					&data->data.psys_list[i],
					frame );
      }
   }
}


/******************************************************************************
*  AnimateParticles - update the attributes of each particle in each system.  *
******************************************************************************/
void 
AnimateParticles(MyProgram *data)
{
   int i, p;


   printf("animating particles\n");


   for (i = 0; i < data->data.psys_count; i++)
   {
      for (p = 0; p < data->data.psys_list[i].count; p++)
      {

         data->data.psys_list[i].plist[p].position.x += data->data.psys_list[i].plist[p].velocity.x;
         data->data.psys_list[i].plist[p].position.y += data->data.psys_list[i].plist[p].velocity.y;
         data->data.psys_list[i].plist[p].position.z += data->data.psys_list[i].plist[p].velocity.z;

         data->data.psys_list[i].plist[p].velocity.y -= GRAVITY;

         /* check for hitting the ground */
         if (data->data.psys_list[i].plist[p].position.y <= 0.0)
	 {
	    data->data.psys_list[i].plist[p].position.y = 0.0;
	    data->data.psys_list[i].plist[p].velocity.x = 0.0;
	    data->data.psys_list[i].plist[p].velocity.y = 0.0;
	    data->data.psys_list[i].plist[p].velocity.z = 0.0;
	 }

         /* update the particle's age */
         data->data.psys_list[i].plist[p].age++;

      }
   }
}


/******************************************************************************
*  ResurrectParticles - dead particles are reborn.                            *
******************************************************************************/
void 
ResurrectParticles(MyProgram *data, int frame)
{
   int i, p;

   for (i = 0; i < data->data.psys_count; i++)
   {
      for (p = 0; p < data->data.psys_list[i].count; p++)
      {
         if (data->data.psys_list[i].plist[p].age >= data->data.psys_list[i].plist[p].life)
         {
            GenerateParticle(&data->data.psys_list[i].plist[p], 
					&data->data.psys_list[i], frame);
         }
      }
   }
}


/******************************************************************************
*  ComputeNextFrame - computes next frame of camera path animation            *
*                     and updates display for new camera position.            *
******************************************************************************/
void 
ComputeNextFrame(MyProgram *data)
{
   int i;

   printf("computing next frame\n");

   for (i = 0; i < data->data.psys_count; i++)
   {
      /* animate the particles */
      AnimateParticles(data);

      /* regenerate dead particles */
/*
      ResurrectParticles(data, data->data.anim.frame_count);
*/

      /* create new particles */
      if ((data->data.anim.frame_count < (data->data.anim.num_frames - 10)) 
		&& (nrand() > 0.80))
      {
         GenerateParticleSystem(data, data->data.anim.frame_count);
      }

   }

   UpdateDisplay(data);

   data->data.anim.frame_count++;

}

/* end of particle.c */
