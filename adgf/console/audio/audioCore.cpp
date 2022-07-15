/*****************************************************************************
 *
 *  Audio processing functions.
 *
 *  Implemetation of an audio processing model that processes one sample at a time.
 *
 *
 *	File:	audioCore.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audioCore.h"

#include "audioUtils.h"
#include "audioBlocks.h"
#include "audioModel.h"
#include "audioFilter.h"
#include "audioMixer.h"
#include "audioWaveform.h"




/*
 *  STATICS
 */

extern AudioModel audioModel;



/*
 *  PUBLIC FUNCTIONS
 */

void AudioInit( void )
{
	audioModel.enableBypass  = 0;

	audioModel.bitsPerSample   = 16;
	audioModel.sampleRateKhz   = 48;
	audioModel.samplesPerFrame = audioModel.sampleRateKhz * 1000;

    audioModel.vol.mute        = 0;
    audioModel.vol.volume      = DEFAULT_VOLUME;
    audioModel.vol.minVolume   = MIN_VOLUME;
    audioModel.vol.maxVolume   = MAX_VOLUME;

    audioModel.fir.enable      = 0;
    audioModel.fir.div1        = 2;
    audioModel.fir.div2        = 2;
    zeroSample( &audioModel.fir.previousSample );

    audioModel.filter.enable   = 0;
    zeroSample( &audioModel.filter.previousInput );
    zeroSample( &audioModel.filter.previousOutput );

    audioModel.mixer.enable = 1;
    audioModel.mixer.gain1.Numerator   = 1;
    audioModel.mixer.gain1.Denominator = 8;
    audioModel.mixer.gain2.Numerator   = 7;
    audioModel.mixer.gain2.Denominator = 8;

    zeroSample( &audioModel.currentSample );
}

void  AudioCreateScale( Int16 numerator, Int16 denominator, Scale *gain )
{
    createScale( numerator, denominator, gain );
}

//
// Sample functions
//

void  AudioCreateSample( Int16 left, Int16 right, Sample *out )
{
    setSample( left, right, out );
}

void AudioProcessSample( Sample *in, Sample *out )
{
	if (audioModel.enableBypass)
	{
		copySample( in, out );
	}
	else
	{
        // copy unprocessed sample to current sample
        copySample( in, &audioModel.currentSample );

        // process as per our audio pipeline
        blockSimpleFIR( &audioModel.currentSample );

        blockVolume( &audioModel.currentSample );

        blockMute( &audioModel.currentSample );

        // copy processed sample back to output
        copySample( &audioModel.currentSample, out );
	}
}

void AudioProcessMixedSample( Sample *in, Sample *mix, Sample *out )
{
    if (audioModel.enableBypass)
	{
		copySample( in, out );
	}
	else
	{
        // copy unprocessed sample to current sample
        copySample( in, &audioModel.currentSample );

        // process as per our audio pipeline
        blockMixer( mix, &audioModel.mixer.gain1, &audioModel.currentSample, &audioModel.mixer.gain2 );

        blockVolume( &audioModel.currentSample );

        blockMute( &audioModel.currentSample );

        // copy processed sample back to output
        copySample( &audioModel.currentSample, out );
	}
}

//
// Waveform functions
//

void AudioCreateWaveform( WAVEFORM_TYPE type, Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset )
{
    switch(type)
    {
        case WAVEFORM_NONE:
            GenerateNone( wfm, amplitude, frequency, offset );
            break;

        case WAVEFORM_SINE:
            GenerateSine( wfm, amplitude, frequency, offset );
            break;

        case WAVEFORM_COSINE:
            GenerateCosine( wfm, amplitude, frequency, offset );
            break;

        case WAVEFORM_SQUARE:
            GenerateSquare( wfm, amplitude, frequency, offset );
            break;

        case WAVEFORM_RAMP:
            GenerateRamp( wfm, amplitude, frequency, offset );
            break;

        case WAVEFORM_TRIANGLE:
            GenerateTriangle( wfm, amplitude, frequency, offset );
            break;

        case WAVEFORM_RANDOM:
            GenerateRandom( wfm, amplitude, frequency, offset );
            break;

        case WAVEFORM_PINK:
            break;

        case WAVEFORM_WHITE:
            break;

        default:
            break;
    }
}

void AudioProcessWaveform( Waveform *in, Waveform *out )
{
    int ii;

    if (in->num_samples == out->num_samples)
    {
        for (ii = 0; ii < in->num_samples; ii++)
        {
            AudioProcessSample( &in->samples[ii], &out->samples[ii] );
        }
    }
}

void  AudioProcessMixedWaveform( Waveform *in, Waveform *mix, Waveform *out )
{
    int ii;

    if (in->num_samples == out->num_samples && in->num_samples == mix->num_samples)
    {
        for (ii = 0; ii < in->num_samples; ii++)
        {
            AudioProcessMixedSample( &in->samples[ii], &mix->samples[ii], &out->samples[ii] );
        }
    }
}

void AudioGetWaveformSample(Waveform *wfm, Int16 index, Sample *out)
{
    if (index < wfm->num_samples)
    {
        out->Left = wfm->samples[ index ].Left;
        out->Right = wfm->samples[ index ].Right;
    }
}

//
// Mixer functions
//

void  AudioMixerCreate( Mixer *mix, Scale *gain1, Scale *gain2 )
{
    MixerCreate( mix, gain1, gain2 );
}

void  AudioMixerAdd( Mixer *mix, Waveform *in1, Waveform *in2, Waveform *out )
{
    MixerAdd( mix, in1, in2, out );
}


/* end of audioCore.cpp */

