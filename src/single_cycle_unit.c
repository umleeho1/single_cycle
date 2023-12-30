#include "../header/CPU/cpu.h"
#include "../header/bit_functions/bit_functions.h"
#include "../header/logic_gates/logic_gates.h"
#include "../header/memory/memory.h"

#include<stdio.h>

int main(void){
	reg[29] = 0x01000000;
	reg[31] = 0xffffffff;
	
	FILE* file = fopen("HW2/input4/input.bin", "r");
	CPU cpu;
	
	int i = 0;
	while(fgets(mem+i, 5, file) != NULL){
		i+=4;
	}
	
	while (pc != 0xffffffff){
		fetch(&cpu, mem);
		decode(&cpu);
		execute(&cpu);
		memory_operation(&cpu, mem);
		write_back(&cpu, mem);
		pc_update(&cpu); 
	}
	print_result();
	fclose(file);
	return 0;
}