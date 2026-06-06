#include <sys/types.h>
#include <sys/kcons.h>
#include <sys/mm/buddy.h>

int mm_init(phys_t mem_start, phys_t mem_end) {
	if (buddy_init(mem_start, mem_end)) {
		kern_printf("buddy_init() failed\r\n");
		return 1;
	}

	return 0;
}