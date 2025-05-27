/*****************************************************************************
 *
 *	DiagMon monitor main functions
 *
 *	File:	MonMain.c
 *
 *	Author: Brian Lingard
 *	Date:	10/21/2003
 *
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "types.h"
#include "config.h"
#include "video.h"
#include "mon.h"


#define MON_DEBUG




/*
 *  GLOBALS
 */
extern DATABASE_S_T *data;
extern unsigned long mapped_sdram_base;
extern unsigned long mapped_flash_base;


/*
 *  STATICS
 */



/*  MonInit	- initializes monitor data
 *
 *  Parameters:
 *	DATABASE_S_T *mondata	- pointer to mon database
 *
 *  Returns:
 *
 */
void 
MonInit( DATABASE_S_T *mondata )
{
   mondata->board_type = BOARD_ID;
   mondata->cpu_type   = CPU_ID;

   mondata->mbar_base  = MBAR_BASE;
   mondata->mbar_size  = MBAR_SIZE;

   mondata->sdram_base = SDRAM_BASE;
   mondata->sdram_size = SDRAM_SIZE;

   mondata->flash_base = FLASH_BASE;
   mondata->flash_size = FLASH_SIZE;
   mondata->flash_sector = FLASH_SECTOR_SIZE;

   mondata->count = -1;		/* default, loop forever */

#if 0
   mapped_mbar_base = (unsigned long) hw_map_os_memory( 
		(unsigned long long) (MBAR_BASE), (size_t) (MBAR_SIZE) );
   mapped_flash_base = (unsigned long) hw_map_os_memory( 
		(unsigned long long) (FLASH_BASE), (size_t) (FLASH_TEST_SIZE) );
   mapped_sdram_base = (unsigned long) hw_map_os_memory( 
		(unsigned long long) (SDRAM_BASE), (size_t) (SDRAM_TEST_SIZE) );
#endif

}


/*  MonClose	- closes monitor data
 *
 *  Parameters:
 *	DATABASE_S_T *mondata	- pointer to mon database
 *
 *  Returns:
 *
 */
void 
MonClose( DATABASE_S_T *mondata )
{
#if 0
   hw_unmap_os_memory( mapped_mbar_base, (size_t) MBAR_SIZE );
   hw_unmap_os_memory( mapped_flash_base, (size_t) FLASH_TEST_SIZE );
   hw_unmap_os_memory( mapped_sdram_base, (size_t) SDRAM_TEST_SIZE );
#endif
}


/*  MonRun		- runs canned tests
 *
 *  Parameters:
 *	DATABASE_S_T *mondata	- pointer to mon database
 *
 *  Returns:
 *
 */
void 
MonRun( DATABASE_S_T *mondata )
{
   int result;
   int msr;

//   msr = readMSR();
//   printf("msr = %x\n", msr);

#ifdef CFG_ENABLE_PCI_FIND
   result = hw_pciattach_mgt5200(TRUE);
   result = hw_pcifind_mgt5200(TRUE);
   result = hw_pcifind_coralp(TRUE);
#endif

//   post_config();
//   post_run();
}


/*  MonList		- runs list
 *
 *  Parameters:
 *	DATABASE_S_T *mondata	- pointer to mon database
 *
 *  Returns:
 *
 */
void 
MonList( DATABASE_S_T *mondata )
{
//   post_config();
//   post_display_header();
//   post_display_table();
//   post_display_footer();
}


/*  MonConfig		- runs list
 *
 *  Parameters:
 *	DATABASE_S_T *mondata	- pointer to mon database
 *
 *  Returns:
 *
 */
void 
MonConfig( DATABASE_S_T *mondata )
{
//   post_config();
}


/*===========================================================================*/
/*                                                                           */
/* Static Functions                                                          */
/*                                                                           */
/*===========================================================================*/


/* end of MonMain.c */
