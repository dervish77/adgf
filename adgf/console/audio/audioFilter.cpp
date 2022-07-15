/*****************************************************************************
 *
 *  Audio filtering functions.
 *
 *
 *	File:	audioFilter.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audioFilter.h"

#include "audioModel.h"

#include "audioWaveform.h"



/*
 *  STATICS
 */

extern AudioModel audioModel;



/*
 *  FUNCTIONS
 */

void FilterCreateLowPass(Filter *config, float R, float C, float dt)
{
    config->R = R;
    config->C = C;

    config->tau = config->R * config->C;

    config->alpha = dt / ( config->tau + dt );

    config->type = FILTER_LOW_PASS;
}

void FilterCreateHighPass(Filter *config, float R, float C, float dt)
{
    config->R = R;
    config->C = C;

    config->tau = config->R * config->C;

    config->alpha = config->tau / ( config->tau + dt );

    config->type = FILTER_HIGH_PASS;
}


#if 0
 // Return RC low-pass filter output samples, given input samples,
 // time interval dt, and time constant RC
 function lowpass(real[0..n] x, real dt, real RC)
   var real[0..n] y
   var real a := dt / (RC + dt)
   y[0] := x[0]
   for i from 1 to n
       y[i] := a * x[i] + (1-a) * y[i-1]
   return y

The loop which calculates each of the n outputs can be refactored into the equivalent:

   for i from 1 to n
       y[i] := y[i-1] + a * (x[i] - y[i-1])
#endif

void FilterSampleLowPass(Filter *config, Sample *in, Sample *out)
{
    if ( audioModel.filter.enable )
    {
        // filter left sample
        out->Left = audioModel.filter.previousOutput.Left + config->alpha * (in->Left - audioModel.filter.previousOutput.Left);

        // filter right sample
        out->Right = audioModel.filter.previousOutput.Right + config->alpha * (in->Right - audioModel.filter.previousOutput.Right);

        // save previous output for next pass
        copySample( out, &audioModel.filter.previousOutput );
    }
    else
    {
        copySample( in, out );
    }
}

void FilterWaveformLowPass(Filter *config, Waveform *in, Waveform *out)
{
    int ii;

    if ( in->num_samples == out->num_samples )
    {
        for (ii = 0; ii < in->num_samples; ii++)
        {
            FilterSampleLowPass( config, &in->samples[ii], &out->samples[ii] );
        }
    }
}


#if 0
 // Return RC high-pass filter output samples, given input samples,
 // time interval dt, and time constant RC
 function highpass(real[0..n] x, real dt, real RC)
   var real[0..n] y
   var real a := RC / (RC + dt)
   y[0] := x[0]
   for i from 1 to n
     y[i] := a * y[i-1] + a * (x[i] - x[i-1])
   return y

The loop which calculates each of the n outputs can be refactored into the equivalent:

   for i from 1 to n
     y[i] := a * (y[i-1] + x[i] - x[i-1])
#endif

void FilterSampleHighPass(Filter *config, Sample *in, Sample *out)
{
    if ( audioModel.filter.enable )
    {
        // filter left sample
        out->Left = config->alpha * ( audioModel.filter.previousOutput.Left + in->Left - audioModel.filter.previousInput.Left );

        // filter right sample
        out->Right = config->alpha * ( audioModel.filter.previousOutput.Right + in->Right - audioModel.filter.previousInput.Right );

        // save previous input and output for next pass
        copySample( in, &audioModel.filter.previousInput );
        copySample( out, &audioModel.filter.previousOutput );
    }
    else
    {
        copySample( in, out );
    }
}

void FilterWaveformHighPass(Filter *config, Waveform *in, Waveform *out)
{
    int ii;

    if ( in->num_samples == out->num_samples )
    {
        for (ii = 0; ii < in->num_samples; ii++)
        {
            FilterSampleHighPass( config, &in->samples[ii], &out->samples[ii] );
        }
    }
}


/* end of filter.cpp */
