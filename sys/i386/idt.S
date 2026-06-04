;
//  idt.S
//  
//
//  Created by neo on 6/4/26.
//

#define _ASM
#include <machdef.h>

.altmacro
.macro TRAP id handler
.globl _trap_\id
_trap_\id:
.if (!(id == 8 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 17 || id == 21))
    pushl $0
.endif
    pushl $\id
    pushl %gs
    pushl %fs
    pushal
.if (id == 14)
    movl %cr2, %eax
    pushl %eax
.else
    pushl $0
.endif
    movl $\handler, %edi
    jmp _trapsecondhalf
.endm

.macro ISRPTR id
.long _trap_\id
.endm

.section .text

.globl _trapsecondhalf

/*
 * on entry:
 * %edi - pointer to function that handles this exception
 * %esp - contains the old register states
 * 68(%esp) - %ss
 * 64(%esp) - %esp
 * 60(%esp) - %eflags
 * 56(%esp) - %cs
 * 52(%esp) - %eip
 * 48(%esp) - error code
 * 44(%esp) - interrupt number
 * 40(%esp) - %gs
 * 36(%esp) - %fs
 * 32(%esp) - %edi
 * 28(%esp) - %esi
 * 24(%esp) - %ebp
 * 20(%esp) - (garbage ESP)
 * 16(%esp) - %ebx
 * 12(%esp) - %edx
 * 8(%esp) - %ecx
 * 4(%esp) - %eax
 * 0(%esp) - %cr2
 */
_trapsecondhalf:
    cld
    pushl %esp
    call *%edi
    add $20, %esp
    popal
    iretl

.globl _trapuserdefined
_trapuserdefined:
    ret

.extern i386_trap_div
.extern i386_trap_debug
.extern i386_trap_nmi
.extern i386_trap_bounderflow
.extern i386_trap_segmentfault
.extern i386_trap_stacksegfault
.extern i386_trap_pagefault
.extern i386_trap_fpusimd
.extern i386_trap_other
.extern i386_trap_instruction
.extern i386_trap_doublefault
.extern i386_trap_invalidtss
.extern i386_trap_accessfault
.extern i386_syscall

TRAP 0, i386_trap_div
TRAP 1, i386_trap_debug
TRAP 2, i386_trap_nmi
TRAP 3, i386_trap_debug
TRAP 4, i386_trap_bounderflow
TRAP 5, i386_trap_bounderflow
TRAP 6, i386_trap_instruction
TRAP 7, i386_trap_fpusimd
TRAP 8, i386_trap_doublefault
TRAP 9, i386_trap_fpusimd
TRAP 10, i386_trap_invalidtss
TRAP 11, i386_trap_segmentfault
TRAP 12, i386_trap_stacksegfault
TRAP 13, i386_trap_segmentfault
TRAP 14, i386_trap_pagefault
TRAP 15, i386_trap_other
TRAP 16, i386_trap_fpusimd
TRAP 17, i386_trap_accessfault
TRAP 18, i386_trap_nmi
TRAP 19, i386_trap_fpusimd
TRAP 20, i386_trap_other
TRAP 21, i386_trap_other
TRAP 22, i386_trap_other
TRAP 23, i386_trap_other
TRAP 24, i386_trap_other
TRAP 25, i386_trap_other
TRAP 26, i386_trap_other
TRAP 27, i386_trap_other
TRAP 28, i386_trap_other
TRAP 29, i386_trap_other
TRAP 30, i386_trap_other
TRAP 31, i386_trap_other
.set i, 32
.rept 224
.if (i == SYSCALL_ISR)
TRAP %i, i386_syscall
.else
TRAP %i, _trapuserdefined
.endif
.set i, i + 1
.endr

.section .data

.align 8
.globl _idt

_idt:
.set i, 0
.rept 256
    ISRPTR %i
    .long 0
.set i, i + 1
.endr

.globl _idtr

_idtr:
    .word (256 * 8) - 1
    .long _idt
