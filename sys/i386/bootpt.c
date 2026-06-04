#include <sys/types.h>
#include <sys/memory.h>
#include <sys/boot.h>

#include <bootbump.h>
#include <archvm.h>
#include <archtypes.h>
#include <multiboot.h>

extern char _kernel_start[];
extern char _kernel_end[];
extern char _text_start[];
extern char _text_end[];
extern char _rodata_start[];
extern char _rodata_end[];
extern char _data_start[];
extern char _data_end[];
extern char _bss_start[];
extern char _bss_end[];

static uintptr_t get_mem_limit(struct mb_header* hdr) {
    uintptr_t limit = 0;
    struct mb_mmap_entry* ptr;
    int i;
    for (i = 0; i < (hdr->mmap_len / sizeof(struct mb_mmap_entry)); i++) {
        ptr = &hdr->mmap[i];
        if (ptr->type == MB_MEM_USABLE) {
            if ((ptr->addr + ptr->len) > limit) {
                limit = (ptr->addr + ptr->len);
            }
        }
    }
    return limit;
}

void boot_creatept(struct mb_header* hdr, struct boot_s* bootpage) {
    uintptr_t memory_max = get_mem_limit(hdr);
    pagetable_t* ptbase = boot_bump(4096, 4096);
    pagetable_t* curpt;
    int npts = (memory_max / 0x400000);
    int i;
    int x;
    
    bootpage->memory_end = memory_max;
    bootpage->memory_start = 0;
    
    npts = (npts == 0) ? 1 : npts;
    npts = (npts > 512) ? 512 : npts;

    (void)memset(ptbase, 0, 4096);

    for (i = 0; i < npts; i++) {
        curpt = boot_bump(4096, 4096);
        (void)memset(curpt, 0, 4096);
        for (x = 0; x < 1024; x++) {
            if (x == 0 && i == 0) {
                curpt[x] = PT((4096 * x) + (i * 0x400000), PT_PRESENT); //((4096 * x) + (i * 0x400000)) | (PT_PRESENT);
            } else {
                curpt[x] = PT((4096 * x) + (i * 0x400000), PT_PRESENT | PT_WRITE);
            }
        }
        ptbase[i] = (((uintptr_t)curpt) - UPPERHALF) | (PT_PRESENT | PT_WRITE);
    }

    curpt = boot_bump(4096, 4096);
    (void)memset(curpt, 0, 4096);

    npts = ((uintptr_t)_text_end - (uintptr_t)_text_start) / 4096;
    x = ((uintptr_t)_text_start >> 12) & 0x3ff;
    for (i = 0; i < npts; i++) {
        curpt[x + i] = PT(((uintptr_t)_text_start - UPPERHALF) + (i * 4096), PT_PRESENT | PT_WIRED); 
    }

    npts = ((uintptr_t)_rodata_end - (uintptr_t)_rodata_start) / 4096;
    x = ((uintptr_t)_rodata_start >> 12) & 0x3ff;
    for (i = 0; i < npts; i++) {
        curpt[x + i] = PT(((uintptr_t)_rodata_start - UPPERHALF) + (i * 4096), PT_PRESENT | PT_WIRED); 
    }

    npts = ((uintptr_t)_data_end - (uintptr_t)_data_start) / 4096;
    x = ((uintptr_t)_data_start >> 12) & 0x3ff;
    for (i = 0; i < npts; i++) {
        curpt[x + i] = PT(((uintptr_t)_data_start - UPPERHALF) + (i * 4096), PT_PRESENT | PT_WRITE | PT_WIRED); 
    }

    npts = ((uintptr_t)_bss_end - (uintptr_t)_bss_start) / 4096;
    x = ((uintptr_t)_bss_start >> 12) & 0x3ff;
    for (i = 0; i < npts + 376; i++) {
        curpt[x + i] = PT(((uintptr_t)_bss_start - UPPERHALF) + (i * 4096), PT_PRESENT | PT_WRITE | PT_WIRED);
    }

    ptbase[(((uintptr_t)_kernel_start >> 22) & 0x3ff)] = PT((uintptr_t)curpt - UPPERHALF, PT_PRESENT | PT_WRITE | PT_WIRED);
    
    __asm__ volatile ("mov %0, %%cr3" : : "a"((uintptr_t)ptbase - UPPERHALF));
}
