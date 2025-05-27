/*****************************************************************************
 *
 *	DiagMon program header file.
 *
 *	File:	config.h
 *
 *	Author: Brian Lingard
 *
 *	Date:	10/21/2003
 *
 *	Revs:
 *	  0.0 	10/21/2003  originated
 *
 *****************************************************************************/

#ifndef __config_h
#define __config_h


/*===========================================================================*/
/*                                                                           */
/* Select Target or SIM                                                      */
/*                                                                           */
/*===========================================================================*/

#undef CONFIG_ON_TARGET
#define CONFIG_ON_SIM


/*===========================================================================*/
/*                                                                           */
/* Config On SIM                                                             */
/*                                                                           */
/*===========================================================================*/

#ifdef CONFIG_ON_SIM
#define CFG_OS_SIM
#define CFG_CPU_SIM
#define CFG_BOARD_SIM
#endif


/*===========================================================================*/
/*                                                                           */
/* Config On Target                                                          */
/*                                                                           */
/*===========================================================================*/

/* config OS Type */
#ifdef CONFIG_ON_TARGET
#define CFG_OS_LINUX
#undef CFG_OS_NONE
#endif

/* config CPU Type */
#ifdef CONFIG_ON_TARGET
#define CFG_CPU_SH4
#undef CFG_CPU_X86
#endif

/* config Board Type */
#ifdef CONFIG_ON_TARGET
#define CFG_BOARD_SH4
#endif

#ifdef CONFIG_ON_TARGET
#undef CFG_BOARD_X86PC
#endif

/* config Functions Enabled */
#ifdef CONFIG_ON_TARGET
#undef CFG_ENABLE_POST
#undef CFG_ENABLE_PCI_FIND
#undef CFG_ENABLE_REG_PROBE
#undef CFG_ENABLE_SOFT_RESET
#undef CFG_ENABLE_RAM_ACCESS
#undef CFG_ENABLE_FLASH_ACCESS
#undef CFG_ENABLE_LOGGING
#endif


#endif 	/* __config_h */
