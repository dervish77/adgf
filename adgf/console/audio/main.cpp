/*****************************************************************************
 *
 *  AudioDemo main program.
 *
 *  Description:
 *      AudioDemo using Audio Processing Library
 *
 *	File:	main.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#include "audioCore.h"


/*
 *  STATICS
 */




/*
 *  FUNCTIONS
 */

void ExecuteSampleSim(int mode)
{
    Sample testSample;
    Sample mixSample;
    Sample outSample;

    printf("\nSample TEST:\n\n");

    AudioInit();

    AudioCreateSample( 35, 27, &testSample );
    printSample( "initial         ", &testSample );

    AudioSetVolume( 5 );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed nomute", &outSample );

    AudioSetVolume( 5 );
    AudioIncrVolume();
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed incr  ", &outSample );

    AudioSetVolume( 5 );
    AudioDecrVolume();
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed decr  ", &outSample );

    AudioSetMute( 1 );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed mute  ", &outSample );
    AudioSetMute( 0 );

    AudioSetVolume( 1 );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed vol 1 ", &outSample );

    AudioSetVolume( 10 );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed vol 10", &outSample );

    AudioSetEnableFIR( 1 );
    AudioCreateSample( 29, 25, &testSample );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed FIR   ", &outSample );
    AudioCreateSample( 19, 13, &testSample );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed FIR   ", &outSample );
    AudioCreateSample( 17, 29, &testSample );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed FIR   ", &outSample );
    AudioCreateSample( 27, 15, &testSample );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed FIR   ", &outSample );
    AudioCreateSample( 21, 33, &testSample );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed FIR   ", &outSample );

    AudioSetEnableFIR( 0 );
    AudioCreateSample( 39, 17, &testSample );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed no FIR", &outSample );
    AudioCreateSample( 21, 13, &testSample );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed no FIR", &outSample );
    AudioCreateSample( 17, 21, &testSample );
    AudioProcessSample( &testSample, &outSample );
    printSample( "processed no FIR", &outSample );

    AudioCreateSample( 17, 13, &mixSample );
    AudioSetVolume( 10 );
    AudioCreateSample( 35, 27, &testSample );
    AudioProcessMixedSample( &testSample, &mixSample, &outSample );
    printSample( "processed mixed ", &outSample );
    AudioCreateSample( 33, 25, &testSample );
    AudioProcessMixedSample( &testSample, &mixSample, &outSample );
    printSample( "processed mixed ", &outSample );

}

void ExecuteWaveformSim(int mode)
{
    Waveform test, sineWfm, noiseWfm, mixedWfm;
    Mixer theMixer;
    Sample mixSample;
    Scale theScale;

    printf("\nWaveform TEST:\n");

    AudioInit();

    AudioCreateWaveform( WAVEFORM_SINE, &test, 0x7fff, 1000, 0 );
    DumpWaveform( &test, "sine" );

    AudioCreateWaveform( WAVEFORM_SQUARE, &test, 0xff, 1000, 0 );
    DumpWaveform( &test, "square" );

    AudioCreateWaveform( WAVEFORM_RAMP, &test, 0xff, 1000, 0 );
    DumpWaveform( &test, "ramp" );

    AudioCreateWaveform( WAVEFORM_TRIANGLE, &test, 0xff, 1000, 0 );
    DumpWaveform( &test, "triangle" );

    AudioCreateWaveform( WAVEFORM_RANDOM, &test, 0x7fff, 1000, 0 );
    DumpWaveform( &test, "random" );

    AudioCreateWaveform( WAVEFORM_SINE, &sineWfm, 0x7fff, 1000, 0 );
    AudioCreateWaveform( WAVEFORM_RANDOM, &noiseWfm, 0x7fff, 1000, 0 );
    AudioCreateScale( 1, 2, &theScale );
    AudioMixerCreate( &theMixer, &theScale, &theScale );
    AudioMixerAdd( &theMixer, &sineWfm, &noiseWfm, &mixedWfm );
    DumpWaveform( &mixedWfm, "mixed" );

    AudioGetWaveformSample( &mixedWfm, 0, &mixSample );
    printSample( "mixed 0", &mixSample );

}


void ExecuteFilterSim(int mode)
{
    Waveform sineWfm, noiseWfm, mixedWfm, filteredWfm;
    Mixer theMixer;
    Scale theScale;
    Filter theFilter;

    printf("\nFilter TEST:\n");

    AudioInit();
    AudioSetEnableFilter( 1 );

    AudioCreateWaveform( WAVEFORM_SINE, &sineWfm, 0x3FF, 1000, 0 );
    DumpWaveform( &sineWfm, "sine" );

    AudioCreateWaveform( WAVEFORM_RANDOM, &noiseWfm, 0x3F, 1000, 0 );
    DumpWaveform( &noiseWfm, "noise" );

    AudioCreateScale( 1, 1, &theScale );
    AudioMixerCreate( &theMixer, &theScale, &theScale );
    AudioMixerAdd( &theMixer, &sineWfm, &noiseWfm, &mixedWfm );
    DumpWaveform( &mixedWfm, "mixed" );

    AudioCreateWaveform( WAVEFORM_NONE, &filteredWfm, 0x3FF, 1000, 0 );
    FilterCreateLowPass( &theFilter, 100, 0.1, sineWfm.time_per_sample_us );
    FilterWaveformLowPass( &theFilter, &mixedWfm, &filteredWfm );
    DumpWaveform( &filteredWfm, "low filtered" );

    AudioCreateWaveform( WAVEFORM_NONE, &filteredWfm, 0x3FF, 1000, 0 );
    FilterCreateHighPass( &theFilter, 100, 0.1, sineWfm.time_per_sample_us );
    FilterWaveformHighPass( &theFilter, &mixedWfm, &filteredWfm );
    DumpWaveform( &filteredWfm, "high filtered" );

}

void Demo(int mode)
{
    // BEGIN DEMO HERE //

    int done = 0;
    while (!done)
    {
        switch(mode)
        {
            case MODE_ALL:
                ExecuteSampleSim( mode );
                printf("\n");
                ExecuteWaveformSim( mode );
                printf("\n");
                ExecuteFilterSim( mode );
                done = 1;
                break;
            case MODE_SAMPLE:
                ExecuteSampleSim( mode );
                done = 1;
                break;
            case MODE_WAVEFORM:
                ExecuteWaveformSim( mode );
                done = 1;
                break;
            case MODE_FILTER:
                ExecuteFilterSim( mode );
                done = 1;
                break;
            default:
                break;
        }
    }

    printf("\n");

    // END DEMO HERE //
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
    int mode = MODE_ALL;
    int play = 1;
    int i;


    // if no command line arguments
    switch (argc)
    {
        case 1:
            PrintBanner();
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
                        case 'f':
                            mode = MODE_FILTER;
                            break;
                        case 's':
                            mode = MODE_SAMPLE;
                            break;
                        case 'w':
                            mode = MODE_WAVEFORM;
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
        Demo(mode);
    }

    exit(0);
}

void PrintBanner()
{
    printf("******************************************************\n");
    printf("             Welcome to AudioDemo %s\n", VERSION);
    printf("******************************************************\n");
}

void PrintUsage()
{
    printf("Usage:  audiodemo [-f|-s|-w] [-h] [-v]\n");
    printf("\n");
    printf("   -h           display help\n");
    printf("   -v           display version\n");
    printf("\n");
    printf("   -f           run audio filter test\n");
    printf("   -s           run audio sample test\n");
    printf("   -w           run audio waveform test\n");
    printf("\n");
}

/* end of main.c */
