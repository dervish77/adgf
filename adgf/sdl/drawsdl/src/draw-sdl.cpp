/*
 *     Module Name:  draw-sdl.cpp
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


#define DEBUG


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


static void localWritePixel(SDL_Surface *theScreen, Uint8 R, Uint8 G, Uint8 B, int x, int y);
static void localReadPixel(SDL_Surface *theScreen, Uint8 *R, Uint8 *G, Uint8 *B, int x, int y);


//////////////////////////////////////////////////////////////////////////////
// color functions
//////////////////////////////////////////////////////////////////////////////

static Uint16 CreateHicolorPixelFromLongColor(SDL_PixelFormat * fmt, long color)
{
    Uint16 value;
    Uint8 red, green, blue, alpha;

    // ignore most significant byte
    alpha = (color & 0xFF000000) >> 24;
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

static long CreateLongColorFromHicolorPixel(SDL_PixelFormat * fmt, Uint16 value)
{
    long color;
    Uint8 red, green, blue, alpha;
    Uint32 temp;

    /* Get Red component */
    temp = value & fmt->Rmask;  /* Isolate red component */
    temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
    red = (Uint8)temp;
    
    /* Get Green component */
    temp = value & fmt->Gmask;  /* Isolate green component */
    temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
    green = (Uint8)temp;
   
    /* Get Blue component */
    temp = value & fmt->Bmask;  /* Isolate blue component */
    temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
    blue = (Uint8)temp;
   
    /* Get Alpha component */
    temp = value & fmt->Amask;  /* Isolate alpha component */
    temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
    temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
    alpha = (Uint8)temp;

//    printf("Pixel Color -> R: %02x,  G: %02x,  B: %02x,  A: %02x\n", red, green, blue, alpha);

    color = (alpha << 24) + (red << 16) + (green << 8) + (blue);

    return color;
}

static Uint16 CreateHicolorPixel(SDL_PixelFormat * fmt, Uint8 red, Uint8 green, Uint8 blue)
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

static void clearPixelCount()
{
     pixelCount = 0;
}

static int getPixelCount()
{
    return(pixelCount);
}

static void Slock(SDL_Surface *theScreen)
{
    if ( SDL_MUSTLOCK(theScreen) )
    {
        if ( SDL_LockSurface(theScreen) < 0 )
        {
            return;
        }
    }
}

static void Sulock(SDL_Surface *theScreen)
{
    if ( SDL_MUSTLOCK(theScreen) )
    {
        SDL_UnlockSurface(theScreen);
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

    clearPixelCount();

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

SDL_Surface *drawGetSpriteScreen(spriteContext *sprite)
{
    return(sprite->image);
}

//////////////////////////////////////////////////////////////////////////////
// full screen functions
//////////////////////////////////////////////////////////////////////////////

void drawBackground(long color)
{
    /* Video memory can be strange, and it's sometimes necessary to
       "lock" it before it can be modified. SDL abstracts this with
       the SDL_LockSurface function. */
    Slock(screen);

    SDL_FillRect(screen, NULL, color);
	   
    pixelCount = screen->w * screen->h;

    /* We're finished drawing, so unlock the surface. */
    Sulock(screen);
}

//////////////////////////////////////////////////////////////////////////////
// pixel functions
//////////////////////////////////////////////////////////////////////////////

static void localWritePixel(SDL_Surface *theScreen, Uint8 R, Uint8 G, Uint8 B, int x, int y)
{
    Uint32 color = SDL_MapRGB(theScreen->format, R, G, B);

    Slock(theScreen);

    switch (theScreen->format->BytesPerPixel) {
        case 1: { /* Assuming 8-bpp */
            Uint8 *bufp;

            bufp = (Uint8 *)theScreen->pixels + y*theScreen->pitch + x;
            *bufp = color;
        }
        break;

        case 2: { /* Probably 15-bpp or 16-bpp */
            Uint16 *bufp;

            bufp = (Uint16 *)theScreen->pixels + y*theScreen->pitch/2 + x;
            *bufp = color;
        }
        break;

        case 3: { /* Slow 24-bpp mode, usually not used */
            Uint8 *bufp;

            bufp = (Uint8 *)theScreen->pixels + y*theScreen->pitch + x;
            *(bufp+screen->format->Rshift/8) = R;
            *(bufp+screen->format->Gshift/8) = G;
            *(bufp+screen->format->Bshift/8) = B;
        }
        break;

        case 4: { /* Probably 32-bpp */
            Uint32 *bufp;

            bufp = (Uint32 *)theScreen->pixels + y*theScreen->pitch/4 + x;
            *bufp = color;
        }
        break;
    }

    Sulock(theScreen);
}

static void localReadPixel(SDL_Surface *theScreen, Uint8 *R, Uint8 *G, Uint8 *B, int x, int y)
{
    Uint32 color = 0;

    Slock(theScreen);

    switch (theScreen->format->BytesPerPixel) {
        case 1: { /* Assuming 8-bpp */
            Uint8 *bufp;

            bufp = (Uint8 *)theScreen->pixels + y*theScreen->pitch + x;
            color = *bufp;
            SDL_GetRGB(color, theScreen->format, R, G, B);
        }
        break;

        case 2: { /* Probably 15-bpp or 16-bpp */
            Uint16 *bufp;

            bufp = (Uint16 *)theScreen->pixels + y*theScreen->pitch/2 + x;
            color = *bufp;
            SDL_GetRGB(color, theScreen->format, R, G, B);
        }
        break;

        case 3: { /* Slow 24-bpp mode, usually not used */
            Uint8 *bufp;

            bufp = (Uint8 *)theScreen->pixels + y*theScreen->pitch + x;
            *R = *(bufp+screen->format->Rshift/8);
            *G = *(bufp+screen->format->Gshift/8);
            *B = *(bufp+screen->format->Bshift/8);
        }
        break;

        case 4: { /* Probably 32-bpp */
            Uint32 *bufp;

            bufp = (Uint32 *)theScreen->pixels + y*theScreen->pitch/4 + x;
            color = *bufp;
            SDL_GetRGB(color, theScreen->format, R, G, B);
        }
        break;
    }

    Sulock(theScreen);
}


void drawPixel(long color, int x, int y)
{   
    drawWritePixel( screen, color, x, y );
}

void drawWritePixel(SDL_Surface *theScreen, long color, int x, int y)
{    
    Uint8 red, green, blue;

    red   = (color & 0x00FF0000) >> 16;
    green = (color & 0x0000FF00) >> 8;
    blue  = (color & 0x000000FF) >> 0;

    if (theScreen)
    {
        localWritePixel( theScreen, red, green, blue, x, y );
    }

    pixelCount++;
}

long drawReadPixel(SDL_Surface *theScreen, int x, int y)
{   
    long color = 0;

    Uint8 red, green, blue;
    Uint32 temp;

    if (theScreen)
    {
        localReadPixel( theScreen, &red, &green, &blue, x, y );
    }   

    temp = red;
    color += temp << 16;
    temp = green;
    color += temp << 8;
    temp = blue;
    color += temp << 0;
    
    if (y == 24) printf("read color %06X\n", color);

    return(color);
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
		
		sprite->half_w = sprite->width / 2;
		sprite->half_h = sprite->height / 2;

        // these are not currently used
        sprite->pitch = sprite->image->pitch;                      // bytes per scanline
        sprite->bpp = (sprite->image->pitch / sprite->width) * 8;  // bits per pixel
        sprite->alphaEnabled = 0;
#ifdef DEBUG
        printf("Loaded sprite %s - w,h,pitch,bpp %d,%d,%d,%d\n", file, sprite->width, sprite->height, sprite->pitch, sprite->bpp);
#endif
    }
}

void drawSaveSprite(spriteContext *sprite, char *file)
{
    if (sprite)
    {
        /* Save the surface into a BMP file */
        if ( sprite->image != NULL ) 
        {
            if ( -1 == SDL_SaveBMP(sprite->image, file) ) {
                fprintf(stderr, "Couldn't save %s: %s\n", file, SDL_GetError());
                return;
            }
        }
    }
}

void drawCreateSprite(spriteContext *sprite, int w, int h)
{
    if (sprite)
    {
        // assume 24 bit image (ala Windows BMP format)
        sprite->image = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,DEPTH_BPP_24,0,0,0,0);
        sprite->width = w;
        sprite->height = h;
        sprite->half_w = w / 2;
        sprite->half_h = h / 2;
        sprite->pitch = (DEPTH_BPP_24 / 8) * w;  // bytes per pixel * width in pixels
        sprite->bpp = DEPTH_BPP_24;              // bits per pixel
        sprite->alphaEnabled = 0;
#ifdef DEBUG
        printf("Created sprite - w,h,pitch,bpp %d,%d,%d,%d\n", sprite->width, sprite->height, sprite->pitch, sprite->bpp);
#endif
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

    image = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,DEPTH_BPP_16,0,0,0,0);

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
    userevent.data1 = param;
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
    userevent.data1 = param;
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
    color = (long) LERP( alpha, color1, color2 );
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
    return(getPixelCount());
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

void drawCreateBitBlitBuffer(unsigned short *buffer, int width, int height, int pitch_bpp)
{
    unsigned long *mapped32 = NULL;
    unsigned long *mapped24 = NULL;
    // assumes 16 bit Blt
    unsigned short *mapped16 = NULL;

    switch(pitch_bpp)
    {
        case PITCH_BPP_32:
            mapped32 = (unsigned long *) malloc( width * height * 4 );
            break;
        case PITCH_BPP_24:
            mapped24 = (unsigned long *) malloc( width * height * 4 );
            break;
        case PITCH_BPP_16:
            mapped16 = (unsigned short *) malloc( width * height * 2 );
            break;   
        default:
            break;    
    }
         
    if (mapped16 == NULL)
    {
        printf("drawCreateBitBlitBuffer: malloc failed\n");
        buffer = NULL;
    }
    else
    {
        printf("drawCreateBitBlitBuffer: buffer created\n");
        buffer = mapped16;
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

/* end of draw-sdl.cpp */

