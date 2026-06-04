#include <sys/types.h>

extern char _kernel_end[];
size_t bump_amount = 0;

/*
 * Basic early-boot bump allocator
 */
void* boot_bump(size_t amount, size_t align) {
    void* ptr; 
    bump_amount = (bump_amount + (align - 1)) & ~(align - 1);
    ptr = (void*)((uintptr_t)_kernel_end + bump_amount);
    bump_amount += amount;
    return ptr;
}