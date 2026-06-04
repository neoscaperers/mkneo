#include <sys/types.h>
#include <sys/systm.h>
#include <sys/kcons.h>
#include <sys/boot.h>

#include <multiboot.h>
#include <devcons.h>

struct boot_s bootstruct;

void archentry(uint32_t magic, struct mb_header* header) {
    boot_creatept(header, &bootstruct);
    init_kcons();
    
    kern_init(&bootstruct);
    while (1);
}

