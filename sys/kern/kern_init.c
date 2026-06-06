#include <sys/types.h>
#include <sys/kcons.h>
#include <sys/boot.h>

//#include <sys/vm/vm_init.h>

#include <sys/mm/init.h>

void kern_init(struct boot_s* bootstruct) {
    kern_printf("mkneo booting\r\n");
    /*if (vm_init(bootstruct->memory_start, bootstruct->memory_end)) {
        kern_printf("vm_init() failed\n");
        
    }*/

    if (mm_init(bootstruct->memory_start, bootstruct->memory_end)) {
        kern_printf("mm_init() failed\r\n");
    }
}

