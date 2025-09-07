/* fact.c */

#include <stdio.h>
#include <stdlib.h>

#include "fact.h"

unsigned int do_fact( int num )
{
	if (num <= 0)
	{
		return 1;
	}
	else
	{
		return (num * do_fact(num - 1));
	}
}

