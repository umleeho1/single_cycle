#include "../../header/logic_gates/shifter.h"

void set_shifter(Shifter* shifter, int input, int shamt, char left, char sra){
	//input
	shifter->input = input;
	shifter->shamt = shamt;
	shifter->left = left;
	shifter->sra = sra;
	
	//output
	if (shifter->left){
		shifter->result = ((unsigned int)shifter->input) << shifter->shamt;
	}
	else{
		if (shifter->sra){
			shifter->result = ((int)shifter->input) >> shifter->shamt;
		}
		else{
			shifter->result = ((unsigned int)shifter->input) >> shifter->shamt;
		}
	}
	return;
}

int get_shifter_result(Shifter shifter){
	return shifter.result;
}
