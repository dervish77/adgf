/***********************************************************************

 Drawing functions which directly call LIBSX routines.

   File:  	drawing.h

   Author: 	Brian Lingard

   Date:	02/09/96

   Revisions:
	0.2	02/12/96  Reduced database to two levels (removed frames)
	0.0	02/09/96  Originated

***********************************************************************/

#ifndef _DRAWING_H
#define _DRAWING_H


/*  include necessary files 
 */
#include <stdio.h>

#include "libsx.h"

#ifndef _MAIN_H
#include "main.h"
#endif

#ifndef _CALLBACK_H
#include "callback.h"
#endif



/*  declare default label positions
 */
#define DEFAULT_LABEL_SPACING1	10
#define DEFAULT_LABEL_SPACING2	30

#define DEFAULT_PROJ_LABEL_X	10
#define DEFAULT_PROJ_LABEL_y	(SCREEN_Y_SIZE - 20)


/*  declare scene position and sizes
 */
#define DEFAULT_SCENE_BOTTOM_OFFSET	10
#define DEFAULT_SCENE_TOP_OFFSET	30
#define DEFAULT_SCENE_LEFT_OFFSET	10
#define DEFAULT_SCENE_RIGHT_OFFSET	10

#define DEFAULT_SCENE_BOT_LEFT_X	DEFAULT_SCENE_LEFT_OFFSET
#define DEFAULT_SCENE_BOT_LEFT_Y	DEFAULT_SCENE_BOTTOM_OFFSET

#define DEFAULT_SCENE_TOP_RIGHT_X	(MAX_SCENE_X_SIZE - DEFAULT_SCENE_RIGHT_OFFSET)
#define DEFAULT_SCENE_TOP_RIGHT_Y	(MAX_SCENE_Y_SIZE - DEFAULT_SCENE_TOP_OFFSET)

#define DEFAULT_SCENE_TEXT_SPACING	5


#endif	/* _DRAWING_H */

/* end of drawing.h */

