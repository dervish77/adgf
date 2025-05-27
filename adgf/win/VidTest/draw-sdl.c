/*
 *     Module Name:  draw-sdl.c
 *
 *     Author:       Brian Lingard (adapted for diags use)
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

#include "config.h"

#include "draw.h"


//////////////////////////////////////////////////////////////////////////////
// globals
//////////////////////////////////////////////////////////////////////////////

int display_w;
int display_h;
int display_bpp;

SDL_Surface *screen;

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
//  printf("drawCreateColor32: created 0x%08x\n", (unsigned int) color);
  return(color);
}

long drawCreateColor24(char red, char green, char blue)
{
  long color = 0x80000000;
  color = color + (red<<16) + (green<<8) + blue;
//  printf("drawCreateColor24: created 0x%08x\n", (unsigned int) color);
  return(color);
}

unsigned short drawCreateColor16(char red, char green, char blue)
{
  unsigned short color = 0x8000;
  color = CreateHicolorPixel( screen->format, red, green, blue );
//  color = color + ((red&0x1F)<<10) + ((green&0x1F)<<5) + (blue&0x1F);
//  printf("drawCreateColor16: created 0x%04x\n", color);
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

void drawWait(int milliseconds)
{
    SDL_Delay(milliseconds);
}

int drawInit(int screen_x, int screen_y, int bpp)
{
    display_w = screen_x;
    display_h = screen_y;
    display_bpp = bpp;

    printf("drawInit: calling SDL_Init...\n");

    /* Initialize SDL's video system and check for errors. */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
	    printf("Unable to initialize SDL: %s\n", SDL_GetError());
	    return(1);
    }

    /* Make sure SDL_Quit gets called when the program exits! */
    atexit(SDL_Quit);

    printf("drawInit: calling SDL_SetVideoMode...\n");

    /* Attempt to set a 256x256 hicolor (16-bit) video mode.
       This will set some type of 16-bit mode, but we won't
       know which particular pixel format ahead of time. If
       the video card can't handle hicolor modes, SDL will
       emulate it. */
    screen = SDL_SetVideoMode(display_w, display_h, display_bpp, SDL_HWSURFACE|SDL_DOUBLEBUF);
    //screen = SDL_SetVideoMode(display_w, display_h, display_bpp, SDL_SWSURFACE);
    //screen = SDL_SetVideoMode(display_w, display_h, display_bpp, SDL_FULLSCREEN);
    if (screen == NULL) 
    {
	    printf("Unable to set video mode: %s\n", SDL_GetError());
	    return(1);
    }
    
    printf("drawInit: screen size %d x %d\n", display_w, display_h );

    printf("drawInit: done\n");

    return(0);
}

void drawSwapBuffers()
{
//  printf("drawSwapBuffers: swapping\n");
  //usleep(100000);

    /* Inform SDL that the screen has been changed. This is necessary
       because SDL's screen surface is not always the real framebuffer;
       it is sometimes emulated behind the scenes. */
    SDL_UpdateRect(screen, 0, 0, 0, 0);

  //usleep(40000);
//  printf("drawSwapBuffers: done\n");
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

    printf("drawGradient: done\n");
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

//    printf("drawBackground: done\n");
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
    offset = (screen->pitch / 2 * y + x);
    raw_pixels[offset] = pixel_color;

    Sulock(screen);

    pixelCount++;
//    printf("drawPixel: done\n");
}

//////////////////////////////////////////////////////////////////////////////
// bitmap functions
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

//    printf("drawBitmap: image loaded, size is w,h = %d,%d\n", image->w, image->h);

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

//    printf("drawBitmap: done\n");
}

void drawBitBlit(unsigned short *buffer, int tlx, int tly, int width, int height)
{
    // assumes 16 bit Blt
    SDL_Surface *image;
    SDL_Rect dest;

    Uint16 *blit_pixels, *src_buffer;
    int x, y;

    printf("drawBitBlit: drawing blit of size (%dx%d)\n", width, height);

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
            printf("offset = %d\n", offset);
            printf("src_buffer[offset] = 0x%04X\n", src_buffer[offset]);
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
        
    printf("drawBitBlit: done\n");
}

/* end of draw-sdl.c */

