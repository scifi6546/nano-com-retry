#include "../bus.h"
#define RES_NOT_DONE 0
#define RES_DONE 1
struct mem_result{
	unsigned short data=0;
	unsigned char progress=RES_NOT_DONE;
};
struct mem_result load_mem(struct ram_bus *bus,unsigned int address);
struct mem_result write_mem(struct ram_bus *bus,unsigned int address,unsigned short data);
//called to skip current memory cycle
//load_mem and write_mem will return RES_NOT_DONE
void skip_cycle();
//called at start of every bus tick. 
void tick_mem();
