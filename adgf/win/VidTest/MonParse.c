/*****************************************************************************
 *
 *	DiagMon monitor CLI functions
 *
 *	File:	MonParse.c
 *
 *	Author: Brian Lingard
 *	Date:	10/21/2003
 *
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

#include "types.h"
#include "config.h"
#include "video.h"
#include "mon.h"


#undef MON_DEBUG



/*
 *  GLOBALS
 */
extern DATABASE_S_T *data;
extern unsigned long mapped_sdram_base;
extern unsigned long mapped_flash_base;


/*
 *  STATICS
 */
void MonDisplayHelp( void );



/*  MonInteractive	- runs interactive mode
 *
 *  Parameters:
 *	DATABASE_S_T *mondata	- pointer to mon database
 *
 *  Returns:
 *
 */
void 
MonInteractive( DATABASE_S_T *mondata, BOOLEAN_T runcli, char *script )
{
   MON_LONG_BUFFER_T	cmd, cmdstring;	
   BOOLEAN_T		exit = FALSE;
   char 		*buffer;
   char			*cmdargs[MAX_CMD_ARGS];
   int			i, argcount;
   int			value;
   unsigned long	start, end, data;
   int			testlist[MAX_CMD_ARGS];
   FILE			*infp;

   /* initialize post data */
//   post_config();

   if (runcli)
   {
      printf("{type 'help' to get started}\n");
   }
   else
   {
      printf("\nExecuting script - %s ...\n", script);
      infp = fopen(script, "r"); 
      if (infp == (FILE *)NULL)
      {
         fprintf(stderr, "Error: can't open %s for input\n", script);
         exit = TRUE;
      }
   }

   /* loop while not exit */
   while (!exit)
   {
      if (runcli)
      {
         /* get command string from user */
         printf("\n%s ", PROMPT);
         fgets( cmd, MON_LONG_BUFF_LEN, stdin );
         strncpy( cmdstring, cmd, MON_LONG_BUFF_LEN );
      }
      else
      {
         /* get command string from script file */
         fgets( cmd, MON_LONG_BUFF_LEN, infp );
         strncpy( cmdstring, cmd, MON_LONG_BUFF_LEN );
#ifdef MON_DEBUG
         printf("read - %s\n", cmdstring);
#endif
      }

      /* parse command string */
      buffer = &cmdstring[0];
      cmdstring[MON_LONG_BUFF_LEN - 1] = '\0';
      argcount = MonParseString( buffer, cmdargs );

      if ( strcmp( cmdargs[0], "test" ) == 0 )
      {
         if (argcount == 1)
         {
//            post_display_header();
//            post_display_table();
//            post_display_footer();
         }
         else
         {
            MonTestExecute( argcount, cmdargs );
         }
      }
      else if ( strcmp( cmdargs[0], "run" ) == 0 )
      {
//         post_run();
      }
      else if ( strcmp( cmdargs[0], "loop" ) == 0 )
      {
         if (argcount == 1)
            MonDisplayHelp();
         else
         {
            MonTestLoop( argcount, cmdargs, mondata->count );
         }          
      }
      else if ( strcmp( cmdargs[0], "count" ) == 0 )
      {
         if (argcount == 2)
         {
            value = atoi( cmdargs[1] );
            mondata->count = value;
//            post_set_count( value, TRUE );
         }
         else
         {
//            post_display_count();
         }
      }
      else if ( strcmp( cmdargs[0], "mode" ) == 0 )
      {
         if (argcount == 2)
         {
            value = atoi( cmdargs[1] );
//            post_set_mode( value, TRUE );
         }
         else
         {
//            post_display_mode();
         }
      }
      else if ( strcmp( cmdargs[0], "method" ) == 0 )
      {
         if (argcount == 2)
         {
            value = atoi( cmdargs[1] );
//            post_set_method( value, TRUE );
         }
         else
         {
//            post_display_method();
         }
      }
      else if ( strcmp( cmdargs[0], "list" ) == 0 )
      {
//         post_display_header();
//         post_display_table();
//         post_display_footer();
      }
      else if ( strcmp( cmdargs[0], "md" ) == 0 )
      {
         if (argcount == 3)
         {
            start = strtoul( cmdargs[1], NULL, 16 );
            end = strtoul( cmdargs[2], NULL, 16 );
            MonDumpMemory( start, end );
         }
         else
         {
            printf("Usage: md [<start> <end>]\n");
            printf("<start>  - start address in hex\n");
            printf("<end>    - end address in hex\n");
         }
      }
      else if ( strcmp( cmdargs[0], "mf" ) == 0 )
      {
         if (argcount == 4)
         {
            start = strtoul( cmdargs[1], NULL, 16 );
            end = strtoul( cmdargs[2], NULL, 16 );
            data = strtoul( cmdargs[3], NULL, 16 );
            MonFillMemory( start, end, data );
         }
         else
         {
            printf("Usage: mf <start> <end> <data>\n");
            printf("<start>    - start address in hex\n");
            printf("<end>      - end address in hex\n");
            printf("<data>     - data in hex\n");
         }
      }
      else if ( strcmp( cmdargs[0], "mm" ) == 0 )
      {
         if (argcount == 3)
         {
            start = strtoul( cmdargs[1], NULL, 16 );
            data = strtoul( cmdargs[2], NULL, 16 );
            MonModifyMemory( start, data );
         }
         else
         {
            printf("Usage: mm <address> <data>\n");
            printf("<address>  - address in hex\n");
            printf("<data>     - data in hex\n");
         }
      }
      else if ( strcmp( cmdargs[0], "mr" ) == 0 )
      {
         if (argcount == 2)
         {
            start = strtoul( cmdargs[1], NULL, 16 );
            MonReadMemory( start );
         }
         else
         {
            printf("Usage: mr <address>\n");
            printf("<address>  - address in hex\n");
         }
      }
      else if ( strcmp( cmdargs[0], "fd" ) == 0 )
      {
         if (argcount == 3)
         {
            start = strtoul( cmdargs[1], NULL, 16 );
            end = strtoul( cmdargs[2], NULL, 16 );
            MonDumpFlash( start, end );
         }
         else
         {
            printf("Usage: fd [<start> <end>]\n");
            printf("<start>  - start address in hex\n");
            printf("<end>    - end address in hex\n");
         }
      }
      else if ( strcmp( cmdargs[0], "fs" ) == 0 )
      {
         MonFlashSectors();
      }

      else if ( strcmp( cmdargs[0], "rmbar" ) == 0 )
      {
         if (argcount == 2)
         {
            start = strtol( cmdargs[1], NULL, 16 );
            MonReadMbar( start );
         }
         else
         {
            printf("Usage: rmbar <offset>\n");
            printf("<offset>  - offset in hex\n");
         }
      }
      else if ( strcmp( cmdargs[0], "wmbar" ) == 0 )
      {
         if (argcount == 3)
         {
            start = strtol( cmdargs[1], NULL, 16 );
            data = strtoul( cmdargs[2], NULL, 16 );
            MonWriteMbar( start, data );
         }
         else
         {
            printf("Usage: wmbar <offset> <data>\n");
            printf("<offset>  - offset in hex\n");
            printf("<data>    - data in hex\n");
         }
      }

#ifdef CFG_BOARD_VOW5200
      else if ( strcmp( cmdargs[0], "rcpld" ) == 0 )
      {
         if (argcount == 2)
         {
            start = strtol( cmdargs[1], NULL, 16 );
            MonReadCpld( start );
         }
         else
         {
            printf("Usage: rcpld <offset>\n");
            printf("<offset>  - offset in hex\n");
         }
      }
      else if ( strcmp( cmdargs[0], "wcpld" ) == 0 )
      {
         if (argcount == 3)
         {
            start = strtol( cmdargs[1], NULL, 16 );
            data = strtoul( cmdargs[2], NULL, 16 );
            MonWriteCpld( start, data );
         }
         else
         {
            printf("Usage: wcpld <offset> <data>\n");
            printf("<offset>  - offset in hex\n");
            printf("<data>    - data in hex\n");
         }
      }
#endif

      else if ( strcmp( cmdargs[0], "probe" ) == 0 )
      {
         if (argcount == 2)
         {
            if ( strcmp( cmdargs[1], "all" ) == 0 )
            {
               MonCpuProbe();
               MonAtaProbe();
               MonEthProbe();
               MonPciProbe();
               MonUsbProbe();
            }
            else if ( strcmp( cmdargs[1], "ata" ) == 0 )
            {
               MonAtaProbe();
            }
            else if ( strcmp( cmdargs[1], "cpu" ) == 0 )
            {
               MonCpuProbe();
            }
            else if ( strcmp( cmdargs[1], "eth" ) == 0 )
            {
               MonEthProbe();
            }
            else if ( strcmp( cmdargs[1], "pci" ) == 0 )
            {
               MonPciProbe();
            }
            else if ( strcmp( cmdargs[1], "usb" ) == 0 )
            {
               MonUsbProbe();
            }
            else 
            {
               printf("Usage: probe <select>\n");
               printf("<select>  - register group\n");
               printf("            <all,ata,cpu,eth,pci,usb>\n");
            }
         }
         else
         {
            printf("Usage: probe <select>\n");
            printf("<select>  - register group\n");
            printf("            <all,ata,cpu,eth,pci,usb>\n");
         }
      }
      else if ( strcmp( cmdargs[0], "scan" ) == 0 )
      {
         if (argcount == 2)
         {
            if ( strcmp( cmdargs[1], "pci" ) == 0 )
            {
               MonPciScan();
            }
            else if ( strcmp( cmdargs[1], "usb" ) == 0 )
            {
               MonUsbScan();
            }
            else 
            {
               printf("Usage: scan <select>\n");
               printf("<select>  - device group\n");
               printf("            <pci,usb>\n");
            }
         }
         else
         {
            printf("Usage: scan <select>\n");
            printf("<select>  - device group\n");
            printf("            <pci,usb>\n");
         }
      }
      else if ( strcmp( cmdargs[0], "video" ) == 0 )
      {
         if (argcount == 2)
         {
            value = atoi( cmdargs[1] );
            MonVideo( value );
         }
         else
         {
            printf("Usage: video <select>\n");
            printf("<select>  - video pattern\n");
            printf("            <1,2,3,4>\n");
         }
      }
      else if ( strcmp( cmdargs[0], "rem" ) == 0 )
      {
         printf("rem ignored\n");
      }
      else if ( strcmp( cmdargs[0], "#" ) == 0 )
      {
         printf("# ignored\n");
      }
      else if ( strcmp( cmdargs[0], "ver" ) == 0 )
      {
         MonDisplayVersion();
      }
      else if ( strcmp( cmdargs[0], "info" ) == 0 )
      {
         MonDisplayInfo();
      }
      else if ( strcmp( cmdargs[0], "reset" ) == 0 )
      {
         MonSoftReset();
      }
      else if ( strcmp( cmdargs[0], "help" ) == 0 )
      {
         MonDisplayHelp();
      }
      else if ( strcmp( cmdargs[0], "h" ) == 0 )
      {
         MonDisplayHelp();
      }
      else if ( strcmp( cmdargs[0], "?" ) == 0 )
      {
         MonDisplayHelp();
      }
      else if ( strcmp( cmdargs[0], "exit" ) == 0 )
      {
         if (!runcli) fclose( infp );
         exit = TRUE;
      }
      else if ( strcmp( cmdargs[0], "ex" ) == 0 )
      {
         if (!runcli) fclose( infp );
         exit = TRUE;
      }
      else if ( strcmp( cmdargs[0], "quit" ) == 0 )
      {
         if (!runcli) fclose( infp );
         exit = TRUE;
      }
      else
      {
         if ( strcmp( cmdargs[0], "" ) != 0 )
            printf("Error - unknown command!\n");
      }
   }
}


/*  MonParseString	- general purpose string parser
 *
 *  Parameters:
 *	string	- pointer to string to be parsed
 *	args	- pointer to parsed array of strings
 *
 *  Returns:
 *	count	- count of substrings in array
 */
int 
MonParseString(char *string, char *args[])
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of MonParseString() */


/*===========================================================================*/
/*                                                                           */
/* Static Functions                                                          */
/*                                                                           */
/*===========================================================================*/

/*  MonDisplayHelp	- output help message
 *
 *  Parameters:
 *	none
 *
 *  Returns:
 *	none
 */
void
MonDisplayHelp( void )
{
   printf("\nAvailable CLI commands:\n");
   printf("  list                - display list of tests\n");
   printf("  run                 - run all test in this mode\n");
   printf("\n");
   printf("  test # | [#...#]    - execute list of tests\n");
   printf("  loop # | [#...#]    - loop on single test or list\n");
   printf("  count #             - set loop count (-1 loop forever)\n");
   printf("\n");
   printf("  mode #              - set test mode {valid 1,2,3,4,5}\n");
   printf("  method #            - set test method {valid 1,2,3}\n");
   printf("\n");
   printf("  probe <select>      - display register group\n");
   printf("  scan <select>       - display device group\n");
   printf("  video <select>      - display video pattern\n");
   printf("\n");
   printf("  fd [<start> <end>]  - flash dump (offsets from FLASH_BASE)\n");
   printf("  fs                  - flash status (sectors used)\n");
   printf("\n");
   printf("  md [<start> <end>]  - memory dump\n");
   printf("  mf <s> <e> <data>   - memory fill\n");
   printf("  mm <addr> <data>    - memory modify\n");
   printf("  mr <addr>           - memory read\n");
   printf("\n");
   printf("  rmbar <off>         - read MBAR register\n");
   printf("  wmbar <off> <data>  - write MBAR register\n");
   printf("\n");
#ifdef CFG_BOARD_VOW5200
   printf("  rcpld <off>         - read CPLD register\n");
   printf("  wcpld <off> <data>  - write CPLD register\n");
   printf("\n");
#endif
   printf("  help                - display help\n");
   printf("  info                - display board info\n");
   printf("  rem                 - do nothing, comment in script\n");
   printf("  ver                 - display version info\n");
   printf("  exit                - exit monitor\n");
}


/* end of MonParse.c */
