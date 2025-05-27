/*****************************************************************************
 *
 *	MOS app test program - tasks
 *
 *	File:	apptasks.cpp
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/31/2003
 *
 *	Revs:
 *	  0.0 	10/31/2003  originated
 *
 *****************************************************************************/

#include "mos.h"

#include "apptasks.h"


static int toggle = 1;


ARG_STRUCT dummyargs = 
{
	1,
	2,
	3
};

// task that just reads its own id
void getid( void *args )
{
   int id;
   ARG_STRUCT *my;
      
   my = (ARG_STRUCT *) args;

   // pretend to do some work
   id = mosGetTaskId( "getid" );
}

// task that toggles state of an LED
void blinktask( void *args )
{
   ARG_STRUCT *my;
      
   my = (ARG_STRUCT *) args;

   if (toggle)
   {
      digitalWrite(13, LOW);
      toggle = 0;
   }
   else
   {
      digitalWrite(13, HIGH);
      toggle = 1;
   }
   
   // delay 200 ms
   mosSleep(200);
}

/* end of apptasks.cpp */
