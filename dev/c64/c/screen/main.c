/* fibonacci for C64 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "peekpoke.h"

#include "display.h"

#define USE_COLOR 1

int main( void )
{	
	int i;
	int count = 1;
	
	int fore_color = COLOR_PURPLE;
	int fore_value = 0xA0;
	
	int fill_color = COLOR_BLACK;
	int fill_value = 0x20;
	
#ifdef USE_COLOR
	POKE( 0xd020, 13 ); /* set border to green */
	POKE( 0xd021, 0 ); /* set background to black */
	POKE( 646, 1 );   /* set text to white */
#endif	

	printf("### Screen Write Test ###\n");
	printf("\n");
	
	do_screen_fill( count, fill_value, fill_color );
			
	for (i=0; i<10; i++)
	{
		do_set_loc( 0, i+0, fore_value, fore_color );
		do_set_loc( 1, i+1, fore_value, fore_color );
		do_set_loc( 2, i+2, fore_value, fore_color );
		do_set_loc( 3, i+3, fore_value, fore_color );
		do_set_loc( 4, i+4, fore_value, fore_color );
		do_set_loc( 5, i+5, fore_value, fore_color );
		do_set_loc( 6, i+6, fore_value, fore_color );
		do_set_loc( 7, i+7, fore_value, fore_color );

		sleep(1);
		
		do_set_loc( 0, i+0, fill_value, fill_color );
		do_set_loc( 1, i+1, fill_value, fill_color );
		do_set_loc( 2, i+2, fill_value, fill_color );
		do_set_loc( 3, i+3, fill_value, fill_color );
		do_set_loc( 4, i+4, fill_value, fill_color );
		do_set_loc( 5, i+5, fill_value, fill_color );
		do_set_loc( 6, i+6, fill_value, fill_color );
		do_set_loc( 7, i+7, fill_value, fill_color );
	}
	
	while (1);
	
    return EXIT_SUCCESS;
}
