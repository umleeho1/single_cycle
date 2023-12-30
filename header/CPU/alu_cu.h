#ifndef _ALU_CONTROL_UNIT_H_
#define _ALU_CONTROL_UNIT_H_

#include "function_code.h"

////////////////////////
#define alu_and		0x00
#define alu_or		0x01
#define alu_add 	0x02
#define alu_sll		0x04
#define alu_xor		0x05
#define alu_nor 	0x06
#define alu_srl 	0x07
#define alu_sra		0x08

#define alu_sub		0x12
#define alu_slt		0x13

#define alu_sllv	0x24
#define alu_srlv 	0x27
#define alu_srav	0x28
////////////////////////


typedef struct alu_control_unit_input{
	unsigned int alu_op		: 3;
	unsigned int funct		: 6;
}Acu_input;

typedef struct alu_control_unit_output{
	unsigned char alu_control	: 6;

	unsigned char jr			: 1;
	unsigned char jalr			: 1;
}Acu_output;

typedef struct alu_control_unit{
	//input
	Acu_input acu_input;
	//output
	Acu_output acu_output;
}Alu_control_unit;

void set_alu_control_unit(Alu_control_unit* acu, Acu_input acu_input);
Acu_output get_alu_control_unit_output(Alu_control_unit acu);

#endif