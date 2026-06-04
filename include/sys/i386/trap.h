//
//  trap.h
//  
//
//  Created by neo on 6/4/26.
//

#ifndef _SYS_I386_TRAP_H
#define _SYS_I386_TRAP_H

#include <sys/types.h>

/*
 * on entry:
 * %edi - pointer to function that handles this exception
 * %esp - contains the old register states
 * 64(%esp) - %ss
 * 60(%esp) - %esp
 * 56(%esp) - %eflags
 * 52(%esp) - %cs
 * 48(%esp) - %eip
 * 44(%esp) - error code
 * 40(%esp) - interrupt number
 * 36(%esp) - %gs
 * 32(%esp) - %fs
 * 28(%esp) - %edi
 * 24(%esp) - %esi
 * 20(%esp) - %ebp
 * 16(%esp) - (garbage ESP)
 * 12(%esp) - %ebx
 * 8(%esp) - %edx
 * 4(%esp) - %ecx
 * 0(%esp) - %eax
 */
struct i386_trapframe_s {
    uint32_t cr2;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t _garbage;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t fs;
    uint32_t gs;
    uint32_t intnum;
    uint32_t ecode;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
} __attribute__((packed));

struct i386_descriptor_s {
    uint32_t low;
    uint32_t high;
} __attribute__((packed));

#define ISR_TRAP    0
#define ISR_INTR    1

#endif /*_SYS_I386_TRAP_H*/
