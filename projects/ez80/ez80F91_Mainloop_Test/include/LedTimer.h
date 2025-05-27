/*
 *****************************************************************************
 *  LedTimer.h
 *
 *****************************************************************************
 */

extern void ledtimer_init( int interval );
extern void interrupt tmr2_isr( void );
extern void wait( int j );

extern int timer;
