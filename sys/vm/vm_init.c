//
//  vm_init.c
//  
//
//  Created by neo on 6/4/26.
//

#include <sys/systm.h>
#include <sys/types.h>
#include <sys/vm/vm_page.h>
#include <sys/kcons.h>
#include <machdef.h>

struct vm_page* vm_page_base;

/*
 * Initializes the virtual memory manager subsystem
 */
int vm_init(phys_t start, phys_t end) {
    size_t i;
    size_t nrpages = (end - start) / PAGESIZE;
    struct vm_page* curpage;
    vm_page_base = boot_bump(nrpages * sizeof(struct vm_page), 64);
    
    if (vm_page_base == NULL) {
        return 1;
    }
    
    for (i = 0; i < nrpages; i++) {
        curpage = &vm_page_base[i];
        curpage->free_next = (i == (nrpages - 1)) ? NULL : &vm_page_base[i + 1];
        curpage->queue = NULL;
        curpage->mutex = 0;
        curpage->physaddr = (i * PAGESIZE);
        curpage->flags = PG_CLEAN;
        curpage->wire_count = 0;
        curpage->object = NULL;
        curpage->offset = 0;
    }
    
    
    
    kern_printf("vm_init(): %d vm_pages between range 0x%p - 0x%p\r\n", nrpages, (uintptr_t)start, (uintptr_t)end);
    return 0;
}
