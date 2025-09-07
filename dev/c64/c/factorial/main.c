/* factorial for C64 */

#include <stdio.h>
#include <stdlib.h>

#include "peekpoke.h"

#include "fact.h"

#define USE_COLOR 1

int main( void )
{	
	int number = 0;
	unsigned int result = 0;
	
	int done = 0;
	char answer[4];
	
#ifdef USE_COLOR
	POKE( 0xd020, 13 ); /* set border to green */
	POKE( 0xd021, 0 ); /* set background to black */
	POKE( 646, 1 );   /* set text to white */
#endif	

	while (!done)
	{
		printf("\n### Factorial C64 ###\n");
		printf("\n");
		printf("Enter a number? ");
		scanf("%d", &number );
		
		if ( number <= MAXVALUE )
		{
			printf("\n");
			result = do_fact( number );
			printf("Factorial(%d) is %u\n", number, result);
		}
		else
		{
			printf("ERROR: enter number less than %d\n", MAXVALUE );
			done = 1;
		}
		
		if (!done)
		{
			printf("\nRun again (y/n)?");
			scanf("%s", &answer);
			if (answer[0] == 'n') done = 1;
		}
	}
    
    return EXIT_SUCCESS;
}
