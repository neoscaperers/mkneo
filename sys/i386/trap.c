//
//  trap.c
//  
//
//  Created by neo on 6/4/26.
//

#include <sys/types.h>

#include <trap.h>
#include <machdef.h>

/*
 .extern i386_trap_div
 .extern i386_trap_debug
 .extern i386_trap_nmi
 .extern i386_trap_bounderflow
 .extern i386_trap_segmentfault
 .extern i386_trap_stacksegfault
 .extern i386_trap_pagefault
 .extern i386_trap_fpusimd
 .extern i386_trap_other
 */

extern struct i386_descriptor_s _idt[];
extern char _idtr[];

static void build_isr(struct i386_descriptor_s* isr, int dpl, int type) {
    uint32_t base = isr->low;
    isr->low &= 0xffff;
    isr->low |= (KERNEL_CS << 16);
    isr->high = (base & 0xffff0000);
    isr->high |= (1 << 15) | (dpl << 13) | (1 << 11);
    isr->high |= (6 | type) << 8;
}

/*
 * note - The low 32 bits of each ISR is pre-populated with a pointer to a handler function
 */
void i386_init_idt(void) {
    int i;
    
    for (i = 0; i < 256; i++) {
        build_isr(&_idt[i], (i == SYSCALL_ISR) ? 3 : 0, ((i >= 32) && (i < 48)) ? ISR_INTR : ISR_TRAP);
    }
    
    __asm__ volatile ("lidt (%0)" : :"a"(&_idtr));
}

void i386_trap_div(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_debug(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_nmi(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_bounderflow(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_segmentfault(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_stacksegfault(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_pagefault(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_fpusimd(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_other(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_instruction(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_doublefault(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_invalidtss(struct i386_trapframe_s* trapframe) {
    return;
}

void i386_trap_accessfault(struct i386_trapframe_s* trapframe) {
    return;
}
