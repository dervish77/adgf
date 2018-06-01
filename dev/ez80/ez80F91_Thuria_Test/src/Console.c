/*                                                   Copyright (c) ZiLOG, 2003
 *****************************************************************************
 *  Console.c (1.0)
 *
 *  Console I/O functions used by standard print functions...
 *****************************************************************************
 */
#include <ez80.h>
#include "Console.h"
#include "LedMatrix.h"

extern void set_vector(unsigned short vector,void (*hndlr)(void));

/* masterclock and UART 0 interrupt vectors for the various devices */
#define UART_DR 0x01
#define UART_THRE 0x20
#define UARTMODE 0x01

#ifdef _EZ80F91
#define SYSTEMCLOCK 50000000
#define UART0_IVECT 0x70
#endif

#ifdef _EZ80L92
#define SYSTEMCLOCK 48000000
#define UART0_IVECT 0x18
#endif

#ifdef _EZ80F92
#define SYSTEMCLOCK 20000000
#define UART0_IVECT 0x18
#endif

#ifdef _EZ80F93
#define SYSTEMCLOCK 20000000
#define UART0_IVECT 0x18
#endif

#ifdef _EZ80190
#define SYSTEMCLOCK 50000000
#define UART0_IVECT 0x12
#define	UART0_BRG_L	(*(ISFR)0xC0)
#define	UART0_BRG_H	(*(ISFR)0xC1)
#define	UART0_RBR	(*(ISFR)0xC0)
#define	UART0_THR	(*(ISFR)0xC0)
#define	UART0_IER	(*(ISFR)0xC1)
#define	UART0_IIR	(*(ISFR)0xC2)
#define	UART0_FCTL	(*(ISFR)0xC2)
#define	UART0_LCTL	(*(ISFR)0xC3)
#define	UART0_MCTL	(*(ISFR)0xC4)
#define	UART0_LSR	(*(ISFR)0xC5)
#define	UART0_MSR	(*(ISFR)0xC6)
#define	UART0_SPR	(*(ISFR)0xC7)
#endif


/* character ready flag */
char char_ready;
/* received character holder */
unsigned char char_rcvd;

/*****************************************************************************
 *  UART 0 interrupt service routine
 *
 *  designed for recieve interrupt only
 */
void interrupt uart0_isr( void )
{
    char_ready = 1;
	user_input = 1;
	char_rcvd = UART0_RBR;
	p_user_input = &matrix_char_map[char_rcvd - 31][0];
}


/*****************************************************************************
 *  console_init()
 *
 *  initializes console port -- UART0
 *  
 *  Parameters:
 *  57600 bps, 8 Data bits, 1 Stop bit, No Parity bit
 */
void console_init( int baudrate )
{
	unsigned short brg;

	brg = (unsigned short)(SYSTEMCLOCK / (baudrate * 16));

	//Set the PortD bits D1,D0 to Alternate function mode
	PD_ALT2 = 0x03;
	PD_ALT1 = 0x00;
	PD_DDR = 0xFF;
	PD_DR = 0x00;

    /* set UART0 interrupt vector */
    set_vector( UART0_IVECT, uart0_isr );

	UART0_LCTL |= 0x80; 			//Set DLAB, dont disturb other bits
	/* Set UART baudrate */
	UART0_BRG_L = (unsigned char) ( brg & 0x00FF );        //Load divisor low
	UART0_BRG_H = (unsigned char)(( brg & 0xFF00 ) >> 8);  //Load divisor high

	/* Clear DLAB, configure for 8 data bits, no parity, 1 stop bit  */
	UART0_LCTL = 0x03; 		    //Reset DLAB, dont disturb other bits

	/* Enable recieve interrupt only */
    UART0_IER = 0x01;

	char_ready = 0;
}

/*****************************************************************************
 *  kbhit()
 *
 *  wait for input
 */
int kbhit(void)
{
    while ( char_ready != 1 );

	char_ready = 0;
}

/*****************************************************************************
 *  putch()
 *
 *  waits for an empty transmit holding register and puts a character in it
 */
void putch(unsigned char ch)
{
	while ((UART0_LSR & UART_THRE) == 0);
	UART0_THR = (unsigned char)ch;

	if ((unsigned char)ch == '\n')
	{
		while ((UART0_LSR & UART_THRE) == 0);
		UART0_THR = '\r';
	}
}

/*****************************************************************************
 *  getch()
 *
 *  waits for a character to be received and gets it from UART recieve buffer
 */
unsigned char getch(void)
{
	kbhit();
	return( char_rcvd );
}

/*****************************************************************************
 *  getche()
 *
 *  waits for a character to be received and gets it from UART recieve buffer
 *  with echo
 */
unsigned char getche(void)
{
    unsigned char ch;

   	kbhit();
	putch( char_rcvd );
	return( char_rcvd );
}
