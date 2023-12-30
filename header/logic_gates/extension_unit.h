#ifndef _EXTENSION_UNIT_H_
#define _EXTENSION_UNIT_H_

typedef struct extension_unit{
	//input
	int input;
	char mode; //0 zero_ex, 1 sign_ex
	//output
	int result;
}Extension_unit;

void set_extension_unit(Extension_unit* e_unit, int input, char mode);
int get_extension_unit_result(Extension_unit e_unit);

#endif