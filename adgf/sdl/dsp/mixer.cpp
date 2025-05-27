/*****************************************************************************
 *
 *  Mixing functions.
 *
 *
 *	File:	mixer.cpp
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mixer.h"

#include "waveform.h"



/*
 *  STATICS
 */




/*
 *  FUNCTIONS
 */

void MixerCreate(Mixer *mix, float gain1, float gain2)
{
    mix->gain_in1 = gain1;
    mix->gain_in2 = gain2;
    mix->gain_out = 1;
}


void MixerAdd(Mixer *mix, Waveform *in1, Waveform *in2, Waveform *out)
{
    int n;
    CopyWaveform(in1, out);

    if (in1->num_samples == in2->num_samples)
    {
        for (n = 0; n < in1->num_samples; n++)
        {
            out->samples[n] = in1->samples[n] * mix->gain_in1 + in2->samples[n] * mix->gain_in2;
        }
    }
    else
    {
        CopyWaveform(in1, out);
    }
}


/* end of mixer.cpp */
