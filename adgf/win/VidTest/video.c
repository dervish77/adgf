/*
 *     Module Name:  video.c
 *
 *     Author:       Brian Lingard (adapted for diags use)
 *
 *     Description:
 *
 *
 *     Assumptions:
 *
 *
 *
 */

/*
 *  INCLUDES
 */

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include "config.h"

#include "draw.h"
#include "video.h"


//////////////////////////////////////////////////////////////////////////////
// static functions
//////////////////////////////////////////////////////////////////////////////

static int Random( int low, int high )
{
    float fhigh = (float) high;
    int j;

    j = low + (int) (fhigh * (rand() / (RAND_MAX + 1.0)));

    return(j);
}

static int CalcLineLengthSquared( int x0, int y0, int x1, int y1 )
{
    int A, B;
    int Csquared;

    A = x1 - x0;
    B = y1 - y0;

    Csquared = A*A + B*B;

    return(Csquared);
}

//////////////////////////////////////////////////////////////////////////////
// pattern functions
//////////////////////////////////////////////////////////////////////////////

// initialize drawing canvas
int hw_draw_init()
{
   return( drawInit(WIDTH, HEIGHT, BPP) ); 
}

// 
int hw_draw_pattern_anim()		/* edwin's demo */
{
  int state = 0;

  printf("hw_draw_pattern_anim: starting animation, type ctl-c to quit\n");

  while (1) {
    drawBlueBackground();
    drawBlackBox();
    state = drawMovingWhiteBox();
    drawSwapBuffers();
    drawWait(2);
    if (state) break;
    //break;
  }

  hw_draw_wait();

  return 1;
}

//============================================================================

// open boxes pattern
int hw_draw_pattern_1()
{
  int incr = drawGetHeight()/4;

  drawBackground(CLR_BLACK);

  drawBox(CLR_WHITE,   50,incr*1 - incr/2, drawGetWidth()-100,100 );
  drawBox(CLR_CYAN,    50,incr*2 - incr/2, drawGetWidth()-100,100 );
  drawBox(CLR_MAGENTA, 50,incr*3 - incr/2, drawGetWidth()-100,100 );

  drawSwapBuffers();

  return 1;
}

// shaded boxes pattern
int hw_draw_pattern_2()
{
  int incr = drawGetHeight()/4;

  drawBackground(CLR_BLUE);

  drawShadedBox(CLR_RED, CLR_GREEN, 50,incr*1 - incr/2, drawGetWidth()-100,150 );	/* red/grn box */
  drawShadedBox(CLR_GREEN, CLR_RED, 50,incr*3 - incr/2, drawGetWidth()-100,150 );	/* grn/red box */
//  drawShadedBox(CLR_BLACK, CLR_WHITE, 50,incr*3 - incr/2, drawGetWidth()-100,150 );	/* grn/red box */

  drawSwapBuffers();

  return 1;
}

// fan of lines pattern
int hw_draw_pattern_3()
{
  int y_upper = drawGetHeight()/4;
  int y_lower = (drawGetHeight()/4) * 3;

  int x_lower = drawGetWidth()/2;

  int count = 19;

  int x_incr = drawGetWidth() / (count + 1);

  drawBackground(CLR_GRAY_DARK);

  int i;
  for (i = 0; i < count; i++)
  {
      drawSolidLine( CLR_WHITE, x_lower, y_lower,  x_incr + (i * x_incr), y_upper );
  }

  drawSwapBuffers();

  return 1;
}

// color bar pattern
int hw_draw_pattern_4()
{
  int incx;

  int ox = 50;
  int oy = 50;

  incx = (drawGetWidth() - ox - ox) / 7;

  int w = incx;
  int h = (drawGetHeight() - oy - oy);

  drawBackground(CLR_BLACK);

//  printf("w,h = %d, %d\n", w,h);

  drawSolidBox(CLR_WHITE,   ox+0*incx,oy,  w,h );	
  drawSolidBox(CLR_RED,     ox+1*incx,oy,  w,h );	
  drawSolidBox(CLR_GREEN,   ox+2*incx,oy,  w,h );	
  drawSolidBox(CLR_BLUE,    ox+3*incx,oy,  w,h );	
  drawSolidBox(CLR_MAGENTA, ox+4*incx,oy,  w,h );   
  drawSolidBox(CLR_YELLOW,  ox+5*incx,oy,  w,h );    
  drawSolidBox(CLR_CYAN,    ox+6*incx,oy,  w,h );   

//  drawShadedBox(CLR_BLACK, CLR_WHITE, 50,330, 700,50 );
//  drawShadedBox(CLR_WHITE, CLR_BLACK, 50,380, 700,50 );

  drawSwapBuffers();

  return 1;
}

// circles pattern
int hw_draw_pattern_5()
{
  int incr = drawGetWidth()/4;
  int radius = drawGetHeight()/8;

  drawBackground(CLR_BLACK);	

  drawCircle( CLR_RED,   incr * 1, drawGetHeight()/2, radius );
  drawCircle( CLR_WHITE, incr * 2, drawGetHeight()/2, radius );
  drawCircle( CLR_BLUE,  incr * 3, drawGetHeight()/2, radius );

  drawSwapBuffers();

  return 1;
}

// horizontal lines pattern
int hw_draw_pattern_6()
{
  int y;
  int count = 10;
  int interval = drawGetHeight() / (count +1);

  drawBackground(CLR_BLACK);
  for (y=0; y<count; y++)
  {
    drawSolidLine(CLR_WHITE, 50,interval+(y*interval), drawGetWidth()-50,interval+(y*interval) );
  }
  drawSwapBuffers();

  return 1;
}

// vertical lines pattern
int hw_draw_pattern_7()
{
  int y;
  int count = 10;
  int interval = drawGetWidth() / (count +1);

  drawBackground(CLR_BLACK);
  for (y=0; y<count; y++)
  {
    drawSolidLine(CLR_WHITE, interval+(y*interval),50, interval+(y*interval),drawGetHeight()-50 );
  }
  drawSwapBuffers();

  return 1;
}

#define BLIT_WIDTH	80
#define BLIT_HEIGHT	80

// blit boxes pattern
int hw_draw_pattern_8()
{
  drawBackground(CLR_BLACK);

  int tb_w, tb_h;
  int ob_w, ob_h;

  tb_w = drawGetBitmapWidth(  "texture.bmp" );
  tb_h = drawGetBitmapHeight( "texture.bmp" );

  ob_w = drawGetBitmapWidth(  "out.bmp" );
  ob_h = drawGetBitmapHeight( "out.bmp" );

  int width  = drawGetWidth();
  int height = drawGetHeight();

  int x, y;

  int toggle = 1;

  for (y = 0; y < height; y=y+tb_h)
  {
      for (x = 0; x < width; x=x+(tb_w*2))
      {

          if (toggle)
          {
              drawBitmap( "texture.bmp", x,      y );
              drawBitmap( "out.bmp",     x+tb_w, y );
          }
          else
          {
              drawBitmap( "out.bmp",     x,      y );
              drawBitmap( "texture.bmp", x+tb_w, y );
          }

      }
      
      if (toggle)
          toggle = 0;
      else 
          toggle = 1;
  }

#if 0
  unsigned short color;
  unsigned short myblit[BLIT_WIDTH][BLIT_HEIGHT];
  unsigned short *buffer;
  buffer = (unsigned short *) &myblit;
  color = drawCreateColor16( 0xFF, 0xFF, 0xFF );
  drawFillBitBlitBuffer( buffer, BLIT_WIDTH, BLIT_HEIGHT, color );
  drawBitBlit( buffer, 80, 80+320, BLIT_WIDTH, BLIT_HEIGHT );
#endif

#if 1
  unsigned short color;
  unsigned short myblit[BLIT_WIDTH][BLIT_HEIGHT];
  unsigned short *buffer;

  buffer = (unsigned short *) &myblit;

  color = drawCreateColor16( 0xFF, 0xFF, 0xFF );
  drawFillBitBlitBuffer( buffer, BLIT_WIDTH, BLIT_HEIGHT, color );

  drawBitBlit( buffer,  0, 80+  0, BLIT_WIDTH, BLIT_HEIGHT );
  drawBitBlit( buffer,  0, 80+240, BLIT_WIDTH, BLIT_HEIGHT );
  drawBitBlit( buffer, 80, 80+ 80, BLIT_WIDTH, BLIT_HEIGHT );
  drawBitBlit( buffer, 80, 80+320, BLIT_WIDTH, BLIT_HEIGHT );

//  drawSolidRect(color,  drawGetWidth()/2,    80+  0, 80,80 );   
//  drawSolidRect(color,  drawGetWidth()/2,    80+240, 80,80 );  
//  drawSolidRect(color,  drawGetWidth()/2+80, 80+ 80, 80,80 );  
//  drawSolidRect(color,  drawGetWidth()/2+80, 80+320, 80,80 );  
#endif

  drawSwapBuffers();

  return 1;
}

// gradient fill pattern
int hw_draw_pattern_9()
{ 
//  drawBackground(CLR_BLACK);
  drawGradient(CLR_BLACK,CLR_WHITE);
  drawSwapBuffers();

  return 1;
}

// draw line using pixels pattern
int hw_draw_pattern_10()
{
  int x;

  drawBackground(CLR_BLACK);

  for (x=100; x<(drawGetWidth()-100); x++)
  {
    drawPixel(CLR_YELLOW, x, drawGetHeight()/2);		/* draw line using pixels */
  }

  drawSwapBuffers();

  return 1;
}

//============================================================================

// clear screen pattern
int hw_draw_pattern_cls()
{
  drawBackground(CLR_BLACK);			
  drawSwapBuffers();

  return 1;
}

// pause so user can gaze in awe
int hw_draw_wait()
{
  drawWait(3000);
  return 1;
}

// draw selected pattern
int hw_draw_pattern(int pattern, int wait)
{
   switch(pattern)
   {
      case 1:
         hw_draw_pattern_1();
         break;
      case 2:
         hw_draw_pattern_2();
         break;
      case 3:
         hw_draw_pattern_3();
         break;
      case 4:
         hw_draw_pattern_4();
         break;
      case 5:
         hw_draw_pattern_5();
         break;
      case 6:
         hw_draw_pattern_6();
         break;
      case 7:
         hw_draw_pattern_7();
         break;
      case 8:
         hw_draw_pattern_8();
         break;
      case 9:
         hw_draw_pattern_9();
         break;
      case 10:
         hw_draw_pattern_10();
         break;
   }

   if (wait) hw_draw_wait();
   
   return 1;
}

//============================================================================

int hw_draw_pattern_crazy_lines()
{
    int count = 100;

    printf ("Screen should be displaying - %d crazy lines\n", count);

    int startx, starty, endx, endy;
 
    int i;
    int minls = 100*100;
    int ls;

    long color;
    long colors[8] = {CLR_WHITE, CLR_RED, CLR_GREEN, CLR_BLUE, CLR_GRAY_MED, CLR_YELLOW, CLR_MAGENTA, CLR_CYAN};

    drawBackground (CLR_BLACK);

    int index = 0;

    while(1)
    {
        color = colors[index];

        for (i = 0; i < count; i++)
        {
             // random start position
             startx = Random( 1, drawGetWidth() - 1 );
             starty = Random( 1, drawGetHeight() - 1 );

             // random end position
             endx = Random( 1, drawGetWidth() - 1 );
             endy = Random( 1, drawGetHeight() - 1 );

             // ensure a minimum line length before drawing the line
             ls = CalcLineLengthSquared( startx, starty, endx, endy );
             if ( ls > minls)
             {
                 drawLine (color, startx, starty, endx, endy );
                 drawSwapBuffers();
             }
        }

        index++;
        if (index == 8) index = 0;
    }
   
    return 1;
}

int hw_draw_pattern_crazy_boxes()
{
    int count = 200;
            
    printf ("Screen should be displaying - %d crazy boxes\n", count);

    int tlx, tly;
    int size = 100;
 
    int i;
    int index = 0;

    long colors[8] = {CLR_WHITE, CLR_RED, CLR_GREEN, CLR_BLUE, CLR_GRAY_MED, CLR_YELLOW, CLR_MAGENTA, CLR_CYAN};

    while(1)
    {
         drawBackground (CLR_BLACK);
    
         for (i = 0; i < count; i++)
         {
             // random top left position
             tlx = Random( 1, drawGetWidth() - size );
             tly = Random( 1, drawGetHeight() - size );

             // random color
             index = Random( 0, 7 );

//             printf("box at (%d,%d) in color %d - %08X\n", tlx,tly,index, colors[index]);

             drawSolidBox ( colors[index], tlx, tly, size, size );    
             drawSwapBuffers();
         }
    }

    return 1;
}



int hw_draw_pattern_crazy_circles()
{
    int count = 200;
            
    printf ("Screen should be displaying - %d crazy circles\n", count);

    int cx, cy, radius;
 
    int i;
    int index = 0;

    long colors[8] = {CLR_WHITE, CLR_RED, CLR_GREEN, CLR_BLUE, CLR_GRAY_MED, CLR_YELLOW, CLR_MAGENTA, CLR_CYAN};

    while(1)
    {
         drawBackground (CLR_BLACK);
    
         for (i = 0; i < count; i++)
         {
             radius = 50 + Random( 0, 50 );
             
             // random center position
             cx = 100 + Random( 0, drawGetWidth() - 200 );
             cy = 100 + Random( 0, drawGetHeight() - 200 );

             // random color
             index = Random( 0, 7 );

//             printf("box at (%d,%d) in color %d - %08X\n", tlx,tly,index, colors[index]);

             drawCircle ( colors[index], cx, cy, radius );    
             drawSwapBuffers();
         }
    }

    return 1;
}



//============================================================================

#define NUM_PATTERNS	9

int hw_draw_pattern_cycle_slow()
{
   int i;

   for (i = 1; i <= NUM_PATTERNS; i++)
   {
      hw_draw_pattern( i, 0 );
#ifndef WIN32
      sleep(1);
#else
      Sleep(2000);       // sleep in milliseconds, tunes for windows
#endif
   }

   hw_draw_pattern_cls();

   return 1;
}

int hw_draw_pattern_cycle_fast()
{
   int i;

   for (i = 1; i <= NUM_PATTERNS; i++)
   {
      hw_draw_pattern( i, 0 );
#ifndef WIN32
      usleep(250000);   // sleep in microseconds, tuned for Linux
#else
      Sleep(500);       // sleep in milliseconds, tunes for windows
#endif
   }

   hw_draw_pattern_cls();

   return 1;
}

//============================================================================

int hw_video_pass( int enable )
{
   drawVideoPassInit();

   if (enable)
   {
      drawVideoPassOn();
   }
   else
   {
      drawVideoPassOff();
   }

   return 1;
}

int hw_video_scale( int scalew, int scaleh )
{
   int hscale;
   int vscale;

// calls to GdcCapSetVideoCaptureScale use a range of scaling 
// from 0xffff (max scaling) to 0x0800 (no scaling)

   // calculate scaling width
   hscale = ( ( (100 - scalew) * 0xf7ff ) / 100 ) + 0x0800;

   // calculate scaling height
   vscale = ( ( (100 - scaleh) * 0xf7ff ) / 100 ) + 0x0800;

   // set scale on Coral-P
   printf("hw_video_scale: hscale = 0x%04x\n", hscale);
   printf("hw_video_scale: vscale = 0x%04x\n", vscale);

   drawVideoPassScale( hscale, vscale );

   return 1;
}

/* end of hw-video.c */

