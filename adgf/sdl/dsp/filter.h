/*****************************************************************************
 *
 *  Filtering functions.
 *
 *
 *	File:	filter.h
 *
 *	Author: Brian Lingard
 *	Date:	06/18/2010
 *
 *
 *****************************************************************************/

#ifndef __filter_h
#define __filter_h

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

typedef struct _filter_t
{
    float R1;
    float C1;
    float R2;
    float C2;
    float tau;		// time constant = R1 * C1
} Filter;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void FilterCreate(Filter *config, float R1, float C1, float R2, float C2);

void FilterLowPass(Filter *config, Waveform *in, Waveform *out);

void FilterHighPass(Filter *config, Waveform *in, Waveform *out);



#endif /* __filter_h */

