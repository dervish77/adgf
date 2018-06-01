/*
 *     Module Name:  draw.h
 *
 *     Author:      Brian Lingard (adapted for diags use)
 *
 *     Description:
 *
 * 	WARNING!! -- Must be ported to your platform!!
 *
 *     Assumptions:
 *
 *
 *
 */

#ifndef __draw_h
#define __draw_h


//////////////////////////////////////////////////////////////////////////////
// defines for drawing
//////////////////////////////////////////////////////////////////////////////

// screen color depths
#define BPP_32  32
#define BPP_16  16
#define BPP_8   8

#define BPP     BPP_16

// screen sizes
#define WIDTH_640   640
#define WIDTH_800   800
#define WIDTH_1024  1024
#define WIDTH_1280  1280
#define WIDTH_1920  1920

#define HEIGHT_480  480
#define HEIGHT_600  600
#define HEIGHT_768  768
#define HEIGHT_1024 1024
#define HEIGHT_1080 1080

//#define WIDTH   WIDTH_1024
//#define HEIGHT  HEIGHT_768
#define WIDTH   800
#define HEIGHT  600


// 32 bit colors
#define CLR_BLACK	    0xFF000000
#define CLR_WHITE	    0xFFFFFFFF
#define CLR_RED	    	0xFFFF0000
#define CLR_GREEN   	0xFF00FF00
#define CLR_BLUE    	0xFF0000FF
#define CLR_MAGENTA 	0xFFFF00FF
#define CLR_YELLOW  	0xFFFFFF00
#define CLR_CYAN    	0xFF00FFFF
#define CLR_GRAY_DARK	0xFF404040
#define CLR_GRAY_MED	0xFF808080
#define CLR_GRAY_LIGHT	0xFFC0C0C0

// 16 bit colors
#define CLR16_BLACK	    0x8000
#define CLR16_WHITE 	0xFFFF
#define CLR16_RED   	0xFC00
#define CLR16_GREEN	    0x83E0
#define CLR16_BLUE	    0x801F
#define CLR16_MAGENTA	0xFC1F
#define CLR16_YELLOW	0xFFE0
#define CLR16_CYAN	    0x83FF

// line patterns
#define LINE_SOLID	    0xFFFFFFFF
#define LINE_DOTTED 	0xAAAAAAAA
#define LINE_DASHED	    0xF0F0F0F0


//////////////////////////////////////////////////////////////////////////////
// define useful macros
//////////////////////////////////////////////////////////////////////////////

/* find minimum of a and b */
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))

/* find maximum of a and b */
#define MAX(a,b)	(((a) > (b)) ? (a) : (b))

/* swap a and b */
#define SWAP(a,b)	{ a^=b; b^=a; a^=b; }

/* linear interpolation from l (when a=0) to h (when a=1) */
/* (equal to (a*h) + ((l-a)*l) */
#define LERP(a,l,h)	((l) + (((h) - (l)) * (a)))

/* clamp the input to a specified range */
#define CLAMP(v,l,h)	((v) < (l) ? (l) : (v) > (h) ? (h) : v)

/* absolute value of input */
#define ABS(a)		(((a) < 0) ? -(a) : (a))


//////////////////////////////////////////////////////////////////////////////
// prototypes
//////////////////////////////////////////////////////////////////////////////

// from draw-sdl.c

int  drawInit(int screen_x, int screen_y, int bpp);

void drawWait(int milliseconds);

void drawSwapBuffers();

void drawBackground(long color);
void drawGradient(long color1, long color2);

void drawPixel(long color, int x, int y);

void drawBitmap(char *file, int x, int y);
int  drawGetBitmapWidth(char *file);
int  drawGetBitmapHeight(char *file);

void drawBitBlit(unsigned short *buffer, int x, int y, int width, int height);

long           drawCreateColor32(char red, char green, char blue);
long           drawCreateColor24(char red, char green, char blue);
unsigned short drawCreateColor16(char red, char green, char blue);


// from draw.c

void drawDisplayOn();
void drawDisplayOff();

void drawSetMatrix();

int  drawGetWidth();
int  drawGetHeight();

void drawLine(long color, int x1, int y1, int x2, int y2);
void drawSolidLine(long color, int x1, int y1, int x2, int y2);
void drawDashedLine(long color, int x1, int y1, int x2, int y2);

void drawBox(long color, int tlx, int tly, int width, int height);
void drawSolidBox(long color, int tlx, int tly, int width, int height);
void drawShadedBox(long color1, long color2, 
                   int tlx, int tly, int width, int height);
void drawWildBox(long color1, long color2, long color3, long color4, 
                 int tlx, int tly, int width, int height);

void drawSolidRect(short color, int tlx, int tly, int width, int height);

void drawCircle(long color, int xCenter, int yCenter, int radius);

void drawCreateBitBlitBuffer(unsigned short *buffer, int width, int height, int bpp);
void drawFillBitBlitBuffer(unsigned short *buffer, int width, int height, unsigned short color);

void drawVideoPassInit();
void drawVideoPassOn();
void drawVideoPassOff();
void drawVideoPassScale( int hscale, int vscale );

void drawBlueBackground();
void drawBlackBox();
int drawMovingWhiteBox();

#endif /* __draw_h */

