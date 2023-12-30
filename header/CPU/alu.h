#ifndef _ALU_H_
#define _ALU_H_

#include "../logic_gates/logic_gates.h"
typedef struct alu_signal{
	unsigned char zero: 1;
	unsigned char ltz: 1;
	unsigned char gtz: 1;
	unsigned char lez: 1;
}Alu_signal;

typedef struct alu{
	//input
	int shamt;
	int input_a;
	int input_b;
	char alu_control;
	//logic_gates
	Mux shamt_mux;
	Mux b_mux;
	Mux output_mux;
	Shifter sra_unit;
	Shifter srl_unit;
	Shifter sll_unit;
	Adder adder;
	Extension_unit slt_ext_unit;
	//output
	int result;
	//signal
	Alu_signal alu_signal;
}ALU;

void set_alu(ALU* alu, int shamt, int input_a, int input_b, char alu_control);
int get_alu_result(ALU alu);
Alu_signal get_alu_signal(ALU alu);

#endif