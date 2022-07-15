/*****************************************************************************
 *
 *	DrawSdl main program.
 *
 *  Description:
 *  Demo program for drawing with LibSDL.
 *
 *	File:	main.c
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
#include "version.h"


/*
 *  CONSTANTS
 */

#define WIDTH   WIDTH_1024
#define HEIGHT  HEIGHT_768
#define BPP     BPP_16


/*
 *  PROTOTYPES
 */

void PrintBanner();
int  DoMenu();

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
void DemoAnimBlit();
void DemoFull();


/*
 *  STATICS
 */



/*  main	- main program
 *
 *  Parameters:
 *	argc	- number of command line arguments
 *	argv	- pointer to command line argument array
 *
 *  Returns:
 *	none
 */
int main(int argc, char **argv)
{
    int choice;    
    
    // let's print a banner on the command line
    PrintBanner();
   
    // if no command line arguments
    if (argc == 1)
    { 
        // display menu of demos
        choice = DoMenu();
    }
    else
    {
        // otherwise, parse command line arguments
        choice = 0; // for now, just say "no choice"
    }
    
    // run the chosen demo
    switch(choice)
    {
        case 1:
            DemoPixels();
            break;
        case 2:
            DemoLines();
            break;
        case 3:
            DemoBoxes();
            break;
        case 4:
            DemoTriangles();
            break;
        case 5:
            DemoCircles();
            break;
        case 6:
            DemoBitmaps();
            break;
        case 7:
            DemoBlitters();
            break;
        case 8:
            DemoKeys();
            break;
        case 9:
            DemoMouse();
            break;
        case 10:
            DemoAnim();
            break;
        case 11:
            DemoAnimBlit();
            break;
        case 99:
            DemoFull();
            break;
        default:
            break;
    }
    
    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("    Welcome to DrawSdl %s - LibSDL drawing demo\n", VERSION);
    printf("******************************************************\n");
}

int DoMenu()
{
    char choice[8];
    
    printf("\n");
    printf("1.  Demo Pixels\n");
    printf("2.  Demo Lines\n");
    printf("3.  Demo Boxes\n");
    printf("4.  Demo Triangles\n");
    printf("5.  Demo Circles\n");
    printf("6.  Demo Bitmaps\n");
    printf("7.  Demo Blitters\n");
    printf("8.  Demo Keys\n");
    printf("9.  Demo Mouse\n");
    printf("10. Demo Animation\n");
    printf("11. Demo Animation Blitter\n");
    printf("99. Full Demo\n");
    printf("0.  Exit\n");
    printf("\n");
    printf("Enter choice: ");
    gets(choice);
    printf("\n");

    return(atoi(choice));  // converts ascii 0-9 into number 0-9
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
    drawLine( CLR_WHITE,   50, h/2,       w-50, h/2 );
    drawLine( CLR_RED,     50, (h/2)+20,  w-50, (h/2)+20 );    
    drawLine( CLR_GREEN,   50, (h/2)+40,  w-50, (h/2)+40 );    
    drawLine( CLR_BLUE,    50, (h/2)+60,  w-50, (h/2)+60 );    
    drawLine( CLR_MAGENTA, 50, (h/2)+80,  w-50, (h/2)+80 );    
    drawLine( CLR_YELLOW,  50, (h/2)+100, w-50, (h/2)+100 );    
    drawLine( CLR_CYAN,    50, (h/2)+120, w-50, (h/2)+120 );    

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
    drawRect(       CLR_WHITE,  100, h/2,      50, 50 );
    drawSolidRect(  CLR_WHITE,  100, h/2 + 70, 50, 50 );

    drawRect(       CLR_RED,    200, h/2,      50, 50 );
    drawSolidRect(  CLR_RED,    200, h/2 + 70, 50, 50 );

    drawRect(       CLR_GREEN,  300, h/2,      50, 50 );
    drawSolidRect(  CLR_GREEN,  300, h/2 + 70, 50, 50 );

    drawRect(       CLR_BLUE,   400, h/2,      50, 50 );
    drawSolidRect(  CLR_BLUE,   400, h/2 + 70, 50, 50 );

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

    // draw several circles across middle of screen
    drawCircle( CLR_WHITE,   100, h/2, 40 );
    drawCircle( CLR_MAGENTA, 200, h/2, 40 );
    drawCircle( CLR_YELLOW,  300, h/2, 40 );
    drawCircle( CLR_CYAN,    400, h/2, 40 );
    drawCircle( CLR_RED,     500, h/2, 40 );
    drawCircle( CLR_GREEN,   600, h/2, 40 );
    drawCircle( CLR_BLUE,    700, h/2, 40 );

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
    bh = drawGetBitmapHeight("fun.bmp");
    drawBitmap("fun.bmp",     50,  50);
    bh = drawGetBitmapHeight("texture.bmp");
    drawBitmap("texture.bmp", w/2, 50);

    // draw two bitmaps near bottom of screen
    bh = drawGetBitmapHeight("odie.bmp");
    drawBitmap("odie.bmp",    50,  h/2);
    bh = drawGetBitmapHeight("ufo.bmp");
    drawBitmap("ufo.bmp",  w/2, h/2);

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
    drawFillBitBlitBuffer( &myblit, 200, 200, color );
    drawBitBlit(&myblit, w/2 - 100, 100, 200, 200);
    drawBitBlit(&myblit, w/2 - 100, h/2, 200, 200);

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
    int animTimerId = drawAddTimer( interval, TIMER1_EVENT );
    
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

void DemoAnimBlit()
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
    drawInitExtended(WIDTH, HEIGHT, BPP, "DrawSDL - AnimBlit");
    
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
    
    // create bit blit
    tsImage whiteblit;
    drawCreateBitBlitImage( &whiteblit, 50, 50, 16 );
    drawFillBitBlitImage( &whiteblit, CLR16_WHITE );
    tsImage blackblit;
    drawCreateBitBlitImage( &blackblit, 50, 50, 16 );
    drawFillBitBlitImage( &blackblit, CLR16_BLACK );
    
    // draw first rectangle
//    drawSolidRect( CLR_WHITE, x, y, 50, 50);
    drawBitBlitImage( &whiteblit, x, y );
    drawSwapBuffers();
    
    // set up anim timer for 30 frames per second
    int interval = 33;              // milliseconds per frame
    int animTimerId = drawAddTimer( interval, TIMER1_EVENT );
    
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
                        drawBitBlitImage( &blackblit, x, y );
//                        drawSolidRect( CLR_BLACK, x, y, 50, 50 );
                    }
                    // move rectangle
                    x += 20;
                    if (x < (w/2 - 12))
                        y -= 12;
                    else
                        y += 12;
                    // draw moved rectangle
                    drawBitBlitImage( &whiteblit, x, y );
//                    drawSolidRect( CLR_WHITE, x, y, 50, 50 );
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

void DemoFull()
{
    int w, h;    // screen width and height   
    int bw, bh;  // bitmap width and height
  
    // initialize the drawing package
    drawInit(WIDTH, HEIGHT, BPP);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);
    
    // BEGIN DEMO HERE //
    
    // draw large rextangle near top of screen
    drawRect( CLR_MAGENTA, 50, 50, w-100, 100 );
    
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
    drawCircle( CLR_YELLOW, 450, h/2, 10 );
    
    drawLine(      CLR_WHITE, 600, h/2,      w-50, h/2 );
    drawSolidLine( CLR_BLUE,  600, (h/2)+20, w-50, (h/2)+20 );    
    
    // draw some bitmaps near bottom of screen
    bw = drawGetBitmapWidth("fun.bmp");
    bh = drawGetBitmapHeight("fun.bmp");
    drawBitmap("fun.bmp",     50,      h-bh-50);
    bw = drawGetBitmapWidth("texture.bmp");
    bh = drawGetBitmapHeight("texture.bmp");
    drawBitmap("texture.bmp", w-bw-50, h-bh-50);
    
    // let's create our own bit blit buffer and display it
    unsigned short myblit[200][200];
    unsigned short color = drawCreateColor16( 0x80, 0x80, 0x80 );
    drawFillBitBlitBuffer( &myblit, 200, 200, color );
    drawBitBlit(&myblit, w/2 - 100, h-200-50, 200, 200);

    // END DEMO HERE //

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    // call this to wait for user to 'X' out
    drawWaitQuit();
}

/* end of main.c */
