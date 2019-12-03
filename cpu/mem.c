#include "mem.h"
#include "../logger.h"
#include <stdio.h>
#define DEVICE_SELECT 0x1
#define ADDRESS_WRITE 0x2
#define MMU_READ      0x3
#define DATA_READ     0x4
//counts number of memory ops in a tick
//set to 1 initially so that system does not error out
//on boot
char MEM_OPS_TICK=1;
char SKIP_CYCLE=0;
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
		if(!SKIP_CYCLE){
			bus->address_bus=address;
			bus->WRITE_OR_READ=READ;
		}
		memory_stage=MMU_READ;
	}else if(memory_stage==MMU_READ){
		memory_stage=DATA_READ;
	}else if(memory_stage==DATA_READ){
		if(!SKIP_CYCLE){
			memory_stage=DEVICE_SELECT;
			struct mem_result res;
			res.data = bus->data_bus;
			res.progress=RES_DONE;
			return res;
		}else{
			memory_stage=DEVICE_SELECT;
			SKIP_CYCLE=0;
		}
	}
	struct mem_result res;
	return res;

}
struct mem_result write_mem(struct ram_bus *bus,unsigned int address,unsigned short data){
	if(MEM_OPS_TICK!=0){
		add_log(ERROR,"RUNNING 2 MEM OPS in 1 CYCLE!","");
	}else{
		MEM_OPS_TICK++;	
	}
	if(memory_stage==DEVICE_SELECT){
		memory_stage=ADDRESS_WRITE;
	}else if(memory_stage==ADDRESS_WRITE){
		if(!SKIP_CYCLE){
			bus->WRITE_OR_READ=WRITE;
			bus->address_bus=address;
			bus->data_bus=data;
		}
		memory_stage=MMU_READ;
	}else if(memory_stage==MMU_READ){

		memory_stage=DATA_READ;
	}else if(memory_stage==DATA_READ){
		memory_stage=DEVICE_SELECT;
		if(!SKIP_CYCLE){
			struct mem_result res;
			res.progress=RES_DONE;
			return res;
		}else{
			SKIP_CYCLE=0;
		}
	}
	struct mem_result res;
	return res;
}
void skip_cycle(){
	add_log(INFO,"skip_cycle",
			"skipping current memory cycle");
	SKIP_CYCLE=1;
}
void tick_mem(){
	if(MEM_OPS_TICK!=0){
		MEM_OPS_TICK=0;
	}else{
		if(!SKIP_CYCLE){
			add_log(ERROR,"RAM did not tick!","");
		}else{
			MEM_OPS_TICK=0;
			//advancing ticks
			if(memory_stage==DEVICE_SELECT)
				memory_stage=ADDRESS_WRITE;
			else if(memory_stage==ADDRESS_WRITE)
				memory_stage=MMU_READ;
			else if(memory_stage==MMU_READ)
				memory_stage=DATA_READ;
			else if(memory_stage==DATA_READ){
				memory_stage=DEVICE_SELECT;
				SKIP_CYCLE=0;
			}else
				add_log(ERROR,"tick_mem","invalid memory_stage");
			add_log(INFO,"tick_mem","skipping cycle");
		}
	}
}
