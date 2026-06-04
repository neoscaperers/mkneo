#ifndef _SYS_I386_BOOTBUMP_H
#define _SYS_I386_BOOTBUMP_H
#include <sys/types.h>

void* boot_bump(size_t amount, size_t align);
#endif /*_SYS_I386_BOOTBUMP_H*/

