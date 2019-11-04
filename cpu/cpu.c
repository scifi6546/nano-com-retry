#include "../bus.h"
#include <stdio.h>
#define MOV 0x00
#define JMP 0x01
#define CALL 0x02
#define RET 0x03
unsigned char cpu_opcode=0xFF;
unsigned char cpu_operand0 = 0x0;
unsigned char cpu_operand1 = 0x0;
unsigned char cpu_register_pointed_to=0x0;//data pointed to by cpu register only used when memory access
                                          //specified
unsigned char* to_modify=&cpu_opcode;
//cpu memory stages
#define OPCODE_READ 0x00
#define OPRAND0_READ 0x01
#define OPARAND1_READ 0x02
#define REGISTER_DEREFRENCE_UPPER 0x3
#define REGISTER_DEREFRENCE_LOWER 0x4


//ram reading macros
#define DEVICE_SELECT 0x1
#define ADDRESS_WRITE 0x2
#define MMU_READ      0x3
#define DATA_READ     0x4

//instructions
#define MOV  0x00
#define JMP  0x01
#define CALL 0x02
#define RET  0x03
#define PUSH 0x04
#define POP  0x05
#define ADD  0x06
#define ADDS 0x07
#define OR   0x08
#define XOR  0x09
#define AND  0x0A


//cpu register opcodes
#define R0  0x0
#define R0o 0x1
#define R1  0x2
#define R1o 0x3
#define IP  0x4
#define Io 0x5
#define SP  0x6
#define So 0x7
char cpu_current_stage = 0x0;
char cpu_memory_stage=DEVICE_SELECT;
unsigned short r0 =0;
unsigned short r0o=0;
unsigned short r1 =0;
unsigned short r1o=0;
unsigned short ip =0;
unsigned short io =0;
unsigned short sp =0;
unsigned short so =0;
//gets pointer to register from register opcode
unsigned short* get_register_addr(unsigned char register_code){
	switch(register_code){
		case R0:
			return &r0;
		case R0o:
			return &r0o;
		case R1:
			return &r1;
		case R1o:
			return &r1o;
		case IP:
			return &ip;
		case Io:
			return &io;
		case SP:
			return &sp;
		case So:
			return &so;
	}

}
void print_registers();
void print_instruction();
void execute_instruction(){
	
	print_instruction();
	switch(cpu_opcode&0x7F){
		case MOV:
			if(cpu_opcode>>0x7==0x0){
				
			}else{

			}
			break;
		case JMP:
			if(cpu_opcode>>0x7==0x1){
				ip = cpu_operand1;
				printf("jumped\n");
			}else{
				printf("seen: %x",cpu_opcode>>0x7);
				printf("todo memory_access\n");
			}
			printf("todo make jump\n");
			break;
	}
	printf("instruction: %i\n",cpu_opcode&0x7F);
	print_registers();
}
void print_instruction(){
	printf("instruction executed: 0x%x\t0x%x\t0x%x\n",cpu_opcode,cpu_operand0,cpu_operand1);
}
void print_registers(){
	printf("r0: 0x%x\tr0o: 0x%x\n",r0,r0o);
	printf("r1: 0x%x\tr1o: 0x%x\n",r1,r1o);
	printf("ip: 0x%x\tio:  0x%x\n",ip,io);
	printf("sp: 0x%x\tso:  0x%x\n",sp,so);

}
void boot_cpu(){

}
short ram_read();
//main cpu_tick loop
//how it works:
//the cpu has to be put in cold storage inbetween each tick so all state information
//has to be stored as global variables=, cpu_memory_stage keeps track of 
//which part of the memory access cycle the system is on.
//cpu_current_stage keeps track of whick part of instruction decoding
//the processer is doing.
void cpu_tick(struct bus *sys_bus,struct ram_bus *in){
	unsigned int temp_addr = io<<0x10;
	temp_addr+=ip;
	switch(cpu_memory_stage){	
		case DEVICE_SELECT:
			cpu_memory_stage=ADDRESS_WRITE;	
			return;
		case ADDRESS_WRITE:
			in->address_bus=temp_addr;
			in->WRITE_OR_READ=READ;
			cpu_memory_stage=MMU_READ;
			return;
		case MMU_READ:
			cpu_memory_stage=DATA_READ;
			return;
		case DATA_READ:
			to_modify[0] = in->data_bus;
			cpu_memory_stage=DEVICE_SELECT;
	}
	switch(cpu_current_stage){
		case OPCODE_READ:
			cpu_current_stage=OPRAND0_READ;
			to_modify=&cpu_operand0;
			ip++;
			break;
		//read first opcode from memory
		case OPRAND0_READ:
			//if use constant==0 derefrence address
			//todo get memory pointers working.
			if(cpu_opcode>>0x7==0){
				cpu_current_stage=REGISTER_DEREFRENCE_UPPER;
				unsigned short reg = cpu_register_pointed_to(to_modify[0]);
				reg=0;
				to_modify=&cpu_opcode;
				break;
			}
			cpu_current_stage=OPARAND1_READ;
			to_modify=&cpu_operand1;
			ip++;
			break;
		//read 0th operand from memory and if opcode&0x80==0 execute instruction

		case OPARAND1_READ:
			execute_instruction();
			cpu_current_stage=OPCODE_READ;
			to_modify=&cpu_opcode;
			break;
		case REGISTER_DEREFRENCE:
			execute_instruction();
			break;


		//read 1st operand from memory and execute
	}
	cpu_memory_stage=DEVICE_SELECT;


}
