/*                                                   Copyright (c) ZiLOG, 2003
 *****************************************************************************
 *  LedTimer.c (1.0)
 *
 *  routines for timing the LED Matrix and wait routine
 *****************************************************************************
 */

#include <ez80.h>
#include "LedMatrix.h"
#include "Console.h"

int timer;

extern void set_vector(unsigned short vector,void (*hndlr)(void));

/* masterclock and timer 2 interrupt vectors for the various devices */
#ifdef _EZ80F91
#define SYSTEMCLOCK 50000000
#define TMR2_IVECT 0x5c
#endif

#ifdef _EZ80F93
#define SYSTEMCLOCK 20000000
#define TMR2_IVECT 0x0e
#endif

#ifdef _EZ80F92
#define SYSTEMCLOCK 20000000
#define TMR2_IVECT 0x0e
#endif

#ifdef _EZ80L92
#define SYSTEMCLOCK 48000000
#define TMR2_IVECT 0x0e
#endif

#ifdef _EZ80190
#define SYSTEMCLOCK 50000000
#define TMR2_IVECT 0x0a
#endif

/*****************************************************************************
 *  timer 2 interrupt service routine
 *
 *  controls the LED Matrix scroll rate
 */
void interrupt tmr2_isr( void )
{
    static unsigned char i, row;
    unsigned char tmp;

#ifdef _EZ80F91
    tmp = TMR2_IIR;
#else
    /* _EZ80190, _EZ80L92, _EZ80F92, _EZ80F93 */
	tmp = TMR2_CTL;
#endif

    if( 0 > i || i > 6 )
    {
        row = 0x01;
        i = 0;
	}

    LEDMATRIX_ROW = row;
    LEDMATRIX_COLUMN = *(pcolumn + i);

    i++;
    row = row << 1;

    timer++;
}

/*****************************************************************************
 *  ledtimer_init()
 *
 *  initialization routine for timer 2
 *
 */
void ledtimer_init( int interval )
{
    unsigned char tmp;
	unsigned short rr;

	TMR2_CTL = 0x00;

	/* set Timer 2 interrupt vector */
    set_vector( TMR2_IVECT, tmr2_isr );

	rr = ( unsigned short )((( SYSTEMCLOCK / 1000) * interval ) / 16 );
	TMR2_RR_H = (unsigned char)(( rr & 0xFF00 ) >> 8);
	TMR2_RR_L = (unsigned char) ( rr & 0x00FF );

#ifdef _EZ80190
	tmp = TMR2_CTL;
    TMR2_CTL = 0x5f;
#endif

#ifdef _EZ80F91
    tmp = TMR2_IIR;
    TMR2_CTL = 0x0F;
   	TMR2_IER = 0x01;
#endif

#ifdef _EZ80L92
	tmp = TMR2_CTL;
    TMR2_CTL = 0x57;
#endif

#ifdef _EZ80F92
	tmp = TMR2_CTL;
    TMR2_CTL = 0x57;
#endif

#ifdef _EZ80F93
	tmp = TMR2_CTL;
    TMR2_CTL = 0x57;
#endif

}

/*****************************************************************************
 *  wait()
 *
 *  wait routine for displaying text messages
 */
void wait( int j )
{
    timer = 0;

	while( timer < j )
	{
	    if( user_input == 1 )
		{
			user_input = 0;
			char_ready = 0;
		    pcolumn = p_user_input;
			timer = 0;
			j = 2000;
	    }
	}
}
