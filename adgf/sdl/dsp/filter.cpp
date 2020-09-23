/*****************************************************************************
 *
 *  Filtering functions.
 *
 *
 *	File:	filter.cpp
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter.h"

#include "waveform.h"



/*
 *  STATICS
 */




/*
 *  FUNCTIONS
 */

void FilterCreate(Filter *config, float R1, float C1, float R2, float C2)
{
    config->R1 = R1;
    config->C1 = C1;
    config->R2 = R2;
    config->C2 = C2;

    config->tau = config->R1 * config->C1;
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

void FilterLowPass(Filter *config, Waveform *in, Waveform *out)
{
    CopyWaveform(in, out);
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


void FilterHighPass(Filter *config, Waveform *in, Waveform *out)
{
    CopyWaveform(in, out);
}


/* end of filter.cpp */
