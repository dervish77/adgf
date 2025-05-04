/*****************************************************************************
 *
 *	DrawSdl main program.  Demo routines.
 *
 *  Description:
 *  Demo program for drawing with LibSDL.
 *
 *	File:	demo.cpp
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

#include "demo.h"
#include "main.h"



/*
 *  STATICS
 */



/*
 *  FUNCTIONS
 */

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

    // call this to wait for user to 'X' out
    drawWaitQuit();
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

    // call this to wait for user to 'X' out
    drawWaitQuit();
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

    // call this to wait for user to 'X' out
    drawWaitQuit();
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

    // call this to wait for user to 'X' out
    drawWaitQuit();
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

    // call this to wait for user to 'X' out
    drawWaitQuit();
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

    // call this to wait for user to 'X' out
    drawWaitQuit();
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

    // call this to wait for user to 'X' out
    drawWaitQuit();
}

void DemoKeys()
{
    int w, h;    // screen width and height

    // show key menu before opening drawing screen
    printf("Key commands:\n");
    printf(" l  - draw line in current color\n");
    printf(" r  - set color to red\n");
    printf(" g  - set color to green\n");
    printf(" b  - set color to blue\n");
    printf(" w  - set color to white\n");
    printf(" x  - clear screen\n");
    printf(" q  - quit\n");
    printf("\n");
    drawWait(2000);

    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);

    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // use keys to draw a line in a selected color
    int done = 0;
    long color = CLR_WHITE;
    char key;
    int x, y;
    while (!done)
    {
        switch( drawGetEvent(&x, &y, &key) )
        {
            case KEY_DOWN:
                switch(key)
                {
                    case 'l':
                        drawLine( color, 0,0,  w,h );
                        drawSwapBuffers();
                        break;
                    case 'r':
                        color = CLR_RED;
                        break;
                    case 'g':
                        color = CLR_GREEN;
                        break;
                    case 'b':
                        color = CLR_BLUE;
                        break;
                    case 'w':
                        color = CLR_WHITE;
                        break;
                    case 'x':
                        drawBackground(CLR_BLACK);
                        drawSwapBuffers();
                        break;
                    case 'q':
                        done = 1;
                        break;
                }
                break;
            case WINDOW_QUIT:
                done = 1;
                break;
        }
    }

    // END DEMO HERE //

    drawQuit();
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

void DemoMouse()
{
    int w, h;    // screen width and height

    // show key menu before opening drawing screen
    printf("Key commands:\n");
    printf(" p  - pixel mode\n");
    printf(" r  - rectangle mode\n");
    printf(" c  - circle mode\n");
    printf(" x  - clear screen\n");
    printf(" q  - quit\n");
    printf("\n");
    drawWait(1000);

    // initialize the drawing package
    drawInitExtended(WIDTH, HEIGHT, BPP, "DrawSDL - Mouse");

    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // draw white dots while left mouse button is pressed
    int done = 0;
    int drawing = 0;
    char key;
    int x, y;
    int mode = 1;
    while (!done)
    {
        switch( drawGetEvent( &x, &y, &key ) )
        {
            case KEY_DOWN:
                switch(key)
                {
                    case 'p':
                        mode = 1;
                        break;
                    case 'r':
                        mode = 2;
                        break;
                    case 'c':
                        mode = 3;
                        break;
                    case 'q':
                        done = 1;
                        break;
                    case 'x':
                        drawBackground(CLR_BLACK);
                        drawSwapBuffers();
                        break;
                }
                break;
            case MOUSE_MOTION:
                if (drawing)
                {
                    DrawByMode( mode, x, y );
                }
                break;
            case MOUSE_LEFT_DOWN:
                drawing = 1;
                if (drawing)
                {
                    DrawByMode( mode, x, y );
                }
                break;
            case MOUSE_LEFT_UP:
                drawing = 0;
                break;
            case MOUSE_RIGHT_DOWN:
                done = 1;
                break;
            case WINDOW_QUIT:
                done = 1;
                break;
        }
    }

    // END DEMO HERE //

    drawQuit();
}

void DemoAnim()
{
    int w, h;    // screen width and height

    // show key menu before opening drawing screen
    printf("Key commands:\n");
    printf(" e  - toggle erase\n");
    printf(" r  - reset and run anim again\n");
    printf(" x  - clear screen\n");
    printf(" q  - quit\n");
    printf("\n");
    drawWait(1000);

    // initialize the drawing package
    drawInitExtended(WIDTH, HEIGHT, BPP, "DrawSDL - Anim");

    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    char key;
    int mx, my;
    int x = 50, y = 3 * (h/4);      // starting position

    // draw reference line
    drawLine( CLR_WHITE, 50, y+51, w-50, y+51);

    // draw first rectangle
    drawSolidRect( CLR_WHITE, x, y, 50, 50);
    drawSwapBuffers();

    // set up anim timer for 30 frames per second
    int interval = 33;              // milliseconds per frame
    TIMERID animTimerId = drawAddTimer( interval, TIMER1_EVENT );

    int erase = 1;
    int drawing = 1;
    int done = 0;
    while (!done)
    {
        switch( drawGetEvent( &mx, &my, &key ) )
        {
            case TIMER1_EVENT:
                // draw next frame
                if (drawing)
                {
                    // erase original rectangle
                    if (erase)
                    {
                        drawSolidRect( CLR_BLACK, x, y, 50, 50 );
                    }
                    // move rectangle
                    x += 20;
                    if (x < (w/2 - 12))
                        y -= 12;
                    else
                        y += 12;
                    // draw moved rectangle
                    drawSolidRect( CLR_WHITE, x, y, 50, 50 );
                    // update screen
                    drawSwapBuffers();
                }
                // have we reach the right hand limit?
                if (x > (w-100))
                {
                    drawing = 0;
                }
                break;
            case KEY_DOWN:
                switch(key)
                {
                    case 'e':  // toggle erase
                        if (erase)
                            erase = 0;
                        else
                            erase = 1;
                        break;
                    case 'r':  // reset and run anim again
                        x = 50;
                        y = 3 * (h/4);
                        drawBackground(CLR_BLACK);
                        drawLine( CLR_WHITE, 50, y+51, w-50, y+51);
                        drawSolidRect( CLR_WHITE, x, y, 50, 50);
                        drawSwapBuffers();
                        drawing = 1;
                        break;
                    case 'x':  // clear screen
                        drawBackground(CLR_BLACK);
                        drawSwapBuffers();
                        break;
                    case 'q':  // quit
                        done = 1;
                        break;
                }
                break;
            case WINDOW_QUIT:
                done = 1;
                break;
        }
    }

    // END DEMO HERE //

    // remove anim timer and quit drawing package
    drawRemoveTimer( animTimerId );
    drawQuit();
}

void DemoText()
{
    int y;       // position of text
    int w, h;    // screen width and height
    int tw, th;  // bitmap width and height

    int fontsize = 12;

    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    drawTextInit("fonts/times.ttf");

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
    drawWaitQuit();
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

    // call this to wait for user to 'X' out
    drawWaitQuit();
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

    // call this to wait for user to 'X' out
    drawWaitQuit();
}

void DemoSpriteCopy()
{
    int x, y;
    int w, h;    // screen width and height
    int sw, sh;  // width and height of sprite


    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);

    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    // load sprite image
    spriteContext oldSprite;
    drawLoadSprite(&oldSprite, "images/ship.bmp");
    drawGetSpriteExtent(&oldSprite, &sw, &sh);

    // copy pixel data from old to new sprite
    spriteContext newSprite;
    drawCreateSprite(&newSprite, sw, sh);
    long color;
    for (y = 0; y < sh; y++)
    {
        for (x = 0; x < sw; x++)
        {
            color = drawReadPixel( drawGetSpriteScreen(&oldSprite), x, y );
            drawWritePixel( drawGetSpriteScreen(&newSprite), color, x, y );
        }
    }

    // draw both sprites with outlines
    drawSprite(&oldSprite, w/2 - sw/2 - 100, h/2);
    drawSprite(&newSprite, w/2 + 100, h/2);

    drawRect( CLR_WHITE, w/2 - sw/2 - 100, h/2, sw, sh );
    drawRect( CLR_WHITE, w/2 + 100, h/2, sw, sh );

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();

    // call this to wait for user to 'X' out
    drawWaitQuit();
}

void DemoFull()
{
    int w, h;    // screen width and height
    int bw, bh;  // bitmap width and height

    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    drawTextInit("fonts/ARIAL1.TTF");

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
    drawTextSetFont("fonts/cour.ttf");
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
    drawWaitQuit();
}

/* end of demo.cpp */
