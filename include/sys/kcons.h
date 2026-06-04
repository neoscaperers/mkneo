#ifndef _SYS_KCONS_H
#define _SYS_KCONS_H

/*
 * Kernel console device driver
 * Does not accept input.
 */
struct kcons_dev {
    int active;
    int (*init)(void);
    void (*putc)(char);
    void (*puts)(const char*);
};

extern struct kcons_dev* kcons_main;
extern struct kcons_dev* kcons_debug;

void init_kcons(void);
void kern_putc(char c);
void kern_puts(const char* s);
void kern_printf(const char* fmt, ...);

#endif /*_SYS_KCONS_H*/

