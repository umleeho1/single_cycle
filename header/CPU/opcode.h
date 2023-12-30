#ifndef _OPCODE_H_
#define _OPCODE_H_

/*
///////////		R		I		J
#define ADD		0x20					//
#define ADDU	0x21					//
#define AND		0x24					//
#define JR		0x08					//
#define JALR	0x09					//
#define NOR		0x27					//
#define OR		0x25					//
#define SLT		0x2a					//
#define SLTU	0x2b					//
#define SLL		0x00					//
#define SRL		0x02					//
#define SUB		0x22					//
#define SUBU	0x23					//
*/

typedef struct opcode{
	unsigned char op6;
	unsigned char op5;
	unsigned char op4;
	unsigned char op3;
	unsigned char op2;
	unsigned char op1;
}Opcode;

#define R 		0x00
#define BLTZ	0x01
#define J		0x02
#define JAL		0x03
#define BEQ		0x04
#define BNE		0x05
#define BLEZ	0x06
#define BGTZ	0x07
#define ADDI	0x08
#define ADDIU	0x09
#define ALTI	0x0a
#define ALTIU	0x0b
#define ANDI	0x0c
#define ORI		0x0d
#define XORI	0x0e
#define LUI		0x0f
//#define op_not_defined 0x10	
#define FP		0x11
//#define op_not_defined 0x12	
//#define op_not_defined 0x13	
//#define op_not_defined 0x14	
//#define op_not_defined 0x15	
//#define op_not_defined 0x16	
//#define op_not_defined 0x17	
//#define op_not_defined 0x18	
//#define op_not_defined 0x19	
//#define op_not_defined 0x1a	
//#define op_not_defined 0x1b	
//#define op_not_defined 0x1c		
//#define op_not_defined 0x1d	
//#define op_not_defined 0x1e	
//#define op_not_defined 0x1f		
#define LB		0x20
#define LH		0x21
#define LWL		0x22
#define LW		0x23
#define LBU		0x24
#define LHU		0x25
#define LWR		0x26
//#define op_not_defined 0x27
#define SB		0x28
#define SH		0x29
#define SWL		0x2a
#define SW		0x2b
//#define op_not_defined 0x2c
//#define op_not_defined 0x2d
#define SWR		0x2e
#define CACHE	0x2f
#define LL		0x30
#define LWC1	0x31
#define LWC2	0x32
#define PREF	0x33
//#define op_not_defined 0x34
#define LDC1	0x35
#define LDC2	0x36
//#define op_not_defined 0x37
#define SC		0x38
#define SWC1	0x39
#define SWC2	0x3a
//#define op_not_defined 0x3b
#define HLT		0x3c
#define SDC1	0x3d
#define SDC2	0x3e
//#define op_not_defined 0x3f

#endif