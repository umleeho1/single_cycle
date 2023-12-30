#include "../../header/logic_gates/mux.h"

void set_mux(Mux* mux, int* input_arr, int condition){
	//input
	mux->input_arr = input_arr;
	mux->condition = condition;
	
	//output
	mux->result = mux->input_arr[mux->condition];
	
	return;
}

int get_mux_result(Mux mux){
	return mux.result;
}
