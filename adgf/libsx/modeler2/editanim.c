/* 
 * editanim()
 * 
 * Popup dialog for editing animation attributes.
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
  Widget 	areq_window;
  Widget 	type_list;
  Widget 	nf_string, fr_string;
  Widget 	lin_sx_string, lin_sy_string, lin_sz_string;
  Widget 	lin_ex_string, lin_ey_string, lin_ez_string;
  int 		cancelled;
  ANIM_S_T	data;
} AReqData;

#define ANIM_LIST_WIDTH 	100
#define ANIM_LIST_HEIGHT	75

static char *anim_item_list[] = 
{ 
	"None", "Linear", "Circle", 
	"Bezier", "Spline", NULL
};

#define DEFAULT_NF	((int) 20)
#define DEFAULT_FR	((int) 15)
#define DEFAULT_LIN_S	((float) 10.0)
#define DEFAULT_LIN_E	((float) 10.0)


static void init_anim_data(AReqData *data);

static void anim_list_cb(Widget w, char *string, int index, AReqData *data);

static void num_frames(Widget w, char *string, AReqData *data);
static void frame_rate(Widget w, char *string, AReqData *data);

static void start_eye_pt_x(Widget w, char *string, AReqData *data);
static void start_eye_pt_y(Widget w, char *string, AReqData *data);
static void start_eye_pt_z(Widget w, char *string, AReqData *data);

static void end_eye_pt_x(Widget w, char *string, AReqData *data);
static void end_eye_pt_y(Widget w, char *string, AReqData *data);
static void end_eye_pt_z(Widget w, char *string, AReqData *data);

static void button_ok(Widget w, AReqData *data);
static void button_cancel(Widget w, AReqData *data);
static void button_clear(Widget w, AReqData *data);



int editanim(ANIM_S_T *anim)
{
  AReqData 	adata;
  Widget 	w[28];
  char 		value[8];
  char 		ivalue[6];
  int 		width;
  int 		iwidth;

  /* copy current lighting data */
  adata.data.type = anim->type;
  adata.data.num_frames = anim->num_frames;
  adata.data.frame_rate = anim->frame_rate;
  adata.data.lpath.start_eye_pt.x = anim->lpath.start_eye_pt.x;
  adata.data.lpath.start_eye_pt.y = anim->lpath.start_eye_pt.y;
  adata.data.lpath.start_eye_pt.z = anim->lpath.start_eye_pt.z;
  adata.data.lpath.end_eye_pt.x = anim->lpath.end_eye_pt.x;
  adata.data.lpath.end_eye_pt.y = anim->lpath.end_eye_pt.y;
  adata.data.lpath.end_eye_pt.z = anim->lpath.end_eye_pt.z;


  adata.areq_window = MakeWindow("Edit Animation", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);


  w[0] = MakeLabel("Anim Path Type ");
  w[1] = MakeScrollList(anim_item_list, ANIM_LIST_WIDTH, ANIM_LIST_HEIGHT, (void *)anim_list_cb, &adata);

  /* determine the width to make the string widgets with */
  width = TextWidth(GetWidgetFont(w[0]),  "88888888");
  iwidth = TextWidth(GetWidgetFont(w[0]),  "888888");

  w[2] = MakeLabel("        ");

  w[3] = MakeLabel("Num Frames ");
  sprintf(ivalue, "%4d", adata.data.num_frames);
  w[4] = MakeStringEntry(ivalue, iwidth, (void *)num_frames, &adata);

  w[5] = MakeLabel("Frame Rate ");
  sprintf(ivalue, "%4d", adata.data.frame_rate);
  w[6] = MakeStringEntry(ivalue, iwidth, (void *)frame_rate, &adata);
  w[7] = MakeLabel(" frames per sec ");

  w[8] = MakeLabel("        ");
  w[9] = MakeLabel("Linear Path Parameters");

  w[10] = MakeLabel("   Start Eye Point");
  sprintf(value, "%3.3f", adata.data.lpath.start_eye_pt.x);
  w[11] = MakeLabel("   X ");
  w[12] = MakeStringEntry(value, width, (void *)start_eye_pt_x, &adata);
  sprintf(value, "%3.3f", adata.data.lpath.start_eye_pt.y);
  w[13] = MakeLabel("Y ");
  w[14] = MakeStringEntry(value, width, (void *)start_eye_pt_y, &adata);
  sprintf(value, "%3.3f", adata.data.lpath.start_eye_pt.z);
  w[15] = MakeLabel("Z ");
  w[16] = MakeStringEntry(value, width, (void *)start_eye_pt_z, &adata);

  w[17] = MakeLabel("   End Eye Point");
  sprintf(value, "%3.3f", adata.data.lpath.end_eye_pt.x);
  w[18] = MakeLabel("   X ");
  w[19] = MakeStringEntry(value, width, (void *)end_eye_pt_x, &adata);
  sprintf(value, "%3.3f", adata.data.lpath.end_eye_pt.y);
  w[20] = MakeLabel("Y ");
  w[21] = MakeStringEntry(value, width, (void *)end_eye_pt_y, &adata);
  sprintf(value, "%3.3f", adata.data.lpath.end_eye_pt.z);
  w[22] = MakeLabel("Z ");
  w[23] = MakeStringEntry(value, width, (void *)end_eye_pt_z, &adata);

  w[24] = MakeLabel("        ");

  w[25] = MakeButton("   OK   ", (void *)button_ok, &adata);
  w[26] = MakeButton(" Cancel ", (void *)button_cancel, &adata);
  w[27] = MakeButton(" Clear  ", (void *)button_clear, &adata);



  /* position all the little widgets */
  
  SetWidgetPos(w[1],  PLACE_RIGHT, w[0],  NO_CARE,     NULL);

  SetWidgetPos(w[2],  PLACE_UNDER, w[1],  NO_CARE,     NULL);

  SetWidgetPos(w[3],  PLACE_UNDER, w[2],  NO_CARE,     NULL);
  SetWidgetPos(w[4],  PLACE_RIGHT, w[3],  PLACE_UNDER, w[2]);

  SetWidgetPos(w[5],  PLACE_UNDER, w[3],  NO_CARE,     NULL);
  SetWidgetPos(w[6],  PLACE_RIGHT, w[5],  PLACE_UNDER, w[3]);
  SetWidgetPos(w[7],  PLACE_RIGHT, w[6],  PLACE_UNDER, w[3]);

  SetWidgetPos(w[8],  PLACE_UNDER, w[5],  NO_CARE,     NULL);
  SetWidgetPos(w[9],  PLACE_UNDER, w[8],  NO_CARE,     NULL);

  SetWidgetPos(w[10], PLACE_UNDER, w[9],  NO_CARE,     NULL);
  SetWidgetPos(w[11], PLACE_UNDER, w[10], NO_CARE,     NULL);
  SetWidgetPos(w[12], PLACE_RIGHT, w[11], PLACE_UNDER, w[10]);
  SetWidgetPos(w[13], PLACE_RIGHT, w[12], PLACE_UNDER, w[10]);
  SetWidgetPos(w[14], PLACE_RIGHT, w[13], PLACE_UNDER, w[10]);
  SetWidgetPos(w[15], PLACE_RIGHT, w[14], PLACE_UNDER, w[10]);
  SetWidgetPos(w[16], PLACE_RIGHT, w[15], PLACE_UNDER, w[10]);

  SetWidgetPos(w[17], PLACE_UNDER, w[11], NO_CARE,     NULL);
  SetWidgetPos(w[18], PLACE_UNDER, w[17], NO_CARE,     NULL);
  SetWidgetPos(w[19], PLACE_RIGHT, w[18], PLACE_UNDER, w[17]);
  SetWidgetPos(w[20], PLACE_RIGHT, w[19], PLACE_UNDER, w[17]);
  SetWidgetPos(w[21], PLACE_RIGHT, w[20], PLACE_UNDER, w[17]);
  SetWidgetPos(w[22], PLACE_RIGHT, w[21], PLACE_UNDER, w[17]);
  SetWidgetPos(w[23], PLACE_RIGHT, w[22], PLACE_UNDER, w[17]);

  SetWidgetPos(w[24], PLACE_UNDER, w[23], NO_CARE,     NULL);

  SetWidgetPos(w[25], PLACE_UNDER, w[24], NO_CARE,     NULL);
  SetWidgetPos(w[26], PLACE_RIGHT, w[25], PLACE_UNDER, w[24]);
  SetWidgetPos(w[27], PLACE_RIGHT, w[26], PLACE_UNDER, w[24]);

  /* save important widgets */
  adata.type_list         = w[1];
  adata.nf_string         = w[4];
  adata.fr_string         = w[6];
  adata.lin_sx_string     = w[12];
  adata.lin_sy_string     = w[14];
  adata.lin_sz_string     = w[16];
  adata.lin_ex_string     = w[19];
  adata.lin_ey_string     = w[21];
  adata.lin_ez_string     = w[23];

  SetCurrentListItem(adata.type_list, (adata.data.type - 1));

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
  if (adata.cancelled)
    return(TRUE);

  /* copy entered light source data */
  anim->type = adata.data.type;
  anim->num_frames = adata.data.num_frames;
  anim->frame_rate = adata.data.frame_rate;
  anim->lpath.start_eye_pt.x = adata.data.lpath.start_eye_pt.x;
  anim->lpath.start_eye_pt.y = adata.data.lpath.start_eye_pt.y;
  anim->lpath.start_eye_pt.z = adata.data.lpath.start_eye_pt.z;
  anim->lpath.end_eye_pt.x = adata.data.lpath.end_eye_pt.x;
  anim->lpath.end_eye_pt.y = adata.data.lpath.end_eye_pt.y;
  anim->lpath.end_eye_pt.z = adata.data.lpath.end_eye_pt.z;

  return(FALSE);
}


/*    widget callbacks 
 */
void anim_list_cb(Widget w, char *string, int index, AReqData *data)
{
  data->data.type = index + 1;
}

void num_frames(Widget w, char *string, AReqData *data)
{
  AReqData *me=data;
  int value;

  value = atoi(string);

  me->data.num_frames = value;
}

void frame_rate(Widget w, char *string, AReqData *data)
{
  AReqData *me=data;
  int value;

  value = atoi(string);

  me->data.frame_rate = value;
}

void start_eye_pt_x(Widget w, char *string, AReqData *data)
{
  AReqData *me=data;
  float value;

  value = atof(string);

  me->data.lpath.start_eye_pt.x = value;
}

void start_eye_pt_y(Widget w, char *string, AReqData *data)
{
  AReqData *me=data;
  float value;

  value = atof(string);

  me->data.lpath.start_eye_pt.y = value;
}

void start_eye_pt_z(Widget w, char *string, AReqData *data)
{
  AReqData *me=data;
  float value;

  value = atof(string);

  me->data.lpath.start_eye_pt.z = value;
}

void end_eye_pt_x(Widget w, char *string, AReqData *data)
{
  AReqData *me=data;
  float value;

  value = atof(string);

  me->data.lpath.end_eye_pt.x = value;
}

void end_eye_pt_y(Widget w, char *string, AReqData *data)
{
  AReqData *me=data;
  float value;

  value = atof(string);

  me->data.lpath.end_eye_pt.y = value;
}

void end_eye_pt_z(Widget w, char *string, AReqData *data)
{
  AReqData *me=data;
  float value;

  value = atof(string);

  me->data.lpath.end_eye_pt.z = value;
}

void button_ok(Widget w, AReqData *data)
{
  data->cancelled = FALSE;
  SetCurrentWindow(data->areq_window);
  CloseWindow();
}

void button_cancel(Widget w, AReqData *data)
{
  data->cancelled = TRUE;
  SetCurrentWindow(data->areq_window);
  CloseWindow();
}

void button_clear(Widget w, AReqData *data)
{
  char value[8];
  char ivalue[6];

  init_anim_data(data);

  SetCurrentListItem(data->type_list, (data->data.type - 1));

  sprintf(value, "%4d", data->data.num_frames);
  SetStringEntry(data->nf_string, value);

  sprintf(value, "%4d", data->data.frame_rate);
  SetStringEntry(data->fr_string, value);

  sprintf(value, "%3.3f", data->data.lpath.start_eye_pt.x);
  SetStringEntry(data->lin_sx_string, value);
  sprintf(value, "%3.3f", data->data.lpath.start_eye_pt.y);
  SetStringEntry(data->lin_sy_string, value);
  sprintf(value, "%3.3f", data->data.lpath.start_eye_pt.z);
  SetStringEntry(data->lin_sz_string, value);

  sprintf(value, "%3.3f", data->data.lpath.end_eye_pt.x);
  SetStringEntry(data->lin_ex_string, value);
  sprintf(value, "%3.3f", data->data.lpath.end_eye_pt.y);
  SetStringEntry(data->lin_ey_string, value);
  sprintf(value, "%3.3f", data->data.lpath.end_eye_pt.z);
  SetStringEntry(data->lin_ez_string, value);
}

void init_anim_data(AReqData *data)
{
  data->data.type = NO_ANIM;

  data->data.num_frames = DEFAULT_NF; 
  data->data.frame_rate = DEFAULT_FR;

  data->data.lpath.start_eye_pt.x = -DEFAULT_LIN_S;  
  data->data.lpath.start_eye_pt.y = 0.0;  
  data->data.lpath.start_eye_pt.z = -DEFAULT_LIN_S;

  data->data.lpath.end_eye_pt.x = -DEFAULT_LIN_E; 
  data->data.lpath.end_eye_pt.y = 0.0; 
  data->data.lpath.end_eye_pt.z = DEFAULT_LIN_E;
}
