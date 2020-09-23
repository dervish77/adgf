/*****************************************************************************
 *
 *	Random number routines.
 *
 *  Description:
 *  An interface to random number generation functions.
 *
 *	File:	random.c
 *
 *	Author: Brian Lingard
 *	Date:	07/06/2010
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/* 
 * nrand() 
 *      - normalized rand()
 *      - returns floating point random number between -1.0 and 1.0
 *
 * PARAMETERS
 *	none
 *
 * RETURNS
 *	num     - normalized random number
 *
 */
static float nrand(void)
{
   float num = (float) (2.0*(rand() / (float)RAND_MAX) - 1.0);

   return( num );
}


/* 
 * RandomSetSeed() - set seed for random number generator 
 *
 * PARAMETERS
 *	none
 *
 * RETURNS
 *	none
 *
 */
void RandomSetSeed()
{
   srand((unsigned int)time(NULL));
}


/* 
 * RandomFloat() - scaled floating point random number 
 *
 * PARAMETERS
 *	min_value	- minimum value
 *	max_value	- maximum value
 *
 * RETURNS
 *	float_rand_num	- scaled random number
 *
 */
float RandomFloat(int min_value, int max_value)
{
   float rand_raw, rand_num;
   float float_rand_num;

   /*  get raw random number
    */
   rand_raw = nrand();

   /*  make it positive
    */
   if (rand_raw < 0)
   {
      rand_raw = rand_raw * (-1);
   }
 
   /*  scale by min and max values
    */
   rand_num = ((max_value - min_value) * rand_raw) + min_value;

   /*  convert to integer and output
    */
   float_rand_num = (float) rand_num;

   return(float_rand_num);
}


/* 
 * RandomInteger() - scaled integer random number 
 *
 * PARAMETERS
 *	min_value	- minimum value
 *	max_value	- maximum value
 *
 * RETURNS
 *	int_rand_num	- scaled random number
 *
 */
int RandomInteger(int min_value, int max_value)
{
   float rand_raw, rand_num;
   int int_rand_num;

   /*  get raw random number
    */
   rand_raw = nrand();

   /*  make it positive
    */
   if (rand_raw < 0)
   {
      rand_raw = rand_raw * (-1);
   }
 
   /*  scale by min and max values
    */
   rand_num = ((max_value - min_value) * rand_raw) + min_value;

   /*  convert to integer and output
    */
   int_rand_num = (int) rand_num;

   return(int_rand_num);
}

/* end of random.c */
