#include <sys/types.h>
#include <sys/kcons.h>

void kern_init(void) {
    init_kcons();
    kern_printf("mkneo booting\r\n");
}