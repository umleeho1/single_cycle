#ifndef _BIT_FUNCTION_H_
#define _BIT_FUNCTION_H_

void printb();
int load_word(unsigned int address, char* mem);
void save_n_bytes(int count, unsigned int address, int value, char* mem);

#endif