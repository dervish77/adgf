/* fibonacci for C128 */

#include <stdio.h>
#include <stdlib.h>

#include "peekpoke.h"

#include "fib.h"

#define USE_COLOR 1

int main( void )
{	
	int results = 0;
	int done = 0;
	char answer[4];
	
#ifdef USE_COLOR
	POKE( 0xd020, 13 ); /* set border to green */
	POKE( 0xd021, 0 ); /* set background to black */
	POKE( 646, 1 );   /* set text to white */
#endif	

	while (!done)
	{
		printf("\n### Fibonacci C64 ###\n");
		printf("\n");
		printf("- how many results? ");
		scanf("%d", &results );
		
		if ( results > MINCOUNT && results <= MAXCOUNT )
		{
			printf("\n");
			do_fib( results );
			printf("\n");
		}
		else
		{
			printf("ERROR: enter number between %d and %d\n", MINCOUNT, MAXCOUNT );
			done = 1;
		}
		
		if (!done)
		{
			printf("Run again (y/n)?");
			scanf("%s", &answer);
			if (answer[0] == 'n') done = 1;
		}
	}
    
    return EXIT_SUCCESS;
}
