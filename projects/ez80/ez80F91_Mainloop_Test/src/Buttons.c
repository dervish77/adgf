/*                                                   Copyright (c) ZiLOG, 2003
 *****************************************************************************
 *  Buttons.c (1.0)
 *
 *  demo functions for buttons on the ZiLOG Development Board
 *****************************************************************************
 */

#include <ez80.h>

#include "LedMatrix.h"

extern void set_vector(unsigned short vector,void (*hndlr)(void));

/* Port B interrupt vectors for the various eZ80 and eZ80Acclaim! devices */
#ifdef _EZ80F91
#define PB0_IVECT 0xA0
#define PB1_IVECT 0xA4
#define PB2_IVECT 0xA8
#endif

#ifdef _EZ80F93
#define PB0_IVECT 0x30
#define PB1_IVECT 0x32
#define PB2_IVECT 0x34
#endif

#ifdef _EZ80F92
#define PB0_IVECT 0x30
#define PB1_IVECT 0x32
#define PB2_IVECT 0x34
#endif

#ifdef _EZ80L92
#define PB0_IVECT 0x30
#define PB1_IVECT 0x32
#define PB2_IVECT 0x34
#endif

#ifdef _EZ80190
#define PB0_IVECT 0x26
#define PB1_IVECT 0x28
#define PB2_IVECT 0x2a
#endif

/*****************************************************************************
 *  GPIO Port B 0 interrupt service routine
 *
 *  display a 1 on the LED matrix
 */
void interrupt pb0_isr( void )
{
    user_input = 1;
    p_user_input = &matrix_char_map['1' - 31][0];
	PB_DR = 0x01;
}

/*****************************************************************************
 *  GPIO Port B 1 interrupt service routine
 *
 *  display a 2 on the LED matrix
 */
void interrupt pb1_isr( void )
{
    user_input = 1;
    p_user_input = &matrix_char_map['2' - 31][0];
	PB_DR = 0x02;
}

/*****************************************************************************
 *  GPIO Port B 2 interrupt service routine
 *
 *  display a 3 on the LED matrix
 */
void interrupt pb2_isr( void )
{
    user_input = 1;
    p_user_input = &matrix_char_map['3' - 31][0];
	PB_DR = 0x04;

}


/*****************************************************************************
 *  Buttons initialization routine
 *
 *  
 */
void interrupt buttons_init( void )
{
    
	/* set port B 0 interrupt vector */
    set_vector( PB0_IVECT, pb0_isr );
	
	/* set port B 1 interrupt vector */
    set_vector( PB1_IVECT, pb1_isr );
	
	/* set port B 2 interrupt vector */
    set_vector( PB2_IVECT, pb2_isr );

    //Set the Port B bits 0, 1, and 2 to falling edge triggered interrupt mode
	PB_ALT2 |= 0x07;
	PB_ALT1 |= 0x07;
	PB_DDR |= 0x07;
	PB_DR = 0x00;

}
