#include "../../header/CPU/data_memory.h"
#include <stdio.h>
void set_data_memory(Data_mem* d_mem, unsigned int address, int write_data, char* mem, char sh_b, char mem_write){
	//input
	d_mem->address = address;
	d_mem->write_data = write_data;
	//signal
	d_mem->sh_b = sh_b;
	d_mem->mem_write = mem_write;
	//output
	d_mem->read_data = load_word(d_mem->address, mem);
	return;
}

void store_data_memory(Data_mem d_mem, char* mem){
	if (d_mem.mem_write == 1){
		save_n_bytes(d_mem.sh_b+1, d_mem.address, d_mem.write_data, mem);
	}
	return;
}

int get_data_memory_data(Data_mem d_mem){
	return d_mem.read_data;
}

