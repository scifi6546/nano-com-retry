#include "mem.h"
#include "logger.h"
#include <stdio.h>
#define DEVICE_SELECT 0x1
#define ADDRESS_WRITE 0x2
#define MMU_READ      0x3
#define DATA_READ     0x4
//counts number of memory ops in a tick
//set to 1 initially so that system does not error out
//on boot
char MEM_OPS_TICK=1;
unsigned char memory_stage=DEVICE_SELECT;
struct mem_result load_mem(struct ram_bus *bus,unsigned int address){
	if(MEM_OPS_TICK!=0){
		add_log(ERROR,"RUNNING 2 MEM OPS in 1 CYCLE!","");
	}else{
		MEM_OPS_TICK++;	
	}
	if(memory_stage==DEVICE_SELECT){
		memory_stage=ADDRESS_WRITE;
	}else if(memory_stage==ADDRESS_WRITE){
		bus->address_bus=address;
		bus->WRITE_OR_READ=READ;
		memory_stage=MMU_READ;
	}else if(memory_stage==MMU_READ){
		memory_stage=DATA_READ;
	}else if(memory_stage==DATA_READ){
		memory_stage=DEVICE_SELECT;
		struct mem_result res;
		res.data = bus->data_bus;
		res.progress=RES_DONE;
		return res;
	}
	struct mem_result res;
	return res;

}
//not done
struct mem_result write_mem(struct ram_bus *bus,unsigned int address,unsigned short data){
	if(MEM_OPS_TICK!=0){
		add_log(ERROR,"RUNNING 2 MEM OPS in 1 CYCLE!","");
	}else{
		MEM_OPS_TICK++;	
	}
	if(memory_stage==DEVICE_SELECT){
		memory_stage=ADDRESS_WRITE;
	}else if(memory_stage==ADDRESS_WRITE){
		bus->WRITE_OR_READ=WRITE;
		bus->address_bus=address;
		bus->data_bus=data;
		memory_stage=MMU_READ;
	}else if(memory_stage==MMU_READ){

		memory_stage=DATA_READ;
	}else if(memory_stage==DATA_READ){
		struct mem_result res;
		res.progress=RES_DONE;
		return res;
	}
	struct mem_result res;
	return res;
}
void tick_mem(){
	if(MEM_OPS_TICK!=0){
		MEM_OPS_TICK=0;
	}else{
		add_log(ERROR,"RAM did not tick!","");
	}
}
