/* 
 * iconset()
 * 
 * Popup dialog for setting up an icon's attributes.
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
  Widget 	ireq_window;
  Widget 	sx_string, sy_string;
  Widget 	tlx_string, tly_string;
  Widget 	nc_string;
  int 		cancelled;
  ICON_S_T	data;
} IReqData;


static void init_data(IReqData *data);

static void size_x(Widget w, char *string, IReqData *data);
static void size_y(Widget w, char *string, IReqData *data);

static void top_left_x(Widget w, char *string, IReqData *data);
static void top_left_y(Widget w, char *string, IReqData *data);

static void num_colors(Widget w, char *string, IReqData *data);

static void button_ok(Widget w, IReqData *data);
static void button_cancel(Widget w, IReqData *data);
static void button_clear(Widget w, IReqData *data);


int iconset(ICON_S_T *new)
{
  IReqData 	idata;
  Widget 	w[15];
  char 		value[4];
  int 		width;

     
  /* copy necessary data */
  idata.data.size.x = new->size.x;
  idata.data.size.y = new->size.y;
  idata.data.top_left.x = new->top_left.x;
  idata.data.top_left.y = new->top_left.y;
  idata.data.num_colors = new->num_colors;


  idata.ireq_window = MakeWindow("Setup Icon", SAME_DISPLAY, EXCLUSIVE_WINDOW);


  w[0] = MakeLabel("Icon Size");

  /* determine the width to make the string widgets with */
  width = TextWidth(GetWidgetFont(w[0]),  "8888");

  sprintf(value, "%d", idata.data.size.x);
  w[1] = MakeLabel("X ");
  w[2] = MakeStringEntry(value, width, (void *)size_x, &idata);
  sprintf(value, "%d", idata.data.size.y);
  w[3] = MakeLabel("Y ");
  w[4] = MakeStringEntry(value, width, (void *)size_y, &idata);

  w[5] = MakeLabel("Top Left Position");
  sprintf(value, "%d", idata.data.top_left.x);
  w[6] = MakeLabel("X ");
  w[7] = MakeStringEntry(value, width, (void *)top_left_x, &idata);
  sprintf(value, "%d", idata.data.top_left.y);
  w[8] = MakeLabel("Y ");
  w[9] = MakeStringEntry(value, width, (void *)top_left_y, &idata);

  w[10] = MakeLabel("Num Colors ");
  sprintf(value, "%d", idata.data.num_colors);
  w[11] = MakeStringEntry(value, width, (void *)num_colors, &idata);

  w[12] = MakeButton("   OK   ", (void *)button_ok, &idata);
  w[13] = MakeButton(" Cancel ", (void *)button_cancel, &idata);
  w[14] = MakeButton(" Clear  ", (void *)button_clear, &idata);


  /* position all the little widgets */
  SetWidgetPos(w[1],  PLACE_UNDER, w[0],  NO_CARE,     NULL);
  SetWidgetPos(w[2],  PLACE_RIGHT, w[1],  PLACE_UNDER, w[0]);
  SetWidgetPos(w[3],  PLACE_RIGHT, w[2],  PLACE_UNDER, w[0]);
  SetWidgetPos(w[4],  PLACE_RIGHT, w[3],  PLACE_UNDER, w[0]);

  SetWidgetPos(w[5],  PLACE_UNDER, w[1],  NO_CARE,     NULL);
  SetWidgetPos(w[6],  PLACE_UNDER, w[5],  NO_CARE,     NULL);
  SetWidgetPos(w[7],  PLACE_RIGHT, w[6],  PLACE_UNDER, w[5]);
  SetWidgetPos(w[8],  PLACE_RIGHT, w[7],  PLACE_UNDER, w[5]);
  SetWidgetPos(w[9],  PLACE_RIGHT, w[8],  PLACE_UNDER, w[5]);

  SetWidgetPos(w[10], PLACE_UNDER, w[6],  NO_CARE,     NULL);
  SetWidgetPos(w[11], PLACE_RIGHT, w[10], PLACE_UNDER, w[6]);

  SetWidgetPos(w[12], PLACE_UNDER, w[10], NO_CARE,     NULL);
  SetWidgetPos(w[13], PLACE_RIGHT, w[12], PLACE_UNDER, w[10]);
  SetWidgetPos(w[14], PLACE_RIGHT, w[13], PLACE_UNDER, w[10]);

  /* save important widgets */
  idata.sx_string     = w[2];
  idata.sy_string     = w[4];
  idata.tlx_string    = w[7];
  idata.tly_string    = w[9];
  idata.nc_string     = w[11];


  ShowDisplay();

  GetStandardColors();

  SetFgColor(w[12], WHITE);
  SetBgColor(w[12], BLUE);
  SetFgColor(w[13], WHITE);
  SetBgColor(w[13], BLUE);
  SetFgColor(w[14], WHITE);
  SetBgColor(w[14], BLUE);

  MainLoop();

  SetCurrentWindow(ORIGINAL_WINDOW);

  /* check for cancel */
  if(idata.cancelled)
    return(TRUE);

  /* copy entered primitive data */
  new->size.x = idata.data.size.x;
  new->size.y = idata.data.size.y;
  new->top_left.x = idata.data.top_left.x;
  new->top_left.y = idata.data.top_left.y;
  new->num_colors = idata.data.num_colors;

  return(FALSE);
}


/*    widget callbacks 
 */
void size_x(Widget w, char *string, IReqData *data)
{
  IReqData *me=data;
  float value;

  value = atoi(string);

  if (value <= MAX_ICON_X_SIZE)
     me->data.size.x = value;
  else
     me->data.size.x = MAX_ICON_X_SIZE;
}

void size_y(Widget w, char *string, IReqData *data)
{
  IReqData *me=data;
  float value;

  value = atoi(string);

  if (value <= MAX_ICON_Y_SIZE)
     me->data.size.y = value;
  else
     me->data.size.y = MAX_ICON_Y_SIZE;
}

void top_left_x(Widget w, char *string, IReqData *data)
{
  IReqData *me=data;
  float value;

  value = atoi(string);

  me->data.top_left.x = value;
}

void top_left_y(Widget w, char *string, IReqData *data)
{
  IReqData *me=data;
  float value;

  value = atoi(string);

  me->data.top_left.y = value;
}

void num_colors(Widget w, char *string, IReqData *data)
{
  IReqData *me=data;
  float value;

  value = atoi(string);

  if (value <= MAX_COLORS)
     me->data.num_colors = value;
  else
     me->data.num_colors = MAX_COLORS;
}

void button_ok(Widget w, IReqData *data)
{
  data->cancelled = FALSE;
  SetCurrentWindow(data->ireq_window);
  CloseWindow();
}

void button_cancel(Widget w, IReqData *data)
{
  data->cancelled = TRUE;
  SetCurrentWindow(data->ireq_window);
  CloseWindow();
}

void button_clear(Widget w, IReqData *data)
{
  char value[4];

  init_data(data);

  sprintf(value, "%d", data->data.size.x);
  SetStringEntry(data->sx_string, value);
  sprintf(value, "%d", data->data.size.y);
  SetStringEntry(data->sy_string, value);

  sprintf(value, "%d", data->data.top_left.x);
  SetStringEntry(data->tlx_string, value);
  sprintf(value, "%d", data->data.top_left.y);
  SetStringEntry(data->tly_string, value);

  sprintf(value, "%d", data->data.num_colors);
  SetStringEntry(data->nc_string, value);
}

void init_data(IReqData *data)
{
  data->cancelled = TRUE;

  data->data.size.x = DEFAULT_ICON_X_SIZE;  
  data->data.size.y = DEFAULT_ICON_Y_SIZE;  

  data->data.top_left.x = 0; 
  data->data.top_left.y = 0; 

  data->data.num_colors = MAX_COLORS;
}
