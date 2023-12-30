#include "../../header/CPU/registers.h"

int pc = 0x00000000;
int reg[32] = {0, };
// input write_reg is result of WR_mux
void set_register_file(Reg_file* r_file, int read_reg1, int read_reg2, int write_reg, char reg_write){
	//set input
	r_file->read_reg1 = read_reg1;
	r_file->read_reg2 = read_reg2;
	r_file->write_reg = write_reg;
	//set signal
	r_file->reg_write = reg_write;
	//set output
	r_file->read_data1 = reg[r_file->read_reg1];
	r_file->read_data2 = reg[r_file->read_reg2];
	return;
}

// input write_data is result of WD_mux
void set_register_file_write_data(Reg_file* r_file, int write_data){
	r_file->write_data = write_data;
	return;
}

void store_register_file_write_data(Reg_file r_file){
	if (r_file.reg_write && r_file.write_reg != 0){
		reg[r_file.write_reg] = r_file.write_data;
	}
	return;
}

int get_register_file_read_data1(Reg_file r_file){
	return r_file.read_data1;
}

int get_register_file_read_data2(Reg_file r_file){
	return r_file.read_data2;
}