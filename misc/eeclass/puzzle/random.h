/************************************************************************
* File:		random.h 			  			*
*							  		*
* Description:	random number functions 				*
*									*
* Revision:	1.0 	originated			2/6/94		*
*									*
*************************************************************************/

/* NOTE:  must include <math.h>,<time.h>,<stdlib.h> in calling file */
#define RDEBUG 0
#define MAXINT 32767

/* global variable to count how many times this routine gets called */
int myrandomcnt;

void myrandominit()
{
  myrandomcnt = 0;
}

short int myrandom(maxnum)	/* returns random number 0 to maxnum-1 */
    int maxnum;
{
  short int inum;	/* integer random number */
  double dnum;	/* random number 0.0 up to 1.0 */
  long seednum; /* 32-bit seed value */

/* set new seed to current time */
  seednum = (long) time((long int *) 0);
  seednum = seednum + myrandomcnt;	/* ensures more randomness */
if (RDEBUG==1) printf("seednum is %d",seednum);
  srand(seednum);

/* get random number 0 to MAXINT */
  inum = rand();
if (RDEBUG==1) printf("   inum is %d\n",inum);

/* scale from 0.0 to 1.0 */
  dnum = (double) inum / MAXINT;
  if (dnum < 0.0)		/* if number is negative */
	dnum = dnum * -1;	/* change it to positive*/

/* limit number to 0 to maxnum-1 */
  inum = maxnum * dnum;

  myrandomcnt++; /* incr count of how many times this routine gets called */

  return inum;
}
