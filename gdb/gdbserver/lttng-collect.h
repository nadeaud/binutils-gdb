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
    	int, tp_id,/*
		uint64_t, address,*/
        unsigned char*, array8
    ),
    TP_FIELDS(
         ctf_integer(int, tp_id, tp_id)
//       ctf_integer(uint64_t, tp_address, address)
        ctf_array(unsigned char, data, array8, 8)
    )
)

TRACEPOINT_EVENT(
    gdb_trace,
    lttng_16bytes,
    TP_ARGS(/*
        	uint32_t, tp_id,
			uint64_t, address,*/
    		unsigned char*, array16
    ),
    TP_FIELDS(
//        ctf_integer(uint32_t, tp_id, tp_id)
//        ctf_integer(uint64_t, tp_address, address)
        ctf_array(unsigned char, data, array16, 16)
    )
)

TRACEPOINT_EVENT(
    gdb_trace,
    lttng_24bytes,
    TP_ARGS(/*
        	uint32_t, tp_id,
        	uint64_t, address,*/
    		unsigned char*, array24
    ),
    TP_FIELDS(
//        ctf_integer(uint32_t, tp_id, tp_id)
//    	ctf_integer(uint64_t, tp_address, address)
        ctf_array(unsigned char, data, array24, 24)
    )
)




TRACEPOINT_EVENT(
    gdb_trace,
    amd64_registers,
    TP_ARGS(/*
        uint32_t, tp_id,
        uint64_t, address,*/
        uint64_t, rax,
		uint64_t, rbx,
		uint64_t, rcx,
		uint64_t, rdx/*,
		uint64_t, rsi,
		uint64_t, rdi,
		uint64_t, rbp,
		uint64_t, rsp,
		uint64_t, r8,
		uint64_t, r9,
		uint64_t, r10,
		uint64_t, r11,
		uint64_t, r12,
		uint64_t, r13,
		uint64_t, r14,
		uint64_t, r15,
		uint64_t, rip*/
    ),
    TP_FIELDS(
//        ctf_integer(uint32_t, tp_id, tp_id)
//    	ctf_integer(uint64_t, tp_address, address)
        ctf_integer(uint64_t, my_rax, rax)
		ctf_integer(uint64_t, my_rbx, rbx)
		ctf_integer(uint64_t, my_rcx, rcx)
		ctf_integer(uint64_t, my_rdx, rdx)/*
		ctf_integer(uint64_t, my_rsi, rsi)
		ctf_integer(uint64_t, my_rdi, rdi)
		ctf_integer(uint64_t, my_rbp, rbp)
		ctf_integer(uint64_t, my_rsp, rsp)
		ctf_integer(uint64_t, my_r8, r8)
		ctf_integer(uint64_t, my_r9, r9)
		ctf_integer(uint64_t, my_r10, r10)
		ctf_integer(uint64_t, my_r11, r11)
		ctf_integer(uint64_t, my_r12, r12)
		ctf_integer(uint64_t, my_r13, r13)
		ctf_integer(uint64_t, my_r14, r14)
		ctf_integer(uint64_t, my_r15, r15)
		ctf_integer(uint64_t, my_rip, rip)*/
    )
)

#endif /* _HELLO_TP_H */

#include <lttng/tracepoint-event.h>
