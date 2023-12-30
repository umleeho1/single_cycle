#include "../../header/logic_gates/extension_unit.h"

void set_extension_unit(Extension_unit* e_unit, int input, char mode){
	//input
	e_unit->input = input;
	e_unit->mode = mode;
	//output
	if (e_unit->mode==1){
		if (e_unit->input&0x8000){
			e_unit->result = e_unit->input|(0xffff0000);
		}
		else{
			e_unit->result = e_unit->input;
		}
	}
	else{
		e_unit->result = e_unit->input;
	}
	return;
}

int get_extension_unit_result(Extension_unit e_unit){
	return e_unit.result;
}
