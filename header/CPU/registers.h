#ifndef _REGISTERS_H_
#define _REGISTERS_H_

typedef struct register_file{
	//input
	int read_reg1;
	int read_reg2;
	int write_reg;
	int write_data;
	//control_signal
	char reg_write;
	//output
	int read_data1;
	int read_data2;
}Reg_file;

int pc;
int reg[32];

/*int lo;
int hi;*/

void set_register_file(Reg_file* r_file, int read_reg1, int read_reg2, int write_reg, char reg_write);
void set_register_file_write_data(Reg_file* r_file, int write_data);
void store_register_file_write_data(Reg_file r_file);
int get_register_file_read_data1(Reg_file r_file);
int get_register_file_read_data2(Reg_file r_file);

#endif