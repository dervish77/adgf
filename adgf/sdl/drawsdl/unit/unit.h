/*****************************************************************************
 *
 *	DrawSdl unit test main program.  Test routines.
 *
 *  Description:
 *  Unit test program for drawing with LibSDL.
 *
 *	File:	unit.h
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/

#ifndef __unit_h
#define __unit_h

//////////////////////////////////////////////////////////////////////////////
// defines
//////////////////////////////////////////////////////////////////////////////

#define DEMO_EXIT       0
#define DEMO_PIXELS     1
#define DEMO_LINES      2
#define DEMO_BOXES      3
#define DEMO_TRIANGLES  4
#define DEMO_CIRCLES    5
#define DEMO_BITMAPS    6
#define DEMO_BLITTERS   7
#define DEMO_TEXT       11
#define DEMO_POLYGONS   12
#define DEMO_SPRITES    13
#define DEMO_FULL       99

//////////////////////////////////////////////////////////////////////////////
// prototypes
//////////////////////////////////////////////////////////////////////////////

void DoUnitTest();

void DemoPixels();
void DemoLines();
void DemoBoxes();
void DemoTriangles();
void DemoCircles();
void DemoBitmaps();
void DemoBlitters();
void DemoText();
void DemoPolygons();
void DemoSprites();
void DemoFull();

#endif /* __unit_h */

