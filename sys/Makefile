ARCH 	?= i386
TARGET 	= mkneo.$(ARCH)
CCARGS 	= -I$(TOPSRC)/include -I$(TOPSRC)/include/sys/$(ARCH) -Werror -Wall \
			-Wpedantic -ffreestanding -fno-ident -D_KERNEL
LDARGS 	= -nostdlib -s -S -A $(ARCH)

SRCS	= kern/kern_init.c kern/kern_console.c libkern/memory.c vm/vm_init.c
SSRCS	= 
export 
include $(TOPSRC)/sys/$(ARCH)/Makefile
OBJS 	= $(SRCS:.c=.o) $(SSRCS:.S=.So)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDARGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CCARGS) -c $< -o $@
%.So: %.S
	$(CC) $(CCARGS) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET)
