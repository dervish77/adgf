/* hello world for C64 */

#include <stdio.h>
#include <stdlib.h>

#include "peekpoke.h"

#define USE_COLOR 1

int main( void )
{
	int i;
	
#ifdef USE_COLOR
	POKE( 0xd020, 0x4 ); /* set border to black */
	POKE( 0xd021, 0 ); /* set background to black */
	POKE( 646, 1 );   /* set text to white */
#endif	
	
	for (i = 0 ; i < 10 ; i++)
	{
		printf("Hello C64\n");
	}
    
    return EXIT_SUCCESS;
}
