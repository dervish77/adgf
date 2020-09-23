/*****************************************************************************
 *
 *	Random number routines.
 *
 *  Description:
 *  An interface to random number generation functions.
 *
 *	File:	random.h
 *
 *	Author: Brian Lingard
 *	Date:	07/06/2010
 *
 *
 *****************************************************************************/

#ifndef __random_h
#define __random_h



/*
 *  CONSTANTS
 */

#ifndef RAND_MAX
#define RAND_MAX 32767
#endif


/*
 *  STRUCTURES
 */



/*
 *  PROTOTYPES
 */

void RandomSetSeed();

float RandomFloat(int min_value, int max_value);

int RandomInteger(int min_value, int max_value);


/*
 *  STATICS
 */

float nrand(void);


#endif /* __random_h */

