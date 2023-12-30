#include "../../header/logic_gates/adder.h"

void set_adder(Adder* adder, int operand1, int operand2, char c_in){
	//input
	adder->operand1 = operand1;
	adder->operand2 = operand2;
	adder->c_in = c_in;
	
	//output
	adder->result = adder->operand1 + adder->operand2 + adder->c_in;
	adder->zero = adder->result==0 ? 1 : 0;
	adder->overflow = 0;
	if ((adder->operand1 > 0) && (adder->operand2 > 0) && (adder->operand1 > adder->result)){
		adder->overflow = 1;
	}
	else if ((adder->operand1 < 0) && (adder->operand2 < 0) && (adder->operand1 < adder->result)){
		adder->overflow = 1;
	}

	return;
}

int get_adder_result(Adder adder){
	return adder.result;
}

int get_adder_overflow(Adder adder){
	return adder.overflow;
}

int get_adder_zero(Adder adder){
	return adder.zero;
}