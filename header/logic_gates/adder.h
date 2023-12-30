#ifndef _ADDER_H_
#define _ADDER_H_

typedef struct adder{
	//input
	int operand1;
	int operand2;
	char c_in;
	//output
	int zero;
	int overflow;
	int result;
}Adder;

void set_adder(Adder* adder, int operand1, int operand2, char c_in);
int get_adder_result(Adder adder);
int get_adder_overflow(Adder adder);
int get_adder_zero(Adder adder);

#endif