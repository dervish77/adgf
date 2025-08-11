/*****************************************************************************
 *
 *	MOS library source code - hw specifc code
 *
 *  NOTE: "hw.c" requires porting to your hardware platform.
 *
 *	File:	hw.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	03/25/2009
 *
 *	Revs:
 *	  0.0 	03/25/2009  originated
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "platform.h"
#include "types.h"



#undef DEBUG



/*
 *  GLOBALS
 */



/*
 *  STATICS
 */




/* =========================================================================================== */
/*  Hardware Initialization - board related                                                    */
/* =========================================================================================== */

/*  hwInitBoard - initializes board level hardware resources 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void hwInitBoard(void)
{

}


/* =========================================================================================== */
/*  Hardware Initialization - timer related                                                    */
/* =========================================================================================== */

/*  hwInitTaskTimer - initializes task timer 
 *
 *  Parameters:
 *	tickTime - timer tick time in microseconds (us)
 *
 *  Returns:
 *	none
 */
void hwInitTaskTimer(int tickTime)
{
    UNUSED(tickTime);

}

/*  hwStartTaskTimer - starts task timer 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void hwStartTaskTimer(void)
{

}

/*  hwCheckTaskTimer - checks task timer 
 *
 *  Parameters:
 *	tickTime - time per tick
 *
 *  Returns:
 *	none
 */
void hwCheckTaskTimer(int tickTime)
{
    // simulate an OS time tick
    usleep(tickTime);
}

/*  hwStopTaskTimer - stops task timer 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void hwStopTaskTimer(void)
{

}


/* =========================================================================================== */
/*  Hardware Initialization - device related                                                   */
/* =========================================================================================== */

/*  hwInitDevice - initializes specified device resources
 *
 *  Parameters:
 *	deviceId - specified device id
 *
 *  Returns:
 *	none
 */
void hwInitDevice(int deviceId)
{
    UNUSED(deviceId);

}

/* end of hw.c */
