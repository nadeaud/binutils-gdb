/*
 * lttng-functions.c
 *
 *  Created on: Apr 5, 2016
 *      Author: didier
 */

#include "stdio.h"

#include "lttng-functions.h"

unsigned long traceframe_id=0;

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
		{
			printf("\n%d bytes collector selected\n", collector_size[i]);
			return i;
		}
	}

	return -1;
}

unsigned long get_traceframe()
{
	unsigned long result = 1;
	__asm__ __volatile__ ("lock; xadd %0, %1"
	            :"=r"(result), "=m"(traceframe_id)
	            :"r"(result), "m"(traceframe_id)
	            :"memory");
	return result;
}


