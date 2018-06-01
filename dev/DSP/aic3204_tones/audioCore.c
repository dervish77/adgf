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

    audioModel.vol.mute      = 0;
    audioModel.vol.volume    = DEFAULT_VOLUME;
    audioModel.vol.minVolume = MIN_VOLUME;
    audioModel.vol.maxVolume = MAX_VOLUME;

    audioModel.fir.enable = 0;
    audioModel.fir.div1 = 2;
    audioModel.fir.div2 = 2;

    audioModel.mixer.enable = 1;
    audioModel.mixer.gain1.Numerator   = 1;
    audioModel.mixer.gain1.Denominator = 8;
    audioModel.mixer.gain2.Numerator   = 7;
    audioModel.mixer.gain2.Denominator = 8;

    zeroLongSample( &audioModel.currentLongSample );
    zeroLongSample( &audioModel.previousLongSample );
}

void AudioSetMute( Int16 mute )
{
    audioModel.vol.mute = mute;
}

Int16 AudioGetMute( void )
{
    return audioModel.vol.mute;
}

void AudioSetVolume( Int16 volume )
{
    if (volume > audioModel.vol.maxVolume)
    {
        audioModel.vol.volume = audioModel.vol.maxVolume;
    }
    else if (volume < audioModel.vol.minVolume)
    {
        audioModel.vol.volume = audioModel.vol.minVolume;
    }
    else
    {
        audioModel.vol.volume = volume;
    }
}

Int16 AudioGetVolume( void )
{
    return audioModel.vol.volume;
}

void  AudioIncrVolume( void )
{
    Int16 newVolume = audioModel.vol.volume;
    newVolume++;
    AudioSetVolume( newVolume );
}

void  AudioDecrVolume( void )
{
    Int16 newVolume = audioModel.vol.volume;
    newVolume--;
    AudioSetVolume( newVolume );
}

void  AudioSetEnableBypass( Int16 enable )
{
    audioModel.enableBypass = enable;
}

Int16 AudioGetEnableBypass( void )
{
	return audioModel.enableBypass;
}

void  AudioSetEnableFIR( Int16 enable )
{
    audioModel.fir.enable = enable;
}

Int16 AudioGetEnableFIR( void )
{
	return audioModel.fir.enable;
}

void AudioProcessSample( Sample *in, Sample *out )
{
	if (audioModel.enableBypass)
	{
		copySample( in, out );
	}
	else
	{
        // convert to internal format
        convertSampleToLong( in, &audioModel.currentLongSample );

        // process as per our audio pipeline
        blockSimpleFIR( &audioModel.currentLongSample );

        blockVolume( &audioModel.currentLongSample );

        blockMute( &audioModel.currentLongSample );

        // convert back to external format
        convertLongToSample( &audioModel.currentLongSample, out );
	}
}

void AudioProcessMixedSample( Sample *in, Sample *mix, Sample *out )
{
    LongSample mixLong;

	if (audioModel.enableBypass)
	{
		copySample( in, out );
	}
	else
	{
        // convert to internal format
        convertSampleToLong( in, &audioModel.currentLongSample );
        convertSampleToLong( mix, &mixLong );

        // process as per our audio pipeline
        blockMixer( &mixLong, &audioModel.mixer.gain1, &audioModel.currentLongSample, &audioModel.mixer.gain2 );

        blockVolume( &audioModel.currentLongSample );

        blockMute( &audioModel.currentLongSample );

        // convert back to external format
        convertLongToSample( &audioModel.currentLongSample, out );
	}
}


/* end of audioCore.cpp */

