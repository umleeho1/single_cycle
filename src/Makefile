CC=gcc
TARGET=single_cycle_unit
OBJS=single_cycle_unit.o
CFLAGS=-Wall

$(TARGET): $(OBJS)
		$(CC) -o ../$(TARGET) $(OBJS) ./CPU/cpu.a ./bit_functions/bit_functions.a ./logic_gates/logic_gates.a ./memory/memory.a
		
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@
		
clean:
		rm -f $(OBJS) $(TARGET)