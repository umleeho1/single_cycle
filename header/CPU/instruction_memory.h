#ifndef _INSTRUCTION_MEMORY_H_
#define _INSTRUCTION_MEMORY_H_

#include "../bit_functions/bit_functions.h"

typedef struct instruction_memory{
	//input
	int address;
	//output
	int read_data;
}Inst_mem;

void set_instruction_memory(Inst_mem* i_mem, int pc, char* mem);
int get_instruction_memory_data(Inst_mem i_mem);

#endif