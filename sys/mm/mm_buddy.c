#include <sys/types.h>
#include <sys/systm.h>
#include <sys/kcons.h>
#include <sys/mm/buddy.h>

static size_t buddy_sizes[NRBUDDIES] = BUDDY_SIZES;

struct buddydescriptor_s buddy;

/*
 * Creates a free bitmap for a buddy size using the early-boot bump allocator.
 */
static int create_buddies(int size_index, phys_t mem_start, phys_t mem_end) {
	size_t size = buddy_sizes[size_index];
	size_t nrbuddies = ((mem_end - mem_start) / size) / (sizeof(bitmap_t) * 8);
	size_t i;
	bitmap_t* ptr = boot_bump(nrbuddies * (sizeof(bitmap_t)), sizeof(bitmap_t));

	if (ptr == NULL)
		return 1;

	buddy.size_pointers[size_index] = ptr;

	for (i = 0; i < nrbuddies; i++) {
		ptr[i] = (bitmap_t)-1;
	}

	buddy.free_sizes[size_index] = ((mem_end - mem_start) / size);
	
	return 0;
}

/*
 * Initializes our buddy structure
 */
int buddy_init(phys_t mem_start, phys_t mem_end) {
	int i;
	buddy.lock = 0;
	buddy.quick_free_cache = 0;
	
	for (i = 0; i < NRBUDDIES; i++) {
		if (create_buddies(i, mem_start, mem_end)) {
			return 1;
		}
	}

	return 0;
}