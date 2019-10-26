#include "../bus.h"
#include <stdio.h>
#define MOV 0x00
#define JMP 0x01
#define CALL 0x02
#define RET 0x03
unsigned char opcode=0xFF;
unsigned char operand0 = 0x0;
unsigned char operand1 = 0x0;
#define OPCODE_READ 0x00
#define OPRAND0_READ 0x01
#define OPARAND1_READ 0x02


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
char current_stage = 0x0;
char memory_stage=DEVICE_SELECT;
unsigned short r0 =0;
unsigned short r0o=0;
unsigned short r1 =0;
unsigned short r1o=0;
unsigned short ip =0;
unsigned short io =0;
unsigned short sp =0;
unsigned short so =0;
void print_registers();
void print_instruction();
void execute_instruction(){
	
	print_instruction();
	switch(opcode&0x7F){
		case MOV:
			break;
		case JMP:
			if(opcode>>0x7==0x1){
				ip = operand1;
				printf("jumped\n");
			}else{
				printf("seen: %x",opcode>>0x7);
				printf("todo memory_access\n");
			}
			printf("todo make jump\n");
			break;
	}
	printf("instruction: %i\n",opcode&0x7F);
	print_registers();
}
void print_instruction(){
	printf("instruction executed: 0x%x\t0x%x\t0x%x\n",opcode,operand0,operand1);
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
void cpu_tick(struct bus *sys_bus,struct ram_bus *in){
	unsigned char data;
	switch(memory_stage){	
		case DEVICE_SELECT:
			memory_stage=ADDRESS_WRITE;	
			return;
		case ADDRESS_WRITE:
			in->address_bus=ip+io<<0x10;
			in->WRITE_OR_READ=1;
			memory_stage=MMU_READ;
			return;
		case MMU_READ:
			memory_stage=DATA_READ;
			return;
		case DATA_READ:
			data = in->data_bus;
			memory_stage=DEVICE_SELECT;
	}
	switch(current_stage){
		case OPCODE_READ:
			opcode = data;
			current_stage=OPRAND0_READ;
			ip++;
			break;
		//read first opcode from memory
		case OPRAND0_READ:
			operand0=data;
			if(opcode>>0x7==0){
				execute_instruction();
				current_stage=OPCODE_READ;
				break;
			}
			current_stage=OPARAND1_READ;
			ip++;
			break;
		//read 0th operand from memory and if opcode&0x80==0 execute instruction

		case OPARAND1_READ:
			operand1=data;
			execute_instruction();
			current_stage=OPCODE_READ;
			ip++;
			break;
		//read 1st operand from memory and execute
	}
	memory_stage=DEVICE_SELECT;


}
