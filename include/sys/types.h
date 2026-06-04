#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <types.h>

typedef int kern_return_t;

typedef int mk_prim_t;
typedef mk_prim_t mk_port_t;
typedef mk_prim_t mk_type_t;
typedef mk_port_t mk_msg_port_t;
typedef mk_port_t mk_rpc_port_t;
typedef mk_prim_t mk_pid_t;
typedef mk_prim_t mk_tid_t;
typedef uint64_t mk_tag_t;

typedef size_t limit_t;
typedef intptr_t virt_t;

typedef size_t bitmap_t;

#endif /*_SYS_TYPES_H*/