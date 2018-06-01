/***********************************************************************

 Drawing functions which directly call LIBSX routines.

   File:  	drawing.c

   Author: 	Brian Lingard

   Date:	02/08/96

   Revisions:
	0.2	02/12/96  Reduced database to two levels (removed frames)
	0.0	02/08/96  Originated

***********************************************************************/

/*  include necessary files 
 */
#ifndef _DRAWING_H
#include "drawing.h"
#endif



/* 
 * DrawHeader() 
 *	- draws header label within main drawing area
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 */
void
DrawHeader(MyProgram *data)
{
   pointType	label_pos;

   int		width, height;
   XFont	font;


   font = GetWidgetFont( data->draw_area_widget );
   height = FontHeight( font );

   label_pos.x = DEFAULT_PROJ_LABEL_X;
   label_pos.y = DEFAULT_PROJ_LABEL_y;
   DrawText("Project:", label_pos.x, InvertY(label_pos.y));

   width = TextWidth( font, "Project:" );
   label_pos.x += (width + DEFAULT_LABEL_SPACING1);
   DrawText(data->proj.projname_str, label_pos.x, InvertY(label_pos.y));

   width = TextWidth( font, data->proj.projname_str );
   label_pos.x += (width + DEFAULT_LABEL_SPACING2);
   DrawText("Act:", label_pos.x, InvertY(label_pos.y));

   width = TextWidth( font, "Act:" );
   label_pos.x += (width + DEFAULT_LABEL_SPACING1);
   DrawText("1", label_pos.x, InvertY(label_pos.y));

   width = TextWidth( font, "1" );
   label_pos.x += (width + DEFAULT_LABEL_SPACING2);
   DrawText("Scene:", label_pos.x, InvertY(label_pos.y));

   width = TextWidth( font, "Scene:" );
   label_pos.x += (width + DEFAULT_LABEL_SPACING1);
   DrawText("1", label_pos.x, InvertY(label_pos.y));

}


/* 
 * DrawSceneOutline() 
 *	- draws scene outline within main drawing area
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 */
void
DrawSceneOutline(MyProgram *data)
{
   XPoint	points[5];

   points[0].x = DEFAULT_SCENE_BOT_LEFT_X;
   points[0].y = InvertY(DEFAULT_SCENE_BOT_LEFT_Y);

   points[1].x = DEFAULT_SCENE_BOT_LEFT_X;
   points[1].y = InvertY(DEFAULT_SCENE_TOP_RIGHT_Y);

   points[2].x = DEFAULT_SCENE_TOP_RIGHT_X;
   points[2].y = InvertY(DEFAULT_SCENE_TOP_RIGHT_Y);

   points[3].x = DEFAULT_SCENE_TOP_RIGHT_X;
   points[3].y = InvertY(DEFAULT_SCENE_BOT_LEFT_Y);

   points[4].x = DEFAULT_SCENE_BOT_LEFT_X;
   points[4].y = InvertY(DEFAULT_SCENE_BOT_LEFT_Y);

   DrawPolyline( &points[0], 5 );
}


/* 
 * DrawSceneTextArea() 
 *	- updates scene text area within main drawing area
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 */
void
DrawSceneTextArea(MyProgram *data)
{
   pointType	left_pt, right_pt;

   int		height;
   XFont	font;

   int 		vert_spacing, text_offset;


   font = GetWidgetFont( data->draw_area_widget );
   height = FontHeight( font );

   vert_spacing = 2 * DEFAULT_SCENE_TEXT_SPACING;

   text_offset = DEFAULT_SCENE_TEXT_SPACING;

   left_pt.x = DEFAULT_SCENE_BOT_LEFT_X;
   left_pt.y = height + DEFAULT_SCENE_BOT_LEFT_Y + vert_spacing;

   right_pt.x = DEFAULT_SCENE_TOP_RIGHT_X;
   right_pt.y = left_pt.y;

   DrawLine( left_pt.x, InvertY(left_pt.y), right_pt.x, InvertY(right_pt.y) );
   DrawText( "Sound:", (left_pt.x+text_offset), 
		InvertY((left_pt.y-text_offset-height)) );

   left_pt.y += (height + vert_spacing);
   right_pt.y = left_pt.y;

   DrawLine( left_pt.x, InvertY(left_pt.y), right_pt.x, InvertY(right_pt.y) );
   DrawText( "Dialog:", (left_pt.x+text_offset), 
		InvertY((left_pt.y-text_offset-height)) );

   left_pt.y += (height + vert_spacing);
   right_pt.y = left_pt.y;

   DrawLine( left_pt.x, InvertY(left_pt.y), right_pt.x, InvertY(right_pt.y) );
   DrawText( "Action:", (left_pt.x+text_offset), 
		InvertY((left_pt.y-text_offset-height)) );

}


/* 
 * DrawSceneBitmap() 
 *	- updates scene bitmap within main drawing area
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 */
void
DrawSceneBitmap(MyProgram *data)
{



}


/* 
 * DrawScene() 
 *	- updates scene data within main drawing area
 *
 * PARAMETERS
 *	data	- pointer to MyProgram structure
 *
 * RETURNS
 *	nothing
 */
void
DrawScene(MyProgram *data)
{
   DrawSceneOutline(data);

   DrawSceneTextArea(data);

   DrawSceneBitmap(data);
}


/* end of drawing.c */
