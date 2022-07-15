/*****************************************************************************
 *
 *  Audio model interface.
 *
 *
 *	File:	audioModel.h
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#ifndef __audio_model_h
#define __audio_model_h

#include "audioUtils.h"


/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */

#define MAX_VOLUME          10
#define MIN_VOLUME          0

#define DEFAULT_VOLUME      5


/*
 *  STRUCTURES
 */

typedef struct _audio_volume_t
{
    Int16 mute;
    Int16 volume;
    Int16 minVolume;
    Int16 maxVolume;
} AudioVolume;

typedef struct _audio_fir_t
{
    Int16   enable;
    Int16   div1;
    Int16   div2;
    Sample  previousSample;
} AudioFIR;

typedef struct _audio_filter_t
{
    Int16   enable;
    Sample  previousInput;
    Sample  previousOutput;
} AudioFilter;

typedef struct _audio_mixer_t
{
    Int16 enable;
    Scale gain1;
    Scale gain2;
} AudioMixer;

typedef struct _audio_model_t
{
	Int16       enableBypass;
	Int16       bitsPerSample;
	Int16       sampleRateKhz;
	Uint16      samplesPerFrame;
    AudioVolume vol;
    AudioFIR    fir;
    AudioFilter filter;
    AudioMixer  mixer;
    Sample      currentSample;
} AudioModel;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void  AudioSetMute( Int16 mute );
Int16 AudioGetMute( void );

void  AudioSetVolume( Int16 volume );
Int16 AudioGetVolume( void );

void  AudioIncrVolume( void );
void  AudioDecrVolume( void );

void  AudioSetEnableBypass( Int16 enable );
Int16 AudioGetEnableBypass( void );

void  AudioSetEnableFIR( Int16 enable );
Int16 AudioGetEnableFIR( void );

void  AudioSetEnableFilter( Int16 enable );
Int16 AudioGetEnableFilter( void );

#endif /* __audio_model_h */

