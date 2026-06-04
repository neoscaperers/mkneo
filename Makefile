TOPSRC = $(shell pwd)

export

kernel:
	$(MAKE) -C $(TOPSRC)/sys

clean:
	$(MAKE) -C $(TOPSRC)/sys clean