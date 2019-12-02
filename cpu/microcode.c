#include "mem.h"
#include "logger.h"
#include <stdio.h>
//How will it work?
#define R0  0x0
#define R0o 0x1
#define R1  0x2
#define R1o 0x3
#define IP  0x4
#define IO 0x5
#define SP  0x6
#define SO 0x7
#define STRATCH_REGISTER 0x8
#define STRATCH_REGISTER2 0x9
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

u16 r0=0;
u16 r0o=0;
u16 r1=0;
u16 r1o=0;
u16 ip =0;
u16 io=0;
u16 sp=0;
u16 so=0;
u16 scratch=0;
u16 scratch2=0;
u16 get_register(char reg_code){
	switch(reg_code){
		case R0:
			return r0;
		case R0o:
			return r0o;
		case R1:
			return r1;
		case R1o:
			return r1o;
		case IP:
			return ip;
		case IO:
			return io;
		case SP:
			return sp;
		case SO:
			return so;
		case STRATCH_REGISTER:
			return scratch;
		case STRATCH_REGISTER2:
			return scratch2;
	}
}
void set_register(u8 reg_code,u16 data){
	if(reg_code==R0){
		r0=data;
	}else if(reg_code==R0o){
		r0o=data;
	}else if(reg_code==R1){
		r1=data;
	}else if(reg_code==R1o){
		r1o=data;
	}else if(reg_code==IP){
		ip=data;
	}else if(reg_code==IO){
		io=data;
	}else if(reg_code==SP){
		sp=data;
	}else if(reg_code==SO){
		sp=data;
	}else if(reg_code==STRATCH_REGISTER){
		scratch=data;
	}else if(reg_code==STRATCH_REGISTER2){
		scratch2=data;
	}
}
u32 get_reg_address(u8 reg_code){
	if(reg_code==R0){
		u32 o =r0o;
		o=o<<0x10;
		o+=r0;
		return o;
	}else if(reg_code==R1){
		u32 o = r1o;
		o=o<<0x10;
		o+=r1;
		return o;
	}else if(reg_code==IP){
		u32 o=io;
		o=o<<0x10;
		o+=ip;
		return o;
	}else if(reg_code==SP){
		u32 o=so;
		o<<0x10;
		o+=sp;
		return o;
	}else{
		add_log(ERROR,"invalid instruction","invalid instruction");
	}
}
void log_state(){
	char string[80];
	sprintf(string,"r0: %i \nr1: %i\nip: %i\nsp: %i\n",r0,r1,ip,sp);
	add_log(CPU_STATE,"register state",string);
}
#define M_NULL_INS 0x0
/* LOAD memory at address into register at source operand
 */
#define M_LOAD_MEM 0x1
// Move contents of reg at source to destination
// No memory access
#define M_MOV_REG 0x2


#define TO_EXEC 0
#define M_WAIT 1
struct microins{
	//INSTRUCTIONS needed for mov
	#define NULL_INS 0x0
	#define LOAD 0x1 //LOADS source addr from memory into reg at destination
	#define REG_MOV 0x2 //copyies datain src reg to dest reg
	#define REG_MOV_C 0x3//copies const data in src to dest reg
	#define MEM_WRITE_C 0x4 //writes data in source register to const destination address
	#define MEM_WRITE_R 0x5 //writes data in source reg to reg destination
	#define INCR_REG 0x6 //increments src reg by 1
	#define DECR_REG 0x7 //decrements src reg by 1
	#define ADD_REG 0x8 //adds src to dest and writes back to dest
	#define ADD_C 0x9 //adds constant to dest and writes to res to dest
	unsigned short opcode=0;
	unsigned short source=0;
	unsigned short destination=0;
	unsigned char progress=TO_EXEC;

};

#define MAX_QUEUE 0x20
struct micro_stack{
	struct microins to_execute[MAX_QUEUE];
	unsigned char size=0;
};
void push_microins(struct micro_stack *stack,struct microins instruction){
	char s[80];
	sprintf(s,"pushing opcode %i onto microstack",instruction.opcode);
	add_log(INFO,"push_microins",s);
	sprintf(s,"current_ins: 0x%x\n",stack->size);
	add_log(INFO,"push_microins",s);
	if(stack->size<MAX_QUEUE){
		stack->to_execute[stack->size]=instruction;
		stack->size++;
	}
	return;
};
struct microins get_ins(struct micro_stack *stack){
	if(stack->size>0){
		return stack->to_execute[0];
	}else{
		struct microins t;
		return t;
	}
}
void pop_top_microins(struct micro_stack *stack){
	add_log(INFO,"pop_top_microins","poping instruction");
	if(stack->size>1){
		for(int i=1;i<stack->size;i++){
			stack->to_execute[i-1]=stack->to_execute[i];
		}
		stack->size--;
	}else{
		stack->size=0;
	}
	
}
int get_stack_size(struct micro_stack *stack){
	return stack->size;
}
void print_microstack(struct micro_stack *stack){
	char st[80] = "Microstack stack_size: %i";
	sprintf(st,"Microstack stack_size: %i",get_stack_size(stack));
	add_log(INFO,"microstack instuctions",st);
	for(int i=0;i<get_stack_size(stack);i++){
		char s[80];
		sprintf(s,"opcode: %x dest: %x source: %x\n",
			stack->to_execute[i].opcode,
			stack->to_execute[i].destination,
			stack->to_execute[i].source);
		add_log(INFO,"microstack instuctions",s);
	}
}
struct micro_stack MICRO_STACK;
#define NOT_DONE_EXEC 0x0
#define DONE_EXEC 0x1
//used if cpu is to halt
#define HALT 0x2
#define FALSE 0
#define TRUE 1
char execute_instruction(struct bus *sys_bus,struct ram_bus *ram,char can_mem){
	add_log(INFO,"execute_instruction","starting to execute instruction");
	print_microstack(&MICRO_STACK);
	if(get_stack_size(&MICRO_STACK)==0){
		add_log(INFO,"execute_instruction","done executing instruction");
		return DONE_EXEC;
	}
	struct microins ins = get_ins(&MICRO_STACK);
	if(ins.opcode!=NULL_INS){
		if(ins.opcode==LOAD){
			if(can_mem==FALSE)
				return NOT_DONE_EXEC;
			//do memory loading
			u32 addr = get_reg_address(ins.source);
			struct mem_result res = load_mem(ram,addr);
			
			if(res.progress==RES_DONE){
				set_register(ins.destination,res.data);
				pop_top_microins(&MICRO_STACK);
				return execute_instruction(sys_bus,ram,can_mem);
			}else{
				return NOT_DONE_EXEC;
			}

		}else if(ins.opcode==REG_MOV){
			u16 data = get_register(ins.source);
			set_register(ins.destination,data);
			pop_top_microins(&MICRO_STACK);
			return execute_instruction(sys_bus,ram,can_mem);

		}else if(ins.opcode==REG_MOV_C){
			set_register(ins.destination,ins.source);
			pop_top_microins(&MICRO_STACK);
			return execute_instruction(sys_bus,ram,can_mem);
		}else if(ins.opcode==MEM_WRITE_C){
			if(can_mem==FALSE)
				return NOT_DONE_EXEC;
			u32 addr=get_reg_address(ins.destination);
			struct mem_result res = write_mem(ram,addr,ins.source);
			if(res.progress==RES_DONE){
				pop_top_microins(&MICRO_STACK);
				return execute_instruction(sys_bus,ram,can_mem);
			}else{
				return NOT_DONE_EXEC;
			}

		}else if(ins.opcode==MEM_WRITE_R){
			if(can_mem==FALSE)
				return NOT_DONE_EXEC;
			u32 addr=get_reg_address(ins.destination);
			u16 data = get_register(ins.source);
			struct mem_result res = write_mem(ram,addr,data);
			if(res.progress==RES_DONE){
				pop_top_microins(&MICRO_STACK);
				return execute_instruction(sys_bus,ram,can_mem);
			}else{
				return NOT_DONE_EXEC;
			}


		}else if(ins.opcode==INCR_REG){
			char buffer[80];
			sprintf(buffer,"incrementing 0x%x\n",ins.source);

			add_log(INFO,"execute_instruction",buffer);
			u16 data = get_register(ins.source);
			data++;
			set_register(ins.source,data);
			pop_top_microins(&MICRO_STACK);
			return execute_instruction(sys_bus,ram,can_mem);
		}else if(ins.opcode==DECR_REG){
			u16 data = get_register(ins.source);
			data--;
			set_register(ins.source,data);
			pop_top_microins(&MICRO_STACK);
			return execute_instruction(sys_bus,ram,can_mem);
		}else if(ins.opcode==ADD_REG){
			u16 data = get_register(ins.source);
			data+=get_register(ins.destination);
			set_register(ins.destination,data);
			pop_top_microins(&MICRO_STACK);
			return execute_instruction(sys_bus,ram,can_mem);

		}else if(ins.opcode==ADD_C){
			u16 data = get_register(ins.destination);
			data+=ins.source;
			set_register(ins.destination,data);
			pop_top_microins(&MICRO_STACK);
			return execute_instruction(sys_bus,ram,can_mem);
		}
	}else{
		add_log(ERROR,"execute instruction","null instruction found");
		return DONE_EXEC;

	}

}
void decode_instruction(unsigned int instruction){
	char s[80];
	sprintf(s,"raw opcode: 0x%x",instruction);
	add_log(INFO,"decode_instruction",s);

	//upcode is the upper 8 bytes of the instruct
	u32 temp = instruction>>0x10;
	u8 opcode = temp;	
	sprintf(s,"interperted opcode: 0x%x",opcode);
	add_log(INFO,"decode_instruction",s);
	//getting the second byte
	u8 regs = (instruction&0x0F00)>>0x10;
	u16 constant = instruction&0x00FF;
	//move reg into reg
	u8 dest_reg = (regs & 0b11110000)>>0x4;
	u8 src_reg = regs & 0b00001111;
	sprintf(s,"src reg: 0x%x",src_reg);
	add_log(INFO,"decode_instruction",s);
	sprintf(s,"dest reg: 0x%x",dest_reg);
	add_log(INFO,"decode_instruction",s);
	if(opcode==0x0){
		if(dest_reg&0b1000==0b1000){
			//dest is pointer
			if(src_reg&0b1000==0b1000){
				//src is ptr
				//instructions:
				//load scratch_reg src_reg
				//MEM_WRITE_R dest_reg scratch_reg
				//REG_MOV_C scratch_reg 0
				//incr ip
				struct microins ins;
					ins.opcode=LOAD;
					ins.source=src_reg;
					ins.destination=STRATCH_REGISTER;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=MEM_WRITE_R;
					ins.source=STRATCH_REGISTER;
					ins.destination=dest_reg;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=REG_MOV_C;
					ins.destination=STRATCH_REGISTER;
					ins.source=0;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=INCR_REG;
					ins.source=IP;
				push_microins(&MICRO_STACK,ins);
				print_microstack(&MICRO_STACK);
			}
			if(src_reg&0b1000==0b0000){
				struct microins ins;
					ins.opcode=MEM_WRITE_R;
					ins.source=src_reg;
					ins.destination=dest_reg;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=INCR_REG;
					ins.source=IP;
				push_microins(&MICRO_STACK,ins);

				//src is reg
				//instructions:
				//MEM_WRITE_R dest_reg src_reg
				//incr ip
			}
			
		}
		if(dest_reg&0b1000==0b0000){
			//dest is not pointer
			if(src_reg&0b1000==0b1000){
				//src is a ptr
				//LOAD scratch_reg src_reg
				//REG_MOV dest_reg scratch_reg
				//REG_MOV_C scratch_reg 0
				struct microins ins;
					ins.opcode=LOAD;
					ins.source=src_reg;
					ins.destination=STRATCH_REGISTER;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=REG_MOV;
					ins.source=STRATCH_REGISTER;
					ins.destination=dest_reg;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=REG_MOV_C;
					ins.source=0;
					ins.destination=STRATCH_REGISTER;
				push_microins(&MICRO_STACK,ins);
				
			}
			if(src_reg&0b1000==0b0000){
				//src is not a ptr
				//REG_MOV dest_reg src_reg
				struct microins ins;
					ins.opcode=REG_MOV;
					ins.source=src_reg;
					ins.destination=dest_reg;
				push_microins(&MICRO_STACK,ins);
			}

		}
		

	}
	if(opcode==0x80){
		add_log(INFO,"decode_instruction","decoding mov constant");
		//mov constant
		//desst is ptr
		char buff[80];
		sprintf(buff,"dest_reg&0b1000: 0x%x\n",dest_reg&0b1000);
		add_log(INFO,"decode_instruction",buff);
		if(dest_reg&0b100==0b100){
			add_log(INFO,"decode_instruction",
				"decoding mov constant when dest is ptr");
			//MEM_WRITE_C constant
			//ADD_C ip 4
			struct microins ins;
				ins.opcode=MEM_WRITE_C;
				ins.source=constant;
				ins.destination=dest_reg;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=ADD_C;
				ins.source=4;
				ins.destination=IP;
			push_microins(&MICRO_STACK,ins);
		}else{
			//dest is not ptr
			//REG_MOV_C dest_reg constant
			//ADD_C ip 4
			add_log(INFO,"decode_instruction",
				"decoding mov constant when dest is not ptr");
			struct microins ins;
				ins.opcode=REG_MOV_C;
				ins.source=constant;
				ins.destination=dest_reg;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=ADD_C;
				ins.source=4;
				ins.destination=IP;
			push_microins(&MICRO_STACK,ins);
		}
	}
	//jmp [reg]
	if(opcode==0x01){
		add_log(INFO,"decode instruction","jump reg");
		//if ptr
		if(src_reg&0b100==0b100){
			//LOAD ip src_reg
			struct microins ins;
				ins.opcode=LOAD;
				ins.source=src_reg;
				ins.destination=IP;
			push_microins(&MICRO_STACK,ins);
		}else{
		//if not ptr
			//REG_MOV ip src_reg
			struct microins ins;
				ins.opcode=REG_MOV;
				ins.source=src_reg;
				ins.destination=IP;
			push_microins(&MICRO_STACK,ins);
		}
	}
	//jmp addr
	if(opcode==0x81){
		//REG_MOV_C constant
		struct microins ins;
			ins.opcode=REG_MOV_C;
			ins.source=constant;
			ins.destination=IP;
		push_microins(&MICRO_STACK,ins);
	}
	//call [reg]
	if(opcode==0x02){
		if(src_reg&0b1000==0b1000){
			//src is ptr
			//incr sp
			//load scratch_reg src_reg
			//MEM_WRITE_R sp ip
			//REG_MOV ip scratch_reg
			//REG_MOV STRATCH_REGISTER 0
			struct microins ins;
				ins.opcode=INCR_REG;
				ins.source=sp;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=LOAD;
				ins.source=src_reg;
				ins.destination=STRATCH_REGISTER;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=MEM_WRITE_R;
				ins.source=IP;
				ins.destination=SP;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=REG_MOV;
				ins.source=STRATCH_REGISTER;
				ins.destination=IP;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=REG_MOV_C;
				ins.source=0;
				ins.destination=STRATCH_REGISTER;
			push_microins(&MICRO_STACK,ins);
		}
		if(src_reg&0b1000==0b0000){
			//src is not ptr
			//incr sp
			//MEM_WRITE_R sp ip
			//REG_MOV ip src_reg
			struct microins ins;
				ins.opcode=INCR_REG;
				ins.source=SP;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=MEM_WRITE_R;
				ins.source=IP;
				ins.destination=SP;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=REG_MOV;
				ins.source=src_reg;
				ins.destination=IP;


		}
	}
	//call constant
	if(opcode==0x82){
		//incr sp
		//MEM_WRITE_R sp ip
		//REG_MOV_C ip constant
		struct microins ins;
			ins.opcode=INCR_REG;
			ins.source=SP;
		push_microins(&MICRO_STACK,ins);
			ins.opcode=MEM_WRITE_R;
			ins.source=IP;
			ins.destination=SP;
		push_microins(&MICRO_STACK,ins);
			ins.opcode=REG_MOV_C;
			ins.source=constant;
			ins.destination=ip;
		push_microins(&MICRO_STACK,ins);
	}
	//ret
	if(opcode==0x3||opcode==0x83){
		//LOAD IP SP
		//DEC SP
		struct microins ins;
			ins.opcode=LOAD;
			ins.source=SP;
			ins.destination=IP;
		push_microins(&MICRO_STACK,ins);
			ins.opcode=DECR_REG;
			ins.source=SP;
		push_microins(&MICRO_STACK,ins);
	}
	//push reg
	if(opcode==0x04){
		if(src_reg&0b1000==0b1000){
			//src is ptr
			//incr SP
			//LOAD scratch_reg src_reg
			//MEM_WRITE_R SP scratch_reg
			//REG_MOV_C scratch_reg 0
			struct microins ins;
				ins.opcode=INCR_REG;
				ins.source=SP;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=LOAD;
				ins.source=src_reg;
				ins.destination=STRATCH_REGISTER;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=MEM_WRITE_R;
				ins.source=STRATCH_REGISTER;
				ins.destination=SP;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=REG_MOV_C;
				ins.source=0;
				ins.destination=STRATCH_REGISTER;
			push_microins(&MICRO_STACK,ins);
		}if(src_reg&0b1000==0b0000){
			//src is not ptr
			//incr sp
			//MEM_WRITE_R sp src_reg
			struct microins ins;
				ins.opcode=INCR_REG;
				ins.source=SP;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=MEM_WRITE_R;
				ins.source=src_reg;
				ins.destination=SP;
			push_microins(&MICRO_STACK,ins);
		}
	}
	//push constant
	if(opcode==0x84){
		//incr sp
		//MEM_WRITE_C sp, constant
		struct microins ins;
			ins.opcode=INCR_REG;
			ins.source=SP;
		push_microins(&MICRO_STACK,ins);
			ins.opcode=MEM_WRITE_C;
			ins.source=constant;
			ins.destination=SP;
		push_microins(&MICRO_STACK,ins);
	}
	if(opcode==0x05){
		if(src_reg&0b1000==0b1000){
			//register is ptr memory
			//MEM_WRITE_R dest_reg SP
			//dec SP
			struct microins ins;
				ins.opcode=MEM_WRITE_R;
				ins.source=SP;
				ins.destination=dest_reg;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=DECR_REG;
				ins.source=SP;
			push_microins(&MICRO_STACK,ins);
		}
		if(src_reg&0b1000==0b0000){
			//register is not a ptr
			//LOAD dest_reg SP
			//DEC SP
			struct microins ins;
				ins.opcode=LOAD;
				ins.source=SP;
				ins.destination=dest_reg;
			push_microins(&MICRO_STACK,ins);
				ins.opcode=DECR_REG;
				ins.source=SP;
			push_microins(&MICRO_STACK,ins);
		}
	}if(opcode==0x06){
		//ADD
		if(src_reg&0b1000==0b1000){
			//src is ptr
			if(dest_reg&0b1000==0b1000){
				//dest is ptr
				//LOAD scratch_reg src;
				//LOAD STRATCH_REGISTER2 dest;
				//ADD STRATCH_REGISTER2 STRATCH_REGISTER
				//MEM_WRITE_R dest_reg STRATCH_REGISTER
				struct microins ins;
					ins.opcode=LOAD;
					ins.source=src_reg;
					ins.destination=STRATCH_REGISTER;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=LOAD;
					ins.source=dest_reg;
					ins.destination=STRATCH_REGISTER2;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=ADD_REG;
					ins.source=STRATCH_REGISTER;
					ins.destination=STRATCH_REGISTER2;
				push_microins(&MICRO_STACK,ins);
					ins.source=MEM_WRITE_R;
					ins.source=STRATCH_REGISTER2;
					ins.destination=dest_reg;
				push_microins(&MICRO_STACK,ins);
			}if(dest_reg&0b1000==0b0000){
				//dest is not ptr
				//LOAD STRATCH_REGISTER src
				//ADD dest_reg STRATCH_REGISTER
				//dest is not ptr
				struct microins ins;
					ins.opcode=LOAD;
					ins.source=src_reg;
					ins.destination=STRATCH_REGISTER;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=ADD_REG;
					ins.source=STRATCH_REGISTER;
					ins.destination=dest_reg;
				push_microins(&MICRO_STACK,ins);

			}
		}
		if(src_reg&0b1000==0b0000){
			//src is not ptr
			
			if(dest_reg&0b1000==0b1000){
				//dest is ptr
				//LOAD STRATCH_REGISTER dest_reg
				//ADD STRATCH_REGISTER src_reg
				//MEM_WRITE_R dest_reg STRATCH_REGISTER
				struct microins ins;
					ins.opcode=LOAD;
					ins.source=dest_reg;
					ins.destination=STRATCH_REGISTER;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=ADD_REG;
					ins.source=src_reg;
					ins.destination=STRATCH_REGISTER;
				push_microins(&MICRO_STACK,ins);
					ins.opcode=MEM_WRITE_R;
					ins.source=STRATCH_REGISTER;
					ins.destination=dest_reg;
				push_microins(&MICRO_STACK,ins);

			}if(dest_reg&0b1000==0b0000){
				//dest is not ptr
				//ADD dest_reg src_reg
				struct microins ins;
					ins.opcode=ADD_REG;
					ins.source=src_reg;
					ins.destination=dest_reg;
				push_microins(&MICRO_STACK,ins);

			}
		}
	}
	
	//out
	if(opcode==0xA){
		//src is ptr
		if(src_reg&0b1000==0b1000){
			if(dest_reg&0b1000==0b1000){
				//dest is ptr
			}
			if(dest_reg&0b1000==0b000){
				//dest is not ptr
			}
		}
		if(src_reg&0b1000==0){
			//src is not ptr
			if(dest_reg&0b1000==0b1000){
				//dest is ptr
			}
			if(dest_reg&0b1000==0b000){
				//dest is not ptr
			}
		}
	}


}
/* CPU LOOP:
 *  Decode instruction
 *  push instruction to stack
 *  execute micro-instruction
 *
 *
 */
struct cpu_state{
    #define INSTRUCTION_DECODE 0x1
    #define INSTRUCTION_EXECUTE 0x2
    char main_task=INSTRUCTION_DECODE;
    #define START 0x0
    #define MEM_LOAD_1ST_SHORT 0x1
    #define MEM_LOAD_2ND_SHORT 0x2
    //instruction execution
    #define INSTRUCTION_EXECUTE_BEGIN 0x0

    char sub_task=START;
};
struct cpu_state STATE;
unsigned int TEMP_INSTRUCTION;
void tick_micro_ins(struct bus *sys_bus,struct ram_bus *in){
	log_state();
	tick_mem();
	if(STATE.main_task==INSTRUCTION_DECODE){
		if(STATE.sub_task==START){
		    struct mem_result res = load_mem(in,get_register(IP));	
			STATE.sub_task=MEM_LOAD_1ST_SHORT;
			add_log(INFO,"read first instruction","");
			return;
		}
		if(STATE.sub_task==MEM_LOAD_1ST_SHORT){
		    struct mem_result res = load_mem(in,get_register(IP));	
			add_log(INFO,"starting to read first short\n","");
			if(res.progress==RES_DONE){
				TEMP_INSTRUCTION=res.data;
				//setting the upper 0x10 bytest to the first half of the instruction
				TEMP_INSTRUCTION=TEMP_INSTRUCTION<<0x10;
				STATE.sub_task=MEM_LOAD_2ND_SHORT;
				STATE.main_task=INSTRUCTION_DECODE;
				add_log(INFO,"Read 1/2 of Instruction","");
				return;
			}
			return;
		}
		if(STATE.sub_task==MEM_LOAD_2ND_SHORT){
		    struct mem_result res = load_mem(in,get_register(IP)+2);	
			if(res.progress==RES_DONE){
				TEMP_INSTRUCTION+=res.data;
				//setting the upper 0x10 bytest to the first half of the instruction
				STATE.main_task=INSTRUCTION_EXECUTE;
				STATE.sub_task=START;
				add_log(INFO,"Read full Instruction","");
				decode_instruction(TEMP_INSTRUCTION);
				char status = execute_instruction(sys_bus,in,FALSE);
				if(status==DONE_EXEC){
					STATE.main_task=INSTRUCTION_DECODE;
					STATE.sub_task=MEM_LOAD_1ST_SHORT;
				}
				return;
			}
			return;

		}
	}
	
	if(STATE.main_task==INSTRUCTION_EXECUTE){
		char status = execute_instruction(sys_bus,in,TRUE);
		if(status==DONE_EXEC){
			STATE.main_task=INSTRUCTION_DECODE;
			STATE.sub_task=MEM_LOAD_1ST_SHORT;
		}

	}
}
