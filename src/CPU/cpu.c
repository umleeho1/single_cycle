#include "../../header/CPU/cpu.h"

#include<stdio.h>

int cle = 0;
int R_type_num = 0;
int I_type_num = 0;
int J_type_num = 0;
int Branch_num = 0;
int Mem_access_num = 0;

void fetch(CPU* cpu, char* mem){
	cle++;
	set_instruction_memory(&(cpu->i_mem), pc, mem);
	printf("cle[%d] (pc: 0x%x)\n", cle, pc);
	printf("[Fetch instruction] ");
	printf("0x%08x\n", get_instruction_memory_data(cpu->i_mem));
	return;
}

void decode(CPU* cpu){
	int instruction = get_instruction_memory_data(cpu->i_mem);
	set_control_unit(	&(cpu->c_unit),
						((R_type*)&instruction)->opcode);
	Control_unit_signal c_unit_signal = get_control_unit_signal(cpu->c_unit);
	
	Acu_input acu_input;
	acu_input.alu_op = c_unit_signal.alu_op;
	acu_input.funct = ((R_type*)&instruction)->funct;
	set_alu_control_unit(	&(cpu->acu),
							acu_input);
	
	int write_reg_mux_arr[3] = {((R_type*)&instruction)->rt,
							   	((R_type*)&instruction)->rd,
							   	31};
	set_mux(&(cpu->write_reg_mux),
		   	write_reg_mux_arr,
			c_unit_signal.reg_dst);
	
	set_register_file(	&(cpu->r_file), 
					 	((R_type*)&instruction)->rs,
					  	((R_type*)&instruction)->rt,
					  	get_mux_result(cpu->write_reg_mux),
					 	c_unit_signal.reg_write);
	
	set_extension_unit(	&(cpu->sign_extension_unit),
					  	((I_type*)&instruction)->imm,
					  	1);
	
	set_extension_unit(	&(cpu->zero_extension_unit),
					  	((I_type*)&instruction)->imm,
					  	0);
	
	set_shifter(&(cpu->lui_shifter),
			   	((I_type*)&instruction)->imm,
			   	16, 1, 0);

	set_shifter(&(cpu->branch_address_shifter),
				get_extension_unit_result(cpu->sign_extension_unit),
			   	2, 1, 0);
	
	set_shifter(&(cpu->jump_address_shifter),
			   	((J_type*)&instruction)->address,
			   	2, 1, 0);
	
	printf("[Decode instruction] type: ");
	if (instruction == 0){
		printf("Nop\n");
	}
	else if (((R_type*)&instruction)->opcode == R){
		printf("R\n");
		printf("\topcode: 0x%x, ", ((R_type*)&instruction)->opcode);
		printf("rs: 0x%x (R[%d]=0x%x), ", ((R_type*)&instruction)->rs, ((R_type*)&instruction)->rs, reg[((R_type*)&instruction)->rs]);
		printf("rt: 0x%x (R[%d]=0x%x), ", ((R_type*)&instruction)->rt, ((R_type*)&instruction)->rt, reg[((R_type*)&instruction)->rt]);
		printf("rd: 0x%x (%d), ", ((R_type*)&instruction)->rd, ((R_type*)&instruction)->rd);
		printf("shamt: 0x%x, ", ((R_type*)&instruction)->shamt);
		printf("funct: 0x%x\n", ((R_type*)&instruction)->funct);
		R_type_num++;
	}
	else if(((J_type*)&instruction)->opcode == J || ((J_type*)&instruction)->opcode == JAL){
		printf("J\n");
		printf("\topcode: 0x%x, ", ((J_type*)&instruction)->opcode);
		printf("address: 0x%x\n", ((J_type*)&instruction)->address);
		J_type_num++;
	}
	else{
		printf("I\n");
		printf("\topcode: 0x%x, ", ((I_type*)&instruction)->opcode);
		printf("rs: 0x%x (R[%d]=0x%x), ", ((I_type*)&instruction)->rs, ((I_type*)&instruction)->rs, reg[((I_type*)&instruction)->rs]);
		printf("rt: 0x%x (R[%d]=0x%x), ", ((I_type*)&instruction)->rt, ((I_type*)&instruction)->rt, reg[((I_type*)&instruction)->rt]);
		printf("imm: 0x%x\n", ((I_type*)&instruction)->imm);
		I_type_num++;
	}
	
	return;
}

void execute(CPU* cpu){
	int instruction = get_instruction_memory_data(cpu->i_mem);
	Control_unit_signal c_unit_signal = get_control_unit_signal(cpu->c_unit);
	Acu_output acu_output = get_alu_control_unit_output(cpu->acu);
	
	int alu_src_mux_arr[4] = {	get_register_file_read_data2(cpu->r_file),
							 	get_extension_unit_result(cpu->sign_extension_unit),
							 	get_extension_unit_result(cpu->zero_extension_unit),
							 	get_shifter_result(cpu->lui_shifter)};
	
	set_mux(&(cpu->alu_src_mux),
		   	alu_src_mux_arr,
		   	c_unit_signal.alu_src);
	
	set_alu(&(cpu->alu),
		   	((R_type*)&instruction)->shamt,
		   	get_register_file_read_data1(cpu->r_file),
		   	get_mux_result(cpu->alu_src_mux),
		   	acu_output.alu_control);
	
	Alu_signal alu_signal = get_alu_signal(cpu->alu);
	//pc&branch operation
	int pc_04_mux_arr[2] = {4, 0};
	set_mux(&(cpu->pc_04_mux),
		   	pc_04_mux_arr,
		   	c_unit_signal.hlt);
	set_adder(	&(cpu->pc_adder),
			 	pc,
			 	get_mux_result(cpu->pc_04_mux),
			 	0);
	set_adder(	&(cpu->branch_adder),
			 	get_shifter_result(cpu->branch_address_shifter),
			 	get_adder_result(cpu->pc_adder),
			 	0);
	
	int pcsrc = (c_unit_signal.branch & alu_signal.zero) ||
				(c_unit_signal.brchne & ~alu_signal.zero) ||
				(c_unit_signal.bgtz & alu_signal.gtz) ||
				(c_unit_signal.blez & alu_signal.lez) ||
				(c_unit_signal.bltz & alu_signal.ltz);
	set_control_unit_pcsrc(	&(cpu->c_unit),
						  	pcsrc);
	
	printf("[Execute]\n");
	printf("\talu src1: 0x%x, src2: 0x%x, result: 0x%x\n", cpu->alu.input_a, cpu->alu.input_b, cpu->alu.result);
	
	return;
}

void memory_operation(CPU* cpu, char* mem){
	int instruction = get_instruction_memory_data(cpu->i_mem);
	if (instruction == 0x00000000){
		return;
	}

	Control_unit_signal c_unit_signal = get_control_unit_signal(cpu->c_unit);
	
	set_data_memory(&(cpu->d_mem),
				   	get_alu_result(cpu->alu),
				   	get_register_file_read_data2(cpu->r_file),
				   	mem,
				   	c_unit_signal.sh_b,
				   	c_unit_signal.mem_write);
	
	store_data_memory(cpu->d_mem, mem);
	
	if (cpu->d_mem.mem_write){
		printf("[Store] ");
		printf("Mem[0x%08x] <- R[%d] = 0x%x\n", cpu->d_mem.address, cpu->r_file.read_reg2 , cpu->r_file.read_data2);
		Mem_access_num++;
	}
	
	return;
}

void write_back(CPU* cpu, char* mem){
	int instruction = get_instruction_memory_data(cpu->i_mem);
	if (instruction == 0x00000000){
		return;
	}
	Control_unit_signal c_unit_signal = get_control_unit_signal(cpu->c_unit);
	Acu_output acu_output = get_alu_control_unit_output(cpu->acu);
	
	int lw = get_data_memory_data(cpu->d_mem);
	set_extension_unit(	&(cpu->lh_extension_unit),
						(lw&0xffff0000)>>16,
						c_unit_signal.s_zext == 1 ? 0 : 1);
	int lh = get_extension_unit_result(cpu->lh_extension_unit);
					   
	set_extension_unit(	&(cpu->lb_extension_unit),
						(lw&0xff000000)>>24,
						c_unit_signal.s_zext == 1 ? 0 : 1);
	int lb = get_extension_unit_result(cpu->lb_extension_unit);
					   
	int alu_mem_mux_arr[4] = {	get_alu_result(cpu->alu),
							 	lw,
							 	lh,
							 	lb};
	set_mux(&(cpu->alu_mem_mux),
		   	alu_mem_mux_arr,
		   	c_unit_signal.mem_to_reg);
	
	set_adder(	&(cpu->jal_adder),
			 	get_adder_result(cpu->pc_adder),
			 	4,
			 	0);
	
	int pc_alumem_mux_arr[2] = {get_mux_result(cpu->alu_mem_mux),
							   	get_adder_result(cpu->jal_adder)};
	
	set_mux(&(cpu->wd_mux_unit.pc_alumem_mux),
		   	pc_alumem_mux_arr,
		   	c_unit_signal.jal | acu_output.jalr);
	set_register_file_write_data(&(cpu->r_file), get_mux_result(cpu->wd_mux_unit.pc_alumem_mux));
	
	store_register_file_write_data(cpu->r_file);
	if (c_unit_signal.mem_to_reg > 0){
		printf("[Load] ");
		printf("R[%d] <- Mem[0x%08x] = 0x%x\n", cpu->r_file.write_reg, cpu->d_mem.address, cpu->d_mem.read_data);
		Mem_access_num++;
	}
	else if (cpu->r_file.reg_write && cpu->r_file.write_reg != 0){
		printf("[Write Back] ");
		printf("R[%d] <- 0x%x\n", cpu->r_file.write_reg, cpu->r_file.write_data);
	}
	return;
}

void pc_update(CPU* cpu){
	Control_unit_signal c_unit_signal = get_control_unit_signal(cpu->c_unit);
	Acu_output acu_output = get_alu_control_unit_output(cpu->acu);
	
	int pc_next_br_arr[2] = {get_adder_result(cpu->pc_adder),
							 get_adder_result(cpu->branch_adder)};
	set_mux(&(cpu->pc_mux_unit.pc_next_br),
		   	pc_next_br_arr,
		   	c_unit_signal.pcsrc);
	
	int pc_next_j_arr[2] = {get_mux_result(cpu->pc_mux_unit.pc_next_br),
						   	(pc&0xf0000000) | get_shifter_result(cpu->jump_address_shifter)};
	set_mux(&(cpu->pc_mux_unit.pc_next_j),
		   	pc_next_j_arr,
		   	c_unit_signal.jump);

	int pc_next_jr_arr[2] = {	get_mux_result(cpu->pc_mux_unit.pc_next_j),
								get_mux_result(cpu->alu_mem_mux)};
	set_mux(&(cpu->pc_mux_unit.pc_next_jr),
		   	pc_next_jr_arr,
		   	acu_output.jr);
	
	printf("[PC Update] ");
	printf("PC <- 0x%08x = ", get_mux_result(cpu->pc_mux_unit.pc_next_jr));
	if (acu_output.jr){
		printf("R[%d]: 0x%08x\n", cpu->r_file.read_reg1, cpu->r_file.read_data1);
	}
	else if (c_unit_signal.jump){
		printf("Jump address\n");
	}
	else if (c_unit_signal.pcsrc){
		printf("Branch address\n");
		Branch_num++;
	}
	else{
		printf("0x%08x+4\n", pc);
	}
	printf("\n");
	pc = get_mux_result(cpu->pc_mux_unit.pc_next_jr);
	
	return;
}

void print_result(){
	printf("Return value (r2): %d\n", reg[2]);
	printf("Total Cycle: %d\n", cle);
	printf("Executed 'R' instruction: %d\n", R_type_num);
	printf("Executed 'I' instruction: %d\n", I_type_num);
	printf("Executed 'J' instruction: %d\n", J_type_num);
	printf("Number of Branch Taken: %d\n", Branch_num);
	printf("Number of Memory Access Instruction: %d\n", Mem_access_num);
	return;
}