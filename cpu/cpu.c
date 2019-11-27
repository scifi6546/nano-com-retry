#include "../bus.h"
#include "microcode.h"
#include <stdio.h>
#define MOV 0x00
#define JMP 0x01
#define CALL 0x02
#define RET 0x03
unsigned char cpu_opcode=0xFF;
unsigned char cpu_operand0 = 0x0;
unsigned char temp_mod_char=0x0;
unsigned short cpu_operand1 = 0x0;
unsigned char cpu_register_pointed_to=0x0;//data pointed to by cpu register only used when memory access
                                          //specified
unsigned char* to_modify=&cpu_opcode;
//contains data of derefrenced register
unsigned short derefrenced_reg_data;
//cpu memory stages
#define OPCODE_READ 0x00
#define OPRAND0_READ 0x01
#define OPERAND1_READ_UPPER 0x2
#define OPERAND1_READ_LOWER 0x3
#define REGISTER_DEREFRENCE_UPPER 0x4
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
	tick_micro_ins(sys_bus,in);
}
