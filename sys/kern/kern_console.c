#include <sys/kcons.h>
#include <sys/types.h>

#include <stdarg.h>

void init_kcons(void) {
    if (kcons_main) {
        if (!kcons_main->init()) {
            kcons_main->active = 1;
        }
    }

    if (kcons_debug) {
        if (!kcons_debug->init()) {
            kcons_debug->active = 1;
        }
    }
}

void kern_putc(char c) {
    if (kcons_main->active)
        kcons_main->putc(c);
}

void kern_puts(const char* s) {
    if (kcons_main->active)
        kcons_main->puts(s);
}

static void itoa(uintptr_t num, int base, int padding, void (*_puts)(const char*)) {
    static char chars[] = "0123456789abcdef";
    static char buffer[32];
    char* buffer_ptr = &buffer[31];

    if (base > 16)
        base = 16;

    *buffer_ptr = '\0';

    while (num) {
        char current_char = chars[num % base];
        *--buffer_ptr = current_char;
        num /= base;
    }

    while (buffer_ptr > &buffer[31 - padding])
        *--buffer_ptr = '0';
    
    _puts(buffer_ptr);
}

static void vaprintf(const char* fmt, va_list args, void (*_putc)(char), void (*_puts)(const char*)) {
    char c = 0;
    int padding_amt = 1;
    int islong = 0;
    int i;
    int fmt_val_i;
    uintptr_t fmt_val_l;
    char* str;

    for (i = 0; (c = fmt[i]) != 0; i++) {
        if (c != '%') {
            _putc(c);
            continue;
        } else {
            c = fmt[++i];
            padding_amt = 1;
            if (c == 0)
                break;
            if (c >= '0' && c <= '9') {
                padding_amt = 0;
                while (c >= '0' && c <= '9' && c != '\0') {
                    padding_amt = padding_amt * 10 + (c - '0');
                    c = fmt[++i];
                }
            }
            
            if (c == 'l') {
                islong = 1;
                c = fmt[++i];
            }
            
            switch (c) {
                case 'd': {
                    if (islong) {
                        fmt_val_l = va_arg(args, uintptr_t);
                        itoa(fmt_val_l, 10, padding_amt, _puts);
                        islong = 0;
                    } else {
                        fmt_val_i = va_arg(args, int);
                        itoa(fmt_val_i, 10, padding_amt, _puts);
                    }
                    break;
                }

                case 'p':
                case 'x': {
                    if (islong) {
                        fmt_val_l = va_arg(args, uintptr_t);
                        itoa(fmt_val_l, 16, padding_amt, _puts);
                        islong = 0;
                    } else {
                        fmt_val_i = va_arg(args, int);
                        itoa(fmt_val_i, 16, padding_amt, _puts);
                    }
                    break;
                }

                case 's': {
                    str = va_arg(args, char*);
                    if (str == 0)
                        str = "(null)";
                    _puts(str);
                    break;
                }

                case '%': {
                    _putc('%');
                }
            }
        }
    }
}

void kern_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vaprintf(fmt, args, kern_putc, kern_puts);
    va_end(args);
}