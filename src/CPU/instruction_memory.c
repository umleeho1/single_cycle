#include "../../header/CPU/instruction_memory.h"

void set_instruction_memory(Inst_mem* i_mem, int pc, char* mem){
	//input
	i_mem->address = pc;
	//output
	i_mem->read_data = load_word(i_mem->address, mem);
	return;
}

int get_instruction_memory_data(Inst_mem i_mem){
	return i_mem.read_data;
}