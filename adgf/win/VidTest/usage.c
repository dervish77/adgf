/*****************************************************************************
 *
 *	DiagMon usage function.
 *
 *	File:	usage.c
 *
 *	Author: Brian Lingard
 *	Date:	10/21/2003
 *
///  BOSE CORPORATION.
///  COPYRIGHT 2004 BOSE CORPORATION ALL RIGHTS RESERVED.
///  This program may not be reproduced, in whole or in part in any form or
///  any means whatsoever without the written permission of:
///     BOSE CORPORATION
///     The Mountain,
///     Framingham, MA 01701-9168.
 *
 *****************************************************************************/
/*****************************************************************************
 *
 *	Usage:	vidtest [-g|-h|-j|-k|-v]
 *
 *		-g <pattern>		display graphics pattern
 *		-h			display help
 *		-j <1|0>		enables/disables video pass-through
 *		-k <scalew> <scaleh>	sets scaling for video pass-through
 *		-v			display version
 *
 * other options:
 *		-a		run all tests in default mode
 *		-d		display list of tests in default mode
 *		-f <s> <e>	flash dump
 *		-h		display help
 *		-i		display info/status
 *		-l <c> #	loop on test number <c> times
 *		-m <s> <e>	memory dump
 *		-p <select>	probe registers <all,ata,cpu,eth,pci,usb>
 *		-s <select>	scan devices <pci,usb>
 *		-t #		execute test number
 *		-v		display version
 *              -x <script>	load and run script file 
 *		-z		reset cpu
 *
 *****************************************************************************/


#include <stdio.h>
#include <string.h>



/*
 *  GLOBALS
 */


/*
 *  STATICS
 */


/*  Usage	- output usage error message and exit 
 *
 *  Parameters:
 *	fp		- file pointer
 *	program		- program name
 *
 *  Returns:
 *	none
 */
void 
Usage( FILE *fp, char *program )
{
   fprintf(fp, "\nUsage: %s [-g|-h|-j|-k|-v]\n", program);
   fprintf(fp, "\n");
   fprintf(fp, "  options:\n");
   fprintf(fp, "    -g <pattern>            display graphics pattern\n");
   fprintf(fp, "    -h                      display help\n");
   fprintf(fp, "    -j <1|0>                enables/disables video pass-through\n");
   fprintf(fp, "    -k <scalew> <scaleh>    sets scaling for video pass-through\n");
   fprintf(fp, "    -v                      display version\n");
   fprintf(fp, "\n");
   fprintf(fp, "  <pattern>\n");
   fprintf(fp, "                0       Edwin's anim demo\n");
   fprintf(fp, "                1       line boxes\n");
   fprintf(fp, "                2       color gradient\n");
   fprintf(fp, "                3       multi shading\n");
   fprintf(fp, "                4       color bars\n");
   fprintf(fp, "                5       cicrles\n");
   fprintf(fp, "                6       horizontal lines\n");
   fprintf(fp, "                7       vertical lines\n");
   fprintf(fp, "                8       blit boxes\n");
   fprintf(fp, "                9       gradient\n");
   fprintf(fp, "                44      crazy lines demo\n");
   fprintf(fp, "                55      crazy boxes demo\n");
   fprintf(fp, "                77      fast loop on patterns\n");
   fprintf(fp, "                88      slow loop on patterns\n");
   fprintf(fp, "                99      clear screen\n");
   fprintf(fp, "\n");
}


/* end of usage.c */
