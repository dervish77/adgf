/********************************************************************

   Private header information for Dev8085 development package.

   Author:    Brian Lingard

   File:      dev8085.h
 
   Revision History:
     0.0  12/04/96  originated

*********************************************************************/

#ifndef DEV8085_H
#define DEV8085_H

#include <stdio.h>
#include <stdlib.h>


/***********************************************************

 Private definitions and typedefs -- DO NOT EDIT

***********************************************************/

/* 
 *  define some useful types
 */
typedef char BYTE_T;
typedef unsigned char UBYTE_T;

typedef short int SHORT_T;
typedef unsigned short int USHORT_T;

typedef long int LONG_T;
typedef unsigned long int ULONG_T;

typedef unsigned char BOOLEAN_T;


#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define EQ	==


/* 
 *  define necessary constants
 */

#define FILENAME_LEN 32

#define NEUMONIC_LEN 10

#define NUM_OF_INSTRUCTIONS 256


/*
 *  define address modes
 */
#define AM_IMMEDIATE	1




/*
 *  define instruction table entry structure
 */

typedef struct instr_entry_s_t {
   BYTE_T    machine_code;
   char      neumonic_str[NEUMONIC_LEN];
   BYTE_T    address_mode;
   BOOLEAN_T legal_instr_flag;   
} INSTR_ENTRY_S_T;


/*
 *  define assembler file structure
 */

typedef struct asm_s_t {
   char src_file_name[FILENAME_LEN];
   FILE *src_fp;
   char raw_file_name[FILENAME_LEN];
   FILE *raw_fp;   
} ASM_S_T;


/*
 *  declare externs for globals and function protos
 */

extern INSTR_ENTRY_S_T instruction_table[];





#endif	/* DEV8085_H */

/* end of file dev8085.h */
