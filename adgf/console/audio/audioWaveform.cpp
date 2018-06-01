/*****************************************************************************
 *
 *  Audio waveform functions.
 *
 *
 *	File:	audioWaveform.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "audioWaveform.h"

#include "random.h"



/*
 *  STATICS
 */

static void InitWaveform(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset)
{
    wfm->amplitude = amplitude;
    wfm->frequency = frequency;
    wfm->offset    = offset;

    wfm->num_samples = MAX_SAMPLES;

    wfm->samples_per_cycle = SAMPLES_PER_CYCLE;

    wfm->time_per_sample_us = 21; // based on 48000 sample rate

    memset(wfm->samples, 0, wfm->num_samples * 2 * sizeof(Int16));
}


/*
 *  PUBLIC FUNCTIONS
 */

void GenerateNone(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset)
{
    InitWaveform(wfm, amplitude, frequency, offset);
}

void GenerateSine(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset)
{
    int ii, jj;
    int cycle_offset;
    float value;

    InitWaveform(wfm, amplitude, frequency, offset);

    float two_pi_per_cycle = 2 * 3.14159 / SAMPLES_PER_CYCLE;

    for (jj = 0; jj < (MAX_SAMPLES / SAMPLES_PER_CYCLE); jj++)
    {
        cycle_offset = jj * SAMPLES_PER_CYCLE;

        for (ii = 0; ii < SAMPLES_PER_CYCLE; ii++)
        {
            value = wfm->amplitude * sinf( two_pi_per_cycle * ii ) + wfm->offset;

            wfm->samples[ cycle_offset + ii ].Left  = (Int16) value;
            wfm->samples[ cycle_offset + ii ].Right = (Int16) value;
        }
    }
}


void GenerateCosine(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset)
{
    int ii, jj;
    int cycle_offset;
    float value;

    InitWaveform(wfm, amplitude, frequency, offset);

    float two_pi_per_cycle = 2 * 3.14159 / SAMPLES_PER_CYCLE;

    for (jj = 0; jj < (MAX_SAMPLES / SAMPLES_PER_CYCLE); jj++)
    {
        cycle_offset = jj * SAMPLES_PER_CYCLE;

        for (ii = 0; ii < SAMPLES_PER_CYCLE; ii++)
        {
            value = wfm->amplitude * cosf( two_pi_per_cycle * ii ) + wfm->offset;

            wfm->samples[ cycle_offset + ii ].Left  = (Int16) value;
            wfm->samples[ cycle_offset + ii ].Right = (Int16) value;
        }
    }
}


void GenerateSquare(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset)
{
    int ii, jj;
    int cycle_offset;
    float value;

    InitWaveform(wfm, amplitude, frequency, offset);

    for (jj = 0; jj < (MAX_SAMPLES / SAMPLES_PER_CYCLE); jj++)
    {
        cycle_offset = jj * SAMPLES_PER_CYCLE;

        for (ii = 0; ii < SAMPLES_PER_CYCLE; ii++)
        {
            if (ii <= (SAMPLES_PER_CYCLE/2))
                value = wfm->amplitude + wfm->offset;
            else
                value = -wfm->amplitude + wfm->offset;

            wfm->samples[ cycle_offset + ii ].Left  = (Int16) value;
            wfm->samples[ cycle_offset + ii ].Right = (Int16) value;
        }
    }
}


void GenerateRamp(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset)
{
    int ii, jj;
    int cycle_offset;
    float value, increment, amp;

    InitWaveform(wfm, amplitude, frequency, offset);

    for (jj = 0; jj < (MAX_SAMPLES / SAMPLES_PER_CYCLE); jj++)
    {
        cycle_offset = jj * SAMPLES_PER_CYCLE;

        value = -wfm->amplitude + wfm->offset;

        amp = (float) wfm->amplitude;
        increment = (2 * amp) / SAMPLES_PER_CYCLE;

        for (ii = 0; ii < SAMPLES_PER_CYCLE; ii++)
        {
            wfm->samples[ cycle_offset + ii ].Left  = (Int16) value;
            wfm->samples[ cycle_offset + ii ].Right = (Int16) value;

            value += increment;
        }
    }
}


void GenerateTriangle(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset)
{
    int ii, jj;
    int cycle_offset;
    float value, increment, amp;

    InitWaveform(wfm, amplitude, frequency, offset);

    for (jj = 0; jj < (MAX_SAMPLES / SAMPLES_PER_CYCLE); jj++)
    {
        cycle_offset = jj * SAMPLES_PER_CYCLE;

        value = -wfm->amplitude + wfm->offset;

        amp = (float) wfm->amplitude;
        increment = (2 * amp) / (SAMPLES_PER_CYCLE / 2);

        for (ii = 0; ii < SAMPLES_PER_CYCLE; ii++)
        {
            wfm->samples[ cycle_offset + ii ].Left  = (Int16) value;
            wfm->samples[ cycle_offset + ii ].Right = (Int16) value;

            if (ii <= (SAMPLES_PER_CYCLE / 2))
                value += increment;
            else
                value -= increment;
        }
    }
}


void GenerateRandom(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset)
{
    int ii, jj;
    int cycle_offset;
    float value;

    InitWaveform(wfm, amplitude, frequency, offset);

    RandomSetSeed();

    for (jj = 0; jj < (MAX_SAMPLES / SAMPLES_PER_CYCLE); jj++)
    {
        cycle_offset = jj * SAMPLES_PER_CYCLE;

        for (ii = 0; ii < SAMPLES_PER_CYCLE; ii++)
        {
            value = RandomInteger( -wfm->amplitude, wfm->amplitude ) + wfm->offset;

            wfm->samples[ cycle_offset + ii ].Left  = (Int16) value;
            wfm->samples[ cycle_offset + ii ].Right = (Int16) value;
        }
    }
}


void DumpWaveform(Waveform *wfm, char *string)
{
    int ii;
    int count = 0;

    printf("\nWaveform - %s\n", string);
    printf(" - amplitude = %d\n", wfm->amplitude);
    printf(" - frequency = %d\n", wfm->frequency);
    printf(" - offset    = %d\n", wfm->offset);
    printf(" DATA:\n");

    for (ii = 0; ii < wfm->num_samples; ii++)
    {
        printf(" 0x%08x", wfm->samples[ii].Left);

        if ( count == 7 )
        {
            printf("\n");
            count = 0;
        }
        else
        {
            count++;
        }

    }

    printf(" END\n");
}


void CopyWaveform(Waveform *src, Waveform *dst)
{
    memcpy(dst, src, sizeof(Waveform));
}


/* end of audioWaveform.cpp */

