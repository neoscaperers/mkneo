/*
 * Physical page buddy allocator
 */

#ifndef _SYS_MM_BUDDY_H
#define _SYS_MM_BUDDY_H

#include <sys/types.h>
#include <machdef.h>

#define BUDDY_SIZE0	(PAGESIZE)
#define BUDDY_SIZE1	(PAGESIZE*2)
#define BUDDY_SIZE2 (PAGESIZE*4)
#define BUDDY_SIZE3 (PAGESIZE*8)
#define BUDDY_SIZE4 (PAGESIZE*16)
#define BUDDY_SIZE5 (PAGESIZE*32)
#define BUDDY_SIZE6 (PAGESIZE*64)
#define BUDDY_SIZE7 (PAGESIZE*128)

#define BUDDY_SIZES	{BUDDY_SIZE0, BUDDY_SIZE1, BUDDY_SIZE2, BUDDY_SIZE3, BUDDY_SIZE4, BUDDY_SIZE5, BUDDY_SIZE6, BUDDY_SIZE7}

#define NRBUDDIES	8

#define BUDDY_INVALID	(phys_t)-1
#define BUDDY_IS_INVALID(b)	(b == BUDDY_INVALID)

struct buddydescriptor_s {
	mutex_t lock;
	bitmap_t* size_pointers[NRBUDDIES];
	bitmap_t quick_free_cache;

	struct {
		phys_t base;
		bitmap_t* bitmap_ptr;
	} free_cache[NRBUDDIES];

	size_t free_sizes[NRBUDDIES];
};

int buddy_init(phys_t mem_start, phys_t mem_end);

#endif /*_SYS_MM_BUDDY_H*/