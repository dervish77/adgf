/*****************************************************************************
 *
 *	DiagMon monitor handler functions
 *
 *	File:	MonHandle.c
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


/* used by DumpBlock */
#define DEFAULT_BLOCK_SIZE	    256		/* 256 bytes */
#define DEFAULT_BYTES_PER_ROW	16


/*
 *  GLOBALS
 */
extern DATABASE_S_T *data;
extern unsigned long mapped_sdram_base;
extern unsigned long mapped_flash_base;

/* used by DumpBlock */
BOOLEAN_T	suppress_ascii = FALSE;
int		base = 0;


/*
 *  STATICS
 */
BOOLEAN_T DumpMemBlock(int start, int end, int size, 
	int bytes_per_row, FILE *out_file_p, BOOLEAN_T flash);



/*  MonTestExecute	- execute list of tests 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonTestExecute( int argcount, char *cmdargs[MAX_CMD_ARGS] )
{
   int			i;
   int			testlist[MAX_CMD_ARGS];

   /* clear test list */
   for (i=0; i < MAX_CMD_ARGS; i++)
   {
      testlist[i] = -1;
   }

   /* copy test numbers to test list */
   for (i=1; i < argcount; i++)
   {
      testlist[i-1] = atoi( cmdargs[i] );
   }

   /* if testnum = 0, run all tests */
   if (testlist[0] == 0)
   {
//      post_run();
   }
   else /* else, run list of test numbers */
   {
//      post_execute( &testlist );
   }
}


/*  MonTestLoop	- execute list of tests in a loop
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonTestLoop( int argcount, char *cmdargs[MAX_CMD_ARGS], int loopcount )
{
   int			i;
   int			testlist[MAX_CMD_ARGS];

   /* clear test list */
   for (i = 0; i < MAX_CMD_ARGS; i++)
   {
      testlist[i] = -1;
   }

   /* copy test numbers to test list */
   for (i = 1; i < argcount; i++)
   {
      testlist[i-1] = atoi( cmdargs[i] );
   }

   /* if testnum = 0, run all tests */
   if (testlist[0] == 0)
   {
      /* if loop forever */
      if (loopcount == -1)
      {
         i = 0;
         printf("\nLooping forever...\n");
         for (;;)
         {
            printf("\nLoopcount = %d\n", i+1);
//            post_run();
            i++;
         } 
      }
      /* else, loop for loopcount times */
      else
      {
         printf("\nLooping %d times ...\n", loopcount);
         for (i = 0; i < loopcount; i++)
         {
             printf("\nLoopcount = %d\n", i+1);
//             post_run();
         } 
      }
   }
   /* otherwise, run list of test numbers */
   else
   {
      /* if loop forever */
      if (loopcount == -1)
      {
         i = 0;
         printf("\nLooping forever...\n");
         for (;;)
         {
            printf("\nLoopcount = %d\n", i+1);
//            post_execute( &testlist ); 
            i++;
         } 
      }
      /* else, loop for loopcount times */
      else
      {
         printf("\nLooping %d times ...\n", loopcount);
         for (i = 0; i < loopcount; i++)
         {
            printf("\nLoopcount = %d\n", i+1);
//            post_execute( &testlist ); 
         } 
      }
   }
}


/*  MonSoftReset	- reset cpu via soft reset 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonSoftReset( void )
{
#ifdef CFG_ENABLE_SOFT_RESET
   printf("RESETTING!!!\n");
   hw_delay_sec(2);
   hw_do_soft_reset();
#else
   printf("Soft reset is disabled\n");
#endif /* CFG_ENABLE_SOFT_RESET */
}


/*  MonAtaProbe		- display ata registers 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonAtaProbe( void )
{
#ifdef CFG_ENABLE_REG_PROBE
   hw_ata_reg_probe();
#else
   printf("ATA reg probe is disabled\n");
#endif /* CFG_ENABLE_REG_PROBE */
}


/*  MonCpuProbe		- display cpu registers 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonCpuProbe( void )
{
#ifdef CFG_ENABLE_REG_PROBE
   hw_cpu_reg_probe();
#else
   printf("CPU reg probe is disabled\n");
#endif /* CFG_ENABLE_REG_PROBE */
}


/*  MonEthProbe		- display eth registers 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonEthProbe( void )
{
#ifdef CFG_ENABLE_REG_PROBE
   hw_eth_reg_probe();
#else
   printf("ETH reg probe is disabled\n");
#endif /* CFG_ENABLE_REG_PROBE */
}


/*  MonPciProbe		- display pci registers 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonPciProbe( void )
{
#ifdef CFG_ENABLE_REG_PROBE
   hw_pci_reg_probe();
#else
   printf("PCI reg probe is disabled\n");
#endif /* CFG_ENABLE_REG_PROBE */
}


/*  MonUsbProbe		- display usb registers 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonUsbProbe( void )
{
#ifdef CFG_ENABLE_REG_PROBE
   hw_usb_reg_probe();
#else
   printf("USB reg probe is disabled\n");
#endif /* CFG_ENABLE_REG_PROBE */
}


/*  MonPciScan		- display pci devices 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonPciScan( void )
{
   printf("scan pci not implemented yet!!\n");
}


/*  MonUsbScan		- display usb devices 
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonUsbScan( void )
{
   printf("scan usb not implemented yet!!\n");
}


/*  MonFlashSectors	- display flash sectors
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void 
MonFlashSectors( void )
{
   unsigned long	address;
   unsigned long	read;
   BOOLEAN_T		done;
   int			i, sector_size;

#ifdef CFG_ENABLE_FLASH_ACCESS
   printf("\nFlash sectors ...\n");

   sector_size = data->flash_sector;
   i = 1;

   for (address = 0x0; address < FLASH_SIZE; address += sector_size)
   {
      read = hw_read_flash_long( address );
      printf("0x%08x : ", (address + FLASH_BASE) );
      if ( read == FLASH_BLANK )
         printf("----    ");
      else
         printf("used    ");

      if ( (i++ % 4) == 0 )
         printf("\n");

   } /* end for */
#else
   printf("Flash access is disabled\n");
#endif /* CFG_ENABLE_FLASH_ACCESS */
}


/*  MonDumpFlash	- display contents of flash 
 *
 *  Parameters:
 *	start	- start address in flash
 *	end  	- end address in flash
 *
 *  Returns:
 *	none
 */
void 
MonDumpFlash( unsigned long start, unsigned long end )
{
   unsigned long	address, address2;
   unsigned long	read;

   BOOLEAN_T	done;
   char		response[20];		/* response buffer */
   int		block_size = DEFAULT_BLOCK_SIZE;
   int		bytes_per_row = DEFAULT_BYTES_PER_ROW;

#ifdef CFG_ENABLE_FLASH_ACCESS
   printf("\nFlash dump ...\n");
   printf("  start = 0x%08x\n", start);
   printf("  end   = 0x%08x\n", end);

   if ( start < end )
   {
      if ( (start >= FLASH_BASE) && (start < (FLASH_BASE + FLASH_SIZE - 1) ) )
      {
         if ( (end >= FLASH_BASE) && (end < (FLASH_BASE + FLASH_SIZE - 1) ) )
         {
            done = FALSE;
            address = start - FLASH_BASE;
            address2 = end - FLASH_BASE;
            while ( !done )
            {
               /* if DumpMemBlock returns EOF, set done flag */
               if ( DumpMemBlock( address, address2, block_size, bytes_per_row, stdout, TRUE) )
               {
                  done = TRUE;
               }

               /* else, prompt for next block */
               else
               {
                  printf("\nDump next block (Y/n)? ");

                  gets( &response[0] );

                  if ( (response[0] == 'n') || (response[0] == 'N'))
                  {
                     done = TRUE;
                  }
               }
               address += block_size;
            } /* end while */
         }
         else
         {
            printf("End address out of range!\n");
            printf("  0x%08x <= end < 0x%08x\n", FLASH_BASE, (FLASH_BASE + FLASH_SIZE));
         }
      }
      else
      {
         printf("Start address out of range!\n");
         printf("  0x%08x <= start < 0x%08x\n", FLASH_BASE, (FLASH_BASE + FLASH_SIZE));
      }
   }
   else
   {
      printf("Start address must be less than end address!\n");
   }
#else
   printf("Flash access is disabled\n");
#endif /* CFG_ENABLE_FLASH_ACCESS */
}


/*  MonDumpMemory	- display contents of memory 
 *
 *  Parameters:
 *	start	- start address in memory
 *	end  	- end address in memory
 *
 *  Returns:
 *	none
 */
void 
MonDumpMemory( unsigned long start, unsigned long end )
{
   unsigned long	address;
   unsigned long	read;

   BOOLEAN_T	done;
   char		response[20];		/* response buffer */
   int		block_size = DEFAULT_BLOCK_SIZE;
   int		bytes_per_row = DEFAULT_BYTES_PER_ROW;

#ifdef CFG_ENABLE_RAM_ACCESS
   printf("\nSDRAM dump ...\n");

   if ( start < end )
   {
      if ( (start >= SDRAM_BASE) && (start < SDRAM_SIZE) )
      {
         if ( (end >= SDRAM_BASE) && (end < SDRAM_SIZE) )
         {
            done = FALSE;
            address = start;
            while ( !done )
            {
               /* if DumpMemBlock returns EOF, set done flag */
               if ( DumpMemBlock( address, end, block_size, bytes_per_row, stdout, FALSE) )
               {
                  done = TRUE;
               }

               /* else, prompt for next block */
               else
               {
                  printf("\nDump next block (Y/n)? ");

                  gets( &response[0] );

                  if ( (response[0] == 'n') || (response[0] == 'N'))
                  {
                     done = TRUE;
                  }
               }
               address += block_size;
            } /* end while */
         }
         else
         {
            printf("End address out of range!\n");
            printf("  0x%08x <= end < 0x%08x\n", SDRAM_BASE, SRAM_SIZE);
         }
      }
      else
      {
         printf("Start address out of range!\n");
         printf("  0x%08x <= start < 0x%08x\n", SDRAM_BASE, SRAM_SIZE);
      }
   }
   else
   {
      printf("Start address must be less than end address!\n");
   }
#else
   printf("Ram access is disabled\n");
#endif /* CFG_ENABLE_RAM_ACCESS */
}


/*  MonFillMemory	- display contents of memory 
 *
 *  Parameters:
 *	start	- start address in memory
 *	end  	- end address in memory
 *	data	- data pattern to fill
 *
 *  Returns:
 *	none
 */
void 
MonFillMemory( unsigned long start, unsigned long end, unsigned long data )
{
   unsigned long	address;
   unsigned long	read;

#ifdef CFG_ENABLE_RAM_ACCESS
   printf("\nSDRAM fill ...\n");

   if ( start < end )
   {
      if ( (start >= SDRAM_BASE) && (start < SDRAM_SIZE) )
      {
         if ( (end >= SDRAM_BASE) && (end < SDRAM_SIZE) )
         {
            for (address = start; address < end; address += 4)
            {
               read = hw_write_sdram_long(address, data);
            }
            printf("done.\n");
         }
         else
         {
            printf("End address out of range!\n");
            printf("  0x%04x <= end < 0x%04x\n", SDRAM_BASE, SRAM_SIZE);
         }
      }
      else
      {
         printf("Start address out of range!\n");
         printf("  0x%04x <= start < 0x%04x\n", SDRAM_BASE, SRAM_SIZE);
      }
   }
   else
   {
      printf("Start address must be less than end address!\n");
   }
#else
   printf("Ram access is disabled\n");
#endif /* CFG_ENABLE_RAM_ACCESS */
}


/*  MonModifyMemory	- modify contents of memory 
 *
 *  Parameters:
 *	start	- start address in memory
 *	data	- data pattern to fill
 *
 *  Returns:
 *	none
 */
void 
MonModifyMemory( unsigned long start, unsigned long data )
{
   unsigned long	address;
   unsigned long	read;

#ifdef CFG_ENABLE_RAM_ACCESS
   printf("\nSDRAM modify ...\n");

   if ( (start >= SDRAM_BASE) && (start < SDRAM_SIZE) )
   {
      address = start;
      read = hw_write_sdram_long(address, data);
      printf("Wrote 0x%08x to 0x%08x\n", data, (address + SDRAM_BASE) );
   }
   else
   {
      printf("Address out of range!\n");
      printf("  0x%04x <= address < 0x%04x\n", SDRAM_BASE, SRAM_SIZE);
   }
#else
   printf("Ram access is disabled\n");
#endif /* CFG_ENABLE_RAM_ACCESS */
}


/*  MonReadMemory	- read contents of memory 
 *
 *  Parameters:
 *	start	- address in memory to read
 *
 *  Returns:
 *	none
 */
void 
MonReadMemory( unsigned long start )
{
   unsigned long	address;
   unsigned long	read;

#ifdef CFG_ENABLE_RAM_ACCESS
   printf("\nSDRAM read ...\n");

   if ( (start >= SDRAM_BASE) && (start < SDRAM_SIZE) )
   {
      address = start;
      read = hw_read_sdram_long(address);
      printf("0x%08x = 0x%08x\n", (address + SDRAM_BASE), read);
   }
   else
   {
      printf("Address out of range!\n");
      printf("  0x%04x <= address < 0x%04x\n", SDRAM_BASE, SRAM_SIZE);
   }
#else
   printf("Ram access is disabled\n");
#endif /* CFG_ENABLE_RAM_ACCESS */
}


/*  MonWriteMbar	- modify contents of mbar register 
 *
 *  Parameters:
 *	offset	- offset from MBAR base
 *	data	- data to write
 *
 *  Returns:
 *	none
 */
void 
MonWriteMbar( unsigned long offset, unsigned long data )
{
   unsigned long	address;
   unsigned long	read;

   printf("\nMBAR write ...\n");

}


/*  MonReadMbar		- read contents of mbar register 
 *
 *  Parameters:
 *	offset	- offset from MBAR base
 *
 *  Returns:
 *	none
 */
void 
MonReadMbar( unsigned long offset )
{
   unsigned long	address;
   unsigned long	read;

   printf("\nMBAR read ...\n");

}


#ifdef CFG_BOARD_VOW5200
/*  MonWriteCpld	- modify contents of cpld register 
 *
 *  Parameters:
 *	offset	- offset from CPLD base
 *	data	- data to write
 *
 *  Returns:
 *	none
 */
void 
MonWriteCpld( unsigned long offset, unsigned long data )
{
   unsigned long	address;
   unsigned long	read;

   printf("\nCPLD write ...\n");

}


/*  MonReadCpld		- read contents of cpld register 
 *
 *  Parameters:
 *	offset	- offset from CPLD base
 *
 *  Returns:
 *	none
 */
void 
MonReadCpld( unsigned long offset )
{
   unsigned long	address;
   unsigned long	read;

   printf("\nCPLD read ...\n");

}
#endif 


/*  MonVideo	- display video pattern
 *
 *  Parameters:
 *	pattern		- video pattern
 *
 *  Returns:
 *	none
 */
void
MonVideo( int pattern )
{
   printf("\nDisplaying pattern %d\n", pattern);

   hw_draw_init();

   switch(pattern)
   {
      case 0:
         hw_draw_pattern_anim();	/* edwin's moving box demo */
         break;
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
         hw_draw_pattern(pattern, 1);
         break;
      case 44:
         hw_draw_pattern_crazy_lines();
         break;
      case 55:
         hw_draw_pattern_crazy_boxes();
         break;
      case 66:
         hw_draw_pattern_crazy_circles();
         break;
      case 77:
         hw_draw_pattern_cycle_fast();
         break;
      case 88:
         hw_draw_pattern_cycle_slow();
         break;
      case 99:
         hw_draw_pattern_cls();
         break;
      default:
         printf("Error - unknown video pattern!\n");
         break;
   }
}


/*  MonVidPass	- enable/disable video pass-thru
 *
 *  Parameters:
 *	enable		- enable flag
 *
 *  Returns:
 *	none
 */
void
MonVidPass( int enable )
{
   printf("\nVideo pass-thru is ");

   if (enable == 1)
   {
      printf("Enabled\n");
      hw_video_pass( 1 );
   }
   else if (enable == 0)
   {
      printf("Disabled\n");
      hw_video_pass( 0 );
   }
   else
   {
      printf("\nError - unknown flag entered\n");
   }
}


/*  MonVidScale	- set scaling for video pass-thru
 *
 *  Parameters:
 *	width		- scale width percent
 *	height		- scale height percent
 *
 *  Returns:
 *	none
 */
void
MonVidScale( int width, int height )
{
   printf("\nVideo pass-thru scaling is - ");

   if (width >= 0 && width <= 100)
   {
      if (height >= 0 && height <= 100)
      {
         printf("width %d height %d\n", width, height);
         hw_video_scale( width, height );
      }
      else
      {
         printf("\nError - scale height is out of range\n");
      }
   }
   else
   {
      printf("\nError - scale width is out of range\n");
   }
}


/*  MonDisplayVersion	- output version message
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void
MonDisplayVersion( void )
{
   printf("VidTest - Version %d.%d.%d - ", 
	VERSION_MAJOR, VERSION_MINOR, VERSION_INTERNAL);
#ifdef CFG_OS_SIM
   printf("OS SIM on ");
#endif
#ifdef CFG_OS_LINUX
   printf("OS Linux on ");
#endif
#ifdef CFG_CPU_SIM
   printf("SIM\n");
#endif
#ifdef CFG_CPU_SH4
   printf("SH4\n");
#endif
}


/*  MonDisplayInfo	- output info message
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void
MonDisplayInfo( void )
{
//   post_config();
   printf("\nMON Board Info:\n");
   printf("  Board Type   = ");
   switch(data->board_type)
   {
      case BOARD_ID_SIM:
         printf("SIM\n");
         break;
      case BOARD_ID_SH4:
         printf("SH4\n");
         break;
      default:
         printf("unknown\n");
         break;
   }
   printf("  CPU Type     = ", data->cpu_type);
   switch(data->cpu_type)
   {
      case CPU_ID_SIM:
         printf("SIM\n");
         break;
      case CPU_ID_SH4:
         printf("SH4\n");
         break;
      default:
         printf("unknown\n");
         break;
   }

   printf("\n");
   printf("  MBAR base    = 0x%08x\n", data->mbar_base);
   printf("\n");
   printf("  SDRAM base   = 0x%08x\n", data->sdram_base);
   printf("  SDRAM size   = 0x%08x\n", data->sdram_size);
   printf("\n");
   printf("  FLASH base   = 0x%08x\n", data->flash_base);
   printf("  FLASH size   = 0x%08x\n", data->flash_size);
   printf("  FLASH sector = 0x%08x\n", data->flash_sector);
   printf("\n");

   printf("MON Post Status:\n");
//   post_display_mode();
//   post_display_method();
   printf("\n");
}


/*===========================================================================*/
/*                                                                           */
/* Static Functions                                                          */
/*                                                                           */
/*===========================================================================*/


/*  DumpMemBlock - read a block of size bytes from memory 
 *		   and send to output file
 *
 *  PARAMETERS:
 *	start		- start address
 *	end		- end address
 *	size		- size of block in bytes
 *	bytes_per_row	- bytes per row
 *	out_file_p	- output file pointer
 *
 *  RETURNS:
 *	eof		- TRUE if at EOF
 */
BOOLEAN_T 
DumpMemBlock(int start, int end, int size, 
	int bytes_per_row, FILE *out_file_p, BOOLEAN_T flash)
{

   return(TRUE);
}


/* end of MonHandle.c */
