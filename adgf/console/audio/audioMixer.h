/*****************************************************************************
 *
 *  Audio mixing functions.
 *
 *
 *	File:	audioMixer.h
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#ifndef __audio_mixer_h
#define __audio_mixer_h

#include "audioWaveform.h"



/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */




/*
 *  STRUCTURES
 */

typedef struct _mixer_t
{
    Scale gain_in1;
    Scale gain_in2;
    Scale gain_out;
} Mixer;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void MixerCreate(Mixer *mix, Scale *gain1, Scale *gain2);

void MixerAdd(Mixer *mix, Waveform *in1, Waveform *in2, Waveform *out);


#endif /* __audio_mixer_h */

