#include "../../header/CPU/alu.h"

void set_alu(ALU* alu, int shamt, int input_a, int input_b, char alu_control){
	//set input
	alu->shamt = shamt;
	alu->input_a = input_a;
	alu->input_b = input_b;
	alu->alu_control = alu_control;
	//set logic_gates
	int shamt_mux_arr[2] = {alu->shamt, alu->input_a};
	set_mux(&(alu->shamt_mux), shamt_mux_arr, ((alu->alu_control)&0x20)>>5);
	int b_mux_arr[2] = {alu->input_b, ~(alu->input_b)};
	set_mux(&(alu->b_mux), b_mux_arr, ((alu->alu_control)&0x10)>>4);
	set_shifter(&(alu->sra_unit), alu->input_a, get_mux_result(alu->shamt_mux), 0, 1);
	set_shifter(&(alu->srl_unit), alu->input_a, get_mux_result(alu->shamt_mux), 0, 0);
	set_shifter(&(alu->sll_unit), alu->input_a, get_mux_result(alu->shamt_mux), 1, 0);
	set_adder(&(alu->adder), alu->input_a, get_mux_result(alu->b_mux), (char)((alu->alu_control)&0x10)>>4);
	set_extension_unit(&(alu->slt_ext_unit), ((get_adder_result(alu->adder))&0x80000000)>>31, 0);
	int output_mux_arr[9] = {(alu->input_a & get_mux_result(alu->b_mux)),
						 (alu->input_a | get_mux_result(alu->b_mux)),
						 (get_adder_result(alu->adder)),
						 (get_extension_unit_result(alu->slt_ext_unit)),
						 (get_shifter_result(alu->sll_unit)),
						 (alu->input_a ^ get_mux_result(alu->b_mux)),
						 ~(alu->input_a | get_mux_result(alu->b_mux)),
						 (get_shifter_result(alu->srl_unit)),
						 (get_shifter_result(alu->sra_unit))
						};
	set_mux(&(alu->output_mux), output_mux_arr, (int)(alu->alu_control&0x7));
	//set ouput
	alu->result = get_mux_result(alu->output_mux);
	//set signal
	alu->alu_signal.zero = alu->result==0 ? 1 : 0;
	alu->alu_signal.ltz = ~alu->alu_signal.zero & (alu->result&0x80000000)>>31 ? 1 : 0;
	alu->alu_signal.gtz = ~alu->alu_signal.zero & ~(alu->result&0x80000000)>>31 ? 1 : 0;
	alu->alu_signal.lez = alu->alu_signal.zero | (alu->result&0x80000000)>>31 ? 1 : 0;
	
	return;
}

int get_alu_result(ALU alu){
	return alu.result;
}

Alu_signal get_alu_signal(ALU alu){
	return alu.alu_signal;
}