/********************************************************************

   Instruction table for 8085.

   Author:    Brian Lingard

   File:      instr.c
 
   Revision History:
     0.0  12/04/96  originated

*********************************************************************/

#include <stdio.h>
#include "dev8085.h"


/*
 *  Declare table of 8085 instructions
 */

INSTR_ENTRY_S_T instruction_table[] = 
{
	0x00, "LDA       ", AM_IMMEDIATE, TRUE,
	0x01, "STA       ", AM_IMMEDIATE, TRUE
};

