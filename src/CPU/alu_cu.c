#include "../../header/CPU/alu_cu.h"
#include <stdio.h>

void set_alu_control_unit(Alu_control_unit* acu, Acu_input acu_input){
	//input
	acu->acu_input = acu_input;
	//output
	//alu_control
	switch(acu->acu_input.alu_op){
		case 0:
			acu->acu_output.alu_control = alu_add;
			break;
		case 1:
			acu->acu_output.alu_control = alu_sub;
			break;
		case 2:
			acu->acu_output.alu_control = alu_and;
			break;
		case 3:
			acu->acu_output.alu_control = alu_or;
			break;
		case 4:
			acu->acu_output.alu_control = alu_xor;
			break;
		case 5:
			acu->acu_output.alu_control = alu_slt;
			break;
		case 6:
			switch(acu->acu_input.funct){
				case ADD: case ADDU: case JR: case JALR:
					acu->acu_output.alu_control = alu_add;
					break;
				case SUB: case SUBU:
					acu->acu_output.alu_control = alu_sub;
					break;
				case AND:
					acu->acu_output.alu_control = alu_and;
					break;
				case OR:
					acu->acu_output.alu_control = alu_or;
					break;
				case XOR:
					acu->acu_output.alu_control = alu_xor;
					break;
				case NOR:
					acu->acu_output.alu_control = alu_nor;
					break;
				case SLT: case SLTU:
					acu->acu_output.alu_control = alu_slt;
					break;
				case SLL:
					acu->acu_output.alu_control = alu_sll;
					break;
				case SRL:
					acu->acu_output.alu_control = alu_srl;
					break;
				case SRA:
					acu->acu_output.alu_control = alu_sra;
					break;
				case SLLV:
					acu->acu_output.alu_control = alu_sllv;
					break;
				case SRLV:
					acu->acu_output.alu_control = alu_srlv;
					break;
				case SRAV:
					acu->acu_output.alu_control = alu_srav;
					break;
			}
			break;
		default:
			printf("raise reserved instruction exception(function code)\n");
	}
	
	acu->acu_output.jr = 0;
	acu->acu_output.jalr = 0;
	if (acu->acu_input.alu_op == 6){
		//jr
		if (acu->acu_input.funct == JR || acu->acu_input.funct == JALR){
			acu->acu_output.jr = 1;
		}
		else{
			acu->acu_output.jr = 0;
		}
		//jalr
		if (acu->acu_input.funct == JALR){
			acu->acu_output.jalr = 1;
		}
		else{
			acu->acu_output.jalr = 0;
		}
	}
	
	return;
}

Acu_output get_alu_control_unit_output(Alu_control_unit acu){
	return acu.acu_output;
}