/* fib.c */

#include <stdio.h>
#include <stdlib.h>

#include "fib.h"

void do_fib( int count )
{
	int i;
	
	int previous2 = 0;
	int previous1 = 1;
	int current = 1;
			
	printf("%d\n", previous2);
	
	if (count > 1)
	{
		printf("%d\n", previous1);
		
		if (count > 2)
		{
			for (i = 3; i <= count ; i++)
			{
				current = previous2 + previous1;
				printf("%d\n", current);
				previous2 = previous1;
				previous1 = current;
			}
		}
	}
}

