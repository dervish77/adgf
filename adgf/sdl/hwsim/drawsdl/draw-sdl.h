/*
 *     Module Name:  draw-sdl.h
 *
 *     Author:      Brian Lingard
 *
 *     Description:
 *	   Contains platform specific drawing functions for SDL graphics platform.
 *
 *     Notes:
 *     - you must port these functions to your graphics platform
 *
 *
 */

#ifndef __draw_sdl_h
#define __draw_sdl_h

#include <SDL/SDL.h>


#define DRAWSDL_VERSION "0.7.5"


//////////////////////////////////////////////////////////////////////////////
// configuration
//////////////////////////////////////////////////////////////////////////////

//#define DRAWSDL_ENABLE_FULLSCREEN
#define DRAWSDL_ENABLE_DOUBLEBUF

#ifdef HAS_TEXT
#define DRAWSDL_ENABLE_TEXT
#endif

#define UNUSED(x) (void)(x)

//////////////////////////////////////////////////////////////////////////////
// defines for drawing
//////////////////////////////////////////////////////////////////////////////

// screen color depths (bits per pixel)
#define DEPTH_BPP_32  32
#define DEPTH_BPP_24  24
#define DEPTH_BPP_16  16
#define DEPTH_BPP_8   8

#define PITCH_BPP_32  4
#define PITCH_BPP_24  3
#define PITCH_BPP_16  2
#define PITCH_BPP_8   1


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

/* clamp the input v to a specified range */
#define CLAMP(v,l,h)	((v) < (l) ? (l) : (v) > (h) ? (h) : v)

/* absolute value of input */
#define ABS(a)		(((a) < 0) ? -(a) : (a))

//////////////////////////////////////////////////////////////////////////////
// define useful events
//////////////////////////////////////////////////////////////////////////////

#define MOUSE_MOTION        1
#define MOUSE_LEFT_DOWN     2
#define MOUSE_LEFT_UP       3
#define MOUSE_MIDDLE_DOWN   4
#define MOUSE_MIDDLE_UP     5
#define MOUSE_RIGHT_DOWN    6
#define MOUSE_RIGHT_UP      7
#define KEY_DOWN            8
#define KEY_UP              9
#define WINDOW_QUIT         10
#define TIMER1_EVENT        11
#define TIMER2_EVENT        12

//////////////////////////////////////////////////////////////////////////////
// define useful structures
//////////////////////////////////////////////////////////////////////////////

typedef struct {
    SDL_Surface *screen;
    SDL_Event event;
    int width;
    int height;
    int pitch;
    int bpp;
    int alphaEnabled;
    int pixelCount;
} screenContext;

typedef struct {
    SDL_Surface *image;
    int width;
    int height;
	int half_w;
	int half_h;
    int pitch;
    int bpp;
    int alphaEnabled;
} spriteContext;

typedef struct {
    int x;
    int y;
} screenPoint;

typedef struct {
    int x;
    int y;
    int state;
} tsMouseState;

typedef struct {
    char key;
    int state;
} tsKeyState;

//////////////////////////////////////////////////////////////////////////////
// prototypes
//////////////////////////////////////////////////////////////////////////////

// from draw-sdl.c SDL dependent section (public)

int  drawInit(int screen_x, int screen_y, int bpp);
int  drawInitExtended(int screen_x, int screen_y, int bpp, char *caption);
void drawSetCaption(char *caption);
void drawQuit();

void drawWait(int milliseconds);
void drawWaitQuit();

int  drawGetQuitState();

char drawGetKey();
int  drawGetKeyState(char *key);

int  drawGetMouseState(int *x, int *y);

int  drawGetEvent(int *x, int *y, char *key);

void drawSwapBuffers();

void drawBackground(long color);

void drawPixel(long color, int x, int y);
void drawWritePixel(SDL_Surface *theScreen, long color, int x, int y);
long drawReadPixel(SDL_Surface *theScreen, int x, int y);

void drawBitmap(char *file, int x, int y);
int  drawGetBitmapWidth(char *file);
int  drawGetBitmapHeight(char *file);

void drawLoadSprite(spriteContext *sprite, char *file);
void drawSaveSprite(spriteContext *sprite, char *file);
void drawCreateSprite(spriteContext *sprite, int w, int h);
void drawGetSpriteExtent(spriteContext *sprite, int *w, int *h);
void drawSprite(spriteContext *sprite, int tlx, int tly);

void drawBitBlit(unsigned short *buffer, int x, int y, int width, int height);

long           drawCreateColor32(char red, char green, char blue);
long           drawCreateColor24(char red, char green, char blue);
unsigned short drawCreateColor16(char red, char green, char blue);

int  drawGetTicks();
int  drawIsTicksInterval(int start, int interval);

int  drawAddTimer(int delay, int eventId);
int  drawRemoveTimer(int timer_id);

// from draw-sdl.c SDL dependent section (not for public use)

SDL_Surface *drawGetScreen();
SDL_Surface *drawGetSpriteScreen(spriteContext *sprite);

// from draw-sdl.c platform independent section (public)

char *drawGetVersion();

int  drawIsFullScreenSupported();
int  drawIsDoubleBufferSupported();
int  drawIsTextSupported();

int  drawGetWidth();
int  drawGetHeight();

int  drawGetPixelCount();

void drawLine(long color, int x1, int y1, int x2, int y2);
void drawSolidLine(long color, int x1, int y1, int x2, int y2);
void drawDashedLine(long color, int x1, int y1, int x2, int y2);
void drawDottedLine(long color, int x1, int y1, int x2, int y2);

void drawRect(long color, int tlx, int tly, int width, int height);
void drawSolidRect(long color, int tlx, int tly, int width, int height);
void drawShadedRect(long color1, long color2, int tlx, int tly, int width, int height);

void drawTriangle(long color, int x1, int y1, int x2, int y2, int x3, int y3);
void drawSolidTriangle(long color, int x1, int y1, int x2, int y2, int x3, int y3);

void drawPolyline(long color, screenPoint *pointList, int numPoints);
void drawPolygon(long color, screenPoint *pointList, int numPoints);
void drawSolidPolygon(long color, screenPoint *pointList, int numPoints);

void drawCircle(long color, int xCenter, int yCenter, int radius);
void drawSolidCircle(long color, int xCenter, int yCenter, int radius);

void drawCreateBitBlitBuffer(unsigned short *buffer, int width, int height, int pitch_bpp);
void drawFillBitBlitBuffer(unsigned short *buffer, int width, int height, unsigned short color);

#endif /* __draw_sdl_h */

