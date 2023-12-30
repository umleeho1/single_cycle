#include "../../header/CPU/control_unit.h"
#include <stdio.h>

void set_control_unit(Control_unit* c_unit, int opcode){
	//input
	c_unit->opcode = opcode;
	//output
	//sh_b
	if ((c_unit->opcode & 0x3c) == 0x28){
		c_unit->control_unit_signal.sh_b = c_unit->opcode&0x3;
	}
	else{
		c_unit->control_unit_signal.sh_b = 0;
	}
	//s_zext
	if ((c_unit->opcode & 0x3e) == 0x24){
		c_unit->control_unit_signal.s_zext = 1;
	}
	else{
		c_unit->control_unit_signal.s_zext = 0;
	}
	//reg_write
	if ((c_unit->opcode & 0x38) == 0x20 || (c_unit->opcode & 0x38) == 0x08 || c_unit->opcode == R || c_unit->opcode == JAL){
		c_unit->control_unit_signal.reg_write = 1;
	}
	else{
		c_unit->control_unit_signal.reg_write = 0;
	}
	//reg_dst
	if (c_unit->opcode == R){
		c_unit->control_unit_signal.reg_dst = 1;
	}
	else if (c_unit->opcode == JAL){
		c_unit->control_unit_signal.reg_dst = 2;
	}
	else{
		c_unit->control_unit_signal.reg_dst = 0;
	}
	//alu_src
	if ((c_unit->opcode & 0x3c) == 0x8 || (c_unit->opcode & 0x30) == 0x20){
		c_unit->control_unit_signal.alu_src = 1;
	}
	else if (c_unit->opcode == LUI){
		c_unit->control_unit_signal.alu_src = 3;
	}
	else if ((c_unit->opcode & 0x3c) == 0xc){
		c_unit->control_unit_signal.alu_src = 2;
	}
	else{
		c_unit->control_unit_signal.alu_src = 0;
	}
	//branch
	if (c_unit->opcode == BEQ){
		c_unit->control_unit_signal.branch = 1;
	}
	else{
		c_unit->control_unit_signal.branch = 0;
	}
	//brchne
	if (c_unit->opcode == BNE){
		c_unit->control_unit_signal.brchne = 1;
	}
	else{
		c_unit->control_unit_signal.brchne = 0;
	}
	//blez
	if (c_unit->opcode == BLEZ){
		c_unit->control_unit_signal.blez = 1;
	}
	else{
		c_unit->control_unit_signal.blez = 0;
	}
	//bltz
	if (c_unit->opcode == BLTZ){
		c_unit->control_unit_signal.bltz = 1;
	}
	else{
		c_unit->control_unit_signal.bltz = 0;
	}
	//bgtz
	if (c_unit->opcode == BGTZ){
		c_unit->control_unit_signal.bgtz = 1;
	}
	else{
		c_unit->control_unit_signal.bgtz = 0;
	}
	//mem_write
	if ((c_unit->opcode & 0x38) == 0x28){
		c_unit->control_unit_signal.mem_write = 1;
	}
	else{
		c_unit->control_unit_signal.mem_write = 0;
	}
	//mem_to_reg
	if ((c_unit->opcode & 0x38) == 0x20){
		if ((c_unit->opcode & 0x03) == 0x00){
			c_unit->control_unit_signal.mem_to_reg = 3;
		}
		else if ((c_unit->opcode & 0x03) == 0x01){
			c_unit->control_unit_signal.mem_to_reg = 2;
		}
		else{
			c_unit->control_unit_signal.mem_to_reg = 1;
		}
	}
	else{
		c_unit->control_unit_signal.mem_to_reg = 0;
	}
	//jump
	if (c_unit->opcode == J || c_unit->opcode == JAL){
		c_unit->control_unit_signal.jump = 1;
	}
	else{
		c_unit->control_unit_signal.jump = 0;
	}
	//jal
	if (c_unit->opcode == JAL){
		c_unit->control_unit_signal.jal = 1;
	}
	else{
		c_unit->control_unit_signal.jal = 0;
	}
	//alu_op
	if ((c_unit->opcode & 0x30) == 0x20 || (c_unit->opcode & 0x3e) == 0x08 || c_unit->opcode == LUI){
		c_unit->control_unit_signal.alu_op = 0;
	}
	else if ((c_unit->opcode & 0x3c) == 0x04 || c_unit->opcode == BLTZ){
		c_unit->control_unit_signal.alu_op = 1;
	}
	else if ((c_unit->opcode & 0x3c) == 0x0c){
		c_unit->control_unit_signal.alu_op = 2 + (c_unit->opcode & 0x03);
	}
	else if ((c_unit->opcode & 0x3e) == 0x0a){
		c_unit->control_unit_signal.alu_op = 5;
	}
	else if (c_unit->opcode == R){
		c_unit->control_unit_signal.alu_op = 6;
	}
	else if (c_unit->opcode == J || c_unit->opcode == JAL || c_unit->opcode == HLT){
		printf("J,JAL,HLT\n");
	}
	else{
		printf("raise reserved instruction exception\n");
	}
	//hlt
	if (c_unit->opcode == HLT){
		c_unit->control_unit_signal.hlt = 1;
	}
	else{
		c_unit->control_unit_signal.hlt = 0;
	}
	return;
}

void set_control_unit_pcsrc(Control_unit* c_unit, int pcsrc){
	c_unit->control_unit_signal.pcsrc = pcsrc;
	return;
}

Control_unit_signal get_control_unit_signal(Control_unit c_unit){
	return c_unit.control_unit_signal;
}