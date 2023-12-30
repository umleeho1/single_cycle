#ifndef _CONTROL_UNIT_H_
#define _CONTROL_UNIT_H_

#include "opcode.h"

typedef struct control_unit_signal{
	unsigned int sh_b		: 2;
	unsigned int s_zext		: 1;
	unsigned int reg_write	: 1;
	unsigned int reg_dst	: 2;
	unsigned int alu_src	: 2;
	unsigned int branch		: 1;
	unsigned int brchne		: 1;
	unsigned int blez		: 1;
	unsigned int bltz		: 1;
	unsigned int bgtz		: 1;
	unsigned int mem_write	: 1;
	unsigned int mem_to_reg	: 2;
	unsigned int jump		: 1;
	unsigned int jal		: 1;
	unsigned int alu_op		: 3;
	unsigned int hlt		: 1;
	//
	unsigned int pcsrc		: 1;
}Control_unit_signal;

typedef struct control_unit{
	//input
	int opcode; // opcode
	//output
	Control_unit_signal control_unit_signal;
}Control_unit;

void set_control_unit(Control_unit* c_unit, int opcode);
void set_control_unit_pcsrc(Control_unit* c_unit, int pcsrc);
Control_unit_signal get_control_unit_signal(Control_unit c_unit);

#endif