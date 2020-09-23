/* 
 * del_prim()
 * 
 * Popup dialog for selecting a which primitive object to delete from database.
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
  Widget 	dreq_window;
  Widget 	type_list;
  int 		cancelled;
  int		index;
} DReqData;

#define DEL_LIST_WIDTH 	500
#define DEL_LIST_HEIGHT	100

#define MAX_LINE_LEN	120

static char *del_item_list[MAX_PRIMITIVES];


static void del_list_cb(Widget w, char *string, int index, DReqData *data);

static void button_ok(Widget w, DReqData *data);
static void button_cancel(Widget w, DReqData *data);


int del_prim(BOOLEAN_T delete_flag, int *index, MyProgram *data)
{
  DReqData 	ddata;
  Widget 	w[9];
  int		i, j;
  char		type_string[TYPE_STRING_LEN+1];
  char		format_text[MAX_PRIMITIVES][MAX_LINE_LEN];

  /* clear out format text array */
  for (i = 0; i < MAX_PRIMITIVES; i++)
     for (j = 0; j < MAX_LINE_LEN; j++)
        format_text[i][j] = '\0';


  i = 0;
  j = 0; 

  /* format text data for each primitive in database */
  while (i < data->data.prim_count)
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


        sprintf(&format_text[j][0], 
		"%s  %3.3f %3.3f %3.3f   %3.3f %3.3f %3.3f   %c         %3.1f          %d %d %d", 
		type_string,
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

        format_text[j][MAX_LINE_LEN - 1] = '\0';

        del_item_list[j] = &format_text[j][0];

        j++;
     }
     i++;
  }

  del_item_list[data->data.prim_count] = NULL;

  if (delete_flag)
     ddata.dreq_window = MakeWindow("Delete Primitive", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);
  else
     ddata.dreq_window = MakeWindow("Select Primitive", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);


  w[0] = MakeLabel("Type    ");
  w[1] = MakeLabel("Center                ");
  w[2] = MakeLabel("Scaling             ");
  w[3] = MakeLabel("Axis ");
  w[4] = MakeLabel("Angle ");
  w[5] = MakeLabel("Color ");


  w[6] = MakeScrollList(del_item_list, DEL_LIST_WIDTH, DEL_LIST_HEIGHT, (void *)del_list_cb, &ddata);

  w[7] = MakeButton("   OK   ", (void *)button_ok, &ddata);
  w[8] = MakeButton(" Cancel ", (void *)button_cancel, &ddata);


  /* position all the little widgets */
  SetWidgetPos(w[1],  PLACE_RIGHT, w[0],  NO_CARE,     NULL);
  SetWidgetPos(w[2],  PLACE_RIGHT, w[1],  NO_CARE,     NULL);
  SetWidgetPos(w[3],  PLACE_RIGHT, w[2],  NO_CARE,     NULL);
  SetWidgetPos(w[4],  PLACE_RIGHT, w[3],  NO_CARE,     NULL);
  SetWidgetPos(w[5],  PLACE_RIGHT, w[4],  NO_CARE,     NULL);

  SetWidgetPos(w[6],  PLACE_UNDER, w[0],  NO_CARE,     NULL);

  SetWidgetPos(w[7],  PLACE_UNDER, w[6],  NO_CARE,     NULL);
  SetWidgetPos(w[8],  PLACE_RIGHT, w[7],  PLACE_UNDER, w[6]);

  /* save important widgets */
  ddata.type_list     = w[6];

  /* init highlight to first list item */
  SetCurrentListItem(ddata.type_list, 0);
  ddata.index = 0;


  ShowDisplay();

  GetStandardColors();

  SetFgColor(w[7], WHITE);
  SetBgColor(w[7], BLUE);
  SetFgColor(w[8], WHITE);
  SetBgColor(w[8], BLUE);

  MainLoop();

  SetCurrentWindow(ORIGINAL_WINDOW);

  /* check for cancel */
  if(ddata.cancelled)
    return(TRUE);

  /* return index of selected primitive */
  *index = ddata.index;

  return(FALSE);
}


/*    widget callbacks 
 */
void del_list_cb(Widget w, char *string, int index, DReqData *data)
{
  data->index = index;

  printf("picked index %d to delete\n", index);
}

void button_ok(Widget w, DReqData *data)
{
  data->cancelled = FALSE;
  SetCurrentWindow(data->dreq_window);
  CloseWindow();
}

void button_cancel(Widget w, DReqData *data)
{
  data->cancelled = TRUE;
  SetCurrentWindow(data->dreq_window);
  CloseWindow();
}

