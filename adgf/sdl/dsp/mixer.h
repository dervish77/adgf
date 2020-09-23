/*****************************************************************************
 *
 *  Mixing functions.
 *
 *
 *	File:	mixer.h
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#ifndef __mixer_h
#define __mixer_h

#include "waveform.h"



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
    float gain_in1;
    float gain_in2;
    float gain_out;
} Mixer;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void MixerCreate(Mixer *mix, float gain1, float gain2);

void MixerAdd(Mixer *mix, Waveform *in1, Waveform *in2, Waveform *out);




#endif /* __mixer_h */

