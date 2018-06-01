/*****************************************************************************
 *
 *  Audio block functions.
 *
 *
 *	File:	audioBlocks.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audioBlocks.h"
#include "audioModel.h"




/*
 *  STATICS
 */

extern AudioModel audioModel;

static Scale volumeTable[NUM_VOLUME_ENTRIES] =
{
	{  0, 10 },
	{  1, 10 },
	{  2, 10 },
	{  3, 10 },
	{  4, 10 },
	{  5, 10 },
	{  6, 10 },
	{  7, 10 },
	{  8, 10 },
	{  9, 10 },
	{ 10, 10 }
};


/*
 *  PUBLIC FUNCTIONS
 */

void blockMute( Sample *out )
{
	// if we're muted, then output zeros
    if (audioModel.vol.mute)
    {
        zeroSample( out );
    }
}

void blockVolume( Sample *out )
{
    // apply gain scale for current volume
    scaleSample( out, &volumeTable[audioModel.vol.volume] );
}

void blockSimpleFIR( Sample *out )
{
    Sample temp;

    //
    // Simple 2-way averaging filter
    //
    // y(n) = 0.5 x(n) + 0.5 x(n-1)
    //

    if (audioModel.fir.enable)
    {
        // compute left Simple FIR
        temp.Left = (out->Left / audioModel.fir.div1) + (audioModel.fir.previousSample.Left / audioModel.fir.div2);

        // compute right Simple FIR
        temp.Right = (out->Right / audioModel.fir.div1) + (audioModel.fir.previousSample.Right / audioModel.fir.div2);

        // save current sample for next iteration
        copySample( out, &audioModel.fir.previousSample );

        // output processed sample
        copySample( &temp, out );
    }
    else
    {
        // save current sample for next iteration
        copySample( out, &audioModel.fir.previousSample );
    }
}

void blockMixer( Sample *in, Scale *inGain, Sample *out, Scale *outGain )
{
    Sample temp1, temp2;

    //
    // Simple 2-way mixer - mixes in with out producing new out
    //
    // y(n) = gain1 * x1(n) + gain2 * x2(n)
    //

    if (audioModel.mixer.enable)
    {
        // apply gain1 to x1(n)
        copySample( in, &temp1 );
        scaleSample( &temp1, inGain );

        // apply gain2 to x2(n)
        copySample( out, &temp2 );
        scaleSample( &temp2, outGain );

        // mix left samples
        out->Left = temp1.Left + temp2.Left;

        // mix right samples
        out->Right = temp1.Right + temp2.Right;
    }
}


/* end of audioBlocks.cpp */

