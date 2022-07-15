/*
 *     Module Name:  draw-sdl.c
 *
 *     Author:       Brian Lingard 
 *
 *     Description:
 *	   Contains platform specific drawing functions for SDL graphics platform.
 *
 *     Notes:
 *     - you must port these functions to your graphics platform
 *
 */

/*
 *  INCLUDES
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include <SDL/SDL.h>

#include "draw-sdl.h"


//#define DEBUG


//***************************************************************************//
// BEGIN SDL dependent section
//***************************************************************************//

//////////////////////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////////////////////

int display_w;
int display_h;
int display_bpp;

SDL_Surface *screen;

SDL_Event event;

int alphaEnabled = 0;

int pixelCount = 0;


//////////////////////////////////////////////////////////////////////////////
// color functions
//////////////////////////////////////////////////////////////////////////////

Uint16 CreateHicolorPixelFromLongColor(SDL_PixelFormat * fmt, long color)
{
    Uint16 value;
    Uint8 red;
    Uint8 green;
    Uint8 blue;

    // ignore most significant byte
    red   = (color & 0x00FF0000) >> 16;
    green = (color & 0x0000FF00) >> 8;
    blue  = (color & 0x000000FF) >> 0;

    /* This series of bit shifts uses the information from the SDL_Format
       structure to correctly compose a 16-bit pixel value from 8-bit red,
       green, and blue data. */
    value = ((red >> fmt->Rloss) << fmt->Rshift) +
	               ((green >> fmt->Gloss) << fmt->Gshift) +
	               ((blue >> fmt->Bloss) << fmt->Bshift);

    return value;
}

Uint16 CreateHicolorPixel(SDL_PixelFormat * fmt, Uint8 red, Uint8 green, Uint8 blue)
{
    Uint16 value;

    /* This series of bit shifts uses the information from the SDL_Format
       structure to correctly compose a 16-bit pixel value from 8-bit red,
       green, and blue data. */
    value = ((red >> fmt->Rloss) << fmt->Rshift) +
	               ((green >> fmt->Gloss) << fmt->Gshift) +
	               ((blue >> fmt->Bloss) << fmt->Bshift);

    return value;
}

long drawCreateColor32(char red, char green, char blue)
{
    long color = 0xFF000000;
    color = color + (red<<16) + (green<<8) + blue;
    return(color);
}

long drawCreateColor24(char red, char green, char blue)
{
    long color = 0x80000000;
    color = color + (red<<16) + (green<<8) + blue;
    return(color);
}

unsigned short drawCreateColor16(char red, char green, char blue)
{
    unsigned short color = 0x8000;
    color = CreateHicolorPixel( screen->format, red, green, blue );
    return(color);
}

//////////////////////////////////////////////////////////////////////////////
// control functions
//////////////////////////////////////////////////////////////////////////////

void clearPixelCount()
{
     pixelCount = 0;
}

int getPixelCount()
{
    return(pixelCount);
}

void Slock(SDL_Surface *screen)
{
    if ( SDL_MUSTLOCK(screen) )
    {
        if ( SDL_LockSurface(screen) < 0 )
        {
            return;
        }
    }
}

void Sulock(SDL_Surface *screen)
{
    if ( SDL_MUSTLOCK(screen) )
    {
        SDL_UnlockSurface(screen);
    }
}

//////////////////////////////////////////////////////////////////////////////
// event functions
//////////////////////////////////////////////////////////////////////////////

void drawWait(int milliseconds)
{
    printf("Pausing for %d seconds...\n", milliseconds / 1000);
    SDL_Delay(milliseconds);
}

void drawWaitQuit()
{
    int quit = 0;
    
    printf("Waiting for user to quit...\n");
    
    while (quit == 0)
    {
        while( SDL_PollEvent( &event ) ) 
        {
            if( event.type == SDL_QUIT ) 
            { 
                quit = 1; 
            } 
        } 
    }
    
    SDL_Quit();
}

int drawGetQuitState()
{
    int quit = 0;
    
    while( SDL_PollEvent( &event ) ) 
    {
        if( event.type == SDL_QUIT ) 
        { 
            printf("QUIT\n");
            quit = 1; 
        } 
    } 
    return(quit);
}

char drawGetKey()
{
    char key = 0;
        
    while( SDL_PollEvent( &event ) ) 
    {
        if( event.type == SDL_KEYDOWN ) 
        { 
            printf("KEY DOWN\n");
            key = event.key.keysym.sym; 
        }
    } 

    return(key);  // returns key as ascii code
}

int drawGetKeyState(char *key)
{
    int state = 0;
        
    while( SDL_PollEvent( &event ) ) 
    {
        if( event.type == SDL_KEYDOWN ) 
        { 
            printf("KEY DOWN\n");
            *key = event.key.keysym.sym; 
            state = KEY_DOWN;
        }
        if( event.type == SDL_KEYUP ) 
        { 
            printf("KEY UP\n");
            *key = event.key.keysym.sym; 
            state = KEY_UP;
        }
    } 

    return(state);
}

int drawGetMouseState(int *x, int *y)
{
    int state = 0;
    
    while( SDL_PollEvent( &event ) ) 
    { 
        if( event.type == SDL_MOUSEMOTION ) 
        { 
            *x = event.motion.x; 
            *y = event.motion.y;
            state = MOUSE_MOTION;
        }
        
        if( event.type == SDL_MOUSEBUTTONDOWN ) 
        { 
            printf("MOUSE DOWN\n");
            if( event.button.button == SDL_BUTTON_LEFT ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_LEFT_DOWN;
            }
            if( event.button.button == SDL_BUTTON_MIDDLE ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_MIDDLE_DOWN;
            }
            if( event.button.button == SDL_BUTTON_RIGHT ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_RIGHT_DOWN;
            }            
        }
        
        if( event.type == SDL_MOUSEBUTTONUP ) 
        { 
            printf("MOUSE UP\n");
            if( event.button.button == SDL_BUTTON_LEFT ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_LEFT_UP;
            }
            if( event.button.button == SDL_BUTTON_MIDDLE ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_MIDDLE_UP;
            }
            if( event.button.button == SDL_BUTTON_RIGHT ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_RIGHT_UP;
            }            
        }
    }
    
    return(state);
}

int drawGetEvent(int *x, int *y, char *key)
{
    int state = 0;
    
    if( SDL_PollEvent( &event ) ) 
    { 
        if( event.type == SDL_USEREVENT )
        { 
            state = event.user.code;  // currently conveys which timer event occurred
        }
        
        if( event.type == SDL_QUIT ) 
        { 
            printf("QUIT\n");
            state = WINDOW_QUIT; 
        } 
        
        if( event.type == SDL_KEYDOWN ) 
        { 
            printf("KEY DOWN\n");
            *key = event.key.keysym.sym; 
            state = KEY_DOWN;
        }
        if( event.type == SDL_KEYUP ) 
        { 
            printf("KEY UP\n");
            *key = event.key.keysym.sym; 
            state = KEY_UP;
        }
        
        if( event.type == SDL_MOUSEMOTION ) 
        { 
            *x = event.motion.x; 
            *y = event.motion.y;
            state = MOUSE_MOTION;
        }
        
        if( event.type == SDL_MOUSEBUTTONDOWN ) 
        { 
            printf("MOUSE DOWN\n");
            if( event.button.button == SDL_BUTTON_LEFT ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_LEFT_DOWN;
            }
            if( event.button.button == SDL_BUTTON_MIDDLE ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_MIDDLE_DOWN;
            }
            if( event.button.button == SDL_BUTTON_RIGHT ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_RIGHT_DOWN;
            }            
        }
        
        if( event.type == SDL_MOUSEBUTTONUP ) 
        { 
            printf("MOUSE UP\n");
            if( event.button.button == SDL_BUTTON_LEFT ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_LEFT_UP;
            }
            if( event.button.button == SDL_BUTTON_MIDDLE ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_MIDDLE_UP;
            }
            if( event.button.button == SDL_BUTTON_RIGHT ) 
            {  
                *x = event.button.x; 
                *y = event.button.y;
                state = MOUSE_RIGHT_UP;
            }            
        }
    }
    
    return(state);
}

//////////////////////////////////////////////////////////////////////////////
// init functions
//////////////////////////////////////////////////////////////////////////////

int drawInit(int screen_x, int screen_y, int bpp)
{
    display_w = screen_x;
    display_h = screen_y;
    display_bpp = bpp;

#ifdef DEBUG
    printf("drawInit: calling SDL_Init...\n");
#endif

    /* Initialize SDL's video system and check for errors. */
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) 
    {
	    printf("Unable to initialize SDL: %s\n", SDL_GetError());
	    return(1);
    }

    /* Make sure SDL_Quit gets called when the program exits! */
    atexit(SDL_Quit);

#ifdef DEBUG
    printf("drawInit: calling SDL_SetVideoMode...\n");
#endif

    /* Attempt to set a 256x256 hicolor (16-bit) video mode.
       This will set some type of 16-bit mode, but we won't
       know which particular pixel format ahead of time. If
       the video card can't handle hicolor modes, SDL will
       emulate it. */
#ifdef DRAWSDL_ENABLE_FULLSCREEN
  printf("drawInit: using fullscreen...\n");
  #ifdef DRAWSDL_ENABLE_DOUBLEBUF
    printf("drawInit: using double buffers...\n");
    screen = SDL_SetVideoMode(display_w, display_h, display_bpp, SDL_FULLSCREEN|SDL_HWSURFACE|SDL_DOUBLEBUF);
  #else
    screen = SDL_SetVideoMode(display_w, display_h, display_bpp, SDL_FULLSCREEN|SDL_SWSURFACE);
  #endif
#else
  #ifdef DRAWSDL_ENABLE_DOUBLEBUF
    printf("drawInit: using double buffers...\n");
    screen = SDL_SetVideoMode(display_w, display_h, display_bpp, SDL_HWSURFACE|SDL_DOUBLEBUF);
  #else
    screen = SDL_SetVideoMode(display_w, display_h, display_bpp, SDL_SWSURFACE);
  #endif
#endif
    if (screen == NULL) 
    {
	    printf("Unable to set video mode: %s\n", SDL_GetError());
	    return(1);
    }
    
#ifdef DEBUG
    printf("drawInit: screen size %d x %d\n", display_w, display_h );
    printf("drawInit: done\n");
#endif

    return(0);
}

int drawInitExtended(int screen_x, int screen_y, int bpp, char *caption)
{
    int retval = drawInit( screen_x, screen_y, bpp );
    drawSetCaption(caption);
    return(retval);
}

void drawSetCaption(char *caption)
{
    SDL_WM_SetCaption( caption, NULL );    
}

void drawSwapBuffers()
{
    /* Inform SDL that the screen has been changed. This is necessary
       because SDL's screen surface is not always the real framebuffer;
       it is sometimes emulated behind the scenes. */
#ifdef DRAWSDL_ENABLE_DOUBLEBUF
    SDL_Flip(screen);
#else
    SDL_UpdateRect(screen, 0, 0, 0, 0);
#endif
}

void drawQuit()
{
    SDL_Quit();
}

SDL_Surface *drawGetScreen()
{
    return(screen);
}

//////////////////////////////////////////////////////////////////////////////
// full screen functions
//////////////////////////////////////////////////////////////////////////////

void drawGradient(long color1, long color2)
{
    Uint16 *raw_pixels;
    int x, y;

    Slock(screen);

    raw_pixels = (Uint16 *) screen->pixels;

    /* We can now safely write to the video surface. We'll draw a nice
       gradient pattern by varying our red and blue components along
       the X and Y axes. Notice the formula used to calculate the
       offset into the framebuffer for each pixel.
       (The pitch is the number of bytes per scanline in memory.) */
    for (x = 0; x < drawGetWidth(); x++) 
    {
	    for (y = 0; y < drawGetHeight(); y++) 
        {
	        Uint16 pixel_color;
	        int offset;
	        pixel_color = CreateHicolorPixel(screen->format, x, 0, y);
	        offset = (screen->pitch / 2 * y + x);
	        raw_pixels[offset] = pixel_color;
	        pixelCount++;
	    }
    }

    Sulock(screen);
}

void drawBackground(long color)
{
    Uint16 *raw_pixels;
    int x, y;

    /* Video memory can be strange, and it's sometimes necessary to
       "lock" it before it can be modified. SDL abstracts this with
       the SDL_LockSurface function. */
    Slock(screen);

    /* Get a pointer to the video surface's memory. */
    raw_pixels = (Uint16 *) screen->pixels;

    Uint16 pixel_color;
    pixel_color = CreateHicolorPixelFromLongColor(screen->format, color);
    for (x = 0; x < drawGetWidth(); x++) 
    {
	    for (y = 0; y < drawGetHeight(); y++) 
        {
	        int offset;
	        offset = (screen->pitch / 2 * y + x);
	        raw_pixels[offset] = pixel_color;
	        pixelCount++;
	    }
    }

    /* We're finished drawing, so unlock the surface. */
    Sulock(screen);
}

//////////////////////////////////////////////////////////////////////////////
// pixel functions
//////////////////////////////////////////////////////////////////////////////

void drawPixel(long color, int x, int y)
{    
    Uint16 *raw_pixels;

    Slock(screen);

    /* Get a pointer to the video surface's memory. */
    raw_pixels = (Uint16 *) screen->pixels;

    Uint16 pixel_color;
    pixel_color = CreateHicolorPixelFromLongColor(screen->format, color);

    int offset;
    if (x < display_w && y < display_h)
    {
        offset = (screen->pitch / 2 * y + x);
        raw_pixels[offset] = pixel_color;
    }

    Sulock(screen);

    pixelCount++;
}

//////////////////////////////////////////////////////////////////////////////
// sprite functions (better suited for gaming)
//////////////////////////////////////////////////////////////////////////////

void drawLoadSprite(spriteContext *sprite, char *file)
{
    if (sprite)
    {
        /* Load the BMP file into a surface */
        sprite->image = SDL_LoadBMP(file);
        if ( sprite->image == NULL ) {
            fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
            return;
        }

        sprite->width = sprite->image->w;
        sprite->height = sprite->image->h;

        // these are not currently used
        sprite->bpp = 0;
        sprite->alphaEnabled = 0;
    }
}

void drawGetSpriteExtent(spriteContext *sprite, int *w, int *h)
{
    if (sprite)
    {
        *w = sprite->width;
        *h = sprite->height;
    }
    else
    {
        *w = 0;
        *h = 0;
    }
}

void drawSprite(spriteContext *sprite, int tlx, int tly)
{
    SDL_Rect dest;

    if (sprite)
    {
        /* Blit sprite onto the screen surface.
           The surfaces should not be locked at this point.
         */
        dest.x = tlx;
        dest.y = tly;
        dest.w = sprite->width;
        dest.h = sprite->height;
        SDL_BlitSurface(sprite->image, NULL, screen, &dest);

        /* Update the changed portion of the screen */
        SDL_UpdateRects(screen, 1, &dest);
    
        pixelCount += (dest.w * dest.h);
    }
}

//////////////////////////////////////////////////////////////////////////////
// bitmap functions (directly loads and displays bitmap)
//////////////////////////////////////////////////////////////////////////////

int drawGetBitmapWidth(char *file)
{
    SDL_Surface *image;

    /* Load the BMP file into a surface */
    image = SDL_LoadBMP(file);
    if ( image == NULL ) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return(0);
    }

    return(image->w);
}

int drawGetBitmapHeight(char *file)
{
    SDL_Surface *image;

    /* Load the BMP file into a surface */
    image = SDL_LoadBMP(file);
    if ( image == NULL ) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return(0);
    }

    return(image->h);
}

void drawBitmap(char *file, int x, int y)
{
    SDL_Surface *image;
    SDL_Rect dest;

    /* Load the BMP file into a surface */
    image = SDL_LoadBMP(file);
    if ( image == NULL ) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return;
    }

    /* Blit onto the screen surface.
       The surfaces should not be locked at this point.
     */
    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;
    SDL_BlitSurface(image, NULL, screen, &dest);

    /* Update the changed portion of the screen */
    SDL_UpdateRects(screen, 1, &dest);
    
    pixelCount += (dest.w * dest.h);
}

void drawBitBlit(unsigned short *buffer, int tlx, int tly, int width, int height)
{
    // assumes 16 bit Blt
    SDL_Surface *image;
    SDL_Rect dest;

    Uint16 *blit_pixels, *src_buffer;
    int x, y;

    image = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,16,0,0,0,0);

    src_buffer = buffer;

    /* Copy buffer into blit image surface
     */
    image->w = width;
    image->h = height;

    blit_pixels = (Uint16 *) image->pixels;

    for (y = 0; y < height; y++) 
    {
        for (x = 0; x < width; x++) 
        {
	        int offset;
	        offset = ((image->pitch / 2) * y + x);
	        *(blit_pixels+offset) = src_buffer[offset];
	    }
    }

    /* Blit onto the screen surface.
       The surfaces should not be locked at this point.
     */
    dest.x = tlx;
    dest.y = tly;
    dest.w = image->w;
    dest.h = image->h;
    SDL_BlitSurface(image, NULL, screen, &dest);

    /* Update the changed portion of the screen */
    SDL_UpdateRects(screen, 1, &dest);
    SDL_FreeSurface( image );
 
    pixelCount += (dest.w * dest.h);
}

//////////////////////////////////////////////////////////////////////////////
// timing functions
//////////////////////////////////////////////////////////////////////////////

int drawGetTicks()
{
    return( SDL_GetTicks() );
}

int drawIsTicksInterval(int start, int interval)
{
    int state = 0;
    int delta = SDL_GetTicks() - start;
    if ((delta % interval) == 0)
    {
        state = 1;
    }
    return(state);
}

Uint32 timer1_callback(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;
    
    userevent.type = SDL_USEREVENT;
    userevent.code = TIMER1_EVENT;
    userevent.data1 = NULL;
    userevent.data2 = NULL;
    
    event.type = SDL_USEREVENT;
    event.user = userevent;
    
    SDL_PushEvent(&event);
    return(interval);
}

Uint32 timer2_callback(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;
    
    userevent.type = SDL_USEREVENT;
    userevent.code = TIMER2_EVENT;
    userevent.data1 = NULL;
    userevent.data2 = NULL;
    
    event.type = SDL_USEREVENT;
    event.user = userevent;
    
    SDL_PushEvent(&event);
    return(interval);
}

int drawAddTimer(int delay, int eventId)
{
    int interval = (delay / 10) * 10;   // round off to nearest 10 ms
    int timer_id;
    switch(eventId)
    {
        case TIMER1_EVENT:
            timer_id = (int) SDL_AddTimer( interval, timer1_callback, (void *)NULL );
            printf("added timer %d\n", timer_id);
            break;
        case TIMER2_EVENT:
            timer_id = (int) SDL_AddTimer( interval, timer2_callback, (void *)NULL );
            printf("added timer %d\n", timer_id);
            break;
        default:
            timer_id = -1;
            printf("Unknown timer requested!\n");
            break;
    }
    return(timer_id);
}

int drawRemoveTimer(int timer_id)
{
    SDL_RemoveTimer( (SDL_TimerID) timer_id );
    return(0);
}

//***************************************************************************//
// END SDL dependent section
//***************************************************************************//



//***************************************************************************//
// BEGIN platform independent section
//***************************************************************************//

//////////////////////////////////////////////////////////////////////////////
// local functions
//////////////////////////////////////////////////////////////////////////////

// lerp requires alpha value that ranges from 0 to 1
float lerpCalcAlpha( int low, int high, int current )
{
    float alpha;
    
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

    return(alpha);
}

// linear interpret 32 bit color1 to color2
long lerpColor32( long color1, long color2, float alpha )
{
    long color;    
    color = LERP( alpha, color1, color2 );
    return(color);
}


//////////////////////////////////////////////////////////////////////////////
// misc drawing functions
//////////////////////////////////////////////////////////////////////////////

int drawGetWidth()
{
    return(display_w);
}

int drawGetHeight()
{
    return(display_h);
}

char *drawGetVersion()
{
    return(DRAWSDL_VERSION);
}

int drawIsFullScreenSupported()
{
#ifdef DRAWSDL_ENABLE_FULLSCREEN
    return(1);
#else
    return(0);
#endif
}

int drawIsDoubleBufferSupported()
{
#ifdef DRAWSDL_ENABLE_DOUBLEBUF
    return(1);
#else
    return(0);
#endif
}

int drawIsTextSupported()
{
#ifdef DRAWSDL_ENABLE_TEXT
    return(1);
#else
    return(0);
#endif
}

int drawGetPixelCount()
{
    return(pixelCount);
}

//////////////////////////////////////////////////////////////////////////////
// line drawing functions
//////////////////////////////////////////////////////////////////////////////

static void lineBresenham(long color, int x0, int y0, int x1, int y1)
{
    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepx, stepy;

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
    dy <<= 1;                                                  // dy is now 2*dy
    dx <<= 1;                                                  // dx is now 2*dx
    
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

           drawPixel( color, x0, y0 );
        }
    }
}

static void lineBresenhamDashed(long dashed, long color, int x0, int y0, int x1, int y1)
{
    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepx, stepy;
    int enable = 1;
    int trigger = 8;
    int count = 1;

    switch (dashed)
    {
        case LINE_DOTTED:
            trigger = 2;
            break;
        case LINE_DASHED:
            trigger = 16;
            break;
    }

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
    dy <<= 1;                                                  // dy is now 2*dy
    dx <<= 1;                                                  // dx is now 2*dx
    
    if (enable) drawPixel( color, x0, y0 );

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

            if (enable) drawPixel( color, x0, y0 );

            if ((count > trigger/2) && (count % trigger == 0))    // toggle every 'trigger' pixels
            {
                if (enable)
                    enable = 0;
                else
                    enable = 1;
            }

            count++;
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

            if (enable) drawPixel( color, x0, y0 );

            if ((count > trigger/2) && (count % trigger == 0))    // toggle every 'trigger' pixels
            {
                if (enable)
                    enable = 0;
                else
                    enable = 1;
            }

            count++;
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
    lineBresenham( color, x1, y1, x2, y2 );
}

void drawSolidLine(long color, int x1, int y1, int x2, int y2)
{
    lineBresenham( color, x1, y1, x2, y2 );
//    lineSimple( color, x1, y1, x2, y2 );
}

void drawDashedLine(long color, int x1, int y1, int x2, int y2)
{
    lineBresenhamDashed( LINE_DASHED, color, x1, y1, x2, y2 );
}

void drawDottedLine(long color, int x1, int y1, int x2, int y2)
{
    lineBresenhamDashed( LINE_DOTTED, color, x1, y1, x2, y2 );
}

//////////////////////////////////////////////////////////////////////////////
// box drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawRect(long color, int tlx, int tly, int width, int height)
{
    drawSolidLine(color, tlx,      tly,        tlx+width,tly );
    drawSolidLine(color, tlx+width,tly,        tlx+width,tly+height );
    drawSolidLine(color, tlx,      tly+height, tlx+width,tly+height );
    drawSolidLine(color, tlx,      tly,        tlx,      tly+height );
}

void drawSolidRect(long color, int tlx, int tly, int width, int height)
{
    int yy;

    for (yy = tly; yy < (tly+height); yy++)
    {
        lineSimple( color, tlx, yy, tlx+width, yy );
    }
}

void drawShadedRect(long color1, long color2, int tlx, int tly, int width, int height)
{
    float alpha;
    long color;
    int yy;

    for (yy = tly; yy < (tly+height); yy++)
    {
	    alpha = lerpCalcAlpha( tly, tly+height, yy );
	    color = lerpColor32( color1, color2, alpha );
        lineSimple( color, tlx, yy, tlx+width, yy );
    }
}

//////////////////////////////////////////////////////////////////////////////
// triangle drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawTriangle(long color, int x1, int y1, int x2, int y2, int x3, int y3)
{
    drawSolidLine(color, x1,y1, x2,y2 );
    drawSolidLine(color, x2,y2, x3,y3 );
    drawSolidLine(color, x3,y3, x1,y1 );
}

void drawSolidTriangle(long color, int x1, int y1, int x2, int y2, int x3, int y3)
{
    drawTriangle(color, x1,y1, x2,y2, x3,y3 );
}

//////////////////////////////////////////////////////////////////////////////
// polygon drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawPolyline(long color, screenPoint *pointList, int numPoints)
{
    screenPoint p1, p2;
    int i;

    // draw all lines except for closing line
    for (i = 0; i < (numPoints - 1); i++)
    {
	p1.x = pointList[i].x;
	p1.y = pointList[i].y;

	p2.x = pointList[i+1].x;
	p2.y = pointList[i+1].y;

	//printf("i %d - p1 %d,%d p2 %d,%d\n", i, p1.x, p1.y, p2.x, p2.y);

        drawSolidLine(color, p1.x, p1.y, p2.x, p2.y );
    }
}

void drawPolygon(long color, screenPoint *pointList, int numPoints)
{
    screenPoint p1, p2;
    int i;

    // draw all lines except for closing line
    for (i = 0; i < (numPoints - 1); i++)
    {
	p1.x = pointList[i].x;
	p1.y = pointList[i].y;

	p2.x = pointList[i+1].x;
	p2.y = pointList[i+1].y;

	//printf("i %d - p1 %d,%d p2 %d,%d\n", i, p1.x, p1.y, p2.x, p2.y);

        drawSolidLine(color, p1.x, p1.y, p2.x, p2.y );
    }

    // draw closing line
    p1.x = pointList[numPoints-1].x;
    p1.y = pointList[numPoints-1].y;

    p2.x = pointList[0].x;
    p2.y = pointList[0].y;

    //printf("i %d - p1 %d,%d p2 %d,%d\n", 3, p1.x, p1.y, p2.x, p2.y);

    drawSolidLine(color, p1.x, p1.y, p2.x, p2.y );
}

void drawSolidPolygon(long color, screenPoint *pointList, int numPoints)
{
    drawPolygon(color, pointList, numPoints );
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
    circleMidpoint (color, xCenter, yCenter, radius);
}

static void circleFilled (long color, int xCenter, int yCenter, int radius)
{
    int x, y;
    int ysquared;
    int rsquared = radius*radius;

    // kind of brute force but seems fast enough
    for (y = -radius; y <= radius; y++)
    {
        ysquared = y*y;
        for (x = -radius; x <= radius; x++)
        {
            if (x*x + ysquared <= rsquared)
            {
                drawPixel (color, xCenter + x, yCenter + y);
            }
        }
    }
}

void drawSolidCircle (long color, int xCenter, int yCenter, int radius)
{
    circleFilled (color, xCenter, yCenter, radius);
}

//////////////////////////////////////////////////////////////////////////////
// blitter drawing functions
//////////////////////////////////////////////////////////////////////////////

void drawCreateBitBlitBuffer(unsigned short *buffer, int width, int height, int bpp)
{
    // assumes 16 bit Blt
    unsigned short *mapped = NULL;

    switch(bpp)
    {
#if 0
        case 4:
            mapped = (unsigned long *) malloc( width * height * 4 );
            break;
        case 3:
            mapped = (unsigned long *) malloc( width * height * 4 );
            break;
#endif
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
 
    ptr = buffer;

    for (y=0; y<height; y++) 
    {
        for (x=0; x<width; x++) 
        {
            *(ptr++) = color;
        }
    }
}

//***************************************************************************//
// END platform independent section
//***************************************************************************//

/* end of draw-sdl.c */

