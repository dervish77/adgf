/*****************************************************************************
 *
 *  Waveform generation functions.
 *
 *
 *	File:	waveform.h
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#ifndef __waveform_h
#define __waveform_h



/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */

#define SAMPLE_SIZE_BYTE	1
#define SAMPLE_SIZE_WORD	2
#define SAMPLE_SIZE_LONG	4

#define SAMPLE_SIZE	SAMPLE_SIZE_BYTE

#define DEFAULT_AMPLITUDE   100

#define MAX_SAMPLES         1024

#define SAMPLES_PER_CYCLE   256


/*
 *  STRUCTURES
 */

typedef struct _waveform_t
{
    int amplitude;
    int frequency;
    int offset;
    int samples[MAX_SAMPLES];   // sample data
    int num_samples;            // number of samples
    float time_per_sample;      // time per sample in seconds
} Waveform;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void GenerateEmpty(Waveform *wfm, int amplitude, int frequency, int offset);

void GenerateSine(Waveform *wfm, int amplitude, int frequency, int offset);

void GenerateCosine(Waveform *wfm, int amplitude, int frequency, int offset);

void GenerateSquare(Waveform *wfm, int amplitude, int frequency, int offset);

void GenerateRamp(Waveform *wfm, int amplitude, int frequency, int offset);

void GenerateTriangle(Waveform *wfm, int amplitude, int frequency, int offset);

void GenerateRandom(Waveform *wfm, int amplitude, int frequency, int offset);

void DumpWaveform(Waveform *wfm, char *string);

void CopyWaveform(Waveform *src, Waveform *dst);


#endif /* __waveform_h */

