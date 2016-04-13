#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER gdb_trace

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./lttng-collect.h"

#if !defined(_LTTNG_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _LTTNG_TP_H

#include <lttng/tracepoint.h>
#include <stdint.h>

TRACEPOINT_EVENT(
    gdb_trace,
    lttng_8bytes,
    TP_ARGS(
    	int, tp_id,
	unsigned long, traceframe_id,
        unsigned char*, array8
    ),
    TP_FIELDS(
         ctf_integer(int, tp_id, tp_id)
	ctf_integer(unsigned long, traceframe_id, traceframe_id)
        ctf_array(unsigned char, data, array8, 8)
    )
)

TRACEPOINT_EVENT(
    gdb_trace,
    lttng_16bytes,
    TP_ARGS(
        int, tp_id,
	unsigned long, traceframe_id,
    	unsigned char*, array16
    ),
    TP_FIELDS(
        ctf_integer(int, tp_id, tp_id)
	ctf_integer(unsigned long, traceframe_id, traceframe_id)
        ctf_array(unsigned char, data, array16, 16)
    )
)

TRACEPOINT_EVENT(
    gdb_trace,
    lttng_24bytes,
    TP_ARGS(
        uint32_t, tp_id,
    	unsigned long, traceframe_id,
   	unsigned char*, array24
    ),
    TP_FIELDS(
        ctf_integer(uint32_t, tp_id, tp_id)
    	ctf_integer(unsigned long, traceframe_id, traceframe_id)
        ctf_array(unsigned char, data, array24, 24)
    )
)

TRACEPOINT_EVENT(
    gdb_trace,
    amd64_registers,
    TP_ARGS(
        int, tp_id,
	unsigned long, traceframe_id,
    	unsigned char*, reg
    ),
    TP_FIELDS(
        ctf_integer(int, tp_id, tp_id)
	ctf_integer(unsigned long, traceframe_id, traceframe_id)
        ctf_array(unsigned char, registers, reg, 544)
    )
)

/*
TRACEPOINT_EVENT(
    gdb_trace,
    amd64_registers,
    TP_ARGS(
        int, tp_id,
        unsigned long, rax,
		unsigned long, rbx,
		unsigned long, rcx,
		unsigned long, rdx,
		unsigned long, rsi,
		unsigned long, rdi,
		unsigned long, rbp,
		unsigned long, rsp,
		unsigned long, r8,
		unsigned long, r9,
		unsigned long, r10,
		unsigned long, r11,
		unsigned long, r12,
		unsigned long, r13,
		unsigned long, r14,
		unsigned long, r15,
		unsigned long, rip
    ),
    TP_FIELDS(
        ctf_integer(uint32_t, tp_id, tp_id)
        ctf_integer(unsigned long, my_rax, rax)
		ctf_integer(unsigned long, my_rbx, rbx)
		ctf_integer(unsigned long, my_rcx, rcx)
		ctf_integer(unsigned long, my_rdx, rdx)
		ctf_integer(unsigned long, my_rsi, rsi)
		ctf_integer(unsigned long, my_rdi, rdi)
		ctf_integer(unsigned long, my_rbp, rbp)
		ctf_integer(unsigned long, my_rsp, rsp)
		ctf_integer(unsigned long, my_r8, r8)
		ctf_integer(unsigned long, my_r9, r9)
		ctf_integer(unsigned long, my_r10, r10)
		ctf_integer(unsigned long, my_r11, r11)
		ctf_integer(unsigned long, my_r12, r12)
		ctf_integer(unsigned long, my_r13, r13)
		ctf_integer(unsigned long, my_r14, r14)
		ctf_integer(unsigned long, my_r15, r15)
		ctf_integer(unsigned long, my_rip, rip)
    )
)
*/
#endif /* _HELLO_TP_H */

#include <lttng/tracepoint-event.h>
