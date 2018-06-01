/* 
 * edit_cam()
 * 
 * Popup dialog for editing the camera attributes.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsx.h"             /* should come first, defines libsx stuff  */

#ifndef _MAIN_H
#include "main.h"              /* where program specific stuff is defined */
#endif

typedef struct {
  Widget 	vreq_window;
  Widget 	lx_string, ly_string, lz_string;
  Widget 	ax_string, ay_string, az_string;
  Widget 	ux_string, uy_string, uz_string;
  Widget 	vx_string, vy_string, vz_string;
  int 		cancelled;
  VIEW_S_T	data;
} VReqData;

#define DEFAULT_LOC	((float) 10.0)
#define DEFAULT_AT	((float) 0.0)
#define DEFAULT_UP	((float) 1.0)
#define DEFAULT_VRP	((float) 0.0)


static void init_view_data(VReqData *data);

static void location_x(Widget w, char *string, VReqData *data);
static void location_y(Widget w, char *string, VReqData *data);
static void location_z(Widget w, char *string, VReqData *data);

static void look_at_x(Widget w, char *string, VReqData *data);
static void look_at_y(Widget w, char *string, VReqData *data);
static void look_at_z(Widget w, char *string, VReqData *data);

static void up_vector_x(Widget w, char *string, VReqData *data);
static void up_vector_y(Widget w, char *string, VReqData *data);
static void up_vector_z(Widget w, char *string, VReqData *data);

static void vrp_x(Widget w, char *string, VReqData *data);
static void vrp_y(Widget w, char *string, VReqData *data);
static void vrp_z(Widget w, char *string, VReqData *data);

static void button_ok(Widget w, VReqData *data);
static void button_cancel(Widget w, VReqData *data);
static void button_clear(Widget w, VReqData *data);



int edit_cam(VIEW_S_T *view)
{
  VReqData 	vdata;
  Widget 	w[31];
  char 		value[8];
  int 		width;

  /* copy current view data */
  vdata.data.eyeloc.x = view->eyeloc.x;
  vdata.data.eyeloc.y = view->eyeloc.y;
  vdata.data.eyeloc.z = view->eyeloc.z;
  vdata.data.lookat.x = view->lookat.x;
  vdata.data.lookat.y = view->lookat.y;
  vdata.data.lookat.z = view->lookat.z;
  vdata.data.vup.x = view->vup.x;
  vdata.data.vup.y = view->vup.y;
  vdata.data.vup.z = view->vup.z;
  vdata.data.vrp.x = view->vrp.x;
  vdata.data.vrp.y = view->vrp.y;
  vdata.data.vrp.z = view->vrp.z;


  vdata.vreq_window = MakeWindow("Edit Camera View", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);


  w[0] = MakeLabel("Location");

  /* determine the width to make the string widgets with */
  width = TextWidth(GetWidgetFont(w[0]),  "88888888");

  sprintf(value, "%3.3f", vdata.data.eyeloc.x);
  w[1] = MakeLabel("X ");
  w[2] = MakeStringEntry(value, width, (void *)location_x, &vdata);
  sprintf(value, "%3.3f", vdata.data.eyeloc.y);
  w[3] = MakeLabel("Y ");
  w[4] = MakeStringEntry(value, width, (void *)location_y, &vdata);
  sprintf(value, "%3.3f", vdata.data.eyeloc.z);
  w[5] = MakeLabel("Z ");
  w[6] = MakeStringEntry(value, width, (void *)location_z, &vdata);

  w[7] = MakeLabel("Look At");
  sprintf(value, "%3.3f", vdata.data.lookat.x);
  w[8] = MakeLabel("X ");
  w[9] = MakeStringEntry(value, width, (void *)look_at_x, &vdata);
  sprintf(value, "%3.3f", vdata.data.lookat.y);
  w[10] = MakeLabel("Y ");
  w[11] = MakeStringEntry(value, width, (void *)look_at_y, &vdata);
  sprintf(value, "%3.3f", vdata.data.lookat.z);
  w[12] = MakeLabel("Z ");
  w[13] = MakeStringEntry(value, width, (void *)look_at_z, &vdata);

  w[14] = MakeLabel("Up Vector");
  sprintf(value, "%3.3f", vdata.data.vup.x);
  w[15] = MakeLabel("X ");
  w[16] = MakeStringEntry(value, width, (void *)up_vector_x, &vdata);
  sprintf(value, "%3.3f", vdata.data.vup.y);
  w[17] = MakeLabel("Y ");
  w[18] = MakeStringEntry(value, width, (void *)up_vector_y, &vdata);
  sprintf(value, "%3.3f", vdata.data.vup.z);
  w[19] = MakeLabel("Z ");
  w[20] = MakeStringEntry(value, width, (void *)up_vector_z, &vdata);

  w[21] = MakeLabel("View Ref Point");
  sprintf(value, "%3.3f", vdata.data.vrp.x);
  w[22] = MakeLabel("X ");
  w[23] = MakeStringEntry(value, width, (void *)vrp_x, &vdata);
  sprintf(value, "%3.3f", vdata.data.vrp.y);
  w[24] = MakeLabel("Y ");
  w[25] = MakeStringEntry(value, width, (void *)vrp_y, &vdata);
  sprintf(value, "%3.3f", vdata.data.vrp.z);
  w[26] = MakeLabel("Z ");
  w[27] = MakeStringEntry(value, width, (void *)vrp_z, &vdata);

  w[28] = MakeButton("   OK   ", (void *)button_ok, &vdata);
  w[29] = MakeButton(" Cancel ", (void *)button_cancel, &vdata);
  w[30] = MakeButton(" Clear  ", (void *)button_clear, &vdata);


  /* position all the little widgets */
  SetWidgetPos(w[1],  PLACE_UNDER, w[0],  NO_CARE,     NULL);
  SetWidgetPos(w[2],  PLACE_RIGHT, w[1],  PLACE_UNDER, w[0]);
  SetWidgetPos(w[3],  PLACE_RIGHT, w[2],  PLACE_UNDER, w[0]);
  SetWidgetPos(w[4],  PLACE_RIGHT, w[3],  PLACE_UNDER, w[0]);
  SetWidgetPos(w[5],  PLACE_RIGHT, w[4],  PLACE_UNDER, w[0]);
  SetWidgetPos(w[6],  PLACE_RIGHT, w[5],  PLACE_UNDER, w[0]);

  SetWidgetPos(w[7],  PLACE_UNDER, w[1],  NO_CARE,     NULL);
  SetWidgetPos(w[8],  PLACE_UNDER, w[7],  NO_CARE,     NULL);
  SetWidgetPos(w[9],  PLACE_RIGHT, w[8],  PLACE_UNDER, w[7]);
  SetWidgetPos(w[10], PLACE_RIGHT, w[9],  PLACE_UNDER, w[7]);
  SetWidgetPos(w[11], PLACE_RIGHT, w[10], PLACE_UNDER, w[7]);
  SetWidgetPos(w[12], PLACE_RIGHT, w[11], PLACE_UNDER, w[7]);
  SetWidgetPos(w[13], PLACE_RIGHT, w[12], PLACE_UNDER, w[7]);

  SetWidgetPos(w[14], PLACE_UNDER, w[8],  NO_CARE,     NULL);
  SetWidgetPos(w[15], PLACE_UNDER, w[14], NO_CARE,     NULL);
  SetWidgetPos(w[16], PLACE_RIGHT, w[15], PLACE_UNDER, w[14]);
  SetWidgetPos(w[17], PLACE_RIGHT, w[16], PLACE_UNDER, w[14]);
  SetWidgetPos(w[18], PLACE_RIGHT, w[17], PLACE_UNDER, w[14]);
  SetWidgetPos(w[19], PLACE_RIGHT, w[18], PLACE_UNDER, w[14]);
  SetWidgetPos(w[20], PLACE_RIGHT, w[19], PLACE_UNDER, w[14]);

  SetWidgetPos(w[21], PLACE_UNDER, w[15], NO_CARE,     NULL);
  SetWidgetPos(w[22], PLACE_UNDER, w[21], NO_CARE,     NULL);
  SetWidgetPos(w[23], PLACE_RIGHT, w[22], PLACE_UNDER, w[21]);
  SetWidgetPos(w[24], PLACE_RIGHT, w[23], PLACE_UNDER, w[21]);
  SetWidgetPos(w[25], PLACE_RIGHT, w[24], PLACE_UNDER, w[21]);
  SetWidgetPos(w[26], PLACE_RIGHT, w[25], PLACE_UNDER, w[21]);
  SetWidgetPos(w[27], PLACE_RIGHT, w[26], PLACE_UNDER, w[21]);

  SetWidgetPos(w[28], PLACE_UNDER, w[22], NO_CARE,     NULL);
  SetWidgetPos(w[29], PLACE_RIGHT, w[28], PLACE_UNDER, w[22]);
  SetWidgetPos(w[30], PLACE_RIGHT, w[29], PLACE_UNDER, w[22]);


  /* save important widgets */
  vdata.lx_string     = w[2];
  vdata.ly_string     = w[4];
  vdata.lz_string     = w[6];
  vdata.ax_string     = w[9];
  vdata.ay_string     = w[11];
  vdata.az_string     = w[13];
  vdata.ux_string     = w[16];
  vdata.uy_string     = w[18];
  vdata.uz_string     = w[20];
  vdata.vx_string     = w[23];
  vdata.vy_string     = w[25];
  vdata.vz_string     = w[27];

  ShowDisplay();

  GetStandardColors();

  SetFgColor(w[28], WHITE);
  SetBgColor(w[28], BLUE);
  SetFgColor(w[29], WHITE);
  SetBgColor(w[29], BLUE);
  SetFgColor(w[30], WHITE);
  SetBgColor(w[30], BLUE);

  MainLoop();

  SetCurrentWindow(ORIGINAL_WINDOW);

  /* check for cancel */
  if (vdata.cancelled)
    return(TRUE);

  /* copy entered camera view data */
  view->eyeloc.x = vdata.data.eyeloc.x;
  view->eyeloc.y = vdata.data.eyeloc.y;
  view->eyeloc.z = vdata.data.eyeloc.z;
  view->lookat.x = vdata.data.lookat.x;
  view->lookat.y = vdata.data.lookat.y;
  view->lookat.z = vdata.data.lookat.z;
  view->vup.x = vdata.data.vup.x;
  view->vup.y = vdata.data.vup.y;
  view->vup.z = vdata.data.vup.z;
  view->vrp.x = vdata.data.vrp.x;
  view->vrp.y = vdata.data.vrp.y;
  view->vrp.z = vdata.data.vrp.z;

  return(FALSE);
}


/*    widget callbacks 
 */
void location_x(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.eyeloc.x = value;
}

void location_y(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.eyeloc.y = value;
}

void location_z(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.eyeloc.z = value;
}

void look_at_x(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.lookat.x = value;
}

void look_at_y(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.lookat.y = value;
}

void look_at_z(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.lookat.z = value;
}

void up_vector_x(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.vup.x = value;
}

void up_vector_y(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.vup.y = value;
}

void up_vector_z(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.vup.z = value;
}

void vrp_x(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.vrp.x = value;
}

void vrp_y(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.vrp.y = value;
}

void vrp_z(Widget w, char *string, VReqData *data)
{
  VReqData *me=data;
  float value;

  value = atof(string);

  me->data.vrp.z = value;
}


void button_ok(Widget w, VReqData *data)
{
  char *string;
  data->cancelled = FALSE;

  string = GetStringEntry(data->lx_string);
  data->data.eyeloc.x = atof(string);
  string = GetStringEntry(data->ly_string);
  data->data.eyeloc.y = atof(string);
  string = GetStringEntry(data->lz_string);
  data->data.eyeloc.z = atof(string);

  string = GetStringEntry(data->ax_string);
  data->data.lookat.x = atof(string);
  string = GetStringEntry(data->ay_string);
  data->data.lookat.y = atof(string);
  string = GetStringEntry(data->az_string);
  data->data.lookat.z = atof(string);

  string = GetStringEntry(data->ux_string);
  data->data.vup.x = atof(string);
  string = GetStringEntry(data->uy_string);
  data->data.vup.y = atof(string);
  string = GetStringEntry(data->uz_string);
  data->data.vup.z = atof(string);

  string = GetStringEntry(data->vx_string);
  data->data.vrp.x = atof(string);
  string = GetStringEntry(data->vy_string);
  data->data.vrp.y = atof(string);
  string = GetStringEntry(data->vz_string);
  data->data.vrp.z = atof(string);

  SetCurrentWindow(data->vreq_window);
  CloseWindow();
}

void button_cancel(Widget w, VReqData *data)
{
  data->cancelled = TRUE;
  SetCurrentWindow(data->vreq_window);
  CloseWindow();
}

void button_clear(Widget w, VReqData *data)
{
  char value[8];

  init_view_data(data);

  sprintf(value, "%3.3f", -DEFAULT_LOC);
  SetStringEntry(data->lx_string, value);
  sprintf(value, "%3.3f", DEFAULT_LOC);
  SetStringEntry(data->ly_string, value);
  sprintf(value, "%3.3f", -DEFAULT_LOC);
  SetStringEntry(data->lz_string, value);

  sprintf(value, "%3.3f", DEFAULT_AT);
  SetStringEntry(data->ax_string, value);
  SetStringEntry(data->ay_string, value);
  SetStringEntry(data->az_string, value);

  sprintf(value, "%3.3f", 0.0);
  SetStringEntry(data->ux_string, value);
  sprintf(value, "%3.3f", 1.0);
  SetStringEntry(data->uy_string, value);
  sprintf(value, "%3.3f", 0.0);
  SetStringEntry(data->uz_string, value);

  sprintf(value, "%3.3f", DEFAULT_VRP);
  SetStringEntry(data->vx_string, value);
  SetStringEntry(data->vy_string, value);
  SetStringEntry(data->vz_string, value);
}

void init_view_data(VReqData *data)
{
  data->cancelled = TRUE;

  data->data.eyeloc.x = -DEFAULT_LOC;  
  data->data.eyeloc.y = DEFAULT_LOC;  
  data->data.eyeloc.z = -DEFAULT_LOC;

  data->data.lookat.x = DEFAULT_AT; 
  data->data.lookat.y = DEFAULT_AT; 
  data->data.lookat.z = DEFAULT_AT;

  data->data.vup.x = 0.0; 
  data->data.vup.y = 1.0; 
  data->data.vup.z = 0.0;

  data->data.vrp.x = DEFAULT_VRP; 
  data->data.vrp.y = DEFAULT_VRP; 
  data->data.vrp.z = DEFAULT_VRP;

}
