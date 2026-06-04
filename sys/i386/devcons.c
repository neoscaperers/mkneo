#include <sys/types.h>
#include <sys/kcons.h>
#include <i386.h>
#include <devcons.h>

int init_devcons(void) {
    outb(COM0 + 1, 0);
    outb(COM0 + 3, 0x80);
    outb(COM0, (BASE_BAUD / BAUD_RATE) & 255);
    outb(COM0 + 1, 0);
    outb(COM0 + 3, 3);
    outb(COM0 + 2, 0xC7);
    outb(COM0 + 4, 8);
    outb(COM0 + 4, 0x1E);
    outb(COM0, 0xAE);

    if (inb(COM0) != 0xAE) {
        return 1;
    }
    outb(COM0 + 4, 0xF);
    return 0;
}

void devcons_writec(char c) {
    while (!(inb(COM0 + 5) & 0x20));
    outb(COM0, c);
}

void devcons_writes(const char* s) {
    for (;*s != '\0'; s++) {
        devcons_writec(*s);
    }
}

struct kcons_dev serialdev = {
    .active = 0,
    .init = &init_devcons,
    .putc = &devcons_writec,
    .puts = &devcons_writes  
};

struct kcons_dev* kcons_main = &serialdev;
struct kcons_dev* kcons_debug = &serialdev;

