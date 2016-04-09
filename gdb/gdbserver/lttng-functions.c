/*
 * lttng-functions.c
 *
 *  Created on: Apr 5, 2016
 *      Author: didier
 */

#include "lttng-functions.h"

int collector_size[] = {
		8,
		16,
		24
};

int get_lttng_trace_function(int size)
{
	if(size == 0)
		return -1;
	if(size > collector_size[NUMBER_COLLECTOR_FUNCTIONS-1])
		return -1;

	int i;
	for( i=0; i<NUMBER_COLLECTOR_FUNCTIONS; ++i)
	{
		if(size <= collector_size[i])
			return i;
	}

	return -1;
}
