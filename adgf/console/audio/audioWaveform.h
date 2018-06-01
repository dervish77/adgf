/*****************************************************************************
 *
 *  Audio waveform functions.
 *
 *
 *	File:	audioWaveform.h
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#ifndef __audio_waveform_h
#define __audio_waveform_h

#include "audioUtils.h"




/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */

#define SAMPLE_SIZE_BYTE    1
#define SAMPLE_SIZE_WORD    2
#define SAMPLE_SIZE_LONG    4

#define SAMPLE_SIZE	        SAMPLE_SIZE_WORD

#define DEFAULT_AMPLITUDE	255

#define MAX_AMPLITUDE       0x7FFF

#define MAX_SAMPLES         48      // equates to 48000 for the sample rate

#define SAMPLES_PER_CYCLE	48      // for now, a waveform is one cycle

#define DEFAULT_FREQUENCY   1000


/*
 *  STRUCTURES
 */

typedef struct _waveform_t
{
    Int16 amplitude;              // range is -32767 to +32767
    Int16 frequency;              // hertz
    Int16 offset;                 // for now always '0'
    Sample samples[MAX_SAMPLES];  // sample data
    Int16 num_samples;            // number of samples
    Int16 samples_per_cycle;      // allows for multiple cycles per waveform
    Int16 time_per_sample_us;     // time per sample in microseconds
} Waveform;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void GenerateNone(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset);

void GenerateSine(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset);

void GenerateCosine(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset);

void GenerateSquare(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset);

void GenerateRamp(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset);

void GenerateTriangle(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset);

void GenerateRandom(Waveform *wfm, Int16 amplitude, Int16 frequency, Int16 offset);

void DumpWaveform(Waveform *wfm, char *string);

void CopyWaveform(Waveform *src, Waveform *dst);


#endif /* __audio_waveform_h */

