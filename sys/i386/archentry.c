#include <sys/types.h>
#include <sys/systm.h>

#include <multiboot.h>
#include <devcons.h>

void archentry(uint32_t magic, struct mb_header* header) {
    boot_creatept(header);
    kern_init();
    while (1);
}