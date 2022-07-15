/*****************************************************************************
 *
 *  Audio utility functions.
 *
 *
 *	File:	audioUtils.cpp
 *
 *	Author: Brian Lingard
 *	Date:	02/24/2012
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audioUtils.h"




/*
 *  STATICS
 */



/*
 *  PUBLIC FUNCTIONS
 */

// scale functions

void createScale( Int16 numerator, Int16 denominator, Scale *gain )
{
    gain->Numerator = numerator;
    gain->Denominator = denominator;
}

void copyScale( Scale *in, Scale *out )
{
    out->Numerator = in->Numerator;
    out->Denominator = in->Denominator;
}

// sample functions

void copySample( Sample *in, Sample *out )
{
    out->Left = in->Left;
    out->Right = in->Right;
}

void zeroSample( Sample *out )
{
    out->Left = 0;
    out->Right = 0;
}

void scaleSample( Sample *out, Scale *scale )
{
    Int16 tempLeft, tempRight;

    tempLeft  = (out->Left / scale->Denominator) * scale->Numerator;
    tempRight = (out->Right / scale->Denominator) * scale->Numerator;

    out->Left = tempLeft;
    out->Right = tempRight;
}

// debugging aids

void printSample( char *label, Sample *in )
{
    printf("%s -- Left %04x - Right %04x\n", label, in->Left, in->Right );
}

void setSample( Int16 left, Int16 right, Sample *out )
{
    out->Left = left;
    out->Right = right;
}

/* end of audioUtils.cpp */

