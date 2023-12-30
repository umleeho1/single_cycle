#ifndef _MUX_H_
#define _MUX_H_

typedef struct mux{
	//input
	int* input_arr;
	int condition;
	//output
	int result;
}Mux;

void set_mux(Mux* mux, int* input_arr, int condition);
int get_mux_result(Mux mux);

#endif