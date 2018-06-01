/*****************************************************************************
 *
 *  Audio mixing functions.
 *
 *
 *	File:	audioMixer.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audioMixer.h"

#include "audioWaveform.h"



/*
 *  STATICS
 */




/*
 *  FUNCTIONS
 */

void MixerCreate(Mixer *mix, Scale *gain1, Scale *gain2)
{
    copyScale( gain1, &mix->gain_in1 );
    copyScale( gain2, &mix->gain_in2 );
    createScale( 1, 1, &mix->gain_out );;
}


void MixerAdd(Mixer *mix, Waveform *in1, Waveform *in2, Waveform *out)
{
    int n;
    CopyWaveform(in1, out);

    if (in1->num_samples == in2->num_samples)
    {
        for (n = 0; n < in1->num_samples; n++)
        {
            out->samples[n].Left  = (in1->samples[n].Left / mix->gain_in1.Denominator) * mix->gain_in1.Numerator
                                        + (in2->samples[n].Left / mix->gain_in2.Denominator) * mix->gain_in2.Numerator;

            out->samples[n].Right = (in1->samples[n].Right / mix->gain_in1.Denominator) * mix->gain_in1.Numerator
                                        + (in2->samples[n].Right / mix->gain_in2.Denominator) * mix->gain_in2.Numerator;
        }
    }
    else
    {
        CopyWaveform(in1, out);
    }
}


/* end of audioMixer.cpp */
