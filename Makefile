DIRS = src/bit_functions src/logic_gates src/memory src/CPU src
.PHONY: all clean

all:
		@for d in $(DIRS); \
		do \
				$(MAKE) -C $$d; \
		done
		
clean:
		@for d in $(DIRS); \
		do \
				$(MAKE) -C $$d clean; \
		done