/* This file contains all the header definitions for working with this
 * library of functions that make X stuff a lot easier to swallow.
 *
 *              --  This code under the GNU copyleft --
 * 
 *   Dominic Giampaolo
 */

#ifndef _DISPLAY_H_    /* prevent accidental re-inclusions */
#define _DISPLAY_H_  

#include <X11/Intrinsic.h>


/* these should be typedef's, but on sun's they are already defined in 
 * <sys/types.h>, but I'm sure I can't guarantee that on other systems.
 */
#define ushort unsigned short int
#define ulong  unsigned long  int
#define uchar  unsigned char



/* define's for button/gadget placement, used to call SetWidgetPos() */
#define NO_CARE       0x00 /* don't care where the gadget is placed */
#define PLACE_RIGHT   0x01 /* place me to the right of specified gadget */
#define PLACE_UNDER   0x02 /* place me under the specified gadget */




/* protos for the interface functions */
int    OpenDisplay(int argc, char **argv);
void   ShowDisplay(void);
void   SyncDisplay(void);

void   MainLoop(void);
Widget MakeHorizScrollbar(float where, float max, float size_shown,
			  int length, void (*scroll_func), void *data);
Widget MakeVertScrollbar(float where, float max, float size_shown,
			 int height, void (*scroll_func), void *data);
Widget MakeButton(char *label, void (*function)(), void *data); 
Widget MakeDrawArea(int width, int height, void *data);
Widget MakeLabel(char *txt);

/* position setting function */
void SetWidgetPos(Widget w, int where1, Widget from1, int where2,Widget from2);

/* miscellaneous */
void  SetScrollbar(Widget w, float where, float max, float size_shown);
int   SetWidgetFont(Widget w, char *fontname);
int   SetDrawAreaFont(char *fontname);
void  SetFgColor(Widget w, int color);
void  SetBgColor(Widget w, int color);
void  SetBorderColor(Widget w, int color);
void  GetWinSize(int *w, int *h);
int   GetFgColor(Widget w);
int   GetBgColor(Widget w);
void  UpdateLabel(Widget w, char *txt);


/* User-input functions 
 */
char *GetString(char *blurb, char *default_string);
int   GetYesNo(char *question);

char *TranslateKeyCode(XEvent *ev);


/* protos for the drawing functions */
void SetDrawArea(Widget w);

void ClearDisplay(void);
void SetColor(int color);

void DrawPoint(int x1, int y1);
void DrawLine(int x1, int y1, int x2, int y2);
void DrawPolyline(XPoint *points, int n);
void DrawFilledPolygon (XPoint *points, int n);
void DrawFilledBox(int x, int y, int width, int height);
void DrawBox(int x, int y, int width, int height);
void DrawText(char *string, int x, int y, int bcolor);
void DrawArc(int x, int y, int width, int height, int angle1, int angle2);
void DrawFilledArc(int x, int y, int width, int height, 
		   int angle1, int angle2);
void DrawImage(char *data, int width, int height, int x, int y);


#endif /* _DISPLAY_H_ */
