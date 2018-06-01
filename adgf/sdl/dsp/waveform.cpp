/*****************************************************************************
 *
 *  Waveform generation functions.
 *
 *
 *	File:	waveform.cpp
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "waveform.h"

#include "random.h"



/*
 *  STATICS
 */

static void InitWaveform(Waveform *wfm, int amplitude, int frequency, int offset)
{
    int ii;

    wfm->amplitude = amplitude;
    wfm->frequency = frequency;
    wfm->offset = offset;

    wfm->num_samples = MAX_SAMPLES;

    wfm->time_per_sample = 0.001;

    for (ii = 0; ii < wfm->num_samples; ii++)
    {
        wfm->samples[ii] = 0;
    }
}


/*
 *  FUNCTIONS
 */

void GenerateEmpty(Waveform *wfm, int amplitude, int frequency, int offset)
{
    InitWaveform(wfm, amplitude, frequency, offset);
}

void GenerateSine(Waveform *wfm, int amplitude, int frequency, int offset)
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

            wfm->samples[ cycle_offset + ii ] = (int) value;
        }
    }
}


void GenerateCosine(Waveform *wfm, int amplitude, int frequency, int offset)
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

            wfm->samples[ cycle_offset + ii ] = (int) value;
        }
    }
}


void GenerateSquare(Waveform *wfm, int amplitude, int frequency, int offset)
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

            wfm->samples[ cycle_offset + ii ] = (int) value;
        }
    }
}


void GenerateRamp(Waveform *wfm, int amplitude, int frequency, int offset)
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
            wfm->samples[ cycle_offset + ii ] = (int) value;

            value += increment;
        }
    }
}


void GenerateTriangle(Waveform *wfm, int amplitude, int frequency, int offset)
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
            wfm->samples[ cycle_offset + ii ] = (int) value;

            if (ii <= (SAMPLES_PER_CYCLE / 2))
                value += increment;
            else
                value -= increment;
        }
    }
}


void GenerateRandom(Waveform *wfm, int amplitude, int frequency, int offset)
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
            value = RandomInteger( -wfm->amplitude, wfm->amplitude ) + wfm->offset;

            wfm->samples[ cycle_offset + ii ] = (int) value;
        }
    }
}


void DumpWaveform(Waveform *wfm, char *string)
{
    int ii;

    printf("Waveform - %s\n", string);
    printf(" - amplitude = %d\n", wfm->amplitude);
    printf(" - frequency = %d\n", wfm->frequency);
    printf(" - offset    = %d\n", wfm->offset);
    printf(" DATA:\n");

    for (ii = 0; ii < wfm->num_samples; ii++)
    {
        printf(" %d\n", wfm->samples[ii]);
    }

    printf(" END\n");
}


void CopyWaveform(Waveform *src, Waveform *dst)
{
    memcpy(dst, src, sizeof(Waveform));
}


/* end of waveform.cpp */
