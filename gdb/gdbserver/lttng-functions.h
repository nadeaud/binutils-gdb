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
