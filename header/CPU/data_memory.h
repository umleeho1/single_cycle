#ifndef _DATA_MEMORY_H_
#define _DATA_MEMORY_H_

#include "../bit_functions/bit_functions.h"

typedef struct data_memory{
	//input
	unsigned int address;
	int write_data;
	//control_signal
	char sh_b;
	char mem_write;
	//output
	int read_data;
}Data_mem;

void set_data_memory(Data_mem* d_mem, unsigned int address, int write_data, char* mem, char sh_b, char mem_write);
void store_data_memory(Data_mem d_mem, char* mem);

int get_data_memory_data(Data_mem d_mem);

#endif