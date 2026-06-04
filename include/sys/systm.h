#ifndef _SYS_SYSTM_H
#define _SYS_SYSTM_H

#ifdef _KERNEL

#include <sys/types.h>
#include <sys/boot.h>

void kern_init(struct boot_s* bootstruct);
void* boot_bump(size_t amt, size_t align);

#endif /*_KERNEL*/

#endif /*_SYS_SYSTM_H*/
