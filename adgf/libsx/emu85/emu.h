/***********************************************************************

 Header file for Emu85.

   File:  	emu.h

   Author: 	Brian Lingard

   Date:	02/02/98

   Revisions:
	0.0	02/02/98 Originated

***********************************************************************/

#ifndef _EMU_H
#define _EMU_H


#ifndef _VECMATH_H
#include "vecmath.h"
#endif

#ifndef _IN6502_H
#include "in6502.h"
#endif



#define VERSION			0.1


#define SCREEN_X_SIZE   	(640)
#define SCREEN_Y_SIZE		(400)

#define STATUS_X_SIZE		(SCREEN_X_SIZE)
#define STATUS_Y_SIZE		(50)


#define BUTTON_UP	0		/* left button state */
#define BUTTON_DOWN	1


/* define special keys */
#define KEY_UP		'U'
#define KEY_DOWN	'D'
#define KEY_LEFT	'L'
#define KEY_RIGHT	'R'

#define KEY_RESET	'r'
#define KEY_STEP	's'
#define KEY_GO		'g'
#define KEY_HALT	'h'



/* define some common types */
#define BUFFER_LEN	80
typedef char BUFFER_T[BUFFER_LEN];

#define FILE_STRING_LEN	32
typedef char FILE_STRING_T[FILE_STRING_LEN];

typedef unsigned char	UBYTE_T;

typedef UBYTE_T		BOOLEAN_T;

#define DEFAULT_MEMBLK_SIZE	256



#ifndef TRUE
#define TRUE  ((BOOLEAN_T) 1)
#define FALSE ((BOOLEAN_T) 0)
#endif



/*  define some useful macros 
 */
#define InvertY(y)	(SCREEN_Y_SIZE - y)


/*  define register types
 */
typedef unsigned char		REG8_T;
typedef unsigned short int	REG16_T;
typedef unsigned long int	REG32_T;


/*  define memory block structure
 */
typedef struct memblk_s_t {
   REG16_T	start;			/* starting offset address */
   REG16_T	size;			/* size in bytes */
   REG8_T	*data;			/* pointer to allocated block */
} MEMBLK_S_T;


/*  define memory image structure
 */
typedef struct memory_s_t {
   MEMBLK_S_T	rom;
   MEMBLK_S_T	ram;
} MEMORY_S_T;


/*  define 6502 cpu structures
 */
typedef struct flag6502_s_t {
   REG8_T	n:1;		/* sign (negative) */
   REG8_T	v:1;		/* overflow */
   REG8_T	res:1;	
   REG8_T	b:1;		/* break */
   REG8_T	d:1;		/* decimal */
   REG8_T	i:1;		/* interrupt */
   REG8_T	z:1;		/* zero */
   REG8_T	c:1;		/* carry */
} FLAG6502_S_T;

typedef struct cpu6502_s_t {
   REG8_T	x;		/* x index */
   REG8_T	y;		/* y index */
   REG8_T	sp;		/* stack ranges from 0x100 to 0x1ff */
   REG16_T	pc;		/* program counter */
   REG8_T	a;		/* accumulator */
   FLAG6502_S_T	p;		/* processor status */
   REG8_T	ir;		/* instruction register */
   REG16_T	address;	/* address bus */
   REG8_T	data_in;	/* data bus in */
   REG8_T	data_out;	/* data bus out */
} CPU6502_S_T;


/*  define 8085 cpu structures
 */
typedef struct flag8085_s_t {
   REG8_T	s:1;		/* sign flag */
   REG8_T	z:1;		/* zero flag */
   REG8_T	res5:1;		
   REG8_T	ac:1;		/* auxiliary carry flag */
   REG8_T	res3:1;
   REG8_T	p:1;		/* parity flag */
   REG8_T	res1:1;
   REG8_T	cy:1;		/* carry flag */
} FLAG8085_S_T;

typedef struct cpu8085_s_t {
   REG8_T	a;		/* accumulator */
   FLAG8085_S_T	flag;		/* processor status flags */
   REG8_T  	ir;		/* instruction register */
   REG8_T	b;		/* paired with c */
   REG8_T	c;
   REG8_T	d;		/* paired with e */
   REG8_T	e;
   REG8_T	h;		/* paired with l */
   REG8_T	l;
   REG16_T	sp;		/* stack pointer */
   REG16_T	pc;		/* program counter */
   REG16_T	address;	/* address bus */
   REG8_T	data_in;
   REG8_T	data_out;
} CPU8085_S_T;


/*  define display types
 */
typedef enum display_t {
	DISPLAY_MPU = 0,
	DISPLAY_SYSTEM,
	DISPLAY_BOTH,
	DISPLAY_IMAGE
} DISPLAY_T;


/*  define control types
 */
typedef enum control_t {
	CONTROL_RESET = 0,
	CONTROL_STEP,
	CONTROL_GO,
	CONTROL_HALT
} CONTROL_T;


/*  define status structure 
 */ 
typedef struct status_s_t {
   DISPLAY_T	display;		/* current display type */
   CONTROL_T	control;		/* current active control */
} STATUS_S_T;



#endif /* _EMU_H */
/* end of emu.h */
