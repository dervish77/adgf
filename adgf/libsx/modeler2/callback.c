/* This file contains routines that are called when a button is pressed 
 * in your window or when things happen in a drawing area.
 *
 * If you add a function to this file, you should also add a function 
 * prototype for it to the callbacks.h file (unless it is an internal 
 * function, then you should just add it down below where it says 
 * "internal prototypes").
 *
 *              --  This code is under the GNU copyleft  --
 *
 *   Dominic Giampaolo
 */

#include <stdio.h>
#include <time.h>

#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"              /* where program specific stuff is defined */
#endif

#ifndef _CALLBACK_H
#include "callback.h"         /* prototypes for callback functions       */
#endif





/*  -- CALLBACK ROUTINES  --
 *
 * These functions are called when various things happen in your windows.
 * They should handle what happened and give feedback to the user.  Most
 * likely they will set options in your program (which is what the 
 * MyProgram data structure is for), and cause different things to happen, 
 * like loading and saving files, etc.
 *
 * Remember, the last argument to your callback is always a void pointer
 * to whatever data you specified when you created the widget.  You
 * must cast the pointer to be whatever type it really is.
 */


/* file callbacks */

void file_open(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;

   printf("loading model ...\n");

   new_file_name = GetString("Enter file name to open (file.mdl)\n", "");

   if ( (new_file_name != (char *) NULL) && (strlen(new_file_name) > 0) )
   {
      if (strlen(new_file_name) < FILE_STRING_LEN)
         strcpy(me->load_file_name, new_file_name);
      else {
         strncpy(me->load_file_name, new_file_name, FILE_STRING_LEN);
         me->load_file_name[FILE_STRING_LEN - 1] = '\0';
      }

      strcpy(me->save_file_name, me->load_file_name);

      me->load_file = fopen(me->load_file_name, "r");
      if (me->load_file == (FILE *) NULL)
      {
         fprintf(stderr, "file_open: can't open '%s' as model file\n", me->load_file_name);
         exit(1);
      }

      LoadModel(me);

      fclose(me->load_file);

      printf("done loading\n");
   }
   else
      printf("loading cancelled\n");
}


void file_save(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;
   int okay;
   char *string;

   printf("saving model ...\n");

   if (strlen(me->save_file_name) == 0)
   {
      new_file_name = GetString("Enter file name to save as (file.mdl)\n", NULL);

      if (new_file_name == (char *) NULL)
      {
         okay = FALSE;
      }
      else
      {
         if (strlen(new_file_name) < FILE_STRING_LEN)
            strcpy(me->save_file_name, new_file_name);
         else 
         {
            strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
            me->save_file_name[FILE_STRING_LEN - 1] = '\0';
         }

         okay = TRUE;
      }
   }
   else
   {
      okay = TRUE;
   }

   if (okay)
   {
      me->save_file = fopen(me->save_file_name, "w");
      if (me->save_file == (FILE *) NULL)
      {
         fprintf(stderr, "file_save: can't open '%s' as model file\n", me->save_file_name);
         exit(1);
      }

      SaveModel(me);

      me->project_saved = TRUE;

      fclose(me->save_file);

      printf("done saving\n");
   }
   else
      printf("save cancelled\n");
}


void file_save_as(Widget w, void *data)
{
   MyProgram *me=data;
   char *new_file_name;

   printf("saving model ...\n");

   new_file_name = GetString("Enter file name to save as (file.mdl)\n", NULL);

   if ( (new_file_name != (char *) NULL) && (strlen(new_file_name) > 0) )
   {
      if (strlen(new_file_name) < FILE_STRING_LEN)
         strcpy(me->save_file_name, new_file_name);
      else 
      {
         strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
         me->save_file_name[FILE_STRING_LEN - 1] = '\0';
      }

      me->save_file = fopen(me->save_file_name, "w");
      if (me->save_file == (FILE *) NULL)
      {
         fprintf(stderr, "file_save_as: can't open '%s' as model file\n", me->save_file_name);
         exit(1);
      }

      SaveModel(me);

      me->project_saved = TRUE;

      fclose(me->save_file);

      printf("done saving\n");
   }
   else
      printf("saving cancelled\n");
}


void file_close(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char *new_file_name;

   if (me->project_saved == FALSE)
   {
      okay = GetYesNo("Model file not saved!!\n\nDo you want to save it now?");  
      if (okay)
      {
         if (strlen(me->save_file_name) == 0)
         {
            new_file_name = GetString("Enter file name to save as (file.mdl)\n", NULL);

            if ( (new_file_name != (char *) NULL) 
			&& (strlen(new_file_name) > 0) )
            {
               if (strlen(new_file_name) < FILE_STRING_LEN)
                  strcpy(me->save_file_name, new_file_name);
               else {
                  strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
                  me->save_file_name[FILE_STRING_LEN - 1] = '\0';
               }
            }
            else
            {
               printf("saving cancelled\n");
               okay = FALSE;
            }
         }

         if (okay)
         {
            me->save_file = fopen(me->save_file_name, "w");
            if (me->save_file == (FILE *) NULL)
            {
               fprintf(stderr, "file_close: can't open '%s' as model file\n", me->save_file_name);
               exit(1);
            }

            SaveModel(me);

            me->project_saved = TRUE;

            fclose(me->save_file);
         }
      }
   }

   InitDatabase(me);
   UpdateDisplay(me);
   
   printf("files closed\n");
}


void file_export_raw(Widget w, void *data)
{
   MyProgram *me=data;
   char *raw_file_name;

   printf("exporting raw ...\n");

   raw_file_name = GetString("Enter file name to export for renderer (file.rnd)\n", NULL);

   if ( (raw_file_name != (char *) NULL) && (strlen(raw_file_name) > 0) )
   {
      if (strlen(raw_file_name) < FILE_STRING_LEN)
         strcpy(me->export_raw_file_name, raw_file_name);
      else {
         strncpy(me->export_raw_file_name, raw_file_name, FILE_STRING_LEN);
         me->export_raw_file_name[FILE_STRING_LEN - 1] = '\0';
      }

      me->export_raw_file = fopen(me->export_raw_file_name, "w");
      if (me->export_raw_file == (FILE *) NULL)
      {
         fprintf(stderr, "file_export_raw: can't open '%s' as export file\n", me->export_raw_file_name);
         exit(1);
      }
   
      ExportModel(me);

      me->project_exported = TRUE;

      fclose(me->export_raw_file);

      printf("done export\n");
   }
   else
      printf("export cancelled\n");

}

void file_export_vrml(Widget w, void *data)
{
   MyProgram *me=data;
   char *vrml_file_name;

   printf("exporting vrml ...\n");

   vrml_file_name = GetString("Enter file name to export vrml (file.wrl)\n", NULL);

   if ( (vrml_file_name != (char *) NULL) && (strlen(vrml_file_name) > 0) )
   {
      if (strlen(vrml_file_name) < FILE_STRING_LEN)
         strcpy(me->export_vrml_file_name, vrml_file_name);
      else {
         strncpy(me->export_vrml_file_name, vrml_file_name, FILE_STRING_LEN);
         me->export_vrml_file_name[FILE_STRING_LEN - 1] = '\0';
      }

      me->export_vrml_file = fopen(me->export_vrml_file_name, "w");
      if (me->export_vrml_file == (FILE *) NULL)
      {
         fprintf(stderr, "file_export_vrml: can't open '%s' as vrml file\n", me->export_vrml_file_name);
         exit(1);
      }
   
      ExportVRML(me);

      me->project_vrml = TRUE;

      fclose(me->export_vrml_file);

      printf("done export vrml\n");
   }
   else
      printf("export vrml cancelled\n");

}



void file_about(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("Modeler\n\n  by Brian Lingard\n\nversion 1.0");  
}


void file_help(Widget w, void *data)
{
   int okay;

   okay = GetYesNo("HELP\n----\n\nFile->Open - to load model\nFile->Save - to save model\nFile->Save As - save to new file\nFile->Close - close current file\nFile->Export - dump info for renderer");  
}


void file_quit(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char *new_file_name;

   /* Do any cleanup that is necessary for your program here */

   if (me->project_saved == FALSE)
   {
      okay = GetYesNo("Model file not saved!!\n\nDo you want to save it now?");  
      if (okay)
      {
         if (strlen(me->save_file_name) == 0)
         {
            new_file_name = GetString("Enter file name to save as (file.mdl)\n", NULL);

            if ( (new_file_name != (char *) NULL) 
			&& (strlen(new_file_name) > 0) )
            {
               if (strlen(new_file_name) < FILE_STRING_LEN)
                  strcpy(me->save_file_name, new_file_name);
               else {
                  strncpy(me->save_file_name, new_file_name, FILE_STRING_LEN);
                  me->save_file_name[FILE_STRING_LEN - 1] = '\0';
               }
            }
            else
            {
               printf("saving cancelled\n");
               okay = FALSE;
            }
         }

         if (okay)
         {
            me->save_file = fopen(me->save_file_name, "w");
            if (me->save_file == (FILE *) NULL)
            {
               fprintf(stderr, "file_close: can't open '%s' as model file\n", me->save_file_name);
               exit(1);
            }

            SaveModel(me);

            me->project_saved = TRUE;

            fclose(me->save_file);
         }
      }
   }

   okay = GetYesNo("Do you really want to quit?");  
   if (okay)
   {
      printf("We're out of here!!!\n");
      exit(0);
   }
}


/* command callbacks */

void cmd_add_prim(Widget w, void *data)
{
  MyProgram *me=data;
  PRIMITIVE_S_T new_primitive;

  printf("add primitive\n");

  if (add_prim(FALSE, &new_primitive))
     printf("  Cancelled\n");
  else
     AddPrimitiveToDatabase(&new_primitive, me);
}

void cmd_del_prim(Widget w, void *data)
{
  MyProgram *me=data;
  int index;

  printf("delete primitive\n");

  if (del_prim(TRUE, &index, me))
     printf("  Cancelled\n");
  else
     DeletePrimitiveFromDatabase(index, me);
}

void cmd_edit_prim(Widget w, void *data)
{
  MyProgram *me=data;
  PRIMITIVE_S_T *primitive;
  int index;

  printf("edit primitive\n");

  if (del_prim(FALSE, &index, me))
    printf("  Cancelled\n");
  else
  {
    printf("  selected primitive %d\n", index);

    primitive = &me->data.prim_list[index];

    if (add_prim(TRUE, primitive))
      printf("  Cancelled\n");
    else
    {
      TranslateDatabase(me);
      UpdateDisplay(me);
    }
  }
}

void cmd_edit_camera(Widget w, void *data)
{
  MyProgram *me=data;

  printf("edit camera view\n");

  if (edit_cam(&me->data.view))
    printf("  Cancelled\n");
  else
  {
    printf(" camera attributes:\n");
    printf("  eye loc %f %f %f \n", me->data.view.eyeloc.x, me->data.view.eyeloc.y, me->data.view.eyeloc.z);
    printf("  lookat  %f %f %f \n", me->data.view.lookat.x, me->data.view.lookat.y, me->data.view.lookat.z);
    printf("  vup     %f %f %f \n", me->data.view.vup.x, me->data.view.vup.y, me->data.view.vup.z);
    printf("  vrp     %f %f %f \n", me->data.view.vrp.x, me->data.view.vrp.y, me->data.view.vrp.z);

    me->project_saved = FALSE;

    UpdateDisplay(me);
  }
}

void cmd_edit_light(Widget w, void *data)
{
  MyProgram *me=data;

  printf("edit light\n");

  if (edit_lit(&me->data.light))
    printf("Cancelled\n");
  else
  {
    printf("light attributes:\n");
    printf("  type      %d\n", me->data.light.type);
    printf("  location  %f %f %f \n", me->data.light.location.x, me->data.light.location.y, me->data.light.location.z);
    printf("  direction %f %f %f \n", me->data.light.direction.x, me->data.light.direction.y, me->data.light.direction.z);
    printf("  spot size %f \n", me->data.light.spot_size);
    printf("  intensity %f \n", me->data.light.intensity);
    printf("  color     %d %d %d\n", me->data.light.color[0], me->data.light.color[1], me->data.light.color[2]);

    me->project_saved = FALSE;

    UpdateDisplay(me);
  }
}

void cmd_edit_anim(Widget w, void *data)
{
  MyProgram *me=data;

  printf("edit anim\n");

  if (editanim(&me->data.anim))
    printf("Cancelled\n");
  else
  {
    printf("anim attributes:\n");
    printf("  type       %d\n", me->data.anim.type);
    printf("  num frames %d\n", me->data.anim.num_frames);
    printf("  frame rate %d\n", me->data.anim.frame_rate);
    printf("  start eye pt %f %f %f \n", me->data.anim.lpath.start_eye_pt.x, me->data.anim.lpath.start_eye_pt.y, me->data.anim.lpath.start_eye_pt.z);
    printf("  end eye pt   %f %f %f \n", me->data.anim.lpath.end_eye_pt.x, me->data.anim.lpath.end_eye_pt.y, me->data.anim.lpath.end_eye_pt.z);
    printf("  start lap pt %f %f %f \n", me->data.anim.lpath.start_lap_pt.x, me->data.anim.lpath.start_lap_pt.y, me->data.anim.lpath.start_lap_pt.z);
    printf("  end lap pt   %f %f %f \n", me->data.anim.lpath.end_lap_pt.x, me->data.anim.lpath.end_lap_pt.y, me->data.anim.lpath.end_lap_pt.z);

    SetupAnimToRun(data);
  }
}



/* options callbacks */

void opt_setup_defaults(Widget w, void *data)
{
   MyProgram *me=data;

  printf("setup defaults\n");

/*
  if (setupdef(me))
    printf("Cancelled\n");
  else
  {

  }
*/
}

void opt_dump_database(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;

   okay = GetYesNo("Do you really want to\ndump the entire database?"); 

   if (okay == TRUE)
   {
      printf("dumping database ... ");
      DumpDatabase(me);
      printf("done dumping\n");
   }
}

void opt_status(Widget w, void *data)
{
   MyProgram *me=data;
   int okay;
   char status[400], string[50];

   sprintf(status, "Current Status\n--------------\n");

   sprintf(string, "\nLoad File = %s\n", me->load_file_name);
   strcat(status, string);

   sprintf(string, "Save File = %s\n", me->save_file_name);
   strcat(status, string);

   sprintf(string, "Export Raw File = %s\n", me->export_raw_file_name);
   strcat(status, string);

   sprintf(string, "Export VRML File = %s\n", me->export_vrml_file_name);
   strcat(status, string);

   sprintf(string, "\nNumber Primitives = %d out of %d\n", me->data.prim_count, MAX_PRIMITIVES);
   strcat(status, string);

   sprintf(string, "Number Vertices = %d out of %d\n", me->data.vert_count, MAX_VERTICES);
   strcat(status, string);

   sprintf(string, "Number Polygons = %d out of %d\n", me->data.poly_count, MAX_POLYGONS);
   strcat(status, string);

   sprintf(string, "\nDatabase size = %d bytes\n", sizeof(*me));
   strcat(status, string);

   switch(me->view_screen_mode)
   {
      case ALL_VIEW:
         sprintf(string, "\nView Mode = All\n");
         break;
      case ORTH_XY_VIEW:
         sprintf(string, "\nView Mode = XY\n");
         break;
      case ORTH_ZY_VIEW:
         sprintf(string, "\nView Mode = ZY\n");
         break;
      case ORTH_XZ_VIEW:
         sprintf(string, "\nView Mode = XZ\n");
         break;
      case CAMERA_VIEW:
         sprintf(string, "\nView Mode = Camera\n");
         break;
   }
   strcat(status, string);

   switch(me->render_mode)
   {
      case WIRE_REND:
         sprintf(string, "Render Mode = Wire\n\n");
         break;
      case SOLID_REND:
         sprintf(string, "Render Mode = Solid\n\n");
         break;
      case SHADE_REND:
         sprintf(string, "Render Mode = Shade\n\n");
         break;
   }
   strcat(status, string);

   switch(me->data.light.type)
   {
      case AMB_LIGHT:
         sprintf(string, "Lighting Type = Ambient\n\n");
         break;
      case POINT_LIGHT:
         sprintf(string, "Lighting Type = Point\n\n");
         break;
      case SPOT_LIGHT:
         sprintf(string, "Lighting Type = Spot\n\n");
         break;
      case INFIN_LIGHT:
         sprintf(string, "Lighting Type = Infinite\n\n");
         break;
   }
   strcat(status, string);

   switch(me->data.anim.type)
   {
      case NO_ANIM:
         sprintf(string, "Anim Path Type = None\n");
         break;
      case LINEAR_ANIM:
         sprintf(string, "Anim Path Type = Linear\n");
         break;
      case CIRCLE_ANIM:
         sprintf(string, "Anim Path Type = Circle\n");
         break;
      case BEZIER_ANIM:
         sprintf(string, "Anim Path Type = Bezier\n");
         break;
      case SPLINE_ANIM:
         sprintf(string, "Anim Path Type = Spline\n");
         break;
   }
   strcat(status, string);
   sprintf(string, "Number of Frames = %d\n", me->data.anim.num_frames);
   strcat(status, string);
   sprintf(string, "Frame Rate = %d\n\n", me->data.anim.frame_rate);
   strcat(status, string);

   okay = GetYesNo(status); 
}

void opt_toggle_color(Widget w, void *data)
{
  MyProgram *me=data;

  if ( enable_color_render )
  {   
     enable_color_render = FALSE;
     printf("color rendering disabled\n");
  }
  else
  {
     enable_color_render = TRUE;
     printf("color rendering enabled\n");
  }

  UpdateDisplay(me);
  
}


/* view callbacks */

void view_all(Widget w, void *data)
{
  MyProgram *me=data;

  me->view_screen_mode = ALL_VIEW;

  UpdateDisplay(me);
}

void view_xy(Widget w, void *data)
{
  MyProgram *me=data;

  me->view_screen_mode = ORTH_XY_VIEW;

  UpdateDisplay(me);
}

void view_zy(Widget w, void *data)
{
  MyProgram *me=data;

  me->view_screen_mode = ORTH_ZY_VIEW;

  UpdateDisplay(me);
}

void view_xz(Widget w, void *data)
{
  MyProgram *me=data;

  me->view_screen_mode = ORTH_XZ_VIEW;

  UpdateDisplay(me);
}

void view_camera(Widget w, void *data)
{
  MyProgram *me=data;

  me->view_screen_mode = CAMERA_VIEW;

  UpdateDisplay(me);
}


/* render callbacks */

void rend_wire(Widget w, void *data)
{
  MyProgram *me=data;

  me->render_mode = WIRE_REND;

  UpdateDisplay(me);
}

void rend_solid(Widget w, void *data)
{
  MyProgram *me=data;

  me->render_mode = SOLID_REND;

  UpdateDisplay(me);
}

void rend_flat(Widget w, void *data)
{
  MyProgram *me=data;

  me->render_mode = SHADE_REND;

  UpdateDisplay(me);
}


/* anim callbacks */

void next_frame(void *data, XtIntervalId *id)
{
  MyProgram *me=data;

  if (me->data.anim.enable_anim) 
  {

/*     
printf("frame #%d:\n", me->data.anim.frame_count);
*/

     switch(me->data.anim.mode)
     {
        case STOP_ANIM:
           ComputeNextFrame(me);
           me->data.anim.enable_anim = FALSE;
           break;

        case RUN_ANIM:
           ComputeNextFrame(me);
           AddTimeOut(me->data.anim.frame_interval, 
						((void *)next_frame), data);

           if (me->data.anim.forward 
		&& (me->data.anim.frame_count >= me->data.anim.num_frames))
           {
              me->data.anim.enable_anim = FALSE;
              CopyWPoint( &me->data.anim.lpath.start_eye_pt, 
					&me->data.anim.lpath.curr_eye_pt);
              CopyWPoint( &me->data.anim.lpath.start_eye_pt, 
					&me->data.view.eyeloc);

              CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.anim.lpath.curr_lap_pt);
              CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.view.lookat);
              CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.view.vrp);
           }

           if (!me->data.anim.forward && (me->data.anim.frame_count == 0))
           {
              me->data.anim.enable_anim = FALSE;
              CopyWPoint( &me->data.anim.lpath.end_eye_pt, 
					&me->data.anim.lpath.curr_eye_pt);
              CopyWPoint( &me->data.anim.lpath.end_eye_pt, 
					&me->data.view.eyeloc);

              CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.anim.lpath.curr_lap_pt);
              CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.view.lookat);
              CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.view.vrp);
           }
           break;

        case LOOP_ANIM:
           ComputeNextFrame(me);
           AddTimeOut(me->data.anim.frame_interval, 
						((void *)next_frame), data);

           if (me->data.anim.frame_count >= me->data.anim.num_frames)
           {
              CopyWPoint( &me->data.anim.lpath.start_eye_pt, 
					&me->data.anim.lpath.curr_eye_pt);
              CopyWPoint( &me->data.anim.lpath.start_eye_pt, 
					&me->data.view.eyeloc);

              CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.anim.lpath.curr_lap_pt);
              CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.view.lookat);
              CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.view.vrp);
              me->data.anim.frame_count = 0;
           }
           break;

        case PING_ANIM:
           ComputeNextFrame(me);
           AddTimeOut(me->data.anim.frame_interval, 
						((void *)next_frame), data);

           if (me->data.anim.forward 
		&& (me->data.anim.frame_count >= me->data.anim.num_frames))
           {
              me->data.anim.forward = FALSE;
           }

           if (!me->data.anim.forward && (me->data.anim.frame_count == 0))
           {
              me->data.anim.forward = TRUE;
           }
           break;

        case STEP_ANIM:
           ComputeNextFrame(me);
           me->data.anim.enable_anim = FALSE;
           break;

        default:
           me->data.anim.enable_anim = FALSE;
           break;
     }
  }
}

void anim_stop(Widget w, void *data)
{
  MyProgram *me=data;

  me->data.anim.mode = STOP_ANIM;
  me->data.anim.enable_anim = FALSE;

  printf("stop anim\n");
}

void anim_run_forward(Widget w, void *data)
{
  MyProgram *me=data;

  if (me->data.anim.type != NO_ANIM)
  {
     me->data.anim.mode = RUN_ANIM;
     me->data.anim.enable_anim = TRUE;
     me->data.anim.forward = TRUE;
     me->data.anim.frame_count = 0;

     CopyWPoint( &me->data.anim.lpath.start_eye_pt, 
					&me->data.anim.lpath.curr_eye_pt);
     CopyWPoint( &me->data.anim.lpath.start_eye_pt, 
					&me->data.view.eyeloc);

     CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.anim.lpath.curr_lap_pt);
     CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.view.lookat);
     CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.view.vrp);

     ComputeNextFrame(me);

     AddTimeOut(me->data.anim.frame_interval, ((void *)next_frame), data);

     printf("running anim forward\n");
  }
}

void anim_run_reverse(Widget w, void *data)
{
  MyProgram *me=data;

  if (me->data.anim.type != NO_ANIM)
  {
     me->data.anim.mode = RUN_ANIM;
     me->data.anim.enable_anim = TRUE;
     me->data.anim.forward = FALSE;
     me->data.anim.frame_count = me->data.anim.num_frames - 1;

     CopyWPoint( &me->data.anim.lpath.end_eye_pt, 
					&me->data.anim.lpath.curr_eye_pt);
     CopyWPoint( &me->data.anim.lpath.end_eye_pt, 
					&me->data.view.eyeloc);

     CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.anim.lpath.curr_lap_pt);
     CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.view.lookat);
     CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.view.vrp);

     ComputeNextFrame(me);

     AddTimeOut(me->data.anim.frame_interval, ((void *)next_frame), data);

     printf("running anim reverse\n");
  }
}

void anim_loop(Widget w, void *data)
{
  MyProgram *me=data;

  if (me->data.anim.type != NO_ANIM)
  {
     me->data.anim.mode = LOOP_ANIM;
     me->data.anim.enable_anim = TRUE;
     me->data.anim.forward = TRUE;
     me->data.anim.frame_count = 0;

     AddTimeOut(me->data.anim.frame_interval, ((void *)next_frame), data);

     printf("looping anim\n");
  }
}

void anim_ping(Widget w, void *data)
{
  MyProgram *me=data;

  if (me->data.anim.type != NO_ANIM)
  {
     me->data.anim.mode = PING_ANIM;
     me->data.anim.enable_anim = TRUE;
     me->data.anim.forward = TRUE;
     me->data.anim.frame_count = 0;

     AddTimeOut(me->data.anim.frame_interval, ((void *)next_frame), data);

     printf("looping anim\n");
  }
}

void anim_step_forward(Widget w, void *data)
{
  MyProgram *me=data;

  if (me->data.anim.type != NO_ANIM)
  {
     me->data.anim.mode = STEP_ANIM;
     me->data.anim.enable_anim = TRUE;
     me->data.anim.forward = TRUE;

     AddTimeOut(me->data.anim.frame_interval, ((void *)next_frame), data);

     printf("stepping anim\n");
  }
}

void anim_step_reverse(Widget w, void *data)
{
  MyProgram *me=data;

  if (me->data.anim.type != NO_ANIM)
  {
     me->data.anim.mode = STEP_ANIM;
     me->data.anim.enable_anim = TRUE;
     me->data.anim.forward = FALSE;

     AddTimeOut(me->data.anim.frame_interval, ((void *)next_frame), data);

     printf("stepping anim\n");
  }
}

void anim_first(Widget w, void *data)
{
  MyProgram *me=data;

  if (me->data.anim.type != NO_ANIM)
  {
     me->data.anim.mode = STEP_ANIM;
     me->data.anim.enable_anim = TRUE;

     me->data.anim.frame_count = 0;

     CopyWPoint( &me->data.anim.lpath.start_eye_pt, 
					&me->data.anim.lpath.curr_eye_pt);
     CopyWPoint( &me->data.anim.lpath.start_eye_pt, 
					&me->data.view.eyeloc);

     CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.anim.lpath.curr_lap_pt);
     CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.view.lookat);
     CopyWPoint( &me->data.anim.lpath.start_lap_pt, 
					&me->data.view.vrp);

     ComputeNextFrame(me);

     printf("first frame of anim\n");
  }
}

void anim_last(Widget w, void *data)
{
  MyProgram *me=data;

  if (me->data.anim.type != NO_ANIM)
  {
     me->data.anim.mode = STEP_ANIM;
     me->data.anim.enable_anim = TRUE;

     me->data.anim.frame_count = me->data.anim.num_frames - 1;

     CopyWPoint( &me->data.anim.lpath.end_eye_pt, 
					&me->data.anim.lpath.curr_eye_pt);
     CopyWPoint( &me->data.anim.lpath.end_eye_pt, 
					&me->data.view.eyeloc);

     CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.anim.lpath.curr_lap_pt);
     CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.view.lookat);
     CopyWPoint( &me->data.anim.lpath.end_lap_pt, 
					&me->data.view.vrp);

     ComputeNextFrame(me);

     printf("last frame of anim\n");
  }
}


/* zoom callbacks */

void zoom_in(Widget w, void *data)
{
  MyProgram *me=data;

  me->zoom_value -= (0.25 * DEFAULT_ZOOM_VALUE);

  UpdateDisplay(me);
}

void zoom_normal(Widget w, void *data)
{
  MyProgram *me=data;

  me->zoom_value = DEFAULT_ZOOM_VALUE;

  UpdateDisplay(me);
}

void zoom_out(Widget w, void *data)
{
  MyProgram *me=data;

  me->zoom_value += (0.25 * DEFAULT_ZOOM_VALUE);

  UpdateDisplay(me);
}



/*
 * The following functions are callbacks for the drawing area widgets.
 *
 * The only required callback is redisplay().  The others are optional
 * but have been setup to be used by init_display() in main.c.
 */


/* Here is where all redrawing will take place for your program. 
 * When the window needs to be redrawn, this function will be called.
 * When your program starts up for the first time, this function will 
 * be called and you should draw anything you need to draw in here.
 */
void redisplay(Widget w, int new_width, int new_height, void *data)
{
   MyProgram *me=data;

   UpdateDisplay(me);
}


void button_down(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;

   printf("You clicked button %d at (%d,%d)\n", which_button, x,y);
}


void button_up(Widget w, int which_button, int x, int y, void *data)
{
   MyProgram *me=data;

   printf("You released button %d at (%d,%d)\n", which_button, x,y);
}




/*
 * The following function is called when keypresses happen in the drawing
 * area widget.
 *
 *  It is useful to know that the string returned to your program is
 * not necessarily a single ASCII character. You will get the usual
 * ASCII characters, including control characters (such as ^C or ^H).
 * But, the workstation's function keys will also be returned in a
 * string such as "F11" or "F23".  You will also get other longer
 * strings such as "Control_L", "Alt_R", or "Shift_L".  It is
 * important to understand that even if you just press the shift key to
 * get a capital letter, you will first receive the string "Shift_L"
 * or "Shift_R", then you will receive a capital letter (say, "H").
 * You should probably ignore the "Shift_L" or "Shift_R" messages (but
 * who knows, you may find some use for them).
 *
 * The argument, up_or_down, tells you whether the given key was pressed 
 * or released.  If the key was pressed down, up_or_down has a zero (0),
 * if the key was released, up_or_down contains a 1.
 *
 * NOTE WELL:
 *   The string that is returned to you can _NOT_ (I'll repeat that,
 *   can _NOT_) be modified by your program.  Got it?  Do _NOT_ modify
 *   the string.  If you want to munge with it, make a copy using
 *   strdup() or strcpy() into your own buffer space.
 */

void keypress(Widget w, char *input, int up_or_down, void *data)
{
   char *str;

   if (input == NULL)
     return;

   if (up_or_down == 0)
      str = "pressed";
   else
      str = "released";

   printf("You %s : <<%s>>\n", str, input);
}




/* Called when a DrawingArea gets mouse motion events.  The arguments
 * X and Y are the current position of the mouse in the window.
 *
 * NOTE: This routine should be _fast_ because *every* single time
 *       the mouse moves in the drawing area, this function is called. 
 *       So even if you are just moving the mouse across the drawing area,
 *       this routine is called. As it stands, it doesn't do anything.
 */
void motion(Widget w, int x, int y, void *data)
{
  MyProgram *me=data;

}
