/*****************************************************************************
 *
 *  Audio model implementation.
 *
 *
 *	File:	audioModel.cpp
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




/*
 *  STATICS
 */

AudioModel audioModel;


/*
 *  PUBLIC FUNCTIONS
 */

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

void  AudioSetEnableFilter( Int16 enable )
{
    audioModel.filter.enable = enable;
}

Int16 AudioGetEnableFilter( void )
{
	return audioModel.filter.enable;
}

/* end of audioModel.cpp */

