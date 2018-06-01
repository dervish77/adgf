/* 
 * add_prim()
 * 
 * Popup dialog for select a new primitive object and its attributes.
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
  Widget 	preq_window;
  Widget 	type_list;
  Widget 	cx_string, cy_string, cz_string;
  Widget 	sx_string, sy_string, sz_string;
  Widget	lsx_string, lsy_string, lsz_string;
  Widget 	axis_string, angle_string, color_string;
  UBYTE_T 	r, g, b;
  int 		cancelled;
  PRIMITIVE_S_T	data;
} PReqData;

#define LIST_WIDTH 	100
#define LIST_HEIGHT	75

static char *type_item_list[] = 
{ 
	"Plane", "Cube", "Cylinder", "Pyramid", 
	"Prism", "Cone", "Sphere", NULL
};

#define DEFAULT_CENTER	((float) 0.0)
#define DEFAULT_SCALE	((float) 1.0)
#define DEFAULT_AXIS	'n'
#define DEFAULT_ANGLE	((float) 0.0)

#define DEFAULT_GREY	((unsigned char) 175)


static void init_data(PReqData *data);

static void list_cb(Widget w, char *string, int index, PReqData *data);
static void center_x(Widget w, char *string, PReqData *data);
static void center_y(Widget w, char *string, PReqData *data);
static void center_z(Widget w, char *string, PReqData *data);

static void scaling_x(Widget w, char *string, PReqData *data);
static void scaling_y(Widget w, char *string, PReqData *data);
static void scaling_z(Widget w, char *string, PReqData *data);

static void rotate_axis(Widget w, char *string, PReqData *data);
static void rotate_angle(Widget w, char *string, PReqData *data);

static void color_edit(Widget w, PReqData *data);

static void button_ok(Widget w, PReqData *data);
static void button_cancel(Widget w, PReqData *data);
static void button_clear(Widget w, PReqData *data);


int add_prim(BOOLEAN_T edit_flag, PRIMITIVE_S_T *new)
{
  PReqData 	pdata;
  Widget 	w[27];
  char 		value[8];
  char 		cvalue[12];
  int 		width;
  int 		awidth;
  int 		cwidth;

  if (edit_flag)
  {
     /* copy necessary data */
     pdata.data.type = new->type;
     pdata.data.center.x = new->center.x;
     pdata.data.center.y = new->center.y;
     pdata.data.center.z = new->center.z;
     pdata.data.scaling.x = new->scaling.x;
     pdata.data.scaling.y = new->scaling.y;
     pdata.data.scaling.z = new->scaling.z;
     pdata.data.axis = new->axis;
     pdata.data.angle = new->angle;
     pdata.data.color[R_IDX] = new->color[R_IDX];
     pdata.data.color[G_IDX] = new->color[G_IDX];
     pdata.data.color[B_IDX] = new->color[B_IDX];

     pdata.r = pdata.data.color[R_IDX];
     pdata.g = pdata.data.color[G_IDX];
     pdata.b = pdata.data.color[B_IDX];

     pdata.preq_window = MakeWindow("Edit Primitive", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);
  }
  else
  {
     /* init necessary data */
     init_data(&pdata);

     pdata.preq_window = MakeWindow("Add Primitive", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);
  }


  w[0] = MakeLabel("Primitive Type ");
  w[1] = MakeScrollList(type_item_list, LIST_WIDTH, LIST_HEIGHT, (void *)list_cb, &pdata);

  /* determine the width to make the string widgets with */
  awidth = TextWidth(GetWidgetFont(w[0]),  "88");
  width = TextWidth(GetWidgetFont(w[0]),  "88888888");
  cwidth = TextWidth(GetWidgetFont(w[0]),  "888888888888");

  w[2] = MakeLabel("Center");
  sprintf(value, "%3.3f", pdata.data.center.x);
  w[3] = MakeLabel("X ");
  w[4] = MakeStringEntry(value, width, (void *)center_x, &pdata);
  sprintf(value, "%3.3f", pdata.data.center.y);
  w[5] = MakeLabel("Y ");
  w[6] = MakeStringEntry(value, width, (void *)center_y, &pdata);
  sprintf(value, "%3.3f", pdata.data.center.z);
  w[7] = MakeLabel("Z ");
  w[8] = MakeStringEntry(value, width, (void *)center_z, &pdata);

  w[9] = MakeLabel("Scaling");
  sprintf(value, "%3.3f", pdata.data.scaling.x);
  if ((pdata.data.type == CYLIN_PRIM) || (pdata.data.type == CONE_PRIM))
  {
     w[10] = MakeLabel("R ");
  }
  else
  {
     w[10] = MakeLabel("X ");
  }
  w[11] = MakeStringEntry(value, width, (void *)scaling_x, &pdata);
  sprintf(value, "%3.3f", pdata.data.scaling.y);
  if ((pdata.data.type == CYLIN_PRIM) || (pdata.data.type == CONE_PRIM))
  {
     w[12] = MakeLabel("S ");
  }
  else
  {
     w[12] = MakeLabel("Y ");
  }
  w[13] = MakeStringEntry(value, width, (void *)scaling_y, &pdata);
  sprintf(value, "%3.3f", pdata.data.scaling.z);
  if ((pdata.data.type == CYLIN_PRIM) || (pdata.data.type == CONE_PRIM))
  {
     w[14] = MakeLabel("H ");
  }
  else
  {
     w[14] = MakeLabel("Z ");
  }
  w[15] = MakeStringEntry(value, width, (void *)scaling_z, &pdata);

  w[16] = MakeLabel("Rotation");
  value[0] = pdata.data.axis;
  value[1] = '\0';
  w[17] = MakeLabel("Axis ");
  w[18] = MakeStringEntry(value, awidth, (void *)rotate_axis, &pdata);
  sprintf(value, "%3.3f", pdata.data.angle);
  w[19] = MakeLabel("Angle ");
  w[20] = MakeStringEntry(value, width, (void *)rotate_angle, &pdata);

  w[21] = MakeLabel("Color ");
  sprintf(cvalue, "%d %d %d", pdata.data.color[R_IDX], pdata.data.color[G_IDX], pdata.data.color[B_IDX]);
  w[22] = MakeStringEntry(cvalue, cwidth, (void *)NULL, NULL);
  w[23] = MakeButton(" Edit ", (void *)color_edit, &pdata);

  w[24] = MakeButton("   OK   ", (void *)button_ok, &pdata);
  w[25] = MakeButton(" Cancel ", (void *)button_cancel, &pdata);
  w[26] = MakeButton(" Clear  ", (void *)button_clear, &pdata);


  /* position all the little widgets */
  SetWidgetPos(w[1],  PLACE_RIGHT, w[0], NO_CARE,     NULL);

  SetWidgetPos(w[2],  PLACE_UNDER, w[1],  NO_CARE,     NULL);
  SetWidgetPos(w[3],  PLACE_UNDER, w[2],  NO_CARE,     NULL);
  SetWidgetPos(w[4],  PLACE_RIGHT, w[3],  PLACE_UNDER, w[2]);
  SetWidgetPos(w[5],  PLACE_RIGHT, w[4],  PLACE_UNDER, w[2]);
  SetWidgetPos(w[6],  PLACE_RIGHT, w[5],  PLACE_UNDER, w[2]);
  SetWidgetPos(w[7],  PLACE_RIGHT, w[6],  PLACE_UNDER, w[2]);
  SetWidgetPos(w[8],  PLACE_RIGHT, w[7],  PLACE_UNDER, w[2]);

  SetWidgetPos(w[9],  PLACE_UNDER, w[3],  NO_CARE,     NULL);
  SetWidgetPos(w[10], PLACE_UNDER, w[9],  NO_CARE,     NULL);
  SetWidgetPos(w[11], PLACE_RIGHT, w[10], PLACE_UNDER, w[9]);
  SetWidgetPos(w[12], PLACE_RIGHT, w[11], PLACE_UNDER, w[9]);
  SetWidgetPos(w[13], PLACE_RIGHT, w[12], PLACE_UNDER, w[9]);
  SetWidgetPos(w[14], PLACE_RIGHT, w[13], PLACE_UNDER, w[9]);
  SetWidgetPos(w[15], PLACE_RIGHT, w[14], PLACE_UNDER, w[9]);

  SetWidgetPos(w[16], PLACE_UNDER, w[10], NO_CARE,     NULL);
  SetWidgetPos(w[17], PLACE_UNDER, w[16], NO_CARE,     NULL);
  SetWidgetPos(w[18], PLACE_RIGHT, w[17], PLACE_UNDER, w[16]);
  SetWidgetPos(w[19], PLACE_RIGHT, w[18], PLACE_UNDER, w[16]);
  SetWidgetPos(w[20], PLACE_RIGHT, w[19], PLACE_UNDER, w[16]);

  SetWidgetPos(w[21], PLACE_UNDER, w[17], NO_CARE,     NULL);
  SetWidgetPos(w[22], PLACE_RIGHT, w[21], PLACE_UNDER, w[17]);
  SetWidgetPos(w[23], PLACE_RIGHT, w[22], PLACE_UNDER, w[17]);

  SetWidgetPos(w[24], PLACE_UNDER, w[21], NO_CARE,     NULL);
  SetWidgetPos(w[25], PLACE_RIGHT, w[24], PLACE_UNDER, w[21]);
  SetWidgetPos(w[26], PLACE_RIGHT, w[25], PLACE_UNDER, w[21]);

  /* save important widgets */
  pdata.type_list     = w[1];
  pdata.cx_string     = w[4];
  pdata.cy_string     = w[6];
  pdata.cz_string     = w[8];
  pdata.lsx_string    = w[10];
  pdata.sx_string     = w[11];
  pdata.lsy_string    = w[12];
  pdata.sy_string     = w[13];
  pdata.lsz_string    = w[14];
  pdata.sz_string     = w[15];
  pdata.axis_string   = w[17];
  pdata.angle_string  = w[19];
  pdata.color_string  = w[22];

  SetCurrentListItem(pdata.type_list, (pdata.data.type - 1));

  ShowDisplay();

  GetStandardColors();

  SetFgColor(w[24], WHITE);
  SetBgColor(w[24], BLUE);
  SetFgColor(w[25], WHITE);
  SetBgColor(w[25], BLUE);
  SetFgColor(w[26], WHITE);
  SetBgColor(w[26], BLUE);

  MainLoop();

  SetCurrentWindow(ORIGINAL_WINDOW);

  /* check for cancel */
  if(pdata.cancelled)
    return(TRUE);

  /* copy entered primitive data */
  new->type = pdata.data.type;
  new->center.x = pdata.data.center.x;
  new->center.y = pdata.data.center.y;
  new->center.z = pdata.data.center.z;
  new->scaling.x = pdata.data.scaling.x;
  new->scaling.y = pdata.data.scaling.y;
  new->scaling.z = pdata.data.scaling.z;
  new->axis = pdata.data.axis;
  new->angle = pdata.data.angle;
  new->color[R_IDX] = pdata.data.color[R_IDX];
  new->color[G_IDX] = pdata.data.color[G_IDX];
  new->color[B_IDX] = pdata.data.color[B_IDX];

  return(FALSE);
}


/*    widget callbacks 
 */
void list_cb(Widget w, char *string, int index, PReqData *data)
{
  char value[3];

  data->data.type = index + 1;

  if ((data->data.type == CYLIN_PRIM) || (data->data.type == CONE_PRIM))
  {
     sprintf(value, "R ");
     SetLabel(data->lsx_string, value);
     sprintf(value, "S ");
     SetLabel(data->lsy_string, value);
     sprintf(value, "H ");
     SetLabel(data->lsz_string, value);
  }
  else
  {
     sprintf(value, "X ");
     SetLabel(data->lsx_string, value);
     sprintf(value, "Y ");
     SetLabel(data->lsy_string, value);
     sprintf(value, "Z ");
     SetLabel(data->lsz_string, value);
  }

  printf("picked index %d, %d\n", index, data->data.type);
}

void center_x(Widget w, char *string, PReqData *data)
{
  PReqData *me=data;
  float value;

  value = atof(string);

  me->data.center.x = value;
}

void center_y(Widget w, char *string, PReqData *data)
{
  PReqData *me=data;
  float value;

  value = atof(string);

  me->data.center.y = value;
}

void center_z(Widget w, char *string, PReqData *data)
{
  PReqData *me=data;
  float value;

  value = atof(string);

  me->data.center.z = value;
}

void scaling_x(Widget w, char *string, PReqData *data)
{
  PReqData *me=data;
  float value;

  value = atof(string);

  me->data.scaling.x = value;
}

void scaling_y(Widget w, char *string, PReqData *data)
{
  PReqData *me=data;
  float value;

  value = atof(string);

  me->data.scaling.y = value;
}

void scaling_z(Widget w, char *string, PReqData *data)
{
  PReqData *me=data;
  float value;

  value = atof(string);

  me->data.scaling.z = value;
}

void rotate_axis(Widget w, char *string, PReqData *data)
{
  PReqData *me=data;

  me->data.axis = string[0];
}

void rotate_angle(Widget w, char *string, PReqData *data)
{
  PReqData *me=data;
  float value;

  value = atof(string);

  me->data.angle = value;
}

void color_edit(Widget w, PReqData *data)
{
  PReqData *me=data;
  unsigned char r,g,b;
  char cvalue[12];
  
  r = me->r; g = me->g; b = me->b;

  if (GetColor(&r, &g, &b))
    printf("Cancelled\n");
  else
    printf("Red=%d, Green=%d, Blue=%d\n", r, g, b);

  me->data.color[R_IDX] = r;
  me->data.color[G_IDX] = g;
  me->data.color[B_IDX] = b;
  me->r = r;
  me->g = g;
  me->b = b;

  sprintf(cvalue, "%d %d %d", me->r, me->g, me->b);
  SetStringEntry(data->color_string, cvalue);
}

void button_ok(Widget w, PReqData *data)
{
  data->cancelled = FALSE;
  SetCurrentWindow(data->preq_window);
  CloseWindow();
}

void button_cancel(Widget w, PReqData *data)
{
  data->cancelled = TRUE;
  SetCurrentWindow(data->preq_window);
  CloseWindow();
}

void button_clear(Widget w, PReqData *data)
{
  char value[8];
  char cvalue[12];

  init_data(data);

  SetCurrentListItem(data->type_list, 0);

  sprintf(value, "%3.3f", DEFAULT_CENTER);
  SetStringEntry(data->cx_string, value);
  SetStringEntry(data->cy_string, value);
  SetStringEntry(data->cz_string, value);

  sprintf(value, "%3.3f", DEFAULT_SCALE);
  SetStringEntry(data->sx_string, value);
  SetStringEntry(data->sy_string, value);
  SetStringEntry(data->sz_string, value);

  sprintf(value, "%c", DEFAULT_AXIS);
  SetStringEntry(data->axis_string, value);
  sprintf(value, "%3.3f", DEFAULT_ANGLE);
  SetStringEntry(data->angle_string, value);

  sprintf(cvalue, "%d %d %d", data->r, data->g, data->b);
  SetStringEntry(data->color_string, cvalue);

}

void init_data(PReqData *data)
{
  data->r = DEFAULT_GREY;  
  data->g = DEFAULT_GREY;  
  data->b = DEFAULT_GREY;
  data->cancelled = TRUE;

  data->data.type = PLANE_PRIM;

  data->data.center.x = DEFAULT_CENTER;  
  data->data.center.y = DEFAULT_CENTER;  
  data->data.center.z = DEFAULT_CENTER;

  data->data.scaling.x = DEFAULT_SCALE; 
  data->data.scaling.y = DEFAULT_SCALE; 
  data->data.scaling.z = DEFAULT_SCALE;

  data->data.axis = DEFAULT_AXIS; 
  data->data.angle = DEFAULT_ANGLE;

  data->data.color[R_IDX] = DEFAULT_GREY; 
  data->data.color[G_IDX] = DEFAULT_GREY;
  data->data.color[B_IDX] = DEFAULT_GREY;
}
