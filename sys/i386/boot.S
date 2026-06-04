
#define _ASM
#include <sys/i386/multiboot.h>

#define BOOT_STACK  0x7c00
#define BOOT_PTBASE 0

.section .multiboot, "aw"
.globl mbheader
.type mbheader, @object
.align 4096
mbheader:
    .long MULTIBOOT_MAGIC
    .long MULTIBOOT_FLAGS
    .long -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
    .long 0


.globl _higherhalf_start
.type _higherhalf_start, @function

.globl _start
.type _start, @function
/*
 * mkneo Entry point for i386
 */
_start:
    cli
    mov $BOOT_STACK, %esp
    mov $BOOT_PTBASE, %edi
    push %ebx
    push %eax
/* Build an initial page table */
    mov $4096, %ecx
    xor %eax, %eax
    cld
    rep stosb
    mov $4096, %ecx
    rep stosb
    movl $((BOOT_PTBASE + 4096) | 3), BOOT_PTBASE
    movl $((BOOT_PTBASE + 4096) | 3), (BOOT_PTBASE + (768*4))
    
    mov $1024, %ecx
    xor %edx, %edx
    mov $(BOOT_PTBASE + 4096), %ebp
.looptop:
    mov %edx, %eax
    lea (%ebp, %edx, 4), %esi
    shl $12, %eax
    or $3, %eax
    mov %eax, (%esi)
    inc %edx
    loop .looptop

    mov $BOOT_PTBASE, %eax
    mov %eax, %cr3
    mov %cr0, %eax
    or $(1<<31), %eax
    mov %eax, %cr0

    jmp _higherhalf_start

.section .rodata
.align 8
_gdt:
    .quad 0
    .quad 0xCF98000000FFFF
    .quad 0xCF92000000FFFF
    .quad 0xCFF8000000FFFF
    .quad 0xCFF2000000FFFF

_gdtr:
    .word (8 * 5) - 1
    .long _gdt

.section .text

.extern archentry

_higherhalf_start:
    mov $_gdtr, %eax
    lgdt (%eax)
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    ljmp $0x08,$.pm
.pm:    
    call archentry
    cli
    hlt