#include "mem.h"
//How will it work?
#define R0  0x0
#define R0o 0x1
#define R1  0x2
#define R1o 0x3
#define IP  0x4
#define Io 0x5
#define SP  0x6
#define So 0x7
#define scratch_reg 0x8

#define M_NULL_INS 0x0
/* LOAD memory at address into register at source operand
 */
#define M_LOAD_MEM 0x1
// Move contents of reg at source to destination
// No memory access
#define M_MOV_REG 0x2


#define TO_EXEC 0
#define M_WAIT 1
#define DONE 2
struct microins{
	unsigned short opcode=0;
	unsigned short source=0;
	unsigned short destination=0;
	unsigned char progress=TO_EXEC;

};
#define MAX_QUEUE 0x20
struct micro_stack{
	struct microins to_execute[MAX_QUEUE];
	unsigned char current_ins=0;
};
void push_microins(struct micro_stack *stack,struct microins instruction){
	if(stack->current_ins<MAX_QUEUE){
		stack->current_ins++;
		stack->to_execute[stack->current_ins]=instruction;
	}
};
