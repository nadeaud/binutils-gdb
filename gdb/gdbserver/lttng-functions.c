/*
 * lttng-functions.c
 *
 *  Created on: Apr 5, 2016
 *      Author: didier
 */

#include <stdio.h>

#include "lttng-functions.h"

#ifdef IN_PROCESS_AGENT
#include "lttng-collect.h"
#endif

unsigned long traceframe_id=0;

int collector_size[] = {
		8,
		16,
		24
};

int get_lttng_trace_function(int size)
{
	int i;

	if(size == 0)
		return -1;
	if(size > collector_size[NUMBER_COLLECTOR_FUNCTIONS-1])
		return -1;

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

unsigned long 
get_traceframe()
{
	static __thread unsigned long id = 0;

	return id++;
}

#ifdef IN_PROCESS_AGENT

void _trace_16bytes(void * tpoint, void * tpoint_hit, int tpoint_number, unsigned long stop_pc)
{
	unsigned char buf[16];
	unsigned long traceframe_id = get_traceframe();

	general_lttng_tracepoint(tpoint, tpoint_hit, stop_pc, traceframe_id, buf);

	tracepoint(gdb_trace, lttng_16bytes, tpoint_number, traceframe_id, buf);
}

#endif



