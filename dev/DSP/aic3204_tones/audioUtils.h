/*****************************************************************************
 *
 *  Audio utlity functions.
 *
 *
 *	File:	audioUtils.h
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#ifndef __audio_utils_h
#define __audio_utils_h


#define UNIT_TEST


#ifndef UNIT_TEST
#include "usbstk5515.h"
#endif



/*
 *  CONFIGURATION
 */



/*
 *  CONSTANTS
 */




/*
 *  STRUCTURES
 */

#ifdef UNIT_TEST
typedef long int Int32;
typedef short int Int16;
typedef unsigned short int Uint16;
#endif

typedef struct _long_sample_t
{
    Int16 Left;
    Int16 Right;
} LongSample;

typedef struct _sample_t
{
    Int16 LeftMsw;
    Int16 LeftLsw;
    Int16 RightMsw;
    Int16 RightLsw;
} Sample;

typedef struct _scale_t
{
    Int16 Numerator;
    Int16 Denominator;
} Scale;


/*
 *  STATICS
 */



/*
 *  PROTOTYPES
 */

void copySample( Sample *in, Sample *out );

void copyLongSample( LongSample *in, LongSample *out );

void zeroLongSample( LongSample *out );

void scaleLongSample( LongSample *out, Scale *scale );

void convertSampleToLong( Sample *in, LongSample *out );

void convertLongToSample( LongSample *in, Sample *out );

// debugging aids

void printLongSample( LongSample *in );

void printSample( char *label, Sample *in );

void setSample( Int16 lMsw, Int16 lLsw, Int16 rMsw, Int16 rLsw, Sample *out );

#endif /* __audio_utils_h */

