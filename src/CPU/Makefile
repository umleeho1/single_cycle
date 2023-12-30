CC=gcc
LIB=cpu.a
OBJS=alu.o alu_cu.o control_unit.o data_memory.o fpu.o instruction_memory.o registers.o cpu.o
CFLAGS=-Wall

$(LIB): $(OBJS)
		$(AR) rv $@ $(OBJS)
		
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@
		
clean:
		rm -f $(OBJS) $(LIB)