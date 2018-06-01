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
#include "audioBlocks.h"


/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */



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

void  AudioProcessSample( Sample *in, Sample *out );

void  AudioProcessMixedSample( Sample *in, Sample *mix, Sample *out );


#endif /* __audio_core_h */

