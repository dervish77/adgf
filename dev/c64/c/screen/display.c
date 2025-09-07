/* display.c */

#include <stdio.h>
#include <stdlib.h>

#include "peekpoke.h"
#include "display.h"

int do_screen_fill( int count, int value, int color )
{
	int r,c;
	
	int pixels = 0;
	
	int screenloc = SCREEN_TOP_LEFT_LOC;
	int colorloc = COLOR_TOP_LEFT_LOC;


	if (count > 0 && count <= 1000)
	{
        for (r = 0; r < ROWS ; r++)
		{
			for (c = 0; c < COLS ; c++)
			{
				POKE( colorloc, color );
                POKE( screenloc, value );
				//printf("screenloc = %x\n", screenloc);
				screenloc = screenloc + 1;
				colorloc = colorloc + 1;
				pixels = pixels + 1;
				#if 0
				if (pixels >= count)
				{
					return(0);
				}
				#endif
			}
		}
	}
	
	return(0);
}

int do_set_loc( int row, int col, int value, int color )
{
	int offset;
	int screenloc;
	int colorloc;
	
	if ( row <= ROWS )
	{
		if ( col <= COLS )
		{
			offset = (row * COLS) + col;
			colorloc = COLOR_TOP_LEFT_LOC + offset;
			POKE( colorloc, color );
	        screenloc = SCREEN_TOP_LEFT_LOC + offset;
			POKE( screenloc, value );			
		}
		else
		{
			return(1);
		}
	}
	else
	{
		return(1);
	}
	
	return(0);
}