#include "../bus.h"
#define NOT_DONE 0
#define DONE 1
struct mem_result{
	unsigned short data=0;
	unsigned char progress=NOT_DONE;
};
struct mem_result load_mem(struct ram *bus,unsigned int address);
