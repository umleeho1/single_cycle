#include "../../header/bit_functions/bit_functions.h"

#include <stdio.h>

void printb(int i){
	for(int a=31; a>=0; a--){
		if ((i>>a)<=0){
			continue;
		}
		else{
			printf("%d", (i>>a)&1);
		}
	}
	printf("\n");
	return;
}

int load_word(unsigned int address, char* mem){
	int ret = 0;
	for(int i = 0; i<4; i++){
		ret = ret<<8;
		ret = ret | (mem[address+i]&0xff);
	}
	return ret;
}	

void save_n_bytes(int count, unsigned int address, int value, char* mem){
	int tmp = value << 8*(4-count);
	for(int i = 0; i<count; i++){
		mem[address+i] = (tmp & 0xff000000)>>24;
		tmp = tmp<<8;
	}
	return;
}