/********************************************************************

   This file contains header information for LIBGFS, a GUI library 
   based upon SRGP.  Used for drawing GUI type gadgets on the screen 
   using the SRGP graphics library.

   Author:    Brian Lingard

   File:      gspublic.h
 
   Revision History:
     0.2  01/26/96  corrected bugs, cleaned up documentation
     0.1  04/04/95  split original code into separate files
     0.0  03/28/95  originated

*********************************************************************/

#ifndef GSPUBLIC_H
#define GSPUBLIC_H

#include "srgp.h"	/* should only be included here */


/***********************************************************

 Public definitions and typedefs

***********************************************************/

/*  generic null value
 */
#define GSNULL		((long int) -1)


/*  max number of vertices for polylines or polygons
 */
#define GS_MAX_VERTICES	((int) 20)


/*  boolean types
 */
typedef int GS_boolean;
#define GSFALSE		((GS_boolean) 0)
#define GSTRUE		((GS_boolean) 1)


/*  gadget types 
 */
typedef short int GS_gadgetType;

#define GSPUSHBUTTON 	((GS_gadgetType) 1)	/* push button gadget */
#define GSTOGBUTTON 	((GS_gadgetType) 2)	/* toggle button gadget */
#define GSMENUBAR   	((GS_gadgetType) 3)	/* menu bar gadget */
#define GSSUBMENU	((GS_gadgetType) 4)	/* pull down menu gadget */
#define GSDRAWAREA	((GS_gadgetType) 5)	/* draw area gadget */
#define GSTEXTGAD	((GS_gadgetType) 6)	/* text gadget */


/*  gadget types 
 */
typedef short int GS_toggleShape;
#define GSTOGSQUARE	((GS_toggleShape) 1)	/* toggle shape square */
#define GSTOGDIAMOND	((GS_toggleShape) 2)	/* toggle shape diamond */
#define GSTOGCIRCLE	((GS_toggleShape) 3)	/* toggle shape circle */


/*  gadget and draw area location types
 */
typedef short int GS_locType;

#define GSCENTERED	((GS_locType) 1)	/* default */
#define GSTOPLEFT	((GS_locType) 2)
#define GSBOTLEFT	((GS_locType) 3)
#define GSTOPRIGHT	((GS_locType) 4)
#define GSBOTRIGHT	((GS_locType) 5)


/*  event types
 */
typedef short int GS_eventType;

#define GSNOEVENT	((GS_eventType) 0)	/* no event */
#define GSKEYEVENT	((GS_eventType) 1)	/* keyboard event */
#define GSMOUSEVENT	((GS_eventType) 2)	/* mouse event */
#define GSTIMEOUT	((GS_eventType) 3)	/* time out event */


/*  color indexes used
 */
typedef short int GS_colorindexType;

#define GSWHITE		((GS_colorindexType) 0)	/* same as SRGP_WHITE */
#define GSBLACK		((GS_colorindexType) 1)	/* same as SRGP_BLACK */
#define GSRED		((GS_colorindexType) 2)
#define GSGREEN		((GS_colorindexType) 3)
#define GSBLUE		((GS_colorindexType) 4)
#define GSCYAN		((GS_colorindexType) 5)
#define GSMAGENTA	((GS_colorindexType) 6)
#define GSYELLOW	((GS_colorindexType) 7)
#define GSGREY		((GS_colorindexType) 8)

#define GS_CUSTOM_COLOR_START	((GS_colorindexType) 9)


/*  color structures
 */
typedef unsigned short ush;

#define GSMAXGREYLEVEL	((unsigned short int) 65535)

typedef struct {
   unsigned short int R;
   unsigned short int G;
   unsigned short int B;
} GS_rgbType;

typedef struct {
   float IR;
   float IG;
   float IB;
} GS_colorType;


/*  error codes for drawing functions
 */
typedef short int GS_errorType;

#define GSNOERROR	((GS_errorType) 0)
#define GSNOTINAREA	((GS_errorType) 1)
#define GSGADGETERR	((GS_errorType) 2)
#define GSNOTBUTTONERR	((GS_errorType) 3)
#define GSNOTMENUBARERR ((GS_errorType) 4)
#define GSNOTSUBMENUERR ((GS_errorType) 5)
#define GSNOTDRAWAREA	((GS_errorType) 6)


/*  define gadget and window id types
 */
typedef short int GS_gadgetID;
typedef short int GS_windowID;


/*  button structure
 */
typedef struct {
   char 	*label;
   point	label_pos;
} GSbutton;


/*  toggle button structure
 */
typedef struct {
   char 	*label;
   point	label_pos;
   GS_boolean	state;			/* toggle button state */
   short int	shape;			/* toggle shape type */
   rectangle	square;
   point	diamond[4];
   point	center;
   int		radius;
} GStogbutton;


/*  menu bar structure
 */
#define GS_MAX_ITEM_COUNT	10
typedef struct {
   short int	item_count;
   char		*item_list;		/* list of menu item names */
   point	*item_pos;		/* list of text positions */
   rectangle	*item_rect;		/* list of bounding rectangles */
   GS_gadgetID	*submenu_ids;		/* list of sub menu gadget IDs */
} GSmenubar;


/*  sub menu structure
 */
typedef struct {
   short int	item_count;
   char		*item_list;		/* list of sub menu item names */
   point	*item_pos;		/* list of text positions */
   rectangle	*item_rect;		/* list of bounding rectangles */    	
} GSsubmenu;


/*  text gadget structure
 */
typedef struct {
   short int	num_chars;		/* number of chars in string */
   char		*string; 		/* pointer to text string buffer */
} GStextgad;


/*  gadget structure 
 */
typedef struct {
   GS_gadgetID	gadget_id;
   short int	gadget_type;
   long  int	gadget_width;
   long  int	gadget_height;
   long  int 	gadget_xloc;
   long  int	gadget_yloc;
   short int	gadget_loc_type;
   short int	gadget_bor_color;	/* border color - default GSWHITE */
   short int	gadget_bgd_color;	/* background color - default GSBLACK */
   short int	gadget_fgd_color;	/* foreground color - default GSWHITE */
   short int	gadget_high_color;	/* highlight color - default GSWHITE */
   rectangle	gadget_extent;		/* bounding rectangle of gadget */
   point	gadget_center;		/* center point of gadget */
   GSbutton	*button;		/* pointer to button structure */
   GStogbutton	*togbutton;		/* pointer to toggle button structure */
   GSmenubar	*menubar;		/* pointer to menu bar structure */
   GSsubmenu	*submenu;		/* pointer to sub menu structure */
   GStextgad	*textgad;		/* pointer to test gadget structure */
} GSgadgetStruct;


/*  event structure
 *
 *	which button - LEFT_BUTTON, MIDDLE_BUTTON, RIGHT_BUTTON
 *	button status - UP, DOWN
 */
typedef struct {
   short int 	event_type;
   int		event_button;		/* which mouse button */
   int		event_button_stat;	/* mouse button status, UP, DOWN */
   char 	event_char;
   GS_gadgetID	event_gadget_id;	/* equals -1 if not hit */
   GS_windowID	event_window_id;	/* always equals 0 */
   short int	event_menu_item;	/* index of menu item hit */
   point	event_loc;		/* current mouse x,y location */
 } GSeventStruct;


/*  window structure
 */
typedef struct {
   GS_windowID	window_id;		/* currently only 1 window allowed */
   char 	*window_name;
   long  int	window_width;
   long  int	window_height;
   short int	window_num_planes;
   short int	window_planes_avail;
   short int	window_bgd_color;	/* background color - default GSBLACK */
   short int	window_fgd_color;	/* foreground color - default GSWHITE */
   GSeventStruct *window_event;		/* event structure for this window */
} GSwindowStruct;



/*  extern all public functions
 */
GS_gadgetID GS_MakePushButton(char *label,
			long int width,
			long int height,
			long int xloc,
			long int yloc,
			short int loc_type,
			short int bor_color,
			short int bgd_color,
			short int text_color);

GS_gadgetID GS_MakeToggleButton(char *label,
			long int width,
			long int height,
			long int xloc,
			long int yloc,
			short int loc_type,
			short int bor_color,
			short int bgd_color,
			short int text_color,
			short int toggle_shape);

GS_gadgetID GS_MakeMenuBar(short int item_count,
			char *item_list,
			GS_gadgetID *submenu_list,
			long int width,
			long int height,
			long int xloc,
			long int yloc,
			short int loc_type,
			short int bor_color,
			short int bgd_color,
			short int text_color);

GS_gadgetID GS_MakeSubMenu( );

GS_gadgetID GS_MakeDrawArea( long int width,
			long int height,
			long int xloc,
			long int yloc,
			short int loc_type,
			short int bor_color,
			short int bgd_color,
			short int fgd_color);

GS_gadgetID GS_MakeTextGadget( );

GS_windowID GS_MakeWindow( char *name,
			long int width,
			long int height,
			short int num_planes,
			short int bgd_color,
			short int fgd_color);

GS_errorType GS_InitWindow(GS_windowID w);

GS_errorType GS_CloseWindow(GS_windowID w);

GS_eventType GS_WaitForEvent();

char         GS_InquireEventChar();

GS_gadgetID  GS_InquireEventGadgetID();

point        GS_InquireEventLocation();

int          GS_InquireEventWhichButton();

int          GS_InquireEventButtonStat();

short int    GS_InquireEventMenuItem();

GS_errorType GS_AddNewColor(GS_colorindexType index, GS_rgbType color);

GS_errorType GS_SetDrawingColor(GS_gadgetID g, GS_colorindexType index);

GS_errorType GS_ClearDrawArea(GS_gadgetID g);

point        GS_DefPoint(int x, int y);

GS_errorType GS_DrawPoint(GS_gadgetID g, point pt);

GS_errorType GS_DrawLine(GS_gadgetID g, point start, point end);

GS_errorType GS_DrawPolyline(GS_gadgetID g, int vert_count, point *vertices);

GS_errorType GS_DrawPolygon(GS_gadgetID g, int vert_count, point *vertices);

GS_errorType GS_DrawRectangle(GS_gadgetID g, rectangle rect);

GS_errorType GS_InquireGadgetExtent(GS_gadgetID g, rectangle *rect);

GS_errorType GS_SetToggleState(GS_gadgetID g, GS_boolean state);

GS_boolean   GS_GetToggleState(GS_gadgetID g);



#endif 	/* GSPUBLIC_H */

/* end of file gspublic.h */
