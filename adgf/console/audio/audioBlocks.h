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
#include "audioModel.h"


/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */

#define NUM_VOLUME_ENTRIES  (MAX_VOLUME + 1)


/*
 *  STRUCTURES
 */



/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void blockMute( Sample *out );

void blockVolume( Sample *out );

void blockSimpleFIR( Sample *out );

void blockMixer( Sample *in, Scale *inGain, Sample *out, Scale *outGain );

#endif /* __audio_blocks_h */

