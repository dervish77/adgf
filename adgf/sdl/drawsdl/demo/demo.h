/*****************************************************************************
 *
 *	DrawSdl main program.  Demo routines.
 *
 *  Description:
 *  Demo program for drawing with LibSDL.
 *
 *	File:	demo.h
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/

#ifndef __demo_h
#define __demo_h

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
#define DEMO_KEYS       8
#define DEMO_MOUSE      9
#define DEMO_ANIM       10
#define DEMO_TEXT       11
#define DEMO_POLYGONS   12
#define DEMO_SPRITES    13
#define DEMO_SPRITECP   50
#define DEMO_FULL       99

//////////////////////////////////////////////////////////////////////////////
// prototypes
//////////////////////////////////////////////////////////////////////////////

void DemoPixels();
void DemoLines();
void DemoBoxes();
void DemoTriangles();
void DemoCircles();
void DemoBitmaps();
void DemoBlitters();
void DemoKeys();
void DemoMouse();
void DemoAnim();
void DemoText();
void DemoPolygons();
void DemoSprites();
void DemoSpriteCopy();
void DemoFull();

#endif /* __demo_h */

