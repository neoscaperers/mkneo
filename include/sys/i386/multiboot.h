#ifndef _SYS_I386_MULTIBOOT_H
#define _SYS_I386_MULTIBOOT_H

#define MULTIBOOT_PAGE_ALIGN    0x1
#define MULTIBOOT_MEM_INFO      0x2

#define MULTIBOOT_MAGIC     0x1badb002
#define MULTIBOOT_FLAGS     (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO)

#ifndef _ASM

#include <stdint.h>

#define MB_MEM_USABLE       1
#define MB_MEM_RESERVED     2
#define MB_MEM_ACPI_RECLAIMABLE 3
#define MB_MEM_NVS          4
#define MB_MEM_BADRAM       5

struct mb_mmap_entry {
    uint32_t size;
    uint64_t addr;
    uint64_t len;
    uint32_t type;
} __attribute__((packed));

struct mb_module_entry {
    uint32_t mod_start;
    uint32_t mod_end;
    const char* cmdline;
    uint32_t pad;
};

struct mb_header {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_dev;
    const char* cmdline;
    uint32_t num_mods;
    struct mb_module_entry* mods;
    uint32_t reserved[4];
    uint32_t mmap_len;
    struct mb_mmap_entry* mmap;
    /* We care not for anything else beyond this. */
};

struct boot_s;

void boot_creatept(struct mb_header* hdr, struct boot_s* bootstruct);

#endif /*_ASM*/

#endif /*_SYS_I386_MULTIBOOT_H*/

