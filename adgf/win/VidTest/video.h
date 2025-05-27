/*
 *     Module Name:  video.h
 *
 *     Description:
 *
 *      Diagnostics firmware for the TBD Modules.
 *
 *      This file contains platform specific hardware info used 
 *	by Diagnostics.
 *
 *     Assumptions:  N/A
 *
 *	!!!  This file must be ported to your hardware  !!!
 *
 */

#ifndef __video_h
#define __video_h

#ifdef CFG_CPU_SH4
#include "sh4.h"
#endif

#include "types.h"


/*===========================================================================*/
/*                                                                           */
/* Macros                                                                    */
/*                                                                           */
/*===========================================================================*/

#define setbit(v,m)		((v)|=(m))
#define clrbit(v,m)		((v)&=~(m))
#define togglebit(v,m)		((v)^=(m))

#define eieio() __asm__ __volatile__ ("eieio" : : : "memory");
#define sync()  __asm__ __volatile__ ("sync" : : : "memory");

#define PCI_BUS(d)	(((d) >> 16) & 0xff)
#define PCI_DEV(d)	(((d) >> 11) & 0x1f)
#define PCI_FUNC(d)	(((d) >> 8) & 0x7)
#define PCI_BDF(b,d,f)	((b) << 16 | (d) << 11 | (f) << 8)

#if 0
inline uint32 in_le32(volatile uint32 *addr)
{
    unsigned ret;

    __asm__ __volatile__("lwbrx %0,0,%1; eieio" : "=r" (ret) :
		 "r" (addr), "m" (*addr));
    return ret;
}

inline void out_le32(volatile uint32 *addr, int val)
{
    __asm__ __volatile__("stwbrx %1,0,%2; eieio" : "=m" (*addr) :
		 "r" (val), "r" (addr));
}
#endif



/*===========================================================================*/
/*                                                                           */
/* Memory map and register address definitions                               */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/*                                                                           */
/* Register structure definitions                                            */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/*                                                                           */
/* Register Masks                                                            */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/*                                                                           */
/* Device Types                                                              */
/*                                                                           */
/*===========================================================================*/

#define CPU_ID_SIM  0x1234
#define CPU_ID_SH4  0x5678

#define FLASH_BLANK	0xFFFFFFFF

#define PCI_ID_CORALP	0x201910CF

#define PCI_VENDOR_ID_FUJITSU		    0x10CF
#define PCI_DEVICE_ID_FUJITSU_CORALP	0x2019

#define BOARD_ID_SIM    	1
#define BOARD_ID_SH4    	2

#ifdef CFG_BOARD_SIM
#define CPU_ID		  CPU_ID_SIM
#define BOARD_ID      BOARD_ID_SIM
#define MBAR_BASE           0
#define MBAR_SIZE           1000
#define SDRAM_BASE          0
#define SDRAM_SIZE          1000
#define FLASH_BASE          0
#define FLASH_SIZE          1000
#define FLASH_SECTOR_SIZE   32
#define FLASH_TEST_SIZE     32
#define SDRAM_TEST_SIZE     32
#endif

#ifdef CFG_BOARD_SH4
#define CPU_ID		  CPU_ID_SH4
#define BOARD_ID	  BOARD_ID_SH4
#define SDRAM_BASE          0
#define SDRAM_SIZE          1000
#define FLASH_BASE          0
#define FLASH_SIZE          1000
#define FLASH_SECTOR_SIZE   32
#define FLASH_TEST_SIZE     32
#define SDRAM_TEST_SIZE     32
#endif


/*===========================================================================*/
/*                                                                           */
/* Hardware Access Library Prototypes                                        */
/*                                                                           */
/*===========================================================================*/


void * hw_map_os_memory( unsigned long long physical, size_t len );
void hw_unmap_os_memory( void * virtual, int len );


/* video.c */
int hw_draw_init();
int hw_draw_wait();
int hw_draw_pattern_anim();
int hw_draw_pattern_cls();
int hw_draw_pattern_cycle();
int hw_draw_pattern(int pattern, int wait);
int hw_video_pass( int enable );
int hw_video_scale( int scalew, int scaleh );

#endif /* __video_h */
