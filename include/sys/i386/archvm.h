#ifndef _SYS_I386_ARCHVM_H
#define _SYS_I386_ARCHVM_H

#define UPPERHALF   0xC0000000

#define PT_PRESENT  1
#define PT_WRITE    2
#define PT_USER     4
#define PT_WRTHRU   8
#define PT_NOCACHE  16
#define PT_ACCESSED 32
#define PT_DIRTY    64
#define PT_WIRED    512

#define PT(a, f)    (((a) & ~0xFFF) | (f))

#endif /*_SYS_I386_ARCHVM_H*/

