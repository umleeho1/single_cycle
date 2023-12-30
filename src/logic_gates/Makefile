CC=gcc
LIB=logic_gates.a
OBJS=adder.o mux.o shifter.o extension_unit.o
CFLAGS=-Wall

$(LIB): $(OBJS)
		$(AR) rv $@ $(OBJS)
		
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@
		
clean:
		rm -f $(OBJS) $(LIB)