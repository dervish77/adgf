/*****************************************************************************
 *
 *  DspDemo main program.
 *
 *  Description:
 *      DspDemo using LibSDL.
 *
 *	File:	main.cpp
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#include "waveform.h"

#include "filter.h"

#include "mixer.h"



/*
 *  STATICS
 */




/*
 *  FUNCTIONS
 */

void DrawWaveform(Waveform *wfm, long color)
{
    int ii;
    int x, y;

    int scaled;

    int w, h;    // screen width and height

    w = drawGetWidth();
    h = drawGetHeight();

    int fullscale = h/2 - 100;

    for (ii = 0; ii < wfm->num_samples; ii++)
    {
        x = ii;

        scaled = fullscale * wfm->samples[ii] / DEFAULT_AMPLITUDE;

        y = h/2 - scaled;

        //printf("scaled x,y %d %d,%d\n", scaled, x, y);

        drawPixel(color, x, y);
    }
}


void ResetSim(Waveform *wfm)
{
    Waveform base;

    // create base waveform
    GenerateSine(&base, 50, 10, 0);
//    GenerateCosine(&base, 50, 10, 0);
//    GenerateSquare(&base, 50, 10, 0);
//    GenerateRamp(&base, 50, 10, 0);
//    GenerateTriangle(&base, 50, 10, 0);
//    GenerateRandom(&base, 20, 10, 0);

    // create secondary waveform
    Waveform noise;
    GenerateRandom(&noise, 10, 10, 0);
//    GenerateEmpty(&noise, 10, 10, 0);

    // mix secondary with base waveform
    Mixer theMixer;
    MixerCreate(&theMixer, 1, 1);
    MixerAdd(&theMixer, &base, &noise, wfm);

    DumpWaveform(wfm, "testing");

    drawBackground(CLR_BLACK);
    drawSwapBuffers();
}


void ExecuteSim(Waveform *wfm, int mode)
{
    int w, h;    // screen width and height

    w = drawGetWidth();
    h = drawGetHeight();

    Filter theFilter;
    Waveform filtered;

    switch (mode)
    {
        case MODE_NONE:
	    drawLine(CLR_WHITE, 0, h/2, w, h/2);
	    DrawWaveform(wfm, CLR_GREEN);
	    break;
	case MODE_LOWPASS:
	    drawLine(CLR_WHITE, 0, h/2, w, h/2);
	    DrawWaveform(wfm, CLR_GREEN);
	    FilterCreate(&theFilter, 100, 100, 0, 0);
	    FilterLowPass(&theFilter, wfm, &filtered);
	    DrawWaveform(&filtered, CLR_BLUE);
	    break;
	case MODE_HIGHPASS:
	    drawLine(CLR_WHITE, 0, h/2, w, h/2);
	    DrawWaveform(wfm, CLR_GREEN);
	    FilterCreate(&theFilter, 100, 100, 0, 0);
	    FilterLowPass(&theFilter, wfm, &filtered);
	    DrawWaveform(&filtered, CLR_RED);
        break;
	default:
	    break;
    }

    drawSwapBuffers();
}


void Demo()
{
    int w, h;    // screen width and height

    // show key menu before opening drawing screen
    printf("Key commands:\n");
    printf(" h  - mode high pass\n");
    printf(" l  - mode low pass\n");
    printf(" n  - mode none\n");
    printf(" r  - reset sim\n");
    printf(" s  - execute sim\n");
    printf(" x  - clear screen\n");
    printf(" q  - quit\n");
    printf("\n");
    drawWait(1000);

    // initialize the drawing package
    drawInitExtended(WIDTH, HEIGHT, BPP, "DspDemo");

    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // BEGIN DEMO HERE //

    Waveform input;

    ResetSim(&input);

    // handle interactive UI events
    int done = 0;
    char key;
    int x, y;
    int mode = MODE_NONE;
    while (!done)
    {
        switch( drawGetEvent( &x, &y, &key ) )
        {
            case KEY_DOWN:
                switch(key)
                {
                    case 'h':
                        mode = MODE_HIGHPASS;
                        break;
                    case 'l':
                        mode = MODE_LOWPASS;
                        break;
                    case 'n':
                        mode = MODE_NONE;
                        break;
                    case 'r':
                        ResetSim(&input);
                        drawLine(CLR_WHITE, 0, h/2, w, h/2);
                        drawSwapBuffers();
                        break;
                    case 's':
                        ExecuteSim(&input, mode);
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

            case WINDOW_QUIT:
                done = 1;
                break;
        }
    }

    // END DEMO HERE //

    drawQuit();
}


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
    int play = 1;
    int i;


    // if no command line arguments
    switch (argc)
    {
        case 1:
            PrintBanner();
            printf("Let's draw ...\n");
            break;
        case 2:
        case 3:
            i = 1;
            while (i < argc)
            {
                if (argv[i][0] == '-')
                {
                    switch(argv[i][1])
                    {
                        case 'h':
                            PrintUsage();
                            play = 0;
                            break;
                        case 'v':
                            PrintBanner();
                            play = 0;
                            break;
                        default:
                            play = 0;
                            exit(1);
                    }	/* end of inner switch */
                }
                i++;	/* increment arg index */
            }
            break;
        default:
            break;
    }

    if (play)
    {
        Demo();
    }

    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("             Welcome to DspDemo %s\n", VERSION);
    printf("******************************************************\n");
    printf("\nUsing DrawSdl version %s\n\n", drawGetVersion() );
}

void PrintUsage()
{
    printf("Usage:  dspdemo [-h][-v]\n");
    printf("   -h           display help\n");
    printf("   -v           display version\n");
}

/* end of main.c */
