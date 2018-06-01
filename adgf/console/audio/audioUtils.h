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

typedef struct _sample_t
{
    Int16 Left;
    Int16 Right;
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

// scale functions

void createScale( Int16 numerator, Int16 denominator, Scale *gain );

void copyScale( Scale *in, Scale *out );

// sample functions

void copySample( Sample *in, Sample *out );

void zeroSample( Sample *out );

void scaleSample( Sample *out, Scale *scale );

// debugging aids

void printSample( char *label, Sample *in );

void setSample( Int16 left, Int16 right, Sample *out );

#endif /* __audio_utils_h */

