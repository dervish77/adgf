/*****************************************************************************
 *
 *  Audio filtering functions.
 *
 *
 *	File:	audioFilter.h
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#ifndef __audio_filter_h
#define __audio_filter_h

#include "audioWaveform.h"



/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */

typedef enum _filter_type_t
{
    FILTER_NONE,
    FILTER_LOW_PASS,
    FILTER_HIGH_PASS
} FILTER_TYPE;


/*
 *  STRUCTURES
 */

typedef struct _filter_t
{
    float       R;
    float       C;
    float       tau;      // time constant = R * C
    float       alpha;    // filter dependent gain
    FILTER_TYPE type;
} Filter;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void FilterCreateLowPass(Filter *config, float R, float C, float dt);

void FilterCreateHighPass(Filter *config, float R, float C, float dt);


void FilterSampleLowPass(Filter *config, Sample *in, Sample *out);

void FilterSampleHighPass(Filter *config, Sample *in, Sample *out);


void FilterWaveformLowPass(Filter *config, Waveform *in, Waveform *out);

void FilterWaveformHighPass(Filter *config, Waveform *in, Waveform *out);



#endif /* __audio_filter_h */

