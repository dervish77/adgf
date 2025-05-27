/*                                                   Copyright (c) ZiLOG, 2003
 *****************************************************************************
 *  main.c (1.0)
 *
 *  eZ80 Development Board demonstration program
 *
 *  This project displays a text message on the 5x7 LED matrix.
 *
 *****************************************************************************
 */

#include <ez80.h>
#include <stdio.h>

#include "Console.h"
#include "LedMatrix.h"
#include "LedTimer.h"
#include "Buttons.h"

#include "main.h"

BOOLEAN_T suppress_intro = FALSE;


extern void DisplayIntroduction(void);
extern void DisplayTitle(void);
extern void LoadGame(GAME_S_T *game);
extern void SaveGame(GAME_S_T *game);
extern void InitGame(GAME_S_T *game);
extern void PlayGame(GAME_S_T *game);
extern void CloseAll(GAME_S_T *game);


extern void _init_default_vectors( void );

/* device names -- chosen at build-time */
#ifdef _EZ80190
char device_name[] = "eZ80190";
#endif
#ifdef _EZ80L92
char device_name[] = "eZ80L92";
#endif
#ifdef _EZ80F93
char device_name[] = "eZ80F93";
#endif
#ifdef _EZ80F92
char device_name[] = "eZ80F92";
#endif
#ifdef _EZ80F91
char device_name[] = "eZ80F91";
#endif

const char version[] = "1.0";

/*****************************************************************************
 *  main()
 *
 *  - initializes LED matrix, timer, buttons(gpio), and console
 *  - sends welcome message and instruction to console
 *  - displays simple spin and full matrix blink test
 *  - continually displays device name on LED matrix
 */
void main( void )
{
#if 0
    char i, ch;
	char buffer[128];
	int count=0;

    /* initialize system peripherals */
    _init_default_vectors();
    ledmatrix_init();
	ledtimer_init( 1 );  /* 1 mS interval */
	buttons_init();
    console_init( 57600 );

    /* flash full LED matrix */
    ledmatrix_flash();
    /* show a rotating bar on the LED matrix */
    ledmatrix_spin();
   	
	/* console welcome message and instruction */
	printf( "\n  ZiLOG Development Board Demonstration Program (%s)", version );
	printf( "\n        Featuring the %s\n", device_name );

	printf( "\n  Console Test Program:\n" );

	printf(">> ");
	ledmatrix_clear();

	/* main demonstration loop */
	while( 1 )
	{

        /* display device name on LED Matrix one character at a time */
		ledmatrix_puts( device_name );

		/* wait a half a second */
        wait( 500 );

		ch = getchar();
		if (ch == '\r')
		{
			buffer[count] = '\0';
			count = 0;

			printf("You typed - %s\n", buffer);
			printf(">> ");	
		}
		else
		{
			buffer[count] = ch;
			count++;
		}
	}
#endif

   GAME_S_T game;
   int i;


   /*  initialize game
    */
   InitGame(&game);


   /*  prompt for introduction
    */
   if ( !suppress_intro )
   {
      DisplayIntroduction();
   }


   /*  display title block
    */
   DisplayTitle();


   /*  start playing the game
    */
   if (game.load_game) 
   {
      LoadGame(&game);
   }


   /*  start playing the game
    */
   PlayGame(&game);


   /*  close all files
    */
   CloseAll(&game);

}



