CC=gcc
LIB=memory.a
OBJS=memory.o
CFLAGS=-Wall

$(LIB): $(OBJS)
		$(AR) rv $@ $(OBJS)
		
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@
		
clean:
		rm -f $(OBJS) $(LIB)