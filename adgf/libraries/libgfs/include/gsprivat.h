/********************************************************************

   Private header information in support of LIBGFS, a GUI library 
   based upon SRGP.

   Author:    Brian Lingard

   File:      gsprivat.h
 
   Revision History:
     0.2  01/26/96  corrected bugs, cleaned up documentation
     0.1  04/04/95  split original code into separate files
     0.0  03/28/95  originated

*********************************************************************/

#ifndef GSPRIVAT_H
#define GSPRIVAT_H


#ifndef GSPUBLIC_H
#include "gspublic.h"
#endif



#ifdef GS_DEBUG
   extern FILE *gs_debug_file;
#endif


/***********************************************************

 Private definitions and typedefs -- DO NOT EDIT

***********************************************************/

/*  max counts of gadgets and windows
 */
#define GS_MAX_GADGETS 		((short int) 20)
#define GS_MAX_WINDOWS		((short int) 1)


/*  default number of planes
 */
#define GS_DEFAULT_PLANES	((short int) 8)


/*  default foreground and background colors
 */
#define GS_DEF_BGD_COLOR	GSBLACK
#define GS_DEF_FGD_COLOR	GSWHITE


/*  default buffer size
 */
#define GS_BUFLEN		80


/*  result flags for point in box test
 */
#define GS_NOTINBOX		((short int) 0)
#define GS_INBOX		((short int) 1)


/*  define error message type
 */
#define GS_ERROR_MSG_LEN 30	
typedef char GS_errorMsgType[GS_ERROR_MSG_LEN];


/*  declare toggle state macro
 */
#define TOGGLE_STATE(s)		(((s) == 0) ? (1) : (0))


/*  extern private global variables 
 */
extern GS_gadgetID current_gadget_count;
extern GS_windowID current_window_count;

extern GSgadgetStruct *known_gadgets[];
extern GSwindowStruct *known_windows[];

extern GS_errorMsgType error_strings[];


/*  extern all private functions 
 */
extern GS_gadgetID  CorrelatePick(point pt);
extern short int CorrelateMenuItem(GS_gadgetID gid, point pt);

extern GS_errorType ComputeGadgetExtent(GSgadgetStruct *b);
extern GS_errorType ComputeGadgetCenter(GSgadgetStruct *b);
extern GS_errorType ComputeMaxTextWHD(short int count, char *item_list, 
					int *mxtw, int *mxth, int *mxtd);
extern GS_errorType DrawPushButton(GSgadgetStruct *bg);
extern GS_errorType DrawToggleButton(GSgadgetStruct *bg);
extern GS_errorType DrawMenuBar(GSgadgetStruct *mb);
extern GS_errorType DrawSubMenu(GSgadgetStruct *sm);
extern GS_errorType DrawDrawingArea(GSgadgetStruct *area);
extern GS_errorType DrawTextGadget(GSgadgetStruct *tg);

extern GS_errorType ToggleButtonState(GSgadgetStruct *tb);
extern short int    PointInBox(point p, rectangle r);
extern GS_errorType ExtractItemLabel(int which, char *item_list, 
						char *item_label);
extern GS_errorType InitColorTable();
extern GS_errorType OutputGadget(FILE *file, GSgadgetStruct *g);
extern GS_errorType FreeGadgets();
extern GS_errorType FreeWindows();

extern GS_errorType OutputErrorMsg(GS_errorType type);

extern int          ParseString(char *string, char *args[]);


#endif	/* GSPRIVAT_H */

/* end of file gsprivat.h */
