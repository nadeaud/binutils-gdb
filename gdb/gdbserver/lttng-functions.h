/*
 * lttng-functions.h
 *
 *  Created on: Apr 4, 2016
 *      Author: didier
 */

#ifndef GDB_GDBSERVER_LTTNG_FUNCTIONS_H_
#define GDB_GDBSERVER_LTTNG_FUNCTIONS_H_

#define NUMBER_COLLECTOR_FUNCTIONS 3
#define STEP_COLLECTOR_FUNCTIONS 8

//typedef void (*lttng_collect_fcnt)(struct tracepoint_hit_ctx *ctx, CORE_ADDR stop_pc, struct tracepoint *tpoint);

int get_lttng_trace_function(int size);

unsigned long get_traceframe();

#endif /* GDB_GDBSERVER_LTTNG_FUNCTIONS_H_ */

#ifdef IN_PROCESS_AGENT

void _trace_16bytes(void * tpoint, void * tpoint_hit, int tpoint_number, unsigned long stop_pc);

//void general_lttng_tracepoint(struct tracepoint_hit_ctx *ctx, CORE_ADDR stop_pc, struct tracepoint *tpoint);
//void general_lttng_tracepoint(void *ptr_tpoint, void * ptr_tpoint_hit, unsigned long stop_pc, int traceframe_id, unsigned char *buf);

#endif
