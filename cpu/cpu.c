#define MOV 0x00
#define JMP 0x01
#define CALL 0x02
#define RET 0x03
char opcode=0xFF;
char arg1 = 0x0;
char arg2 = 0x0;
#define OPCODE_READ 0x00
#define OPRAND0_READ 0x01
#define OPARAND1_READ 0x02
char next_stage = 0x0;
struct registers{
	char r0 =0;
	char r0o=0;
	char r1 =0;
	char r1o=0;
	char ip =0;
	char io =0;
	char sp =0;
	char so =0;
}
struct registers current_reg;
void boot_cpu(){
}
void cpu_tick(struct bus *sys_bus,struct ram_bus *in){
	if(next_stage==OPCODE_READ){
		//read first opcode from memory
	}else if(next_stage==OPRAND0_READ){
		//read 0th operand from memory and if opcode&0x80==0 execute instruction

	}else if(next_stage==OPARAND1_READ){
		//read 1st operand from memory and execute
	}
}
