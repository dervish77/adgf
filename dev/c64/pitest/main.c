/* pitest for C64 */

#include <stdio.h>
#include <stdlib.h>

#include "peekpoke.h"

#include "pi.h"

#define USE_COLOR 1

int main( void )
{	
   int numdigits = 10;
	
#ifdef USE_COLOR
	POKE( 0xd020, 13 ); /* set border to green */
	POKE( 0xd021, 0 ); /* set background to black */
	POKE( 646, 1 );   /* set text to white */
#endif	

	printf("### PI Test C64 ###\n");
	printf("\n");
	printf("- how many digits? ");
	scanf("%d", &numdigits );
	
	if ( numdigits > MINCOUNT && numdigits <= MAXCOUNT )
	{
		printf("\n");
		//CalcPi64( numdigits );
		CalcPiDiv( numdigits );
		printf("\n");
	}
	else
	{
		printf("ERROR: enter number between %d and %d\n", MINCOUNT, MAXCOUNT );
	}
    
    return EXIT_SUCCESS;
}
