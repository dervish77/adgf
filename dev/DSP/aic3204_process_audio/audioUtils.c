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

void copySample( Sample *in, Sample *out )
{
    out->LeftMsw = in->LeftMsw;
    out->LeftLsw = in->LeftLsw;
    out->RightMsw = in->RightMsw;
    out->RightLsw = in->RightLsw;
}

void copyLongSample( LongSample *in, LongSample *out )
{
    out->Left = in->Left;
    out->Right = in->Right;
}

void zeroLongSample( LongSample *out )
{
    out->Left = 0;
    out->Right = 0;
}

void scaleLongSample( LongSample *out, Scale *scale )
{
    Int16 tempLeft, tempRight;

    tempLeft  = (out->Left / scale->Denominator) * scale->Numerator;
    tempRight = (out->Right / scale->Denominator) * scale->Numerator;

    out->Left = tempLeft;
    out->Right = tempRight;
}

void convertSampleToLong( Sample *in, LongSample *out )
{
//    out->Left  = (in->LeftMsw << 16) + in->LeftLsw;
//    out->Right = (in->RightMsw << 16) + in->RightLsw;
    out->Left  = in->LeftMsw;
    out->Right = in->RightMsw;
}

void convertLongToSample( LongSample *in, Sample *out )
{
//    out->LeftMsw  = (Int16) (in->Left >> 16) & 0x0000FFFF;
//    out->LeftLsw  = (Int16) (in->Left) & 0x0000FFFF;

//    out->RightMsw  = (Int16) (in->Right >> 16) & 0x0000FFFF;
//    out->RightLsw  = (Int16) (in->Right) & 0x0000FFFF;

    out->LeftMsw  = in->Left;
    out->LeftLsw  = 0;

    out->RightMsw  = in->Right;
    out->RightLsw  = 0;
}

// debugging aids

void printLongSample( LongSample *in )
{
    printf("left %d - right %d\n", in->Left, in->Right );
}

void printSample( char *label, Sample *in )
{
    printf("%s -- Left %04x - Right %04x\n", label, in->LeftMsw, in->RightMsw );
}

void setSample( Int16 lMsw, Int16 lLsw, Int16 rMsw, Int16 rLsw, Sample *out )
{
    out->LeftMsw = lMsw;
    out->LeftLsw = lLsw;
    out->RightMsw = rMsw;
    out->RightLsw = rLsw;
}

/* end of audioUtils.cpp */

