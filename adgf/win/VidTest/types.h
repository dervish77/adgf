/*
 *     Module Name:  types.h
 *
 *     Description:
 *
 *      Diagnostics firmware for the TBD Modules.
 *
 *      This file contains generic types used by POST/Diags.
 *
 *     Assumptions:  N/A
 *
 *
 *
 */

#ifndef __types_h
#define __types_h

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned long		uint32;
typedef unsigned long long	uint64;

typedef signed char		sint8;
typedef signed short		sint16;
typedef signed long		sint32;
typedef signed long long	sint64;

typedef volatile unsigned char		reg8;
typedef volatile unsigned short		reg16;
typedef volatile unsigned long		reg32;
typedef volatile unsigned long long	reg64;


typedef int 		BOOLEAN_T;
typedef unsigned char 	UBYTE_T;

#ifndef WIN32
typedef unsigned long int	UINT32;
typedef long int		INT32;
typedef unsigned short int	UINT16;
typedef short int		INT16;
typedef unsigned char		UINT8;
typedef char			INT8;
#endif

#endif /* __types_h */
