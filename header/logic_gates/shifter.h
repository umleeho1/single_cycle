#ifndef _SHIFTER_H_
#define _SHIFTER_H_

typedef struct shifter{
	//input
	int input;
	int shamt;
	char left;
	char sra;
	//output
	int result;
}Shifter;

void set_shifter(Shifter* shifter, int input, int shamt, char left, char sra);
int get_shifter_result(Shifter shifter);

#endif