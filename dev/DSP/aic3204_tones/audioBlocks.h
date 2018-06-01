/*****************************************************************************
 *
 *  Audio block functions.
 *
 *
 *	File:	audioBlocks.h
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#ifndef __audio_blocks_h
#define __audio_blocks_h

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

#define NUM_VOLUME_ENTRIES  (MAX_VOLUME + 1)


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
    Int16 enable;
    Int16 div1;
    Int16 div2;
} AudioFIR;

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
    AudioMixer  mixer;
    LongSample  currentLongSample;
    LongSample  previousLongSample;
} AudioModel;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void blockMute( LongSample *out );

void blockVolume( LongSample *out );

void blockSimpleFIR( LongSample *out );

void blockMixer( LongSample *in, Scale *inGain, LongSample *out, Scale *outGain );

#endif /* __audio_blocks_h */

