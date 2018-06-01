/*****************************************************************************
 *
 *	DrawSdl unit test main program.  Test routines.
 *
 *  Description:
 *  Unit test program for drawing with LibSDL.
 *
 *	File:	unit.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/04/2009
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw-sdl.h"
#include "draw-text.h"

#include "unit.h"
#include "main.h"



/*
 *  STATICS
 */



/*
 *  FUNCTIONS
 */

void DoUnitTest()
{
    DemoPixels();
    DemoLines();
    DemoBoxes();
    DemoTriangles();
    DemoCircles();
    DemoBitmaps();
    DemoBlitters();
    DemoText();
    DemoPolygons();
    DemoSprites();
    DemoFull();
}


void DemoPixels()
{
    int i;
    int w, h;    // screen width and height   
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // draw sets of white dots across middle of screen
    for (i = 50; i < w-50; i+=50)
    {
        drawPixel( CLR_WHITE, i, h/2 );
        drawPixel( CLR_WHITE, i, h/2 + 5 );
        drawPixel( CLR_WHITE, i, h/2 + 10);
        drawPixel( CLR_WHITE, i, h/2 + 15);
    }

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    drawWait(500);
}

void DemoLines()
{
    int w, h;    // screen width and height   
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // draw several lines in different colors
    drawLine( CLR_WHITE,   50, (h/2)-60,     w-50, (h/2)-60 );
    drawLine( CLR_RED,     50, (h/2)-40,     w-50, (h/2)-40 );    
    drawLine( CLR_GREEN,   50, (h/2)-20,     w-50, (h/2)-20 );    
    drawLine( CLR_BLUE,    50, (h/2),        w-50, (h/2) );    
    drawLine( CLR_MAGENTA, 50, (h/2)+20,     w-50, (h/2)+20 );    
    drawLine( CLR_YELLOW,  50, (h/2)+40,     w-50, (h/2)+40 );    
    drawLine( CLR_CYAN,    50, (h/2)+60,     w-50, (h/2)+60 );    

    drawDashedLine( CLR_WHITE,   50, 50,       w-50, 50 );
    drawDashedLine( CLR_WHITE,   50, 50,       w-50, 150 );
    drawDashedLine( CLR_WHITE,   50, 50,       w-50, 250 );
    
    drawDottedLine( CLR_WHITE,   50, h-50,       w-50, h-50 );
    drawDottedLine( CLR_WHITE,   50, h-50,       w-50, h-150 );
    drawDottedLine( CLR_WHITE,   50, h-50,       w-50, h-250 );

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    drawWait(500);
}

void DemoBoxes()
{
    int w, h;    // screen width and height   
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // draw several open and solid boxes across middle of screen
    drawRect(       CLR_WHITE,   100, h/2 - 70, 50, 50 );
    drawSolidRect(  CLR_WHITE,   100, h/2 + 70, 50, 50 );

    drawRect(       CLR_MAGENTA, 200, h/2 - 70, 50, 50 );
    drawSolidRect(  CLR_MAGENTA, 200, h/2 + 70, 50, 50 );

    drawRect(       CLR_YELLOW,  300, h/2 - 70, 50, 50 );
    drawSolidRect(  CLR_YELLOW,  300, h/2 + 70, 50, 50 );

    drawRect(       CLR_CYAN,    400, h/2 - 70, 50, 50 );
    drawSolidRect(  CLR_CYAN,    400, h/2 + 70, 50, 50 );

    drawRect(       CLR_RED,     500, h/2 - 70, 50, 50 );
    drawSolidRect(  CLR_RED,     500, h/2 + 70, 50, 50 );

    drawRect(       CLR_GREEN,   600, h/2 - 70, 50, 50 );
    drawSolidRect(  CLR_GREEN,   600, h/2 + 70, 50, 50 );

    drawRect(       CLR_BLUE,    700, h/2 - 70, 50, 50 );
    drawSolidRect(  CLR_BLUE,    700, h/2 + 70, 50, 50 );

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
    
    drawWait(500);
}

void DemoTriangles()
{
    int w, h;    // screen width and height   
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // draw two triangles that abutt each other
    drawTriangle( CLR_WHITE,   50, h/2,   w-50, h/2,   w/2, 50 );
    drawTriangle( CLR_WHITE,   50, h/2,   w-50, h/2,   w/2, h-50 );

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    drawWait(500);
}

void DemoCircles()
{
    int w, h;    // screen width and height   
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // draw several open circles across middle of screen
    drawCircle( CLR_WHITE,   100, h/2 - 70, 40 );
    drawCircle( CLR_MAGENTA, 200, h/2 - 70, 40 );
    drawCircle( CLR_YELLOW,  300, h/2 - 70, 40 );
    drawCircle( CLR_CYAN,    400, h/2 - 70, 40 );
    drawCircle( CLR_RED,     500, h/2 - 70, 40 );
    drawCircle( CLR_GREEN,   600, h/2 - 70, 40 );
    drawCircle( CLR_BLUE,    700, h/2 - 70, 40 );

    // draw several solid circles across middle of screen
    drawSolidCircle( CLR_WHITE,   100, h/2 + 70, 40 );
    drawSolidCircle( CLR_MAGENTA, 200, h/2 + 70, 40 );
    drawSolidCircle( CLR_YELLOW,  300, h/2 + 70, 40 );
    drawSolidCircle( CLR_CYAN,    400, h/2 + 70, 40 );
    drawSolidCircle( CLR_RED,     500, h/2 + 70, 40 );
    drawSolidCircle( CLR_GREEN,   600, h/2 + 70, 40 );
    drawSolidCircle( CLR_BLUE,    700, h/2 + 70, 40 );
    

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    drawWait(500);
}

void DemoBitmaps()
{
    int w, h;    // screen width and height   
    int bh;      // height of bitmap
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // draw two bitmps near top of screen
    bh = drawGetBitmapHeight("images/fun.bmp");
    drawBitmap("images/fun.bmp",     50,  50);
    bh = drawGetBitmapHeight("images/texture.bmp");
    drawBitmap("images/texture.bmp", w/2, 50);

    // draw two bitmaps near bottom of screen
    bh = drawGetBitmapHeight("images/odie.bmp");
    drawBitmap("images/odie.bmp",    50,  h/2);
    bh = drawGetBitmapHeight("images/ufo.bmp");
    drawBitmap("images/ufo.bmp",  w/2, h/2);

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    drawWait(500);
}

void DemoBlitters()
{
    int w, h;    // screen width and height   
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // define and then draw some blitters
    unsigned short myblit[200][200];
    unsigned short color = drawCreateColor16( 0x80, 0x80, 0x80 );
    drawFillBitBlitBuffer( &myblit[0][0], 200, 200, color );
    drawBitBlit(&myblit[0][0], w/2 - 100, 100, 200, 200);
    drawBitBlit(&myblit[0][0], w/2 - 100, h/2, 200, 200);

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    drawWait(500);
}


void DrawByMode(int mode, int x, int y)
{
    switch(mode)
    {
        case 1:
            drawPixel( CLR_WHITE, x, y );
            break;
        case 2:
            drawSolidRect( CLR_WHITE, x, y, 5, 5 );
            break;
        case 3:
            drawCircle( CLR_WHITE, x, y, 5 );
            break;
    }
    drawSwapBuffers();
}


void DemoText()
{
    int y;       // position of text
    int w, h;    // screen width and height   
    int tw, th;  // bitmap width and height

    int fontsize = 12;
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    drawTextInit("fonts/ARIAL.TTF");
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);
    
    // BEGIN DEMO HERE //

    drawTextGetExtent("This is some sample text.", fontsize, &tw, &th);
    printf("Text extent w,h = %d,%d\n", tw, th);

    drawTextSetSize(fontsize);
    drawTextSetColor(CLR_WHITE, CLR_GRAY_DARK);

    for (y = 50; y < (h-50); y = y+50)
    {
        drawText("This is some sample text.", y, y);
        fontsize++;
        drawTextSetSize(fontsize);
    }

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    // call this to wait for user to 'X' out
    drawTextQuit();
    drawWait(500);
}

void DemoPolygons()
{
    int w, h;    // screen width and height   
    screenPoint polygon[10];
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);
    
    // BEGIN DEMO HERE //

    polygon[0].x = w/2 - 200;
    polygon[0].y = 100;

    polygon[1].x = w/2 + 200;
    polygon[1].y = 100;

    polygon[2].x = w/2 + 400;
    polygon[2].y = h - 100;

    polygon[3].x = w/2 - 400;
    polygon[3].y = h - 100;

    drawPolygon( CLR_WHITE, &polygon[0], 4 );

    polygon[0].x = w/2 - 80;
    polygon[0].y = 300;

    polygon[1].x = w/2 + 80;
    polygon[1].y = 300;

    polygon[2].x = w/2 + 40;
    polygon[2].y = h - 300;

    polygon[3].x = w/2 - 40;
    polygon[3].y = h - 300;

    drawSolidPolygon( CLR_BLUE, &polygon[0], 4 );
    
//    drawSolidLine( CLR_YELLOW, w/2, 50, w/2, h-50);

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    drawWait(500);
}


void DemoSprites()
{
    int x, y;
    int w, h;    // screen width and height   
    int sw, sh;  // width and height of sprite

    spriteContext sprite;
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // load sprite image
    drawLoadSprite(&sprite, "images/ship.bmp");
    drawGetSpriteExtent(&sprite, &sw, &sh);

    // save sprite to new file
    drawSaveSprite(&sprite, "images/shipcopy.bmp");

    // fill screen with sprites
    for (y = sh; y < (h-sh); y += sh*2)
    {
        for (x = sw; x < (w-sw); x += sw*2)
        {
            drawSprite(&sprite, x, y);
        }
    }

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    drawWait(500);
}

void DemoFull()
{
    int w, h;    // screen width and height   
    int bw, bh;  // bitmap width and height
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    drawTextInit("fonts/ARIAL.TTF");
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);
    
    // BEGIN DEMO HERE //
    
    // draw large rextangle near top of screen
    drawRect( CLR_MAGENTA, 50, 50, w-100, 100 );

    // draw triangle inside large rectangle
    drawTriangle( CLR_WHITE, w/2 - 50, 140,   w/2 + 50, 140,   w/2, 60 );
    
    // draw one of each shape across middle of screen
    drawPixel( CLR_WHITE, 50, h/2 );
    drawPixel( CLR_WHITE, 50, h/2 + 5 );
    drawPixel( CLR_WHITE, 50, h/2 + 10);
    drawPixel( CLR_WHITE, 50, h/2 + 15);
    
    drawRect(       CLR_RED,             100, h/2, 50, 50 );
    drawSolidRect(  CLR_GREEN,           200, h/2, 50, 50 );
    drawShadedRect( CLR_RED,   CLR_BLUE, 300, h/2, 50, 50 );
   
    drawCircle( CLR_YELLOW, 450, h/2, 50 );
    drawCircle( CLR_YELLOW, 450, h/2, 40 );
    drawCircle( CLR_YELLOW, 450, h/2, 30 );
    drawCircle( CLR_YELLOW, 450, h/2, 20 );
    drawSolidCircle( CLR_YELLOW, 450, h/2, 10 );
    
    drawLine(       CLR_WHITE,  600, h/2,      w-50, h/2 );
    drawSolidLine(  CLR_BLUE,   600, (h/2)+20, w-50, (h/2)+20 );    
    drawDottedLine( CLR_YELLOW, 600, (h/2)-20, w-50, (h/2)-80 );    
    drawDashedLine( CLR_GREEN,  600, (h/2)-40, w-50, (h/2)-140 );    

    // draw some bitmaps near bottom of screen
    bw = drawGetBitmapWidth("images/fun.bmp");
    bh = drawGetBitmapHeight("images/fun.bmp");
    drawBitmap("images/fun.bmp",     50,      h-bh-50);
    bw = drawGetBitmapWidth("images/texture.bmp");
    bh = drawGetBitmapHeight("images/texture.bmp");
    drawBitmap("images/texture.bmp", w-bw-50, h-bh-50);
    
    // let's create our own bit blit buffer and display it
    unsigned short myblit[200][200];
    unsigned short color = drawCreateColor16( 0x80, 0x80, 0x80 );
    drawFillBitBlitBuffer( &myblit[0][0], 200, 200, color );
    drawBitBlit(&myblit[0][0], w/2 - 100, h-200-50, 200, 200);

    // let's add some text
    drawTextSetFont("fonts/COURIER.TTF");
    drawTextGetExtent("DrawSdl Full Demo", 16, &bw, &bh);
    drawText("DrawSdl Full Demo", 16, w/2 - bw/2, 200 - bh/2, CLR_WHITE, CLR_GRAY_DARK);

    // let's draw a sprite
    spriteContext sprite;    
    drawLoadSprite(&sprite, "images/ship.bmp");
    drawGetSpriteExtent(&sprite, &bw, &bh);
    drawSprite(&sprite, w/2 - bw/2, h/2 - bh/2 - 100);

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();

    printf("Pixel Count = %d\n", drawGetPixelCount() );
  
    // call this to wait for user to 'X' out
    drawTextQuit();
    drawWait(500);
}

/* end of unit.cpp */
