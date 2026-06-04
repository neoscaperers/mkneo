CCARGS	+= -m32 -fno-PIC -fno-PIE -mno-80387 -mno-mmx -mno-sse -mno-sse2
LDARGS	+= --script=$(TOPSRC)/sys/i386/link.ld -melf_i386
SRCS 	+= $(TOPSRC)/sys/i386/archentry.c $(TOPSRC)/sys/i386/devcons.c $(TOPSRC)/sys/i386/bootbump.c \
			$(TOPSRC)/sys/i386/bootpt.c $(TOPSRC)/sys/i386/syscall.c $(TOPSRC)/sys/i386/trap.c
SSRCS	+= $(TOPSRC)/sys/i386/boot.S $(TOPSRC)/sys/i386/idt.S
