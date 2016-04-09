/*
 * lttng-functions.c
 *
 *  Created on: Apr 4, 2016
 *      Author: didier
 */

//#define IN_PROCESS_AGENT
//#include "lttng-functions.h"

//#ifdef IN_PROCESS_AGENT

#define TRACEPOINT_CREATE_PROBES
#define TRACEPOINT_DEFINE


#include "lttng-collect.h"
//#include "tracepoint.h"

/*
extern struct tracepoint_hit_ctx;
extern struct tracepoint_action;
extern struct traceframe;
static void do_action_at_lttng_tracepoint (struct tracepoint_hit_ctx *ctx,
				     CORE_ADDR stop_pc,
				     struct tracepoint *tpoint,
				     struct traceframe *tframe,
				     struct tracepoint_action *taction,
					 unsigned char * buf);
*/
/*
void trace_8bytes(struct tracepoint_hit_ctx *ctx, CORE_ADDR stop_pc, struct tracepoint *tpoint)
{
	char buf[8];
	struct traceframe *tframe;
	int acti;

	for (acti = 0; acti < tpoint->numactions; ++acti)
	{
		do_action_at_lttng_tracepoint (ctx, stop_pc, tpoint, tframe,tpoint->actions[acti], buf);
	}
	tracepoint(gdb_trace, lttng_8bytes, buf);
}

void trace_16bytes(struct tracepoint_hit_ctx *ctx, CORE_ADDR stop_pc, struct tracepoint *tpoint)
{
	char buf[16];
	struct traceframe *tframe;
	int acti;

	for (acti = 0; acti < tpoint->numactions; ++acti)
	{
		do_action_at_lttng_tracepoint (ctx, stop_pc, tpoint, tframe,tpoint->actions[acti]);
	}
	tracepoint(gdb_trace, lttng_16bytes, buf);
}

void trace_24bytes(struct tracepoint_hit_ctx *ctx, CORE_ADDR stop_pc, struct tracepoint *tpoint)
{
	char buf[24];
	struct traceframe *tframe;
	int acti;

	for (acti = 0; acti < tpoint->numactions; ++acti)
	{
		do_action_at_lttng_tracepoint (ctx, stop_pc, tpoint, tframe,tpoint->actions[acti]);
	}
	tracepoint(gdb_trace, lttng_24bytes, buf);
}

lttng_collect_fcnt collect_functions[3] = {
		&trace_8bytes,
		&trace_16bytes,
		&trace_24bytes
};
*/
/*
#else

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

#endif
*/
