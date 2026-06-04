#ifndef _SYS_I386_MACHDEF_H
#define _SYS_I386_MACHDEF_H

#define BITSCAN_FORWARD(s)  __builtin_ffs(s)

#define PAGESIZE    4096

/*
 * Machine specific stuff below
 */

#define KERNEL_CS   0x0008
#define KERNEL_DS   0x0010
#define KERNEL_GS   0x0018
#define KERNEL_FS   0x0020

#define SYSCALL_ISR 0x90

#ifndef _ASM
#endif /*_ASM*/

#endif /*_SYS_I386_MACHDEF_H*/
