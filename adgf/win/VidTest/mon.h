/*****************************************************************************
 *
 *	DiagMon program header file.
 *
 *	File:	mon.h
 *
 *	Author: Brian Lingard
 *	Date:	10/21/2003
 *
 *
 *****************************************************************************/

#ifndef __mon_h
#define __mon_h


#include "version.h"


#define POST_MAJOR_VERSION	VERSION_MAJOR
#define POST_MINOR_VERSION	VERSION_MINOR
#define POST_INTERNAL_VERSION	VERSION_INTERNAL


/*  declare common types
 */
#define EQ	==
#define AND	&&
#define OR	||


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


/*  define prompt and buffer type
 */
#define PROMPT			"mon>"	

#define MAX_CMD_ARGS		21

#define MON_SHORT_BUFF_LEN	40
#define MON_LONG_BUFF_LEN	120

typedef char MON_SHORT_BUFFER_T[MON_SHORT_BUFF_LEN];
typedef char MON_LONG_BUFFER_T[MON_LONG_BUFF_LEN]; 


/*  define file name string type
 */
#define FILE_NAME_LEN		30
typedef char FILENAME_T[FILE_NAME_LEN];   


/*  define register structure type
 */
typedef struct reg_s_t {
   int			width;		/* width of register - 1,2,4 */
   union regdata_u_t {
      long int		ldata;		/* 32 bit register data */
      short int		wdata;		/* 16 bit register data */
      char		bdata;		/* 8 bit register data */
   } data;
   union regmask_u_t {
      long int		lmask;		/* 32 bit register mask */
      short int		wmask;		/* 16 bit register mask */
      char		bmask;		/* 8 bit register mask */
   } mask;
} REG_S_T;


/*  define main database structure 
 */
typedef struct database_s_t {
   int			board_type;	/* 1 = Lite, 2 = MB, 3 = VOW */
   int			cpu_type;
   unsigned long	mbar_base;	/* MBAR base address  */
   unsigned long	mbar_size;	/* size of MBAR space */
   unsigned long	sdram_base;	/* start of sdram     */
   unsigned long	sdram_size;	/* size of sdram      */
   unsigned long	flash_base;	/* start of flash     */
   unsigned long	flash_size;	/* size of flash      */ 
   unsigned long	flash_sector;	/* flash sector size  */
   unsigned long	mapped_mbar_base;
   unsigned long	mapped_sdram_base;
   unsigned long	mapped_flash_base;
   BOOLEAN_T		pass;		/* pass/fail flag     */
   int			count;		/* loop count         */
} DATABASE_S_T;   


/*  declare prototypes for all functions
 */
extern void MonRun( DATABASE_S_T *mondata );
extern void MonList( DATABASE_S_T *mondata );
extern void MonInteractive( DATABASE_S_T *mondata, BOOLEAN_T runcli, char *script );
extern void MonConfig( DATABASE_S_T *mondata );

extern void MonInit( DATABASE_S_T *mondata );
extern void MonClose( DATABASE_S_T *mondata );

extern void MonTestExecute( int argcount, char *cmdargs[MAX_CMD_ARGS] );
extern void MonTestLoop( int argcount, char *cmdargs[MAX_CMD_ARGS], int loopcount );

extern void MonDumpFlash( unsigned long start, unsigned long end );
extern void MonFlashSectors( void );

extern void MonDumpMemory( unsigned long start, unsigned long end );
extern void MonFillMemory( unsigned long start, unsigned long end, unsigned long data );
extern void MonModifyMemory( unsigned long start, unsigned long data );
extern void MonReadMemory( unsigned long start );

extern void MonWriteMbar( unsigned long offset, unsigned long data );
extern void MonReadMbar( unsigned long offset );

extern void MonVideo( int pattern );
extern void MonVidPass( int enable );
extern void MonVidScale( int scalew, int scaleh );

#ifdef CFG_BOARD_VOW5200
extern void MonWriteCpld( unsigned long offset, unsigned long data );
extern void MonReadCpld( unsigned long offset );
#endif

extern void MonAtaProbe( void );
extern void MonCpuProbe( void );
extern void MonEthProbe( void );
extern void MonPciProbe( void );
extern void MonUsbProbe( void );

extern void MonPciScan( void );
extern void MonUsbScan( void );

extern void MonSoftReset( void );

extern void MonDisplayInfo( void );
extern void MonDisplayVersion( void );
extern int  MonParseString(char *string, char *args[]);

#endif 	/* __mon_h */
