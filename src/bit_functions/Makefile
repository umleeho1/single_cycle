CC=gcc
LIB=bit_functions.a
OBJS=bit_functions.o
CFLAGS=-Wall

$(LIB): $(OBJS)
		$(AR) rv $@ $(OBJS)
		
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@
		
clean:
		rm -f $(OBJS) $(LIB)