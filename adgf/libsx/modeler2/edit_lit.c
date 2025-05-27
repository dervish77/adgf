/* 
 * edit_lit()
 * 
 * Popup dialog for editing the light source attributes.
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
  Widget 	lreq_window;
  Widget 	type_list;
  Widget 	lx_string, ly_string, lz_string;
  Widget 	dx_string, dy_string, dz_string;
  Widget 	spot_string;
  Widget 	int_string;
  Widget 	color_string;
  UBYTE_T 	r, g, b;
  int 		cancelled;
  LIGHT_S_T	data;
} LReqData;

#define LIGHT_LIST_WIDTH 	100
#define LIGHT_LIST_HEIGHT	75

static char *light_item_list[] = 
{ 
	"Ambient", "Point", "Spot", 
	"Infinite", NULL
};

#define DEFAULT_POS	((float) 30.0)
#define DEFAULT_DIR	((float) 0.0)
#define DEFAULT_SPOT	((float) 30.0)
#define DEFAULT_INT	((float) 1.0)


static void init_light_data(LReqData *data);

static void lit_list_cb(Widget w, char *string, int index, LReqData *data);
static void location_x(Widget w, char *string, LReqData *data);
static void location_y(Widget w, char *string, LReqData *data);
static void location_z(Widget w, char *string, LReqData *data);

static void direction_x(Widget w, char *string, LReqData *data);
static void direction_y(Widget w, char *string, LReqData *data);
static void direction_z(Widget w, char *string, LReqData *data);

static void spot_angle(Widget w, char *string, LReqData *data);
static void intensity(Widget w, char *string, LReqData *data);

static void color_edit(Widget w, LReqData *data);

static void button_ok(Widget w, LReqData *data);
static void button_cancel(Widget w, LReqData *data);
static void button_clear(Widget w, LReqData *data);



int edit_lit(LIGHT_S_T *light)
{
  LReqData 	ldata;
  Widget 	w[28];
  char 		value[8];
  char 		cvalue[12];
  int 		width;
  int 		cwidth;

  /* copy current lighting data */
  ldata.data.type = light->type;
  ldata.data.location.x = light->location.x;
  ldata.data.location.y = light->location.y;
  ldata.data.location.z = light->location.z;
  ldata.data.direction.x = light->direction.x;
  ldata.data.direction.y = light->direction.y;
  ldata.data.direction.z = light->direction.z;
  ldata.data.spot_size = light->spot_size;
  ldata.data.intensity = light->intensity;
  ldata.data.color[R_IDX] = light->color[R_IDX];
  ldata.data.color[G_IDX] = light->color[G_IDX];
  ldata.data.color[B_IDX] = light->color[B_IDX];
  ldata.r = ldata.data.color[R_IDX];
  ldata.g = ldata.data.color[G_IDX];
  ldata.b = ldata.data.color[B_IDX];


  ldata.lreq_window = MakeWindow("Edit Light Source", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);


  w[0] = MakeLabel("Light Type ");
  w[1] = MakeScrollList(light_item_list, LIGHT_LIST_WIDTH, LIGHT_LIST_HEIGHT, (void *)lit_list_cb, &ldata);

  /* determine the width to make the string widgets with */
  width = TextWidth(GetWidgetFont(w[0]),  "88888888");
  cwidth = TextWidth(GetWidgetFont(w[0]),  "888888888888");

  w[2] = MakeLabel("Location");
  sprintf(value, "%3.3f", ldata.data.location.x);
  w[3] = MakeLabel("X ");
  w[4] = MakeStringEntry(value, width, (void *)location_x, &ldata);
  sprintf(value, "%3.3f", ldata.data.location.y);
  w[5] = MakeLabel("Y ");
  w[6] = MakeStringEntry(value, width, (void *)location_y, &ldata);
  sprintf(value, "%3.3f", ldata.data.location.z);
  w[7] = MakeLabel("Z ");
  w[8] = MakeStringEntry(value, width, (void *)location_z, &ldata);

  w[9] = MakeLabel("Direction");
  sprintf(value, "%3.3f", ldata.data.direction.x);
  w[10] = MakeLabel("X ");
  w[11] = MakeStringEntry(value, width, (void *)direction_x, &ldata);
  sprintf(value, "%3.3f", ldata.data.direction.y);
  w[12] = MakeLabel("Y ");
  w[13] = MakeStringEntry(value, width, (void *)direction_y, &ldata);
  sprintf(value, "%3.3f", ldata.data.direction.z);
  w[14] = MakeLabel("Z ");
  w[15] = MakeStringEntry(value, width, (void *)direction_z, &ldata);

  w[16] = MakeLabel("Spot Size ");
  sprintf(value, "%3.3f", ldata.data.spot_size);
  w[17] = MakeStringEntry(value, width, (void *)spot_angle, &ldata);
  w[18] = MakeLabel(" degrees ");

  w[19] = MakeLabel("Intensity ");
  sprintf(value, "%3.3f", ldata.data.intensity);
  w[20] = MakeStringEntry(value, width, (void *)intensity, &ldata);
  w[21] = MakeLabel(" lumens ");

  w[22] = MakeLabel("Color ");
  sprintf(cvalue, "%d %d %d", ldata.data.color[R_IDX], ldata.data.color[G_IDX], ldata.data.color[B_IDX]);
  w[23] = MakeStringEntry(cvalue, cwidth, (void *)NULL, NULL);
  w[24] = MakeButton(" Edit ", (void *)color_edit, &ldata);

  w[25] = MakeButton("   OK   ", (void *)button_ok, &ldata);
  w[26] = MakeButton(" Cancel ", (void *)button_cancel, &ldata);
  w[27] = MakeButton(" Clear  ", (void *)button_clear, &ldata);



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
  SetWidgetPos(w[17], PLACE_RIGHT, w[16], PLACE_UNDER, w[10]);
  SetWidgetPos(w[18], PLACE_RIGHT, w[17], PLACE_UNDER, w[10]);

  SetWidgetPos(w[19], PLACE_UNDER, w[16], NO_CARE,     NULL);
  SetWidgetPos(w[20], PLACE_RIGHT, w[19], PLACE_UNDER, w[16]);
  SetWidgetPos(w[21], PLACE_RIGHT, w[20], PLACE_UNDER, w[16]);

  SetWidgetPos(w[22], PLACE_UNDER, w[19], NO_CARE,     NULL);
  SetWidgetPos(w[23], PLACE_RIGHT, w[22], PLACE_UNDER, w[19]);
  SetWidgetPos(w[24], PLACE_RIGHT, w[23], PLACE_UNDER, w[19]);

  SetWidgetPos(w[25], PLACE_UNDER, w[22], NO_CARE,     NULL);
  SetWidgetPos(w[26], PLACE_RIGHT, w[25], PLACE_UNDER, w[22]);
  SetWidgetPos(w[27], PLACE_RIGHT, w[26], PLACE_UNDER, w[22]);


  /* save important widgets */
  ldata.type_list     = w[1];
  ldata.lx_string     = w[4];
  ldata.ly_string     = w[6];
  ldata.lz_string     = w[8];
  ldata.dx_string     = w[11];
  ldata.dy_string     = w[13];
  ldata.dz_string     = w[15];
  ldata.spot_string   = w[17];
  ldata.int_string    = w[20];
  ldata.color_string  = w[23];

  SetCurrentListItem(ldata.type_list, (ldata.data.type - 1));

  ShowDisplay();

  GetStandardColors();

  SetFgColor(w[25], WHITE);
  SetBgColor(w[25], BLUE);
  SetFgColor(w[26], WHITE);
  SetBgColor(w[26], BLUE);
  SetFgColor(w[27], WHITE);
  SetBgColor(w[27], BLUE);

  MainLoop();

  SetCurrentWindow(ORIGINAL_WINDOW);

  /* check for cancel */
  if (ldata.cancelled)
    return(TRUE);

  /* copy entered light source data */
  light->type = ldata.data.type;
  light->location.x = ldata.data.location.x;
  light->location.y = ldata.data.location.y;
  light->location.z = ldata.data.location.z;
  light->direction.x = ldata.data.direction.x;
  light->direction.y = ldata.data.direction.y;
  light->direction.z = ldata.data.direction.z;
  light->spot_size = ldata.data.spot_size;
  light->intensity = ldata.data.intensity;
  light->color[R_IDX] = ldata.data.color[R_IDX];
  light->color[G_IDX] = ldata.data.color[G_IDX];
  light->color[B_IDX] = ldata.data.color[B_IDX];

  return(FALSE);
}


/*    widget callbacks 
 */
void lit_list_cb(Widget w, char *string, int index, LReqData *data)
{
  data->data.type = index + 1;

  printf("picked index %d, %d\n", index, data->data.type);
}

void location_x(Widget w, char *string, LReqData *data)
{
  LReqData *me=data;
  float value;

  value = atof(string);

  me->data.location.x = value;
}

void location_y(Widget w, char *string, LReqData *data)
{
  LReqData *me=data;
  float value;

  value = atof(string);

  me->data.location.y = value;
}

void location_z(Widget w, char *string, LReqData *data)
{
  LReqData *me=data;
  float value;

  value = atof(string);

  me->data.location.z = value;
}

void direction_x(Widget w, char *string, LReqData *data)
{
  LReqData *me=data;
  float value;

  value = atof(string);

  me->data.direction.x = value;
}

void direction_y(Widget w, char *string, LReqData *data)
{
  LReqData *me=data;
  float value;

  value = atof(string);

  me->data.direction.y = value;
}

void direction_z(Widget w, char *string, LReqData *data)
{
  LReqData *me=data;
  float value;

  value = atof(string);

  me->data.direction.z = value;
}

void spot_angle(Widget w, char *string, LReqData *data)
{
  LReqData *me=data;
  float value;

  value = atof(string);

  me->data.spot_size = value;
}

void intensity(Widget w, char *string, LReqData *data)
{
  LReqData *me=data;
  float value;

  value = atof(string);

  me->data.intensity = value;
}

void color_edit(Widget w, LReqData *data)
{
  LReqData *me=data;
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

void button_ok(Widget w, LReqData *data)
{
  data->cancelled = FALSE;
  SetCurrentWindow(data->lreq_window);
  CloseWindow();
}

void button_cancel(Widget w, LReqData *data)
{
  data->cancelled = TRUE;
  SetCurrentWindow(data->lreq_window);
  CloseWindow();
}

void button_clear(Widget w, LReqData *data)
{
  char value[8];
  char cvalue[12];

  init_light_data(data);

  SetCurrentListItem(data->type_list, 0);

  sprintf(value, "%3.3f", DEFAULT_POS);
  SetStringEntry(data->lx_string, value);
  SetStringEntry(data->ly_string, value);
  SetStringEntry(data->lz_string, value);

  sprintf(value, "%3.3f", DEFAULT_DIR);
  SetStringEntry(data->dx_string, value);
  SetStringEntry(data->dy_string, value);
  SetStringEntry(data->dz_string, value);

  sprintf(value, "%3.3f", DEFAULT_SPOT);
  SetStringEntry(data->spot_string, value);

  sprintf(value, "%3.3f", DEFAULT_INT);
  SetStringEntry(data->int_string, value);

  sprintf(cvalue, "%d %d %d", data->r, data->g, data->b);
  SetStringEntry(data->color_string, cvalue);

}

void init_light_data(LReqData *data)
{
  data->r = 253;  
  data->g = 253;  
  data->b = 253;
  data->cancelled = TRUE;

  data->data.type = AMB_LIGHT;

  data->data.location.x = DEFAULT_POS;  
  data->data.location.y = DEFAULT_POS;  
  data->data.location.z = DEFAULT_POS;

  data->data.direction.x = DEFAULT_DIR; 
  data->data.direction.y = DEFAULT_DIR; 
  data->data.direction.z = DEFAULT_DIR;

  data->data.spot_size = DEFAULT_SPOT; 
  data->data.intensity = DEFAULT_INT;

  data->data.color[R_IDX] = 253; 
  data->data.color[G_IDX] = 253;
  data->data.color[B_IDX] = 253;
}
