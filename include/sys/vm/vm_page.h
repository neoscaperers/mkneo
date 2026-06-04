//
//  vm_page.h
//  
//
//  Created by neo on 6/4/26.
//

#ifndef _SYS_VM_VM_PAGE_H
#define _SYS_VM_VM_PAGE_H

#include <sys/types.h>

struct vm_object;

struct vm_page {
    struct vm_page* queue;
    struct vm_page* free_next;
    mutex_t mutex;
    
    phys_t physaddr;
    
    int flags;
    int wire_count;
    struct vm_object* object;
    virt_t offset;
};

#define PG_CLEAN    0x1
#define PG_DIRTY    0x2
#define PG_BUSY     0x4
#define PG_PAGEOUT  0x8
#define PG_FAKE     0x10
#define PG_RELEASED 0x20
#define PG_RDONLY   0x40
#define PG_ANON     0x80

#endif /*_SYS_VM_VM_PAGE_H*/
