/*****************************************************************************
 *
 *  Audio processing functions.
 *
 *  Interface to an audio processing model that processes one sample at a time.
 *
 *
 *	File:	audioCore.h
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#ifndef __audio_core_h
#define __audio_core_h

#include "audioUtils.h"
#include "audioModel.h"
#include "audioFilter.h"
#include "audioMixer.h"
#include "audioWaveform.h"


/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */

 typedef enum _waveform_type_t
 {
     WAVEFORM_NONE = 0,
     WAVEFORM_SINE,
     WAVEFORM_COSINE,
     WAVEFORM_SQUARE,
     WAVEFORM_RAMP,
     WAVEFORM_TRIANGLE,
     WAVEFORM_RANDOM,
     WAVEFORM_PINK,
     WAVEFORM_WHITE
 } WAVEFORM_TYPE;



/*
 *  STRUCTURES
 */



/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void  AudioInit( void );


void  AudioCreateScale( Int16 numerator, Int16 denominator, Scale *gain );


void  AudioCreateSample( Int16 left, Int16 right, Sample *out );

void  AudioProcessSample( Sample *in, Sample *out );

void  AudioProcessMixedSample( Sample *in, Sample *mix, Sample *out );


void  AudioCreateWaveform( WAVEFORM_TYPE type, Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset );

void  AudioProcessWaveform( Waveform *in, Waveform *out );

void  AudioProcessMixedWaveform( Waveform *in, Waveform *mix, Waveform *out );

void  AudioGetWaveformSample( Waveform *wfm, Int16 index, Sample *out );


void  AudioMixerCreate( Mixer *mix, Scale *gain1, Scale *gain2 );

void  AudioMixerAdd( Mixer *mix, Waveform *in1, Waveform *in2, Waveform *out );


#endif /* __audio_core_h */

