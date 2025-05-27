/*
 *     Module Name:  draw.c
 *
 *     Author:       Brian Lingard (adapted for diags use)
 *
 *     Description:
 *	   Contains platform independent drawing functions for typical geometric shapes.
 *
 */

/*
 *  INCLUDES
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include "config.h"

#include "draw.h"


//////////////////////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////////////////////

extern int display_w;
extern int display_h;
extern int display_bpp;


//////////////////////////////////////////////////////////////////////////////
// local functions
//////////////////////////////////////////////////////////////////////////////

// lerp requires alpha value that ranges from 0 to 1
float lerpCalcAlpha( int low, int high, int current )
{
    float alpha;

//    printf("low = %d, high = %d, current = %d\n", low, high, current);
    
    // calculate 
    //   alpha = (current - low) / (high - low)
    // or 
    //   alpha = delta / range
    //
    //   when current = low,  alpha = 0
    //   when current = high, alpha = 1
    //
    float delta = current - low;
    float range = high - low;
    alpha = delta / range;

//    printf("delta = %f, range = %f, alpha = %f\n", delta, range, alpha);

    return(alpha);
}

// linear interpret 32 bit color1 to color2
long lerpColor32( long color1, long color2, float alpha )
{
    long color;    
#if 0
    float r, g, b;
    char r1, g1, b1;
    char r2, g2, b2;

    r1 = (char ) (color1 & 0x00FF0000) >> 16;
    g1 = (char ) (color1 & 0x0000FF00) >>  8;
    b1 = (char ) (color1 & 0x000000FF) >>  0;

    r2 = (char ) (color2 & 0x00FF0000) >> 16;
    g2 = (char ) (color2 & 0x0000FF00) >>  8;
    b2 = (char ) (color2 & 0x000000FF) >>  0;

    r = LERP( alpha, r1, r2 );
    g = LERP( alpha, g1, g2 );
    b = LERP( alpha, b1, b2 );

    printf("r,g,b = %02X,%02X,%02X\n", r,g,b);

    color = drawCreateColor32( r, g, b );
#endif

    color = LERP( alpha, color1, color2 );

    return(color);
}


//////////////////////////////////////////////////////////////////////////////
// misc drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawDisplayOn()
{
//   GdcDispOn();
   printf("display is ON\n");
}

void drawDisplayOff()
{
//   GdcDispOff();
   printf("display is OFF\n");
}

void drawSetMatrix()
{
  float m[16];

  // load default transform matrix
  m[0] =1.0f; m[1] =0.0f; m[2] =0.0f; m[3]=0.0f;
  m[4] =0.0f; m[5] =1.0f; m[6] =0.0f; m[7]=0.0f;
  m[8] =0.0f; m[9] =0.0f; m[10]=1.0f; m[11]=0.0f;
  m[12]=0.0f; m[13]=0.0f; m[14]=0.0f; m[15]=1.0f;

//  XGdcGeoLoadMatrixf(gdc, m);
}

int drawGetWidth()
{
    return(display_w);
}

int drawGetHeight()
{
    return(display_h);
}

//////////////////////////////////////////////////////////////////////////////
// line drawing functions
//////////////////////////////////////////////////////////////////////////////

static void lineBresenham(long color, int x0, int y0, int x1, int y1)
{
    //int pix = color.getRGB();
    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepx, stepy;

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
    dy <<= 1;                                                  // dy is now 2*dy
    dx <<= 1;                                                  // dx is now 2*dx

    //raster.setPixel(pix, x0, y0);
    drawPixel( color, x0, y0 );
    if (dx > dy) 
    {
        int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
        while (x0 != x1) 
        {
            if (fraction >= 0) 
            {
                y0 += stepy;
                fraction -= dx;                                // same as fraction -= 2*dx
            }
            x0 += stepx;
            fraction += dy;                                    // same as fraction -= 2*dy
            //raster.setPixel(pix, x0, y0);
            drawPixel( color, x0, y0 );
        }
    } 
    else 
    {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) 
        {
           if (fraction >= 0) 
           {
               x0 += stepx;
               fraction -= dy;
           }
           y0 += stepy;
           fraction += dx;
           //raster.setPixel(pix, x0, y0);
           drawPixel( color, x0, y0 );
        }
    }
}

static void lineSimple(long color, int x1, int y1, int x2, int y2)
{
    int x,y;

    // check if horizontal line
    if (y1 == y2)
    {
        for (x = x1; x < x2; x++)
        {
            drawPixel( color, x, y1 );
        }
    }

    // check if vertical line
    if (x1 == x2)
    {
        for (y = y1; y < y2; y++)
        {
            drawPixel( color, x1, y );
        }
    }
}

void drawLine(long color, int x1, int y1, int x2, int y2)
{
    drawSolidLine( color, x1, y1, x2, y2 );
}

void drawSolidLine(long color, int x1, int y1, int x2, int y2)
{
    lineBresenham( color, x1, y1, x2, y2 );
//    lineSimple( color, x1, y1, x2, y2 );
//    printf("drawSolidLine: done\n");
}

void drawDashedLine(long color, int x1, int y1, int x2, int y2)
{
#if 0
  XGdcColor(gdc,(GDC_COL16)color);
  XGdcBackColor(gdc,0xF000);
  XGdcGeoSetAttrLine(gdc,GDC_GEO_UNIFORM_LINE_WIDTH, GDC_ENABLE);
  XGdcSetLinePattern(gdc,LINE_DASHED);

  XGdcGeoPrimType(gdc,GDC_LINES);
  XGdcGeoDrawVertex2Di(gdc,x1,y1);
  XGdcGeoDrawVertex2Di(gdc,x2,y2);

  XGdcGeoPrimEnd(gdc);
#endif
  printf("drawDashedLine: done\n");
}

//////////////////////////////////////////////////////////////////////////////
// box drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawBox(long color, int tlx, int tly, int width, int height)
{
  drawSolidLine(color, tlx,      tly,        tlx+width,tly );
  drawSolidLine(color, tlx+width,tly,        tlx+width,tly+height );
  drawSolidLine(color, tlx,      tly+height, tlx+width,tly+height );
  drawSolidLine(color, tlx,      tly,        tlx,      tly+height );

  printf("drawBox: done\n");
}

void drawSolidBox(long color, int tlx, int tly, int width, int height)
{
    int yy;

//    printf("drawSolidBox: tlx = %d\n", tlx);
//    printf("drawSolidBox: tly = %d\n", tly);
//    printf("drawSolidBox: width  = %d\n", width);
//    printf("drawSolidBox: height = %d\n", height);

    for (yy = tly; yy < (tly+height); yy++)
    {
        drawSolidLine( color, tlx, yy, tlx+width, yy );
    }

//    printf("drawSolidBox: done\n");
}

void drawShadedBox(long color1, long color2, 
	int tlx, int tly, int width, int height)
{
    float alpha;
    long color;
    int yy;

    for (yy = tly; yy < (tly+height); yy++)
    {
	    alpha = lerpCalcAlpha( tly, tly+height, yy );
	    color = lerpColor32( color1, color2, alpha );
	
//        printf("color1 = %08X, color2 = %08X, color = %08X\n", color1, color2, color );

        drawSolidLine( color, tlx, yy, tlx+width, yy );
    }

    printf("drawShadedBox: done\n");
}

void drawWildBox(long color1, long color2, long color3, long color4,
	int tlx, int tly, int width, int height)
{
    //temp
    drawSolidBox( color1, tlx, tly, width, height );
#if 0
  XGdcGeoPrimType(gdc,GDC_TRIANGLE_FAN);
  XGdcVertexColor32(gdc,(GDC_COLOR32)color1);
  XGdcGeoDrawVertex2Di(gdc, tlx,         tly);
  XGdcVertexColor32(gdc,(GDC_COLOR32)color2);
  XGdcGeoDrawVertex2Di(gdc, tlx + width, tly);
  XGdcVertexColor32(gdc,(GDC_COLOR32)color3);
  XGdcGeoDrawVertex2Di(gdc, tlx + width, tly + height);
  XGdcVertexColor32(gdc,(GDC_COLOR32)color4);
  XGdcGeoDrawVertex2Di(gdc, tlx,         tly + height);
  
  XGdcGeoPrimEnd(gdc);
#endif
  printf("drawWildBox: done\n");
}

void drawSolidRect(short color, int tlx, int tly, int width, int height)
{
    drawSolidBox( color, tlx, tly, width, height );
    printf("drawRect: done\n");
}

//////////////////////////////////////////////////////////////////////////////
// circle drawing functions
//////////////////////////////////////////////////////////////////////////////

static void circlePoints (int cx, int cy, int x, int y, long pix) 
{
    int act = pix;

    if (x == 0)
    {
        drawPixel (act, cx, cy + y);
        drawPixel (pix, cx, cy - y);
        drawPixel (pix, cx + y, cy);
        drawPixel (pix, cx - y, cy);
    }
    else
    if (x == y)
    {
        drawPixel (act, cx + x, cy + y);
        drawPixel (pix, cx - x, cy + y);
        drawPixel (pix, cx + x, cy - y);
        drawPixel (pix, cx - x, cy - y);
    }
    else
    if (x < y)
    {
        drawPixel (act, cx + x, cy + y);
        drawPixel (pix, cx - x, cy + y);
        drawPixel (pix, cx + x, cy - y);
        drawPixel (pix, cx - x, cy - y);
        drawPixel (pix, cx + y, cy + x);
        drawPixel (pix, cx - y, cy + x);
        drawPixel (pix, cx + y, cy - x);
        drawPixel (pix, cx - y, cy - x);
    }
}

static void circleMidpoint (long color, int xCenter, int yCenter, int radius)
{
    int x = 0;
    int y = radius;
    int p = (5 - radius * 4) / 4;

    circlePoints (xCenter, yCenter, x, y, color);

    while (x < y)
    {
        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        circlePoints (xCenter, yCenter, x, y, color);
    }
}

void drawCircle (long color, int xCenter, int yCenter, int radius)
{
//    printf("x,y = %d,%d -- radius = %d\n", xCenter, yCenter, radius );
    circleMidpoint (color, xCenter, yCenter, radius);
//    printf("drawCircle: done\n");
}


//////////////////////////////////////////////////////////////////////////////
// blitter drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawCreateBitBlitBuffer(unsigned short *buffer, int width, int height, int bpp)
{
  // assumes 16 bit Blt
  unsigned short *mapped;

  switch(bpp)
  {
    case 4:
        mapped = (unsigned long *) malloc( width * height * 4 );
        break;
    case 3:
        mapped = (unsigned long *) malloc( width * height * 4 );
        break;
    case 2:
        mapped = (unsigned short *) malloc( width * height * 2 );
        break;       
  }
         
  if (mapped == NULL)
  {
    printf("drawCreateBitBlitBuffer: malloc failed\n");
    buffer = NULL;
  }
  else
  {
    printf("drawCreateBitBlitBuffer: buffer created\n");
    buffer = mapped;
  }
}

void drawFillBitBlitBuffer(unsigned short *buffer, int width, int height, unsigned short color)
{
  // assumes 16 bit Blt
  int x,y;
  unsigned short *ptr;
 
  printf("drawFillBitBlitBuffer: filling\n");

  ptr = buffer;

  for (y=0; y<height; y++) 
  {
    for (x=0; x<width; x++) 
    {
//       printf("0x%04x ", color);
       *(ptr++) = color;
    }
//    printf("\n");
  }

  printf("drawFillBitBlitBuffer: filled with 0x%04x\n", color);
}

//////////////////////////////////////////////////////////////////////////////
// Edwin's drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawBlueBackground()
{
    drawBackground(CLR_BLUE);
//    printf("drawBlueBackground: done\n");
}

void drawBlackBox()
{
    drawSolidBox( CLR_BLACK, 50, drawGetHeight()/4, drawGetWidth()-100, drawGetHeight()/2 );
//    printf("drawBlackBox: done\n");
}

unsigned int offset = 0;

int drawMovingWhiteBox()
{
    int size = drawGetHeight()/2 - 50;
    int tly  = drawGetHeight()/4 + 25;

    drawSolidBox( CLR_WHITE, 75 + offset, tly, size, size );
    
    //offset = (offset + 2) % 128;
    offset = (offset + 10);

//    printf("offset = %d\n", offset);

    if (offset >= (drawGetWidth() - size - 150)) return(1);

    return(0);
}

//////////////////////////////////////////////////////////////////////////////
// video pass-thru drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawVideoPassInit()
{
  printf("drawVideoPassInit: init'ing\n");

//  GdcCapSetVideoCaptureMode( GDC_CAP_NTSC );
//  GdcCapSetImageArea( 0,0, 799,479 );
//  GdcCapSetDisplaySize( 799, 479 );

//  GdcDispDimension( GDC_DISP_LAYER_W, GDC_ENABLE,
//			GDC_16BPP_FORMAT, GDC_FLIPMODE_AUTO,
//			TBD, TBD,
//			799, 479 );
//  GdcCapSetWindowMode( GDC_CAP_RGB_MODE, GDC_CAP_NORMAL_MODE );

}

void drawVideoPassOn()
{
  printf("drawVideoPassOn: ON\n");
#if 0
  if (GdcCaptureOn() == GDC_FALSE)
     printf("GdcCaptureOn() failed!!\n");
#endif
}

void drawVideoPassOff()
{
  printf("drawVideoPassOff: OFF\n");
#if 0
  if (GdcCaptureOff() == GDC_FALSE)
     printf("GdcCaptureOff() failed!!\n");
#endif
}

void drawVideoPassScale( int hscale, int vscale )
{
  printf("drawVideoPassScale: scaling set\n");

  printf("WARNING : this command is currently not implemented!!\n");

// calls to GdcCapSetVideoCaptureScale use a range of scaling 
// from 0xffff (max scaling) to 0x0800 (no scaling)

//   GdcCapSetVideoCaptureScale( GDC_FIXED_SCALE hscale, GDC_FIXED_SCALE vscale );
}

/* end of draw.c */

